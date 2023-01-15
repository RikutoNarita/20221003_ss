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

// ライトの情報
cbuffer lightInfo : register(b1)
{
    float4 lightDir; // ライトの向き
}

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
    
    return color;
}
