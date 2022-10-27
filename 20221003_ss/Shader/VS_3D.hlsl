//==============================================================================
// Filename: VS_3D.h
// Description: 3D�I�u�W�F�N�g�p�̒��_�V�F�[�_�[
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// CPU����󂯎��Ƃ��̒��_�̍\��
struct VS_IN
{
    float3 pos      : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD;
    float4 color    : COLOR;
};

// �s�N�Z���V�F�[�_�[�ɓn���f�[�^�̍\���� 
struct VS_OUT
{
    float4 pos      : SV_POSITION;
    float2 uv       : TEXCOORD0;
    float3 normal   : TEXCOORD1;
    float4 color    : TEXCOORD2;
};

// �ϊ��s��̒萔�o�b�t�@
cbuffer global : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};

// ���_�V�F�[�_�[�̃G���g���[�|�C���g
VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    // ���[�J�����W���烏�[���h���W�֕ϊ�
    vout.pos = mul(vout.pos, world);
    // ���[���h���W����J���������_�̍��W�ɕϊ�
    vout.pos = mul(vout.pos, view);
    // �J��������ǂ̂悤�Ɍ�����̂��ϊ�
    vout.pos = mul(vout.pos, proj);
    
    vout.uv = vin.uv; 
    vout.color = vin.color;
    
    vout.normal = mul(vin.normal, (float3x3)world);

    return vout;
}
