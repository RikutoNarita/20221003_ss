//==============================================================================
// Filename: Gfx_D3D11ScissorRect.h
// Description: Direct3D 11のシザー矩形クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

/// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11ScissorRect_Impl.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ScissorRect::GfxD3D11ScissorRect()
{
    m_scissorRect = {};
}

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ScissorRect::GfxD3D11ScissorRect(const Description& desc)
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
GfxD3D11ScissorRect::~GfxD3D11ScissorRect()
{
}

//------------------------------------------------------------------------------
/// シザー矩形の指定
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11ScissorRect::Bind() const
{
    DX->GetRenderCommand<ID3D11DeviceContext>()->RSSetScissorRects(1, &m_scissorRect);
}
