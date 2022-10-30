//==============================================================================
// Filename: Gfx_D3D12RootSigunature.h
// Description: ルートシグネチャクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12RootSignature.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12DescriptorHeap.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RootSignature::GfxD3D12RootSignature()
{
    
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12RootSignature::~GfxD3D12RootSignature()
{
}

//------------------------------------------------------------------------------
/// ルートシグネチャの作成
///
/// \param[in] pDescriptorHeap ディスクリプタヒープ
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12RootSignature::Create(GfxD3D12DescriptorHeap* pDescriptorHeap)
{
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();
    HRESULT hr = S_OK;
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;

    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 横方向の繰り返し
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 縦方向の繰り返し
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;       // 奥行きの繰り返し
    sampler.BorderColor
        = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;              // ボーダーは黒
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;         // ポイント
    sampler.MaxLOD = D3D12_FLOAT32_MAX;                       // ミップマップ最大値
    sampler.MaxLOD = 0.0f;                                    // ミップマップ最小値
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーから見える
    sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;     // リサンプリングしない

    // ルートシグネチャの設定
    D3D12_ROOT_SIGNATURE_DESC signatureDesc = {};
    signatureDesc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;   // 頂点情報がある
    signatureDesc.pParameters = pDescriptorHeap->m_rootParameters; // ルートパラメータ
    signatureDesc.NumParameters = _countof(pDescriptorHeap->m_rootParameters);       // ルートパラメータの数
    signatureDesc.pStaticSamplers = &sampler;                           // サンプラー
    signatureDesc.NumStaticSamplers = 1;                                // サンプラーの数

    // バイナリコードの作成
    hr = D3D12SerializeRootSignature(
        &signatureDesc,                         // ルートシグネチャの設定
        D3D_ROOT_SIGNATURE_VERSION_1_0,         // ルートシグネチャバージョン
        &m_pBlob,                               // ルートシグネチャのバッファー
        &pErrorBlob);                           // エラー処理
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_ROOT");
    }

    // ルートシグネチャの生成
    hr = pDevice->CreateRootSignature(
        0,                                  // ノードマスク
        m_pBlob->GetBufferPointer(),        // バッファーのアドレス
        m_pBlob->GetBufferSize(),           // バッファーのサイズ
        IID_PPV_ARGS(&m_pRootSignature));   // ルートシグネチャ
    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_ROOT");
    }
}

//------------------------------------------------------------------------------
/// ルートシグネチャのバインド
///
/// \return ルートシグネチャのポインタ
//------------------------------------------------------------------------------
void GfxD3D12RootSignature::Bind(unsigned slot) const
{
    UNREFERENCED_PARAMETER(slot);
    auto pCommandList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();
    pCommandList->SetGraphicsRootSignature(m_pRootSignature.Get());
}
