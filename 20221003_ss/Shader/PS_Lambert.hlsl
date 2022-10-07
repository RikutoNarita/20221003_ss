//==============================================================================
// Filename: PS_Lambert.h
// Description: ランバートシェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 頂点シェーダーから受け取るデータの構造体
struct PS_IN
{
  float4 pos : SV_POSITION;     // 座標
  float2 uv : TEXCOORD0;        // uv
  float3 normal : TEXCOORD1;    // 法線
  float4 color : TEXCOORD2;     // カラー
};

// ライトの情報
cbuffer lightInfo : register(b0)
{
    float4 lightDir; // ライトの向き
}

// テクスチャフラグの定数バッファ
cbuffer textureFlag : register(b1)
{
    int texFlag; // テクスチャの有無(0の場合はテクスチャなし)
}

// シェーダーリソース
Texture2D g_texture : register(t0);

// サンプラー
SamplerState g_sampler : register(s0);

// ランバートシェーダーのエントリーポイント
float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = pin.color;    
    // 法線の正規化
    float3 nrm = normalize(pin.normal);
    // ライトの向きの正規化（計算上向きを逆転させる）
    float3 light = normalize(-float3(lightDir.x, lightDir.y, lightDir.z));
    // 影の度合いを計算
    float sahdow = dot(nrm, light);
    // 色に反映
    color *= sahdow;
    
    if (texFlag)
    {
        // テクスチャ反映
        color *= g_texture.Sample(g_sampler, pin.uv);
    }
    
    return color;
}
