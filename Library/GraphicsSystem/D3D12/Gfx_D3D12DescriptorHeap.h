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

    //------------------------------------------------------------------------------
    /// �f�B�X�N���v�^�q�[�v�̍쐬
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Create();

    //------------------------------------------------------------------------------
    /// �f�B�X�N���v�^�q�[�v�̃o�C���h
    /// 
    /// \param[in] slot ���W�X�^�ԍ�
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(
        /*[in]*/
        unsigned int slot = 0) const final;
    
    //------------------------------------------------------------------------------
    /// �e�N�X�`���̃Z�b�g
    ///
    /// \pramga[in] res     �e�N�X�`�����\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindSRV(
        /*[in]*/
        ID3D12Resource* data,
        /*[in]*/
        GfxShader::KIND visible,
        /*[in]*/
        UINT slot);
    
    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�̃Z�b�g
    ///
    /// \pramga[in] res     �萔�o�b�t�@���\�[�X
    /// \pramga[in] shader  �V�F�[�_�[�̎��
    /// \pramga[in] slot    ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindCBV(
        /*[in]*/
        ID3D12Resource* data,
        /*[in]*/
        GfxShader::KIND visible,
        /*[in]*/
        UINT slot);

    //------------------------------------------------------------------------------
    /// �f�B�X�N���v�^�q�[�v�̎擾
    ///
    /// \return �f�B�X�N���v�^�q�[�v
    //------------------------------------------------------------------------------
    inline const ID3D12DescriptorHeap* Get() const
    {
        m_pSRVandCSBheap.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    static const UINT MAX_ROOT_PARAM = 2;
    static const UINT MAX_DHISCTIPTOR = MAX_ROOT_PARAM * 2; // rootparamer * �V�F�[�_�[�̎��(ps, vs)
    static const UINT MAX_TEXTURE = 1;
    static const UINT MAX_CONSTANTBUFFER = 4;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pSRVandCSBheap;
    D3D12_ROOT_PARAMETER m_rootParameters[MAX_ROOT_PARAM];
    D3D12_DESCRIPTOR_RANGE m_descriptorTableRange[MAX_DHISCTIPTOR];
    ID3D12Resource* m_pixelResourceSRV[MAX_TEXTURE];
    ID3D12Resource* m_vertexResourceSRV[MAX_TEXTURE];
    ID3D12Resource* m_pixelResourceCBV[MAX_CONSTANTBUFFER];
    ID3D12Resource* m_vertexResourceCBV[MAX_CONSTANTBUFFER];
    UINT m_descriptorHandleIncrementSize;
    int m_nNumPixelHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// MAX_ROOT_PARAM                  ���[�g�p�����[�^�[�̐�
    /// MAX_DHISCTIPTOR                 �f�B�X�N���v�^�����W�̐�
    /// MAX_TEXTURE                     �e�N�X�`���̍ő吔
    /// MAX_CONSTANTBUFFER              �萔�o�b�t�@�̍ő吔
    /// m_pSRVandCSBheap                �f�B�X�N���v�^�q�[�v
    /// m_rootParameters                ���[�g�p�����[�^
    /// m_descriptorTableRange          �f�B�X�N���v�^�����W
    /// m_pixelResourceSRV              �s�N�Z���V�F�[�_�[�ɑ���V�F�[�_�[���\�[�X�r���[
    /// m_vertexResourceSRV             ���_�V�F�[�_�[�ɑ���V�F�[�_�[���\�[�X�r���[
    /// m_pixelResourceCBV              �s�N�Z���V�F�[�_�[�ɑ���萔�o�b�t�@�r���[
    /// m_vertexResourceCBV             ���_�V�F�[�_�[�ɑ���萔�o�b�t�@�r���[
    /// m_descriptorHandleIncrementSize SRV,CBV�̃C���N�������g�T�C�Y�i�[�p
    /// m_nNumPixelHeap                 �s�N�Z���V�F�[�_�[�ɑ��郊�\�[�X�̐�
    /// </summary> 
};
#endif // __D3D12_DISCRIPTOR_HEAP_H__
