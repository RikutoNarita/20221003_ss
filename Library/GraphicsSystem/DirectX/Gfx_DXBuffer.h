//==============================================================================
// Filename: Gfx_DXBuffer.h
// Description: 
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! �C���N���[�h�K�[�h
#ifndef __DX_BUFFER_H__
#define __DX_BUFFER_H__

//! �C���N���[�h
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

//! �N���X��`
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
        D3D11_PRIMITIVE_TOPOLOGY topology;
    };
    //---------------------------------------------------------------------------
    /// <summary>
    /// Desc�\����
    /// pVtx        ���_�o�b�t�@
    /// vtxSize     ���_�o�b�t�@�̑傫��
    /// vtxCount    ���_�̐�
    /// isWrite
    /// pIdx        �C���f�b�N�X�o�b�t�@
    /// idxSize     �C���f�b�N�X�o�b�t�@�̑傫��
    /// idxCount    �C���f�b�N�X�̐�
    /// topology    �v���~�e�B�u�^�C�v
    /// </summary>

public:

    //---------------------------------------------------------------------------
    
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
    /// 
    ///
    /// \param[in] 
    ///
    /// \return void
    //------------------------------------------------------------------------------
    HRESULT Write(void* pVtx);

    void SwapPrimitive(); // �v���~�e�B�u�^�C�v�̕ύX
    //---------------------------------------------------------------------------

private:

    //---------------------------------------------------------------------------
    
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
    HRESULT CreateVertexBuffer(const void* pIdx, UINT size, UINT count, bool isWrite);

    //------------------------------------------------------------------------------
    /// �C���f�b�N�X�o�b�t�@�쐬
    ///
    /// \param[in] pVtx
    /// \param[in] size
    /// \param[in] count 
    ///
    /// \return �C���f�b�N�X�o�b�t�@�쐬�̐���
    //------------------------------------------------------------------------------
    HRESULT CreateIndexBuffer(const void* pVtx, UINT size, UINT count);

    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    ID3D11Buffer* m_pVtxBuffer;
    UINT m_vtxSize;
    UINT m_vtxCount;
    ID3D11Buffer* m_pIdxBuffer;
    UINT m_idxSize;
    UINT m_idxCount;
    D3D11_PRIMITIVE_TOPOLOGY m_topology;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pVtxBuffer    ���_�o�b�t�@
    /// m_vtxSize       ���_�o�b�t�@�̑傫��
    /// m_vtxCount      ���_�̐�
    /// m_pIdxBuffer    �C���f�b�N�X�o�b�t�@
    /// m_idxSize       �C���f�b�N�X�o�b�t�@�̑傫��
    /// m_idxCount      �C���f�b�N�X�̐�
    /// m_topology      �v���~�e�B�u�^�C�v
    /// </summary>
};



#endif // __DRAW_BUFFER_H__