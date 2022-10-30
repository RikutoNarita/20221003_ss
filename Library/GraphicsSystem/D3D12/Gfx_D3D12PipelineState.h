//==============================================================================
// Filename: Gfx_D3D12PipelineState.h
// Description: パイプラインステートクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_PIPELINE_STATE_H__
#define __D3D12_PIPELINE_STATE_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <d3d12.h>
#include <wrl/client.h>

// 前方宣言
class GfxD3D12PixelShader;
class GfxD3D12VertexShader;
class GfxD3D12RootSignature;

// クラス定義
class GfxPipelineState : GfxGraphicsObject<GfxPipelineState>
{
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxPipelineState();
    
    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxPipelineState();

    //------------------------------------------------------------------------------
    /// デパイプラインの作成
    ///
    /// \param[in] pRootParameter ルートパラメーター
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void Create(
        /*[in]*/
        GfxD3D12RootSignature* pRootParameter);

    //------------------------------------------------------------------------------
    /// パイプラインにピクセルシェーダーをバインドする
    ///
    /// \param[in] ps ピクセルシェーダー
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindPS(
        /*[in]*/
        GfxD3D12PixelShader* ps);

    //------------------------------------------------------------------------------
    /// パイプラインに頂点シェーダーをバインドする
    ///
    /// \param[in] vs 頂点シェーダー
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindVS(
        /*[in]*/
        GfxD3D12VertexShader* vs);


    //------------------------------------------------------------------------------
    /// パイプラインのバインド
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
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pPipeLineState;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC          m_pipelineDesc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pPipeLineState    パイプラインステート
    /// m_pipelineDesc      パイプラインステートの設定項目
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
