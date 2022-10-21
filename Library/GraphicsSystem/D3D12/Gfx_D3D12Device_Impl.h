//==============================================================================
// Filename: IGfx_D3D12Device_Impl.h
// Description: Direct3D 12のデバイス処理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_DEVICE_H__
#define __D3D12_DEVICE_H__

// インクルード
#include <GraphicsSystem/Interface/IGfx_Device.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>

// クラス定義
class GfxD3D12Device : public IGfxDevice
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
    GfxD3D12Device()
        : m_pDevice(nullptr)
    {
    }

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12Device() final
    {
    }

    //------------------------------------------------------------------------------
    /// デバイスの取得
    ///
    /// \return void
    //------------------------------------------------------------------------------
    inline ID3D12Device* GetDevice() const
    {
        return m_pDevice.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Device> m_pDevice;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice   Direct3D 12のデバイス
    /// </summary> 
};
#endif // __D3D12_DEVICE_H__
