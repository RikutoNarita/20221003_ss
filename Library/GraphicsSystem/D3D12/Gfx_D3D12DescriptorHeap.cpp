﻿//==============================================================================
// Filename: Gfx_D3D12DiscriptorHeap.h
// Description: ディスクリプタヒープクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12DescriptorHeap.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12DescriptorHeap::GfxD3D12DescriptorHeap()
    : m_vertexResourceSRV{nullptr}, m_vertexResourceCBV{nullptr}
    , m_pixelResourceSRV{nullptr}, m_pixelResourceCBV{nullptr}
    , m_descriptorHandleIncrementSize(0)
{
    GfxTexture* pTex = GfxGraphicsResource::Find<GfxTexture>(TEX_DEFAULT);
    // 定数バッファとテクスチャバッファにゴミデータを入れておく
    for (UINT i = 0; i < MAX_TEXTURE; i++)
    {
        m_pixelResourceSRV[i] = dynamic_cast<GfxD3D12Texture*>(pTex)->Get();
        m_vertexResourceSRV[i] = dynamic_cast<GfxD3D12Texture*>(pTex)->Get();;
    }
    GfxConstantBuffer* pBuffer = GfxGraphicsResource::Find<GfxConstantBuffer>(CB_DEFAULT);

    for (UINT i = 0; i < MAX_CONSTANTBUFFER; i++)
    {
        m_pixelResourceCBV[i] = dynamic_cast<GfxD3D12ConstantBuffer*>(pBuffer)->Get();
        m_vertexResourceCBV[i] = dynamic_cast<GfxD3D12ConstantBuffer*>(pBuffer)->Get();;
    }
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12DescriptorHeap::~GfxD3D12DescriptorHeap()
{
}

//------------------------------------------------------------------------------
/// ディスクリプタヒープの作成
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12DescriptorHeap::Create()
{
    // デバイスの取得
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();

    //--- ディスクリプタヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC basicDescHeapDesc = {};
    basicDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;            // シェーダーから見えるように
    basicDescHeapDesc.NodeMask = 0;                                                    // マスクは０
    basicDescHeapDesc.NumDescriptors = (MAX_TEXTURE + MAX_CONSTANTBUFFER) * 2;      // SRV, CBVの数の合計
    basicDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;                // デスクリプタヒープのタイプ(定数バッファ、シェーダーリソース)
    auto hr = pDevice->CreateDescriptorHeap(&basicDescHeapDesc, IID_PPV_ARGS(&m_pSRVandCSBheap));
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_DESCRIPTOR");

    /*
    * ルートパラメーターの数 = 2
    * ピクセルシェーダーにバインドするためのルートパラメーターと頂点シェーダーにバインドするためのルートパラメーターの2つを用意
    *
    * ディスクリプタテーブルの数 = 4
    * ピクセルシェーダーにバインドするためのルートパラメーターに設定するディスクリプタテーブルはSRV用, CBV用の２つ
    * 頂点シェーダーにバインドするためのルートパラメーターに設定するディスクリプタテーブルはSRV用, CBV用の２つの計４つを用意
    * 
    *                    → table1 → SRV(view num, finrst slot)
    * rootParam1 → PIXEL
    *                    → table2 → CBV(view num, first slot)
    * 
    * 
    *                    → table3 → SRV(view num, first slot)
    * rootParam2 →VERTEX 
    *                    → table4 → CBV(view num, first slot)
    */

    // ヒープの先頭アドレス
    auto handle = m_pSRVandCSBheap->GetCPUDescriptorHandleForHeapStart();
    // インクリメントサイズの保存
    m_descriptorHandleIncrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    // SRVの設定
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                                // RGBA(0.0f～1.0fに正規化)
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;                      // 2Dテクスチャを指定
    srvDesc.Texture2D.MipLevels = 1;                                            // ミップマップは使用しないので０
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; // 指定されたフォーマットにデータ通りの順序で割り当てる
    //--- ディスクリプタヒープにピクセルシェーダー用のSRVを入れる
    for (size_t i = 0; i < MAX_TEXTURE; i++)
    {
        // シェーダーリソースの生成
        pDevice->CreateShaderResourceView(m_pixelResourceSRV[i], &srvDesc, handle);
        // ハンドルを1つ進める
        handle.ptr += m_descriptorHandleIncrementSize;
    }
    //--- ディスクリプタヒープにピクセルシェーダー用のCBVを入れる
    for (size_t i = 0; i < MAX_CONSTANTBUFFER; i++)
    {
        // CBVの設定
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation = m_pixelResourceCBV[i]->GetGPUVirtualAddress();
        cbvDesc.SizeInBytes = (UINT)m_pixelResourceCBV[i]->GetDesc().Width;
        // 定数バッファの作成
        pDevice->CreateConstantBufferView(&cbvDesc, handle);
        // ハンドルを1つ進める
        handle.ptr += m_descriptorHandleIncrementSize;
    }
    //--- ディスクリプタヒープに頂点シェーダー用のSRVを入れる
    for (size_t i = 0; i < MAX_TEXTURE; i++)
    {
        // シェーダーリソースの生成
        pDevice->CreateShaderResourceView(m_vertexResourceSRV[i], &srvDesc, handle);
        // ハンドルを1つ進める
        handle.ptr += m_descriptorHandleIncrementSize;
    }
    //--- ディスクリプタヒープに頂点シェーダー用のCBVを入れる
    for (size_t i = 0; i < MAX_CONSTANTBUFFER; i++)
    {
        // 定数バッファビューの設定
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation =m_vertexResourceCBV[i]->GetGPUVirtualAddress();
        cbvDesc.SizeInBytes = (UINT)m_vertexResourceCBV[i]->GetDesc().Width;
        // 定数バッファの作成
        pDevice->CreateConstantBufferView(&cbvDesc, handle);
        // ハンドルを1つ進める
        handle.ptr += m_descriptorHandleIncrementSize;
    }

    //--- ディスクリプタテーブルの設定
    // ピクセルシェーダーのt0からSRVの数だけヒープを割り当てる
    m_descriptorTableRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;   // 種別はテクスチャ
    m_descriptorTableRange[0].BaseShaderRegister = 0;                        // 0スロットから
    m_descriptorTableRange[0].NumDescriptors = MAX_TEXTURE;                  // ディスクリプタの数
    m_descriptorTableRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;// 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    m_descriptorTableRange[0].RegisterSpace = 0;
    // ピクセルシェーダーのb0からBRVの数だけヒープを割り当てる
    m_descriptorTableRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;   // 種別はテクスチャ
    m_descriptorTableRange[1].BaseShaderRegister = 0;                        // 0スロットから
    m_descriptorTableRange[1].NumDescriptors = MAX_CONSTANTBUFFER;           // ディスクリプタの数
    m_descriptorTableRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;// 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    m_descriptorTableRange[1].RegisterSpace = 0;
    // ピクセルシェーダーのt0からSRVの数だけヒープを割り当てる
    m_descriptorTableRange[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;   // 種別はテクスチャ
    m_descriptorTableRange[2].BaseShaderRegister = 0;                        // 0スロットから
    m_descriptorTableRange[2].NumDescriptors = MAX_TEXTURE;                  // ディスクリプタの数
    m_descriptorTableRange[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;// 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    m_descriptorTableRange[2].RegisterSpace = 0;
    // ピクセルシェーダーのb0からBRVの数だけヒープを割り当てる
    m_descriptorTableRange[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;   // 種別はテクスチャ
    m_descriptorTableRange[3].BaseShaderRegister = 0;                        // 0スロットから
    m_descriptorTableRange[3].NumDescriptors = MAX_CONSTANTBUFFER;           // ディスクリプタの数
    m_descriptorTableRange[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;// 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    m_descriptorTableRange[3].RegisterSpace = 0;

    //--- ルートパラメーターの設定
    // ピクセルシェーダー用
    m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;          // 頂点シェーダーから見えるようにする
    m_rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    m_rootParameters[0].DescriptorTable.NumDescriptorRanges = 2;                    // ディスクリプタレンジ数
    m_rootParameters[0].DescriptorTable.pDescriptorRanges = &m_descriptorTableRange[0]; // 要素 0と1
    // 頂点シェーダー用
    m_rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;          // 頂点シェーダーから見えるようにする
    m_rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    m_rootParameters[1].DescriptorTable.NumDescriptorRanges = 2;                    // ディスクリプタレンジ数
    m_rootParameters[1].DescriptorTable.pDescriptorRanges = &m_descriptorTableRange[2]; // 要素 2と3

}

//------------------------------------------------------------------------------
/// ディスクリプタヒープのバインド
/// 
/// \param[in] slot レジスタ番号
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12DescriptorHeap::Bind(unsigned int slot) const
{
    UNREFERENCED_PARAMETER(slot);

    // コマンドリストの取得
    ID3D12GraphicsCommandList* pCmdList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();

    // ディスクリプタヒープをセット
    pCmdList->SetDescriptorHeaps(1, m_pSRVandCSBheap.GetAddressOf());

    auto handle = m_pSRVandCSBheap->GetGPUDescriptorHandleForHeapStart();
    // GPUにピクセルシェーダーに送るルートパラメーター(要素0)のアドレスを教える
    pCmdList->SetGraphicsRootDescriptorTable(0, handle);

    // 次のルートパラメータのアドレスへ
    handle.ptr += (MAX_TEXTURE + MAX_CONSTANTBUFFER) * static_cast<UINT64>(m_descriptorHandleIncrementSize);

    // GPUに頂点シェーダーに送るルートパラメーター(要素1)のアドレスを教える
    pCmdList->SetGraphicsRootDescriptorTable(1, handle);
}

//------------------------------------------------------------------------------
/// テクスチャのセット
///
/// \pramga[in] res     テクスチャリソース
/// \pramga[in] shader  シェーダーの種類
/// \pramga[in] slot    レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12DescriptorHeap::BindSRV(
    ID3D12Resource* data, GfxShader::KIND visible, UINT slot)
{
    if (slot < 0 || MAX_TEXTURE < slot) return;

    if (visible == GfxShader::KIND::KIND_VS)
    {
        //※ 警告の対処のため *& をつけています
        *&m_vertexResourceSRV[slot] = data;
    }
    else if (visible == GfxShader::KIND::KIND_PS)
    {
        *&m_pixelResourceSRV[slot] = data;
    }
}

//------------------------------------------------------------------------------
/// 定数バッファのセット
///
/// \pramga[in] res     定数バッファリソース
/// \pramga[in] shader  シェーダーの種類
/// \pramga[in] slot    レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12DescriptorHeap::BindCBV(
    ID3D12Resource* data, GfxShader::KIND visible, UINT slot)
{
    if (slot < 0 || MAX_CONSTANTBUFFER < slot) return;

    if (visible == GfxShader::KIND::KIND_VS)
    {
        //※ 警告の対処のため *& をつけています
        *&m_vertexResourceCBV[slot] = data;
    }
    else if (visible == GfxShader::KIND::KIND_PS)
    {
        //※ 警告の対処のため *& をつけています
        *&m_pixelResourceCBV[slot] = data;
    }
}
