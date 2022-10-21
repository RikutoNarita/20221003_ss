//==============================================================================
// Filename: Gfx_D3D11RenderCommand_Impl.h
// Description: Direct3D 11�̕`�施�߃N���X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_RENDER_COMMAND_H__
#define __D3D11_RENDER_COMMAND_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_RenderCommand.h>
#include <wrl\client.h>
#include <d3d11.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>

// �N���X��`
class GfxD3D11RenderCommand : public IGfxRenderCommand
{
    friend HRESULT DeviceFactory::CreateDeviceAndContext(
        int apiKind,
        std::shared_ptr<IGfxDevice>& pDevice,
        std::shared_ptr<IGfxRenderCommand>& pRenderCommand);

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11RenderCommand();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D11RenderCommand();

    //------------------------------------------------------------------------------
    /// �o�b�N�o�b�t�@�̃N���A
    ///
    /// \param[in] pRenderTagetView �����_�[�^�[�Q�b�g
    /// \param[in] clearColor       �N���A����F
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearRenderTargetView(
        /*[in]*/
        IGfxRenderTarget* pRenderTargetView,
        /*[in]*/
        const float clearColor[4]) const final;

    //------------------------------------------------------------------------------
    /// Z�o�b�t�@�̃N���A
    ///
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearDepthStencilView(
        /*[in]*/
        IGfxDepthStencil* DepthStencilView) const final;

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[�̎w��
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    /// 
    /// \param[in] pRenderTagetView     �����_�[�^�[�Q�b�g�r���[
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void OMSetRenderTargets(
        /*[in]*/
        IGfxRenderTarget* pRenderTargetView,
        /*[in]*/
        IGfxDepthStencil* pDepthStencilView) final;

    //------------------------------------------------------------------------------
    /// �`��I�����߁i�o�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ��j
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw() final;

    //------------------------------------------------------------------------------
    /// �f�o�C�X�R���e�L�X�g�̎擾
    ///
    /// \return �f�o�C�X�R���e�L�X�g
    //------------------------------------------------------------------------------
    ID3D11DeviceContext* GetDeviceContext() const
    {
        return m_pDeviceContext.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDeviceContext   �f�o�C�X�R���e�L�X�g
    /// </summary> 
};
#endif // __D3D11_RENDER_COMMAND_H__
