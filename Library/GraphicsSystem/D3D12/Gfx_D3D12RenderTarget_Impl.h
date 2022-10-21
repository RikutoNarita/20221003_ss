//==============================================================================
// Filename: IGfx_D3D12RenderTarget_Impl.h
// Description: Direct3D 12のレンダーターゲットクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_RENDER_TARGET_H__
#define __D3D12_RENDER_TARGET_H__

// インクルード
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>

// クラス定義
class GfxD3D12RenderTarget : public IGfxRenderTarget
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12RenderTarget();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12RenderTarget() override;

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
    /// 指定したレンダーターゲットのバッファの取得
    ///
    /// \param[in] index   インデックス
    /// 
    /// \return レンダーターゲットのバッファ
    //------------------------------------------------------------------------------
    ID3D12Resource* GetResorces(int index)
    {
        return m_pBufferList[index].Get();
    }

    //------------------------------------------------------------------------------
    /// レンダーターゲットビューディスクリプタヒープの取得
    ///
    /// \return レンダーターゲットビューディスクリプタヒープ
    //------------------------------------------------------------------------------
    ID3D12DescriptorHeap* GetDescriptorHeap()
    {
        return m_pDescriptorHeap.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pDescriptorHeap;
    std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> m_pBufferList;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDescriptorHeap   レンダーターゲットのデスクリプターヒープ
    /// m_pBufferList       レンダーターゲットのバッファ
    /// </summary>

};
#endif // __D3D12_RENDER_TARGET_H__
