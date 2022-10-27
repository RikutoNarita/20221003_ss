//==============================================================================
// Filename: VS_2D.h
// Description: �X�N���[���`��p�̒��_�V�F�[�_�[
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �\���̒�`
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

// �G���g���[�|�C���g
VS_OUTPUT main(VS_INPUT vin)
{
    VS_OUTPUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.uv = vin.uv;
    
    return vout;
}
