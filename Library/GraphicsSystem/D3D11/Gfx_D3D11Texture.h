//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 11テクスチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_TEXTURE_H__
#define __D3D11_TEXTURE_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <d3d11.h>
#include <wrl\client.h>

// クラス定義
class GfxD3D11Texture : public GfxTexture
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] desc テクスチャの設定項目
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11Texture(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11Texture();

    void BindVS(unsigned slot) const final;
    void BindPS(unsigned slot) const final;
    void Bind(unsigned slot = 0) const final;

protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc      テクスチャの設定項目
    /// </summary> 
};
#endif // __TEXTURE_H__
