//==============================================================================
// Filename: main.cpp
// Description: アプリケーションのエントリ ポイントを定義します。
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <Win_Main.h>
#include <CoreSystem\Input.h>
#include <CoreSystem\Debug/imgui\imgui.h>
#include <CoreSystem\Debug/imgui\imgui_impl_win32.h>
#include <CoreSystem\Debug/imgui\imgui_impl_dx11.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>
#include <GraphicsSystem\DirectX\Gfx_Shader.h>
#include <GraphicsSystem\DirectX\Gfx_VertexShader.h>
#include <GraphicsSystem\DirectX\Gfx_PixelShader.h>
#include <GraphicsSystem\DirectX\Gfx_DXBuffer.h>
#include <GraphicsSystem\DirectX\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\DirectX\Gfx_Texture.h>
#include <memory>
#include <vector>

// ライブラリのリンク
#pragma comment(lib, "winmm")
//#pragma comment(lib, "d3d11")

// マクロ定義
#define ASPECT_RATE     (16.0f / 9.0f)  // アスペクト比
#define NEAR_CLIP       (0.1f)          // ニアクリップ
#define FAR_CLIP        (100.0f)        // ファークリップ
#define FOV             (60.0f)         // 画角

// プロトタイプ宣言
//---------------------------------------------
/// \ アプリケーションの初期化
///
/// \param[in] hWnd　ウィンドウハンドル
///
/// \return 初期化の成否
//---------------------------------------------
HRESULT Init(
/*[in]*/
HWND hWnd);

//---------------------------------------------
/// \ アプリケーションの終了処理
///
/// \return void
//---------------------------------------------
void Uninit();

//---------------------------------------------
/// \ 更新
///
/// \return void
//---------------------------------------------
void Update();

//---------------------------------------------
/// \ 描画
///
/// \return void
//---------------------------------------------
void Draw();

// グローバル変数
#ifdef DX12
#else
std::shared_ptr<GfxVertexShader>    g_pVertex2D;
std::shared_ptr<GfxVertexShader>    g_pVertex3D;
std::shared_ptr<GfxPixelShader>     g_pPixel2D;
std::shared_ptr<GfxPixelShader>     g_pPixel3D;
std::shared_ptr<GfxDXBuffer>        g_pTriangle;
std::shared_ptr<GfxDXBuffer>        g_pCube;
std::shared_ptr<GfxConstantBuffer>  g_pWVPTransformation; // world, view, projection
std::shared_ptr<GfxConstantBuffer>  g_pLight;
std::shared_ptr<GfxConstantBuffer>  g_pTexFlag;
std::shared_ptr<GfxTexture>         g_pTestTex;

DirectX::XMFLOAT4 g_light;
DirectX::XMFLOAT3 g_cameraPos;
float g_fAngle;
float g_fDir;
#endif // DX12

//! エントリーポイント
int WINAPI _tWinMain(
_In_ HINSTANCE hInstance,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPTSTR lpCmdLine,
_In_ int nCmdShow)
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

    // インスタンス ハンドル保存
    WINDOW->SetInstance(hInstance);
    // ウィンドウ作成
    WINDOW->Init();

    // フレームカウント初期化
    DWORD dwExecLastTime, dwFPSLastTime, dwCurrentTime, dwFrameCount;
    timeBeginPeriod(1);  //! 分解能を設定
    dwExecLastTime = dwFPSLastTime = timeGetTime();
    dwCurrentTime = dwFrameCount = 0;

    // DirectXの初期化(ウィンドウを作成してから行う)
    if (FAILED(Init(WINDOW->GetWndHandle())))
    {
        return -1;
    }

    // 入力の初期化
    INPUT->Init();

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

