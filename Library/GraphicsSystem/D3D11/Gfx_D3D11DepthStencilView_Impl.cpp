//==============================================================================
// Filename: Gfx_D3D11DepthStencilView_Impl.h
// Description: Direct3D 11のデプスステンシルクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11DepthStencilView_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11DepthStencil::GfxD3D11DepthStencil()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11DepthStencil::~GfxD3D11DepthStencil()
{
}

//-----------------------------------------------------------------------------
/// デプスステンシルビューの生成
///
/// \param[in] desc     設定項目 
/// \param[in] pDevice  デバイス
/// 
/// \return 生成できた場合 S_OK
//-----------------------------------------------------------------------------
const HRESULT GfxD3D11DepthStencil::Create(
    const Description& desc, IGfxDevice* pDeviceImpl)
{
	HRESULT hr =S_OK;

    ID3D11Device* pDevice = dynamic_cast<GfxD3D11Device*>(pDeviceImpl)->GetDevice();

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture11;
    // Zバッファ用テクスチャ生成
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = desc.width;
    td.Height = desc.height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D32_FLOAT;//DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    hr = pDevice->CreateTexture2D(&td, nullptr, &pTexture11);
    if (FAILED(hr)) { return hr; }
    // Zバッファターゲットビュー生成
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    ZeroMemory(&dsvd, sizeof(dsvd));
    dsvd.Format = DXGI_FORMAT_D32_FLOAT;//DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    hr = pDevice->CreateDepthStencilView(pTexture11.Get(), &dsvd, &m_pDepthStencilView);
    if (FAILED(hr)) { return hr; }

	return S_OK;
}
