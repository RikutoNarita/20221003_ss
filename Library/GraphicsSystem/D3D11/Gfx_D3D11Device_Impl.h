//==============================================================================
// Filename: IGfx_D3D11Device_Impl.h
// Description: Direct3D 11�̃f�o�C�X�����N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_DEVICE_H__
#define __D3D11_DEVICE_H__

// �C���N���[�h
#include <GraphicsSystem/Interface/IGfx_Device.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>

// �N���X��`
class GfxD3D11Device : public IGfxDevice
{
    friend HRESULT DeviceFactory::CreateDeviceAndContext(
        int apiKind,
        std::shared_ptr<IGfxDevice>& pDevice,
        std::shared_ptr<IGfxRenderCommand>& pRenderCommand);

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11Device()
        : m_pDevice(nullptr)
    {
    }

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11Device() final
    {
    }

    //------------------------------------------------------------------------------
    /// �f�o�C�X�̎擾
    ///
    /// \return void
    //------------------------------------------------------------------------------
    inline ID3D11Device* GetDevice() const
    {
        return m_pDevice.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice   Direct3D 11�̃f�o�C�X
    /// </summary> 
};
#endif // __D3D11_DEVICE_H__
