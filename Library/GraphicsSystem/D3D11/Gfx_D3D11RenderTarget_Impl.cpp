//==============================================================================
// Filename: IGfx_D3D11RenderTarget_Impl.h
// Description: レンダーターゲットのインターフェースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11RenderTarget_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11SwapChain_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11RenderTarget::GfxD3D11RenderTarget()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11RenderTarget::~GfxD3D11RenderTarget()
{
}

//------------------------------------------------------------------------------
/// レンダーターゲットの生成
///
/// \param[in] desc         設定項目
/// \param[in] pDevice      デバイス
/// \param[in] pSwapChain   スワップチェーン
/// 
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D11RenderTarget::Create(
    const Description& desc,
    IGfxDevice* pDevice,
    IGfxSwapChain* pSwapCahin)
{
    HRESULT hr = S_OK;

    // スワップチェインからバックバッファリソース取得
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
    hr = dynamic_cast<GfxD3D11SwapChain*>(pSwapCahin)->GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (FAILED(hr))
    {
        return hr;
    }

    // バックバッファリソース用のRTVを作成
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = desc.fromat;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    hr = dynamic_cast<GfxD3D11Device*>(pDevice)->GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_pRenderTargetView);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}