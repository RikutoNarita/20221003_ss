//==============================================================================
// Filename: Gfx_D3D11ConstantBuffer.h
// Description: Direct3D 11定数バッファクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_CONSTANT_BUFER_H__
#define __D3D11_CONSTANT_BUFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <wrl\client.h>
#include <d3d11.h>

// クラス定義
class GfxD3D11ConstantBuffer : public GfxConstantBuffer
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \param[in] desc 定数バッファの設定項目
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11ConstantBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11ConstantBuffer();

    void Write(void* pData) final;

    void BindPS(unsigned slot) final;
    void BindVS(unsigned slot) final;

    void Bind(unsigned slot = 0) const final;
    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pBuffer      定数バッファ
    /// </summary> 
};
#endif // __D3D11_CONSTANT_BUFER_H__
