//==============================================================================
// Filename: Gfx_D3D11ConstantBuffer.h
// Description: Direct3D 11�萔�o�b�t�@�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_CONSTANT_BUFER_H__
#define __D3D11_CONSTANT_BUFER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <wrl\client.h>
#include <d3d11.h>

// �N���X��`
class GfxD3D11ConstantBuffer : public GfxConstantBuffer
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] desc �萔�o�b�t�@�̐ݒ荀��
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11ConstantBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11ConstantBuffer();

    void Write(void* pData) final;

    void BindPS(unsigned slot) final;
    void BindVS(unsigned slot) final;

    void Bind(unsigned slot = 0) const final;
    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pBuffer      �萔�o�b�t�@
    /// </summary> 
};
#endif // __D3D11_CONSTANT_BUFER_H__