// 初期化処理
HRESULT Init(HWND hWnd)
{
    HRESULT hr = S_OK;

    // DirectX初期化
    D3D->CreateInstance();
    D3D->Init(hWnd, (UINT)SCREEN_WIDTH, (UINT)SCREEN_HEIGHT);
    if (FAILED(hr))
    {
        return hr;
    }

#ifdef DX12
    

#else
#ifdef _DEBUG
    //// Imgui初期化
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    ////! カラーテーマ設定
    //ImGui::StyleColorsClassic();
    ////! プラットフォーム/レンダラの初期化
    //ImGui_ImplWin32_Init(hWnd);
    //ImGui_ImplDX11_Init(D3D->GetDevice(), D3D->GetDeviceContext());
    //ImGui_ImplDX12_Init();


    //フォント読込
    //io = ImGui::GetIO();
    //ImFont* font = nullptr;
    //font = io.Fonts->AddFontFromFileTTF("data/Font/BIZenAntique-Bold.ttf",
    //    16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
#endif // _DEBUG

    // 2D頂点データ作成-----------
    struct Vertex
    {
        float pos[3];
        float normal[3];
        float uv[2];
        float color[4];
    };
    Vertex vtx[] =
    {
        /*0*/{{ -0.5f,  0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{0.0f, 0.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},
        /*1*/{{  0.5f,  0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{1.0f, 0.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},
        /*3*/{{ -0.5f, -0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{0.0f, 1.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},
                                    /*                      */             /*                         */
        /*2*/{{  0.5f, -0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{1.0f, 1.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},
        /*3*/{{ -0.5f, -0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{0.0f, 1.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},
        /*1*/{{  0.5f,  0.5f, 0.0f},/* {0.0f, 0.0f, -1.0f}, */{1.0f, 0.0f},/* {1.0f, 1.0f, 1.0f, 1.0f}*/},

    };
    UINT indecies[] =
    {
        0, 1, 2, 3, 4, 5,
    };
    // description 記述方法の設定
    GfxDXBuffer::Desc desk = {};
    desk.pVtx = vtx;                                        // 頂点データ
    desk.vtxCount = _countof(vtx);                          // 頂点のサイズ
    desk.vtxSize = sizeof(Vertex);                          // 1頂点のデータサイズ
    desk.pIdx = indecies;                                   // インデックスデータ
    desk.idxCount = _countof(indecies);                     // インデックスのサイズ
    desk.idxSize = sizeof(UINT);                            // データサイズ
    desk.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;  // 頂点の結び方
    // 頂点バッファ作成
    g_pTriangle = std::make_shared<GfxDXBuffer>();
    hr = g_pTriangle->Create(desk);
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    // 3D頂点データ作成----------
    struct Vertex3D
    {
        XMFLOAT3 pos;       // 座標
        XMFLOAT3 normal;    // 法線
        XMFLOAT2 uv;        // uv
        XMFLOAT4 diffuse;   // カラー
    };
    const float side = 1.0f;
    Vertex3D vertices[] =
    {
        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3( side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(0.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        
        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side,  side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        
        { XMFLOAT3(-side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side, -side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3( side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { XMFLOAT3(-side, -side,  side), XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT2(2.0f / 3, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    };
   
    // インデックスバッファの作成
    std::vector<UINT> indexList;
    indexList.resize(_countof(vertices));
    for (size_t i = 0; i < indexList.size(); i++)
    {
        indexList[i]=(UINT)i;
    }
    for (size_t i = 0, Cnt = _countof(vertices); i < Cnt; i += 3)
    {
        auto& vtx0 = vertices[indexList[i]];
        auto& vtx1 = vertices[indexList[i + 1]];
        auto& vtx2 = vertices[indexList[i + 2]];
    
        //外積で法線算出
        DirectX::XMFLOAT3 v1 =
        {
            vtx1.pos.x - vtx0.pos.x, vtx1.pos.y - vtx0.pos.y, vtx1.pos.z - vtx0.pos.z
        };
        DirectX::XMFLOAT3 v2 =
        {
            vtx2.pos.x - vtx0.pos.x, vtx2.pos.y - vtx0.pos.y, vtx2.pos.z - vtx0.pos.z
        };
        const auto n = DirectX::XMVector3Normalize(
            DirectX::XMVector3Cross(
                DirectX::XMLoadFloat3(&v1), DirectX::XMLoadFloat3(&v2)));
        //データ格納
        DirectX::XMStoreFloat3(&vertices[i].normal, n);
        DirectX::XMStoreFloat3(&vertices[i + 1].normal, n);
        DirectX::XMStoreFloat3(&vertices[i + 2].normal, n);
    }
    // description 記述方法の設定
    GfxDXBuffer::Desc desk3D = {};
    desk3D.pVtx = vertices;                                     // 頂点データ
    desk3D.vtxCount = _countof(vertices);                       // 頂点のサイズ
    desk3D.vtxSize = sizeof(Vertex3D);                          // 1頂点のデータサイズ
    desk3D.pIdx = indexList.data();                             // インデックスデータ
    desk3D.idxCount = (UINT)indexList.size();                   // インデックスのサイズ
    desk3D.idxSize = sizeof(UINT);                              // データサイズ
    desk3D.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;    // 頂点の結び方
    g_pCube = std::make_shared<GfxDXBuffer>();
    hr = g_pCube->Create(desk3D);
    if (FAILED(hr))
    {
        return hr;
    }

    // シェーダー読み込み---------
    // 頂点シェーダーの読み込み
    g_pVertex2D = std::make_shared<GfxVertexShader>();
    hr = g_pVertex2D->Load("data/VS_2D.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    g_pVertex3D = std::make_shared<GfxVertexShader>();
    hr = g_pVertex3D->Load("data/VS_3D.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    //! ピクセルシェーダーの読み込み
    g_pPixel2D = std::make_shared<GfxPixelShader>();
    hr = g_pPixel2D->Load("data/PS_2D.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    g_pPixel3D = std::make_shared<GfxPixelShader>();
    hr = g_pPixel3D->Load("data/PS_Lambert.cso");
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    // 定数バッファ-----------
    // 変換行列の定数バッファ作成
    g_pWVPTransformation = std::make_shared<GfxConstantBuffer>();
    hr = g_pWVPTransformation->Create(sizeof(XMFLOAT4X4) * 3);
    if (FAILED(hr))
    {
        return hr;
    }

    // light
    g_pLight = std::make_shared<GfxConstantBuffer>();
    g_pLight->Create(sizeof(DirectX::XMFLOAT4));
    if (FAILED(hr))
    {
        return hr;
    }

    // テクスチャの有無フラグ
    g_pTexFlag = std::make_shared<GfxConstantBuffer>();
    g_pTexFlag->Create(sizeof(DirectX::XMFLOAT4));

    // テクスチャ生成
    g_pTestTex = std::make_shared<GfxTexture>();
    g_pTestTex->Init();
    hr = g_pTestTex->CreateShaderResourceFromTexture2D();
    if (FAILED(hr))
    {
        return hr;
    }

    // カメラの初期化
    g_fAngle = 1.0f;
    g_cameraPos.x = 10.0f * sinf(g_fAngle);
    g_cameraPos.y = 4.0f;
    g_cameraPos.z = -10.0f * cosf(g_fAngle);
    // ライトの初期化
    g_fDir = -0.7f;
    g_light = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
    g_light.y = -1.0f;
    g_light.x = 1.0f * sinf(g_fDir);
    g_light.z = 1.0f * cosf(g_fDir);
#endif // DX12

    return hr;
}

// 終了処理
void Uninit()
{
    // 入力の初期化
    INPUT->Uninit();

    // 開放処理
#ifdef DX12
#else
    g_pVertex2D->ReleaseInputLayout();

    g_pLight.reset();
    g_pWVPTransformation.reset();
    g_pTestTex.reset();
    g_pPixel3D.reset();
    g_pVertex3D.reset();
    g_pVertex2D.reset();
    g_pPixel2D.reset();
    g_pTriangle.reset();
#endif // DX12

#ifdef DX12
#else
#ifdef _DEBUG
    //// Imgui 終了
    //ImGui_ImplDX11_Shutdown();
    //ImGui_ImplWin32_Shutdown();
    //ImGui::DestroyContext();
#endif // DEBUG
#endif // DX12

    D3D->DeleteInstance();
}

// 更新処理
void Update()
{
    // 入力処理更新
    INPUT->Update(); // 必ずUpdate関数の先頭で実行

#ifdef DX12
#else
    if (INPUT->GetKeyPress(DIK_LEFT))
    {
        g_fAngle -= 0.01f;
    }
    if (INPUT->GetKeyPress(DIK_RIGHT))
    {
        g_fAngle += 0.01f;
    }

    g_cameraPos.x = 10.0f * sinf(g_fAngle);
    g_cameraPos.z = -10.0f * cosf(g_fAngle);

    if (INPUT->GetKeyPress(DIK_A))
    {
        g_fDir -= 0.01f;
    }
    if (INPUT->GetKeyPress(DIK_D))
    {
        g_fDir += 0.01f;
    }
    g_light.x = 1.0f * sinf(g_fDir);
    g_light.z = 1.0f * cosf(g_fDir);
#endif // DX12
}

// 描画処理
void Draw()
{
//#ifdef DX12
//#else
//#ifdef _DEBUG
//    //! ImGui New Frame
//    ImGui_ImplDX11_NewFrame();
//    ImGui_ImplWin32_NewFrame();
//    ImGui::NewFrame();
//#endif
//#endif // DX12

    // 描画開始
    D3D->BeginDraw();

//#ifdef DX12
//#else
//#ifdef _DEBUG
//    using namespace ImGui;
//    SetNextWindowSize(ImVec2(160, 160), ImGuiCond_FirstUseEver);                // ImGuiウィンドウの初期の大きさ
//    SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver, ImVec2(0, 0));   // ImGuiウィンドウの初期の位置
//    //! テスト用
//    Begin(reinterpret_cast<const char*>(u8"test"));
//    Text("FPS : %d", (int)(GetIO().Framerate)); //! FPS
//    Text("Camera Pos (%2.1f, %2.1f, %2.1f)", g_cameraPos.x, g_cameraPos.y, g_cameraPos.z);
//    End();
//#endif //! _DEBUG
//#endif // DX12

#ifdef DX12
    D3D->TestDraw();
#else
    // 2D描画----------------
    // 各シェーダーをセット
    g_pVertex2D->Bind();
    g_pPixel2D->Bind();
    int texFlag = true;
    g_pTexFlag->Write(&texFlag);
    g_pTexFlag->BindPS(0);
    // テクスチャをセット
    g_pTestTex->SetTexturePS(0);
    // サンプラーをセット
    g_pTestTex->SetSamplerPS(0);
    // 三角形描画
    g_pTriangle->Draw();
    
    // 3D描画----------------
    // 各シェーダーをセット
    g_pVertex3D->Bind();
    g_pPixel3D->Bind();
    // 変換行列の設定
    XMFLOAT4X4 matrix[3];
    XMMATRIX workMatrix[3];
    // world
    workMatrix[0] = DirectX::XMMatrixIdentity();
    // view
    workMatrix[1] = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(g_cameraPos.x, g_cameraPos.y, g_cameraPos.z, 0.0f), // カメラ位置
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),   // 注視点
        DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));  // 上方ベクトル
    // projection
    workMatrix[2] = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(FOV),
        ASPECT_RATE,
        NEAR_CLIP,
        FAR_CLIP);
    // 転置行列（シェーダーに渡すため）
    DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(workMatrix[0]));
    DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixTranspose(workMatrix[1]));
    DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixTranspose(workMatrix[2]));
    // 定数バッファに書き込み
    g_pWVPTransformation->Write(matrix);
    g_pWVPTransformation->BindVS(0);
    
    // ライトの設定
    g_pLight->Write(&g_light);
    g_pLight->BindPS(0);
    
    // テクスチャをセット
    texFlag = true;
    g_pTexFlag->Write(&texFlag);
    g_pTexFlag->BindPS(1); // register1
    g_pTestTex->SetTexturePS(0);
    // サンプラーをセット
    g_pTestTex->SetSamplerPS(0);
    /// 描画
    g_pCube->Draw();
#endif // DX12

//#ifdef DX12
//#else
//#ifdef _DEBUG
//    //! ImGui Render
//    ImGui::Render();
//    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
//#endif //! _DEBUG
//#endif // DX12

    //! バックバッファとフロントバッファ入れ替え
    D3D->EndDraw();
}
