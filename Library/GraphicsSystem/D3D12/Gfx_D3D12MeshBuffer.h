//==============================================================================
// Filename: Gfx_D3D12MeshBuffer.h
// Description: Direct3D 12メッシュバッファー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_MESH_BUFFER_H__
#define __D3D12_MESH_BUFFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>

#include <wrl\client.h>
#include <d3d12.h>

// クラス定義
class GfxD3D12MeshBuffer : public GfxMeshBuffer
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] shader
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12MeshBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12MeshBuffer();

    HRESULT CreateVertexBuffer() final;

    HRESULT CreateIndexBuffer() final;

    void Write(void* pData) final;

    void Bind(unsigned int slot) const final;

    /*void BindPS(GfxShader* pPS) final;
                                
    void BindVS(GfxShader* pVS) final;


    void Draw(int indexCount = 0) final;

    HRESULT Start() const final;


    void BindConstantBuffer(
    GfxConstantBuffer* pConstantBuffer,
    GfxConstantBuffer::Shader shader,
    unsigned slot) final;

    void BindTexture(GfxTexture* pTex, GfxShader::KIND shader, unsigned slot = 0) override;*/

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    

    D3D12_VERTEX_BUFFER_VIEW                    m_vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW                     m_indexBufferView;
    Microsoft::WRL::ComPtr<ID3D12Resource>      m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D12Resource>      m_pIndexBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPipelineState    パイプラインステート
    /// m_pRootSignature    ルートシグネチャ
    /// m_vertexBufferView  頂点バッファビュー
    /// m_indexBufferView   インデックスバッファビュー
    /// m_pVertexBuffer     頂点バッファ
    /// m_pIndexBuffer      インデックスバッファ
    /// </summary> 
};
#endif // __D3D12_MESH_BUFFER_H__
