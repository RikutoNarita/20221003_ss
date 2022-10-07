//==============================================================================
// Filename: VS_2D.h
// Description: スクリーン描画用の頂点シェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// CPUから受け取るときの頂点の構造
struct VS_IN
{
  float3 pos : POSITION0;       // 座標
  float3 normal : NORMAL0;      // 法線
  float2 uv : TEXCOORD0;        // uv
  float4 color : TEXCOORD1;     // カラー
};

// ピクセルシェーダーに渡すデータの構造体 
struct VS_OUT
{
  float4 pos : SV_POSITION;     // 座標
  float2 uv : TEXCOORD0;        // uv
  float3 normal : TEXCOORD1;    // 法線
  float4 color : TEXCOORD2;     // カラー
};

// 頂点シェーダーのエントリーポイント
VS_OUT main(VS_IN vin)
{
    // そのままピクセルシェーダーに値を渡すだけ
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.normal = vin.normal;
    vout.uv = vin.uv;
    vout.color = vin.color;

    return vout;
}
