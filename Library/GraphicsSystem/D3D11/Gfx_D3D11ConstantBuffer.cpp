//==============================================================================
// Filename: Gfx_D3D11ConstantBuffer.h
// Description: Direct3D 11定数バッファクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] desc 定数バッファの設定項目
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ConstantBuffer::GfxD3D11ConstantBuffer(Description desc)
: GfxConstantBuffer(desc)
{
    /* 定数バッファ作成時の注意
   定数バッファの大きさは4バイト区切り(
   4バイトアライメント)でないと作成できない
   */
    HRESULT hr;

    // 作成するバッファの情報
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = desc.size;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // バッファの作成
    ID3D11Device * pDevice = GRAPHICS->GetDevice<ID3D11Device>();
    hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

    Write(desc.pData);
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11ConstantBuffer::~GfxD3D11ConstantBuffer()
{
}

void GfxD3D11ConstantBuffer::Write(void* pData)
{
    // 定数バッファへの書き込み
    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    pContext->UpdateSubresource(m_pBuffer.Get(), 0, nullptr, pData, 0, 0);
}


void GfxD3D11ConstantBuffer::BindPS(unsigned slot)
{
    GRAPHICS->GetRenderCommand<ID3D11DeviceContext>()->PSSetConstantBuffers(slot, 1, m_pBuffer.GetAddressOf());
}
void GfxD3D11ConstantBuffer::BindVS(unsigned slot)
{
    GRAPHICS->GetRenderCommand<ID3D11DeviceContext>()->VSSetConstantBuffers(slot, 1, m_pBuffer.GetAddressOf());
}

void GfxD3D11ConstantBuffer::Bind(unsigned slot) const
{
}
