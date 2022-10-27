//==============================================================================
// Filename: Gfx_D3D11MeshBuffer.h
// Description: Direct3D 11メッシュバッファー
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D11_MESH_BUFFER_H__
#define __D3D11_MESH_BUFFER_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_MeshBuffer.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11PixelShader.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Texture.h>
#include <Windows.h>
#include <d3d11.h>
#include <wrl\client.h>
#include <map>

// クラス定義
class GfxD3D11MeshBuffer : public GfxMeshBuffer
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
    GfxD3D11MeshBuffer(Description desc);

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11MeshBuffer();

    //------------------------------------------------------------------------------
    /// 頂点バッファの生成
    ///
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    HRESULT CreateVertexBuffer();

    //------------------------------------------------------------------------------
    /// インデックスバッファの生成
    ///
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    HRESULT CreateIndexBuffer();

    //------------------------------------------------------------------------------
    /// バッファの更新
    ///
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    void Write(void* pData) final;
    
    //------------------------------------------------------------------------------
    /// バッファの描画
    ///
    /// \return 生成できた場合 S_OK
    //------------------------------------------------------------------------------
    void Bind(unsigned int slot = 0) const final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;    
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pVertexBuffer 頂点バッファ
    /// m_pIndexBuffer  インデックスバッファ
    /// </summary> 
};
#endif // __D3D11_MESH_BUFFER_H__
