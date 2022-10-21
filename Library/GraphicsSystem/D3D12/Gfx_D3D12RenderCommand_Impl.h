//==============================================================================
// Filename: Gfx_D3D12RenderCommand_Impl.h
// Description: Direct3D 12�̕`�施�߃N���X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_RENDER_COMMAND_H__
#define __D3D12_RENDER_COMMAND_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_RenderCommand.h>    // �p��
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>     // �t�����h�֐��p
#include <wrl\client.h> //COM�|�C���^
#include <d3d12.h>      


// �N���X��`
class GfxD3D12RenderCommand : public IGfxRenderCommand
{
    friend HRESULT DeviceFactory::CreateDeviceAndContext(
        int apiKind,
        std::shared_ptr<IGfxDevice>& pDevice,
        std::shared_ptr<IGfxRenderCommand>& pRenderCommand);

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12RenderCommand();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12RenderCommand();

    //------------------------------------------------------------------------------
    /// �o�b�N�o�b�t�@�̃N���A
    ///
    /// \param[in] pRenderTagetView �����_�[�^�[�Q�b�g
    /// \param[in] clearColor       �N���A����F
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearRenderTargetView(
    /*[in]*/
    IGfxRenderTarget* pRenderTargetView,
    /*[in]*/
    const float clearColor[4]) const final;

    //------------------------------------------------------------------------------
    /// Z�o�b�t�@�̃N���A
    ///
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void ClearDepthStencilView(
    /*[in]*/
    IGfxDepthStencil* DepthStencilView) const final;

    //------------------------------------------------------------------------------
    /// �����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[�̎w��
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    /// 
    /// \param[in] pRenderTagetView     �����_�[�^�[�Q�b�g�r���[
    /// \param[in] pDepthStencilView    �f�v�X�X�e���V���r���[
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void OMSetRenderTargets(
    /*[in]*/
    IGfxRenderTarget* pRenderTargetView,
    /*[in]*/
    IGfxDepthStencil* pDepthStencilView) final;

    //------------------------------------------------------------------------------
    /// �`��I�����߁i�o�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ��j
    /// DX12�̏ꍇ�@���\�[�X�o���A�̐ݒ�������ōs���Ă���
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw() final;

    //------------------------------------------------------------------------------
    /// �R�}���h���X�g�̎擾
    ///
    /// \return �R�}���h���X�g
    //------------------------------------------------------------------------------
    ID3D12GraphicsCommandList* GetCommadList() const
    {
        return m_pCommandList.Get();
    }
    //------------------------------------------------------------------------------
    /// �R�}���h�A���P�[�^�[�̎擾
    ///
    /// \return �R�}���h�A���P�[�^�[
    //------------------------------------------------------------------------------
    ID3D12CommandAllocator* GetCommadAllocator() const
    {
        return m_pCommandAllocator.Get();
    }

    //------------------------------------------------------------------------------
    /// �R�}���h�L���[�̎擾
    ///
    /// \return �R�}���h�L���[
    //------------------------------------------------------------------------------
    ID3D12CommandQueue* GetCommadQueue() const
    {
        return m_pCommandQueue.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>   m_pCommandList;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator>      m_pCommandAllocator;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue>          m_pCommandQueue;
    Microsoft::WRL::ComPtr<ID3D12Fence>                 m_pFence;
    D3D12_RESOURCE_BARRIER                              m_barrierDesc;
    UINT64                                              m_fenceValue;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pCommandList      �R�}���h���X�g
    /// m_pCommandAllocator �A���P�[�^�[
    /// m_pCommandQueue     �R�}���h�L���[
    /// m_pCommandList      �R�}���h���X�g
    /// </summary> 
};
#endif // __D3D12_RENDER_COMMAND_H__
