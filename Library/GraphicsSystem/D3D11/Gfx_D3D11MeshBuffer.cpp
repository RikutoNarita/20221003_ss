// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11MeshBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc バッファの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D11MeshBuffer::GfxD3D11MeshBuffer(Description desc)
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

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11MeshBuffer::~GfxD3D11MeshBuffer()
{
}

//------------------------------------------------------------------------------
/// 頂点バッファの生成
///
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D11MeshBuffer::CreateVertexBuffer()
{
    ID3D11Device* pDevice = GRAPHICS->GetDevice<ID3D11Device>();

    // 作成するバッファ情報
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = m_desc.vertexSize * m_desc.vertexCount;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    if (m_desc.isWrite)
    {
        bufDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }

    //--- バッファの初期値を設定
    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = m_desc.pVertexData;

    //--- 頂点バッファの作成
    HRESULT hr;
    hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVertexBuffer);
    if (FAILED(hr)) { return hr; }

    return S_OK;
}

//------------------------------------------------------------------------------
/// インデックスバッファの生成
///
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
HRESULT GfxD3D11MeshBuffer::CreateIndexBuffer()
{
    // インデックスサイズの確認
    switch (m_desc.indexSize)
    {

    default:
        return E_FAIL;
    case 1:
    case 2:
    case 4:
        break;
    }

    ID3D11Device* pDevice = GRAPHICS->GetDevice<ID3D11Device>();

    // バッファの情報を設定
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = m_desc.indexSize * m_desc.indexCount;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    // バッファの初期データ
    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = m_desc.pIndexData;

    // インデックスバッファ生成
    HRESULT hr;
    hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIndexBuffer);
  
    return hr;
}

//------------------------------------------------------------------------------
/// バッファの更新
///
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
void GfxD3D11MeshBuffer::Write(void* pData)
{
    HRESULT hr;
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    D3D11_MAPPED_SUBRESOURCE mapResource;

    // データコピー
    hr = pContext->Map(m_pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

    if (SUCCEEDED(hr))
    {
        rsize_t size = (rsize_t)(m_desc.vertexSize * m_desc.vertexCount);
        memcpy_s(mapResource.pData, size, pData, size);
        pContext->Unmap(m_pVertexBuffer.Get(), 0);
    }
    else
    {
        _ASSERT_EXPR(false, L"NO_MAP");
    }
}

//------------------------------------------------------------------------------
/// バッファの描画
///
/// \return 生成できた場合 S_OK
//------------------------------------------------------------------------------
void GfxD3D11MeshBuffer::Bind(unsigned int indexCount) const
{
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    UINT stride = m_desc.vertexSize;
    UINT offset = 0;
    // トポロジーのセット
    D3D11_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    switch (m_desc.tpology)
    {
    case TOPOLOGY::LINE_LIST:      topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;      break;
    case TOPOLOGY::TRIANGLE_LIST:  topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;  break;
    case TOPOLOGY::TRIANGLE_STRIP: topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
    default:
        break;
    }
    pContext->IASetPrimitiveTopology(topology);

    // 頂点バッファの設定
    pContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

    // 描画
    if (m_desc.indexCount > 0)
    {
        DXGI_FORMAT format = {};
        switch (m_desc.indexSize)
        {
        case 4: format = DXGI_FORMAT_R32_UINT; break;
        case 2: format = DXGI_FORMAT_R16_UINT; break;
        case 1: format = DXGI_FORMAT_R8_UINT; break;
        }
        pContext->IASetIndexBuffer(m_pIndexBuffer.Get(), format, 0);
        pContext->DrawIndexed(indexCount ? indexCount : m_desc.indexCount, 0, 0);
    }
    else
    {
        // 頂点バッファのみで描画
        pContext->Draw(indexCount ? indexCount : m_desc.vertexCount, 0);
    }
}
