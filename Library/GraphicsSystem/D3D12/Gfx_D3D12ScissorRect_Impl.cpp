//==============================================================================
// Filename: Gfx_D3D12ScissorRect.h
// Description: Direct3D 12のシザー矩形クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

/// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12ScissorRect_Impl.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ScissorRect::GfxD3D12ScissorRect()
{
    m_scissorRect = {};
}

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ScissorRect::GfxD3D12ScissorRect(const Description& desc)
{
    m_scissorRect.left = desc.left;
    m_scissorRect.right = desc.right;
    m_scissorRect.top = desc.top;
    m_scissorRect.bottom = desc.bottom;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ScissorRect::~GfxD3D12ScissorRect()
{
}

//------------------------------------------------------------------------------
/// シザー矩形の指定
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12ScissorRect::Bind() const
{
    GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>()->RSSetScissorRects(1, &m_scissorRect);
}
