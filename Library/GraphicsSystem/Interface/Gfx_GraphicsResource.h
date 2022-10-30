//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: �O���t�B�b�N���\�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __GRAPHICS_RESOURCE_H__
#define __GRAPHICS_RESOURCE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <map>

// �N���X��`
class GfxGraphicsResource
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsResource();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsResource();

    //------------------------------------------------------------------------------
    /// ���\�[�X�̓o�^
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
    /// ���\�[�X�̌���
    ///
    /// \param[in] tag
    /// 
    /// \return ���\�[�X�̃|�C���^
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
