﻿//==============================================================================
// Filename: Gfx_D3D12VertexShader.h
// Description: Direct3D 12頂点シェーダークラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>


//------------------------------------------------------------------------------
/// コンストラクタ
///
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D12VertexShader::GfxD3D12VertexShader(const wchar_t* fileName)
: GfxVertexShader(KIND::KIND_VS)
{
    // エラー対応
    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;
    HRESULT hr = S_OK;

    // 頂点シェーダー読み込み
    hr = D3DCompileFromFile(
        fileName,                                           // ファイル名
        nullptr,                                            // シェーダーマクロオブジェクト
        D3D_COMPILE_STANDARD_FILE_INCLUDE,                  // インクルードはデフォルト
        "main",                                             // エントリーポイント名
        "vs_5_0",                                           // シェーダーモデル
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,    // デバッグ、最適化なし
        0,                                                  // エフェクトコンパイルオプション
        &m_pBlob,                                           // 頂点シェーダー
        &pErrorBlob);                                       // エラー用ポインタアドレス

    if (FAILED(hr))
    {
        _ASSERT_EXPR(false, L"NO_SHADER");
    }

    //// 頂点レイアウトの作成
    //m_inputLayout.push_back(
    //    {// 座標
    //        "POSITION",                                 // セマンティクス名
    //        0,                                          // セマンティクスインデックス
    //        DXGI_FORMAT_R32G32B32_FLOAT,                // フォーマット
    //        0,                                          // 入力スロットインデックス
    //        D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
    //        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
    //        0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
    //    });
    //m_inputLayout.push_back(
    //    {// 法線
    //        "NORMAL",                                       // セマンティクス名
    //            0,                                          // セマンティクスインデックス
    //            DXGI_FORMAT_R32G32B32_FLOAT,                // フォーマット
    //            0,                                          // 入力スロットインデックス
    //            D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
    //            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
    //            0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
    //    });
    //m_inputLayout.push_back(
    //    {
    //        // テクスチャ座標
    //        "TEXCOORD",                                 // セマンティクス名
    //        0,                                          // セマンティクスインデックス
    //        DXGI_FORMAT_R32G32_FLOAT,                   // フォーマット
    //        0,                                          // 入力スロットインデックス
    //        D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
    //        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
    //        0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
    //    });
    //m_inputLayout.push_back(
    //    {
    //        // 色
    //        "COLOR",                                    // セマンティクス名
    //        0,                                          // セマンティクスインデックス
    //        DXGI_FORMAT_R32G32B32A32_FLOAT,             // フォーマット
    //        0,                                          // 入力スロットインデックス
    //        D3D12_APPEND_ALIGNED_ELEMENT,               // データのオフセット位置（データが連続していることを示す）
    //        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, // 入力スロットクラス
    //        0                                           // 1度に描画するインスタンスの数（インスタンシングを利用しないので0）
    //    });
    //
    //m_desc.pInputElementDescs = m_inputLayout.data();
    //m_desc.NumElements = (UINT)m_inputLayout.size();

    /*
    シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
    セマンティクスの配置などから識別子を作成
    識別子が登録済なら再利用、なければ新規作成
    https://blog.techlab-xe.net/dxc-shader-reflection/
    */
    ID3D12ShaderReflection* pReflection;
    D3D12_SHADER_DESC shaderDesc;
    //D3D12_INPUT_ELEMENT_DESC* pInputDesc;
    D3D12_SIGNATURE_PARAMETER_DESC sigDesc;
    std::string key = "";

    DXGI_FORMAT formats[][4] =
    {
        {
            DXGI_FORMAT_R32_UINT,
            DXGI_FORMAT_R32G32_UINT,
            DXGI_FORMAT_R32G32B32_UINT,
            DXGI_FORMAT_R32G32B32A32_UINT,
        }, {
            DXGI_FORMAT_R32_SINT,
            DXGI_FORMAT_R32G32_SINT,
            DXGI_FORMAT_R32G32B32_SINT,
            DXGI_FORMAT_R32G32B32A32_SINT,
        }, {
            DXGI_FORMAT_R32_FLOAT,
            DXGI_FORMAT_R32G32_FLOAT,
            DXGI_FORMAT_R32G32B32_FLOAT,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
        },
    };

    hr = D3DReflect(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), IID_PPV_ARGS(&pReflection));
    if (FAILED(hr)) { return; }

    pReflection->GetDesc(&shaderDesc);
    pInputDesc = new D3D12_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
    for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
    {
        pReflection->GetInputParameterDesc(i, &sigDesc);
        pInputDesc[i].SemanticName = sigDesc.SemanticName;
        pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

        // http://marupeke296.com/TIPS_No17_Bit.html
        BYTE elementCount = sigDesc.Mask;
        elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
        elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

        switch (sigDesc.ComponentType)
        {
        case D3D_REGISTER_COMPONENT_UINT32:
            pInputDesc[i].Format = formats[0][elementCount - 1];
            break;
        case D3D_REGISTER_COMPONENT_SINT32:
            pInputDesc[i].Format = formats[1][elementCount - 1];
            break;
        case D3D_REGISTER_COMPONENT_FLOAT32:
            pInputDesc[i].Format = formats[2][elementCount - 1];
            break;
        }
        pInputDesc[i].InputSlot = 0;
        pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D12_APPEND_ALIGNED_ELEMENT;
        pInputDesc[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        pInputDesc[i].InstanceDataStepRate = 0;

        key += sigDesc.SemanticName;
        key += sigDesc.SemanticIndex;
    }
    m_desc.pInputElementDescs = pInputDesc;
    m_desc.NumElements = shaderDesc.InputParameters;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12VertexShader::~GfxD3D12VertexShader()
{
    delete[] pInputDesc;
}

//------------------------------------------------------------------------------
/// 頂点シェーダーの指定
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12VertexShader::Bind(unsigned int slot) const
{

}

