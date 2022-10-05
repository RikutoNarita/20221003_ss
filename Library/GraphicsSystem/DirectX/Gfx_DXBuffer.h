//==============================================================================
// Filename: Gfx_DXBuffer.h
// Description: 
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルードガード
#ifndef __DX_BUFFER_H__
#define __DX_BUFFER_H__

//! インクルード
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>

//! クラス定義
class GfxDXBuffer
{
public:
    //---------------------------------------------------------------------------
    struct Desc
    {
        const void* pVtx;
        UINT vtxSize;
        UINT vtxCount;
        bool isWrite;
        const void* pIdx;
        UINT idxSize;
        UINT idxCount;
        D3D11_PRIMITIVE_TOPOLOGY topology;
    };
    //---------------------------------------------------------------------------
    /// <summary>
    /// Desc構造体
    /// pVtx        頂点バッファ
    /// vtxSize     頂点バッファの大きさ
    /// vtxCount    頂点の数
    /// isWrite
    /// pIdx        インデックスバッファ
    /// idxSize     インデックスバッファの大きさ
    /// idxCount    インデックスの数
    /// topology    プリミティブタイプ
    /// </summary>

public:

    //---------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxDXBuffer();

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxDXBuffer();

    //------------------------------------------------------------------------------
    /// 頂点バッファ、インデックスバッファを作成する
    ///
    /// \param[in] desc バッファ作成時の記述設定
    ///
    /// \return 作成できたかどうかの状態 S_OKで成功
    //------------------------------------------------------------------------------
    HRESULT Create(
    /*[in]*/
    const Desc& desc);

    //------------------------------------------------------------------------------
    /// 描画処理
    ///
    /// \param[in] count 描画するオブジェクトのインデックスの数
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Draw(
    /*[in]*/
    int count = 0);

    //------------------------------------------------------------------------------
    /// 
    ///
    /// \param[in] 
    ///
    /// \return void
    //------------------------------------------------------------------------------
    HRESULT Write(void* pVtx);

    void SwapPrimitive(); // プリミティブタイプの変更
    //---------------------------------------------------------------------------

private:

    //---------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// 頂点バッファ作成
    ///
    /// \param[in] pIdx
    /// \param[in] size
    /// \param[in] count 
    /// \param[in] isWrite 
    ///
    /// \return 頂点バッファ作成の成否
    //------------------------------------------------------------------------------
    HRESULT CreateVertexBuffer(const void* pIdx, UINT size, UINT count, bool isWrite);

    //------------------------------------------------------------------------------
    /// インデックスバッファ作成
    ///
    /// \param[in] pVtx
    /// \param[in] size
    /// \param[in] count 
    ///
    /// \return インデックスバッファ作成の成否
    //------------------------------------------------------------------------------
    HRESULT CreateIndexBuffer(const void* pVtx, UINT size, UINT count);

    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    ID3D11Buffer* m_pVtxBuffer;
    UINT m_vtxSize;
    UINT m_vtxCount;
    ID3D11Buffer* m_pIdxBuffer;
    UINT m_idxSize;
    UINT m_idxCount;
    D3D11_PRIMITIVE_TOPOLOGY m_topology;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pVtxBuffer    頂点バッファ
    /// m_vtxSize       頂点バッファの大きさ
    /// m_vtxCount      頂点の数
    /// m_pIdxBuffer    インデックスバッファ
    /// m_idxSize       インデックスバッファの大きさ
    /// m_idxCount      インデックスの数
    /// m_topology      プリミティブタイプ
    /// </summary>
};



#endif // __DRAW_BUFFER_H__