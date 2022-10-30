//==============================================================================
// Filename: Gfx_Shader.h
// Description: Direct3D 11ピクセルシェーダー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11PixelShader.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Texture.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] kind シェーダーの種類
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D11PixelShader::GfxD3D11PixelShader(const wchar_t* fileName)
    : GfxPixelShader(KIND::KIND_PS)
{
    ID3D11Device* pDevice = GRAPHICS->GetDevice<ID3D11Device>();

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

    // 頂点シェーダーの作成
    hr = pDevice->CreatePixelShader(m_pBlob->GetBufferPointer(),
        m_pBlob->GetBufferSize(), nullptr, &m_pPS);
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_PIXEL_SHADER");
    }
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11PixelShader::~GfxD3D11PixelShader()
{
}

//------------------------------------------------------------------------------
/// ピクセルシェーダーのバインド
/// 
/// \param[in] slot レジスタ番号
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11PixelShader::Bind(unsigned int slot) const
{
    UNREFERENCED_PARAMETER(slot);

    // 定数バッファのバインド
    for (int i = 0; i < MAX_BUFFER; ++i)
    {
        if (m_buffers[i])
        {
            m_buffers[i]->BindPS(i);
        }
    }

    // テクスチャのバインド
    for (int i = 0; i < MAX_BUFFER; ++i)
    {
        if (m_textures[i])
        {
            dynamic_cast<GfxD3D11Texture*>(m_textures[i])->BindPS(i);
        }
    }

    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    pContext->PSSetShader(m_pPS.Get(), nullptr, 0);
}
