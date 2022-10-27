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
#include <vector>

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


    void Create(GfxD3D12RootSignature* root);

    void BindPS(GfxD3D12PixelShader* ps);
    void BindVS(GfxD3D12VertexShader* vs);


    void Bind(unsigned int slot = 0) const final;

    ID3D12PipelineState* Get()
    {
        return m_pPipeLineState.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pPipeLineState;   // パイプラインステート
    D3D12_GRAPHICS_PIPELINE_STATE_DESC          m_pipelineDesc;
    //------------------------------------------------------------------------------
    /// <summary>
    /// m_pDescriptorHeap       ディスクリプタヒープ
    /// m_pFence                フェンス
    /// </summary> 
};
#endif // __D3D_MANAGER_H__
