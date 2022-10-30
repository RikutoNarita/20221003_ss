//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: リソースをバインドするクラスのベースクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11GraphiccsBinder.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12GraphiccsBinder.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsBinder::GfxGraphicsBinder()
    : m_pMeshBuffer(nullptr), m_pVS(nullptr), m_pPS(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsBinder::~GfxGraphicsBinder()
{
}

//------------------------------------------------------------------------------
/// リソースバインダーの作成
///
/// \pramga[in] tag リソース紐づけるタグ
/// 
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsBinder::Ptr GfxGraphicsBinder::Create(const GfxTag& tag)
{
    GfxGraphicsBinder::Ptr pBinder;

    // APIごとに作成するバインダーを変える
    switch (GRAPHICS->GetAPIKind())
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11
    {
        pBinder = std::make_shared<GfxD3D11GraphicsBinder>();
        break;
    }
    case GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12
    {
        pBinder = std::make_shared<GfxD3D12GraphicsBinder>();
        break;
    }

    case GfxGraphicsManager::API_KIND::OPEN_GL: break;
    case GfxGraphicsManager::API_KIND::VULKAN: break;
    default: break;
    }

    // リソースリストに登録
    GfxGraphicsResource::Resister(tag, pBinder);

    return pBinder;
}
