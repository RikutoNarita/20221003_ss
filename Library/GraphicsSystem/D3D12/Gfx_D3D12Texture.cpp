//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 12テクスチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc テクスチャの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D12Texture::GfxD3D12Texture(Description desc)
: GfxTexture(desc)
{
    HRESULT hr = S_OK;
    ID3D12Device* pDevice = DX->GetDevice<ID3D12Device>();

    // WriteToSubResourceで転送するためのヒープ設定
    D3D12_HEAP_PROPERTIES heapProp = {};
    heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;                         // カスタム設定
    heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;  // ライトバック
    heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;            // メモリプールL0
    heapProp.CreationNodeMask = 0;                                  // シングルアダプターなのでMaskは0
    heapProp.VisibleNodeMask = 0;                                   // シングルアダプターなのでMaskは0

    // テクスチャリソースの設定
    D3D12_RESOURCE_DESC textrueResourceDesc = {};
    textrueResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;            // 8ビット、0.0f～1.0fに正規化された浮動小数点
    textrueResourceDesc.Width = m_desc.width;                           // 幅
    textrueResourceDesc.Height = m_desc.height;                         // 高さ
    textrueResourceDesc.DepthOrArraySize = 1;                           // リソースの配列のサイズ
    textrueResourceDesc.SampleDesc.Count = 1;                           // アンチエイリアシングしない
    textrueResourceDesc.SampleDesc.Quality = 0;                         // クオリティは最低
    textrueResourceDesc.MipLevels = 1;                                  // ミップマップしないので１を指定
    textrueResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; // 2Dテクスチャとして使用
    textrueResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;          // レイアウトの指定なし
    textrueResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;               // オプション指定なし
    // テクスチャバッファの生成
    hr = pDevice->CreateCommittedResource(
        &heapProp,                                  // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                       // 指定なし
        &textrueResourceDesc,                       // リソースの設定
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ用指定
        nullptr,
        IID_PPV_ARGS(&m_pTextureBuffer));           // テクスチャバッファー
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_TEX12");
    
    // テクスチャバッファーの転送
    UINT scrRow     = m_desc.byteSize * m_desc.width;
    UINT scrDepth   = m_desc.byteSize * m_desc.width * m_desc.height;
    hr = m_pTextureBuffer->WriteToSubresource(
        0,                                              // サブリソースインデックス
        nullptr,                                        // 書き込み領域の指定（０：全域へコピー）
        m_desc.pData,                                   // テクスチャデータのアドレス
        scrRow,                                         // 横1列のサイズ
        scrDepth);                                      // テクスチャデータの大きさ
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_TEX12");
    
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12Texture::~GfxD3D12Texture()
{
}

void GfxD3D12Texture::Bind(unsigned slot) const
{
    UNREFERENCED_PARAMETER(slot);
}
