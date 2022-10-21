//==============================================================================
// Filename: IGfx_D3D12RenderTarget_Impl.h
// Description: Direct3D 12のレンダーターゲットクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderTarget_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12SwapChain_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Device_Impl.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RenderTarget::GfxD3D12RenderTarget()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RenderTarget::~GfxD3D12RenderTarget()
{
}

//------------------------------------------------------------------------------
/// レンダーターゲットの生成
///
/// \param[in] desc         設定項目
/// \param[in] pDevice      デバイス
/// \param[in] pSwapChain   スワップチェーン
/// 
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D12RenderTarget::Create(
    const Description& desc,
    IGfxDevice* pDevice,
    IGfxSwapChain* pSwapChain)
{
    HRESULT hr = S_OK;
    
    // 'レンダーターゲットの'ディスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;         // レンダーターゲットのせっていなのでRTV
    heapDesc.NodeMask = 0;                                  // アダプターを一つしか使わないときは0
    heapDesc.NumDescriptors = desc.bufferCount;             // フロントバッファとバックバッファで2つ
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;       // 指定なし
    // ディスクリプタヒープの作成
    hr = dynamic_cast<GfxD3D12Device*>(pDevice)->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pDescriptorHeap));
    if (FAILED(hr))
    {
        return hr;
    }
    // スワップチェーンのメモリと紐づける
    m_pBufferList.resize(heapDesc.NumDescriptors);
    for (int idx = 0; idx < (int)heapDesc.NumDescriptors; idx++)
    {
        // 紐づけ
        hr = dynamic_cast<GfxD3D12SwapChain*>(pSwapChain)->GetSwapChain()->GetBuffer(idx, IID_PPV_ARGS(&m_pBufferList[idx]));
        if (FAILED(hr))
        {
            return hr;
        }

        D3D12_CPU_DESCRIPTOR_HANDLE hadle;
        hadle = m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
        hadle.ptr += idx * 
            static_cast<unsigned long long>(dynamic_cast<GfxD3D12Device*>(pDevice)->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        // レンダーターゲットビューの作成
        dynamic_cast<GfxD3D12Device*>(pDevice)->GetDevice()->CreateRenderTargetView(m_pBufferList[idx].Get(), nullptr, hadle);
    }

    return S_OK;
}