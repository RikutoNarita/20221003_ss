//==============================================================================
// Filename: Platform_Windows_Impl.cpp
// Description: ウィンドウ表示クラス
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <Platfrom_Windows_Impl.h>
#include <wingdi.h>
#include <WinUser.h>
#include <tchar.h>
#include <imm.h>

// ライブラリのリンク
#pragma comment(lib, "imm32")
// ライブラリのリンク
#pragma comment(lib, "winmm")

// マクロ定義
#define CLASS_NAME  _T("AppClass")          // ウインドウのクラス名

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
PlatformWindows::PlatformWindows()
    : m_hWnd(nullptr), m_hInst(nullptr)
{
    timeBeginPeriod(1);  // 分解能を設定
    dwExecLastTime = dwFPSLastTime = timeGetTime();
    dwCurrentTime = dwFrameCount = 0;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
PlatformWindows::~PlatformWindows()
{
    // タイマ設定を元に戻す
    timeEndPeriod(1);

    // ウィンドウクラスの登録を解除
    UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
    m_hWnd = nullptr;
}

//------------------------------------------------------------------------------
/// 初期化
/// 
/// \param[in] desc ウィンドウの設定項目
/// 
/// \return 成功時 true
//------------------------------------------------------------------------------
bool PlatformWindows::Init(Description desc)
{
    //! ウィンドクラス情報の設定
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex)); // ゼロクリア

    wcex.hInstance = GetModuleHandle(NULL);                     // ウィンドウ プロシージャを含むインスタンスへのハンドル
    wcex.lpszClassName = CLASS_NAME;                            // ウインドウのクラス名
    wcex.lpfnWndProc = WndProc;                                 // ウィンドウのメッセージ処理をするコールバック関数のポインタ
    wcex.style = CS_CLASSDC | CS_DBLCLKS;                       // ウィンドウのスタイル
    wcex.cbSize = sizeof(WNDCLASSEX);                           // 構造体のサイズ
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);               // クラス アイコンへのハンドル
    wcex.hIconSm = wcex.hIcon;                                  // クラス アイコンへのハンドル
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                 // マウスカーソルのハンドル
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // ウィンドウの背景色

    // ウィンドウクラス情報の登録
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Failed to RegisterClassEx", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    // ウィンドウの作成
    RECT rect = { 0, 0, (long)desc.width, (long)desc.height };  // ウィンドウの大きさ
    DWORD style = WS_CAPTION | WS_SYSMENU;                      // ウィンドウスタイル
    DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;                     // 拡張ウィンドウスタイル
    AdjustWindowRectEx(&rect, style, false, exStyle);
    m_hWnd = CreateWindowEx(exStyle, wcex.lpszClassName,
        (LPCWSTR)desc.tileName,
        style, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        HWND_DESKTOP, NULL, wcex.hInstance, NULL);

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

//------------------------------------------------------------------------------
/// メッセージループ
/// 
/// \return 
//------------------------------------------------------------------------------
bool PlatformWindows::Run()
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
            // FPS制御
            dwCurrentTime = timeGetTime();
            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
            {
                dwExecLastTime = dwCurrentTime;
                return true;
            }
            dwFrameCount++;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
/// ウィンドウハンドルの取得
/// 
/// \return ウィンドウハンドル
//------------------------------------------------------------------------------
HWND PlatformWindows::GetWndHandle()
{
    return m_hWnd;
}

//------------------------------------------------------------------------------
/// ウィンドウプロシージャ
/// 
/// \param[in] hWnd ウィンドウハンドル
/// \param[in] uMsg 
/// \param[in] wParam 
/// \param[in] lParam 
/// 
/// \return コールバック関数やウィンドウプロシージャから返される32ビットの値
//------------------------------------------------------------------------------
LRESULT CALLBACK PlatformWindows::WndProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // imguiプロシージャ
    //if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    //  return true;

    switch (uMsg)
    {
    case WM_CREATE:         // ウィンドウが生成された
        return Get()->OnCreate(hWnd);
    case WM_DESTROY:        // ウィンドウ破棄指示がきた
        PostQuitMessage(0); // システムにスレッドの終了を要求
        break;
    case WM_KEYDOWN:        // キーボードが押された
        switch (wParam)
        {
        case VK_ESCAPE:                         // [ESC]キーが押された
            PostMessage(hWnd, WM_CLOSE, 0, 0);  // [x]が押されたように振舞う
            return 0;
        }
        break;
    case WM_MENUCHAR:
        return MNC_CLOSE << 16; //! [Alt]+[Enter]時のBEEPを抑止
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
int PlatformWindows::OnCreate(HWND hWnd)
{
    // クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
    RECT rcClnt;
    GetClientRect(hWnd, &rcClnt);
    rcClnt.right -= rcClnt.left;
    rcClnt.bottom -= rcClnt.top;
    if (rcClnt.right != static_cast<signed>(m_desc.width) ||
        rcClnt.bottom != static_cast<signed>(m_desc.height))
    {
        RECT rcWnd;
        GetWindowRect(hWnd, &rcWnd);
        SIZE sizeWnd;
        sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + m_desc.width;
        sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + m_desc.height;
        SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    // IME無効化
    ImmAssociateContext(hWnd, nullptr);

    return 0; // -1を返すとCreateWindow[Ex]が失敗する.
}
