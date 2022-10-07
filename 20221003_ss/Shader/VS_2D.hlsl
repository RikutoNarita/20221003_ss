//==============================================================================
// Filename: VS_2D.h
// Description: �X�N���[���`��p�̒��_�V�F�[�_�[
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// CPU����󂯎��Ƃ��̒��_�̍\��
struct VS_IN
{
  float3 pos : POSITION0;       // ���W
  float3 normal : NORMAL0;      // �@��
  float2 uv : TEXCOORD0;        // uv
  float4 color : TEXCOORD1;     // �J���[
};

// �s�N�Z���V�F�[�_�[�ɓn���f�[�^�̍\���� 
struct VS_OUT
{
  float4 pos : SV_POSITION;     // ���W
  float2 uv : TEXCOORD0;        // uv
  float3 normal : TEXCOORD1;    // �@��
  float4 color : TEXCOORD2;     // �J���[
};

// ���_�V�F�[�_�[�̃G���g���[�|�C���g
VS_OUT main(VS_IN vin)
{
    // ���̂܂܃s�N�Z���V�F�[�_�[�ɒl��n������
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.normal = vin.normal;
    vout.uv = vin.uv;
    vout.color = vin.color;

    return vout;
}
