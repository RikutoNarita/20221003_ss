//==============================================================================
// Filename: DirectX.cpp
// Description: DirectX11 or 12 の管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem/D3D12/Gfx_D3DManager.h>
#include <Win_Main.h>
#include <functional>
#include <iostream>
#include <iterator>

#define ASPECT_RATE     (16.0f / 9.0f)  // アスペクト比
#define NEAR_CLIP       (0.1f)          // ニアクリップ
#define FAR_CLIP        (100.0f)        // ファークリップ
#define FOV             (60.0f)         // 画角

// 静的メンバ変数宣言
GfxD3DManager* GfxD3DManager::m_pInstance = nullptr;


DirectX::XMFLOAT4 g_light;
DirectX::XMFLOAT3 g_cameraPos;
float g_fAngle;
float g_fDir;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3DManager::GfxD3DManager()
    : m_fenceValue(0)
{
    m_pBarrierDesc = {};
    vertexBufferView = {};
    vertexBufferView3D = {};
    indexBufferView = {};
    indexBufferView3D = {};
    viewport = {};
    scissorRect = {};
    m_rootParameters[0] = {};
    m_rootParameters[1] = {};
    m_samplerDesc = {};
    pipelineDesc = {};
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3DManager::~GfxD3DManager()
{
}

//------------------------------------------------------------------------------
/// インスタンス作成
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3DManager::CreateInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new GfxD3DManager();
    }
}

//------------------------------------------------------------------------------
/// インスタンス取得
///
/// \return クラスのインスタンス
//------------------------------------------------------------------------------
GfxD3DManager* GfxD3DManager::GetInstance()
{
    return m_pInstance;
}

//------------------------------------------------------------------------------
/// インスタンス削除
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3DManager::DeleteInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
    }
}

//------------------------------------------------------------------------------
/// D3Dの初期化
///
/// \return 初期化処理の成否
//------------------------------------------------------------------------------
HRESULT GfxD3DManager::Init(HWND hWnd, UINT width, UINT height)
{
    HRESULT hr = S_OK;

#ifdef DX12
    
#ifdef _DEBUG
    // デバッグレイヤーを有効にする
    EnableDebugLayer();
#endif // _DEBUG


    // デバイスの生成
    D3D_FEATURE_LEVEL levels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_12_1,
    };
    for (auto lv : levels)
    {
        // 生成可能なバージョンが見つかったらループ終了
        hr = D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&m_pDevice));
        if (FAILED(hr))
            continue;
        else
            break;
    }
    if(FAILED(hr))
    {
        return hr;
    }

    // ファクトリーの生成
#ifdef _DEBUG
    if (CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_pDXGIFactory6)) != S_OK)
    {
        return E_FAIL;
    }
#else
    if (CreateDXGIFactory1(IID_PPV_ARGS(&m_pDXGIFactory6)) != S_OK)
    {
        return E_FAIL;
    }
#endif // _DEBUG

    // コマンドアロケーターの生成
    hr = m_pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pCommandAllocator));
    if(FAILED(hr))
    {
        return hr;
    }

    // コマンドリストの生成
    hr = m_pDevice->CreateCommandList(
        0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_pCommandAllocator.Get(), nullptr,
        IID_PPV_ARGS(&m_pCommandList));
    if (FAILED(hr))
    {
        return hr;
    }

    // コマンドキューの設定
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;            // タイムアウトなし
    queueDesc.NodeMask = 0;                                     // アダプターを一つしか使わないときは0
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;   // プライオリティは指定なし
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;            // タイプはコマンドリストと合わせる
    // コマンドキューの生成
    hr = m_pDevice->CreateCommandQueue(
        &queueDesc, IID_PPV_ARGS(&m_pCommandQueue));
    if (FAILED(hr))
    {
        return hr;
    }
    
    // スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};                       
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    swapChainDesc.BufferCount = 2;
    // バックバッファーは伸び縮み可能
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    // フリップ後は速やかに破棄
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    // 特に指定なし
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    // ウィンドウ←→フルスクリーン切り替え可能
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // スワップチェーンの生成
    ComPtr<IDXGISwapChain1> swapchain1;
    hr = m_pDXGIFactory6->CreateSwapChainForHwnd(
        m_pCommandQueue.Get(),
        hWnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapchain1);
    if (FAILED(hr)) return hr;
    // SwapChain4 → SwapChain1にする
    swapchain1.As(&m_pSwapChain4);

    // 'レンダーターゲットの'ディスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    /* Type
    *   D3D12_DESCRIPTOR_HEAP_TYPE_RTV          レンダーターゲット
    *   D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV  定数バッファ、シェーダーリソース、コンピュートシェーダー用
    *   D3D12_DESCRIPTOR_HEAP_TYPE_RTV          深度ステンシルビュー
    */
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;         // レンダーターゲットのせっていなのでRTV
    heapDesc.NodeMask = 0;                                  // アダプターを一つしか使わないときは0
    heapDesc.NumDescriptors = 2;                            // フロントバッファとバックバッファで2つ
    /* Flags
    * D3D12_DESCRIPTOR_HEAP_FLAG_NONE           指定なし
    * D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE シェーダー側から参照する必要がある場合
    */
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;       // 指定なし
    // ディスクリプタヒープの作成
    hr = m_pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pDescriptorHeap));
    if(FAILED(hr))
    {
        return hr;
    }
    // スワップチェーンのメモリと紐づける
    m_pBackBuffers.resize(swapChainDesc.BufferCount);
    for (int idx = 0; idx < (signed)swapChainDesc.BufferCount; idx++)
    {
        // 紐づけ
        hr = m_pSwapChain4->GetBuffer(idx, IID_PPV_ARGS(&m_pBackBuffers[idx]));
        if(FAILED(hr))
        {
            return hr;
        }

        D3D12_CPU_DESCRIPTOR_HANDLE hadle;
        hadle = m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
        hadle.ptr += idx * static_cast<unsigned long long>(m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        // レンダーターゲットビューの作成
        m_pDevice->CreateRenderTargetView(m_pBackBuffers[idx].Get(), nullptr, hadle);
    }

    // フェンス(コマンドリストの命令をすべて実行したかを知る役割)の作成
    hr = m_pDevice->CreateFence(m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence));
    if(FAILED(hr))
    {
        return hr;
    }

    if(FAILED(CreateShader())) return hr;

    if(FAILED(CreatePipeline())) return hr;

