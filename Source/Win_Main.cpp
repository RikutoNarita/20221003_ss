//==============================================================================
// Filename: main.cpp
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <IPlatform.h>

#include <GraphicsSystem\Interface\IGfx_Graphics.h>
#include <GameSystem\Scene\Scene_TestScene.h>

// マクロ定義
#define WINDOW_NAME  _T("abstract layer")   // ウインドウのキャプション名

// プロトタイプ宣言
//----------------------------------
/// \ アプリケーションの初期化
///
/// \return void
//----------------------------------
void Init();

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
API_KIND g_apiKind = API_KIND::DIRECT3D_11;

// エントリーポイント
int WINAPI _tWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPTSTR lpCmdLine,
    _In_        int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);      // 未使用宣言
    UNREFERENCED_PARAMETER(hPrevInstance);  // 未使用宣言
    UNREFERENCED_PARAMETER(lpCmdLine);      // 未使用宣言
    UNREFERENCED_PARAMETER(nCmdShow);       // 未使用宣言

    // プラットフォームの初期化
    IPlatform::Description desc =
    {
        SCREEN_WIDTH, SCREEN_HEIGHT, // 画面の大きさ
        WINDOW_NAME                  // タイトル名
     };
    IPlatform* pPlatform = IPlatform::Make(g_apiKind, desc);

    // APIの初期化
    Init();

    // ゲームループ
    while (pPlatform->Run())
    {
        // 更新処理
        Update();
        // 描画処理
        Draw();
    }

    // 終了処理
    Uninit();

    return 0;
}

// 初期化処理
void Init()
{
    // グラフィクスの初期化
    IGfxGraphics::Create(g_apiKind);

    // シーンの初期化
    g_scene.Init();
}

// 終了処理
void Uninit()
{
    // シーンの終了処理
    g_scene.Uninit();

    // グラフィックスAPI終了処理
    GRAPHICS->Uninit();
}

// 更新処理
void Update()
{
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
