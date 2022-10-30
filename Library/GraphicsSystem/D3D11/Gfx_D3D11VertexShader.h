//==============================================================================
// Filename: Gfx_D3D11VertexShader.h
// Description: Direct3D 11���_�V�F�[�_�[�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_VERTEX_SHADER_H__
#define __D3D11_VERTEX_SHADER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d11.h>
#include <map>
#include <string>

// �N���X��`
class GfxD3D11VertexShader : public GfxVertexShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \param[in] fileName �V�F�[�_�[�t�@�C���̃p�X
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11VertexShader(
        /*[in]*/
        const wchar_t* fileName);

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11VertexShader();

    //------------------------------------------------------------------------------
    /// ���_�V�F�[�_�[�̃o�C���h
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
    using ILList = std::map<std::string, ID3D11InputLayout*>;
    using ILKey = std::pair<std::string, ID3D11InputLayout*>;
private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVS;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;
    static ILList m_ILList;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pVS               ���_�V�F�[�_�[
    /// m_pInputLayout      ���_���C�A�E�g
    /// m_ILList            ���_���C�A�E�g���X�g
    /// </summary> 
};
#endif // __D3D11_VERTEX_SHADER_H__
