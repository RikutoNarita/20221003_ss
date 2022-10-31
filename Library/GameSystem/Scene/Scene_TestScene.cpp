﻿//==============================================================================
// Filename: Scene_TestScene.h
// Description: 描画のお試しクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GameSystem\Scene\Scene_TestScene.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>

#include <GameSystem\Object\Game_ObjCube.h>
#include <GameSystem\Object\Game_ObjSphere.h>



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
void SceneTest::Init()
{
    // キューブオブジェクトの生成
    std::shared_ptr<GameObjCube> pCube = std::make_shared<GameObjCube>();
    // オブジェクトの設定
    pCube->SetPS(GfxGraphicsResource::Find<GfxPixelShader>(PS_TEX));
    pCube->SetTexture(GfxGraphicsResource::Find<GfxTexture>(TEX_CHECKER));
    pCube->SetPos(0, 0, 0); // 座標の設定
    // オブジェクトリストに追加
    m_pObjList.push_back(pCube);

    // 球体オブジェクトの生成
    std::shared_ptr<GameObjSphere> pShere = std::make_shared<GameObjSphere>();
    // オブジェクトの設定
    pShere->SetPS(GfxGraphicsResource::Find<GfxPixelShader>(PS_TEX));
    pShere->SetTexture(GfxGraphicsResource::Find<GfxTexture>(TEX_CHECKER));
    pShere->SetPos(6.0f, 3.5f, 3); // 座標の設定
    // オブジェクトリストに追加
    m_pObjList.push_back(pShere);

    // オブジェクトの初期化
    for (const auto& obj : m_pObjList)
    {
        obj->Init();
    }
}

//------------------------------------------------------------------------------
/// グラフィックスAPIの終了処理
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Uninit()
{
    for (const auto& obj : m_pObjList)
    {
        obj->Uninit();
    }
}

//------------------------------------------------------------------------------
/// シーンの更新
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Update()
{
    for (const auto& obj : m_pObjList)
    {
        obj->Update();
    }
}

//------------------------------------------------------------------------------
/// シーンの描画
///
/// \return void
//------------------------------------------------------------------------------
void SceneTest::Draw()
{
    for (const auto& obj : m_pObjList)
    {
        obj->Draw();
    }
}