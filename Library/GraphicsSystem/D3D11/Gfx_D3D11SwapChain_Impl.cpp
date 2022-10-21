//==============================================================================
// Filename: IGfx_D3D11SwapChain_Impl.h
// Description: Direct3D 11のスワップチェーンクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11SwapChain_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>
//#include <dxgi.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11SwapChain::GfxD3D11SwapChain()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11SwapChain::~GfxD3D11SwapChain()
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
HRESULT GfxD3D11SwapChain::Create(
    const Description& desc,
    IGfxDevice* pDevice,
    IGfxRenderCommand* pRenderCommand)
{
    UNREFERENCED_PARAMETER(pRenderCommand); // 未使用宣言

    HRESULT hr = S_OK;

    // ファクトリーを作成
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        return hr;
    }

    // スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
    DXGI_SWAP_CHAIN_DESC scDesc = {};                       // スワップチェーンの設定データ
    scDesc.BufferDesc.Width = desc.width;                   // 画面の幅
    scDesc.BufferDesc.Height = desc.height;                 // 画面の高さ
    scDesc.BufferDesc.Format = desc.fromat;                 // バッファの形式
    scDesc.BufferUsage = desc.bufferUsage;                  // バッファの使用方法
    scDesc.BufferCount = desc.bufferCount;                  // バッファの数
    scDesc.OutputWindow = desc.hWnd;                        // ウィンドウハンドル
    scDesc.SwapEffect = desc.swapEffect;
    scDesc.Flags = desc.flag;
    scDesc.Windowed = TRUE;                                 // ウィンドウモード
    scDesc.SampleDesc.Count = 1;                            // MSAAは使用しない
    scDesc.SampleDesc.Quality = 0;                          // MSAAは使用しない
    scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scDesc.BufferDesc.RefreshRate.Numerator = 0;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    // スワップチェインの作成
    hr = factory->CreateSwapChain(dynamic_cast<GfxD3D11Device*>(pDevice)->GetDevice(), &scDesc, &m_pSwapChain);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

//------------------------------------------------------------------------------
/// フロントバッファとバックバッファの入れ替え
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11SwapChain::Present() const
{
    m_pSwapChain->Present(1, 0);
}
