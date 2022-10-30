//==============================================================================
// Filename: Gfx_D3D11VertexShader.h
// Description: Direct3D 11頂点シェーダークラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_VERTEX_SHADER_H__
#define __D3D11_VERTEX_SHADER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d11.h>
#include <map>
#include <string>

// クラス定義
class GfxD3D11VertexShader : public GfxVertexShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] fileName シェーダーファイルのパス
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11VertexShader(
        /*[in]*/
        const wchar_t* fileName);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11VertexShader();

    //------------------------------------------------------------------------------
    /// 頂点シェーダーのバインド
    /// 
    /// \param[in] slot レジスタ番号
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
    /// m_pVS               頂点シェーダー
    /// m_pInputLayout      頂点レイアウト
    /// m_ILList            頂点レイアウトリスト
    /// </summary> 
};
#endif // __D3D11_VERTEX_SHADER_H__
