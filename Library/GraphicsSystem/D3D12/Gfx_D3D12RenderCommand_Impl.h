//==============================================================================
// Filename: Gfx_D3D12RenderCommand_Impl.h
// Description: Direct3D 12の描画命令クラスクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_RENDER_COMMAND_H__
#define __D3D12_RENDER_COMMAND_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_RenderCommand.h>    // 継承
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>     // フレンド関数用
#include <wrl\client.h> //COMポインタ
#include <d3d12.h>      


// クラス定義
class GfxD3D12RenderCommand : public IGfxRenderCommand
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
    GfxD3D12RenderCommand();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12RenderCommand();

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
    /// コマンドリストの取得
    ///
    /// \return コマンドリスト
    //------------------------------------------------------------------------------
    ID3D12GraphicsCommandList* GetCommadList() const
    {
        return m_pCommandList.Get();
    }
    //------------------------------------------------------------------------------
    /// コマンドアロケーターの取得
    ///
    /// \return コマンドアロケーター
    //------------------------------------------------------------------------------
    ID3D12CommandAllocator* GetCommadAllocator() const
    {
        return m_pCommandAllocator.Get();
    }

    //------------------------------------------------------------------------------
    /// コマンドキューの取得
    ///
    /// \return コマンドキュー
    //------------------------------------------------------------------------------
    ID3D12CommandQueue* GetCommadQueue() const
    {
        return m_pCommandQueue.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>   m_pCommandList;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator>      m_pCommandAllocator;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue>          m_pCommandQueue;
    Microsoft::WRL::ComPtr<ID3D12Fence>                 m_pFence;
    D3D12_RESOURCE_BARRIER                              m_barrierDesc;
    UINT64                                              m_fenceValue;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pCommandList      コマンドリスト
    /// m_pCommandAllocator アロケーター
    /// m_pCommandQueue     コマンドキュー
    /// m_pCommandList      コマンドリスト
    /// </summary> 
};
#endif // __D3D12_RENDER_COMMAND_H__
