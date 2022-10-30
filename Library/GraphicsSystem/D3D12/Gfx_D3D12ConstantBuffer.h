//==============================================================================
// Filename: Gfx_D3D12ConstantBuffer.h
// Description: Direct3D 12�萔�o�b�t�@�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_CONSTANT_BUFER_H__
#define __D3D12_CONSTANT_BUFER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <wrl\client.h>
#include <d3d12.h>

// �N���X��`
class GfxD3D12ConstantBuffer : public GfxConstantBuffer
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
    GfxD3D12ConstantBuffer(
    /*[in]*/
    Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12ConstantBuffer();

    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�̍X�V
    ///
    /// \param[in] pData �萔�o�b�t�@�̃f�[�^
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Write(
    /*[in]*/
    void* pData) final;
    
    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�f�[�^�̎擾
    ///
    /// \return �萔�o�b�t�@�f�[�^�̃|�C���^
    //------------------------------------------------------------------------------
    inline ID3D12Resource* Get() const
    {
        return m_pConstantBuffer.Get();
    }

    void BindPS(unsigned slot) final;
    void BindVS(unsigned slot) final;
    void Bind(unsigned slot = 0) const final;

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Resource> m_pConstantBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pConstantBuffer      �萔�o�b�t�@
    /// </summary> 
};
#endif // __D3D12_CONSTANT_BUFER_H__
