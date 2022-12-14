//==============================================================================
// Filename: Gfx_Shader.h
// Description: シェーダーの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __SHADER_H__
#define __SHADER_H__

// インクルード
#include  <Win_Main.h>
#include <d3d11.h>

// クラス定義
class GfxShader
{
protected:
    //------------------------------------------------------------------------------
    enum class Kind
    {
        VertexShader = 0,
        PixelShader,
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// VertexShader 頂点シェーダー
    /// PixcelShader ピクセルシェーダー
    /// </summary>

public:
    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxShader();

    //------------------------------------------------------------------------------
    /// シェーダーファイル(*.cso)を読み込む処理
    ///
    /// \param[in] pFileName シェーダーファイル名
    /// 
    /// \return 読み込み成功時 true
    //------------------------------------------------------------------------------
    HRESULT Load(
    /*[in]*/
    const char* pFileName);

    //------------------------------------------------------------------------------
    /// シェーダーを描画に使用
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind() = 0;

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] kind シェーダーの種類
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxShader(
    /*[in]*/
    Kind kind);

    //------------------------------------------------------------------------------
    /// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
    ///
    /// \param[in] pData シェーダーのデータへのポインタ
    /// \param[in] size データの大きさ
    /// 
    /// \return シェーダー作成の成否
    //------------------------------------------------------------------------------
    virtual HRESULT MakeShader(
    /*[in]*/
    void* pData,
    /*[in]*/
    UINT size) = 0;

    //------------------------------------------------------------------------------

private:

    //------------------------------------------------------------------------------
    Kind m_eKind;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_eKind シェーダーの種類
    /// </summary> 
};

#endif //! __SHADER_H__
