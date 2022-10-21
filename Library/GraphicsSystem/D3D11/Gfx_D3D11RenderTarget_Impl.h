//==============================================================================
// Filename: IGfx_D3D11RenderTarget_Impl.h
// Description: Direct3D 11�̃����_�[�^�[�Q�b�g�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_RENDER_TARGET_H__
#define __D3D11_RENDER_TARGET_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

// �N���X��`
class GfxD3D11RenderTarget : public IGfxRenderTarget
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11RenderTarget();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11RenderTarget() override;

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�̐���
    ///
    /// \param[in] desc         �ݒ荀��
    /// \param[in] pDevice      �f�o�C�X
    /// \param[in] pSwapChain   �X���b�v�`�F�[��
    /// 
    /// \return �����ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    const Description& desc,
    /*[in]*/
    IGfxDevice* pDevice,
    /*[in]*/
    IGfxSwapChain* pSwapChain) final;
    
    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�r���[�̎擾
    ///
    /// \return �����_�[�^�[�Q�b�g�r���[
    //------------------------------------------------------------------------------
    ID3D11RenderTargetView* GetRenderTargetView()
    {
        return m_pRenderTargetView.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pRenderTargetView   �����_�[�^�[�Q�b�g�r���[
    /// </summary>

};

#endif // __D3D11_RENDER_TARGET_H__
