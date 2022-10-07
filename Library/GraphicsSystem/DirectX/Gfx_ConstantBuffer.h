//==============================================================================
// Filename: GfxConstantBuffer.h
// Description: 定数バッファクラス
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルードガード
#ifndef __CONSTANT_BUFFER_H__
#define __CONSTANT_BUFFER_H__

//! インクルード
#include <Win_Main.h>
#include <d3d11.h>

//! クラス定義
class GfxConstantBuffer
{
public:
    //------------------------------------------------------------------------------
    /// コンストラクタ
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    GfxConstantBuffer();

    //------------------------------------------------------------------------------
    /// デストラクタ
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxConstantBuffer();

    //------------------------------------------------------------------------------
    /// 定数バッファ作成
    /// 
    /// \param[in] size 定数バッファの大きさ
    ///
    /// \return 定数バッファ作成の成否
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    UINT size);

    //------------------------------------------------------------------------------
    /// 定数バッファへの書き込み
    /// 
    /// \param[in] pData 定数バッファのデータ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Write(
    /*[in]*/
    const void* pData);

    //------------------------------------------------------------------------------
    /// 頂点シェーダーの指定したスロットに定数バッファのデータを送る
    /// 
    /// \param[in] slot スロット
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(UINT slot);

    //------------------------------------------------------------------------------
    /// ピクセルシェーダーの指定したスロットに定数バッファのデータを送る
    /// 
    /// \param[in] slot スロット
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(UINT slot);

private:
    //---------------------------------------------------------------------------
    ID3D11Buffer* m_pBuffer;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pBuffer 定数バッファのポインタ
    /// </summary> 
};

#endif // __CONSTANT_BUFFER_H__