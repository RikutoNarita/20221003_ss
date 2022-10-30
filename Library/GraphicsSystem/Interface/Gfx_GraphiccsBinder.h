//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_BINDER_H__
#define __GRAPHICS_BINDER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>

// クラス定義
class GfxGraphicsBinder : public GfxGraphicsObject<GfxGraphicsBinder>
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsBinder();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsBinder();

    //------------------------------------------------------------------------------
    /// パイプラインの構築
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Start() const = 0;

    //------------------------------------------------------------------------------
    /// メッシュバッファのセット
    ///
    /// \pramga[in] res メッシュバッファリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindMesh(
        /*[in]*/
        GfxMeshBuffer* res) = 0;

    //------------------------------------------------------------------------------
    /// ピクセルシェーダーのセット
    ///
    /// \pramga[in] res ピクセルシェーダーのリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindPS(
        /*[in]*/
        GfxPixelShader* res) = 0;

    //------------------------------------------------------------------------------
    /// 頂点シェーダーのセット
    ///
    /// \pramga[in] res 頂点シェーダーのリソース
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindVS(
        /*[in]*/
        GfxVertexShader* res) = 0;

    //------------------------------------------------------------------------------
    /// テクスチャのセット
    ///
    /// \pramga[in] res     テクスチャリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindTexture(
        /*[in]*/
        GfxTexture* res,
        /*[in]*/
        GfxShader::KIND shader,
        /*[in]*/
        unsigned slot = 0) = 0;

    //------------------------------------------------------------------------------
    /// 定数バッファのセット
    ///
    /// \pramga[in] res     定数バッファリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindConstantBuffer(
        /*[in]*/
        GfxConstantBuffer* res,
        /*[in]*/
        GfxShader::KIND shader,
        /*[in]*/
        unsigned slot = 0) = 0;

    //------------------------------------------------------------------------------
    /// リソースバインダーの作成
    ///
    /// \pramga[in] tag リソース紐づけるタグ
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    static GfxGraphicsBinder::Ptr Create(
        /*[in]*/
        const GfxTag& tag);

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    GfxMeshBuffer* m_pMeshBuffer;
    GfxVertexShader* m_pVS;
    GfxPixelShader* m_pPS;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pMesh メッシュバッファー
    /// m_pVS   頂点シェーダー
    /// m_pPS   ピクセルシェーダー
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
