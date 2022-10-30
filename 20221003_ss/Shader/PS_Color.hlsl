//==============================================================================
// Filename: PS_Lambert.h
// Description: ランバートシェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 頂点シェーダーから受け取るデータの構造体
struct PS_IN
{
  float4 pos    : SV_POSITION;  // 座標
  float2 uv     : TEXCOORD0;    // uv
  float3 normal : TEXCOORD1;    // 法線
  float4 color  : TEXCOORD2;    // カラー
};

// シェーダーリソース
Texture2D g_texture : register(t0);
// サンプラー
SamplerState g_sampler : register(s0);

// ランバートシェーダーのエントリーポイント
float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = pin.color;    
    // テクスチャ反映
    //color *= g_texture.Sample(g_sampler, pin.uv);
    
    return color;
}
