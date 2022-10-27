//==============================================================================
// Filename: Gfx_Texture.h
// Description: テクスチャの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Texture.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Texture.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc テクスチャの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxTexture::GfxTexture(Description desc)
{
    m_desc = desc;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxTexture::~GfxTexture()
{
}

//------------------------------------------------------------------------------
/// テクスチャデータの作成
/// 
/// \param[in] tag  リソースに紐づけるタグ
/// \param[in] desc テクスチャの設定項目
///
/// \return このクラスのポインタ
//------------------------------------------------------------------------------
GfxTexture::Ptr GfxTexture::Create(const GfxTag& tag, Description desc)
{
    GfxTexture::Ptr pTexture;

    switch (GRAPHICS->GetAPIKind())
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11: // DX11で生成
    {
        pTexture = std::make_shared<GfxD3D11Texture>(desc);
        break;
    }
    case GfxGraphicsManager::API_KIND::DIRECT3D_12: // DX12で生成
    {
        pTexture = std::make_shared<GfxD3D12Texture>(desc);
        break;
    }
    case GfxGraphicsManager::API_KIND::OPEN_GL:    // OpenGLで生成
    {
        break;
    }
    case GfxGraphicsManager::API_KIND::VULKAN:     // Vulkanで生成
    {
        break;
    }
    default: break;
    }

    // リソースに登録
    GfxGraphicsResource::Resister(GfxTag(tag), pTexture);

    return pTexture;
}
