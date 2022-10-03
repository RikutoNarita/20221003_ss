//==============================================================================
// Filename: DirectX.h
// Description: DirectX�̏�����
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! �C���N���[�h�K�[�h
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

//! �C���N���[�h
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>

//!===== �񋓑̒�` =====
enum EBlendState {
	BS_NONE = 0,							//! ��������������
	BS_ALPHABLEND,							//! ����������
	BS_ADDITIVE,							//! ���Z����
	BS_SUBTRACTION,							//! ���Z����

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,						//! �J�����O���Ȃ�
	CULLMODE_CW,							//! �O�ʃJ�����O
	CULLMODE_CCW,							//! �w�ʃJ�����O

	MAX_CULLMODE
};

//!===== �v���g�^�C�v�錾 =====
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
