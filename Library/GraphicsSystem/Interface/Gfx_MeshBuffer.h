//==============================================================================
// Filename: Gfx_MeshBuffer.h
// Description: メッシュバッファーの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __MESH_BUFFER_H__
#define __MESH_BUFFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>

#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>

// クラス定義
class GfxMeshBuffer : public GfxGraphicsObject<GfxMeshBuffer>
{
public:
    enum class TOPOLOGY
    {
        LINE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_LIST,
    };

    struct Description
    {
        void* pVertexData;  // 頂点データ
        UINT vertexCount;   // 頂点数
        UINT vertexSize;    // １頂点のサイズ

        void* pIndexData;   // インデックスデータ
        UINT indexCount;    // インデックス数
        UINT indexSize;     // 

        bool isWrite;       // 頂点の書き換えの許可フラグ
        TOPOLOGY tpology;   // トポロジー
    };

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxMeshBuffer();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxMeshBuffer();

    // 頂点バッファの生成
    virtual HRESULT CreateVertexBuffer() = 0;

    // インデックスバッファの生成
    virtual HRESULT CreateIndexBuffer() = 0;

    // 頂点情報の更新
    virtual void Write(void* pData) = 0;

    //------------------------------------------------------------------------------
    /// 頂点データの作成
    ///
    /// \param[in] tag  リソースに紐づけるタグ
    /// \param[in] desc 頂点データの設定項目
    /// 
    /// \return このクラスのポインタ
    //------------------------------------------------------------------------------
    static GfxMeshBuffer::Ptr Create(const GfxTag& tag, Description desc);

    //------------------------------------------------------------------------------

public:
    //------------------------------------------------------------------------------
    Description m_desc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc  メッシュデータの情報
    /// </summary> 
};
#endif // __MESH_BUFFER_H__
