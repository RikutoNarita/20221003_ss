//==============================================================================
// Filename: Obj_ObjectBase.h
// Description: オブジェクトのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GameSystem\Object\Game_ObjCube.h>

#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>

#include <DirectXMath.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GameObjCube::GameObjCube()
{   
    m_pGraphics = GfxGraphicsBinder::Create("binder_cube");
    m_pGraphics->BindMesh(GfxGraphicsResource::Find<GfxMeshBuffer>(GEOMETORY_CUBE));
    m_pGraphics->BindVS(GfxGraphicsResource::Find<GfxVertexShader>(VERTEX_3D));
    m_pGraphics->BindPS(GfxGraphicsResource::Find<GfxPixelShader>(PS_LAMBERT));
    m_pGraphics->BindConstantBuffer(
    GfxGraphicsResource::Find<GfxConstantBuffer>(CB_LIGHT), GfxShader::KIND::KIND_PS, 1);
    //m_pGraphics->BindTexture(GfxGraphicsResource::Find<GfxTexture>(CHECKER), GfxShader::KIND::KIND_PS);
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GameObjCube::~GameObjCube()
{
}

//------------------------------------------------------------------------------
/// オブジェクトの初期化
///
/// \return void
//------------------------------------------------------------------------------
void GameObjCube::Init()
{
    // 定数バッファ作成
    DirectX::XMMATRIX mat[3];
    DirectX::XMFLOAT4X4 fmat[3];
    mat[0] = DirectX::XMMatrixIdentity();   // world
    mat[0] = DirectX::XMMatrixMultiply(mat[0],
        DirectX::XMMatrixTranslation(m_fPos[0], m_fPos[1], m_fPos[2]));

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
    GfxConstantBuffer::Description CBVdesc = {};
    CBVdesc.pData = fmat;
    CBVdesc.size = sizeof(DirectX::XMFLOAT4X4) * 3;
    GfxConstantBuffer::Ptr wvp = GfxConstantBuffer::Create(GfxTag("cb_cube_matrix"), CBVdesc);
    
    m_pGraphics->BindConstantBuffer(wvp.get(), GfxShader::KIND::KIND_VS);
    m_pGraphics->Start();
}

//------------------------------------------------------------------------------
/// オブジェクトの終了処理
///
/// \return void
//------------------------------------------------------------------------------
void GameObjCube::Uninit()
{
}

//------------------------------------------------------------------------------
/// オブジェクトの更新
///
/// \return void
//------------------------------------------------------------------------------
void GameObjCube::Update()
{
    DirectX::XMMATRIX mat[3];
    DirectX::XMFLOAT4X4 fmat[3];
    mat[0] = DirectX::XMMatrixIdentity();   // world
    mat[0] = DirectX::XMMatrixMultiply(mat[0],
        DirectX::XMMatrixTranslation(m_fPos[0], m_fPos[1], m_fPos[2]));

    mat[1] = DirectX::XMMatrixLookAtLH(     // view
        DirectX::XMVectorSet(8, 4, 5, 0),   // カメラ座標
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
    GfxConstantBuffer* pBuf = GfxGraphicsResource::Find<GfxConstantBuffer>("cb_cube_matrix");
    pBuf->Write(fmat);
}

//------------------------------------------------------------------------------
/// オブジェクトの描画
///
/// \return void
//------------------------------------------------------------------------------
void GameObjCube::Draw()
{
    m_pGraphics->Bind();
}
