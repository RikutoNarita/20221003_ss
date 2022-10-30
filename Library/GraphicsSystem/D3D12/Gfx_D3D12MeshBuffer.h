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

    //------------------------------------------------------------------------------
    /// ���_�o�b�t�@�̍쐬
    ///
    /// \return �쐬�ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    HRESULT CreateVertexBuffer() final;

    //------------------------------------------------------------------------------
    /// �C���f�b�N�X�o�b�t�@�̐���
    ///
    /// \return �쐬�ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    HRESULT CreateIndexBuffer() final;

    //------------------------------------------------------------------------------
    /// ���_���̍X�V
    ///
    /// \param[in] pData ���_�o�b�t�@�̃f�[�^
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Write(
        /*[in]*/
        void* pData) final;

    //------------------------------------------------------------------------------
    /// ���b�V���o�b�t�@�̌Œ�
    ///
    /// \param[in] slot ���W�X�^�ԍ�
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(
        /*[in]*/
        unsigned int slot = 0) const final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Resource>      m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D12Resource>      m_pIndexBuffer;
    D3D12_VERTEX_BUFFER_VIEW                    m_vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW                     m_indexBufferView;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pVertexBuffer     ���_�o�b�t�@
    /// m_pIndexBuffer      �C���f�b�N�X�o�b�t�@
    /// m_vertexBufferView  ���_�o�b�t�@�r���[
    /// m_indexBufferView   �C���f�b�N�X�o�b�t�@�r���[
    /// </summary> 
};
#endif // __D3D12_MESH_BUFFER_H__
