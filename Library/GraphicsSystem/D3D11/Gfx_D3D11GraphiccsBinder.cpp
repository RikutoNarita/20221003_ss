// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11GraphicsBinder::GfxD3D11GraphicsBinder()
    : m_vertexResourceSRV{nullptr}, m_pixelResourceSRV{nullptr}
    , m_vertexResourceCB{nullptr}, m_pixelResourceCB{nullptr}
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11GraphicsBinder::~GfxD3D11GraphicsBinder()
{
}

//------------------------------------------------------------------------------
/// リソースをGPUにバインドする
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::Bind(unsigned slot) const
{
    // テクスチャのセット
    for (size_t i = 0; i < _countof(m_pixelResourceSRV); i++)
    {
        // ピクセルシェーダーにセット
        m_pPS->SetTexture(m_pixelResourceSRV[i], i);
    }
    for (size_t i = 0; i < _countof(m_vertexResourceSRV); i++)
    {
        // ピクセルシェーダーにセット
        m_pVS->SetTexture(m_vertexResourceSRV[i], i);
    }

    // 定数バッファのセット
    for (size_t i = 0; i < _countof(m_pixelResourceCB); i++)
    {
        // ピクセルシェーダーにセット
        m_pPS->SetBuffer(m_pixelResourceCB[i], i);
    }
    for (size_t i = 0; i < _countof(m_vertexResourceCB); i++)
    {
        // ピクセルシェーダーにセット
        m_pVS->SetBuffer(m_vertexResourceCB[i], i);
    }

    m_pVS->Bind();
    m_pPS->Bind();
    m_pMesh->Bind();
}

//------------------------------------------------------------------------------
/// パイプラインの構築
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::Start() const
{
    
}


void GfxD3D11GraphicsBinder::BindMesh(GfxMeshBuffer* res)
{
    m_pMesh = res;
}
void GfxD3D11GraphicsBinder::BindPS(GfxPixelShader* res)
{
    m_pPS = res;
}
void GfxD3D11GraphicsBinder::BindVS(GfxVertexShader* res)
{
    m_pVS = res;
}

void GfxD3D11GraphicsBinder::BindTexture(GfxTexture* res, GfxShader::KIND shader, unsigned slot)
{
    if (shader == GfxShader::KIND::KIND_PS)
    {
        m_pixelResourceSRV[slot] = res;
    }
    else
    {
        m_vertexResourceSRV[slot] = res;
    }
}

void GfxD3D11GraphicsBinder::BindConstantBuffer(GfxConstantBuffer* res, GfxShader::KIND shader, unsigned slot)
{
    if (shader == GfxShader::KIND::KIND_PS)
    {
        m_pixelResourceCB[slot] = res;
    }
    else
    {
        m_vertexResourceCB[slot] = res;
    }
}
