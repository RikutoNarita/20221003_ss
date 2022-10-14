//==============================================================================
// Filename: Gfx_DXBuffer.cpp
// Description: 
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h
#include <GraphicsSystem\DirectX\Gfx_DXBuffer.h>
#include <Win_Main.h>

//------------------------------------------------------------------------------
/// �R���X�g���N�^
///
/// \return void
//------------------------------------------------------------------------------
GfxDXBuffer::GfxDXBuffer()
#ifdef DX12
    : m_vtxSize(0), m_vtxCount(0)
    , m_idxSize(0), m_idxCount(0)
    , m_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
#else
    : m_pVtxBuffer(nullptr), m_vtxSize(0), m_vtxCount(0)
    , m_pIdxBuffer(nullptr), m_idxSize(0), m_idxCount(0)
    , m_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
#endif // DX12
{
}

//------------------------------------------------------------------------------
/// �f�X�g���N�^
///
/// \return void
//------------------------------------------------------------------------------
GfxDXBuffer::~GfxDXBuffer()
{
#ifdef DX12
#else
    SAFE_RELEASE(m_pIdxBuffer);
    SAFE_RELEASE(m_pVtxBuffer);
#endif // DX12
}

//------------------------------------------------------------------------------
/// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@���쐬����
///
/// \param[in] desc �o�b�t�@�쐬���̋L�q�ݒ�
///
/// \return �쐬�ł������ǂ����̏�� S_OK�Ő���
//------------------------------------------------------------------------------
HRESULT GfxDXBuffer::Create(const Desc& desc)
{
    HRESULT hr = E_FAIL;
    hr = CreateVertexBuffer(desc.pVtx, desc.vtxSize, desc.vtxCount, desc.isWrite);
    if (FAILED(hr))
    {
        return hr;
    }

    if (desc.pIdx)
    {
        hr = CreateIndexBuffer(desc.pIdx, desc.idxSize, desc.idxCount);
        if (FAILED(hr))
        { 
            return hr; 
        }
    }

    m_topology = desc.topology;
    return hr;
}

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
HRESULT GfxDXBuffer::CreateVertexBuffer(const void* pVtx, UINT size, UINT count, bool isWrite)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(pVtx);
    UNREFERENCED_PARAMETER(size);
    UNREFERENCED_PARAMETER(count);
    UNREFERENCED_PARAMETER(isWrite);
    return S_OK;
#else
    //--- �쐬����o�b�t�@�̏��
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = size * count;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    if (isWrite)
    {
        bufDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }

    //--- �o�b�t�@�̏����l��ݒ�
    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = pVtx;

    //--- ���_�o�b�t�@�̍쐬
    HRESULT hr;
    ID3D11Device* pDevice = D3D->GetDevice();
    hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuffer);

    //--- ���̂ق��̏���ݒ�
    if (SUCCEEDED(hr))
    {
        m_vtxSize = size;
        m_vtxCount = count;
    }
    return hr;
#endif // DX12
}

//------------------------------------------------------------------------------
/// �C���f�b�N�X�o�b�t�@�쐬
///
/// \param[in] pVtx
/// \param[in] size
/// \param[in] count 
///
/// \return �C���f�b�N�X�o�b�t�@�쐬�̐���
//------------------------------------------------------------------------------
HRESULT GfxDXBuffer::CreateIndexBuffer(const void* pIdx, UINT size, UINT count)
{
    UNREFERENCED_PARAMETER(pIdx);
    UNREFERENCED_PARAMETER(size);
    UNREFERENCED_PARAMETER(count);
    // �C���f�b�N�X�T�C�Y�̊m�F
    switch (size)
    {

    default:
      return E_FAIL;
    case 1:
    case 2:
    case 4:
        break;
    }
#ifdef DX12
    return S_OK;
#else
    // �o�b�t�@�̏���ݒ�
    D3D11_BUFFER_DESC bufDesc = {};
    bufDesc.ByteWidth = size * count;
    bufDesc.Usage = D3D11_USAGE_DEFAULT;
    bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    // �o�b�t�@�̏����f�[�^
    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = pIdx;

    // �C���f�b�N�X�o�b�t�@����
    ID3D11Device* pDevice = D3D->GetDevice();
    HRESULT hr;
    hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIdxBuffer);
    if (SUCCEEDED(hr))
    {
        m_idxSize = size;
        m_idxCount = count;
    }

  return hr;
#endif // DX12
}

//------------------------------------------------------------------------------
/// �`�揈��
///
/// \param[in] count �`�悷��I�u�W�F�N�g�̃C���f�b�N�X�̐�
///
/// \return void
//------------------------------------------------------------------------------
void GfxDXBuffer::Draw(int count)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(count);

#else
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    UINT stride = m_vtxSize;
    UINT offset = 0;

    pContext->IASetPrimitiveTopology(m_topology);
    pContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &stride, &offset);

    // �`��
    if (m_idxCount > 0)
    {
        DXGI_FORMAT format = {};
        switch (m_idxSize)
        {
        case 4: format = DXGI_FORMAT_R32_UINT; break;
        case 2: format = DXGI_FORMAT_R16_UINT; break;
        case 1: format = DXGI_FORMAT_R8_UINT; break;
        }
        pContext->IASetIndexBuffer(m_pIdxBuffer, format, 0);
        pContext->DrawIndexed(count ? count : m_idxCount, 0, 0);
    }
    else
    {
        // ���_�o�b�t�@�݂̂ŕ`��
        pContext->Draw(count ? count : m_vtxCount, 0);
    }
#endif // DX12
}

//------------------------------------------------------------------------------
/// �萔�o�b�t�@�ւ̏�������
///
/// \param[in] 
///
/// \return �������݂̐���
//------------------------------------------------------------------------------
HRESULT GfxDXBuffer::Write(void* pVtx)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(pVtx);

    return S_OK;
#else
    HRESULT hr;
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    D3D11_MAPPED_SUBRESOURCE mapResource;

    // �f�[�^�R�s�[
    hr = pContext->Map(m_pVtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
    if (SUCCEEDED(hr))
    {
        rsize_t size = (rsize_t)(m_vtxCount * m_vtxSize);
        memcpy_s(mapResource.pData, size, pVtx, size);
        pContext->Unmap(m_pVtxBuffer, 0);
    }
    return hr;
#endif // DX12
}
