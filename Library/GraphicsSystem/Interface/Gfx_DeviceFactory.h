//==============================================================================
// Filename: IGfx_DeviceFactory.h
// Description: �f�o�C�X�̍쐬�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __DEVICE_FACTORY_H__
#define __DEVICE_FACTORY_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_SwapChain.h>
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <Windows.h>
#include <memory>
#include <dxgi.h>

class IGfxDevice;
class IGfxRenderCommand;

// �N���X��`
namespace DeviceFactory
{
    // �f�o�C�X�ƕ`��ɕK�v�ȕϐ��̏�����
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

    // �����_�[�^�[�Q�b�g�̍쐬
    HRESULT CreateRenderTargetView(
        int apiKind,
        std::shared_ptr<IGfxRenderTarget>& pRenderTarget,
        const IGfxRenderTarget::Description& desc,
        IGfxDevice* pDevice,
        IGfxSwapChain* pSwapChain);
}


#endif // __DEVICE_FACTORY_H__
