//==============================================================================
// Filename: VS_2D.h
// Description: スクリーン描画用の頂点シェーダー
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// 構造体定義
struct VS_INPUT
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

// エントリーポイント
VS_OUTPUT main(VS_INPUT vin)
{
    VS_OUTPUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.uv = vin.uv;
    
    return vout;
}
