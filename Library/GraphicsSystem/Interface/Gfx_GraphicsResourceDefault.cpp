#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>

#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>

#include <DirectXMath.h>
#include <vector>

struct Vertex2D
{
    float pos[3];
    float uv[2];
};

struct Vertex3D
{
    DirectX::XMFLOAT3 pos;       // 座標
    DirectX::XMFLOAT3 normal;    // 法線
    DirectX::XMFLOAT2 uv;        // uv
    DirectX::XMFLOAT4 diffuse;   // カラー
};

// プロトタイプ宣言
void CereteVS2D();
void CreateVSGeometory();

void CereatePS2D();
void CreatePSColor();
void CreatePSLambert();

void CreateChekerTexture();
void CreateDefaultTexture();


void CreateGeometoryCube();
void CreateGeometorySprite();

void CreateCBDefault();
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

//void CreateCBWorld();
//void CreateCBViewProj();
//void CreateCBColor();
//void CreateCBLight();
//void CreateGeometoryPlane();
//void CreateGeometorySpehre();




// リソースの生成
void CreateGraphicsResource()
{
    // 定数バッファの作成
    CreateCBDefault();

    // 頂点シェーダーの作成
    CereteVS2D();
    CreateVSGeometory();
    
    // ピクセルシェーダーの作成
    CereatePS2D();
    CreatePSColor();
    CreatePSLambert();

    // テクスチャの作成
    CreateChekerTexture();
    CreateDefaultTexture();

    // メッシュの作成
    CreateGeometoryCube();
    CreateGeometorySprite();
}


//--- シェーダー
void CereteVS2D()
{
    GfxShader::Compile(GfxTag(VERTEX_2D), GfxShader::KIND::KIND_VS, L"Shader/VS_2D.hlsl");
}
void CreateVSGeometory()
{
    GfxShader::Compile(GfxTag(VERTEX_3D), GfxShader::KIND::KIND_VS, L"Shader/VS_3D.hlsl");
}
void CereatePS2D()
{
    GfxShader::Compile(GfxTag(PIXEL_2D), GfxShader::KIND::KIND_PS, L"Shader/PS_2D.hlsl");
}
void CreatePSColor()
{
    GfxShader::Compile(GfxTag(PS_COLOR), GfxShader::KIND::KIND_PS, L"Shader/PS_Color.hlsl");
}
void CreatePSLambert()
{
    GfxShader::Compile(GfxTag(LAMBERT), GfxShader::KIND::KIND_PS, L"Shader/PS_Lambert.hlsl");
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
    for (int y = 0; y < texDesc.height; y++)
    {
        for (int x = 0; x < texDesc.width * 4; x += 4)
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
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x] = 456;
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
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
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
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
                            srcData[(y * texDesc.width * 4) + x] = 456;
                    }
                    // 下側
                    else
                    {
                        if (x % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
                            srcData[(y * texDesc.width * 4) + x] = 456;
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
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x] = 456;
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
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
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 1] = 456;
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
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
                            srcData[(y * texDesc.width * 4) + x] = 456;
                    }
                    // 下側
                    else
                    {
                        if ((x + 4) % 8 == 0)
                        {
                            srcData[(y * texDesc.width * 4) + x + 2] = 456;
                            srcData[(y * texDesc.width * 4) + x] = 456;
                        }
                    }
                }
            }

        }
    }
    texDesc.pData = srcData;
    GfxTexture::Create(GfxTag(CHECKER), texDesc);
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
            vtx1.pos.x - vtx0.pos.x, vtx1.pos.y - vtx0.pos.y, vtx1.pos.z - vtx0.pos.z
        };
        DirectX::XMFLOAT3 v2 =
        {
            vtx2.pos.x - vtx0.pos.x, vtx2.pos.y - vtx0.pos.y, vtx2.pos.z - vtx0.pos.z
        };
        const auto n = DirectX::XMVector3Normalize(
            DirectX::XMVector3Cross(
                DirectX::XMLoadFloat3(&v1), DirectX::XMLoadFloat3(&v2)));
        //データ格納
        DirectX::XMStoreFloat3(&vertices3D[i].normal, n);
        DirectX::XMStoreFloat3(&vertices3D[i + 1].normal, n);
        DirectX::XMStoreFloat3(&vertices3D[i + 2].normal, n);
    }
    meshDesc.pVertexData = vertices3D;
    meshDesc.vertexCount = _countof(vertices3D);
    meshDesc.vertexSize = sizeof(Vertex3D);
    meshDesc.pIndexData = indexList.data();
    meshDesc.indexCount = indexList.size();
    meshDesc.indexSize = sizeof(unsigned short);
    meshDesc.isWrite = true;
    meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_LIST;
    GfxMeshBuffer::Create(GfxTag(GEOMETORY_CUBE), meshDesc);
}

// スプライト
void CreateGeometorySprite()
{
    // オブジェクトのリソースの中身を作成
    GfxMeshBuffer::Description meshDesc = {};
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
    meshDesc.pVertexData = vertices;
    meshDesc.vertexCount = _countof(vertices);
    meshDesc.vertexSize = sizeof(Vertex2D);
    meshDesc.pIndexData = indices;
    meshDesc.indexCount = _countof(indices);
    meshDesc.indexSize = sizeof(unsigned short);
    meshDesc.isWrite = true;
    meshDesc.tpology = GfxMeshBuffer::TOPOLOGY::TRIANGLE_STRIP;
    GfxMeshBuffer::Create(GfxTag(GEOMETORY_CUBE), meshDesc);
}
