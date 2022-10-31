//==============================================================================
// Filename: Gfx_D3D12ViewPort.h
// Description: Direct3D 12のビューポートクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

/// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12ViewPort_Impl.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12Device_Impl.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Device_Impl.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ViewPort::GfxD3D12ViewPort()
{
    m_viewPort = {};
}

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12ViewPort::GfxD3D12ViewPort(const Description& desc)
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
GfxD3D12ViewPort::~GfxD3D12ViewPort()
{
}

//------------------------------------------------------------------------------
/// ビューポートの指定
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12ViewPort::Bind() const
{
    DX->GetRenderCommand<ID3D12GraphicsCommandList>()->RSSetViewports(1, &m_viewPort);
}
