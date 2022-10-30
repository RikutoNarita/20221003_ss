//==============================================================================
// Filename: Gfx_MeshBuffer.h
// Description: メッシュバッファーの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11MeshBuffer.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12MeshBuffer.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxMeshBuffer::GfxMeshBuffer()
{ 
    m_desc = {};
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxMeshBuffer::~GfxMeshBuffer()
{
}

//------------------------------------------------------------------------------
/// 頂点データの作成
///
/// \param[in] tag  リソースに紐づけるタグ
/// \param[in] desc 頂点データの設定項目
/// 
/// \return このクラスのポインタ
//------------------------------------------------------------------------------
GfxMeshBuffer::Ptr GfxMeshBuffer::Create(const GfxTag& tag, Description desc)
{
    GfxMeshBuffer::Ptr pMeshBuffer;

    // APIごとに生成方法を変える
    switch (GRAPHICS->GetAPIKind())
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11
    {
        // メッシュデータの作成
        pMeshBuffer = std::make_shared<GfxD3D11MeshBuffer>(desc);
        break;
    }
    case GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12
    {
        // メッシュデータの作成
        pMeshBuffer = std::make_shared<GfxD3D12MeshBuffer>(desc);
        break;
    }

    case GfxGraphicsManager::API_KIND::OPEN_GL: break;
    case GfxGraphicsManager::API_KIND::VULKAN: break;
    default: break;
    }

    // データの登録
    GfxGraphicsResource::Resister(tag, pMeshBuffer);

    return pMeshBuffer;
}
