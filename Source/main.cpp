//==============================================================================
// Filename: main.cpp
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

////! インクルード
//#include <framework.h>
//#include <main.h>
//#include <Debug\imgui\imgui.h>
//#include <Debug\imgui\imgui_impl_win32.h>
//#include <Debug\imgui\imgui_impl_dx11.h>
//#include <GraphicsSystem\DirectX\DirectX.h>
//#include <vector>
//
////! マクロ定義
//#define MAX_LOADSTRING 100
//
////! グローバル変数:
//HINSTANCE hInst;                                //! 現在のインターフェイス
//WCHAR szTitle[MAX_LOADSTRING];                  //! タイトル バーのテキスト
//WCHAR szWindowClass[MAX_LOADSTRING];            //! メイン ウィンドウ クラス名
//HWND g_hWnd;                                    //! ウィンドウ ハンドル
//
////! このコード モジュールに含まれる関数の宣言を転送します:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    // TODO: ここにコードを挿入してください。
//
//    // グローバル文字列を初期化する
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_MY20221003SS, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//    
//    // アプリケーション初期化の実行:
//    if (!InitInstance (hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    //! DirectXの初期化
//    DirectX11Manager manager;
//    HRESULT hr = S_OK;
//    hr = manager.Init(g_hWnd, hInst, nCmdShow);
//    if (FAILED(hr))
//    {
//        return FALSE;
//    }
//
//    //Shaderを作成
//    VertexShader vs;
//    PixelShader ps;
//    InputLayout il;
//    vs.Attach(manager.CreateVertexShader("Shader/2DPipeLineVS.hlsl", "vsMain"));
//    ps.Attach(manager.CreatePixelShader("Shader/2DPipeLinePS.hlsl", "psMain"));
//
//    //InputLayoutの作成
//    D3D11_INPUT_ELEMENT_DESC elem[] = {
//        { "POSITION",   0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  0,  D3D11_INPUT_PER_VERTEX_DATA,    0},
//        { "TEXCOORD",   0,  DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  12, D3D11_INPUT_PER_VERTEX_DATA,    0}
//    };
//    il.Attach(manager.CreateInputLayout(elem, 2, "Shader/2DPipeLineVS.hlsl", "vsMain"));
//
//    //頂点情報を設定
//    struct Vertex
//    {
//        XMFLOAT3 pos;
//        XMFLOAT4 col;
//    };
//    vector<Vertex> vertexs =
//    {
//        { XMFLOAT3(-0.5f,-0.5f,0), XMFLOAT4(1,0,0,1)},
//        { XMFLOAT3(0.5f,-0.5f,0), XMFLOAT4(0,1,0,1)},
//        { XMFLOAT3(0.5f, 0.5f,0), XMFLOAT4(0,0,1,1)},
//        { XMFLOAT3(-0.5f, 0.5f,0), XMFLOAT4(0,0,0,1)}
//    };
//    VertexBuffer vb;
//    vb.Attach(manager.CreateVertexBuffer(vertexs.data(), static_cast<UINT>(vertexs.size())));
//
//    //インデックス情報の設定
//    vector<UINT> idxs = { 0,1,2,0,2,3 };
//    IndexBuffer ib;
//    ib.Attach(manager.CreateIndexBuffer(idxs.data(), static_cast<UINT>(idxs.size())));
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20221003SS));
//
//    MSG msg;
//
//    // メイン メッセージ ループ:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//
//        //MainLoop
//        manager.DrawBegin();
//        //ポリゴンを書くための各種パラメータセット
//        manager.SetVertexShader(vs.Get());
//        manager.SetPixelShader(ps.Get());
//        manager.SetInputLayout(il.Get());
//        manager.SetVertexBuffer(vb.Get(), sizeof(Vertex));
//        manager.SetIndexBuffer(ib.Get());
//        //DrawCall
//        manager.DrawIndexed(static_cast<UINT>(idxs.size()));
//        manager.DrawEnd();
//    }
//
//    return (int) msg.wParam;
//}
//
//
//
////
////  関数: MyRegisterClass()
////
////  目的: ウィンドウ クラスを登録します。
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20221003SS));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20221003SS);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   関数: InitInstance(HINSTANCE, int)
////
////   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
////
////   コメント:
////
////        この関数で、グローバル変数でインスタンス ハンドルを保存し、
////        メイン プログラム ウィンドウを作成および表示します。
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する
//
//   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!g_hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(g_hWnd, nCmdShow);
//   UpdateWindow(g_hWnd);
//
//   return TRUE;
//}
//
////
////  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  目的: メイン ウィンドウのメッセージを処理します。
////
////  WM_COMMAND  - アプリケーション メニューの処理
////  WM_PAINT    - メイン ウィンドウを描画する
////  WM_DESTROY  - 中止メッセージを表示して戻る
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // 選択されたメニューの解析:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            /*HDC hdc = */BeginPaint(hWnd, &ps);
//            // TODO: HDC を使用する描画コードをここに追加してください...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// バージョン情報ボックスのメッセージ ハンドラーです。
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
//
//
//HWND GetWnd()
//{
//    return g_hWnd;
//}

