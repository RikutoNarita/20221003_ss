//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: ���\�[�X���o�C���h����N���X�̃x�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_GRAPHICS_BINDER_H__
#define __D3D11_GRAPHICS_BINDER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>

// �N���X��`
class GfxD3D11GraphicsBinder : public GfxGraphicsBinder
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11GraphicsBinder();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11GraphicsBinder();

    //------------------------------------------------------------------------------
    /// ���\�[�X���o�C���h����
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind(
    /*[in]*/
    unsigned slot = 0) const final;

    //------------------------------------------------------------------------------
    /// �p�C�v���C���̍\�z
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Start() const final;

    //------------------------------------------------------------------------------
    /// ���b�V���o�b�t�@�̃Z�b�g
    ///
    /// \pramga[in] res ���b�V���o�b�t�@���\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindMesh(
        /*[in]*/
        GfxMeshBuffer* res) final;

    //------------------------------------------------------------------------------
    /// �s�N�Z���V�F�[�_�[�̃Z�b�g
    ///
    /// \pramga[in] res �s�N�Z���V�F�[�_�[�̃��\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(
        /*[in]*/
        GfxPixelShader* res) final;

    //------------------------------------------------------------------------------
    /// ���_�V�F�[�_�[�̃Z�b�g
    ///
    /// \pramga[in] res ���_�V�F�[�_�[�̃��\�[�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(
        /*[in]*/
        GfxVertexShader* res) final;

    //------------------------------------------------------------------------------
    /// �e�N�X�`���̃Z�b�g
    ///
    /// \pramga[in] res     �e�N�X�`�����\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
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
    /// �萔�o�b�t�@�̃Z�b�g
    ///
    /// \pramga[in] res     �萔�o�b�t�@���\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
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
    /// MAX_TEXTURE         �e�N�X�`���̏��
    /// MAX_CONSTANTBUFFER  �萔�o�b�t�@�̏��
    /// m_pixelResourceSRV  �s�N�Z���V�F�[�_�[�ɑ���V�F�[�_�[���\�[�X
    /// m_vertexResourceSRV ���_�V�F�[�_�[�ɑ���V�F�[�_�[���\�[�X
    /// m_pixelResourceCB   �s�N�Z���V�F�[�_�[�ɑ���萔�o�b�t�@
    /// m_vertexResourceCB  ���_�V�F�[�_�[�ɑ���萔�o�b�t�@
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
