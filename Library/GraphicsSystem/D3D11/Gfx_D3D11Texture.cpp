//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 11テクスチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11Texture.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc テクスチャの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D11Texture::GfxD3D11Texture(Description desc)
: GfxTexture(desc)
{
    HRESULT hr = S_OK;

    ID3D11Device* pDevice = GRAPHICS->GetDevice<ID3D11Device>();
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    
    D3D11_TEXTURE2D_DESC desc2D;
    desc2D.Width = desc.width;                     // テクスチャの幅
    desc2D.Height = desc.height;                    // テクスチャの高さ
    desc2D.MipLevels = 1;                           // ミップマップレベルの最大数
    desc2D.ArraySize = 1;                           // テクスチャ配列内のテクスチャの数
    desc2D.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // テクスチャ形式
    desc2D.SampleDesc.Count = 1;                    // マルチサンプリングの数
    desc2D.SampleDesc.Quality = 0;
    desc2D.Usage = D3D11_USAGE_DYNAMIC;             // テクスチャの読み取りと書き込み方法
    desc2D.BindFlags = D3D11_BIND_SHADER_RESOURCE;  // 用途
    desc2D.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // 許可されるCPUアクセスの種類を指定するためのフラグ 
    desc2D.MiscFlags = 0;                           // 一般的でないリソース オプションを識別するフラグ

    hr = pDevice->CreateTexture2D(&desc2D, nullptr, m_pTexture2D.GetAddressOf());
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_TEX11");

    // テクスチャ書き替え
    D3D11_MAPPED_SUBRESOURCE msr;
    pContext->Map(m_pTexture2D.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    rsize_t size = static_cast<rsize_t>(m_desc.width) * static_cast<rsize_t>(m_desc.height) * 4;
    memcpy_s(msr.pData, size, m_desc.pData, size);
    pContext->Unmap(m_pTexture2D.Get(), 0);

    // Texture2DからShaderResourceView作成
    D3D11_SHADER_RESOURCE_VIEW_DESC SRVdesc = {};
    SRVdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SRVdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    SRVdesc.Texture2D.MipLevels = 1;
    hr = pDevice->CreateShaderResourceView(m_pTexture2D.Get(), &SRVdesc, &m_pShaderResourceView);
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_TEX11");

    // テクスチャ サンプラ生成
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    /*
    * D3D11_FILTER_MIN_MAG_MIP_POINT  ポイントサンプリング
    * D3D11_FILTER_MIN_MAG_MIP_LINEAR 線形補間
    * D3D11_FILTER_ANISOTROPIC  異方性
    */
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = pDevice->CreateSamplerState(&sd, &m_pSamplerState);
    if (FAILED(hr)) _ASSERT_EXPR(false, L"NO_TEX11");
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11Texture::~GfxD3D11Texture()
{
}

//------------------------------------------------------------------------------
/// テクスチャを頂点シェーダーにセットする
///
/// \param[in] slot レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------

void GfxD3D11Texture::BindVS(unsigned slot) const
{
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    pContext->PSSetShaderResources(slot, 1, m_pShaderResourceView.GetAddressOf());
}

//------------------------------------------------------------------------------
/// テクスチャをピクセルシェーダーにセットする
///
/// \param[in] slot レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11Texture::BindPS(unsigned slot) const
{
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    pContext->PSSetShaderResources(slot, 1, m_pShaderResourceView.GetAddressOf());
    pContext->PSSetSamplers(slot, 1, m_pSamplerState.GetAddressOf());
}

void GfxD3D11Texture::Bind(unsigned slot) const
{
    UNREFERENCED_PARAMETER(slot);
}
