//==============================================================================
// Filename: IGfx_D3D12RenderTarget_Impl.h
// Description: Direct3D 12�̃����_�[�^�[�Q�b�g�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_RENDER_TARGET_H__
#define __D3D12_RENDER_TARGET_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_RenderTarget.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>

// �N���X��`
class GfxD3D12RenderTarget : public IGfxRenderTarget
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12RenderTarget();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12RenderTarget() override;

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�̐���
    ///
    /// \param[in] desc         �ݒ荀��
    /// \param[in] pDevice      �f�o�C�X
    /// \param[in] pSwapChain   �X���b�v�`�F�[��
    /// 
    /// \return �����ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    const Description& desc,
    /*[in]*/
    IGfxDevice* pDevice,
    /*[in]*/
    IGfxSwapChain* pSwapChain) final;
   
    //------------------------------------------------------------------------------
    /// �w�肵�������_�[�^�[�Q�b�g�̃o�b�t�@�̎擾
    ///
    /// \param[in] index   �C���f�b�N�X
    /// 
    /// \return �����_�[�^�[�Q�b�g�̃o�b�t�@
    //------------------------------------------------------------------------------
    ID3D12Resource* GetResorces(int index)
    {
        return m_pBufferList[index].Get();
    }

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�r���[�f�B�X�N���v�^�q�[�v�̎擾
    ///
    /// \return �����_�[�^�[�Q�b�g�r���[�f�B�X�N���v�^�q�[�v
    //------------------------------------------------------------------------------
    ID3D12DescriptorHeap* GetDescriptorHeap()
    {
        return m_pDescriptorHeap.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pDescriptorHeap;
    std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> m_pBufferList;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDescriptorHeap   �����_�[�^�[�Q�b�g�̃f�X�N���v�^�[�q�[�v
    /// m_pBufferList       �����_�[�^�[�Q�b�g�̃o�b�t�@
    /// </summary>

};
#endif // __D3D12_RENDER_TARGET_H__
