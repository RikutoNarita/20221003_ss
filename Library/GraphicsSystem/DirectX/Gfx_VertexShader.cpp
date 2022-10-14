//==============================================================================
// Filename: Gfx_VertexShader.cpp
// Description: 頂点シェーダーに関するクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <GraphicsSystem\DirectX\Gfx_VertexShader.h>
#include <GraphicsSystem\DirectX\Gfx_D3DManager.h>
#include <d3dcompiler.h>

//! 静的メンバ変数
std::map<std::string, ID3D11InputLayout*> GfxVertexShader::m_inputLayoutList;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxVertexShader::GfxVertexShader()
    : GfxShader(GfxShader::Kind::VertexShader)
    , m_pVS(nullptr)
    , m_pInputLayout(nullptr)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxVertexShader::~GfxVertexShader()
{
    SAFE_RELEASE(m_pVS);
}

//------------------------------------------------------------------------------
/// シェーダーを描画に使用
///
/// \return void
//------------------------------------------------------------------------------
void GfxVertexShader::Bind()
{
#ifdef DX12
#else
    ID3D11DeviceContext* pContext = D3D->GetDeviceContext();
    // 頂点シェーダーをセット
    pContext->VSSetShader(m_pVS, nullptr, 0);
    // インプットレイアウトをセット
    pContext->IASetInputLayout(m_pInputLayout);
#endif // DX12
}

//------------------------------------------------------------------------------
/// インプットレイアウトの開放
///
/// \return void
//------------------------------------------------------------------------------
void GfxVertexShader::ReleaseInputLayout()
{
    std::map<std::string, ID3D11InputLayout*>::iterator it = m_inputLayoutList.begin();
    while (it != m_inputLayoutList.end())
    {
        SAFE_RELEASE((it->second));
        ++it;
    }
}

//------------------------------------------------------------------------------
/// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
///
/// \param[in] pData シェーダーのデータへのポインタ
/// \param[in] size データの大きさ
/// 
/// \return シェーダー作成の成否
//------------------------------------------------------------------------------
HRESULT GfxVertexShader::MakeShader(void* pData, UINT size)
{
#ifdef DX12
    UNREFERENCED_PARAMETER(pData);
    UNREFERENCED_PARAMETER(size);

    return S_OK;
#else
    HRESULT hr;
    ID3D11Device* pDevice = D3D->GetDevice();

    /// シェーダー作成
    hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVS);
    if (FAILED(hr)) { return hr; }

    /*
    シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
    セマンティクスの配置などから識別子を作成
    識別子が登録済→再利用、なければ新規作成
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
        },
        {
            DXGI_FORMAT_R32_SINT,
            DXGI_FORMAT_R32G32_SINT,
            DXGI_FORMAT_R32G32B32_SINT,
            DXGI_FORMAT_R32G32B32A32_SINT,
        },
        {
            DXGI_FORMAT_R32_FLOAT,
            DXGI_FORMAT_R32G32_FLOAT,
            DXGI_FORMAT_R32G32B32_FLOAT,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
        },
    };

    hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
    if (FAILED(hr)) { return hr; }

    pReflection->GetDesc(&shaderDesc);
    pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
    for (int i = 0; i < (int)shaderDesc.InputParameters; ++i)
    {
        pReflection->GetInputParameterDesc(i, &sigDesc);
        pInputDesc[i].SemanticName = sigDesc.SemanticName;
        pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

        // http://marupeke296.com/TIPS_No17_Bit.html
        BYTE elementCount = sigDesc.Mask;
        elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
        elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);
        // 警告の対処　読み取り可能な範囲ではないときの処理を追加
        if (elementCount > 4)
        {
            continue;
        }

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
            key += '0' + (unsigned char)sigDesc.SemanticIndex;
        }

        std::map<std::string, ID3D11InputLayout*>::iterator it = m_inputLayoutList.begin();
        while (it != m_inputLayoutList.end())
        {
            if (it->first == key)
            {
                m_pInputLayout = it->second;
                break;
            }
            ++it;
        }
        if (it == m_inputLayoutList.end())
        {
            hr = pDevice->CreateInputLayout(
            pInputDesc, shaderDesc.InputParameters,
            pData, size, &m_pInputLayout
        );
        if (SUCCEEDED(hr))
        {
            m_inputLayoutList.insert(
            std::pair<std::string, ID3D11InputLayout*>(key, m_pInputLayout));
        }
    }

    delete[] pInputDesc;
    return hr;
#endif // DX12
}
