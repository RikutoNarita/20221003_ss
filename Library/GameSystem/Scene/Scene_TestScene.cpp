//==============================================================================
// Filename: Scene_TestScene.h
// Description: 描画のお試しクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GameSystem\Scene\Scene_TestScene.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>
#include <vector>
#include <DirectXMath.h>


GfxGraphicsBinder::Ptr obj;
GfxGraphicsBinder::Ptr cube;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
SceneTest::SceneTest()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
SceneTest::~SceneTest()
{
}

//------------------------------------------------------------------------------
/// シーンの初期化
///
/// \return 初期化処理の成否
//------------------------------------------------------------------------------
bool SceneTest::Init()
{
    DirectX::XMMATRIX mat2[3];
    DirectX::XMFLOAT4X4 fmat2[3];
    mat2[0] = DirectX::XMMatrixIdentity();   // world
    mat2[0] = DirectX::XMMatrixMultiply(
        mat2[0],
        DirectX::XMMatrixTranslation(5.1f, 0.0f, 0.0f));
    mat2[1] = DirectX::XMMatrixLookAtLH(     // view
        DirectX::XMVectorSet(8, 4, 5, 0),  // カメラ座標
        DirectX::XMVectorSet(0, 0, 0, 0),   // 注視点
        DirectX::XMVectorSet(0, 1, 0, 0));  // 上方ベクトル
    mat2[2] = DirectX::XMMatrixPerspectiveFovLH( // projection
        DirectX::XMConvertToRadians(60.0f), // 画角
        16.0f / 9.0f,                       // aspect
        0.1f,                               // near
        1000.0f);                           // far
    DirectX::XMStoreFloat4x4(&fmat2[0], DirectX::XMMatrixTranspose(mat2[0]));
    DirectX::XMStoreFloat4x4(&fmat2[1], DirectX::XMMatrixTranspose(mat2[1]));
    DirectX::XMStoreFloat4x4(&fmat2[2], DirectX::XMMatrixTranspose(mat2[2]));
    // 定数バッファ作成
    GfxConstantBuffer::Description CBVdesc2 = {};
    CBVdesc2.pData = fmat2;
    CBVdesc2.size = sizeof(DirectX::XMFLOAT4X4) * 3;
    GfxConstantBuffer::Create(GfxTag("cb_pos2"), CBVdesc2);
    
    
    DirectX::XMMATRIX mat[3];
    DirectX::XMFLOAT4X4 fmat[3];
    mat[0] = DirectX::XMMatrixIdentity();   // world
    mat[1] = DirectX::XMMatrixLookAtLH(     // view
        DirectX::XMVectorSet(8, 4, 5, 0),  // カメラ座標
        DirectX::XMVectorSet(0, 0, 0, 0),   // 注視点
        DirectX::XMVectorSet(0, 1, 0, 0));  // 上方ベクトル
    mat[2] = DirectX::XMMatrixPerspectiveFovLH( // projection
        DirectX::XMConvertToRadians(60.0f), // 画角
        16.0f / 9.0f,                       // aspect
        0.1f,                               // near
        1000.0f);                           // far
    DirectX::XMStoreFloat4x4(&fmat[0], DirectX::XMMatrixTranspose(mat[0]));
    DirectX::XMStoreFloat4x4(&fmat[1], DirectX::XMMatrixTranspose(mat[1]));
    DirectX::XMStoreFloat4x4(&fmat[2], DirectX::XMMatrixTranspose(mat[2]));
    // 定数バッファ作成
    GfxConstantBuffer::Description CBVdesc = {};
    CBVdesc.pData = fmat;
    CBVdesc.size = sizeof(DirectX::XMFLOAT4X4) * 3;
    GfxConstantBuffer::Create(GfxTag(WVP_MATRIX), CBVdesc);

    // リソースのバインド
    obj = GfxGraphicsBinder::Create(GfxTag("asdf"));
    obj->BindMesh(GfxGraphicsResource::Find<GfxMeshBuffer>(GEOMETORY_CUBE));
    obj->BindPS(GfxGraphicsResource::Find<GfxPixelShader>(PS_TEX));
    obj->BindVS(GfxGraphicsResource::Find<GfxVertexShader>(VERTEX_3D));
    obj->BindConstantBuffer(GfxGraphicsResource::Find<GfxConstantBuffer>(WVP_MATRIX), GfxShader::KIND::KIND_VS, 0);
    obj->BindTexture(GfxGraphicsResource::Find<GfxTexture>(CHECKER), GfxShader::KIND::KIND_PS);
    obj->Start();

    // リソースのバインド
    cube = GfxGraphicsBinder::Create(GfxTag("binder2"));
    cube->BindMesh(GfxGraphicsResource::Find<GfxMeshBuffer>(GEOMETORY_CUBE));
    cube->BindPS(GfxGraphicsResource::Find<GfxPixelShader>(PS_TEX));
    cube->BindVS(GfxGraphicsResource::Find<GfxVertexShader>(VERTEX_3D));
    cube->BindConstantBuffer(GfxGraphicsResource::Find<GfxConstantBuffer>("cb_pos2"), GfxShader::KIND::KIND_VS, 0);
    cube->BindTexture(GfxGraphicsResource::Find<GfxTexture>(CHECKER), GfxShader::KIND::KIND_PS);
    cube->Start();

    return true;
}

//------------------------------------------------------------------------------
/// グラフィックスAPIの終了処理
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Uninit()
{
}

//------------------------------------------------------------------------------
/// シーンの更新
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Update()
{
}

//------------------------------------------------------------------------------
/// シーンの描画
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Draw()
{
    obj->Bind();

    cube->Bind();
}
