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
#include <vector>

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


    void Create(GfxD3D12RootSignature* root);

    void BindPS(GfxD3D12PixelShader* ps);
    void BindVS(GfxD3D12VertexShader* vs);


    void Bind(unsigned int slot = 0) const final;

    ID3D12PipelineState* Get()
    {
        return m_pPipeLineState.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pPipeLineState;   // �p�C�v���C���X�e�[�g
    D3D12_GRAPHICS_PIPELINE_STATE_DESC          m_pipelineDesc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDescriptorHeap       �f�B�X�N���v�^�q�[�v
    /// m_pFence                �t�F���X
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