#else
    //! ファクトリーを作成
    ComPtr<IDXGIFactory> factory;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        return hr;
    }

    // デバイス生成
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;//DirectX11上でDirect2Dを使用するために必要
#ifdef _DEBUG
    // DEBUGビルド時はDirect3Dのデバッグを有効にする
    // (すごく重いが細かいエラーがわかる)
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1, // Direct3D 11.1    ShaderModel 5
        D3D_FEATURE_LEVEL_11_0, // Direct3D 11      ShaderModel 5
        D3D_FEATURE_LEVEL_10_1, // Direct3D 10.1    ShaderModel 4
        D3D_FEATURE_LEVEL_10_0, // Direct3D 10.0    ShaderModel 4
        D3D_FEATURE_LEVEL_9_3,  // Direct3D 9.3     ShaderModel 3
        D3D_FEATURE_LEVEL_9_2,  // Direct3D 9.2     ShaderModel 3
        D3D_FEATURE_LEVEL_9_1,  // Direct3D 9.1     ShaderModel 3
    };
    // デバイスとでデバイスコンテキストを作成
    D3D_FEATURE_LEVEL futureLevel;
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
    creationFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION,
    &m_pDevice, &futureLevel, &m_pDeviceContext);
    if (FAILED(hr))
    {
        return hr;
    }

    // スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
    DXGI_SWAP_CHAIN_DESC scDesc = {};                       // スワップチェーンの設定データ
    scDesc.BufferDesc.Width = width;                        // 画面の幅
    scDesc.BufferDesc.Height = height;                      // 画面の高さ
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // バッファの形式
    scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scDesc.BufferDesc.RefreshRate.Numerator = 0;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.SampleDesc.Count = 1;                            // MSAAは使用しない
    scDesc.SampleDesc.Quality = 0;                          // MSAAは使用しない
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // バッファの使用方法
    scDesc.BufferCount = 2;                                 // バッファの数
    scDesc.OutputWindow = hWnd;
    scDesc.Windowed = TRUE;                                 // ウィンドウモード
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    // スワップチェインの作成
    hr = factory->CreateSwapChain(m_pDevice.Get(), &scDesc, &m_pSwapChain);
    if (FAILED(hr))
    {
        return hr;
    }

    // スワップチェインからバックバッファリソース取得
    ComPtr<ID3D11Texture2D> pBackBuffer;
    hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (FAILED(hr))
    {
        return hr;
    }

    // バックバッファリソース用のRTVを作成
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = scDesc.BufferDesc.Format;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    hr = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_pRentderTarget);
    if (FAILED(hr))
    {
        return hr;
    }

    ComPtr<ID3D11Texture2D> pTexture11;
    //! Zバッファ用テクスチャ生成
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = SCREEN_WIDTH;
    td.Height = SCREEN_HEIGHT;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    hr = m_pDevice->CreateTexture2D(&td, nullptr, &pTexture11);
    if (FAILED(hr)) { return hr; }
    //! Zバッファターゲットビュー生成
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    ZeroMemory(&dsvd, sizeof(dsvd));
    dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    hr = m_pDevice->CreateDepthStencilView(pTexture11.Get(), &dsvd, &m_pDepthStencilView);
    if (FAILED(hr)) { return hr; }

    //! バックバッファをRTとしてセット
    m_pDeviceContext->OMSetRenderTargets(1, m_pRentderTarget.GetAddressOf(), m_pDepthStencilView.Get());

    //! ビューポートの設定
    D3D11_VIEWPORT vp = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };
    m_pDeviceContext->RSSetViewports(1, &vp);
#endif // DX12
    
    return hr;
}

// 頂点情報、ピクセル/頂点シェーダー、頂点レイアウト、テクスチャ
HRESULT GfxD3DManager::CreateShader()
{
    HRESULT hr = S_OK;
#pragma region 定数バッファの値を格納
    // カメラの初期化
    g_fAngle = 1.0f;
    g_cameraPos.x = 10.0f * sinf(g_fAngle);
    g_cameraPos.y = 4.0f;
    g_cameraPos.z = -10.0f * cosf(g_fAngle);
    // ライトの初期化
    g_fDir = -0.7f;
    g_light = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
    g_light.y = -1.0f;
    g_light.x = 1.0f * sinf(g_fDir);
    g_light.z = 1.0f * cosf(g_fDir);
    // 変換行列の設定
    XMFLOAT4X4 matrix[3];
    XMMATRIX workMatrix[3];
    // world
    workMatrix[0] = DirectX::XMMatrixIdentity();
    // view
    workMatrix[1] = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(g_cameraPos.x, g_cameraPos.y, g_cameraPos.z, 0.0f), // カメラ位置
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),   // 注視点
        DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));  // 上方ベクトル
    // projection
    workMatrix[2] = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(FOV),
        ASPECT_RATE,
        NEAR_CLIP,
        FAR_CLIP);
    // 転置行列（シェーダーに渡すため）
    DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(workMatrix[0]));
    DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixTranspose(workMatrix[1]));
    DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixTranspose(workMatrix[2]));
#pragma endregion

