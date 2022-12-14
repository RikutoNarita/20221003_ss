//==============================================================================
// Filename: Gfx_PixelShader.h
// Description: ピクセルシェーダーに関するクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルードガード
#ifndef __PIXEL_SHADER_H__
#define __PIXEL_SHADER_H__

//! インクルード
#include <GraphicsSystem\DirectX\Gfx_Shader.h>
#include <string>
#include <map>

//! クラス定義
class GfxPixelShader : public GfxShader
{

public:
    //---------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxPixelShader();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxPixelShader();

    //------------------------------------------------------------------------------
    /// シェーダーを描画に使用
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Bind() override;

protected:
    //---------------------------------------------------------------------------

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
    UINT size) override;

    //---------------------------------------------------------------------------

private:

    //---------------------------------------------------------------------------
    ID3D11PixelShader* m_pPS;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pPS ピクセルシェーダー
    /// </summary> 
};

#endif //! __SHADER_H__
