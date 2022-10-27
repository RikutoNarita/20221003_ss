//==============================================================================
// Filename: Gfx_D3D12DiscriptorHeap.h
// Description: �f�B�X�N���v�^�q�[�v�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_DISCRIPTOR_HEAP_H__
#define __D3D12_DISCRIPTOR_HEAP_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>

// �N���X��`
class GfxD3D12DescriptorHeap : GfxGraphicsObject<GfxD3D12DescriptorHeap>
{
    friend class GfxD3D12RootSignature;
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12DescriptorHeap();
    
    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12DescriptorHeap();


    void BindSRV(UINT slot, ID3D12Resource* data, GfxShader::KIND visible);
    void BindCBV(UINT slot, ID3D12Resource* data, GfxShader::KIND visible);

    void Start();

    void SetDescriptorHeap();

    void SetRootDescriptorTable();
    
    inline const ID3D12DescriptorHeap* Get() const
    {
        m_pSRVandCSBheap.Get();
    }

    void Bind(unsigned int slot = 0) const final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pSRVandCSBheap;

    static const UINT MAX_ROOT_PARAM = 2;
    D3D12_ROOT_PARAMETER m_rootParameters[MAX_ROOT_PARAM];
    static const UINT MAX_DHISCTIPTOR = MAX_ROOT_PARAM * 2; // rootparamer * �V�F�[�_�[�̎��(ps, vs)
    D3D12_DESCRIPTOR_RANGE m_descriptorTableRange[MAX_DHISCTIPTOR];

    static const UINT MAX_TEXTURE = 1;
    ID3D12Resource* m_pixelResourceSRV[MAX_TEXTURE];
    ID3D12Resource* m_vertexResourceSRV[MAX_TEXTURE];
    static const UINT MAX_CONSTANTBUFFER = 4;
    ID3D12Resource* m_pixelResourceCBV[MAX_CONSTANTBUFFER];
    ID3D12Resource* m_vertexResourceCBV[MAX_CONSTANTBUFFER];

    UINT m_descriptorHandleIncrementSize;
    int m_nNumPixelHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pSRVandCSBheap    �V�F�[�_�[���\�[�X�r���[�ƒ萔�o�b�t�@�̃f�B�X�N���v�^�q�[�v
    /// m_rootParameters    ���[�g�p�����[�^�[
    /// m_rootParameters    �f�B�X�N���v�^�����W
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
