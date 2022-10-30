//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_GRAPHICS_BINDER_H__
#define __D3D11_GRAPHICS_BINDER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>

// クラス定義
class GfxD3D11GraphicsBinder : public GfxGraphicsBinder
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11GraphicsBinder();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11GraphicsBinder();

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
    static const UINT MAX_TEXTURE = 1;
    static const UINT MAX_CONSTANTBUFFER = 4;
    GfxTexture* m_vertexResourceSRV[MAX_TEXTURE];
    GfxTexture* m_pixelResourceSRV[MAX_TEXTURE];
    GfxConstantBuffer* m_vertexResourceCB[MAX_CONSTANTBUFFER];
    GfxConstantBuffer* m_pixelResourceCB[MAX_CONSTANTBUFFER];
    //------------------------------------------------------------------------------
    /// <summary>
    /// MAX_TEXTURE         テクスチャの上限
    /// MAX_CONSTANTBUFFER  定数バッファの上限
    /// m_pixelResourceSRV  ピクセルシェーダーに送るシェーダーリソース
    /// m_vertexResourceSRV 頂点シェーダーに送るシェーダーリソース
    /// m_pixelResourceCB   ピクセルシェーダーに送る定数バッファ
    /// m_vertexResourceCB  頂点シェーダーに送る定数バッファ
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
