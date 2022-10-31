//==============================================================================
// Filename: Gfx_GraphicsManager.h
// Description: OpenGLの描画管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __OPEN_GL_MANAGER_H__
#define __OPEN_GL_MANAGER_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_Graphics.h>

#include <memory>

// マクロ定義
#define GL    (GfxOpenGL::GetInstance()) // クラスのインスタンスを返す

// クラス定義
class GfxOpenGL : public IGfxGraphics
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxOpenGL();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxOpenGL();

    //------------------------------------------------------------------------------
    /// グラフィックスAPIの初期化
    ///
    /// \param[in] width    ウィンドウの幅
    /// \param[in] height   ウィンドウの高さ
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

    static GfxOpenGL* GetInstance()
    {
        return dynamic_cast<GfxOpenGL*>(m_pGraphics.get());
    }

    //------------------------------------------------------------------------------
private:
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    /// <summary>
    /// </summary> 
    
public:
    //template <typename T>
    //T* GetDevice()
    //{
    //    return *T;
    //}
    //template <>
    //ID3D12Device* GetDevice<ID3D12Device>()
    //{
    //    return dynamic_cast<GfxD3D12Device*>(m_pDevice.get())->GetDevice();
    //}
    //
    //template <>
    //ID3D11Device* GetDevice<ID3D11Device>()
    //{
    //    return dynamic_cast<GfxD3D11Device*>(m_pDevice.get())->GetDevice();
    //}
    //
    //template <typename T>
    //T* GetRenderCommand()
    //{
    //    return *T;
    //}
    //template <>
    //ID3D11DeviceContext* GetRenderCommand<ID3D11DeviceContext>()
    //{
    //    return dynamic_cast<GfxD3D11RenderCommand*>(m_pRenderCommand.get())->GetDeviceContext();
    //}
    //template <>
    //ID3D12GraphicsCommandList* GetRenderCommand<ID3D12GraphicsCommandList>()
    //{
    //    return dynamic_cast<GfxD3D12RenderCommand*>(m_pRenderCommand.get())->GetCommadList();
    //}
    //
    //template <typename T>
    //T* GetSwapChain()
    //{
    //    return *T;
    //}
    //template <>
    //IDXGISwapChain* GetSwapChain<IDXGISwapChain>()
    //{
    //    return dynamic_cast<GfxD3D11SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    //}
    //template <>
    //IDXGISwapChain4* GetSwapChain<IDXGISwapChain4>()
    //{
    //    return dynamic_cast<GfxD3D12SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    //}

};
#endif // __D3D_MANAGER_H__
