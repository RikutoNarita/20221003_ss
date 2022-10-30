//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 12�e�N�X�`���N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_TEXTURE_H__
#define __D3D12_TEXTURE_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <d3d12.h>
#include <wrl\client.h>

// �N���X��`
class GfxD3D12Texture : public GfxTexture
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
    GfxD3D12Texture(
        /*[in]*/
        Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12Texture();

    //------------------------------------------------------------------------------
    /// �e�N�X�`���o�b�t�@�̎擾
    ///
    /// \return �e�N�X�`���o�b�t�@�̃|�C���^
    //------------------------------------------------------------------------------
    inline ID3D12Resource* Get() const
    {
        return m_pTextureBuffer.Get();
    }

    void Bind(unsigned slot = 0) const final;

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Resource> m_pTextureBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pTextureBuffer    �e�N�X�`���o�b�t�@
    /// </summary> 
};
#endif // __TEXTURE_H__
