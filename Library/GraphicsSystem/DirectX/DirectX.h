//==============================================================================
// Filename: DirectX.h
// Description: DirectXの初期化
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルードガード
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

//! インクルード
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>

//!===== 列挙体定義 =====
enum EBlendState {
	BS_NONE = 0,							//! 半透明合成無し
	BS_ALPHABLEND,							//! 半透明合成
	BS_ADDITIVE,							//! 加算合成
	BS_SUBTRACTION,							//! 減算合成

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						//! カリングしない
	CULLMODE_CW,							//! 前面カリング
	CULLMODE_CCW,							//! 背面カリング

	MAX_CULLMODE
};

//!===== プロトタイプ宣言 =====
HRESULT InitDirectX(HWND hWnd, UINT width, UINT height, bool fullscreen);

ID3D11Device* GetDevice();
IDXGISwapChain* GetSwapChain();
ID3D11DeviceContext* GetDeviceContext();
HRESULT CreateBackBuffer();
void ReleaseBackBuffer();
void ReleaseDirectX();
void SetZBuffer(bool bEnable);
void SetZWrite(bool bEnable);
void SetBlendState(int nBlendState);
void SetCullMode(int nCullMode);

void ClearScreen();
void Swap();


#endif // __DIRECTX_H__
