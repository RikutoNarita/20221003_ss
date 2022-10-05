//==============================================================================
// Filename: DirectX.h
// Description: DirectX11 or 12 �̊Ǘ��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! �C���N���[�h�K�[�h
#ifndef __D3D_MANAGER_H__
#define __D3D_MANAGER_H__

#if 1
//! �C���N���[�h
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>

//! �}�N����`
#define D3D (GfxD3DManager::GetInstance())

//! DirectXMath��DirectX�̃l�[���X�y�[�X�ɂ���
using namespace DirectX;
using namespace std;
//! ComPtr(DirectX�ł̃X�}�[�g�|�C���^)
using Microsoft::WRL::ComPtr;

//! �N���X��`
class GfxD3DManager
{
public:
    //---------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3DManager();

    //------------------------------------------------------------------------------
    /// D3D�̏�����
    ///
    /// \return �����������̐���
    //------------------------------------------------------------------------------
    HRESULT Init(HWND hWnd, UINT width, UINT height);

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
    static GfxD3DManager* GetInstance();

    //------------------------------------------------------------------------------
    /// �C���X�^���X�폜
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void DeleteInstance();


    //------------------------------------------------------------------------------
    /// �f�o�C�X�̎擾
    ///
    /// \return �f�o�C�X�̃|�C���^
    //------------------------------------------------------------------------------
    inline ID3D11Device* GetDevice() const
    {
        return m_pDevice.Get();
    }
   
    //------------------------------------------------------------------------------
    /// �X���b�v�`�F�[���̎擾
    ///
    /// \return �X���b�v�`�F�[���̃|�C���^
    //------------------------------------------------------------------------------
    inline IDXGISwapChain* GetSwapChain() const
    {
        return m_pSwapChain.Get();
    }

    //------------------------------------------------------------------------------
    /// �f�o�C�X�R���e�L�X�g�̎擾
    ///
    /// \return �f�o�C�X�R���e�L�X�g�̃|�C���^
    //------------------------------------------------------------------------------
    inline ID3D11DeviceContext* GetDeviceContext() const
    {
        return m_pDeviceContext.Get();
    }

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

    //---------------------------------------------------------------------------

private:

    //---------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3DManager();
    
    //---------------------------------------------------------------------------
    
    //---------------------------------------------------------------------------
    static GfxD3DManager* m_pInstance;
    ComPtr<ID3D11Device>            m_pDevice;
    ComPtr<IDXGISwapChain>          m_pSwapChain;
    ComPtr<ID3D11DeviceContext>     m_pDeviceContext;
    ComPtr<ID3D11RenderTargetView>  m_pRentderTarget;
    //ComPtr<ID3D11Texture2D>         m_pTexrure2D ;
    //ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
    //ComPtr<ID3D11RasterizerState>   m_pRasterizerState;
    //ComPtr<ID3D11BlendState>        m_pBlendState;
    //ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice               �f�o�C�X
    /// m_pSwapChain            �X���b�v�`�F�[��
    /// m_pDeviceContext        �f�o�C�X�R���e�L�X�g
    /// m_pTexrure2D            2D�e�N�X�`��
    /// ID3D11RenderTargetView  �����_�[�^�[�Q�b�g�r���[
    /// m_pDepthStencilView     �f�v�X�X�e���V���r���[
    /// m_pRasterizerState      ���X�^���C�U�X�e�[�g
    /// m_pBlendState           �A���t�@�u�����f�B���O
    /// m_pDepthStencilState    �f�v�X�X�e���V���X�e�[�g
    /// </summary> 
};

#else

//! �񋓑̒�`
//enum EBlendState {
//    BS_NONE = 0,          //! ��������������
//    BS_ALPHABLEND,        //! ����������
//    BS_ADDITIVE,          //! ���Z����
//    BS_SUBTRACTION,       //! ���Z����
//
//    MAX_BLENDSTATE
//};
//
//enum ECullMode {
//    CULLMODE_NONE = 0,    //! �J�����O���Ȃ�
//    CULLMODE_CW,          //! �O�ʃJ�����O
//    CULLMODE_CCW,         //! �w�ʃJ�����O
//
//    MAX_CULLMODE
//};
//
////! �v���g�^�C�v�錾
//HRESULT InitDirectX(HWND hWnd, UINT width, UINT height, bool fullscreen);
//
//ID3D11Device* GetDevice();
//IDXGISwapChain* GetSwapChain();
//ID3D11DeviceContext* GetDeviceContext();
//HRESULT CreateBackBuffer();
//void ReleaseBackBuffer();
//void ReleaseDirectX();
//void SetZBuffer(bool bEnable);
//void SetZWrite(bool bEnable);
//void SetBlendState(int nBlendState);
//void SetCullMode(int nCullMode);
//
//void ClearScreen();
//void Swap();

#endif // 0

#endif //! __D3D_MANAGER_H__
