//==============================================================================
// Filename: Gfx_PixelShader.cpp
// Description: ピクセルシェーダーに関するクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <GraphicsSystem\DirectX\Gfx_PixelShader.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>
#include <d3dcompiler.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxPixelShader::GfxPixelShader()
 : GfxShader(GfxShader::PixelShader)
 , m_pPS(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxPixelShader::~GfxPixelShader()
{
    SAFE_RELEASE(m_pPS);
}

//------------------------------------------------------------------------------
/// シェーダーを描画に使用
///
/// \return void
//------------------------------------------------------------------------------
void GfxPixelShader::Bind()
{
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    //! ピクセルシェーダーをセット
    pContext->PSSetShader(m_pPS, nullptr, 0);
}

//------------------------------------------------------------------------------
/// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
///
/// \param[in] pData シェーダーのデータへのポインタ
/// \param[in] size データの大きさ
/// 
/// \return シェーダー作成の成否
//------------------------------------------------------------------------------
HRESULT GfxPixelShader::MakeShader(
/*[in]*/
void* pData,
/*[in]*/
UINT size)
{
    HRESULT hr;
    ID3D11Device* pDevice = D3D->GetDevice();
    //! ピクセルシェーダー作成
    hr = pDevice->CreatePixelShader(pData, size, nullptr, &m_pPS);
    return hr;
}
