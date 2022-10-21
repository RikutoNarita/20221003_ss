//==============================================================================
// Filename: Gfx_GraphicsManager.h
// Description: Direct3D 11, Direct3D 12�̒��ۉ����C���[
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

// �C���N���[�h
#include <Win_Main.h>
#include <GraphicsSystem\Interface\IGfx_Device.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Device_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11RenderCommand_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderCommand_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11SwapChain_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12SwapChain_Impl.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11RenderTarget_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RenderTarget_Impl.h>


#include <memory>

// �}�N����`
#define GRAPHICS    (GfxGraphicsManager::GetInstance()) // �N���X�̃C���X�^���X��Ԃ�

// �O���錾
class IGfxSwapChain;        // �X���b�v�`�F�[��
class IGfxRenderCommand;    // �`�施��
class IGfxRenderTarget;     // �����_�[�^�[�Q�b�g�r���[
class IGfxDepthStencil;     // �f�v�X�X�e���V���r���[
class IGfxViewPort;         // �r���[�|�[�g
class IGfxScissorRect;      // �V�U�[��`

// �N���X��`
class GfxGraphicsManager
{
public:
    //------------------------------------------------------------------------------
    enum class API_KIND
    {
        DIRECT3D_11,
        DIRECT3D_12,
        OPEN_GL,
        VULKAN,
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// �O���t�B�b�N�XAPI�̎�ނ̗񋓑�
    /// </summary>
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxGraphicsManager();

    //------------------------------------------------------------------------------
    /// �O���t�B�b�N�XAPI�̏�����
    ///
    /// \param[in] type     API�̎��
    /// \param[in] hWnd     �E�B���h�E�n���h��
    /// \param[in] width    �E�B���h�E�̕�
    /// \param[in] height   �E�B���h�E�̍���
    ///
    /// \return �����������̐���
    //------------------------------------------------------------------------------
    HRESULT Init(
        /*[in]*/
        API_KIND type,
        /*[in]*/
        HWND hWnd,
        /*[in]*/
        UINT width,
        /*[in]*/
        UINT height);

    //------------------------------------------------------------------------------
    /// �O���t�B�b�N�XAPI�̏I������
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Uninit();

    //------------------------------------------------------------------------------
    /// �C���X�^���X�쐬
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void CreateInstance();

    //------------------------------------------------------------------------------
    /// �C���X�^���X�擾
    ///
    /// \return �N���X�̃C���X�^���X
    //------------------------------------------------------------------------------
    static GfxGraphicsManager* GetInstance();

    //------------------------------------------------------------------------------
    /// �C���X�^���X�폜
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void DeleteInstance();

    //------------------------------------------------------------------------------
    /// �`��̊J�n(�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BeginDraw();

    //------------------------------------------------------------------------------
    /// �`��̏C��(�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw();

    //------------------------------------------------------------------------------

private:

    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxGraphicsManager();
    
    //------------------------------------------------------------------------------
    

    //------------------------------------------------------------------------------
    static GfxGraphicsManager*          m_pInstance;
    API_KIND                            m_eAPIKind;
    std::shared_ptr<IGfxDevice>         m_pDevice;
    std::shared_ptr<IGfxRenderCommand>  m_pRenderCommand;
    std::shared_ptr<IGfxSwapChain>      m_pSwapChain;
    std::shared_ptr<IGfxRenderTarget>   m_pRenderTarget;
    std::shared_ptr<IGfxDepthStencil>   m_DepthStencil;
    std::shared_ptr<IGfxViewPort>       m_viewPort;
    std::shared_ptr<IGfxScissorRect>    m_scissorRect;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pInstance         �N���X�̃C���X�^���X
    /// m_eAPIKind          API�̎��
    /// m_pDevice           �f�o�C�X�C���^�[�t�F�[�X
    /// m_pRenderCommand    �`��C���^�[�t�F�[�X
    /// m_pSwapChain        �X���b�v�`�F�[���̃C���^�[�t�F�[�X
    /// m_pRenderTarget     �����_�[�^�[�Q�b�g�̃C���^�[�t�F�[�X
    /// m_DepthStencil      �f�v�X�X�e���V���̃C���^�[�t�F�[�X
    /// m_viewPort          �r���[�|�[�g�̃C���^�[�t�F�[�X
    /// m_scissorRect       �V�U�[��`�̃C���^�[�t�F�[�X
    /// </summary> 
    
public:
    template <typename T>
    T* GetDevice()
    {
        return *T;
    }
    template <>
    ID3D12Device* GetDevice<ID3D12Device>()
    {
        return dynamic_cast<GfxD3D12Device*>(m_pDevice.get())->GetDevice();
    }
    
    template <>
    ID3D11Device* GetDevice<ID3D11Device>()
    {
        return dynamic_cast<GfxD3D11Device*>(m_pDevice.get())->GetDevice();
    }

    template <typename T>
    T* GetRenderCommand()
    {
        return *T;
    }
    template <>
    ID3D11DeviceContext* GetRenderCommand<ID3D11DeviceContext>()
    {
        return dynamic_cast<GfxD3D11RenderCommand*>(m_pRenderCommand.get())->GetDeviceContext();
    }
    template <>
    ID3D12GraphicsCommandList* GetRenderCommand<ID3D12GraphicsCommandList>()
    {
        return dynamic_cast<GfxD3D12RenderCommand*>(m_pRenderCommand.get())->GetCommadList();
    }

    template <typename T>
    T* GetSwapChain()
    {
        return *T;
    }
    template <>
    IDXGISwapChain* GetSwapChain<IDXGISwapChain>()
    {
        return dynamic_cast<GfxD3D11SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    }
    template <>
    IDXGISwapChain4* GetSwapChain<IDXGISwapChain4>()
    {
        return dynamic_cast<GfxD3D12SwapChain*>(m_pSwapChain.get())->GetSwapChain();
    }

};
#endif // __D3D_MANAGER_H__
