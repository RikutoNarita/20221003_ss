//==============================================================================
// Filename: DirectX.cpp
// Description: DirectXの初期化
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <GraphicsSystem/DirectX/DirectX.h>
#include <main.h>

//! ライブラリのリンク
#pragma comment(lib,"d3d11.lib")
#pragma comment (lib, "d3d10_1.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment(lib,"dwrite.lib")

//! グローバル変数
ID3D11Device* g_pDevice11;                          //! デバイス
IDXGISwapChain* g_pSwapChain;                       //! スワップチェーン
ID3D11Texture2D* g_pTexture11;                      //! Zバッファ用メモリ
ID3D11DeviceContext* g_pImmContext;                 //! デバイス コンテキスト

ID3D11RenderTargetView* g_pRenderTargetView;        //! フレームバッファ
ID3D11DepthStencilView* g_pDepthStencilView;        //! Zバッファ
ID3D11RasterizerState* g_pRs[MAX_CULLMODE];         //! ラスタライザ ステート
ID3D11BlendState* g_pBlendState[MAX_BLENDSTATE];    //! ブレンド ステート
ID3D11DepthStencilState* g_pDSS[2];                 //! Z/ステンシル ステート
UINT g_uSyncInterval = 0;                           //! 垂直同期 (0:無, 1:有)

//! プロトタイプ宣言
ID3D11Device* GetDevice()
{
	return g_pDevice11;
}
IDXGISwapChain* GetSwapChain()
{
	return g_pSwapChain;
}
ID3D11DeviceContext* GetDeviceContext()
{
	return g_pImmContext;
}
HRESULT CreateBackBuffer()
{
	HRESULT hr = S_OK;

	//! レンダーターゲットビュー生成
	ID3D11Texture2D* pBackBuffer = nullptr;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	hr = g_pDevice11->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr)) { return hr; }

	// Zバッファ用テクスチャ生成
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
	hr = g_pDevice11->CreateTexture2D(&td, nullptr, &g_pTexture11);
	if (FAILED(hr)) { return hr; }

	// Zバッファターゲットビュー生成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = g_pDevice11->CreateDepthStencilView(g_pTexture11, &dsvd, &g_pDepthStencilView);
	if (FAILED(hr)) { return hr; }

	// 各ターゲットビューをレンダーターゲットに設定
	g_pImmContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)SCREEN_WIDTH;
	vp.Height = (float)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmContext->RSSetViewports(1, &vp);

	return S_OK;
}

void ReleaseBackBuffer()
{

	if (g_pImmContext) {
		g_pImmContext->OMSetRenderTargets(0, nullptr, nullptr);
	}

	SAFE_RELEASE(g_pDepthStencilView);
	SAFE_RELEASE(g_pTexture11);
	SAFE_RELEASE(g_pRenderTargetView);

	//RenderTarget::Uninit();
}
void ReleaseDirectX()
{
	// 深度ステンシルステート解放
	for (int i = 0; i < _countof(g_pDSS); ++i) {
		SAFE_RELEASE(g_pDSS[i]);
	}

	// ブレンド ステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i) {
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ラスタライザ ステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i) {
		SAFE_RELEASE(g_pRs[i]);
	}

	// バックバッファ解放
	ReleaseBackBuffer();

	// スワップチェーン解放
	SAFE_RELEASE(g_pSwapChain);

	// デバイス コンテキストの開放
	SAFE_RELEASE(g_pImmContext);

	// デバイスの開放
	SAFE_RELEASE(g_pDevice11);
}
void SetZBuffer(bool bEnable)
{
	g_pImmContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[0], 0);
}
void SetZWrite(bool bEnable)
{
	g_pImmContext->OMSetDepthStencilState((bEnable) ? nullptr : g_pDSS[1], 0);
}
void SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		g_pImmContext->OMSetBlendState(g_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}
void SetCullMode(int nCullMode)
{
	if (nCullMode >= 0 && nCullMode < MAX_CULLMODE) {
		g_pImmContext->RSSetState(g_pRs[nCullMode]);
	}
}
void ClearScreen()
{
	// バックバッファ＆Ｚバッファのクリア
	float ClearColor[4] = { 0.417647f, 0.754902f, 0.852941f, 1.0f };
	g_pImmContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	g_pImmContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// 各ターゲットビューをレンダーターゲットに設定
	g_pImmContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
}
void Swap()
{
	// バックバッファとフロントバッファの入れ替え
	g_pSwapChain->Present(g_uSyncInterval, 0);
}

// DirectX初期化
HRESULT InitDirectX(HWND hWnd, UINT width, UINT height, bool bWindow)
{
	HRESULT hr = S_OK;
	// デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT; //! DXGI_USAGE_SHADER_INPUT…シェーダーリソースと指定使用するため
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = bWindow;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT uiDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;//DirectX11上でDirect2Dを使用するために必要
#ifdef _DEBUG
	uiDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, uiDeviceFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&g_pSwapChain, &g_pDevice11, nullptr, &g_pImmContext);
	if (FAILED(hr)) {
		return hr;
	}

	// バックバッファ生成
	hr = CreateBackBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	g_pDevice11->CreateRasterizerState(&rd, &g_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	g_pDevice11->CreateRasterizerState(&rd, &g_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	g_pDevice11->CreateRasterizerState(&rd, &g_pRs[2]);
	g_pImmContext->RSSetState(g_pRs[2]);

	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_pDevice11->CreateBlendState(&BlendDesc, &g_pBlendState[0]);
	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice11->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice11->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice11->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	// 深度ステンシルステート生成
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	g_pDevice11->CreateDepthStencilState(&dsd, &g_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	g_pDevice11->CreateDepthStencilState(&dsd2, &g_pDSS[1]);

	//hr = RenderTarget::Create(OFFSCREEN_RENDER_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	//if (FAILED(hr)) {
	//	return hr;
	//}

	return hr;
}

ID3D11DepthStencilView* GetDepthStencilView()
{
	return g_pDepthStencilView;
}


ID3D11RenderTargetView* GetMainRenderTargetView()
{
	return g_pRenderTargetView;
}