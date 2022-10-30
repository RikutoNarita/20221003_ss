//==============================================================================
// Filename: Gfx_GraphicsObjectBase.h
// Description: グラフィックスオブジェクトのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_OBJECT_H__
#define __GRAPHICS_OBJECT_H__

#include <memory>

// クラス定義
class GfxGraphicsObjectBase
{
public:
    using Ptr = std::shared_ptr<GfxGraphicsObjectBase>;

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsObjectBase() {}

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsObjectBase() {}

    //------------------------------------------------------------------------------
    /// リソースの固定
    ///
    /// \param[in] slot レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind(
    /*[in]*/
    unsigned int slot = 0) const = 0;

    //------------------------------------------------------------------------------
};

template <typename T>
class GfxGraphicsObject : public GfxGraphicsObjectBase
{
public:
    using Ptr = std::shared_ptr<T>;

public:
    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsObject() {}

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsObject() {}

    //------------------------------------------------------------------------------
};

#endif // __GRAPHICS_OBJECT_H__
