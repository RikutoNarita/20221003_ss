//==============================================================================
// Filename: GfxConstantBuffer.cpp
// Description: �萔�o�b�t�@�N���X
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! �C���N���[�h
#include <GraphicsSystem\DirectX\Gfx_ConstantBuffer.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

//------------------------------------------------------------------------------
/// �R���X�g���N�^
/// 
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::GfxConstantBuffer()
    : m_pBuffer(nullptr)
{
}

//------------------------------------------------------------------------------
/// �f�X�g���N�^
/// 
/// \return void
//------------------------------------------------------------------------------
GfxConstantBuffer::~GfxConstantBuffer()
{
    SAFE_RELEASE(m_pBuffer);
}

//------------------------------------------------------------------------------
/// �萔�o�b�t�@�쐬
/// 
/// \param[in] size �萔�o�b�t�@�̑傫��
///
/// \return �萔�o�b�t�@�쐬�̐���
//------------------------------------------------------------------------------
HRESULT GfxConstantBuffer::Create(UINT size)
{
    /* �萔�o�b�t�@�쐬���̒���
    �萔�o�b�t�@�̑傫����4�o�C�g��؂�(
    4�o�C�g�A���C�����g)�łȂ��ƍ쐬�ł��Ȃ�
    */
    HRESULT hr;

    // �쐬����o�b�t�@�̏��
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = size;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // �o�b�t�@�̍쐬
    ID3D11Device* pDevice = D3D->GetDevice();
    hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

    return hr;
}

//------------------------------------------------------------------------------
/// �萔�o�b�t�@�ւ̏�������
/// 
/// \param[in] pData �萔�o�b�t�@�̃f�[�^
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::Write(const void* pData)
{
    // �萔�o�b�t�@�ւ̏�������
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}

//------------------------------------------------------------------------------
/// ���_�V�F�[�_�[�̎w�肵���X���b�g�ɒ萔�o�b�t�@�̃f�[�^�𑗂�
/// 
/// \param[in] slot �X���b�g
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::BindVS(UINT slot)
{
    /*
    �萔�o�b�t�@�̃f�[�^�𑗂�ہA
    �ǂ̈ʒu�Ɋi�[���邩��1�ڂ̈���(StartSlot)��
    �w�肷��B
    hlsl�̃R�[�h�ł�register(bX)�Ńo�b�t�@�̊i�[
    �ʒu�����߂Ă����B
    */
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}

//------------------------------------------------------------------------------
/// �s�N�Z���V�F�[�_�[�̎w�肵���X���b�g�ɒ萔�o�b�t�@�̃f�[�^�𑗂�
/// 
/// \param[in] slot �X���b�g
///
/// \return void
//------------------------------------------------------------------------------
void GfxConstantBuffer::BindPS(UINT slot)
{
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}