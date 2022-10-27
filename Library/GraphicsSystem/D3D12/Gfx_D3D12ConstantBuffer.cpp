//==============================================================================
// Filename: Gfx_D3D12ConstantBuffer.h
// Description: Direct3D 12定数バッファクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc 定数バッファの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ConstantBuffer::GfxD3D12ConstantBuffer(Description desc)
: GfxConstantBuffer(desc)
{
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();

    // 定数バッファのヒーププロパティの設定
    D3D12_HEAP_PROPERTIES constHeapProp = {};
    constHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                       // デフォルト設定
    constHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;    // デフォルト設定
    constHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;     // デフォルト設定
    // 定数バッファのリソースの生成
    D3D12_RESOURCE_DESC ConstResourceDesc = {};
    ConstResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    ConstResourceDesc.Width = (desc.size + 0xff) & ~0xff; // 頂点情報のサイズ
    ConstResourceDesc.Height = 1;
    ConstResourceDesc.DepthOrArraySize = 1;
    ConstResourceDesc.MipLevels = 1;
    ConstResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    ConstResourceDesc.SampleDesc.Count = 1;
    ConstResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    ConstResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    auto hr = pDevice->CreateCommittedResource(
        &constHeapProp,                        // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                // 指定なし
        &ConstResourceDesc,                    // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pConstantBuffer));    // 定数バッファー
    if (FAILED(hr))  _ASSERT_EXPR(false, L"NO_CSV");

    // 定数バッファのマップ
    void* CBVdata;
    hr = m_pConstantBuffer->Map(0, nullptr, (void**)&CBVdata);
    if (SUCCEEDED(hr))
    {
        memcpy_s(CBVdata, desc.size, m_desc.pData, desc.size);
        m_pConstantBuffer->Unmap(0, nullptr);
    }

    m_desc.size = desc.size;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ConstantBuffer::~GfxD3D12ConstantBuffer()
{
}

void GfxD3D12ConstantBuffer::Write(void* pData)
{
    void* CBVdata;
    auto hr = m_pConstantBuffer->Map(0, nullptr, (void**)&CBVdata);
    if (SUCCEEDED(hr))
    {
        rsize_t size = m_desc.size;
        memcpy_s(CBVdata, size, m_desc.pData, size);
        m_pConstantBuffer->Unmap(0, nullptr);
    }
}


void GfxD3D12ConstantBuffer::BindPS(unsigned slot)
{
}
void GfxD3D12ConstantBuffer::BindVS(unsigned slot)
{
}

void GfxD3D12ConstantBuffer::Bind(unsigned slot) const
{
}
