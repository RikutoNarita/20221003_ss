//==============================================================================
// Filename: main.cpp
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <main.h>
#include <Debug/imgui/imgui.h>
#include <Debug/imgui/imgui_impl_win32.h>
#include <Debug/imgui/imgui_impl_dx11.h>

#include <GraphicsSystem/DirectX/Gfx_D3DManager.h>
#include <GraphicsSystem\DirectX\Gfx_Shader.h>
#include <GraphicsSystem\DirectX\Gfx_VertexShader.h>
#include <GraphicsSystem\DirectX\Gfx_PixelShader.h>
#include <GraphicsSystem\DirectX\Gfx_DXBuffer.h>
#include <GraphicsSystem\DirectX\Gfx_ConstantBuffer.h>
#include <memory>

//#include <GraphicsSystem/DirectX/Polygon.h>

//! ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "d3d11")

//! プロトタイプ宣言
HRESULT Init(HWND hWnd);  //! 初期化
void Uninit();            //! 終了
void Update();            //! 更新
void Draw();              //! 描画

//! グローバル変数
std::shared_ptr<GfxVertexShader> g_pVertex2D;
std::shared_ptr<GfxPixelShader> g_pPixel2D;
std::shared_ptr<GfxDXBuffer> g_pTriangle;
//std::shared_ptr<GfxConstantBuffer> g_pTriangle;


//! エントリーポイント
int WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
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

    // メッセージループ
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
    if (FAILED(hr))
    {
        return hr;
    }

 //! ポリゴン表示初期化
 //hr = CPolygon::Init(GetDevice());
 //if (FAILED(hr)) return hr;

 //! 入力処理初期化
 //hr = INPUT->Init();
 //if (FAILED(hr)) return hr;

    //! Imgui初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //! カラーテーマ設定
    ImGui::StyleColorsClassic();
    //! プラットフォーム/レンダラの初期化
    ImGui_ImplWin32_Init(hWnd);
#if 0
    ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext());
 #else

    ImGui_ImplDX11_Init(D3D->GetDevice(), D3D->GetDeviceContext());
#endif // 0


    //! シェーダーの読み込み
    //SHADER->LoadAll(GetDevice());

    //! カメラの初期化
    //CAMERA->Init();
    struct Vertex
    {
        float pos[3];
        float normal[3];
        float uv[2];
    };
    Vertex vtx[] =
    {
        {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    };

    // description 記述方法の設定
    GfxDXBuffer::Desc desk = {};
    desk.pVtx = vtx;    // 頂点データ
    desk.vtxCount = _countof(vtx); // 頂点のサイズ
    desk.vtxSize = sizeof(Vertex);  // 1頂点のデータサイズ
    desk.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 頂点の結び方
    //! 頂点バッファ作成
    g_pTriangle = std::make_shared<GfxDXBuffer>();
    hr = g_pTriangle->Create(desk);
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    g_pVertex2D = std::make_shared<GfxVertexShader>();
    hr = g_pVertex2D->Load("data/Vertex2D.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    g_pPixel2D = std::make_shared<GfxPixelShader>();
    hr = g_pPixel2D->Load("data/Pixel2D.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }

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

    //! 描画開始
    D3D->BeginDraw();

#ifdef _DEBUG
    using namespace ImGui;
    SetNextWindowSize(ImVec2(160, 160), ImGuiCond_FirstUseEver);                //! ImGuiウィンドウの初期の大きさ
    SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver, ImVec2(0, 0));   //! ImGuiウィンドウの初期の位置
    //! テスト用
    Begin("ImGuiTest");
    Text("FPS : %d", (int)(GetIO().Framerate)); //! FPS
    End();
#endif //! _DEBUG

    //! 各シェーダーをセット
    g_pVertex2D->Bind();
    g_pPixel2D->Bind();

    // 三角形描画
    g_pTriangle->Draw();

#ifdef _DEBUG
    //! ImGui Render
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif //! _DEBUG

    //! バックバッファとフロントバッファ入れ替え
    D3D->EndDraw();
}
