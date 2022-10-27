//==============================================================================
// Filename: IGfx_DeviceFactory.h
// Description: デバイスの作成クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __DEVICE_FACTORY_H__
#define __DEVICE_FACTORY_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_SwapChain.h>
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <Windows.h>
#include <memory>
#include <dxgi.h>

class IGfxDevice;
class IGfxRenderCommand;

// クラス定義
namespace DeviceFactory
{
    // デバイスと描画に必要な変数の初期化
    HRESULT CreateDeviceAndContext(
    int apiKind,
    std::shared_ptr<IGfxDevice>& pDevice,
    std::shared_ptr<IGfxRenderCommand>& pRenderCommand);

    HRESULT CreateSwapChain(
        int apiKind,
        // out
        std::shared_ptr<IGfxSwapChain>& pSwapChain,
        const IGfxSwapChain::Description& desc,
        IGfxDevice* pDevice,
        IGfxRenderCommand* pRenderCommand);

    // レンダーターゲットの作成
    HRESULT CreateRenderTargetView(
        int apiKind,
        std::shared_ptr<IGfxRenderTarget>& pRenderTarget,
        const IGfxRenderTarget::Description& desc,
        IGfxDevice* pDevice,
        IGfxSwapChain* pSwapChain);
}


#endif // __DEVICE_FACTORY_H__
