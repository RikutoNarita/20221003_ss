//==============================================================================
// Filename: GfxConstantBuffer.cpp
// Description: 定数バッファクラス
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <GraphicsSystem\DirectX\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
/// 
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::GfxConstantBuffer()
    : m_pBuffer(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
/// 
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::~GfxConstantBuffer()
{
    SAFE_RELEASE(m_pBuffer);
}

//------------------------------------------------------------------------------
/// 定数バッファ作成
/// 
/// \param[in] size 定数バッファの大きさ
///
/// \return 定数バッファ作成の成否
//------------------------------------------------------------------------------
HRESULT GfxConstantBuffer::Create(UINT size)
{
    /* 定数バッファ作成時の注意
    定数バッファの大きさは4バイト区切り(
    4バイトアライメント)でないと作成できない
    */
    HRESULT hr;

    // 作成するバッファの情報
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = size;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // バッファの作成
    ID3D11Device* pDevice = D3D->GetDevice();
    hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

    return hr;
}

//------------------------------------------------------------------------------
/// 定数バッファへの書き込み
/// 
/// \param[in] pData 定数バッファのデータ
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::Write(const void* pData)
{
    // 定数バッファへの書き込み
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}

//------------------------------------------------------------------------------
/// 頂点シェーダーの指定したスロットに定数バッファのデータを送る
/// 
/// \param[in] slot スロット
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::BindVS(UINT slot)
{
    /*
    定数バッファのデータを送る際、
    どの位置に格納するかを1つ目の引数(StartSlot)に
    指定する。
    hlslのコードではregister(bX)でバッファの格納
    位置を決めておく。
    */
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}

//------------------------------------------------------------------------------
/// ピクセルシェーダーの指定したスロットに定数バッファのデータを送る
/// 
/// \param[in] slot スロット
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::BindPS(UINT slot)
{
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}