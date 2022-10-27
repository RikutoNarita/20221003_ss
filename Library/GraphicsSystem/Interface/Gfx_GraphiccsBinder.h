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
#include <vector>
#include <memory>

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
    GfxGraphicsBinder() {}

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsBinder() {}

    

    //------------------------------------------------------------------------------
    /// パイプラインの構築
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Start() const = 0;


    virtual void BindMesh(GfxMeshBuffer* res) = 0;
    virtual void BindPS(GfxPixelShader* res) = 0;
    virtual void BindVS(GfxVertexShader* res) = 0;
    virtual void BindTexture(GfxTexture* res, GfxShader::KIND shader, unsigned slot = 0) = 0;
    virtual void BindConstantBuffer(GfxConstantBuffer* res, GfxShader::KIND shader, unsigned slot = 0) = 0;


    static GfxGraphicsBinder::Ptr Create(const GfxTag& tag);
    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    GfxMeshBuffer* m_pMesh;
    GfxVertexShader* m_pVS;
    GfxPixelShader* m_pPS;
    //------------------------------------------------------------------------------

};



#endif // __GRAPHICS_RESOURCE_H__
