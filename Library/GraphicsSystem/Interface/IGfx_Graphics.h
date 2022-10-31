//==============================================================================
// Filename: Gfx_Graphics.h
// Description: 描画管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

// インクルード
#include <memory>
#include <IPlatform.h>

// マクロ定義
#define GRAPHICS (IGfxGraphics::Get())

// クラス定義
class IGfxGraphics
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    IGfxGraphics() {}
    
    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~IGfxGraphics() {}

    //------------------------------------------------------------------------------
    /// グラフィックスAPIの初期化
    ///
    /// \param[in] width    ウィンドウの幅
    /// \param[in] height   ウィンドウの高さ
    ///
    /// \return 初期化処理の成否
    //------------------------------------------------------------------------------
    virtual void Init(
        /*[in]*/
        int width,
        /*[in]*/
        int height) = 0;

    //------------------------------------------------------------------------------
    /// グラフィックスAPIの終了処理
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Uninit() = 0;

    //------------------------------------------------------------------------------
    /// 描画の開始(バックバッファ＆Ｚバッファのクリア)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void BeginDraw() = 0;

    //------------------------------------------------------------------------------
    /// 描画の修了(バックバッファとフロントバッファの入れ替え)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void EndDraw() = 0;

    //------------------------------------------------------------------------------
    /// グラフィックスの生成
    ///
    /// \param[in]
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    static void Create(
        /*[in]*/
        API_KIND apiKind);

    //------------------------------------------------------------------------------
    /// インスタンスの取得
    ///
    /// \return インスタンス
    //------------------------------------------------------------------------------
    static IGfxGraphics* Get()
    {
        return m_pGraphics.get();
    }

    //------------------------------------------------------------------------------
    /// APIの種類の取得
    ///
    /// \return APIの種類
    //------------------------------------------------------------------------------
    static API_KIND GetAPIKind()
    {
        return m_eAPIKind;
    }

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    static std::unique_ptr<IGfxGraphics> m_pGraphics;
    static API_KIND     m_eAPIKind;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pGraphics         クラスのインスタンス
    /// m_eAPIKind          APIの種類
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
