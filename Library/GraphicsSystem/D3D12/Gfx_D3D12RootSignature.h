//==============================================================================
// Filename: Gfx_D3D12RootSigunature.h
// Description: ���[�g�V�O�l�`���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_ROOT_SIGNATURE_H__
#define __D3D12_ROOT_SIGNATURE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>
#include <GraphicsSystem\D3D12\Gfx_D3D12DescriptorHeap.h>



// �N���X��`
class GfxD3D12RootSignature : GfxGraphicsObject<GfxD3D12RootSignature>
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12RootSignature();
    
    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12RootSignature();

    void Bind(unsigned slot = 0) const final;

    void Create(GfxD3D12DescriptorHeap* pDescriptorHeap);

    ID3D12RootSignature* Get()
    {
        return m_pRootSignature.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3DBlob>            m_pBlob;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pRootSignature;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pRootSignature       ���[�g�V�O�l�`��
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
