//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 11�e�N�X�`���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_TEXTURE_H__
#define __D3D11_TEXTURE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <d3d11.h>
#include <wrl\client.h>

// �N���X��`
class GfxD3D11Texture : public GfxTexture
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] desc �e�N�X�`���̐ݒ荀��
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11Texture(
        /*[in]*/
        Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11Texture();

    //------------------------------------------------------------------------------
    /// �e�N�X�`���𒸓_�V�F�[�_�[�ɃZ�b�g����
    ///
    /// \param[in] slot ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(unsigned slot = 0) const;

    //------------------------------------------------------------------------------
    /// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɃZ�b�g����
    ///
    /// \param[in] slot ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(unsigned slot = 0) const;

    void Bind(unsigned slot = 0) const final;

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pTexture2D            �e�N�X�`��2D
    /// m_pShaderResourceView   �e�N�X�`�����\�[�X�r���[
    /// m_pSamplerState         �T���v���[
    /// </summary> 
};
#endif // __TEXTURE_H__
