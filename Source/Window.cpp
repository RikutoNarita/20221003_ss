//==============================================================================
// Filename: WindowManager.cpp
// Description: ウィンドウ表示クラス
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <Window.h>
#include <resource.h>
#include <wingdi.h>
#include <WinUser.h>
#include <tchar.h>
#include <imm.h>
#include <Debug/imgui/imgui.h>
#include <Debug/imgui/imgui_impl_win32.h>

//! ライブラリのリンク
#pragma comment(lib, "imm32")

//! プロトタイプ
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
 HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! マクロ定義
#define CLASS_NAME  _T("AppClass")          //! ウインドウのクラス名
#define WINDOW_NAME  _T("abstract layer") //! ウインドウのキャプション名

//! 静的メンバ変数宣言
WindowManager* WindowManager::m_pWindow = nullptr;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
WindowManager::WindowManager()
: m_hWnd(nullptr), m_hInst(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
WindowManager::~WindowManager()
{
    //! ウィンドウクラスの登録を解除
    UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
    m_hWnd = nullptr;
}

//------------------------------------------------------------------------------
/// 初期化
/// 
/// \return 成功時 true
//------------------------------------------------------------------------------
bool WindowManager::Init()
{
    //! ウィンドクラス情報の設定
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex)); //! ゼロクリア

    wcex.hInstance = GetModuleHandle(NULL);                     //! ウィンドウ プロシージャを含むインスタンスへのハンドル
    wcex.lpszClassName = CLASS_NAME;                            //! ウインドウのクラス名
    wcex.lpfnWndProc = WndProc;                                 //! ウィンドウのメッセージ処理をするコールバック関数のポインタ
    wcex.style = CS_CLASSDC | CS_DBLCLKS;                       //! ウィンドウのスタイル
    wcex.cbSize = sizeof(WNDCLASSEX);                           //! 構造体のサイズ
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //! クラス アイコンへのハンドル
    wcex.hIconSm = wcex.hIcon;                                  //! クラス アイコンへのハンドル
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                 //! マウスカーソルのハンドル
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //! ウィンドウの背景色

    //! ウィンドウクラス情報の登録
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Failed to RegisterClassEx", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    //! ウィンドウの作成
    RECT rect = { 0, 0, (long)SCREEN_WIDTH, (long)SCREEN_HEIGHT };  //! ウィンドウの大きさ
    DWORD style = WS_CAPTION | WS_SYSMENU;                          //! ウィンドウスタイル
    DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;                         //! 拡張ウィンドウスタイル
    AdjustWindowRectEx(&rect, style, false, exStyle);
    m_hWnd = CreateWindowEx(exStyle, wcex.lpszClassName, WINDOW_NAME, style, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top, HWND_DESKTOP, NULL, wcex.hInstance, NULL);

    if (m_hWnd == NULL)
    {
        MessageBox(NULL, L"Failed to CreateWindowEx", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    // ウィンドウの表示
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

// メッセージループ
bool WindowManager::Run()
{
    MSG msg;
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
/// ウィンドウハンドルの取得
/// 
/// \return ウィンドウハンドル
//------------------------------------------------------------------------------
HWND WindowManager::GetWndHandle()
{
    return m_hWnd;
}

//------------------------------------------------------------------------------
/// インスタンスハンドル設定
/// 
/// \param[in] hInstance インスタンスハンドル
/// 
/// \return void
//------------------------------------------------------------------------------
void WindowManager::SetInstance(HINSTANCE hInst)
{
    m_hInst = hInst;
}

//------------------------------------------------------------------------------
/// インスタンスハンドルの取得
/// 
/// \return ウィンドウハンドル
//------------------------------------------------------------------------------
HINSTANCE WindowManager::GetInstance()
{
    return m_hInst;
}

//------------------------------------------------------------------------------
/// クラスのインスタンス取得
///
/// \return クラスのインスタンス
//------------------------------------------------------------------------------
WindowManager* WindowManager::Get()
{
    if (!m_pWindow)
    {
        m_pWindow = new WindowManager();
    }
    return m_pWindow;
}

//------------------------------------------------------------------------------
/// 終了処理
///
/// \return void
//------------------------------------------------------------------------------
void WindowManager::Fin()
{
    if (m_pWindow)
    {
        delete m_pWindow;
        m_pWindow = nullptr;
    }
}

// プロシージャ
LRESULT CALLBACK WindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // imguiプロシージャ
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
     return true;

    switch (uMsg) {
        case WM_CREATE:     //! ウィンドウが生成された
            return Get()->OnCreate(hWnd);
        case WM_DESTROY:    //! ウィンドウ破棄指示がきた
            PostQuitMessage(0); //! システムにスレッドの終了を要求
            break;
        case WM_KEYDOWN:    //! キーボードが押された
            switch (wParam) {
                case VK_ESCAPE: //! [ESC]キーが押された
                PostMessage(hWnd, WM_CLOSE, 0, 0); //! [x]が押されたように振舞う
                return 0;
                }
            break;
        case WM_MENUCHAR:
            return MNC_CLOSE << 16;   //! [Alt]+[Enter]時のBEEPを抑止
        default:
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
 

//------------------------------------------------------------------------------
/// WM_CREATEメッセージハンドラ
/// 
/// \param[in] hWnd ウィンドウハンドル
/// 
/// \return 成功時 0
//------------------------------------------------------------------------------
int WindowManager::OnCreate(HWND hWnd)
{
    //! クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
    RECT rcClnt;
    GetClientRect(hWnd, &rcClnt);
    rcClnt.right -= rcClnt.left;
    rcClnt.bottom -= rcClnt.top;
    if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
        RECT rcWnd;
        GetWindowRect(hWnd, &rcWnd);
        SIZE sizeWnd;
        sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
        sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
        SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    //! IME無効化
    ImmAssociateContext(hWnd, nullptr);

    return 0; // -1を返すとCreateWindow[Ex]が失敗する.
}