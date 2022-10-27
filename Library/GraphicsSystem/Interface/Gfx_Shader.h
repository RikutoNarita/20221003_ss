//==============================================================================
// Filename: Gfx_Shader.h
// Description: シェーダーの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __SHADER_H__
#define __SHADER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <Windows.h>
#include <wrl\client.h>
#include <d3dcompiler.h>

class GfxConstantBuffer;
class GfxTexture;

// クラス定義
class GfxShader : public GfxGraphicsObject<GfxShader>
{
public:
    enum class KIND
    {
        KIND_VS,
        KIND_PS,
    };

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] shader
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxShader(KIND kind);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxShader();

    static GfxShader::Ptr Compile(const GfxTag& tag, const KIND& kind, const wchar_t* fileName);

    void SetBuffer(GfxConstantBuffer* pConstantBuffer, unsigned int slot)
    {
        if (0 <= slot && slot < MAX_BUFFER)
        {
            m_buffers[slot] = pConstantBuffer;
        }
    }

    void SetTexture(GfxTexture* pTex, unsigned int slot)
    {
        if (0 <= slot && slot < MAX_BUFFER)
        {
            m_textures[slot] = pTex;
        }
    }

    ID3DBlob* GetBlob() const
    {
        return m_pBlob.Get();
    }

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    static const int MAX_BUFFER = 4;
    GfxConstantBuffer* m_buffers[MAX_BUFFER];
    GfxTexture* m_textures[MAX_BUFFER];
    KIND m_kind;
    Microsoft::WRL::ComPtr<ID3DBlob> m_pBlob;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_kind      シェーダーの種類
    /// </summary> 
};

class GfxVertexShader : public GfxShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] shader
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxVertexShader(KIND kind)
        : GfxShader(kind)
    {
    }

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxVertexShader() {}

    //------------------------------------------------------------------------------
};

class GfxPixelShader : public GfxShader
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] shader
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxPixelShader(KIND kind)
        : GfxShader(kind)
    {
    }

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxPixelShader() {}

    //------------------------------------------------------------------------------
};

#endif // __SHADER_H__
