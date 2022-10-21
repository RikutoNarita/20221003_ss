//==============================================================================
// Filename: Gfx_D3D11RenderCommand_Impl.h
// Description: Direct3D 11の描画命令クラスクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_RENDER_COMMAND_H__
#define __D3D11_RENDER_COMMAND_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_RenderCommand.h>
#include <wrl\client.h>
#include <d3d11.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>

// クラス定義
class GfxD3D11RenderCommand : public IGfxRenderCommand
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
    GfxD3D11RenderCommand();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11RenderCommand();

    //------------------------------------------------------------------------------
    /// バックバッファのクリア
    ///
    /// \param[in] pRenderTagetView レンダーターゲット
    /// \param[in] clearColor       クリアする色
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearRenderTargetView(
        /*[in]*/
        IGfxRenderTarget* pRenderTargetView,
        /*[in]*/
        const float clearColor[4]) const final;

    //------------------------------------------------------------------------------
    /// Zバッファのクリア
    ///
    /// \param[in] pDepthStencilView    デプスステンシルビュー
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearDepthStencilView(
        /*[in]*/
        IGfxDepthStencil* DepthStencilView) const final;

    //------------------------------------------------------------------------------
    /// レンダーターゲットビューとデプスステンシルビューの指定
    /// DX12の場合　リソースバリアの設定もここで行っている
    /// 
    /// \param[in] pRenderTagetView     レンダーターゲットビュー
    /// \param[in] pDepthStencilView    デプスステンシルビュー
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void OMSetRenderTargets(
        /*[in]*/
        IGfxRenderTarget* pRenderTargetView,
        /*[in]*/
        IGfxDepthStencil* pDepthStencilView) final;

    //------------------------------------------------------------------------------
    /// 描画終了命令（バクバッファとフロントバッファの入れ替え）
    /// DX12の場合　リソースバリアの設定もここで行っている
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw() final;

    //------------------------------------------------------------------------------
    /// デバイスコンテキストの取得
    ///
    /// \return デバイスコンテキスト
    //------------------------------------------------------------------------------
    ID3D11DeviceContext* GetDeviceContext() const
    {
        return m_pDeviceContext.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDeviceContext   デバイスコンテキスト
    /// </summary> 
};
#endif // __D3D11_RENDER_COMMAND_H__
