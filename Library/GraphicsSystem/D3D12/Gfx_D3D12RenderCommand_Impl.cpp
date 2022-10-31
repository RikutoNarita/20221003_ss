//==============================================================================
// Filename: Gfx_D3D12RenderCommand_Impl.h
// Description: Direct3D 12の描画命令クラスクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderCommand_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderTarget_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ViewPort_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ScissorRect_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12DepthStencilView_Impl.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RenderCommand::GfxD3D12RenderCommand()
    : m_fenceValue(0)
{
    m_barrierDesc = {};
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RenderCommand::~GfxD3D12RenderCommand()
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
void GfxD3D12RenderCommand::ClearRenderTargetView(
    IGfxRenderTarget* pRenderTargetView,
    const float clearColor[4]) const
{
    auto renderTarget = dynamic_cast<GfxD3D12RenderTarget*>(pRenderTargetView);

    //現在のバックバッファーのインデックス
    auto bbIdx = DX->GetSwapChain<IDXGISwapChain4>()->GetCurrentBackBufferIndex();
    auto rtvHeap = renderTarget->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
    rtvHeap.ptr += bbIdx * static_cast<unsigned long long>(
        DX->GetDevice<ID3D12Device>()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    m_pCommandList->ClearRenderTargetView(rtvHeap, clearColor, 0, nullptr);
}

//------------------------------------------------------------------------------
/// Zバッファのクリア
///
/// \param[in] pDepthStencilView    デプスステンシルビュー
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12RenderCommand::ClearDepthStencilView(
    IGfxDepthStencil* pDepthStencilView) const
{
    auto depthstencil = dynamic_cast<GfxD3D12DepthStencil*>(pDepthStencilView);
    auto dsvHeap = depthstencil->GetDescHeap()->GetCPUDescriptorHandleForHeapStart();
    m_pCommandList->ClearDepthStencilView(dsvHeap, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
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
void GfxD3D12RenderCommand::OMSetRenderTargets(
    IGfxRenderTarget* pRenderTargetView, IGfxDepthStencil* pDepthStencilView) 
{
    auto renderTarget = dynamic_cast<GfxD3D12RenderTarget*>(pRenderTargetView);

    //現在のバックバッファーのインデックス
    auto bbIdx = DX->GetSwapChain<IDXGISwapChain4>()->GetCurrentBackBufferIndex();

    // リソースバリアの設定
    m_barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;  // 遷移
    m_barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;       // 指定なし
    m_barrierDesc.Transition.pResource = renderTarget->GetResorces(bbIdx);// バックバッファーリソース
    m_barrierDesc.Transition.Subresource = 0;                     // バックバッファは一つなので要素0を指定
    // Present状態からRenderTarget状態に遷移
    m_barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    m_barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    // リソースバリア指定実行
    m_pCommandList->ResourceBarrier(1, &m_barrierDesc); // 第1引数は設定バリア数

    auto rtvHeap = renderTarget->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
    rtvHeap.ptr += bbIdx * static_cast<unsigned long long>(
        DX->GetDevice<ID3D12Device>()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    auto depthstencil = dynamic_cast<GfxD3D12DepthStencil*>(pDepthStencilView);
    auto dsvHeap = depthstencil->GetDescHeap()->GetCPUDescriptorHandleForHeapStart();
    // レンダーターゲットをバックバッファにセット
    m_pCommandList->OMSetRenderTargets(1, &rtvHeap, false, &dsvHeap);
}

//------------------------------------------------------------------------------
/// 描画終了命令（バクバッファとフロントバッファの入れ替え）
/// DX12の場合　リソースバリアの設定もここで行っている
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12RenderCommand::EndDraw()
{
    // RenderTarget状態からPresent状態に遷移
    m_barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    m_barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    // リソースバリア指定実行
    m_pCommandList->ResourceBarrier(1, &m_barrierDesc); // 第1引数は設定バリア数

    // クローズ
    m_pCommandList->Close();

    // 命令の実行
    ID3D12CommandList* commandLists[] = { m_pCommandList.Get() };
    m_pCommandQueue->ExecuteCommandLists(1, commandLists);

    // スワップ
    DX->GetSwapChain<IDXGISwapChain4>()->Present(1, 0);

    // 命令がすべて実行されたか
    m_pCommandQueue->Signal(m_pFence.Get(), ++m_fenceValue);
    if (m_pFence->GetCompletedValue() != m_fenceValue)
    {
        // イベントハンドルの取得
        auto eventHandle = CreateEvent(nullptr, false, false, nullptr);
        m_pFence->SetEventOnCompletion(m_fenceValue, eventHandle);
        if (eventHandle)
        {
            // イベントが発生するまで待ち続ける
            WaitForSingleObject(eventHandle, INFINITE);
            // イベントハンドルを閉じる
            CloseHandle(eventHandle);
        }
    }

    // リセット
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);
}
