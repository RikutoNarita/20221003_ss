//==============================================================================
// Filename: VS_3D.h
// Description: 3Dオブジェクト用の頂点シェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// CPUから受け取るときの頂点の構造
struct VS_IN
{
    float3 pos      : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD;
    float4 color    : COLOR;
};

// ピクセルシェーダーに渡すデータの構造体 
struct VS_OUT
{
    float4 pos      : SV_POSITION;
    float2 uv       : TEXCOORD0;
    float3 normal   : TEXCOORD1;
    float4 color    : TEXCOORD2;
};

// 変換行列の定数バッファ
cbuffer global : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};

// 頂点シェーダーのエントリーポイント
VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    // ローカル座標からワールド座標へ変換
    vout.pos = mul(vout.pos, world);
    // ワールド座標からカメラが原点の座標に変換
    vout.pos = mul(vout.pos, view);
    // カメラからどのように見えるのか変換
    vout.pos = mul(vout.pos, proj);
    
    vout.uv = vin.uv; 
    vout.color = vin.color;
    
    vout.normal = mul(vin.normal, (float3x3)world);

    return vout;
}
