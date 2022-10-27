//==============================================================================
// Filename: Gfx_ConstantBuffer.h
// Description: �萔�o�b�t�@�̊��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __CONSTANT_BUFER_H__
#define __CONSTANT_BUFER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <Windows.h>

// �N���X��`
class GfxConstantBuffer : public GfxGraphicsObject<GfxConstantBuffer>
{
public:
    //------------------------------------------------------------------------------
    enum class Shader
    {
        BIND_VERTEX,
        BIND_PIXEL,
    };

    struct Description
    {
       size_t size;
       void* pData;
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// Description
    /// </summary> 

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] desc �萔�o�b�t�@�̐ݒ荀��
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxConstantBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxConstantBuffer();


    virtual void Write(void* pData) = 0;

    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�̍쐬
    /// 
    /// \param[in] tag  ���\�[�X�ɕR�Â���^�O
    /// \param[in] desc �萔�o�b�t�@�̐ݒ荀��
    ///
    /// \return ���̃N���X�̃|�C���^
    //------------------------------------------------------------------------------
    static GfxConstantBuffer::Ptr Create(const GfxTag& tag, Description desc);

    virtual void BindVS(unsigned slot) = 0;
    virtual void BindPS(unsigned slot) = 0;


    //void SetShaderKind(Shader bindShader)
    //{
    //    m_eBind = bindShader;
    //}
    //
    //void SetSlot(unsigned slot)
    //{
    //    m_nSlot = slot;
    //}
    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Description m_desc;
    unsigned m_nSlot;
    Shader m_eBind;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc      �萔�o�b�t�@�̐ݒ荀��
    /// </summary> 
};
#endif // __CONSTANT_BUFER_H__
