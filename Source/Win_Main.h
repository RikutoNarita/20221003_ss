//==============================================================================
// Filename: main.h
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#pragma once

// インクルード
#include <tchar.h>
#include <Platfrom_Windows_Impl.h>
#include <DirectXMath.h>
#include <debugapi.h>

#define SCREEN_HEIGHT (720)     // 画面の幅
#define SCREEN_WIDTH  (1280)    // 画面の高さ

// マクロ定義
#define SAFE_RELEASE(x)\
{\
    if(x)\
    {\
        (x)->Release();x=nullptr;\
    }\
}
