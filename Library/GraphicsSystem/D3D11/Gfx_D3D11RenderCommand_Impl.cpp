//==============================================================================
// Filename: Gfx_D3D11RenderCommand_Impl.h
// Description: Direct3D 11の描画命令クラスクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11RenderCommand_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11RenderTarget_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11ViewPort_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11ScissorRect_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11DepthStencilView_Impl.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11RenderCommand::GfxD3D11RenderCommand()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11RenderCommand::~GfxD3D11RenderCommand()
{
}

//------------------------------------------------------------------------------
/// バックバッファのクリア
///
/// \param[in] pRenderTagetView レンダーターゲット
/// \param[in] clearColor       クリアする色
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11RenderCommand::ClearRenderTargetView(
    IGfxRenderTarget* pRenderTargetView, const float clearColor[4]) const
{
    m_pDeviceContext->ClearRenderTargetView(
        dynamic_cast<GfxD3D11RenderTarget*>(pRenderTargetView)->GetRenderTargetView(), clearColor);
}

//------------------------------------------------------------------------------
/// Zバッファのクリア
///
/// \param[in] pDepthStencilView    デプスステンシルビュー
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11RenderCommand::ClearDepthStencilView(
    IGfxDepthStencil* DepthStencilView) const
{
    
    m_pDeviceContext->ClearDepthStencilView(
        dynamic_cast<GfxD3D11DepthStencil*>(DepthStencilView)->GetDepthStencilView(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//------------------------------------------------------------------------------
/// レンダーターゲットビューとデプスステンシルビューの指定
/// DX12の場合　リソースバリアの設定もここで行っている
/// 
/// \param[in] pRenderTagetView     レンダーターゲットビュー
/// \param[in] pDepthStencilView    デプスステンシルビュー
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11RenderCommand::OMSetRenderTargets(
    IGfxRenderTarget* pRenderTargetView, IGfxDepthStencil* pDepthStencilView)
{
    ID3D11RenderTargetView* rtvs[] = 
    {
        dynamic_cast<GfxD3D11RenderTarget*>(pRenderTargetView)->GetRenderTargetView(),
    };

    m_pDeviceContext->OMSetRenderTargets(1,
        rtvs,
        dynamic_cast<GfxD3D11DepthStencil*>(pDepthStencilView)->GetDepthStencilView());
}

//------------------------------------------------------------------------------
/// 描画終了命令（バクバッファとフロントバッファの入れ替え）
/// DX12の場合　リソースバリアの設定もここで行っている
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11RenderCommand::EndDraw()
{
    DX->GetSwapChain<IDXGISwapChain>()->Present(1, 0);
}
