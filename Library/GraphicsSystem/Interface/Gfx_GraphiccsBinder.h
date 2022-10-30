//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: ���\�[�X���o�C���h����N���X�̃x�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __GRAPHICS_BINDER_H__
#define __GRAPHICS_BINDER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>

// �N���X��`
class GfxGraphicsBinder : public GfxGraphicsObject<GfxGraphicsBinder>
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsBinder();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxGraphicsBinder();

    //------------------------------------------------------------------------------
    /// �p�C�v���C���̍\�z
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Start() const = 0;

    //------------------------------------------------------------------------------
    /// ���b�V���o�b�t�@�̃Z�b�g
    ///
    /// \pramga[in] res ���b�V���o�b�t�@���\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindMesh(
        /*[in]*/
        GfxMeshBuffer* res) = 0;

    //------------------------------------------------------------------------------
    /// �s�N�Z���V�F�[�_�[�̃Z�b�g
    ///
    /// \pramga[in] res �s�N�Z���V�F�[�_�[�̃��\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindPS(
        /*[in]*/
        GfxPixelShader* res) = 0;

    //------------------------------------------------------------------------------
    /// ���_�V�F�[�_�[�̃Z�b�g
    ///
    /// \pramga[in] res ���_�V�F�[�_�[�̃��\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BindVS(
        /*[in]*/
        GfxVertexShader* res) = 0;

    //------------------------------------------------------------------------------
    /// �e�N�X�`���̃Z�b�g
    ///
    /// \pramga[in] res     �e�N�X�`�����\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
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
    /// �萔�o�b�t�@�̃Z�b�g
    ///
    /// \pramga[in] res     �萔�o�b�t�@���\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
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
    /// ���\�[�X�o�C���_�[�̍쐬
    ///
    /// \pramga[in] tag ���\�[�X�R�Â���^�O
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
    /// m_pMesh ���b�V���o�b�t�@�[
    /// m_pVS   ���_�V�F�[�_�[
    /// m_pPS   �s�N�Z���V�F�[�_�[
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
