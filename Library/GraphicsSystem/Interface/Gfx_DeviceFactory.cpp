//==============================================================================
// Filename: IGfx_DeviceFactory.h
// Description: デバイスの作成クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\IGfx_Device.h>
#include <GraphicsSystem\Interface\IGfx_RenderCommand.h>


#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#include <wrl\client.h>

// ライブラリのリンク
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

namespace DeviceFactory
{
    HRESULT CreateDeviceAndContext(
        int apiKind,
        std::shared_ptr<IGfxDevice>& pDevice,
        std::shared_ptr<IGfxRenderCommand>& pRenderCommand)
    {
        HRESULT hr = S_OK;

        // APIの種類によって初期化方法を分ける
        switch (apiKind)
        {
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11の初期化
        {
            
            Microsoft::WRL::ComPtr<ID3D11Device> pDevice11;
            Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext11;
            D3D_FEATURE_LEVEL futureLevel;

            // オプションの設定
            UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
            creationFlags |= D3D11_CREATE_DEVICE_DEBUG; // DEBUGビルド時はDirect3Dのデバッグを有効にする
#endif
            // ハードウェアの機能レベル
            D3D_FEATURE_LEVEL featureLevels[] =
            {
                D3D_FEATURE_LEVEL_11_1, // Direct3D 11.1    ShaderModel 5
                D3D_FEATURE_LEVEL_11_0, // Direct3D 11      ShaderModel 5
            };
            // デバイスとデバイスコンテキストを作成
            hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                creationFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION,
                &pDevice11, &futureLevel, &pDeviceContext11);
            if(FAILED(hr)) return hr;

            // メモリ確保
            pDevice = std::make_shared<GfxD3D11Device>();
            pRenderCommand = std::make_shared<GfxD3D11RenderCommand>();
            // 子クラスからキャストしてメンバ変数に代入
            dynamic_cast<GfxD3D11Device*>(pDevice.get())->m_pDevice = pDevice11;
            dynamic_cast<GfxD3D11RenderCommand*>(pRenderCommand.get())->m_pDeviceContext = pDeviceContext11;

            break;
        }
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12の初期化
        {
            Microsoft::WRL::ComPtr<ID3D12Device> pDevice12;
            Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> pCommandList;
            Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pCommandAllocator;
            Microsoft::WRL::ComPtr<ID3D12CommandQueue> pCommandQueue;
            Microsoft::WRL::ComPtr<ID3D12Fence> pFence;

#ifdef _DEBUG
            // デバッグレイヤーを有効にする
            Microsoft::WRL::ComPtr<ID3D12Debug> pDebug12;
            D3D12GetDebugInterface(IID_PPV_ARGS(&pDebug12));    // デバッグインターフェースの取得
            pDebug12->EnableDebugLayer();                       // デバッグレイヤーを有効
            //pDebug12->Release();                                // 有効にしたら解放
#endif // _DEBUG

            // ハードウェアの機能レベル
            D3D_FEATURE_LEVEL levels[] =
            {
                D3D_FEATURE_LEVEL_12_0,
                D3D_FEATURE_LEVEL_12_1,
            };
            // デバイスの生成
            for (auto lv : levels)
            {
                // 生成可能なバージョンが見つかったらループ終了
                hr = D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(&pDevice12));
                if (FAILED(hr)) continue;
                else            break;
            }
            if (FAILED(hr)) return hr;

            // コマンドアロケーターの生成
            hr = pDevice12->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pCommandAllocator));
            if (FAILED(hr)) return hr;

            // コマンドリストの生成
            hr = pDevice12->CreateCommandList(
                0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                pCommandAllocator.Get(), nullptr,
                IID_PPV_ARGS(&pCommandList));
            if (FAILED(hr)) return hr;

            // コマンドキューの生成
            D3D12_COMMAND_QUEUE_DESC queueDesc = {};
            queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;            // タイムアウトなし
            queueDesc.NodeMask = 0;                                     // アダプターを一つしか使わないときは0
            queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;   // プライオリティは指定なし
            queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;            // タイプはコマンドリストと合わせる
            hr = pDevice12->CreateCommandQueue(
                &queueDesc, IID_PPV_ARGS(&pCommandQueue));
            if (FAILED(hr)) return hr;

            // メモリ確保
            pDevice = std::make_shared<GfxD3D12Device>();
            pRenderCommand = std::make_shared<GfxD3D12RenderCommand>();
            // 子クラスにキャストしてメンバ変数に代入
            GfxD3D12Device* pDeviceInterface = dynamic_cast<GfxD3D12Device*>(pDevice.get());
            GfxD3D12RenderCommand* pRenderInterface = dynamic_cast<GfxD3D12RenderCommand*>(pRenderCommand.get());

             // フェンス(コマンドリストの命令をすべて実行したかを知る役割)の作成
            hr = pDevice12->CreateFence(pRenderInterface->m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence));
            if (FAILED(hr))
            {
                return hr;
            }

            pDeviceInterface->m_pDevice = pDevice12;
            pRenderInterface->m_pCommandList = pCommandList.Get();
            pRenderInterface->m_pCommandAllocator = pCommandAllocator.Get();
            pRenderInterface->m_pCommandQueue = pCommandQueue.Get();
            pRenderInterface->m_pFence = pFence;

            break;
        }
        case (int)GfxGraphicsManager::API_KIND::OPEN_GL:    // OpenGLの初期化
        {
            break;
        }
        case (int)GfxGraphicsManager::API_KIND::VULKAN:     // Vulkanの初期化
        {
            break;
        }
        default:
            break;
        }

        return S_OK;
    }



    // スワップチェーンの作成
    HRESULT CreateSwapChain(
        int apiKind,
        // out
        std::shared_ptr<IGfxSwapChain>& pSwapChain,
        const IGfxSwapChain::Description& desc,
        IGfxDevice* pDevice,
        IGfxRenderCommand* pRenderCommand)
    {
        HRESULT hr = S_OK;

        // APIの種類によって初期化方法を分ける
        switch (apiKind)
        {
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11の初期化
        {
            // メモリの確保
            pSwapChain = std::make_shared<GfxD3D11SwapChain>();
            hr = pSwapChain->Create(desc, pDevice, pRenderCommand);
            if (FAILED(hr))
            {
                return hr;
            }

            //// ファクトリーを作成
            //Microsoft::WRL::ComPtr<IDXGIFactory> factory;
            //hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
            //if (FAILED(hr))
            //{
            //    return hr;
            //}
            //
            //// スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
            //DXGI_SWAP_CHAIN_DESC scDesc = {};                       // スワップチェーンの設定データ
            //scDesc.BufferDesc.Width = desc.width;                   // 画面の幅
            //scDesc.BufferDesc.Height = desc.height;                 // 画面の高さ
            //scDesc.BufferDesc.Format = desc.fromat;                 // バッファの形式
            //scDesc.BufferUsage = desc.bufferUsage;                  // バッファの使用方法
            //scDesc.BufferCount = desc.bufferCount;                  // バッファの数
            //scDesc.OutputWindow = desc.hWnd;                        // ウィンドウハンドル
            //scDesc.SwapEffect = desc.swapEffect;
            //scDesc.Flags = desc.flag;
            //scDesc.Windowed = TRUE;                                 // ウィンドウモード
            //scDesc.SampleDesc.Count = 1;                            // MSAAは使用しない
            //scDesc.SampleDesc.Quality = 0;                          // MSAAは使用しない
            //scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            //scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            //scDesc.BufferDesc.RefreshRate.Numerator = 0;
            //scDesc.BufferDesc.RefreshRate.Denominator = 1;
            //// スワップチェインの作成
            //hr = factory->CreateSwapChain(
            //    dynamic_cast<GfxD3D11Device*>(pDevice)->GetDevice(),
            //    &scDesc,
            //    &dynamic_cast<GfxD3D11SwapChain*>(pSwapChain.get())->m_pSwapChain);
            //if (FAILED(hr))
            //{
            //    return hr;
            //}
            
            break;
        }
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12の初期化
        {
            // メモリの確保
            pSwapChain = std::make_shared<GfxD3D12SwapChain>();
            hr = pSwapChain->Create(desc, pDevice, pRenderCommand);
            if (FAILED(hr))
            {
                return hr;
            }
//            // ファクトリーの生成
//            Microsoft::WRL::ComPtr<IDXGIFactory6> pFactory;
//#ifdef _DEBUG
//            if (CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&pFactory)) != S_OK)
//            {
//                return E_FAIL;
//            }
//#else
//            if (CreateDXGIFactory1(IID_PPV_ARGS(&pFactory)) != S_OK)
//            {
//                return E_FAIL;
//            }
//#endif // _DEBUG
//
//            // スワップチェーンの設定
//            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
//            swapChainDesc.Width = desc.width;
//            swapChainDesc.Height = desc.height;
//            swapChainDesc.Format = desc.fromat;
//            swapChainDesc.BufferUsage = desc.bufferUsage;
//            swapChainDesc.BufferCount = desc.bufferCount;
//            swapChainDesc.SwapEffect = desc.swapEffect;
//            swapChainDesc.Flags = desc.flag;
//            swapChainDesc.Stereo = false;
//            swapChainDesc.SampleDesc.Count = 1;                     // サンプルは1ピクセルづつ
//            swapChainDesc.SampleDesc.Quality = 0;                   // クオリティは最低
//            swapChainDesc.Scaling = DXGI_SCALING_STRETCH;           // バックバッファーは伸び縮み可能
//            swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;  // 指定なし
//
//            // スワップチェーンの生成
//            Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;
//            hr = pFactory->CreateSwapChainForHwnd(
//                dynamic_cast<GfxD3D12RenderCommand*>(pRenderCommand)->GetCommadQueue(),
//                desc.hWnd,
//                &swapChainDesc,
//                nullptr,
//                nullptr,
//                &swapchain1);
//            if (FAILED(hr)) return hr;
//
//            // SwapChain4 → SwapChain1にする
//            swapchain1.As(&dynamic_cast<GfxD3D12SwapChain*>(pSwapChain.get())->m_pSwapChain);

            break;
        }
        case (int)GfxGraphicsManager::API_KIND::OPEN_GL:    // OpenGLの初期化
        {
            break;
        }
        case (int)GfxGraphicsManager::API_KIND::VULKAN:     // Vulkanの初期化
        {
            break;
        }
        default:
            break;
        }

        return S_OK;
    }


    // レンダーターゲットの作成
    HRESULT CreateRenderTargetView(
        int apiKind,
        std::shared_ptr<IGfxRenderTarget>& pRenderTarget,
        const IGfxRenderTarget::Description& desc,
        IGfxDevice* pDevice,
        IGfxSwapChain* pSwapChain)
    {
        HRESULT hr = S_OK;

        // APIの種類によって初期化方法を分ける
        switch (apiKind)
        {
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11の初期化
        {
            // メモリの確保
            pRenderTarget = std::make_shared<GfxD3D11RenderTarget>();
            hr = pRenderTarget->Create(desc, pDevice, pSwapChain);
            if (FAILED(hr))
            {
                return hr;
            }

            break;
        }
        case (int)GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12の初期化
        {
            // メモリの確保
            pRenderTarget = std::make_shared<GfxD3D12RenderTarget>();
            hr = pRenderTarget->Create(desc, pDevice, pSwapChain);
            if (FAILED(hr))
            {
                return hr;
            }
           
            break;
        }
        case (int)GfxGraphicsManager::API_KIND::OPEN_GL:    // OpenGLの初期化
        {
            break;
        }
        case (int)GfxGraphicsManager::API_KIND::VULKAN:     // Vulkanの初期化
        {
            break;
        }
        default:
            break;
        }

        return S_OK;
    }

}
