//==============================================================================
// Filename: Gfx_GraphicsResourceDefault.h
// Description: デフォルトリソースの生成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//--- インクルード
#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
// 抽象化クラス
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>

#include <vector>
#include <DirectXMath.h>

struct Vertex2D
{
    float pos[3];
    float uv[2];
};

struct Vertex3D
{
    //DirectX::XMFLOAT3 pos;       // 座標
    //DirectX::XMFLOAT3 normal;    // 法線
    //DirectX::XMFLOAT2 uv;        // uv
    //DirectX::XMFLOAT4 diffuse;   // カラー
    float pos[3];       // 座標
    float normal[3];    // 法線
    float uv[2];        // uv
    float diffuse[4];   // カラー
};

// プロトタイプ宣言
void CereteVS2D();
void CreateVSGeometory();
void CreatePSTexture();
void CreatePSColor();
void CreatePSLambert();
void CreateChekerTexture();
void CreateDefaultTexture();
void CreateGeometoryCube();
void CreateGeometorySprite();
void CreateGeometorySphere();
void CreateCBDefault();

//void CreateCBWorld();
//void CreateCBViewProj();
//void CreateCBColor();
void CreateCBLight();
//void CreateGeometoryPlane();
//void CreateGeometorySpehre();

//-----------------------------------------------------------------------------
/// デフォルトリソースの作成し
///
/// \return void
//-----------------------------------------------------------------------------
void CreateGraphicsResource()
{
    // 定数バッファの作成
    CreateCBLight();
    CreateCBDefault();

    // 頂点シェーダーの作成
    CereteVS2D();
    CreateVSGeometory();
    
    // ピクセルシェーダーの作成
    CreatePSTexture();
    CreatePSColor();
    CreatePSLambert();

    // テクスチャの作成
    CreateChekerTexture();
    CreateDefaultTexture();

    // メッシュの作成
    CreateGeometoryCube();
    CreateGeometorySprite();
    CreateGeometorySphere();
}

// 定数バッファ
void CreateCBLight()
{
    DirectX::XMFLOAT4 light(-1.0f, -1.0f, -0.5f, 0.0f);
    GfxConstantBuffer::Description CBVdesc = {};
    CBVdesc.pData = &light;
    CBVdesc.size = sizeof(DirectX::XMFLOAT4);
    GfxConstantBuffer::Create(GfxTag(CB_LIGHT), CBVdesc);
}
void CreateCBDefault()
{
    unsigned char pData[256];
    for (size_t i = 0; i < 256; i++)
    {
        pData[i] = 0;
    }
    GfxConstantBuffer::Description CBVdesc = {};
    CBVdesc.pData = pData;
    CBVdesc.size = sizeof(pData);
    GfxConstantBuffer::Create(GfxTag(CB_DEFAULT), CBVdesc);
}

//--- 頂点シェーダー
void CereteVS2D()
{
    GfxShader::Compile(GfxTag(VERTEX_2D), GfxShader::KIND::KIND_VS, L"Shader/VS_2D.hlsl");
}
void CreateVSGeometory()
{
    GfxShader::Compile(GfxTag(VERTEX_3D), GfxShader::KIND::KIND_VS, L"Shader/VS_3D.hlsl");
}
//--- ピクセルシェーダー
void CreatePSTexture()
{
    GfxShader::Compile(GfxTag(PS_TEX), GfxShader::KIND::KIND_PS, L"Shader/PS_Texture.hlsl");
}
void CreatePSColor()
{
    GfxShader::Compile(GfxTag(PS_COLOR), GfxShader::KIND::KIND_PS, L"Shader/PS_Color.hlsl");
}
void CreatePSLambert()
{
    GfxShader::Compile(GfxTag(PS_LAMBERT), GfxShader::KIND::KIND_PS, L"Shader/PS_Lambert.hlsl");
}

