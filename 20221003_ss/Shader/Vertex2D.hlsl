// CPU����󂯎��Ƃ��̒��_�̍\��
struct VS_IN
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};
// �s�N�Z���V�F�[�_�[�ɓn���f�[�^�̍\���� 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD1;
};

//// �萔�o�b�t�@(���_�ȊO�̃f�[�^�͂����Ŏ󂯎��)
//cbuffer Matrix : register(b0) // b0 �� �o�b�t�@�[��0��
//{
//    float4x4 world;
//    float4x4 view;
//    float4x4 proj;
//};

VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    vout.pos = float4(vin.pos, 1.0f);
    vout.normal = vin.normal;
    vout.uv = vin.uv;
    //vout.pos = float4(vin.pos, 1.0f);
    //// ���[�J�����W���烏�[���h���W�֕ϊ�
    //vout.pos = mul(vout.pos, world);
    //// ���[���h���W����J���������_�̍��W�ɕϊ� ���J������Z�̐��̕����������Ă���
    //vout.pos = mul(vout.pos, view);
    //// �J��������ǂ̂悤�Ɍ�����̂��ϊ� ����p�A�j�A�N���b�v�A�t�@�[�N���b�v
    //vout.pos = mul(vout.pos, proj);
    //
    //vout.uv = vin.uv;
    //
    //vout.normal = mul(vin.normal, (float3x3)world);

    return vout;
}