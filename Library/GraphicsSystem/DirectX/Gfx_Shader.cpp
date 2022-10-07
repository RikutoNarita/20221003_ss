//==============================================================================
// Filename: Gfx_Shader.cpp
// Description: シェーダーの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 警告抑止
#define _CRT_SECURE_NO_WARNINGS

// インクルード
#include <GraphicsSystem\DirectX\Gfx_Shader.h>
#include <stdio.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] kind シェーダーの種類
/// 
/// \return void
//------------------------------------------------------------------------------
GfxShader::GfxShader(Kind kind)
    : m_eKind(kind)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxShader::~GfxShader()
{
}

//------------------------------------------------------------------------------
/// シェーダーファイル(*.cso)を読み込む処理
///
/// \param[in] pFileName シェーダーファイル名
/// 
/// \return 読み込み成功時 true
//------------------------------------------------------------------------------
HRESULT GfxShader::Load(const char* pFileName)
{
    HRESULT hr = E_FAIL;

    // ファイルを読み込む
    FILE* fp;
    fp = fopen(pFileName, "rb");
    if (!fp) 
    {
        return hr;
    }

    // ファイルのサイズを調べる
    int fileSize = 0;
    fseek(fp, 0, SEEK_END); // 位置指定子を最後にもってくる
    fileSize = ftell(fp);   // ファイルのサイズを取得

    //! メモリに読み込み
    fseek(fp, 0, SEEK_SET);             // 位置指定子を最初にもってくる
    char* pData = new char[fileSize];   // ファイルサイズ分のメモリを確保
    fread(pData, fileSize, 1, fp);      // 読み込み
    fclose(fp);

    //! シェーダー作成
    hr = MakeShader(pData, fileSize);

    // 終了処理
    if (pData)
    {
        delete[] pData;
    }
    return hr;
}

//------------------------------------------------------------------------------
/// 文字列からシェーダをコンパイル
///
/// \return コンパイル成功時 true
//------------------------------------------------------------------------------
//HRESULT GfxShader::Compile(const char* pCode)
//{
//
//}
