//==============================================================================
// Filename: Gfx_D3D12VertexShader.h
// Description: Direct3D 12���_�V�F�[�_�[�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D12_VERTEX_SHADER_H__
#define __D3D12_VERTEX_SHADER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d12.h>
#include <vector>

// �N���X��`
class GfxD3D12VertexShader : public GfxVertexShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12VertexShader(const wchar_t* fileName);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12VertexShader();

    //------------------------------------------------------------------------------
    /// ���_�V�F�[�_�[�̎w��
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(unsigned int slot) const override;

    //HRESULT Compile(const GfxTag& tag, const wchar_t* fileName);

    UINT GetElementCount()
    {
        return m_desc.NumElements;
    }

    const D3D12_INPUT_ELEMENT_DESC* GetElement()
    {
        return m_desc.pInputElementDescs;
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    
    D3D12_INPUT_ELEMENT_DESC* pInputDesc;
    D3D12_INPUT_LAYOUT_DESC m_desc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_inputLayout   ���_���C�A�E�g
    /// </summary> 
};
#endif // __D3D12_VERTEX_SHADER_H__
