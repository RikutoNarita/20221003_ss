//==============================================================================
// Filename: Gfx_GraphicsManager.cpp
// Description: DirectX11 or 12 の管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================


// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\Gfx_DeviceFactory.h>
#include <GraphicsSystem\Interface\IGfx_ViewPort.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11DepthStencilView_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12DepthStencilView_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11ViewPort_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ViewPort_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11ScissorRect_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ScissorRect_Impl.h>

#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>

#include <wrl\client.h>


// 静的変数
GfxGraphicsManager* GfxGraphicsManager::m_pInstance = nullptr;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsManager::GfxGraphicsManager()
{
    m_eAPIKind = API_KIND::DIRECT3D_11;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsManager::~GfxGraphicsManager()
{
}

//------------------------------------------------------------------------------
/// グラフィックスAPIの初期化
///
/// \param[in] type     APIの種類
/// \param[in] hWnd     ウィンドウハンドル
/// \param[in] width    ウィンドウの幅
/// \param[in] height   ウィンドウの高さ
///
/// \return 初期化処理の成否
//------------------------------------------------------------------------------
HRESULT GfxGraphicsManager::Init(API_KIND type, HWND hWnd, UINT width, UINT height)
{
    m_eAPIKind = type;

    // デバイス、描画命令機能の生成
    auto hr = DeviceFactory::CreateDeviceAndContext(
        static_cast<int>(type), m_pDevice, m_pRenderCommand);
    if (FAILED(hr))
    {
        return hr;
    }

    // スワップチェーンの生成
    IGfxSwapChain::Description swapChainDesc = {};
    swapChainDesc.hWnd = hWnd;
    swapChainDesc.width = width;
    swapChainDesc.width = height;
    swapChainDesc.fromat = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.bufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.bufferCount = 2;
    swapChainDesc.swapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //DXGI_SWAP_EFFECT_DISCARDの方が効率いいかも
    swapChainDesc.flag = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    hr = DeviceFactory::CreateSwapChain(
        static_cast<int>(type),
        m_pSwapChain,
        swapChainDesc,
        m_pDevice.get(),
        m_pRenderCommand.get());
    if (FAILED(hr))
    {
        return hr;
    }

    // レンダーターゲットビューの生成
    IGfxRenderTarget::Description rtvDesc = {};
    rtvDesc.fromat = swapChainDesc.fromat;          // スワップチェーンと同じフォーマットを指定
    rtvDesc.bufferCount = swapChainDesc.bufferCount;// スワップチェーンと同じ個数を指定
    hr = DeviceFactory::CreateRenderTargetView(static_cast<int>(type), m_pRenderTarget,
        rtvDesc, m_pDevice.get(), m_pSwapChain.get());
    
    // デプスステンシルビューの生成
    IGfxDepthStencil::Description dsvDesc = {};
    dsvDesc.width = width;
    dsvDesc.height = height;
    switch (type)
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11:
        m_DepthStencil = std::make_shared<GfxD3D11DepthStencil>();
        m_DepthStencil->Create(dsvDesc, m_pDevice.get());
        break;
    case GfxGraphicsManager::API_KIND::DIRECT3D_12:
        m_DepthStencil = std::make_shared<GfxD3D12DepthStencil>();
        m_DepthStencil->Create(dsvDesc, m_pDevice.get());
        break;
    case GfxGraphicsManager::API_KIND::OPEN_GL:
    case GfxGraphicsManager::API_KIND::VULKAN:
    default:
        break;
    }

    // ビューポート/シザー矩形の作成
    IGfxViewPort::Description viewPortDesc = {};
    viewPortDesc.width = (float)width;      // 出力先の幅（ピクセル数）
    viewPortDesc.height = (float)height;    // 出力先の高さ（ピクセル数）
    viewPortDesc.TopLeftX = 0;              // 出力先の左上座標X
    viewPortDesc.TopLeftY = 0;              // 出力先の左上座標Y
    viewPortDesc.MinDepth = 0.0f;           // 深度値の最小値
    viewPortDesc.MaxDepth = 1.0f;           // 深度値の最大値
    IGfxScissorRect::Description scissorDesc = {};
    scissorDesc.top = 0;                                                // 切り抜き上座標
    scissorDesc.left = 0;                                               // 切り抜き左座標
    scissorDesc.right = scissorDesc.left + (LONG)viewPortDesc.width;    // 切り抜き右座標
    scissorDesc.bottom = scissorDesc.top + (LONG)viewPortDesc.height;   // 切り抜き下座標
    switch (type)
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11:
        m_viewPort = std::make_shared<GfxD3D11ViewPort>(viewPortDesc);
        m_scissorRect = std::make_shared<GfxD3D11ScissorRect>(scissorDesc);
        break;
    case GfxGraphicsManager::API_KIND::DIRECT3D_12:
        m_viewPort = std::make_shared<GfxD3D12ViewPort>(viewPortDesc);
        m_scissorRect = std::make_shared<GfxD3D12ScissorRect>(scissorDesc);
        break;
    case GfxGraphicsManager::API_KIND::OPEN_GL:
    case GfxGraphicsManager::API_KIND::VULKAN:
    default:
        break;
    }

    // デフォルトのリソースを作成
    CreateGraphicsResource();

    return S_OK;
}


//------------------------------------------------------------------------------
/// グラフィックスAPIの終了処理
///
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsManager::Uninit()
{
    m_pDevice.reset();
    m_pRenderCommand.reset();
}

//------------------------------------------------------------------------------
/// 描画の開始(バックバッファ＆Ｚバッファのクリア)
///
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsManager::BeginDraw()
{
    // レンダーターゲットビューとデプスステンシルビューをセット, リソースバリアの設定(DX12)
    m_pRenderCommand->OMSetRenderTargets(m_pRenderTarget.get(), m_DepthStencil.get());

    // バックバッファのクリア
    float color[] = { 0.417647f, 0.754902f, 0.4f, 1.0f };
    m_pRenderCommand->ClearRenderTargetView(m_pRenderTarget.get(), color);

    // Zバッファのクリア
    m_pRenderCommand->ClearDepthStencilView(m_DepthStencil.get());

    // ビューポート\シザー矩形をセット
    m_viewPort->Bind();
    m_scissorRect->Bind();
}

//------------------------------------------------------------------------------
/// 描画の修了(バックバッファとフロントバッファの入れ替え)
///
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsManager::EndDraw()
{
    // バックバッファとフロントバッファの入れ替え, リソースバリアの設定＆命令実行（DX12）
    m_pRenderCommand->EndDraw();
}

//------------------------------------------------------------------------------
/// インスタンス作成
///
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsManager::CreateInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new GfxGraphicsManager();
    }
}

//------------------------------------------------------------------------------
/// インスタンス取得
///
/// \return クラスのインスタンス
//------------------------------------------------------------------------------
GfxGraphicsManager* GfxGraphicsManager::GetInstance()
{
    return m_pInstance;
}

//------------------------------------------------------------------------------
/// インスタンス削除
///
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsManager::DeleteInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
    }
}

//------------------------------------------------------------------------------
/// APIの種類の取得
///
/// \return APIの種類
//------------------------------------------------------------------------------
GfxGraphicsManager::API_KIND GfxGraphicsManager::GetAPIKind()
{
    return m_eAPIKind;
}
