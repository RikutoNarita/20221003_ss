//==============================================================================
// Filename: Gfx_GraphicsManager.h
// Description: OpenGL�̕`��Ǘ��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __OPEN_GL_MANAGER_H__
#define __OPEN_GL_MANAGER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\IGfx_Graphics.h>

#include <memory>

// �}�N����`
#define GL    (GfxOpenGL::GetInstance()) // �N���X�̃C���X�^���X��Ԃ�

// �N���X��`
class GfxOpenGL : public IGfxGraphics
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxOpenGL();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxOpenGL();

    //------------------------------------------------------------------------------
    /// �O���t�B�b�N�XAPI�̏�����
    ///
    /// \param[in] width    �E�B���h�E�̕�
    /// \param[in] height   �E�B���h�E�̍���
    ///
    /// \return �����������̐���
    //------------------------------------------------------------------------------
    void Init(int width, int height) override;

    //------------------------------------------------------------------------------
    /// �O���t�B�b�N�XAPI�̏I������
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Uninit() override;

    //------------------------------------------------------------------------------
    /// �`��̊J�n(�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BeginDraw() override;

    //------------------------------------------------------------------------------
    /// �`��̏C��(�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw() override;

    static GfxOpenGL* GetInstance()
    {
        return dynamic_cast<GfxOpenGL*>(m_pGraphics.get());
    }

    //------------------------------------------------------------------------------
private:
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
    /// <summary>
    /// </summary> 
    
public:
    //template <typename T>
    //T* GetDevice()
    //{
    //    return *T;
    //}
    //template <>
    //ID3D12Device* GetDevice<ID3D12Device>()
    //{
    //    return dynamic_cast<GfxD3D12Device*>(m_pDevice.get())->GetDevice();
    //}
    //
    //template <>
    //ID3D11Device* GetDevice<ID3D11Device>()
    //{
    //    return dynamic_cast<GfxD3D11Device*>(m_pDevice.get())->GetDevice();
    //}
    //
    //template <typename T>
    //T* GetRenderCommand()
    //{
    //    return *T;
    //}
    //template <>
    //ID3D11DeviceContext* GetRenderCommand<ID3D11DeviceContext>()
    //{
    //    return dynamic_cast<GfxD3D11RenderCommand*>(m_pRenderCommand.get())->GetDeviceContext();
    //}
    //template <>
    //ID3D12GraphicsCommandList* GetRenderCommand<ID3D12GraphicsCommandList>()
    //{
    //    return dynamic_cast<GfxD3D12RenderCommand*>(m_pRenderCommand.get())->GetCommadList();
    //}
    //
    //template <typename T>
    //T* GetSwapChain()
    //{
    //    return *T;
    //}
    //template <>
    //IDXGISwapChain* GetSwapChain<IDXGISwapChain>()
    //{
    //    return dynamic_cast<GfxD3D11SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    //}
    //template <>
    //IDXGISwapChain4* GetSwapChain<IDXGISwapChain4>()
    //{
    //    return dynamic_cast<GfxD3D12SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    //}

};
#endif // __D3D_MANAGER_H__
