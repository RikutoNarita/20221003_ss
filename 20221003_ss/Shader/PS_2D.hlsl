//==============================================================================
// Filename: PS_2D.h
// Description: スクリーン描画用のピクセルシェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 頂点シェーダーから受け取るデータの構造体
//struct PS_IN
//{
//    float4 pos : SV_POSITION;   // 座標
//    float2 uv : TEXCOORD0;      // uv
//    float3 normal : TEXCOORD1;  // 法線
//    float4 color : TEXCOORD2;   // カラー
//};
//
//// テクスチャフラグの定数バッファ
//cbuffer textureFlag : register(b0)
//{
//    int texFlag; // テクスチャの有無(0の場合はテクスチャなし)
//}
//
//// シェーダーリソース
//Texture2D g_texture : register(t0);
//
//// サンプラー
//SamplerState g_sampler : register(s0);
//
//// ピクセルシェーダーのエントリーポイント
//float4 main(PS_IN pin) : SV_TARGET
//{
//    float4 color = pin.color;
//    if (texFlag)
//    {
//        // テクスチャ反映
//        color *= g_texture.Sample(g_sampler, pin.uv);
//    }
//    return color;
//}

// 構造体定義
struct VS_OUTPUT
{
    float4 pos  : SV_POSITION;
    float2 uv   : TEXCOORD;
};

Texture2D<float4> g_texture : register(t0); // 0番スロットのテクスチャ
SamplerState g_sampler : register(s0); // 0番スロットのサンプラー

// エントリーポイント
float4 BasicPS(VS_OUTPUT pin) : SV_TARGET
{
    return float4(g_texture.Sample(g_sampler, pin.uv));
}

