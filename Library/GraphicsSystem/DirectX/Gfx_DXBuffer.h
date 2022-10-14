//==============================================================================
// Filename: Gfx_DXBuffer.h
// Description: 
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __DX_BUFFER_H__
#define __DX_BUFFER_H__

// �C���N���[�h
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

// �N���X��`
class GfxDXBuffer
{
public:
    //---------------------------------------------------------------------------
    struct Desc
    {
        const void* pVtx;
        UINT vtxSize;
        UINT vtxCount;
        bool isWrite;
        const void* pIdx;
        UINT idxSize;
        UINT idxCount;
#ifdef DX12
        D3D12_PRIMITIVE_TOPOLOGY topology;
#else
        D3D11_PRIMITIVE_TOPOLOGY topology;
#endif // DX12
    };
    //---------------------------------------------------------------------------
    /// <summary>
    /// Desc�\����
    /// pVtx        ���_�o�b�t�@
    /// vtxSize     1���_�̃T�C�Y
    /// vtxCount    ���_�̐�
    /// isWrite
    /// pIdx        �C���f�b�N�X�o�b�t�@
    /// idxSize     �C���f�b�N�X�o�b�t�@�̑傫��
    /// idxCount    �C���f�b�N�X�̐�
    /// topology    �v���~�e�B�u�^�C�v
    /// </summary>

public:

    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxDXBuffer();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxDXBuffer();

    //------------------------------------------------------------------------------
    /// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@���쐬����
    ///
    /// \param[in] desc �o�b�t�@�쐬���̋L�q�ݒ�
    ///
    /// \return �쐬�ł������ǂ����̏�� S_OK�Ő���
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    const Desc& desc);

    //------------------------------------------------------------------------------
    /// �`�揈��
    ///
    /// \param[in] count �`�悷��I�u�W�F�N�g�̃C���f�b�N�X�̐�
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Draw(
    /*[in]*/
    int count = 0);

    //------------------------------------------------------------------------------
    /// �萔�o�b�t�@�ւ̏�������
    ///
    /// \param[in] 
    ///
    /// \return �������݂̐���
    //------------------------------------------------------------------------------
    HRESULT Write(void* pVtx);

    //------------------------------------------------------------------------------

private:

    //------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// ���_�o�b�t�@�쐬
    ///
    /// \param[in] pIdx
    /// \param[in] size
    /// \param[in] count 
    /// \param[in] isWrite 
    ///
    /// \return ���_�o�b�t�@�쐬�̐���
    //------------------------------------------------------------------------------
    HRESULT CreateVertexBuffer(
    /*[in]*/
    const void* pIdx,
    /*[in]*/
    UINT size,
    /*[in]*/
    UINT count,
    /*[in]*/
    bool isWrite);

    //------------------------------------------------------------------------------
    /// �C���f�b�N�X�o�b�t�@�쐬
    ///
    /// \param[in] pVtx
    /// \param[in] size
    /// \param[in] count 
    ///
    /// \return �C���f�b�N�X�o�b�t�@�쐬�̐���
    //------------------------------------------------------------------------------
    HRESULT CreateIndexBuffer(
    /*[in]*/
    const void* pVtx,
    /*[in]*/
    UINT size,
    /*[in]*/
    UINT count);

    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
#ifdef DX12
    //ID3D12Buffer* m_pVtxBuffer;
    //ID3D12Buffer* m_pIdxBuffer;
    D3D12_PRIMITIVE_TOPOLOGY m_topology;
#else
    ID3D11Buffer* m_pVtxBuffer;
    ID3D11Buffer* m_pIdxBuffer;
    D3D11_PRIMITIVE_TOPOLOGY m_topology;
#endif // DX12
    UINT m_vtxSize;
    UINT m_vtxCount;
    UINT m_idxSize;
    UINT m_idxCount;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pVtxBuffer  ���_�o�b�t�@
    /// m_vtxSize ���_�o�b�t�@�̑傫��
    /// m_vtxCount  ���_�̐�
    /// m_pIdxBuffer  �C���f�b�N�X�o�b�t�@
    /// m_idxSize �C���f�b�N�X�o�b�t�@�̑傫��
    /// m_idxCount  �C���f�b�N�X�̐�
    /// m_topology  �v���~�e�B�u�^�C�v
    /// </summary>
};

#endif // __DRAW_BUFFER_H__
