//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: グラフィックリソースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_RESOURCE_H__
#define __GRAPHICS_RESOURCE_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <map>

// クラス定義
class GfxGraphicsResource
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsResource();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsResource();

    //------------------------------------------------------------------------------
    /// リソースの登録
    ///
    /// \param[in] tag
    /// \param[in] pResource
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    static void Resister(
        /*[in]*/
        const GfxTag& tag,
        /*[in]*/
        GfxGraphicsObjectBase::Ptr pResource);

    //------------------------------------------------------------------------------
    /// リソースの検索
    ///
    /// \param[in] tag
    /// 
    /// \return リソースのポインタ
    //------------------------------------------------------------------------------
    template <class T>
    static T* Find(
        /*[in]*/
        GfxTag tag);

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    static std::map<GfxTag, GfxGraphicsObjectBase::Ptr> m_resources;
    //------------------------------------------------------------------------------

};

template <class T>
T* GfxGraphicsResource::Find(GfxTag tag)
{
    auto itr = m_resources.find(tag);

    if (itr == m_resources.end())
    {
        return nullptr;
    }
    else
    {
        return reinterpret_cast<T*>(itr->second.get());
    }
}

#endif // __GRAPHICS_RESOURCE_H__
