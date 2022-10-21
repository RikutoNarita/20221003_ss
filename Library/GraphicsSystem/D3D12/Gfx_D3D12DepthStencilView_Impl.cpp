//==============================================================================
// Filename: Gfx_D3D12DepthStencilView_Impl.h
// Description: Direct3D 12のデプスステンシルクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12DepthStencilView_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Device_Impl.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12DepthStencil::GfxD3D12DepthStencil()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12DepthStencil::~GfxD3D12DepthStencil()
{
}

//------------------------------------------------------------------------------
/// デプスステンシルビューの生成
///
/// \param[in] desc     設定項目 
/// \param[in] pDevice  デバイス
/// 
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
const HRESULT GfxD3D12DepthStencil::Create(
    const Description& desc, IGfxDevice* pDeviceImpl)
{
	HRESULT hr =S_OK;

    ID3D12Device* pDevice = dynamic_cast<GfxD3D12Device*>(pDeviceImpl)->GetDevice();

    // リソースの作成
    D3D12_RESOURCE_DESC depthResourceDesc = {};
    depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;   // 2Dテクスチャ
    depthResourceDesc.Width = desc.width;                               // レンダーターゲットと同じ幅
    depthResourceDesc.Height = desc.height;                             // レンダーターゲットと同じ高さ
    depthResourceDesc.DepthOrArraySize = 1;                             // リソースの配列のサイズ
    depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;                   // 深度値書き込み用フォーマット
    depthResourceDesc.SampleDesc.Count = 1;                             // サンプルは1ピクセルあたり1つ
    depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;  // デプスステンシルとして使用
    // ヒーププロパティの設定
    D3D12_HEAP_PROPERTIES depthHeapProp = {};
    depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;                       // デフォルト設定
    depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;    // デフォルト設定
    depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;     // デフォルト設定
    // クリアバリューの設定
    D3D12_CLEAR_VALUE depthClearValue = {};
    depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;     // 深度値書き込み用フォーマット
    depthClearValue.DepthStencil.Depth = 1.0f;
    // リソースの作成
    hr = pDevice->CreateCommittedResource(
        &depthHeapProp,                         // ヒーププロパティ
        D3D12_HEAP_FLAG_NONE,
        &depthResourceDesc,                     // リソースの設定
        D3D12_RESOURCE_STATE_DEPTH_WRITE,       // 深度値書き込み用
        &depthClearValue,                       // クリアバリュー
        IID_PPV_ARGS(&m_pDepthBuffer));         // リソースのアドレス
    if (FAILED(hr)) return hr;

    // ディスクリプタヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC depthHeapDesc = {};
    depthHeapDesc.NumDescriptors = 1;                       // 深度ビューは１つ
    depthHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;    // デプスステンシルビューとして使う
    hr = pDevice->CreateDescriptorHeap(&depthHeapDesc, IID_PPV_ARGS(&m_pDSVDescriptorHeap));
    if (FAILED(hr)) return hr;

    // 深度バッファビューの作成
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;                 // 深度値書き込み用フォーマット
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;  // 2Dテクスチャ
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;                    // 指定なし
    pDevice->CreateDepthStencilView(
        m_pDepthBuffer.Get(),
        &dsvDesc,
        m_pDSVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	return S_OK;
}
