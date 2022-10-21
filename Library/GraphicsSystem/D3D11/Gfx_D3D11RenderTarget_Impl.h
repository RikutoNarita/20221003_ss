//==============================================================================
// Filename: IGfx_D3D11RenderTarget_Impl.h
// Description: Direct3D 11のレンダーターゲットクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_RENDER_TARGET_H__
#define __D3D11_RENDER_TARGET_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

// クラス定義
class GfxD3D11RenderTarget : public IGfxRenderTarget
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11RenderTarget();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11RenderTarget() override;

    //------------------------------------------------------------------------------
    /// レンダーターゲットの生成
    ///
    /// \param[in] desc         設定項目
    /// \param[in] pDevice      デバイス
    /// \param[in] pSwapChain   スワップチェーン
    /// 
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    const Description& desc,
    /*[in]*/
    IGfxDevice* pDevice,
    /*[in]*/
    IGfxSwapChain* pSwapChain) final;
    
    //------------------------------------------------------------------------------
    /// レンダーターゲットビューの取得
    ///
    /// \return レンダーターゲットビュー
    //------------------------------------------------------------------------------
    ID3D11RenderTargetView* GetRenderTargetView()
    {
        return m_pRenderTargetView.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pRenderTargetView   レンダーターゲットビュー
    /// </summary>

};

#endif // __D3D11_RENDER_TARGET_H__
