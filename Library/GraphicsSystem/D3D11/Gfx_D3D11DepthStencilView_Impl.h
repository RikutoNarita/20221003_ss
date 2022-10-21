//==============================================================================
// Filename: Gfx_D3D11DepthStencilView_Impl.h
// Description: Direct3D 11�̃f�v�X�X�e���V���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_DEPTH_STENCIL_VIEW_H__
#define __D3D11_DEPTH_STENCIL_VIEW_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_DepthStencilView.h>
#include <d3d11.h>
#include <wrl\client.h>

// �N���X��`
class GfxD3D11DepthStencil : public IGfxDepthStencil
{
public:
    

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11DepthStencil();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11DepthStencil();
    
    //-----------------------------------------------------------------------------
    /// �f�v�X�X�e���V���r���[�̐���
    ///
    /// \param[in] desc     �ݒ荀�� 
    /// \param[in] pDevice  �f�o�C�X
    /// 
    /// \return �����ł����ꍇ S_OK
    //-----------------------------------------------------------------------------
    const HRESULT Create(
        /*[in]*/
        const Description& desc,
        /*[in]*/
        IGfxDevice* pDevice) final;

    //------------------------------------------------------------------------------
    /// �f�v�X�X�e���V���r���[�̎擾
    ///
    /// \return �f�v�X�X�e���V���r���[
    //------------------------------------------------------------------------------
    ID3D11DepthStencilView* GetDepthStencilView() const
    {
        return m_pDepthStencilView.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    m_pDepthStencilView;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDSVDescriptorHeap    �[�x�o�b�t�@�̃f�B�X�N���v�^�q�[�v
    /// m_pDepthBuffer          �[�x�o�b�t�@
    /// </summary>
};
#endif // __D3D11_DEPTH_STENCIL_VIEW_H__