//! インクルード
#include <main.h>
#include <Debug/imgui/imgui.h>
#include <Debug/imgui/imgui_impl_win32.h>
#include <Debug/imgui/imgui_impl_dx11.h>

#include <GraphicsSystem/DirectX/D3DManager.h>
//#include <GraphicsSystem/DirectX/Polygon.h>

//! ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "d3d11")

//! プロトタイプ宣言
HRESULT Init(HWND hWnd);  //! 初期化
void Uninit();            //! 終了
void Update();            //! 更新
void Draw();              //! 描画

//! エントリーポイント
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  //! 未使用宣言
    UNREFERENCED_PARAMETER(lpCmdLine);      //! 未使用宣言
    UNREFERENCED_PARAMETER(nCmdShow);       //! 未使用宣言

    //! COM初期化
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
     MessageBox(NULL, _T("COMの初期化に失敗しました。"), _T("error"), MB_OK);
     return -1;
    }

    //! インスタンス ハンドル保存
    WINDOW->SetInstance(hInstance);
    //! ウィンドウ作成
    WINDOW->Init();

    //! フレームカウント初期化
    DWORD dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
    timeBeginPeriod(1);    //! 分解能を設定
    dwExecLastTime = dwFPSLastTime = timeGetTime();
    dwCurrentTime = dwFrameCount = 0;

    //! DirectXの初期化(ウィンドウを作成してから行う)
    if (FAILED(Init(WINDOW->GetWndHandle()))) {
     return -1;
    }

    while (WINDOW->Run())
    {
        //! FPS制御
        dwCurrentTime = timeGetTime();
        if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
        {
            dwExecLastTime = dwCurrentTime;
            //! 更新処理
            Update();
            //! 描画処理
            Draw();
        }
        dwFrameCount++;
    }

    //! タイマ設定を元に戻す
    timeEndPeriod(1);

    //! 終了処理
    Uninit();

    //! ウィンドウの終了
    WINDOW->Fin();

    //! COM終了処理
    CoUninitialize();

    return 0;
}

//! 初期化処理
HRESULT Init(HWND hWnd)
{
    HRESULT hr = S_OK;

    //! DirectX初期化
    D3D->CreateInstance();
    D3D->Init(hWnd, (UINT)SCREEN_WIDTH, (UINT)SCREEN_HEIGHT);
    if (FAILED(hr)) {
        return hr;
    }

    // ポリゴン表示初期化
    //hr = CPolygon::Init(GetDevice());
    //if (FAILED(hr)) return hr;

    // 入力処理初期化
    //hr = INPUT->Init();
    //if (FAILED(hr)) return hr;

    // Imgui初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // カラーテーマ設定
    ImGui::StyleColorsClassic();
    // プラットフォーム/レンダラの初期化
    ImGui_ImplWin32_Init(hWnd);
#if 0
    ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext());
    #else

    ImGui_ImplDX11_Init(D3D->GetDevice(), D3D->GetDeviceContext());
#endif // 0


    // シェーダーの読み込み
    //SHADER->LoadAll(GetDevice());

    // カメラの初期化
    //CAMERA->Init();


    return hr;
}

// 終了処理
void Uninit()
{
    // カメラの終了処理
    //CAMERA->Uninit();

    //! シェーダー終了処理
    //SHADER->Uninit();

    // Imgui 終了
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // 入力処理終了処理
    //INPUT->Uninit();

    // ポリゴン表示終了処理
    //CPolygon::Fin();

    //--- DirectX終了処理
    //ReleaseDirectX();

    D3D->DeleteInstance();
}

//! 更新処理
void Update()
{
    //! 入力処理更新
    //INPUT->Update(); //! 必ずUpdate関数の先頭で実行
}

// 描画処理
void Draw()
{
#ifdef _DEBUG
    //! ImGui New Frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
#endif

    //ID3D11DeviceContext* pDC = GetDeviceContext();
    //ClearScreen();
    D3D->BeginDraw();

#ifdef _DEBUG
    using namespace ImGui;
    SetNextWindowSize(ImVec2(160, 160), ImGuiCond_FirstUseEver);                //! ImGuiウィンドウの初期の大きさ
    SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver, ImVec2(0, 0));   //! ImGuiウィンドウの初期の位置
    //! テスト用
    Begin("ImGuiTest");
    Text("FPS : %d", (int)(GetIO().Framerate)); //! FPS
    End();

 //! 入力情報の表示
 //INPUT->Draw();

#endif // _DEBUG

#ifdef _DEBUG

    //! Zバッファ無効(Zチェック無&Z更新無)
    //SetZBuffer(false);
    //SetBlendState(BS_ALPHABLEND);

    //! ImGui Render
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

#endif // _DEBUG

    //Swap();
    D3D->EndDraw();
}
