//==============================================================================
// Filename: GfxConstantBuffer.h
// Description: �萔�o�b�t�@�N���X
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! �C���N���[�h�K�[�h
#ifndef __CONSTANT_BUFFER_H__
#define __CONSTANT_BUFFER_H__

//! �C���N���[�h
#include <main.h>
#include <d3d11.h>

//! �N���X��`
class GfxConstantBuffer
{
public:
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxConstantBuffer();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxConstantBuffer();

    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�쐬
    /// 
    /// \param[in] size �萔�o�b�t�@�̑傫��
    ///
    /// \return �萔�o�b�t�@�쐬�̐���
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    UINT size);

    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�ւ̏�������
    /// 
    /// \param[in] pData �萔�o�b�t�@�̃f�[�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Write(
    /*[in]*/
    const void* pData);

    //------------------------------------------------------------------------------
    /// ���_�V�F�[�_�[�̎w�肵���X���b�g�ɒ萔�o�b�t�@�̃f�[�^�𑗂�
    /// 
    /// \param[in] slot �X���b�g
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(UINT slot);

    //------------------------------------------------------------------------------
    /// �s�N�Z���V�F�[�_�[�̎w�肵���X���b�g�ɒ萔�o�b�t�@�̃f�[�^�𑗂�
    /// 
    /// \param[in] slot �X���b�g
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(UINT slot);

private:
    //---------------------------------------------------------------------------
    ID3D11Buffer* m_pBuffer;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pBuffer �萔�o�b�t�@�̃|�C���^
    /// </summary> 
};

#endif // __CONSTANT_BUFFER_H__