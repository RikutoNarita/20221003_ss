//==============================================================================
// Filename: Gfx_ConstantBuffer.h
// Description: 定数バッファの基底クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __CONSTANT_BUFER_H__
#define __CONSTANT_BUFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GrapicsObjectBase.h>
#include <GraphicsSystem\Interface\Gfx_Tag.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <Windows.h>

// クラス定義
class GfxConstantBuffer : public GfxGraphicsObject<GfxConstantBuffer>
{
public:
    //------------------------------------------------------------------------------
    enum class Shader
    {
        BIND_VERTEX,
        BIND_PIXEL,
    };

    struct Description
    {
       size_t size;
       void* pData;
    };
    //------------------------------------------------------------------------------
    /// <summary>
    /// Description
    /// </summary> 

public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] desc 定数バッファの設定項目
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxConstantBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxConstantBuffer();


    virtual void Write(void* pData) = 0;

    //------------------------------------------------------------------------------
    /// 定数バッファの作成
    /// 
    /// \param[in] tag  リソースに紐づけるタグ
    /// \param[in] desc 定数バッファの設定項目
    ///
    /// \return このクラスのポインタ
    //------------------------------------------------------------------------------
    static GfxConstantBuffer::Ptr Create(const GfxTag& tag, Description desc);

    virtual void BindVS(unsigned slot) = 0;
    virtual void BindPS(unsigned slot) = 0;


    //void SetShaderKind(Shader bindShader)
    //{
    //    m_eBind = bindShader;
    //}
    //
    //void SetSlot(unsigned slot)
    //{
    //    m_nSlot = slot;
    //}
    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Description m_desc;
    unsigned m_nSlot;
    Shader m_eBind;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_desc      定数バッファの設定項目
    /// </summary> 
};
#endif // __CONSTANT_BUFER_H__
