//==============================================================================
// Filename: IGfx_RenderTarget.h
// Description: �����_�[�^�[�Q�b�g�̃C���^�[�t�F�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__

// �C���N���[�h
#include <Windows.h>
#include <dxgi.h>

// �O���錾
class IGfxDevice;
class IGfxSwapChain;

// �N���X��`
class IGfxRenderTarget
{
public:
    //------------------------------------------------------------------------------
    struct Description
    {
        DXGI_FORMAT fromat;
        UINT bufferCount;
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// fromat      �`��̃t�H�[�}�b�g
    /// bufferCount �o�b�t�@�̐�
    /// </summary>

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    IGfxRenderTarget() {};

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~IGfxRenderTarget() {};

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�̐���
    ///
    /// \param[in] desc         �ݒ荀��
    /// \param[in] pDevice      �f�o�C�X
    /// \param[in] pSwapChain   �X���b�v�`�F�[��
    /// 
    /// \return �����ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    virtual HRESULT Create(
    /*[in]*/
    const Description& desc,
    /*[in]*/
    IGfxDevice* pDevice,
    /*[in]*/
    IGfxSwapChain* pSwapChain) = 0;

    //------------------------------------------------------------------------------
};
#endif // __RENDER_TARGET_H__