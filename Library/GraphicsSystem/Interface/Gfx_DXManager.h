//==============================================================================
// Filename: Gfx_GraphicsManager.h
// Description: Direct3D 11, Direct3D 12の抽象化レイヤー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __DX_MANAGER_H__
#define __DX_MANAGER_H__

// インクルード
#include <Win_Main.h>

#include <GraphicsSystem\Interface\IGfx_Graphics.h>
#include <GraphicsSystem\Interface\IGfx_Device.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Device_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11RenderCommand_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderCommand_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11SwapChain_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12SwapChain_Impl.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11RenderTarget_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderTarget_Impl.h>


#include <memory>

// マクロ定義
#define DX    (GfxDXManager::GetInstance()) // クラスのインスタンスを返す

// 前方宣言
class IGfxSwapChain;        // スワップチェーン
class IGfxRenderCommand;    // 描画命令
class IGfxRenderTarget;     // レンダーターゲットビュー
class IGfxDepthStencil;     // デプスステンシルビュー
class IGfxViewPort;         // ビューポート
class IGfxScissorRect;      // シザー矩形

// クラス定義
class GfxDXManager : public IGfxGraphics
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxDXManager();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxDXManager();

    //------------------------------------------------------------------------------
    /// グラフィックスAPIの初期化
    ///
    /// \param[in] hWnd     ウィンドウハンドル
    /// \param[in] width    ウィンドウの幅
    ///
    /// \return 初期化処理の成否
    //------------------------------------------------------------------------------
    void Init(int width, int height) override;

    //------------------------------------------------------------------------------
    /// グラフィックスAPIの終了処理
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Uninit() override;

    //------------------------------------------------------------------------------
    /// 描画の開始(バックバッファ＆Ｚバッファのクリア)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BeginDraw() override;

    //------------------------------------------------------------------------------
    /// 描画の修了(バックバッファとフロントバッファの入れ替え)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw() override;

    static GfxDXManager* GetInstance()
    {
        return dynamic_cast<GfxDXManager*>(m_pGraphics.get());
    }

    //------------------------------------------------------------------------------
private:
    //------------------------------------------------------------------------------
    std::shared_ptr<IGfxDevice>         m_pDevice;
    std::shared_ptr<IGfxRenderCommand>  m_pRenderCommand;
    std::shared_ptr<IGfxSwapChain>      m_pSwapChain;
    std::shared_ptr<IGfxRenderTarget>   m_pRenderTarget;
    std::shared_ptr<IGfxDepthStencil>   m_DepthStencil;
    std::shared_ptr<IGfxViewPort>       m_viewPort;
    std::shared_ptr<IGfxScissorRect>    m_scissorRect;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pInstance         クラスのインスタンス
    /// m_pDevice           デバイスインターフェース
    /// m_pRenderCommand    描画インターフェース
    /// m_pSwapChain        スワップチェーンのインターフェース
    /// m_pRenderTarget     レンダーターゲットのインターフェース
    /// m_DepthStencil      デプスステンシルのインターフェース
    /// m_viewPort          ビューポートのインターフェース
    /// m_scissorRect       シザー矩形のインターフェース
    /// </summary> 
    
public:
    template <typename T>
    T* GetDevice()
    {
        return *T;
    }
    template <>
    ID3D12Device* GetDevice<ID3D12Device>()
    {
        return dynamic_cast<GfxD3D12Device*>(m_pDevice.get())->GetDevice();
    }
    
    template <>
    ID3D11Device* GetDevice<ID3D11Device>()
    {
        return dynamic_cast<GfxD3D11Device*>(m_pDevice.get())->GetDevice();
    }

    template <typename T>
    T* GetRenderCommand()
    {
        return *T;
    }
    template <>
    ID3D11DeviceContext* GetRenderCommand<ID3D11DeviceContext>()
    {
        return dynamic_cast<GfxD3D11RenderCommand*>(m_pRenderCommand.get())->GetDeviceContext();
    }
    template <>
    ID3D12GraphicsCommandList* GetRenderCommand<ID3D12GraphicsCommandList>()
    {
        return dynamic_cast<GfxD3D12RenderCommand*>(m_pRenderCommand.get())->GetCommadList();
    }

    template <typename T>
    T* GetSwapChain()
    {
        return *T;
    }
    template <>
    IDXGISwapChain* GetSwapChain<IDXGISwapChain>()
    {
        return dynamic_cast<GfxD3D11SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    }
    template <>
    IDXGISwapChain4* GetSwapChain<IDXGISwapChain4>()
    {
        return dynamic_cast<GfxD3D12SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    }

};
#endif // __D3D_MANAGER_H__
