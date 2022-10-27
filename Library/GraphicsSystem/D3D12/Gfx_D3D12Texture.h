//==============================================================================
// Filename: Gfx_Texture.h
// Description: Direct3D 12テクスチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_TEXTURE_H__
#define __D3D12_TEXTURE_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <d3d12.h>
#include <wrl\client.h>

// クラス定義
class GfxD3D12Texture : public GfxTexture
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
    GfxD3D12Texture(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12Texture();


    inline ID3D12Resource* Get() const
    {
        return m_pTextureBuffer.Get();
    }

    void Bind(unsigned slot = 0) const final
    {

    }

    void BindVS(unsigned slot) const final
    {
    }
    void BindPS(unsigned slot) const final
    {
    }


protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Resource> m_pTextureBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc      テクスチャの設定項目
    /// </summary> 
};
#endif // __TEXTURE_H__
