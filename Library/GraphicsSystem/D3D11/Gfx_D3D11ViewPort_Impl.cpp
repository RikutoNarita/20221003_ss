//==============================================================================
// Filename: Gfx_D3D11ViewPort.h
// Description: Direct3D 11のビューポートクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

/// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11ViewPort_Impl.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ViewPort::GfxD3D11ViewPort()
{
	m_viewPort = {};
}

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ViewPort::GfxD3D11ViewPort(const Description& desc)
{
	m_viewPort.Width = desc.width;
	m_viewPort.Height = desc.height;
	m_viewPort.TopLeftX = desc.TopLeftX;
	m_viewPort.TopLeftY = desc.TopLeftY;
	m_viewPort.MaxDepth = desc.MaxDepth;
	m_viewPort.MinDepth = desc.MinDepth;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ViewPort::~GfxD3D11ViewPort()
{
}

//------------------------------------------------------------------------------
/// ビューポートの指定
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D11ViewPort::Bind() const
{
	GRAPHICS->GetRenderCommand<ID3D11DeviceContext>()->RSSetViewports(1, &m_viewPort);
}
