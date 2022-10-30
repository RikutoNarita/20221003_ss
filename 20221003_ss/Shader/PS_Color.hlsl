//==============================================================================
// Filename: PS_Lambert.h
// Description: �����o�[�g�V�F�[�_�[
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// ���_�V�F�[�_�[����󂯎��f�[�^�̍\����
struct PS_IN
{
  float4 pos    : SV_POSITION;  // ���W
  float2 uv     : TEXCOORD0;    // uv
  float3 normal : TEXCOORD1;    // �@��
  float4 color  : TEXCOORD2;    // �J���[
};

// �V�F�[�_�[���\�[�X
Texture2D g_texture : register(t0);
// �T���v���[
SamplerState g_sampler : register(s0);

// �����o�[�g�V�F�[�_�[�̃G���g���[�|�C���g
float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = pin.color;    
    // �e�N�X�`�����f
    //color *= g_texture.Sample(g_sampler, pin.uv);
    
    return color;
}
