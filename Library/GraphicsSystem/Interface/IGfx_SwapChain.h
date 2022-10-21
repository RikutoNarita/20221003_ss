//==============================================================================
// Filename: IGfx_SwapChain.h
// Description: �X���b�v�`�F�[���̃C���^�[�t�F�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __SWAP_CHAIN_H__
#define __SWAP_CHAIN_H__

// �C���N���[�h
#include <dxgi.h>
#include <Windows.h>

// �O���錾
class IGfxDevice;
class IGfxRenderCommand;

// �N���X��`
class IGfxSwapChain
{
public:
    //------------------------------------------------------------------------------
    struct Description
    {
        UINT width;
        UINT height;
        HWND hWnd;
        DXGI_FORMAT fromat;
        DXGI_SWAP_EFFECT swapEffect;
        DXGI_USAGE bufferUsage;
        UINT bufferCount;
        UINT flag;
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// width       ��ʂ̕�
    /// height      ��ʂ̍���
    /// hWnd        ��ʂ̍����E�B���h�E�n���h��
    /// fromat      �`��̃t�H�[�}�b�g
    /// swapEffect  �o�b�O�o�b�t�@�̏������@�̃I�v�V����
    /// bufferUsage �o�b�O�o�b�t�@�̎g�p�p�r
    /// bufferCount �o�b�t�@�̐�
    /// flag        �X���b�v�`�F�[���̃I�v�V����
    /// </summary>

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    IGfxSwapChain() {};

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~IGfxSwapChain() {};

    //------------------------------------------------------------------------------
    /// �X���b�v�`�F�[���̐���
    ///
    /// \param[in] desc             �X���b�v�`�F�[���̐ݒ荀��
    /// \param[in] pDevice          �f�o�C�X
    /// \param[in] pRenderCommand   �f�o�C�X�R���e�N�X�g
    /// 
    /// \return �����ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    virtual HRESULT Create(
    /*[in]*/
    const Description& desc,
    /*[in]*/
    IGfxDevice* pDevice,
    /*[in]*/
    IGfxRenderCommand* pRenderCommand) = 0;

    //------------------------------------------------------------------------------
    /// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Present() const = 0;

    //------------------------------------------------------------------------------
};

#endif // __SWAP_CHAIN_H__
