//==============================================================================
// Filename: Gfx_D3D12DepthStencilView_Impl.h
// Description: Direct3D 12�̃f�v�X�X�e���V���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_DEPTH_STENCIL_VIEW_H__
#define __D3D12_DEPTH_STENCIL_VIEW_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_DepthStencilView.h>
#include <d3d12.h>
#include <wrl\client.h>

// �N���X��`
class GfxD3D12DepthStencil : public IGfxDepthStencil
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12DepthStencil();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12DepthStencil();

    
    //------------------------------------------------------------------------------
    /// �f�v�X�X�e���V���r���[�̐���
    ///
    /// \param[in] desc     �ݒ荀�� 
    /// \param[in] pDevice  �f�o�C�X
    /// 
    /// \return �����ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    const HRESULT Create(
        /*[in]*/
        const Description& desc,
        /*[in]*/
        IGfxDevice* pDevice) final;

    
    //------------------------------------------------------------------------------
    /// �f�v�X�X�e���V���r���[�̃f�X�N���v�^�q�[�v�̎擾
    ///
    /// \return �f�v�X�X�e���V���r���[�̃f�X�N���v�^�q�[�v
    //------------------------------------------------------------------------------
    ID3D12DescriptorHeap* GetDescHeap() const
    {
        return m_pDSVDescriptorHeap.Get();
    }

    //------------------------------------------------------------------------------
    /// �[�x�o�b�t�@�̎擾
    ///
    /// \return �[�x�o�b�t�@
    //------------------------------------------------------------------------------
    ID3D12Resource* GetDepthBuffer() const
    {
        return m_pDepthBuffer.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    m_pDSVDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12Resource>          m_pDepthBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDSVDescriptorHeap    �[�x�o�b�t�@�̃f�B�X�N���v�^�q�[�v
    /// m_pDepthBuffer          �[�x�o�b�t�@
    /// </summary>
};
#endif // __D3D12_DEPTH_STENCIL_VIEW_H__
