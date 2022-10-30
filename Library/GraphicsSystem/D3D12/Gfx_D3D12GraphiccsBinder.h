//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: ���\�[�X���o�C���h����N���X�̃x�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_GRAPHICS_BINDER_H__
#define __D3D12_GRAPHICS_BINDER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PipelineState.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RootSignature.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12DescriptorHeap.h>

// �N���X��`
class GfxD3D12GraphicsBinder : public GfxGraphicsBinder
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12GraphicsBinder();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12GraphicsBinder();

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
    std::shared_ptr<GfxPipelineState>           m_pPipelineState;
    std::shared_ptr<GfxD3D12RootSignature>      m_pRootSignature;
    std::shared_ptr<GfxD3D12DescriptorHeap>     m_pDescriptorHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPipelineState    �p�C�v���C���X�e�[�g
    /// m_pRootSignature    ���[�g�V�O�l�`��
    /// m_pDescriptorHeap   �f�B�X�N���v�^�q�[�v
    /// </summary> 
};
#endif // __GRAPHICS_RESOURCE_H__
