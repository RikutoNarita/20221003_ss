//==============================================================================
// Filename: Gfx_Shader.h
// Description: Direct3D 12ピクセルシェーダー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>

//------------------------------------------------------------------------------
/// コンストラクタ
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D12PixelShader::GfxD3D12PixelShader(const wchar_t* fileName)
: GfxPixelShader(KIND::KIND_PS)
{
    // エラー対応
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;
    HRESULT hr = S_OK;
    
    // ピクセルシェーダー読み込み
    hr = D3DCompileFromFile(
        fileName,                                           // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "main",                                             // エントリーポイント名
        "ps_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pBlob,                                           // ピクセルシェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス 

    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_SHADER");
    }
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12PixelShader::~GfxD3D12PixelShader()
{
}

//------------------------------------------------------------------------------
/// ピクセルシェーダーのバインド
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12PixelShader::Bind(unsigned int slot) const
{
    UNREFERENCED_PARAMETER(slot);
}
