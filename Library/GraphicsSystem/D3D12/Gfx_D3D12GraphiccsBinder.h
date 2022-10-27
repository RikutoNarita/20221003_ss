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
    /// ���\�[�X��GPU�Ƀo�C���h����
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind(unsigned slot = 0) const final;

    //------------------------------------------------------------------------------
    /// �p�C�v���C���̍\�z
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Start() const final;

    void BindMesh(GfxMeshBuffer* res) final;
    void BindPS(GfxPixelShader* res) final;
    void BindVS(GfxVertexShader* res) final;
    void BindTexture(GfxTexture* res, GfxShader::KIND shader, unsigned slot = 0) final;

    void BindConstantBuffer(GfxConstantBuffer*, GfxShader::KIND shader, unsigned slot = 0) final;
    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    std::shared_ptr<GfxPipelineState>           m_pPipelineState;
    std::shared_ptr<GfxD3D12RootSignature>      m_pRootSignature;
    std::shared_ptr<GfxD3D12DescriptorHeap>     m_pDescriptorHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// 
    /// </summary> 
};



#endif // __GRAPHICS_RESOURCE_H__
