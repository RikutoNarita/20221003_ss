//==============================================================================
// Filename: IGfx_D3D12SwapChain_Impl.h
// Description: Direct3D 12のスワップチェーンクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12SwapChain_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderCommand_Impl.h> // キャストして使用

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12SwapChain::GfxD3D12SwapChain()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12SwapChain::~GfxD3D12SwapChain()
{
}

//------------------------------------------------------------------------------
/// スワップチェーンの生成
///
/// \param[in] desc             スワップチェーンの設定項目
/// \param[in] pDevice          デバイス
/// \param[in] pRenderCommand   デバイスコンテクスト
/// 
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D12SwapChain::Create(
/*[in]*/
const Description& desc,
/*[in]*/
IGfxDevice* pDevice,
/*[in]*/
IGfxRenderCommand* pRenderCommand)
{
    UNREFERENCED_PARAMETER(pDevice); // 未使用宣言

    HRESULT hr = S_OK;

    // ファクトリーの生成
    Microsoft::WRL::ComPtr<IDXGIFactory6> pFactory;
#ifdef _DEBUG
    if (CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&pFactory)) != S_OK)
    {
        return E_FAIL;
    }
#else
    if (CreateDXGIFactory1(IID_PPV_ARGS(&pFactory)) != S_OK)
    {
        return E_FAIL;
    }
#endif // _DEBUG

    // スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = desc.width;
    swapChainDesc.Height = desc.height;
    swapChainDesc.Format = desc.fromat;
    swapChainDesc.BufferUsage = desc.bufferUsage;
    swapChainDesc.BufferCount = desc.bufferCount;
    swapChainDesc.SwapEffect = desc.swapEffect;
    swapChainDesc.Flags = desc.flag;
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;                     // サンプルは1ピクセルづつ
    swapChainDesc.SampleDesc.Quality = 0;                   // クオリティは最低
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;           // バックバッファーは伸び縮み可能
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;  // 指定なし

    // スワップチェーンの生成
    Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;
    hr = pFactory->CreateSwapChainForHwnd(
        dynamic_cast<GfxD3D12RenderCommand*>(pRenderCommand)->GetCommadQueue(),
        desc.hWnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapchain1);
    if (FAILED(hr)) return hr;
    // SwapChain4 → SwapChain1にする
    swapchain1.As(&m_pSwapChain);

    return S_OK;
}

//------------------------------------------------------------------------------
/// フロントバッファとバックバッファの入れ替え
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12SwapChain::Present() const
{
    m_pSwapChain->Present(1, 0);
}
