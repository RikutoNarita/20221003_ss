//==============================================================================
// Filename: main.cpp
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <Win_Main.h>
#include <CoreSystem\Input.h>

#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GameSystem\Scene\Scene_TestScene.h>

// ライブラリのリンク
#pragma comment(lib, "winmm")

// プロトタイプ宣言
//----------------------------------
/// \ アプリケーションの初期化
///
/// \param[in] hWnd　ウィンドウハンドル
///
/// \return 初期化の成否
//----------------------------------
HRESULT Init(
    /*[in]*/
    HWND hWnd);

//----------------------------------
/// \ アプリケーションの終了処理
///
/// \return void
//----------------------------------
void Uninit();

//----------------------------------
/// \ 更新
///
/// \return void
//----------------------------------
void Update();

//----------------------------------
/// \ 描画
///
/// \return void
//----------------------------------
void Draw();

// グローバル変数
SceneTest g_scene;

// エントリーポイント
int WINAPI _tWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPTSTR lpCmdLine,
    _In_        int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // 未使用宣言
    UNREFERENCED_PARAMETER(lpCmdLine);      // 未使用宣言
    UNREFERENCED_PARAMETER(nCmdShow);       // 未使用宣言

    // COM初期化
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
    {
        MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
        return -1;
    }

    // ウィンドウの初期化
    WINDOW->Init(hInstance);

    // フレームカウント初期化
    DWORD dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
    timeBeginPeriod(1);  //! 分解能を設定
    dwExecLastTime = dwFPSLastTime = timeGetTime();
    dwCurrentTime = dwFrameCount = 0;

    // APIの初期化
    if (FAILED(Init(WINDOW->GetWndHandle())))
    {
        return -1;
    }

    // メッセージループ
    while (WINDOW->Run())
    {
        // FPS制御
        dwCurrentTime = timeGetTime();
        if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
        {
            dwExecLastTime = dwCurrentTime;
            // 更新処理
            Update();
            // 描画処理
            Draw();
        }
        dwFrameCount++;
    }

    // タイマ設定を元に戻す
    timeEndPeriod(1);

    // 終了処理
    Uninit();

    //! ウィンドウの終了
    WINDOW->Fin();

    // COM終了処理
    CoUninitialize();

    return 0;
}

// 初期化処理
HRESULT Init(HWND hWnd)
{
    HRESULT hr = S_OK;

    GfxGraphicsManager::CreateInstance();
    // グラフィックスAPIの初期化
    GRAPHICS->Init(
        GfxGraphicsManager::API_KIND::DIRECT3D_11,
        hWnd,
        (UINT)SCREEN_WIDTH,
        (UINT)SCREEN_HEIGHT);

    // 入力の初期化
    INPUT->Init();

    // シーンの初期化
    g_scene.Init();

    return hr;
}

// 終了処理
void Uninit()
{
    // シーンの終了処理
    g_scene.Uninit();

    // 入力の初期化
    INPUT->Uninit();

    // グラフィックスAPI終了処理
    GfxGraphicsManager::DeleteInstance();
}

// 更新処理
void Update()
{
    // 入力処理更新
    INPUT->Update(); // 必ずUpdate関数の先頭で実行

    // シーンの更新
    g_scene.Update();
}

// 描画処理
void Draw()
{
    // 描画処理の開始
    GRAPHICS->BeginDraw();

    // シーンの描画
    g_scene.Draw();

    // 描画処理の終了
    GRAPHICS->EndDraw();
}
