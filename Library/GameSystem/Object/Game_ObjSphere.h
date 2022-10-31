//==============================================================================
// Filename: Game_ObjCube.h
// Description: キューブクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __OBJECT_SPHERE_H__
#define __OBJECT_SPHERE_H__

// インクルード
#include <GameSystem\Object\Game_ObjectBase.h>

// クラス定義
class GameObjSphere : public GameObjectBase
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GameObjSphere();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GameObjSphere();

    //------------------------------------------------------------------------------
    /// オブジェクトの初期化
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Init() override;

    //------------------------------------------------------------------------------
    /// オブジェクトの終了処理
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Uninit() override;

    //------------------------------------------------------------------------------
    /// オブジェクトの更新
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Update() override;

    //------------------------------------------------------------------------------
    /// オブジェクトの描画
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Draw() override;

    //------------------------------------------------------------------------------

private:

};
#endif // __OBJECT_SPHERE_H__
