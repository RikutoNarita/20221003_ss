//==============================================================================
// Filename: Gfx_D3D12DepthStencilView_Impl.h
// Description: Direct3D 12のデプスステンシルクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_DEPTH_STENCIL_VIEW_H__
#define __D3D12_DEPTH_STENCIL_VIEW_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_DepthStencilView.h>
#include <d3d12.h>
#include <wrl\client.h>

// クラス定義
class GfxD3D12DepthStencil : public IGfxDepthStencil
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12DepthStencil();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12DepthStencil();

    
    //------------------------------------------------------------------------------
    /// デプスステンシルビューの生成
    ///
    /// \param[in] desc     設定項目 
    /// \param[in] pDevice  デバイス
    /// 
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    const HRESULT Create(
        /*[in]*/
        const Description& desc,
        /*[in]*/
        IGfxDevice* pDevice) final;

    
    //------------------------------------------------------------------------------
    /// デプスステンシルビューのデスクリプタヒープの取得
    ///
    /// \return デプスステンシルビューのデスクリプタヒープ
    //------------------------------------------------------------------------------
    ID3D12DescriptorHeap* GetDescHeap() const
    {
        return m_pDSVDescriptorHeap.Get();
    }

    //------------------------------------------------------------------------------
    /// 深度バッファの取得
    ///
    /// \return 深度バッファ
    //------------------------------------------------------------------------------
    ID3D12Resource* GetDepthBuffer() const
    {
        return m_pDepthBuffer.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    m_pDSVDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12Resource>          m_pDepthBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDSVDescriptorHeap    深度バッファのディスクリプタヒープ
    /// m_pDepthBuffer          深度バッファ
    /// </summary>
};
#endif // __D3D12_DEPTH_STENCIL_VIEW_H__
