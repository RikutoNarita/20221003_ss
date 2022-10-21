//==============================================================================
// Filename: IGfx_D3D11Device_Impl.h
// Description: Direct3D 11のデバイス処理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_DEVICE_H__
#define __D3D11_DEVICE_H__

// インクルード
#include <GraphicsSystem/Interface/IGfx_Device.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>

// クラス定義
class GfxD3D11Device : public IGfxDevice
{
    friend HRESULT DeviceFactory::CreateDeviceAndContext(
        int apiKind,
        std::shared_ptr<IGfxDevice>& pDevice,
        std::shared_ptr<IGfxRenderCommand>& pRenderCommand);

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11Device()
        : m_pDevice(nullptr)
    {
    }

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11Device() final
    {
    }

    //------------------------------------------------------------------------------
    /// デバイスの取得
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
    /// m_pDevice   Direct3D 11のデバイス
    /// </summary> 
};
#endif // __D3D11_DEVICE_H__