#pragma region シェーダーの読み込み-------------------------------------------------

    //--- 2D用のシェーダーの読み込み
    // 頂点シェーダー読み込み
    ComPtr<ID3DBlob> pErrorBlob; // シェーダー読み込みのエラー対応
    hr = D3DCompileFromFile(
        L"Shader/VS_2D.hlsl",                               // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "BasicVS",                                          // エントリーポイント名
        "vs_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pVSBlob,                                         // 頂点シェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス
    if (FAILED(hr)) return hr;
    // ピクセルシェーダー読み込み
    hr = D3DCompileFromFile(
        L"Shader/PS_2D.hlsl",                               // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "BasicPS",                                          // エントリーポイント名
        "ps_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pPSBlob,                                         // ピクセルシェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス 
    if (FAILED(hr)) return hr;
    // 頂点レイアウトの作成
    inputLayout.push_back(
        {// 座標
            "POSITION",                                 // セマンティクス名
            0,                                          // セマンティクスインデックス
            DXGI_FORMAT_R32G32B32_FLOAT,                // フォーマット
            0,                                          // 入力スロットインデックス
            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });
    inputLayout.push_back(
        {
            // テクスチャ座標
            "TEXCOORD",                                 // セマンティクス名
            0,                                          // セマンティクスインデックス
            DXGI_FORMAT_R32G32_FLOAT,                   // フォーマット
            0,                                          // 入力スロットインデックス
            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });

    //--- 3D用のシェーダー読み込み
    // 頂点シェーダーの読み込み
    hr = D3DCompileFromFile(
        L"Shader/VS_3D.hlsl",                               // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "main",                                             // エントリーポイント名
        "vs_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pVSBlob3D,                                         // 頂点シェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス
    if (FAILED(hr)) return hr;

    // ピクセルシェーダーの読み込み
    hr = D3DCompileFromFile(
        L"Shader/PS_Lambert.hlsl",                               // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "main",                                             // エントリーポイント名
        "ps_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pPSBlob3D,                                         // ピクセルシェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス 
    if (FAILED(hr)) return hr;
    // 頂点レイアウトの作成
    inputLayout3D.push_back(
        {// 座標
            "POSITION",                                 // セマンティクス名
            0,                                          // セマンティクスインデックス
            DXGI_FORMAT_R32G32B32_FLOAT,                // フォーマット
            0,                                          // 入力スロットインデックス
            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });
    inputLayout3D.push_back(
        {// 法線
            "NORMAL",                                 // セマンティクス名
                0,                                          // セマンティクスインデックス
                DXGI_FORMAT_R32G32B32_FLOAT,                // フォーマット
                0,                                          // 入力スロットインデックス
                D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
                0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });
    inputLayout3D.push_back(
        {
            // テクスチャ座標
            "TEXCOORD",                                 // セマンティクス名
            0,                                          // セマンティクスインデックス
            DXGI_FORMAT_R32G32_FLOAT,                   // フォーマット
            0,                                          // 入力スロットインデックス
            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });
    inputLayout3D.push_back(
        {
            // 色
            "COLOR",                                // セマンティクス名
            0,                                          // セマンティクスインデックス
            DXGI_FORMAT_R32G32B32A32_FLOAT,             // フォーマット
            0,                                          // 入力スロットインデックス
            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
        });
    
    // ------------------------------------------------------------------------
#pragma endregion

    // ヒープの設定
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD; // CPUからアクセスできる
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

#pragma region 2D頂点バッファの生成-------------------------------------------------
    // 2D頂点バッファの生成---------------------------------------------------------
    struct Vertex
    {
        float pos[3];
        float uv[2];
    };
    Vertex vertices[] =
    {
        {{ -0.5f,  0.5f, 0.0f}, {0.0f, 0.0f}, },
        {{  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f}, },
        {{ -0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, },
        {{  0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}, },
        {{ -0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, },
        {{  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f}, },
    };

    // リソースの設定
    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;   // リソースのタイプ
    resourceDesc.Width = sizeof(vertices);                      // 頂点情報のサイズ
    resourceDesc.Height = 1;                                    // 頂点情報のサイズ(Widthに格納済み)
    resourceDesc.DepthOrArraySize = 1;                          // リソースの配列のサイズ
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;                  // フォーマット指定なし
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;              // オプションなし
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;       // データが行優先順で格納
    // 頂点バッファの生成
    hr = m_pDevice->CreateCommittedResource(
        &heapprop,                              // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                   // 指定なし
        &resourceDesc,                          // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,      // アップロード ヒープに必要な開始状態
        nullptr,
        IID_PPV_ARGS(&m_pVertexBuffer));        // 頂点バッファー
    // 頂点情報をバッファーにコピーする
    Vertex* vertMap = nullptr;
    hr = m_pVertexBuffer->Map(0, nullptr, (void**)&vertMap);
    if (FAILED(hr)) return hr;
    std::copy(std::begin(vertices), std::end(vertices), vertMap);
    m_pVertexBuffer->Unmap(0, nullptr);
    // 頂点バッファービューの生成
    vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.SizeInBytes = sizeof(vertices);        // 全バイト数
    vertexBufferView.StrideInBytes = sizeof(vertices[0]);   // １頂点あたりのバイト数

    unsigned short indices[] =
    {
        0, 1, 2,
        2, 3, 1
    };
    // インデックスバッファーの生成
    hr = m_pDevice->CreateCommittedResource(
        &heapprop,                              // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                   // 指定なし
        &resourceDesc,                          // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,      // アップロード ヒープに必要な開始状態
        nullptr,
        IID_PPV_ARGS(&m_pIndexBuffer));         // インデックスバッファー
    if (FAILED(hr)) return hr;
    // インデックス情報をバッファーにコピーする
    unsigned short* indexMap = nullptr;
    hr = m_pIndexBuffer->Map(0, nullptr, (void**)&indexMap);
    if (FAILED(hr)) return hr;
    std::copy(std::begin(indices), std::end(indices), indexMap);
    m_pIndexBuffer->Unmap(0, nullptr);
    // インデックスバッファービューの生成
    indexBufferView.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
    indexBufferView.Format = DXGI_FORMAT_R16_UINT;    // フォーマット
    indexBufferView.SizeInBytes = sizeof(indices);    // 全バイト数
    //-------------------------------------------------------------------------
#pragma endregion

#pragma region 3D頂点バッファの生成-------------------------------------------------
    // 3D頂点バッファの生成---------------------------------------------------------
    struct Vertex3D
    {
        XMFLOAT3 pos;       // 座標
        XMFLOAT3 normal;    // 法線
        XMFLOAT2 uv;        // uv
        XMFLOAT4 diffuse;   // カラー
    };
    const float side = 1.0f;
    Vertex3D vertices3D[] =
    {
        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    };

    // インデックスバッファの作成
    std::vector<unsigned short> indexList;
    indexList.resize(_countof(vertices3D));
    for (size_t i = 0; i < indexList.size(); i++)
    {
        indexList[i] = (unsigned short)i;
    }
    for (size_t i = 0, Cnt = _countof(vertices3D); i < Cnt; i += 3)
    {
        auto& vtx0 = vertices3D[indexList[i]];
        auto& vtx1 = vertices3D[indexList[i + 1]];
        auto& vtx2 = vertices3D[indexList[i + 2]];

        //外積で法線算出
        DirectX::XMFLOAT3 v1 =
        {
            vtx1.pos.x - vtx0.pos.x, vtx1.pos.y - vtx0.pos.y, vtx1.pos.z - vtx0.pos.z
        };
        DirectX::XMFLOAT3 v2 =
        {
            vtx2.pos.x - vtx0.pos.x, vtx2.pos.y - vtx0.pos.y, vtx2.pos.z - vtx0.pos.z
        };
        const auto n = DirectX::XMVector3Normalize(
            DirectX::XMVector3Cross(
                DirectX::XMLoadFloat3(&v1), DirectX::XMLoadFloat3(&v2)));
        //データ格納
        DirectX::XMStoreFloat3(&vertices3D[i].normal, n);
        DirectX::XMStoreFloat3(&vertices3D[i + 1].normal, n);
        DirectX::XMStoreFloat3(&vertices3D[i + 2].normal, n);
    }
    // リソースの設定
    D3D12_RESOURCE_DESC resourceDesc3D = {};
    resourceDesc3D.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // リソースのタイプ
    resourceDesc3D.Width = sizeof(vertices3D);                  // 頂点情報のサイズ
    resourceDesc3D.Height = 1;                                  // 頂点情報のサイズ(Widthに格納済み)
    resourceDesc3D.DepthOrArraySize = 1;                        // リソースの配列のサイズ
    resourceDesc3D.MipLevels = 1;
    resourceDesc3D.Format = DXGI_FORMAT_UNKNOWN;                // フォーマット指定なし
    resourceDesc3D.SampleDesc.Count = 1;
    resourceDesc3D.Flags = D3D12_RESOURCE_FLAG_NONE;            // オプションなし
    resourceDesc3D.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;     // データが行優先順で格納
    // 頂点バッファの生成
    hr = m_pDevice->CreateCommittedResource(
        &heapprop, D3D12_HEAP_FLAG_NONE,
        &resourceDesc3D, D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr, IID_PPV_ARGS(&m_pVertexBuffer3D));
    // 頂点のMap
    Vertex3D* vertMap3D = nullptr;
    hr = m_pVertexBuffer3D->Map(0, nullptr, (void**)&vertMap3D);
    if (FAILED(hr)) return hr;
    std::copy(std::begin(vertices3D), std::end(vertices3D), vertMap3D);
    m_pVertexBuffer3D->Unmap(0, nullptr);
    // 頂点バッファービューの生成
    vertexBufferView3D.BufferLocation = m_pVertexBuffer3D->GetGPUVirtualAddress();
    vertexBufferView3D.SizeInBytes = sizeof(vertices3D);        // 全バイト数
    vertexBufferView3D.StrideInBytes = sizeof(vertices3D[0]);   // １頂点あたりのバイト数

    // インデックスバッファーの生成
    D3D12_RESOURCE_DESC indexResourceDesc3D = {};
    indexResourceDesc3D.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;        // リソースのタイプ
    indexResourceDesc3D.Width = indexList.size() * sizeof(unsigned short);  // 頂点情報のサイズ
    indexResourceDesc3D.Height = 1;                                         // 頂点情報のサイズ(Widthに格納済み)
    indexResourceDesc3D.DepthOrArraySize = 1;                               // リソースの配列のサイズ
    indexResourceDesc3D.MipLevels = 1;
    indexResourceDesc3D.Format = DXGI_FORMAT_UNKNOWN;                       // フォーマット指定なし
    indexResourceDesc3D.SampleDesc.Count = 1;
    indexResourceDesc3D.Flags = D3D12_RESOURCE_FLAG_NONE;                   // オプションなし
    indexResourceDesc3D.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;            // データが行優先順で格納
    hr = m_pDevice->CreateCommittedResource(
        &heapprop,                              // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                   // 指定なし
        &indexResourceDesc3D,                   // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,      // アップロード ヒープに必要な開始状態
        nullptr,
        IID_PPV_ARGS(&m_pIndexBuffer3D));       // インデックスバッファー
    if (FAILED(hr)) return hr;
    // インデックスのMap
    unsigned short* indexMap3D = nullptr;
    hr = m_pIndexBuffer3D->Map(0, nullptr, (void**)&indexMap3D);
    if (FAILED(hr)) return hr;
    std::copy(indexList.begin(), indexList.end(), indexMap3D);
    m_pIndexBuffer3D->Unmap(0, nullptr);
    // インデックスバッファービューの生成
    indexBufferView3D.BufferLocation = m_pIndexBuffer3D->GetGPUVirtualAddress();
    indexBufferView3D.SizeInBytes = (UINT)indexList.size() * sizeof(unsigned short);// 全バイト数
    indexBufferView3D.Format = DXGI_FORMAT_R16_UINT;                                // フォーマット

    //-------------------------------------------------------------------------
#pragma endregion


    // ディスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC basicDescHeapDesc = {};
    basicDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;  // シェーダーから見えるように
    basicDescHeapDesc.NodeMask = 0;                                       // マスクは０
    basicDescHeapDesc.NumDescriptors = 2;                                 // SRV, CBVの２つ
    basicDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;      // デスクリプタヒープのタイプ(定数バッファ、シェーダーリソース)
    // ディスクリプタヒープの作成
    hr = m_pDevice->CreateDescriptorHeap(&basicDescHeapDesc, IID_PPV_ARGS(&m_pBasicDescHeap));
    if (FAILED(hr)) return hr;

#pragma region テクスチャの作成----------------------------------------------------
    // テクスチャバッファの作成------------------------------------------------------
    struct TexRGBA
    {
        unsigned char r, g, b, a;
    };
    // 256×256のテクスチャ
    std::vector<TexRGBA> textureData(256 * 256);
   int i = 0;
    // 色情報を書き込む
    for (auto& rgba : textureData)
    {
        rgba.r = i % 256;
        rgba.g = i % 64;
        rgba.b = i % 128;
        rgba.a = 255;

        i++;
    }

    // WriteToSubResourceで転送するためのヒープ設定
    D3D12_HEAP_PROPERTIES heapProp = {};
    heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;                         // カスタム設定
    heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;  // ライトバック
    heapProp.MemoryPoolPreference= D3D12_MEMORY_POOL_L0;            // メモリプールL0
    heapProp.CreationNodeMask = 0;                                  // シングルアダプターなのでMaskは0
    heapProp.VisibleNodeMask = 0;                                   // シングルアダプターなのでMaskは0

    // テクスチャリソースの設定
    D3D12_RESOURCE_DESC textrueResourceDesc = {};
    textrueResourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;            // 8ビット、0.0f～1.0fに正規化された浮動小数点
    textrueResourceDesc.Width = 256;                                    // 幅
    textrueResourceDesc.Height = 256;                                   // 高さ
    textrueResourceDesc.DepthOrArraySize = 1;                           // リソースの配列のサイズ
    textrueResourceDesc.SampleDesc.Count = 1;                           // アンチエイリアシングしない
    textrueResourceDesc.SampleDesc.Quality = 0;                         // クオリティは最低
    textrueResourceDesc.MipLevels = 1;                                  // ミップマップしないので１を指定
    textrueResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; // 2Dテクスチャとして使用
    textrueResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;          // レイアウトの指定なし
    textrueResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;               // オプション指定なし
    // テクスチャバッファの生成
    hr = m_pDevice->CreateCommittedResource(
        &heapProp,                                  // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                       // 指定なし
        &textrueResourceDesc,                       // リソースの設定
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ用指定
        nullptr,
        IID_PPV_ARGS(&m_pTextureBuffer));           // テクスチャバッファー
    if (FAILED(hr)) return hr;

    // テクスチャバッファーの転送
    hr = m_pTextureBuffer->WriteToSubresource(
        0,                                              // サブリソースインデックス
        nullptr,                                        // 書き込み領域の指定（０：全域へコピー）
        textureData.data(),                             // テクスチャデータのアドレス
        sizeof(TexRGBA) * 256,                          // 横1列のサイズ
        sizeof(TexRGBA) * (UINT)textureData.size());    // テクスチャデータの大きさ
    if (FAILED(hr)) return hr;

    // シェーダーリソースビューの作成
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                                // RGBA(0.0f～1.0fに正規化)
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;                      // 2Dテクスチャを指定
    srvDesc.Texture2D.MipLevels = 1;                                            // ミップマップは使用しないので０
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; // 指定されたフォーマットにデータ通りの順序で割り当てる
    // シェーダーリソースの生成
    m_pDevice->CreateShaderResourceView(
        m_pTextureBuffer.Get(),                                 // シェーダーリソースと結びつけるテクスチャリソース
        &srvDesc,                                               // シェーダーリソースの設定
        m_pBasicDescHeap->GetCPUDescriptorHandleForHeapStart());  // ヒープのどこに割り当てるか
    // ------------------------------------------------------------------------
#pragma endregion
    
#pragma region 定数バッファ-------------------------------------------------------
    // 定数バッファ---------------------------------------------------------------
    // 定数バッファのヒーププロパティの設定
    D3D12_HEAP_PROPERTIES constHeapProp = {};
    constHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;                       // デフォルト設定
    constHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;    // デフォルト設定
    constHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;     // デフォルト設定
    // 定数バッファのリソースの生成
    D3D12_RESOURCE_DESC ConstResourceDesc = {};
    ConstResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    ConstResourceDesc.Width = (sizeof(XMFLOAT4X4) * 3 + 0xff) & ~0xff; // 頂点情報のサイズ
    ConstResourceDesc.Height = 1;
    ConstResourceDesc.DepthOrArraySize = 1;
    ConstResourceDesc.MipLevels = 1;
    ConstResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    ConstResourceDesc.SampleDesc.Count = 1;
    ConstResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    ConstResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    m_pConstResources.resize(1);
    hr = m_pDevice->CreateCommittedResource(
        &constHeapProp,                                  // ヒープの設定
        D3D12_HEAP_FLAG_NONE,                       // 指定なし
        &ConstResourceDesc,                       // リソースの設定
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pConstResources[0]));        // 定数バッファー
    if (FAILED(hr)) return hr;

    // 定数バッファのマップ
    XMFLOAT4X4* mapMatrix;
    hr = m_pConstResources[0]->Map(0, nullptr, (void**)&mapMatrix);
    if (FAILED(hr)) return hr;
    std::copy(std::begin(matrix), std::end(matrix), mapMatrix);
    m_pConstResources[0]->Unmap(0, nullptr);
    
    auto handle = m_pBasicDescHeap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    // 定数バッファビューの設定
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = m_pConstResources[0]->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = (UINT)m_pConstResources[0]->GetDesc().Width;
    // 定数バッファの作成
    m_pDevice->CreateConstantBufferView(&cbvDesc, handle);

    // ------------------------------------------------------------------------
#pragma endregion

    return S_OK;
}

// 深度バッファ、サンプラー、パイプライン、シグネチャ、ビューポート、シザー矩形の初期化
HRESULT GfxD3DManager::CreatePipeline()
{
    HRESULT hr = S_OK;
    ComPtr<ID3DBlob> pErrorBlob; // シェーダー読み込みのエラー対応

#pragma region 深度バッファの作成-----------------------------------------------------------

    // リソースの作成
    D3D12_RESOURCE_DESC depthResourceDesc = {};
    depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;   // 2Dテクスチャ
    depthResourceDesc.Width = SCREEN_WIDTH;                             // レンダーターゲットと同じ幅
    depthResourceDesc.Height = SCREEN_HEIGHT;                           // レンダーターゲットと同じ高さ
    depthResourceDesc.DepthOrArraySize = 1;                             // リソースの配列のサイズ
    depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;                   // 深度値書き込み用フォーマット
    depthResourceDesc.SampleDesc.Count = 1;                             // サンプルは1ピクセルあたり1つ
    //depthResourceDesc.SampleDesc.Quality = 0;                           // 
    depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;  // デプスステンシルとして使用
    // ヒーププロパティの設定
    D3D12_HEAP_PROPERTIES depthHeapProp = {};
    depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;                       // デフォルト設定
    depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;    // デフォルト設定
    depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;     // デフォルト設定
    // クリアバリューの設定
    D3D12_CLEAR_VALUE depthClearValue = {};
    depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;     // 深度値書き込み用フォーマット
    depthClearValue.DepthStencil.Depth = 1.0f;
    // リソースの作成
    hr = m_pDevice->CreateCommittedResource(
        &depthHeapProp,                         // ヒーププロパティ
        D3D12_HEAP_FLAG_NONE,
        &depthResourceDesc,                     // リソースの設定
        D3D12_RESOURCE_STATE_DEPTH_WRITE,       // 深度値書き込み用
        &depthClearValue,                       // クリアバリュー
        IID_PPV_ARGS(&m_pDepthBuffer));         // リソースのアドレス
    if (FAILED(hr)) return hr;

    // ディスクリプタヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC depthHeapDesc = {};
    depthHeapDesc.NumDescriptors = 1;                       // 深度ビューは１つ
    depthHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;    // デプスステンシルビューとして使う
    hr = m_pDevice->CreateDescriptorHeap(&depthHeapDesc, IID_PPV_ARGS(&m_pDepthDescHeap));
    if (FAILED(hr)) return hr;

    // 深度バッファビューの作成
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;                 // 深度値書き込み用フォーマット
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;  // 2Dテクスチャ
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;                    // 指定なし
    m_pDevice->CreateDepthStencilView(
        m_pDepthBuffer.Get(),
        &dsvDesc,
        m_pDepthDescHeap->GetCPUDescriptorHandleForHeapStart());
    
    // ------------------------------------------------------------------------
#pragma endregion

#pragma region サンプラーの設定------------------------------------------------------------
    // サンプラーの設定------------------------------------------------------------
    m_samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 横方向の繰り返し
    m_samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 縦方向の繰り返し
    m_samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 奥行きの繰り返し
    m_samplerDesc.BorderColor
        = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;              // ボーダーは黒
    m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;         // 線形補間
    m_samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;                       // ミップマップ最大値
    m_samplerDesc.MaxLOD = 0.0f;                                    // ミップマップ最小値
    m_samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーから見える
    m_samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;     // リサンプリングしない

    // ------------------------------------------------------------------------
#pragma endregion

    // ルートシグネチャにテクスチャのレジスタ種別、レジスタ番号の関連を記述---------------------

    // ディスクリプタレンジの設定
    D3D12_DESCRIPTOR_RANGE descriptorTableRange[2] = {};
    // テクスチャ用レジスタ
    descriptorTableRange[0].NumDescriptors = 1;                            // ディスクリプタの数
    descriptorTableRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;   // 種別はテクスチャ
    descriptorTableRange[0].BaseShaderRegister = 0;                        // 0スロットから
    descriptorTableRange[0].OffsetInDescriptorsFromTableStart =
        D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;                           // 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    descriptorTableRange[0].RegisterSpace = 0;
    // 定数バッファ用レジスタ
    descriptorTableRange[1].NumDescriptors = 1;                            // ディスクリプタの数
    descriptorTableRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;   // 種別は定数バッファ
    descriptorTableRange[1].BaseShaderRegister = 0;                        // 0スロットから
    descriptorTableRange[1].OffsetInDescriptorsFromTableStart =
        D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;                           // 連続したディスクリプタレンジが前のディスクリプタレンジの直後に来る
    descriptorTableRange[1].RegisterSpace = 0;

    // ルートパラメータの作成
    m_rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    m_rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;                    // ディスクリプタレンジ数
    m_rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorTableRange[0];
    m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;           // ピクセルシェーダーから見えるようにする

    m_rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ルートパラメータタイプ
    m_rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;                    // ディスクリプタレンジ数
    m_rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorTableRange[1];
    m_rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;          // 頂点シェーダーから見えるようにする

    // ------------------------------------------------------------------------
    
    // ルートシグネチャの設定--------------------------------------------------------
    D3D12_ROOT_SIGNATURE_DESC signatureDesc = {};
    signatureDesc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;   // 頂点情報がある
    signatureDesc.pParameters = m_rootParameters;                       // ルートパラメータ
    signatureDesc.NumParameters = 2;                                    // ルートパラメータの数
    signatureDesc.pStaticSamplers = &m_samplerDesc;                     // サンプラー
    signatureDesc.NumStaticSamplers = 1;                                // サンプラーの数

    // バイナリコードの作成
    ComPtr<ID3DBlob> pRootSignatureBlob;
    hr = D3D12SerializeRootSignature(
        &signatureDesc,                         // ルートシグネチャの設定
        D3D_ROOT_SIGNATURE_VERSION_1_0,         // ルートシグネチャバージョン
        &pRootSignatureBlob,                    // ルートシグネチャのバッファー
        &pErrorBlob);                           // エラー処理
    if (FAILED(hr)) return hr;

    // ルートシグネチャの生成
    hr = m_pDevice->CreateRootSignature(
        0,                                      // ノードマスク
        pRootSignatureBlob->GetBufferPointer(), // バッファーのアドレス
        pRootSignatureBlob->GetBufferSize(),    // バッファーのサイズ
        IID_PPV_ARGS(&m_pRootSignature));       // ルートシグネチャ
    if (FAILED(hr)) return hr;

    // ------------------------------------------------------------------------

    // パイプラインの設定-----------------------------------------------------------
    // ルートシグネチャの設定
    pipelineDesc.pRootSignature = m_pRootSignature.Get();
    // シェーダーのセット
    pipelineDesc.VS.pShaderBytecode = m_pVSBlob3D->GetBufferPointer();  // 頂点シェーダーのアドレスの先頭
    pipelineDesc.VS.BytecodeLength  = m_pVSBlob3D->GetBufferSize();     // 頂点シェーダーのバッファの大きさ
    pipelineDesc.PS.pShaderBytecode = m_pPSBlob3D->GetBufferPointer();  // ピクセルシェーダーのアドレスの先頭
    pipelineDesc.PS.BytecodeLength  = m_pPSBlob3D->GetBufferSize();     // ピクセルシェーダーのバッファの大きさ
    // インプットレイアウトの設定
    pipelineDesc.InputLayout.pInputElementDescs = inputLayout3D.data(); // インプットレイアウトのアドレス
    pipelineDesc.InputLayout.NumElements = (UINT)inputLayout3D.size();  // インプットレイアウトの要素の数
    // サンプルマスクの設定
    pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // デフォルト
    // ラスタライザのステートの設定
    pipelineDesc.RasterizerState.MultisampleEnable = false;         // アンチエイリアスなし
    pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;   // カリングしない
    pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;  // 塗りつぶしをする
    pipelineDesc.RasterizerState.DepthClipEnable = true;            // 深度方向のクリッピングを有効
    // ブレンドステートの設定
    pipelineDesc.BlendState.AlphaToCoverageEnable = false;          // 三角形の網羅率の計算
    pipelineDesc.BlendState.IndependentBlendEnable = false;         // RTV[0]のブレンドステートをすべてのRTVに適用
    D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
    blendDesc.BlendEnable = false;                                  // ブレンドしない
    blendDesc.LogicOpEnable = false;                                // 論理演算しない
    blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // 書き込むときのマスク値
    pipelineDesc.BlendState.RenderTarget[0] = blendDesc;
    // 頂点のつなぎ方の設定
    pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;     // 切り離ししない
    // プリミティブタイプの設定
    pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;    // 三角形
    // レンダーターゲットの設定
    pipelineDesc.NumRenderTargets = 1;                          // レンダーターゲットの数
    pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;    // 0～1に正規化されたRGBA
    // アンチエイリアシングの設定
    pipelineDesc.SampleDesc.Count = 1;      // サンプリングは1ピクセルにつき1ピクセル
    pipelineDesc.SampleDesc.Quality = 0;    // クオリティは最低
    // 深度バッファの設定
    pipelineDesc.DepthStencilState.DepthEnable = true;                          // 深度バッファを使う
    pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込む
    pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;      // 小さい方を採用
    pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;                             // 深度値書き込み用フォーマット
    // パイプラインの生成
    hr = m_pDevice->CreateGraphicsPipelineState(
        &pipelineDesc, IID_PPV_ARGS(&m_pPipeLineState));
    if (FAILED(hr)) return hr;
    
    // ------------------------------------------------------------------------

#pragma region // ビューポートの作成、シザー矩形
    // ビューポートの作成
    viewport.Width = SCREEN_WIDTH;      // 出力先の幅（ピクセル数）
    viewport.Height = SCREEN_HEIGHT;    // 出力先の高さ（ピクセル数）
    viewport.TopLeftX = 0;              // 出力先の左上座標X
    viewport.TopLeftY = 0;              // 出力先の左上座標Y
    viewport.MinDepth = 0.0f;           // 深度値の最小値
    viewport.MaxDepth = 1.0f;           // 深度値の最大値
    // シザー矩形
    scissorRect.top = 0;                                            // 切り抜き上座標
    scissorRect.left = 0;                                           // 切り抜き左座標
    scissorRect.right = scissorRect.left + (LONG)viewport.Width;    // 切り抜き右座標
    scissorRect.bottom = scissorRect.top + (LONG)viewport.Height;   // 切り抜き下座標
#pragma endregion

    return hr;
}

//------------------------------------------------------------------------------
/// 描画の開始(バックバッファ＆Ｚバッファのクリア)
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3DManager::BeginDraw()
{
#ifdef DX12

    //現在のバックバッファーのインデックス
    auto bbIdx = m_pSwapChain4->GetCurrentBackBufferIndex();
    auto rtvHeap = m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHeap.ptr += bbIdx * static_cast<unsigned long long>(m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    // リソースバリアの設定
    m_pBarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;  // 遷移
    m_pBarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;       // 指定なし
    m_pBarrierDesc.Transition.pResource = m_pBackBuffers[bbIdx].Get();// バックバッファーリソース
    m_pBarrierDesc.Transition.Subresource = 0;                     // バックバッファは一つなので要素0を指定
    // Present状態からRenderTarget状態に遷移
    m_pBarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    m_pBarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    // リソースバリア指定実行
    m_pCommandList->ResourceBarrier(1, &m_pBarrierDesc); // 第1引数は設定バリア数
    // レンダーターゲットをバックバッファにセット
    auto dsvHeap = m_pDepthDescHeap->GetCPUDescriptorHandleForHeapStart();
    m_pCommandList->OMSetRenderTargets(1, &rtvHeap, false, &dsvHeap);
    float clearColor[4] = { 0.417647f, 0.754902f, 0.4f, 1.0f };
    // レンダーターゲットのクリア(第3、第4引数はクリアする範囲なので指定しなくてよい)
    m_pCommandList->ClearRenderTargetView(rtvHeap, clearColor, 0, nullptr);
    m_pCommandList->ClearDepthStencilView(dsvHeap, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    
#else
    // バックバッファ＆Ｚバッファのクリア
    float ClearColor[4] = { 0.417647f, 0.754902f, 0.4f, 1.0f };
    m_pDeviceContext->ClearRenderTargetView(m_pRentderTarget.Get(), ClearColor);
    m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    // 各ターゲットビューをレンダーターゲットに設定
    m_pDeviceContext->OMSetRenderTargets(1, m_pRentderTarget.GetAddressOf(), nullptr);
#endif // DX12

}

// 描画内容
void GfxD3DManager::TestDraw()
{
    // ビューポートの設定
    m_pCommandList->RSSetViewports(1, &viewport);
    // シザー矩形の設定
    m_pCommandList->RSSetScissorRects(1, &scissorRect);

    // ルートシグネチャをセット
    m_pCommandList->SetGraphicsRootSignature(m_pRootSignature.Get());

    // パイプラインをセット
    m_pCommandList->SetPipelineState(m_pPipeLineState.Get());

    // ディスクリプタヒープの指定
    m_pCommandList->SetDescriptorHeaps(1, m_pBasicDescHeap.GetAddressOf());

    // ルートパラメーター0番とディスクリプタヒープの関連付け
    m_pCommandList->SetGraphicsRootDescriptorTable(
        0, m_pBasicDescHeap->GetGPUDescriptorHandleForHeapStart());

    // プリミティブの設定
    //m_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //// 頂点バッファーの設定
    //m_pCommandList->IASetVertexBuffers(0, 1, &vertexBufferView);
    //// インデックスバッファーの設定
    //m_pCommandList->IASetIndexBuffer(&indexBufferView);
    //// 描画命令
    //m_pCommandList->DrawIndexedInstanced(6, 1, 0, 0, 0);

    // 次のアドレスを計算
    auto handle = m_pBasicDescHeap->GetGPUDescriptorHandleForHeapStart();
    handle.ptr += m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    // ルートパラメーター1番とディスクリプタヒープの関連付け
    m_pCommandList->SetGraphicsRootDescriptorTable(1, handle);

    // プリミティブの設定
    m_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    // 頂点バッファーの設定
    m_pCommandList->IASetVertexBuffers(0, 1, &vertexBufferView3D);
    // インデックスバッファーの設定
    m_pCommandList->IASetIndexBuffer(&indexBufferView3D);
    // 描画命令
    m_pCommandList->DrawIndexedInstanced(36, 1, 0, 0, 0);
    
}


//------------------------------------------------------------------------------
/// 描画の修了(バックバッファとフロントバッファの入れ替え)
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3DManager::EndDraw()
{
#ifdef DX12
    // RenderTarget状態からPresent状態に遷移
    m_pBarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    m_pBarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    // リソースバリア指定実行
    m_pCommandList->ResourceBarrier(1, &m_pBarrierDesc); // 第1引数は設定バリア数

    // クローズ
    m_pCommandList->Close();

    // 命令の実行
    ID3D12CommandList* commandLists[] = { m_pCommandList.Get() };
    m_pCommandQueue->ExecuteCommandLists(1, commandLists);

    // スワップ
    m_pSwapChain4->Present(1, 0);

    // 命令がすべて実行されたか
    m_pCommandQueue->Signal(m_pFence.Get(), ++m_fenceValue);
    if (m_pFence->GetCompletedValue() != m_fenceValue)
    {
        // イベントハンドルの取得
        auto eventHandle = CreateEvent(nullptr, false, false, nullptr);
        m_pFence->SetEventOnCompletion(m_fenceValue, eventHandle);
        if (eventHandle)
        {
            // イベントが発生するまで待ち続ける
            WaitForSingleObject(eventHandle, INFINITE);
            // イベントハンドルを閉じる
            CloseHandle(eventHandle);
        }
}

    // リセット
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);
#else
    // バックバッファとフロントバッファの入れ替え
    m_pSwapChain->Present(0, 0);
#endif // DX12
}

#ifdef DX12
//------------------------------------------------------------------------------
/// デバッグレイヤーを有効化する
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3DManager::EnableDebugLayer()
{
    ComPtr<ID3D12Debug> pDebug12;
    
    // デバッグインターフェースの取得
    D3D12GetDebugInterface(IID_PPV_ARGS(&pDebug12));
    pDebug12->EnableDebugLayer(); // デバッグレイヤーを有効
    pDebug12->Release();          // 有効にしたら解放
}
#endif // DX12
