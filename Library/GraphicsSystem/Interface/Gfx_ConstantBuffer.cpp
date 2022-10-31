//==============================================================================
// Filename: Gfx_ConstantBuffer.h
// Description: 定数バッファの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>

#include <GraphicsSystem\D3D11\Gfx_D3D11ConstantBuffer.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc 定数バッファの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::GfxConstantBuffer(Description desc)
{
    m_desc = desc;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::~GfxConstantBuffer()
{
}

//------------------------------------------------------------------------------
/// 定数バッファの作成
/// 
/// \param[in] tag  リソースに紐づけるタグ
/// \param[in] desc 定数バッファの設定項目
///
/// \return このクラスのポインタ
//------------------------------------------------------------------------------
GfxConstantBuffer::Ptr GfxConstantBuffer::Create(const GfxTag& tag, Description desc)
{
    GfxConstantBuffer::Ptr pConstantBuff;

    // APIごとに生成方法を変える
    switch (GRAPHICS->GetAPIKind())
    {
    case API_KIND::DIRECT3D_11: // DX11で生成
    {
        pConstantBuff = std::make_shared<GfxD3D11ConstantBuffer>(desc);
        break;
    }
    case API_KIND::DIRECT3D_12: // DX12で生成
    {
        pConstantBuff = std::make_shared<GfxD3D12ConstantBuffer>(desc);
        break;
    }
    case API_KIND::OPEN_GL:    // OpenGLで生成
    {
        break;
    }
    case API_KIND::VULKAN:    // Vulkanで生成
    {
        break;
    }
    default: break;
    }

    // リソースに登録
    GfxGraphicsResource::Resister(tag, pConstantBuff);

    return pConstantBuff;
}
