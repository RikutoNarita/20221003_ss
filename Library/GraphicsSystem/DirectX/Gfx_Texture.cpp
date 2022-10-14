//==============================================================================
// Filename: Gfx_Texture.cpp
// Description: テクスチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルード
#include <GraphicsSystem\DirectX\Gfx_Texture.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxTexture::GfxTexture()
    : m_pShaderResourceView(nullptr)
    , m_pTexture2D(nullptr)
    , m_pSamplerState(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxTexture::~GfxTexture()
{
    m_pTexture2D.Reset();
    m_pShaderResourceView.Reset();
    SAFE_RELEASE(m_pSamplerState);
}

HRESULT GfxTexture::Init()
{
    HRESULT hr = S_OK;
#ifdef DX12
#else
    // テクスチャ サンプラ生成
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    /*
    * D3D11_FILTER_MIN_MAG_MIP_POINT  ポイントサンプリング
    * D3D11_FILTER_MIN_MAG_MIP_LINEAR 線形補間
    * D3D11_FILTER_ANISOTROPIC  異方性
    */
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = D3D->GetDevice()->CreateSamplerState(&sd, &m_pSamplerState);
    if (FAILED(hr))
    {
        return hr;
    }
#endif // DX12

    return hr;
}

//------------------------------------------------------------------------------
/// ID3D11Texture11 or 12 からシェーダーリソースビューを作成する
///
/// \return 作成の成否
//------------------------------------------------------------------------------
HRESULT GfxTexture::CreateShaderResourceFromTexture2D()
{
#ifdef DX12
#else
    HRESULT hr = S_OK;
    const UINT pixelSizeX = 32;
    const UINT pixelSizeY = 32;

    D3D11_TEXTURE2D_DESC desc2D;
    desc2D.Width =  pixelSizeX;                     // テクスチャの幅
    desc2D.Height = pixelSizeY;                     // テクスチャの高さ
    desc2D.MipLevels = 1;                           // ミップマップレベルの最大数
    desc2D.ArraySize = 1;                           // テクスチャ配列内のテクスチャの数
    desc2D.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // テクスチャ形式
    desc2D.SampleDesc.Count = 1;                    // マルチサンプリングの数
    desc2D.SampleDesc.Quality = 0;
    desc2D.Usage = D3D11_USAGE_DYNAMIC;             // テクスチャの読み取りと書き込み方法
    desc2D.BindFlags = D3D11_BIND_SHADER_RESOURCE;  // 用途
    desc2D.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // 許可されるCPUアクセスの種類を指定するためのフラグ 
    desc2D.MiscFlags = 0;                           // 一般的でないリソース オプションを識別するフラグ
    
    hr = D3D->GetDevice()->CreateTexture2D(&desc2D, nullptr, m_pTexture2D.GetAddressOf());
    if (FAILED(hr))
    {
        return hr;
    }
    
    //! テクスチャ書き替え
    D3D11_MAPPED_SUBRESOURCE msr;
    D3D->GetDeviceContext()->Map(m_pTexture2D.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

    bool even = true;
    byte srcData[pixelSizeX * pixelSizeY * 4] = { 0 }; // ビットマップを黒で初期化

    for (int y = 0; y < pixelSizeY; y++)
    {
        for (int x = 0; x < pixelSizeX * 4; x+= 4)
        {
            if (((y * pixelSizeX * 4) + x) % (pixelSizeX * 4) == 0)
            {
                even = !even;
            }

            srcData[(y * pixelSizeX * 4) + x] = 0;      // Red
            srcData[(y * pixelSizeX * 4) + x + 1] = 0;  // Blue
            srcData[(y * pixelSizeX * 4) + x + 2] = 0;  // Green

            if (even)
            {
                // 一番左
                if (x <= pixelSizeX / 3 * 4)
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {

                        if (x % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                        }
                    }
                }
                // 真ん中
                else if (pixelSizeX * 1 / 3 * 4 <= x && x < pixelSizeX * 2 / 3 * 4)
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {
                        if (x % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                        }
                    }
                }
                // 一番右
                else
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {
                        if (x % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                        }
                    }
                }
            }
            else
            {
                // 一番左
                if (x <= pixelSizeX / 3 * 4)
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {

                        if ((x + 4) % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                        }
                    }
                }
                // 真ん中
                else if (pixelSizeX * 1 / 3 * 4 <= x && x < pixelSizeX * 2 / 3 * 4)
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {
                        if ((x + 4) % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x + 1] = 196;
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                        }
                    }
                }
                // 一番右
                else
                {
                    // 上側
                    if (y < pixelSizeY / 2)
                    {
                        if ((x + 4) % 8 == 0)
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * pixelSizeX * 4) + x + 2] = 196;
                            srcData[(y * pixelSizeX * 4) + x] = 196;
                        }
                    }
                }
            }
            
        }
    }

    memcpy(msr.pData, srcData, sizeof(srcData));
    D3D->GetDeviceContext()->Unmap(m_pTexture2D.Get(), 0);

    // Texture2DからShaderResourceView作成
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;
    hr = D3D->GetDevice()->CreateShaderResourceView(m_pTexture2D.Get(), &desc, &m_pShaderResourceView);
    if (FAILED(hr))
    {
        return hr;
    }
#endif // DX12

    return S_OK;
}

//------------------------------------------------------------------------------
/// シェーダーリソースを頂点シェーダーに渡す
///
/// \param[in] slot スロット
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxTexture::SetTextureVS(UINT slot)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(slot);

#else
    ID3D11ShaderResourceView* srv[] =
    {
        m_pShaderResourceView.Get()
    };
    D3D->GetDeviceContext()->VSSetShaderResources(slot, 1, srv);
#endif // DX12
}

//------------------------------------------------------------------------------
/// シェーダーリソースをピクセルシェーダーに渡す
///
/// \param[in] slot スロット
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxTexture::SetTexturePS( UINT slot)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(slot);

#else
    ID3D11ShaderResourceView* srv[] =
    {
        m_pShaderResourceView.Get()
    };
    D3D->GetDeviceContext()->PSSetShaderResources(slot, 1, srv);
#endif // DX12
}

//------------------------------------------------------------------------------
/// サンプラーをピクセルシェーダーに渡す
///
/// \param[in] slot スロット
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxTexture::SetSamplerPS(UINT slot)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(slot);

#else
    D3D->GetDeviceContext()->PSSetSamplers(slot, 1, &m_pSamplerState);
#endif // DX12
}
