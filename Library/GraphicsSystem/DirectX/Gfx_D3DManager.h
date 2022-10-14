//==============================================================================
// Filename: DirectX.h
// Description: DirectX11 or 12 �̊Ǘ��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D_MANAGER_H__
#define __D3D_MANAGER_H__

//#define DX12

// �C���N���[�h
#ifdef DX12
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")
#else
#include <d3d11_1.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment (lib, "d3d10_1.lib")
#pragma comment (lib, "dxgi.lib")
#endif // DX12

#include <directxcolors.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>

// �}�N����`
#define D3D (GfxD3DManager::GetInstance())

// DirectXMath��DirectX�̃l�[���X�y�[�X�ɂ���
using namespace DirectX;
using namespace std;
// ComPtr(DirectX�ł̃X�}�[�g�|�C���^)
using Microsoft::WRL::ComPtr;

// �N���X��`
class GfxD3DManager
{
public:
    //------------------------------------------------------------------------------

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

#ifdef DX12
    //------------------------------------------------------------------------------
    /// �f�o�C�X�̎擾
    ///
    /// \return �f�o�C�X�̃|�C���^
    //------------------------------------------------------------------------------
    inline ID3D12Device* GetDevice() const
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
        return m_pSwapChain4.Get();
    }

    //------------------------------------------------------------------------------
    /// �f�o�b�O���C���[��L��������
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EnableDebugLayer();

#else
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
#endif // DX12


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

#ifdef DX12
    HRESULT CreateShader();
    HRESULT CreatePipeline();
    void TestDraw();
#endif // DX12


    //------------------------------------------------------------------------------

private:

    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3DManager();
    
    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
#ifdef DX12
    //------------------------------------------------------------------------------
    static GfxD3DManager* m_pInstance;
    ComPtr<ID3D12Device>                m_pDevice;
    ComPtr<IDXGIFactory6>               m_pDXGIFactory6;
    ComPtr<IDXGISwapChain4>             m_pSwapChain4;
    ComPtr<ID3D12GraphicsCommandList>   m_pCommandList;
    ComPtr<ID3D12CommandAllocator>      m_pCommandAllocator;
    ComPtr<ID3D12CommandQueue>          m_pCommandQueue;
    ComPtr<ID3D12DescriptorHeap>        m_pDescriptorHeap;
    ComPtr<ID3D12Fence>                 m_pFence;

    std::vector<ComPtr<ID3D12Resource>> m_pBackBuffers;
    D3D12_RESOURCE_BARRIER m_pBarrierDesc;
    UINT64 m_fenceValue;

    ComPtr<ID3D12Resource> m_pVertexBuffer;     // ���_�o�b�t�@�[
    ComPtr<ID3D12Resource> m_pIndexBuffer;      // �C���f�b�N�X�o�b�t�@�[
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;  // ���_�o�b�t�@�[�r���[
    D3D12_INDEX_BUFFER_VIEW indexBufferView;    // ���_�o�b�t�@�[�r���[

    ComPtr<ID3D12Resource> m_pVertexBuffer3D;     // ���_�o�b�t�@�[
    ComPtr<ID3D12Resource> m_pIndexBuffer3D;      // �C���f�b�N�X�o�b�t�@�[
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView3D;  // ���_�o�b�t�@�[�r���[
    D3D12_INDEX_BUFFER_VIEW indexBufferView3D;    // ���_�o�b�t�@�[�r���[

    ComPtr<ID3DBlob> m_pVSBlob;                     // ���_�V�F�[�_�[
    ComPtr<ID3DBlob> m_pPSBlob;                     // �s�N�Z���V�F�[�_�[
    vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;   // �C���v�b�g���C�A�E�g
    ComPtr<ID3DBlob> m_pVSBlob3D;                     // ���_�V�F�[�_�[
    ComPtr<ID3DBlob> m_pPSBlob3D;                     // �s�N�Z���V�F�[�_�[
    vector<D3D12_INPUT_ELEMENT_DESC> inputLayout3D;   // �C���v�b�g���C�A�E�g

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc;
    ComPtr<ID3D12PipelineState> m_pPipeLineState;   // �p�C�v���C���X�e�[�g
    ComPtr<ID3D12RootSignature> m_pRootSignature;   // ���[�g�V�O�l�`��
    D3D12_ROOT_PARAMETER m_rootParameters[2];           // ���[�g�p�����[�^
    D3D12_STATIC_SAMPLER_DESC m_samplerDesc;         // �T���v���[�f�X�N

    D3D12_VIEWPORT viewport;                    // �r���[�|�[�g
    D3D12_RECT scissorRect;                     // �V�U�[��`

    ComPtr<ID3D12Resource> m_pTextureBuffer;     // �e�N�X�`���o�b�t�@�[
    ComPtr<ID3D12DescriptorHeap> m_pBasicDescHeap; // �e�N�X�`���̃f�B�X�N���v�^�q�[�v

    ComPtr<ID3D12Resource> m_pDepthBuffer;          // �[�x�o�b�t�@�[
    ComPtr<ID3D12DescriptorHeap> m_pDepthDescHeap;  // �f�v�X�X�e���V���̃f�B�X�N���v�^�q�[�v

    vector<ComPtr<ID3D12Resource>> m_pConstResources;    // �萔�o�b�t�@�̃��\�[�X
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice               �f�o�C�X
    /// m_pDXGIFactory6         �t�@�N�g���[
    /// m_pSwapChain4           �X���b�v�`�F�[��
    /// m_pCommandList          �R�}���h���X�g
    /// m_pCommandAllocator     �R�}���h�A���P�[�^�[
    /// m_pCommandQueue         �R�}���h�L���[
    /// m_pDescriptorHeap       �f�B�X�N���v�^�q�[�v
    /// m_pFence                �t�F���X
    /// </summary> 
#else
    //------------------------------------------------------------------------------
    static GfxD3DManager* m_pInstance;
    ComPtr<ID3D11Device>  m_pDevice;
    ComPtr<IDXGISwapChain>  m_pSwapChain;
    ComPtr<ID3D11DeviceContext> m_pDeviceContext;
    ComPtr<ID3D11RenderTargetView>  m_pRentderTarget;
    ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
    //ComPtr<ID3D11Texture2D> m_pTexrure2D ;
    //ComPtr<ID3D11RasterizerState> m_pRasterizerState;
    //ComPtr<ID3D11BlendState>  m_pBlendState;
    //ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice               �f�o�C�X
    /// m_pSwapChain            �X���b�v�`�F�[��
    /// m_pDeviceContext        �f�o�C�X�R���e�L�X�g
    /// ID3D11RenderTargetView  �����_�[�^�[�Q�b�g�r���[
    /// m_pDepthStencilView     �f�v�X�X�e���V���r���[
    /// 
    ///// m_pTexrure2D          2D�e�N�X�`��
    ///// m_pRasterizerState    ���X�^���C�U�X�e�[�g
    ///// m_pBlendState         �A���t�@�u�����f�B���O
    ///// m_pDepthStencilState  �f�v�X�X�e���V���X�e�[�g
    /// </summary> 
#endif // DX12
};

#endif // __D3D_MANAGER_H__
