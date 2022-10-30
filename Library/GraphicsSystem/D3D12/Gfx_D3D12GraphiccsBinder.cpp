//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12GraphicsBinder::GfxD3D12GraphicsBinder()
{
    m_pDescriptorHeap = std::make_shared<GfxD3D12DescriptorHeap>();
    m_pPipelineState  = std::make_shared<GfxPipelineState>();
    m_pRootSignature  = std::make_shared<GfxD3D12RootSignature>();
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12GraphicsBinder::~GfxD3D12GraphicsBinder()
{
}

//------------------------------------------------------------------------------
/// リソースをGPUにバインドする
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::Bind(unsigned slot) const
{
    UNREFERENCED_PARAMETER(slot);

    // パイプラインをセット
    m_pPipelineState->Bind();
    // ルートシグネチャをセット
    m_pRootSignature->Bind();
    // ディスクリプタヒープをセット
    m_pDescriptorHeap->Bind();

    // 頂点バッファ、インデックスバッファのセット
    m_pMeshBuffer->Bind();
}

//------------------------------------------------------------------------------
/// パイプラインの構築
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::Start() const
{
    // ディスクリプタヒープの生成
    m_pDescriptorHeap->Create();

    // ルートシグネチャの作成
    m_pRootSignature->Create(m_pDescriptorHeap.get());

    // パイプラインの生成
    m_pPipelineState->Create(m_pRootSignature.get());
}

//------------------------------------------------------------------------------
/// メッシュバッファのセット
///
/// \pramga[in] res メッシュバッファリソース
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::BindMesh(GfxMeshBuffer* res)
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
void GfxD3D12GraphicsBinder::BindPS(GfxPixelShader* res)
{
    m_pPipelineState->BindPS(dynamic_cast<GfxD3D12PixelShader*>(res));
}

//------------------------------------------------------------------------------
/// 頂点シェーダーのセット
///
/// \pramga[in] res 頂点シェーダーのリソース
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::BindVS(GfxVertexShader* res)
{
    m_pPipelineState->BindVS(dynamic_cast<GfxD3D12VertexShader*>(res));
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
void GfxD3D12GraphicsBinder::BindTexture(
    GfxTexture* pTex, GfxShader::KIND shader, unsigned slot)
{
    m_pDescriptorHeap->BindSRV(
        dynamic_cast<GfxD3D12Texture*>(pTex)->Get(),
        shader,
        slot);
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
void GfxD3D12GraphicsBinder::BindConstantBuffer(
    GfxConstantBuffer* pBuff, GfxShader::KIND shader, unsigned slot)
{
    m_pDescriptorHeap->BindCBV(
        dynamic_cast<GfxD3D12ConstantBuffer*>(pBuff)->Get(),
        shader,
        slot);
}
