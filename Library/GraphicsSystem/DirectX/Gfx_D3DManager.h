//==============================================================================
// Filename: DirectX.h
// Description: DirectX11 or 12 の管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D_MANAGER_H__
#define __D3D_MANAGER_H__

//#define DX12

// インクルード
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

// マクロ定義
#define D3D (GfxD3DManager::GetInstance())

// DirectXMathがDirectXのネームスペースにある
using namespace DirectX;
using namespace std;
// ComPtr(DirectX版のスマートポインタ)
using Microsoft::WRL::ComPtr;

// クラス定義
class GfxD3DManager
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3DManager();

    //------------------------------------------------------------------------------
    /// D3Dの初期化
    ///
    /// \return 初期化処理の成否
    //------------------------------------------------------------------------------
    HRESULT Init(HWND hWnd, UINT width, UINT height);

    //------------------------------------------------------------------------------
    /// インスタンス作成
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void CreateInstance();

    //------------------------------------------------------------------------------
    /// インスタンス取得
    ///
    /// \return クラスのインスタンス
    //------------------------------------------------------------------------------
    static GfxD3DManager* GetInstance();

    //------------------------------------------------------------------------------
    /// インスタンス削除
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void DeleteInstance();

#ifdef DX12
    //------------------------------------------------------------------------------
    /// デバイスの取得
    ///
    /// \return デバイスのポインタ
    //------------------------------------------------------------------------------
    inline ID3D12Device* GetDevice() const
    {
        return m_pDevice.Get();
    }

    //------------------------------------------------------------------------------
    /// スワップチェーンの取得
    ///
    /// \return スワップチェーンのポインタ
    //------------------------------------------------------------------------------
    inline IDXGISwapChain* GetSwapChain() const
    {
        return m_pSwapChain4.Get();
    }

    //------------------------------------------------------------------------------
    /// デバッグレイヤーを有効化する
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EnableDebugLayer();

#else
    //------------------------------------------------------------------------------
    /// デバイスの取得
    ///
    /// \return デバイスのポインタ
    //------------------------------------------------------------------------------
    inline ID3D11Device* GetDevice() const
    {
        return m_pDevice.Get();
    }

    //------------------------------------------------------------------------------
    /// スワップチェーンの取得
    ///
    /// \return スワップチェーンのポインタ
    //------------------------------------------------------------------------------
    inline IDXGISwapChain* GetSwapChain() const
    {
        return m_pSwapChain.Get();
    }

    //------------------------------------------------------------------------------
    /// デバイスコンテキストの取得
    ///
    /// \return デバイスコンテキストのポインタ
    //------------------------------------------------------------------------------
    inline ID3D11DeviceContext* GetDeviceContext() const
    {
        return m_pDeviceContext.Get();
    }
#endif // DX12


    //------------------------------------------------------------------------------
    /// 描画の開始(バックバッファ＆Ｚバッファのクリア)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BeginDraw();

    //------------------------------------------------------------------------------
    /// 描画の修了(バックバッファとフロントバッファの入れ替え)
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
    /// コンストラクタ
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

    ComPtr<ID3D12Resource> m_pVertexBuffer;     // 頂点バッファー
    ComPtr<ID3D12Resource> m_pIndexBuffer;      // インデックスバッファー
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;  // 頂点バッファービュー
    D3D12_INDEX_BUFFER_VIEW indexBufferView;    // 頂点バッファービュー

    ComPtr<ID3D12Resource> m_pVertexBuffer3D;     // 頂点バッファー
    ComPtr<ID3D12Resource> m_pIndexBuffer3D;      // インデックスバッファー
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView3D;  // 頂点バッファービュー
    D3D12_INDEX_BUFFER_VIEW indexBufferView3D;    // 頂点バッファービュー

    ComPtr<ID3DBlob> m_pVSBlob;                     // 頂点シェーダー
    ComPtr<ID3DBlob> m_pPSBlob;                     // ピクセルシェーダー
    vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;   // インプットレイアウト
    ComPtr<ID3DBlob> m_pVSBlob3D;                     // 頂点シェーダー
    ComPtr<ID3DBlob> m_pPSBlob3D;                     // ピクセルシェーダー
    vector<D3D12_INPUT_ELEMENT_DESC> inputLayout3D;   // インプットレイアウト

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc;
    ComPtr<ID3D12PipelineState> m_pPipeLineState;   // パイプラインステート
    ComPtr<ID3D12RootSignature> m_pRootSignature;   // ルートシグネチャ
    D3D12_ROOT_PARAMETER m_rootParameters[2];           // ルートパラメータ
    D3D12_STATIC_SAMPLER_DESC m_samplerDesc;         // サンプラーデスク

    D3D12_VIEWPORT viewport;                    // ビューポート
    D3D12_RECT scissorRect;                     // シザー矩形

    ComPtr<ID3D12Resource> m_pTextureBuffer;     // テクスチャバッファー
    ComPtr<ID3D12DescriptorHeap> m_pBasicDescHeap; // テクスチャのディスクリプタヒープ

    ComPtr<ID3D12Resource> m_pDepthBuffer;          // 深度バッファー
    ComPtr<ID3D12DescriptorHeap> m_pDepthDescHeap;  // デプスステンシルのディスクリプタヒープ

    vector<ComPtr<ID3D12Resource>> m_pConstResources;    // 定数バッファのリソース
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice               デバイス
    /// m_pDXGIFactory6         ファクトリー
    /// m_pSwapChain4           スワップチェーン
    /// m_pCommandList          コマンドリスト
    /// m_pCommandAllocator     コマンドアロケーター
    /// m_pCommandQueue         コマンドキュー
    /// m_pDescriptorHeap       ディスクリプタヒープ
    /// m_pFence                フェンス
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
    /// m_pDevice               デバイス
    /// m_pSwapChain            スワップチェーン
    /// m_pDeviceContext        デバイスコンテキスト
    /// ID3D11RenderTargetView  レンダーターゲットビュー
    /// m_pDepthStencilView     デプスステンシルビュー
    /// 
    ///// m_pTexrure2D          2Dテクスチャ
    ///// m_pRasterizerState    ラスタライザステート
    ///// m_pBlendState         アルファブレンディング
    ///// m_pDepthStencilState  デプスステンシルステート
    /// </summary> 
#endif // DX12
};

#endif // __D3D_MANAGER_H__
