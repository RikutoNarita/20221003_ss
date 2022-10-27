//==============================================================================
// Filename: Gfx_D3D12PipelineState.h
// Description: パイプラインステートクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12PipelineState.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12RootSignature.h>

#include <Win_Main.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxPipelineState::GfxPipelineState()
{
    HRESULT hr = S_OK;
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob; 

    m_pipelineDesc = {};

    // サンプルマスクの設定
    m_pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // デフォルト
    // ラスタライザのステートの設定
    m_pipelineDesc.RasterizerState.MultisampleEnable = false;         // アンチエイリアスなし
    m_pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;   // カリングしない
    m_pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;  // 塗りつぶしをする
    m_pipelineDesc.RasterizerState.DepthClipEnable = true;            // 深度方向のクリッピングを有効
    // ブレンドステートの設定
    m_pipelineDesc.BlendState.AlphaToCoverageEnable = false;          // 三角形の網羅率の計算
    m_pipelineDesc.BlendState.IndependentBlendEnable = false;         // RTV[0]のブレンドステートをすべてのRTVに適用
    D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
    blendDesc.BlendEnable = false;                                  // ブレンドしない
    blendDesc.LogicOpEnable = false;                                // 論理演算しない
    blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // 書き込むときのマスク値
    m_pipelineDesc.BlendState.RenderTarget[0] = blendDesc;
    // 頂点のつなぎ方の設定
    m_pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;     // 切り離ししない
    // プリミティブタイプの設定
    m_pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;    // 三角形
    // レンダーターゲットの設定
    m_pipelineDesc.NumRenderTargets = 1;                          // レンダーターゲットの数
    m_pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;    // 0～1に正規化されたRGBA
    // アンチエイリアシングの設定
    m_pipelineDesc.SampleDesc.Count = 1;      // サンプリングは1ピクセルにつき1ピクセル
    m_pipelineDesc.SampleDesc.Quality = 0;    // クオリティは最低
    // 深度バッファの設定
    m_pipelineDesc.DepthStencilState.DepthEnable = true;                          // 深度バッファを使う
    m_pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込む
    m_pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;      // 小さい方を採用
    m_pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;                             // 深度値書き込み用フォーマット
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxPipelineState::~GfxPipelineState()
{
}

// パイプライン作成
void GfxPipelineState::Create(GfxD3D12RootSignature* root)
{
    ID3D12Device* pDevice = GRAPHICS->GetDevice<ID3D12Device>();

    m_pipelineDesc.pRootSignature = root->Get();

    // パイプラインの生成
    auto hr = pDevice->CreateGraphicsPipelineState(
        &m_pipelineDesc,
        IID_PPV_ARGS(&m_pPipeLineState));

    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_PIPELINE");
    }
}

// ピクセルシェーダーのバインド
void GfxPipelineState::BindPS(GfxD3D12PixelShader* ps)
{
    m_pipelineDesc.PS.pShaderBytecode = ps->GetBlob()->GetBufferPointer();
    m_pipelineDesc.PS.BytecodeLength = (UINT)ps->GetBlob()->GetBufferSize();
}
// 頂点シェーダーのバインド
void GfxPipelineState::BindVS(GfxD3D12VertexShader* vs)
{
    m_pipelineDesc.VS.pShaderBytecode = vs->GetBlob()->GetBufferPointer();
    m_pipelineDesc.VS.BytecodeLength = (UINT)vs->GetBlob()->GetBufferSize();

    m_pipelineDesc.InputLayout.pInputElementDescs = vs->GetElement();
    m_pipelineDesc.InputLayout.NumElements = vs->GetElementCount();
}



void GfxPipelineState::Bind(unsigned int slot) const
{
    auto pCommandList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();
    pCommandList->SetPipelineState(m_pPipeLineState.Get());
}
