//==============================================================================
// Filename: Gfx_D3D12VertexShader.h
// Description: Direct3D 12頂点シェーダークラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_VERTEX_SHADER_H__
#define __D3D12_VERTEX_SHADER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d12.h>
#include <vector>

// クラス定義
class GfxD3D12VertexShader : public GfxVertexShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12VertexShader(const wchar_t* fileName);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12VertexShader();

    //------------------------------------------------------------------------------
    /// 頂点シェーダーの指定
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
    /// m_inputLayout   頂点レイアウト
    /// </summary> 
};
#endif // __D3D12_VERTEX_SHADER_H__
