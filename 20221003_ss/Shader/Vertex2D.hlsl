// CPUから受け取るときの頂点の構造
struct VS_IN
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};
// ピクセルシェーダーに渡すデータの構造体 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD1;
};

//// 定数バッファ(頂点以外のデータはここで受け取る)
//cbuffer Matrix : register(b0) // b0 → バッファーの0番
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
    //// ローカル座標からワールド座標へ変換
    //vout.pos = mul(vout.pos, world);
    //// ワールド座標からカメラが原点の座標に変換 ※カメラはZの正の方向を向いている
    //vout.pos = mul(vout.pos, view);
    //// カメラからどのように見えるのか変換 ※画角、ニアクリップ、ファークリップ
    //vout.pos = mul(vout.pos, proj);
    //
    //vout.uv = vin.uv;
    //
    //vout.normal = mul(vin.normal, (float3x3)world);

    return vout;
}