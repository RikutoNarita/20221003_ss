//==============================================================================
// Filename: Gfx_D3D12MeshBuffer.h
// Description: Direct3D 12���b�V���o�b�t�@�[
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_MESH_BUFFER_H__
#define __D3D12_MESH_BUFFER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>

#include <wrl\client.h>
#include <d3d12.h>

// �N���X��`
class GfxD3D12MeshBuffer : public GfxMeshBuffer
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] shader
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12MeshBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
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
    /// m_pPipelineState    �p�C�v���C���X�e�[�g
    /// m_pRootSignature    ���[�g�V�O�l�`��
    /// m_vertexBufferView  ���_�o�b�t�@�r���[
    /// m_indexBufferView   �C���f�b�N�X�o�b�t�@�r���[
    /// m_pVertexBuffer     ���_�o�b�t�@
    /// m_pIndexBuffer      �C���f�b�N�X�o�b�t�@
    /// </summary> 
};
#endif // __D3D12_MESH_BUFFER_H__
