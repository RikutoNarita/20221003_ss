//==============================================================================
// Filename: main.h
// Description: �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

// �C���N���[�h
#include <tchar.h>
#include <Win_Window.h>
#include <DirectXMath.h>

#define SCREEN_HEIGHT (720)     // ��ʂ̕�
#define SCREEN_WIDTH  (1280)    // ��ʂ̍���

// �}�N����`
#define SAFE_RELEASE(x)\
{\
    if(x)\
    {\
        (x)->Release();x=nullptr;\
    }\
}