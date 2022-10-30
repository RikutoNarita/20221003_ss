//==============================================================================
// Filename: Gfx_D3D12MeshBuffer.h
// Description: Direct3D 12メッシュバッファー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12MeshBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>

#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>

//-----------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] shader
/// 
/// \return void
//-----------------------------------------------------------------------------
GfxD3D12MeshBuffer::GfxD3D12MeshBuffer(Description desc)
{
    m_desc = desc;
    // 頂点バッファの生成
    auto hr = CreateVertexBuffer();
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_VESRTEX_BUFFER");
    }
    if (m_desc.pIndexData)
    {
        // インデックスバッファの生成
        hr = CreateIndexBuffer();
        if (FAILED(hr))
        {
            _ASSERT_EXPR(false, L"NO_INDEX_BUFFER");
        }
    }
}

//-----------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//-----------------------------------------------------------------------------
GfxD3D12MeshBuffer::~GfxD3D12MeshBuffer()
{
}

//------------------------------------------------------------------------------
/// 頂点バッファの作成
///
/// \return 作成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D12MeshBuffer::CreateVertexBuffer()
{
    HRESULT hr = S_OK;
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();

    // ヒープの設定
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD; // CPUからアクセスできる
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    // リソースの設定
    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;   // リソースのタイプ
    resourceDesc.Width =
        static_cast<UINT64>(m_desc.vertexCount) * m_desc.vertexSize;// 頂点情報のサイズ
    resourceDesc.Height = 1;                                    // 頂点情報のサイズ(Widthに格納済み)
    resourceDesc.DepthOrArraySize = 1;                          // リソースの配列のサイズ
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;                  // フォーマット指定なし
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;              // オプションなし
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;       // データが行優先順で格納
    // 頂点バッファの生成
    hr = pDevice->CreateCommittedResource(
        &heapprop,                              // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                   // 指定なし
        &resourceDesc,                          // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,      // アップロード ヒープに必要な開始状態
        nullptr,
        IID_PPV_ARGS(&m_pVertexBuffer));        // 頂点バッファー

    void* vertMap = nullptr;
    hr = m_pVertexBuffer->Map(0, nullptr, (void**)&vertMap);
    if (SUCCEEDED(hr))
    {
        rsize_t size = static_cast<rsize_t>(m_desc.vertexCount) * m_desc.vertexSize;
        memcpy_s(vertMap, size, m_desc.pVertexData, size);
        m_pVertexBuffer->Unmap(0, nullptr);
        // 頂点バッファービューの生成
        m_vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
        m_vertexBufferView.SizeInBytes = (UINT)size;        // 全バイト数
        m_vertexBufferView.StrideInBytes = m_desc.vertexSize;   // １頂点あたりのバイト数
    }
    return S_OK;
}

//------------------------------------------------------------------------------
/// インデックスバッファの生成
///
/// \return 作成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D12MeshBuffer::CreateIndexBuffer()
{
    HRESULT hr = S_OK;
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();

    // ヒープの設定
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD; // CPUからアクセスできる
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    // インデックスバッファーの生成
    D3D12_RESOURCE_DESC indexResourceDesc = {};
    indexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;      // リソースのタイプ
    indexResourceDesc.Width =
        static_cast<UINT64>(m_desc.indexCount) * m_desc.indexSize;     // 頂点情報のサイズ
    indexResourceDesc.Height = 1;                                       // 頂点情報のサイズ(Widthに格納済み)
    indexResourceDesc.DepthOrArraySize = 1;                             // リソースの配列のサイズ
    indexResourceDesc.MipLevels = 1;
    indexResourceDesc.Format = DXGI_FORMAT_UNKNOWN;                     // フォーマット指定なし
    indexResourceDesc.SampleDesc.Count = 1;
    indexResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;                 // オプションなし
    indexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;          // データが行優先順で格納
    // インデックスバッファーの生成
    hr = pDevice->CreateCommittedResource(
        &heapprop,                              // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                   // 指定なし
        &indexResourceDesc,                     // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,      // アップロード ヒープに必要な開始状態
        nullptr,
        IID_PPV_ARGS(&m_pIndexBuffer));         // インデックスバッファー
    if (FAILED(hr)) return hr;

    // インデックス情報をバッファーにコピーする
    unsigned short* indexMap = nullptr;
    hr = m_pIndexBuffer->Map(0, nullptr, (void**)&indexMap);
    if (SUCCEEDED(hr))
    {
        // インデックスバッファービューの生成
        rsize_t size = static_cast<rsize_t>(m_desc.indexCount) * m_desc.indexSize;
        memcpy_s(indexMap, size, m_desc.pIndexData, size);
        m_pIndexBuffer->Unmap(0, nullptr);
        m_indexBufferView.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
        m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;    // フォーマット
        m_indexBufferView.SizeInBytes = (UINT)size;       // 全バイト数
    }
    

    return hr;
}

//------------------------------------------------------------------------------
/// 頂点バッファの更新
///
/// \param[in] pData 頂点バッファのデータ
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12MeshBuffer::Write(void* pData)
{
    void* vertMap = nullptr;
    auto hr = m_pVertexBuffer->Map(0, nullptr, (void**)&vertMap);
    if (SUCCEEDED(hr))
    {
        rsize_t size = static_cast<rsize_t>(m_desc.vertexCount) * m_desc.vertexSize;
        memcpy_s(vertMap, size, pData, size);
        m_pVertexBuffer->Unmap(0, nullptr);
        // 頂点バッファービューの生成
        m_vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
        m_vertexBufferView.SizeInBytes = (UINT)size;        // 全バイト数
        m_vertexBufferView.StrideInBytes = m_desc.vertexSize;   // １頂点あたりのバイト数
    }
}

//------------------------------------------------------------------------------
/// メッシュバッファの固定
///
/// \param[in] slot レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12MeshBuffer::Bind(unsigned int slot) const
{
    UNREFERENCED_PARAMETER(slot);

    // コマンドリストの取得
    auto pCommandList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();

    // 頂点バッファーの設定
    pCommandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);

    // プリミティブの設定
    D3D12_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    switch (m_desc.tpology)
    {
    case TOPOLOGY::LINE_LIST:       topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;     break;
    case TOPOLOGY::TRIANGLE_LIST:   topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
    case TOPOLOGY::TRIANGLE_STRIP:  topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
    default: break;
    }
    pCommandList->IASetPrimitiveTopology(topology);

    // 描画命令
    if (m_desc.indexCount > 0)
    {
        // インデックスバッファーの設定
        pCommandList->IASetIndexBuffer(&m_indexBufferView);
        pCommandList->DrawIndexedInstanced(m_desc.indexCount, 1, 0, 0, 0);
    }
    else
    {
        pCommandList->DrawInstanced(m_desc.vertexCount, 1, 0, 0);
    }
}
