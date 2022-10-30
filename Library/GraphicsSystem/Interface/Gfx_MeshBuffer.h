//==============================================================================
// Filename: Gfx_MeshBuffer.h
// Description: ���b�V���o�b�t�@�[�̊��N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __MESH_BUFFER_H__
#define __MESH_BUFFER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>

#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\Interface\Gfx_Texture.h>

// �N���X��`
class GfxMeshBuffer : public GfxGraphicsObject<GfxMeshBuffer>
{
public:
    //------------------------------------------------------------------------------
    enum class TOPOLOGY
    {
        LINE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_LIST,
    };

    struct Description
    {
        void* pVertexData;  // ���_�f�[�^
        UINT  vertexCount;   // ���_��
        UINT  vertexSize;    // �P���_�̃T�C�Y

        void* pIndexData;   // �C���f�b�N�X�f�[�^
        UINT  indexCount;    // �C���f�b�N�X��
        UINT  indexSize;     // 

        bool isWrite;       // ���_�̏��������̋��t���O
        TOPOLOGY tpology;   // �g�|���W�[
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// pVertexData // ���_�f�[�^
    /// vertexCount // ���_��
    /// vertexSize  // �P���_�̃T�C�Y
    /// pIndexData  // �C���f�b�N�X�f�[�^
    /// indexCount  // �C���f�b�N�X��
    /// indexSize   // 1�C���f�b�N�X�̃T�C�Y
    /// isWrite     // ���_�̏��������̋��t���O
    /// tpology     // �g�|���W�[
    /// </summary> 

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxMeshBuffer();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxMeshBuffer();

    //------------------------------------------------------------------------------
    /// ���_�o�b�t�@�̍쐬
    ///
    /// \return �쐬�ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    virtual HRESULT CreateVertexBuffer() = 0;

    //------------------------------------------------------------------------------
    /// �C���f�b�N�X�o�b�t�@�̐���
    ///
    /// \return �쐬�ł����ꍇ S_OK
    //------------------------------------------------------------------------------
    virtual HRESULT CreateIndexBuffer() = 0;

    //------------------------------------------------------------------------------
    /// ���_���̍X�V
    ///
    /// \param[in] pData ���_�o�b�t�@�̃f�[�^
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Write(
        /*[in]*/
        void* pData) = 0;

    //------------------------------------------------------------------------------
    /// ���_�f�[�^�̍쐬
    ///
    /// \param[in] tag  ���\�[�X�ɕR�Â���^�O
    /// \param[in] desc ���_�f�[�^�̐ݒ荀��
    /// 
    /// \return ���̃N���X�̃|�C���^
    //------------------------------------------------------------------------------
    static GfxMeshBuffer::Ptr Create(
        /*[in]*/
        const GfxTag& tag,
        /*[in]*/
        Description desc);

    //------------------------------------------------------------------------------

public:
    //------------------------------------------------------------------------------
    Description m_desc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc  ���b�V���f�[�^�̏��
    /// </summary> 
};
#endif // __MESH_BUFFER_H__
