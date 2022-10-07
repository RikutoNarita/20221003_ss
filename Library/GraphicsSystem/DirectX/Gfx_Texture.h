//==============================================================================
// Filename: Gfx_Texture.h
// Description: �e�N�X�`���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// �C���N���[�h
#include  <Win_Main.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <dxgi.h>
#include <d2d1.h>
#include <d2d1_1.h>

// �N���X��`
class GfxTexture
{
public:
    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxTexture();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxTexture();

    //------------------------------------------------------------------------------
    /// �T���v���[�̏�����
    ///
    /// \return �������̐���
    //------------------------------------------------------------------------------
    HRESULT Init();

    //------------------------------------------------------------------------------
    /// ID3D11Texture11 or 12 ����V�F�[�_�[���\�[�X�r���[���쐬����
    ///
    /// \return �쐬�̐���
    //------------------------------------------------------------------------------
    HRESULT CreateShaderResourceFromTexture2D();

    //------------------------------------------------------------------------------
    /// �V�F�[�_�[���\�[�X���s�N�Z���V�F�[�_�[�ɓn��
    ///
    /// \param[in] slot �X���b�g
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void SetTexturePS(
    /*[in]*/
    UINT slot);

    //------------------------------------------------------------------------------
    /// �V�F�[�_�[���\�[�X�𒸓_�V�F�[�_�[�ɓn��
    ///
    /// \param[in] slot �X���b�g
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void SetTextureVS(
    /*[in]*/
    UINT slot);

    //------------------------------------------------------------------------------
    /// �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
    ///
    /// \param[in] slot �X���b�g
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void SetSamplerPS(
    /*[in]*/
    UINT slot);

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
    ID3D11SamplerState* m_pSamplerState;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pTexture2D  �e�N�X�`��
    /// m_pShaderResourceView �V�F�[�_�[���\�[�X
    /// m_pSamplerState �T���v���[
    /// </summary> 
};

#endif //! __TEXTURE_H__