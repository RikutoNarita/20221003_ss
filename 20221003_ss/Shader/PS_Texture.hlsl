//==============================================================================
// Filename: PS_Texture.h
// Description: スクリーン描画用のピクセルシェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 構造体定義
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

Texture2D<float4> g_texture : register(t0); // 0番スロットのテクスチャ
SamplerState g_sampler : register(s0);      // 0番スロットのサンプラー

// エントリーポイント
float4 main(VS_OUTPUT pin) : SV_TARGET
{
    return float4(g_texture.Sample(g_sampler, pin.uv));
}
