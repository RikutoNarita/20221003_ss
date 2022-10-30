//==============================================================================
// Filename: Gfx_Texture.h
// Description: テクスチャの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <Windows.h>

// クラス定義
class GfxTexture : public GfxGraphicsObject<GfxTexture>
{
public:
    //------------------------------------------------------------------------------
    enum COLOR_FORMAT
    {
        COLOR_R8G8B8A8_UNORM,
        COLOR_R8G8B8A8_FLOAT,
        COLOR_R32_SINT,
        COLOR_R32_FLOAT,
        COLOR_R32_UINT,
        COLOR_R32_TYPELESS,
        COLOR_R24G8_TYPELESS,
    };
    enum KIND
    {
        KIND_RENDERTARGET,
        KIND_DEPTHSTENCIL,
        KIND_SHADERRESOURCE,
    };
    struct Description
    {
        unsigned int width;
        unsigned int height;
        unsigned int byteSize;
        void* pData;
        COLOR_FORMAT format;
        KIND kind;
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// Description
    /// width       テクスチャの幅
    /// height      テクスチャの高さ
    /// byteSize    テクスチャデータのサイズ
    /// pData       テクスチャデータ
    /// format      テクスチャのカラーフォーマット
    /// kind        テクスチャの用途
    /// </summary> 

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] desc テクスチャの設定項目
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxTexture(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxTexture();

    //------------------------------------------------------------------------------
    /// テクスチャデータの作成
    /// 
    /// \param[in] tag  リソースに紐づけるタグ
    /// \param[in] desc テクスチャの設定項目
    ///
    /// \return このクラスのポインタ
    //------------------------------------------------------------------------------
    static GfxTexture::Ptr Create(
    /*[in]*/
    const GfxTag& tag,
    /*[in]*/
    Description desc);

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Description m_desc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc      テクスチャの設定項目
    /// </summary> 
};
#endif // __TEXTURE_H__
