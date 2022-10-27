//==============================================================================
// Filename: Gfx_D3D11VertexShader.h
// Description: Direct3D 11頂点シェーダークラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\D3D11\Gfx_D3D11VertexShader.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11ConstantBuffer.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11Texture.h>
#include <vector>
#include <map>

GfxD3D11VertexShader::ILList GfxD3D11VertexShader::m_ILList;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] shader
/// 
/// \return void
//------------------------------------------------------------------------------
GfxD3D11VertexShader::GfxD3D11VertexShader(const wchar_t* fileName)
: GfxVertexShader(KIND::KIND_VS)
, m_pVS(nullptr), m_pInputLayout(nullptr)
{
    ID3D11Device* pDevice = GRAPHICS->GetDevice<ID3D11Device>();

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

    // 頂点シェーダーの作成
    pDevice->CreateVertexShader(m_pBlob->GetBufferPointer(),
    (UINT)m_pBlob->GetBufferSize(), nullptr, &m_pVS);

    /*
    シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
    セマンティクスの配置などから識別子を作成
    識別子が登録済なら再利用、なければ新規作成
    https://blog.techlab-xe.net/dxc-shader-reflection/
    */
    ID3D11ShaderReflection* pReflection;
    D3D11_SHADER_DESC shaderDesc;
    D3D11_INPUT_ELEMENT_DESC* pInputDesc;
    D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
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
    pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
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
        pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
        pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        pInputDesc[i].InstanceDataStepRate = 0;

        key += sigDesc.SemanticName;
        key += sigDesc.SemanticIndex;
    }

    std::map<std::string, ID3D11InputLayout*>::iterator it = m_ILList.begin();
    while (it != m_ILList.end())
    {
        if (it->first == key)
        {
            m_pInputLayout = it->second;
            break;
        }
        ++it;
    }
    if (it == m_ILList.end())
    {
        hr = pDevice->CreateInputLayout(
            pInputDesc, shaderDesc.InputParameters,
            m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), &m_pInputLayout);
        if (SUCCEEDED(hr))
        {
            m_ILList.insert(ILKey(key, m_pInputLayout.Get()));
        }
    }

    delete[] pInputDesc;
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D11VertexShader::~GfxD3D11VertexShader()
{
}


// 頂点シェーダーのバインド
void GfxD3D11VertexShader::Bind(unsigned int slot) const
{
    // 定数バッファのバインド
    for (int i = 0; i < MAX_BUFFER; ++i)
    {
        if (m_buffers[i])
        {
            m_buffers[i]->BindVS(i);
        }
    }

    // テクスチャのバインド
    for (int i = 0; i < MAX_BUFFER; ++i)
    {
        if (m_textures[i])
        {
            m_textures[i]->BindVS(i);
        }
    }

    ID3D11DeviceContext* pContext = GRAPHICS->GetRenderCommand<ID3D11DeviceContext>();
    pContext->VSSetShader(m_pVS.Get(), nullptr, 0);
    pContext->IASetInputLayout(m_pInputLayout.Get());
}