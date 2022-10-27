//==============================================================================
// Filename: Gfx_D3D12RootSigunature.h
// Description: ルートシグネチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12RootSignature.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RootSignature::GfxD3D12RootSignature()
{
    
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RootSignature::~GfxD3D12RootSignature()
{
}

void GfxD3D12RootSignature::Create(GfxD3D12DescriptorHeap* pDescriptorHeap)
{
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();
    HRESULT hr = S_OK;
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;

    // ルートシグネチャにテクスチャのレジスタ種別、レジスタ番号の関連を記述
    // ディスクリプタレンジの設定
    //D3D12_DESCRIPTOR_RANGE descriptorTableRange[2] = {};
    //// テクスチャ用レジスタ
    //descriptorTableRange[0].NumDescriptors = 1;                             // ディスクリプタの数
    //descriptorTableRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;    // 種別はテクスチャ
    //descriptorTableRange[0].BaseShaderRegister = 0;                         // 0スロットから
    //descriptorTableRange[0].OffsetInDescriptorsFromTableStart =
    //    D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;                               // 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    //descriptorTableRange[0].RegisterSpace = 0;
    //// 定数バッファ用レジスタ
    //descriptorTableRange[1].NumDescriptors = 1;                             // ディスクリプタの数
    //descriptorTableRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;    // 種別は定数バッファ
    //descriptorTableRange[1].BaseShaderRegister = 0;                         // 0スロットから
    //descriptorTableRange[1].OffsetInDescriptorsFromTableStart =
    //    D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;                               // 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    //descriptorTableRange[1].RegisterSpace = 0;
    //
    //// ルートパラメータの作成
    //m_rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    //m_rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;                    // ディスクリプタレンジ数
    //m_rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorTableRange[0];
    //m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;           // ピクセルシェーダーから見えるようにする
    //
    //m_rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    //m_rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;                    // ディスクリプタレンジ数
    //m_rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorTableRange[1];
    //m_rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;          // 頂点シェーダーから見えるようにする

    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 横方向の繰り返し
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 縦方向の繰り返し
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 奥行きの繰り返し
    sampler.BorderColor
        = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;              // ボーダーは黒
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;         // ポイント
    sampler.MaxLOD = D3D12_FLOAT32_MAX;                       // ミップマップ最大値
    sampler.MaxLOD = 0.0f;                                    // ミップマップ最小値
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーから見える
    sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;     // リサンプリングしない

    // ルートシグネチャの設定
    D3D12_ROOT_SIGNATURE_DESC signatureDesc = {};
    signatureDesc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;   // 頂点情報がある
    signatureDesc.pParameters = pDescriptorHeap->m_rootParameters; // ルートパラメータ
    signatureDesc.NumParameters = _countof(pDescriptorHeap->m_rootParameters);       // ルートパラメータの数
    signatureDesc.pStaticSamplers = &sampler;                           // サンプラー
    signatureDesc.NumStaticSamplers = 1;                                // サンプラーの数

    // バイナリコードの作成
    hr = D3D12SerializeRootSignature(
        &signatureDesc,                         // ルートシグネチャの設定
        D3D_ROOT_SIGNATURE_VERSION_1_0,         // ルートシグネチャバージョン
        &m_pBlob,                               // ルートシグネチャのバッファー
        &pErrorBlob);                           // エラー処理
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_ROOT");
    }

    // ルートシグネチャの生成
    hr = pDevice->CreateRootSignature(
        0,                                  // ノードマスク
        m_pBlob->GetBufferPointer(),        // バッファーのアドレス
        m_pBlob->GetBufferSize(),           // バッファーのサイズ
        IID_PPV_ARGS(&m_pRootSignature));   // ルートシグネチャ
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_ROOT");
    }
}

// ルートシグネチャのバインド
void GfxD3D12RootSignature::Bind(unsigned slot) const
{
    auto pCommandList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();
    pCommandList->SetGraphicsRootSignature(m_pRootSignature.Get());
}
