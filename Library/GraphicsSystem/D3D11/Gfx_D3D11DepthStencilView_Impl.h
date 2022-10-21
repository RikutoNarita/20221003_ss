//==============================================================================
// Filename: Gfx_D3D11DepthStencilView_Impl.h
// Description: Direct3D 11のデプスステンシルクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_DEPTH_STENCIL_VIEW_H__
#define __D3D11_DEPTH_STENCIL_VIEW_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_DepthStencilView.h>
#include <d3d11.h>
#include <wrl\client.h>

// クラス定義
class GfxD3D11DepthStencil : public IGfxDepthStencil
{
public:
    

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11DepthStencil();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11DepthStencil();
    
    //-----------------------------------------------------------------------------
    /// デプスステンシルビューの生成
    ///
    /// \param[in] desc     設定項目 
    /// \param[in] pDevice  デバイス
    /// 
    /// \return 生成できた場合 S_OK
    //-----------------------------------------------------------------------------
    const HRESULT Create(
        /*[in]*/
        const Description& desc,
        /*[in]*/
        IGfxDevice* pDevice) final;

    //------------------------------------------------------------------------------
    /// デプスステンシルビューの取得
    ///
    /// \return デプスステンシルビュー
    //------------------------------------------------------------------------------
    ID3D11DepthStencilView* GetDepthStencilView() const
    {
        return m_pDepthStencilView.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    m_pDepthStencilView;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDSVDescriptorHeap    深度バッファのディスクリプタヒープ
    /// m_pDepthBuffer          深度バッファ
    /// </summary>
};
#endif // __D3D11_DEPTH_STENCIL_VIEW_H__