//--- テクスチャ
// チェッカー柄
void CreateChekerTexture()
{
    // テクスチャの読込(今回はコードから生成)
    const UINT pixelSize = 32;
    GfxTexture::Description texDesc = {};
    texDesc.byteSize = sizeof(unsigned char) * 4;
    texDesc.width = pixelSize;
    texDesc.height = pixelSize;
    bool even = true; // 偶数か奇数か
    byte srcData[pixelSize * pixelSize * 4] = { 0 }; // ビットマップを黒で初期化
    for (unsigned int y = 0; y < texDesc.height; y++)
    {
        for (unsigned int x = 0; x < texDesc.width * 4; x += 4)
        {
            if (((y * texDesc.width * 4) + x) % (texDesc.width * 4) == 0)
            {
                even = !even;
            }

            srcData[(y * texDesc.width * 4) + x] = 0;      // Red
            srcData[(y * texDesc.width * 4) + x + 1] = 0;  // Blue
            srcData[(y * texDesc.width * 4) + x + 2] = 0;  // Green

            if (even)
            {
                // 一番左
                if (x <= texDesc.width / 3 * 4)
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {

                        if (x % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                        }
                    }
                }
                // 真ん中
                else if (texDesc.width * 1 / 3 * 4 <= x && x < texDesc.width * 2 / 3 * 4)
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {
                        if (x % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                        }
                    }
                }
                // 一番右
                else
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {
                        if (x % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                        }
                    }
                }
            }
            else
            {
                // 一番左
                if (x <= texDesc.width / 3 * 4)
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {

                        if ((x + 4) % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                        }
                    }
                }
                // 真ん中
                else if (texDesc.width * 1 / 3 * 4 <= x && x < texDesc.width * 2 / 3 * 4)
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {
                        if ((x + 4) % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 1] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                        }
                    }
                }
                // 一番右
                else
                {
                    // 上側
                    if (y < texDesc.height / 2)
                    {
                        if ((x + 4) % 8 == 0)
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 2] = (unsigned char)255;
                            srcData[(y * texDesc.width * 4) + x] = (unsigned char)255;
                        }
                    }
                }
            }

        }
    }
    texDesc.pData = srcData;
    GfxTexture::Create(GfxTag(TEX_CHECKER), texDesc);
}
// デフォルトテクスチャ(白)
void CreateDefaultTexture()
{
    // テクスチャの読込(今回はコードから生成)
    const UINT pixelSize = 16;
    GfxTexture::Description texDesc = {};
    texDesc.byteSize = sizeof(unsigned char) * 4;
    texDesc.width = pixelSize;
    texDesc.height = pixelSize;
    byte srcData[pixelSize * pixelSize * 4] = { 255 }; // ビットマップを黒で初期化
    
    texDesc.pData = srcData;
    GfxTexture::Create(GfxTag(TEX_DEFAULT), texDesc);
}

