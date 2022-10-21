//==============================================================================
// Filename: IGfx_RenderCommand.h
// Description: �`�施�߃N���X�̃C���^�[�t�F�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __RENDER_COMMAND_H__
#define __RENDER_COMMAND_H__

// �O���錾
class IGfxRenderTarget;
class IGfxDepthStencil;

// �N���X��`
class IGfxRenderCommand
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    IGfxRenderCommand() {};

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~IGfxRenderCommand() {};

    //------------------------------------------------------------------------------
    /// �o�b�N�o�b�t�@�̃N���A
    ///
    /// \param[in] pRenderTagetView �����_�[�^�[�Q�b�g
    /// \param[in] clearColor       �N���A����F
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void ClearRenderTargetView(
    /*[in]*/
    IGfxRenderTarget* pRenderTagetView,
    /*[in]*/
    const float clearColor[4]) const = 0;

    //------------------------------------------------------------------------------
    /// Z�o�b�t�@�̃N���A
    ///
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void ClearDepthStencilView(
    /*[in]*/
    IGfxDepthStencil* pDepthStencilView) const = 0;

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[�̎w��
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    /// 
    /// \param[in] pRenderTagetView     �����_�[�^�[�Q�b�g�r���[
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void OMSetRenderTargets(
    /*[in]*/
    IGfxRenderTarget* pRenderTagetView,
    /*[in]*/
    IGfxDepthStencil* pDepthStencilView) = 0;

    //------------------------------------------------------------------------------
    /// �`��I�����߁i�o�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ��j
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void EndDraw() = 0;

    //------------------------------------------------------------------------------
};
#endif // __RENDER_COMMAND_H__
