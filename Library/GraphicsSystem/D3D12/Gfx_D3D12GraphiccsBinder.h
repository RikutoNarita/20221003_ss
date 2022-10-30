//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_GRAPHICS_BINDER_H__
#define __D3D12_GRAPHICS_BINDER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PipelineState.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RootSignature.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12DescriptorHeap.h>

// クラス定義
class GfxD3D12GraphicsBinder : public GfxGraphicsBinder
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12GraphicsBinder();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12GraphicsBinder();

    //------------------------------------------------------------------------------
    /// リソースをバインドする
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind(
        /*[in]*/
        unsigned slot = 0) const final;

    //------------------------------------------------------------------------------
    /// パイプラインの構築
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Start() const final;

    //------------------------------------------------------------------------------
    /// メッシュバッファのセット
    ///
    /// \pramga[in] res メッシュバッファリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindMesh(
        /*[in]*/
        GfxMeshBuffer* res) final;

    //------------------------------------------------------------------------------
    /// ピクセルシェーダーのセット
    ///
    /// \pramga[in] res ピクセルシェーダーのリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(
        /*[in]*/
        GfxPixelShader* res) final;

    //------------------------------------------------------------------------------
    /// 頂点シェーダーのセット
    ///
    /// \pramga[in] res 頂点シェーダーのリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(
        /*[in]*/
        GfxVertexShader* res) final;

    //------------------------------------------------------------------------------
    /// テクスチャのセット
    ///
    /// \pramga[in] res     テクスチャリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindTexture(
        /*[in]*/
        GfxTexture* res,
        /*[in]*/
        GfxShader::KIND shader,
        /*[in]*/
        unsigned slot = 0) final;

    //------------------------------------------------------------------------------
    /// 定数バッファのセット
    ///
    /// \pramga[in] res     定数バッファリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindConstantBuffer(
        /*[in]*/
        GfxConstantBuffer* res,
        /*[in]*/
        GfxShader::KIND shader,
        /*[in]*/
        unsigned slot = 0) final;
    
    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    std::shared_ptr<GfxPipelineState>           m_pPipelineState;
    std::shared_ptr<GfxD3D12RootSignature>      m_pRootSignature;
    std::shared_ptr<GfxD3D12DescriptorHeap>     m_pDescriptorHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPipelineState    パイプラインステート
    /// m_pRootSignature    ルートシグネチャ
    /// m_pDescriptorHeap   ディスクリプタヒープ
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
