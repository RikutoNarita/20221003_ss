//==============================================================================
// Filename: PS_Texture.h
// Description: �X�N���[���`��p�̃s�N�Z���V�F�[�_�[
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �\���̒�`
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

Texture2D<float4> g_texture : register(t0); // 0�ԃX���b�g�̃e�N�X�`��
SamplerState g_sampler : register(s0);      // 0�ԃX���b�g�̃T���v���[

// �G���g���[�|�C���g
float4 main(VS_OUTPUT pin) : SV_TARGET
{
    return float4(g_texture.Sample(g_sampler, pin.uv));
}
