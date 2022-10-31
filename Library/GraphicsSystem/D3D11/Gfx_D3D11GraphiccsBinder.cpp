//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

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
    UNREFERENCED_PARAMETER(slot);
    // テクスチャをセット
    for (unsigned int i = 0; i < _countof(m_pixelResourceSRV); i++)
    {
        // ピクセルシェーダーにセット
        m_pPS->SetTexture(m_pixelResourceSRV[i], i);
    }
    for (unsigned int i = 0; i < _countof(m_vertexResourceSRV); i++)
    {
        // ピクセルシェーダーにセット
        m_pVS->SetTexture(m_vertexResourceSRV[i], i);
    }

    // 定数バッファをセット
    for (unsigned int i = 0; i < _countof(m_pixelResourceCB); i++)
    {
        // ピクセルシェーダーにセット
        m_pPS->SetBuffer(m_pixelResourceCB[i], i);
    }
    for (unsigned int i = 0; i < _countof(m_vertexResourceCB); i++)
    {
        // ピクセルシェーダーにセット
        m_pVS->SetBuffer(m_vertexResourceCB[i], i);
    }

    // シェーダーのバインド
    m_pVS->Bind();
    m_pPS->Bind();
    // メッシュバッファのバインド
    m_pMeshBuffer->Bind();
}

//------------------------------------------------------------------------------
/// パイプラインの構築
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::Start() const
{
    
}

//------------------------------------------------------------------------------
/// メッシュバッファのセット
///
/// \pramga[in] res メッシュバッファリソース
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::BindMesh(GfxMeshBuffer* res)
{
    m_pMeshBuffer = res;
}

//------------------------------------------------------------------------------
/// ピクセルシェーダーのセット
///
/// \pramga[in] res ピクセルシェーダーのリソース
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::BindPS(GfxPixelShader* res)
{
    m_pPS = res;
}

//------------------------------------------------------------------------------
/// 頂点シェーダーのセット
///
/// \pramga[in] res 頂点シェーダーのリソース
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::BindVS(GfxVertexShader* res)
{
    m_pVS = res;
}

//------------------------------------------------------------------------------
/// テクスチャのセット
///
/// \pramga[in] res     テクスチャリソース
/// \pramga[in] shader  シェーダーの種類
/// \pramga[in] slot    レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::BindTexture(
    GfxTexture* res, GfxShader::KIND shader, unsigned slot)
{
    if (shader == GfxShader::KIND::KIND_PS)
    {
        m_pixelResourceSRV[slot] = res;
    }
    else if (shader == GfxShader::KIND::KIND_VS)
    {
        m_vertexResourceSRV[slot] = res;
    }
}

//------------------------------------------------------------------------------
/// 定数バッファのセット
///
/// \pramga[in] res     定数バッファリソース
/// \pramga[in] shader  シェーダーの種類
/// \pramga[in] slot    レジスタ番号
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11GraphicsBinder::BindConstantBuffer(
    GfxConstantBuffer* res, GfxShader::KIND shader, unsigned slot)
{
    if (shader == GfxShader::KIND::KIND_PS)
    {
        m_pixelResourceCB[slot] = res;
    }
    else if (shader == GfxShader::KIND::KIND_VS)
    {
        m_vertexResourceCB[slot] = res;
    }
}
