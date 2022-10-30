//==============================================================================
// Filename: Gfx_D3D12ConstantBuffer.h
// Description: Direct3D 12定数バッファクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_CONSTANT_BUFER_H__
#define __D3D12_CONSTANT_BUFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_ConstantBuffer.h>
#include <wrl\client.h>
#include <d3d12.h>

// クラス定義
class GfxD3D12ConstantBuffer : public GfxConstantBuffer
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
    GfxD3D12ConstantBuffer(
    /*[in]*/
    Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D12ConstantBuffer();

    //------------------------------------------------------------------------------
    /// 定数バッファの更新
    ///
    /// \param[in] pData 定数バッファのデータ
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Write(
    /*[in]*/
    void* pData) final;
    
    //------------------------------------------------------------------------------
    /// 定数バッファデータの取得
    ///
    /// \return 定数バッファデータのポインタ
    //------------------------------------------------------------------------------
    inline ID3D12Resource* Get() const
    {
        return m_pConstantBuffer.Get();
    }

    void BindPS(unsigned slot) final;
    void BindVS(unsigned slot) final;
    void Bind(unsigned slot = 0) const final;

    //------------------------------------------------------------------------------

protected:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12Resource> m_pConstantBuffer;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pConstantBuffer      定数バッファ
    /// </summary> 
};
#endif // __D3D12_CONSTANT_BUFER_H__
