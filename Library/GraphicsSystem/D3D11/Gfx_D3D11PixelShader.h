//==============================================================================
// Filename: Gfx_Shader.h
// Description: Direct3D 11ピクセルシェーダー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_PIXEL_SHADER_H__
#define __D3D11_PIXEL_SHADER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d11.h>

// クラス定義
class GfxD3D11PixelShader : public GfxPixelShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///

    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11PixelShader(const wchar_t* fileName);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11PixelShader();

    //------------------------------------------------------------------------------
    /// ピクセルシェーダーのバインド
    /// 
    /// \param[in] slot レジスタ番号
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(
        /*[in]*/
        unsigned int slot = 0) const final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPS;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPS       ピクセルシェーダー
    /// </summary> 
};
#endif // __D3D11_PIXEL_SHADER_H__
