//==============================================================================
// Filename: Gfx_Texture.h
// Description: �e�N�X�`���̊��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <Windows.h>

// �N���X��`
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
    /// width       �e�N�X�`���̕�
    /// height      �e�N�X�`���̍���
    /// byteSize    �e�N�X�`���f�[�^�̃T�C�Y
    /// pData       �e�N�X�`���f�[�^
    /// format      �e�N�X�`���̃J���[�t�H�[�}�b�g
    /// kind        �e�N�X�`���̗p�r
    /// </summary> 

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] desc �e�N�X�`���̐ݒ荀��
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxTexture(Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxTexture();

    //------------------------------------------------------------------------------
    /// �e�N�X�`���f�[�^�̍쐬
    /// 
    /// \param[in] tag  ���\�[�X�ɕR�Â���^�O
    /// \param[in] desc �e�N�X�`���̐ݒ荀��
    ///
    /// \return ���̃N���X�̃|�C���^
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
    /// m_desc      �e�N�X�`���̐ݒ荀��
    /// </summary> 
};
#endif // __TEXTURE_H__
