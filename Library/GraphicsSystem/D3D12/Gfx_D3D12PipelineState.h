//==============================================================================
// Filename: Gfx_D3D12PipelineState.h
// Description: �p�C�v���C���X�e�[�g�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_PIPELINE_STATE_H__
#define __D3D12_PIPELINE_STATE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <d3d12.h>
#include <wrl/client.h>

// �O���錾
class GfxD3D12PixelShader;
class GfxD3D12VertexShader;
class GfxD3D12RootSignature;

// �N���X��`
class GfxPipelineState : GfxGraphicsObject<GfxPipelineState>
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxPipelineState();
    
    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxPipelineState();

    //------------------------------------------------------------------------------
    /// �f�p�C�v���C���̍쐬
    ///
    /// \param[in] pRootParameter ���[�g�p�����[�^�[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Create(
        /*[in]*/
        GfxD3D12RootSignature* pRootParameter);

    //------------------------------------------------------------------------------
    /// �p�C�v���C���Ƀs�N�Z���V�F�[�_�[���o�C���h����
    ///
    /// \param[in] ps �s�N�Z���V�F�[�_�[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(
        /*[in]*/
        GfxD3D12PixelShader* ps);

    //------------------------------------------------------------------------------
    /// �p�C�v���C���ɒ��_�V�F�[�_�[���o�C���h����
    ///
    /// \param[in] vs ���_�V�F�[�_�[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(
        /*[in]*/
        GfxD3D12VertexShader* vs);


    //------------------------------------------------------------------------------
    /// �p�C�v���C���̃o�C���h
    ///
    /// \param[in] slot ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(
        /*[in]*/
        unsigned int slot = 0) const final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pPipeLineState;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC          m_pipelineDesc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPipeLineState    �p�C�v���C���X�e�[�g
    /// m_pipelineDesc      �p�C�v���C���X�e�[�g�̐ݒ荀��
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