//--- メッシュ
// キューブ
void CreateGeometoryCube()
{
    // オブジェクトのリソースの中身を作成
    GfxMeshBuffer::Description meshDesc = {};
    
    const float side = 1.0f;
    Vertex3D vertices3D[] =
    {
        { {-side, -side, -side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side, -side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side, -side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },

        { { side, -side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side, -side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },

        { {-side,  side, -side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side, -side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side, -side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side,  side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },

        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side,  side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side,  side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side,  side,  side}, {0.0f, 0.0f, 0.0f}, {0.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },

        { {-side, -side, -side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side, -side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side, -side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side,  side,  side}, {0.0f, 0.0f, 0.0f}, {1.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },

        { {-side, -side, -side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side, -side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side, -side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { { side, -side,  side}, {0.0f, 0.0f, 0.0f}, {3.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {-side, -side,  side}, {0.0f, 0.0f, 0.0f}, {2.0f / 3, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
    };

    // インデックスバッファの作成
    std::vector<unsigned short> indexList;
    indexList.resize(_countof(vertices3D));
    for (size_t i = 0; i < indexList.size(); i++)
    {
        indexList[i] = (unsigned short)i;
    }
    for (size_t i = 0, Cnt = _countof(vertices3D); i < Cnt; i += 3)
    {
        auto& vtx0 = vertices3D[indexList[i]];
        auto& vtx1 = vertices3D[indexList[i + 1]];
        auto& vtx2 = vertices3D[indexList[i + 2]];

        //外積で法線算出
        DirectX::XMFLOAT3 v1 =
        {
            vtx1.pos[0] - vtx0.pos[0], vtx1.pos[1] - vtx0.pos[1], vtx1.pos[2] - vtx0.pos[2]
        };
        DirectX::XMFLOAT3 v2 =
        {
            vtx2.pos[0] - vtx0.pos[0], vtx2.pos[1] - vtx0.pos[1], vtx2.pos[2] - vtx0.pos[2]
        };
        const auto n = DirectX::XMVector3Normalize(
            DirectX::XMVector3Cross(
                DirectX::XMLoadFloat3(&v1), DirectX::XMLoadFloat3(&v2)));
        //データ格納
        //DirectX::XMStoreFloat3(&vertices3D[i].normal, n);
        //DirectX::XMStoreFloat3(&vertices3D[i + 1].normal, n);
        //DirectX::XMStoreFloat3(&vertices3D[i + 2].normal, n);
        DirectX::XMFLOAT3 normal;
        DirectX::XMStoreFloat3(&normal, n);
        float norm[3] = {
            normal.x, normal.y, normal.z
        };
        vtx0.normal[0] = vtx1.normal[0] = vtx2.normal[0] = norm[0];
        vtx0.normal[1] = vtx1.normal[1] = vtx2.normal[1] = norm[1];
        vtx0.normal[2] = vtx1.normal[2] = vtx2.normal[2] = norm[2];
        //vertices3D[indexList[i]].normal = norm;
        //vertices3D[indexList[i] + 1].normal =
        //vertices3D[indexList[i] + 2].normal = norm;
    }
    meshDesc.pVertexData = vertices3D;
    meshDesc.vertexCount = _countof(vertices3D);
    meshDesc.vertexSize = sizeof(Vertex3D);
    meshDesc.pIndexData = indexList.data();
    meshDesc.indexCount = (UINT)indexList.size();
    meshDesc.indexSize = sizeof(unsigned short);
    meshDesc.isWrite = true;
    meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_LIST;
    GfxMeshBuffer::Create(GfxTag(GEOMETORY_CUBE), meshDesc);
}

// スプライト
void CreateGeometorySprite()
{
    // オブジェクトのリソースの中身を作成
    Vertex2D vertices[] =
    {
        {{ -0.5f,  0.5f, 0.0f}, {0.0f, 0.0f}, },
        {{  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f}, },
        {{ -0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, },
        {{  0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}, },
        {{ -0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, },
        {{  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f}, },
    };
    unsigned short indices[] =
    {
        0,1,2,3,4,5
    };
    GfxMeshBuffer::Description meshDesc = {};
    meshDesc.pVertexData = vertices;
    meshDesc.vertexCount = _countof(vertices);
    meshDesc.vertexSize = sizeof(Vertex2D);
    meshDesc.pIndexData = indices;
    meshDesc.indexCount = _countof(indices);
    meshDesc.indexSize = sizeof(unsigned short);
    meshDesc.isWrite = true;
    meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_STRIP;
    GfxMeshBuffer::Create(GfxTag(GEOMETORY_SPRITE), meshDesc);
}

// 球体
void CreateGeometorySphere()
{
    constexpr int split = 16; // 必ず偶数
    constexpr float angle = DirectX::XMConvertToRadians(360.0f / split);
    std::vector<Vertex3D> vtx;
    for (int j = 0; j < split / 2 + 1; ++j)
    {
        float radY = angle * j;
        for (int i = 0; i <= split; ++i)
        {
            float radXZ = angle * i;
            float nx = sinf(radY) * cosf(radXZ);
            float ny = cosf(radY);
            float nz = sinf(radY) * sinf(radXZ);
            vtx.push_back(Vertex3D{
                { nx * 0.5f, ny * 0.5f, nz * 0.5f },
                { nx, ny, nz },
                { static_cast<float>(i) / split, static_cast<float>(j) / (split / 2) },
                {1,1,1,1}
                });
        }
    }
    std::vector<WORD> idx;
    for (int j = 0; j < split / 2; ++j)
    {
        for (int i = 0; i < split; ++i)
        {
            idx.push_back(((unsigned short)j + 1) * ((unsigned short)split + 1) + (unsigned short)i);
            idx.push_back((unsigned short)j       * ((unsigned short)split + 1) + (unsigned short)i);
            idx.push_back((unsigned short)j       * ((unsigned short)split + 1) + (unsigned short)i + 1);
            idx.push_back((unsigned short)j       * ((unsigned short)split + 1) + (unsigned short)i + 1);
            idx.push_back((unsigned short)(j + 1) * ((unsigned short)split + 1) + (unsigned short)i + 1);
            idx.push_back(((unsigned short)j + 1) * ((unsigned short)split + 1) + (unsigned short)i);
        }
    }

    GfxMeshBuffer::Description meshDesc = {};
    meshDesc.pVertexData = vtx.data();
    meshDesc.vertexCount = (UINT)vtx.size();
    meshDesc.vertexSize = sizeof(Vertex3D);
    meshDesc.pIndexData = idx.data();
    meshDesc.indexCount = (UINT)idx.size();
    meshDesc.indexSize = sizeof(unsigned short);
    meshDesc.isWrite = true;
    meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_LIST;
    GfxMeshBuffer::Create(GfxTag(GEOMETORY_SPHERE), meshDesc);
}

void CreateGeometoryPrism()
{
    //namespace dx = DirectX;

    //// オブジェクトのリソースの中身を作成
    //GfxMeshBuffer::Description meshDesc = {};

    //const int longDiv = 100;
    //const auto base = dx::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
    //const auto offset = dx::XMVectorSet(0.0f, 0.0f, 2.0f, 0.0f);
    //const float longitudeAngle = 2.0f * DirectX::XM_PI / longDiv;

    //// near center
    //std::vector<Vertex3D> vertices;
    //vertices.emplace_back();
    //vertices.back().pos = { 0.0f,0.0f,-1.0f };
    //const auto iCenterNear = (unsigned short)(vertices.size() - 1);
    //// far center
    //vertices.emplace_back();
    //vertices.back().pos = { 0.0f,0.0f,1.0f };
    //const auto iCenterFar = (unsigned short)(vertices.size() - 1);

    //// base vertices
    //for (int iLong = 0; iLong < longDiv; iLong++)
    //{
    //    // near base
    //    {
    //        vertices.emplace_back();
    //        auto v = dx::XMVector3Transform(
    //            base,
    //            dx::XMMatrixRotationZ(longitudeAngle * iLong)
    //        );
    //        dx::XMStoreFloat3(&vertices.back().pos, v);
    //    }
    //    // far base
    //    {
    //        vertices.emplace_back();
    //        auto v = dx::XMVector3Transform(
    //            base,
    //            dx::XMMatrixRotationZ(longitudeAngle * iLong)
    //        );
    //        v = dx::XMVectorAdd(v, offset);
    //        dx::XMStoreFloat3(&vertices.back().pos, v);
    //    }
    //}

    //// side indices
    //std::vector<unsigned short> indices;
    //for (unsigned short iLong = 0; iLong < longDiv; iLong++)
    //{
    //    const unsigned short i = iLong * 2;
    //    const auto mod = longDiv * 2;
    //    indices.push_back(i + 2);
    //    indices.push_back((i + 2) % mod + 2);
    //    indices.push_back(i + 1 + 2);
    //    indices.push_back((i + 2) % mod + 2);
    //    indices.push_back((i + 3) % mod + 2);
    //    indices.push_back(i + 1 + 2);
    //}

    //// base indices
    //for (unsigned short iLong = 0; iLong < longDiv; iLong++)
    //{
    //    const unsigned short i = iLong * 2;
    //    const auto mod = longDiv * 2;
    //    indices.push_back(i + 2);
    //    indices.push_back(iCenterNear);
    //    indices.push_back((i + 2) % mod + 2);
    //    indices.push_back(iCenterFar);
    //    indices.push_back(i + 1 + 2);
    //    indices.push_back((i + 3) % mod + 2);
    //}

    //for (size_t i = 0, Cnt = indices.size(); i < Cnt; i += 3)
    //{
    //    auto& vtx0 = vertices[indices[i]];
    //    auto& vtx1 = vertices[indices[i + 1]];
    //    auto& vtx2 = vertices[indices[i + 2]];

    //    //外積で法線算出
    //    DirectX::XMFLOAT3 v1 =
    //    {
    //        vtx1.pos.x - vtx0.pos.x, vtx1.pos.y - vtx0.pos.y, vtx1.pos.z - vtx0.pos.z
    //    };
    //    DirectX::XMFLOAT3 v2 =
    //    {
    //        vtx2.pos.x - vtx0.pos.x, vtx2.pos.y - vtx0.pos.y, vtx2.pos.z - vtx0.pos.z
    //    };
    //    const auto n = DirectX::XMVector3Normalize(
    //        DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&v1), DirectX::XMLoadFloat3(&v2)));
    //    //データ格納
    //    DirectX::XMStoreFloat3(&vertices[indices[i]].normal, n);
    //    DirectX::XMStoreFloat3(&vertices[indices[i + 1]].normal, n);
    //    DirectX::XMStoreFloat3(&vertices[indices[i + 2]].normal, n);
    //}

    //for (size_t i = 0; i < vertices.size(); i++)
    //{
    //    vertices[i].diffuse = 
    //    { (float)i / (float)vertices.size(), (float)i / (float)vertices.size(),
    //    (float)i / (float)vertices.size() ,(float)i / (float)vertices.size() };
    //}

    //for (size_t i = 0; i < vertices.size(); i++)
    //{
    //    vertices[i].uv = { (float)i / (float)vertices.size(), (float)i / (float)vertices.size() };
    //}

    ////std::move(vertices)
    ////std::move(indices)

    //meshDesc.pVertexData = vertices.data();
    //meshDesc.vertexCount = (UINT)vertices.size();
    //meshDesc.vertexSize = sizeof(Vertex3D);
    //meshDesc.pIndexData = indices.data();
    //meshDesc.indexCount = (UINT)indices.size();
    //meshDesc.indexSize = sizeof(unsigned short);
    //meshDesc.isWrite = true;
    //meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_LIST;
    //GfxMeshBuffer::Create(GfxTag(GEOMETORY_SPHERE), meshDesc);
}
