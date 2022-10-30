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
    GfxD3D11Texture(
        /*[in]*/
        Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11Texture();

    //------------------------------------------------------------------------------
    /// テクスチャを頂点シェーダーにセットする
    ///
    /// \param[in] slot レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(unsigned slot = 0) const;

    //------------------------------------------------------------------------------
    /// テクスチャをピクセルシェーダーにセットする
    ///
    /// \param[in] slot レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(unsigned slot = 0) const;

    void Bind(unsigned slot = 0) const final;

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pTexture2D            テクスチャ2D
    /// m_pShaderResourceView   テクスチャリソースビュー
    /// m_pSamplerState         サンプラー
    /// </summary> 
};
#endif // __TEXTURE_H__
