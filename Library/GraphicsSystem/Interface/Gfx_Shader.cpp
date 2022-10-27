// インクルード
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <wrl\client.h>
#include <dxgi.h>
#include <d3d12.h>
#include <vector>

#include <GraphicsSystem\D3D11\Gfx_D3D11VertexShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>

#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] shader
/// 
/// \return void
//------------------------------------------------------------------------------
GfxShader::GfxShader(KIND kind)
: m_kind(kind), m_buffers{nullptr}, m_textures{nullptr}
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxShader::~GfxShader()
{
}

GfxShader::Ptr GfxShader::Compile(const GfxTag& tag, const KIND& kind, const wchar_t* fileName)
{
    GfxShader::Ptr pShader;

    switch (GRAPHICS->GetAPIKind())
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11
    {
        if (kind == KIND::KIND_VS)
        {
            // vertex shader
            pShader = std::make_shared<GfxD3D11VertexShader>(fileName);

            // リソースに登録
            GfxGraphicsResource::Resister(tag, pShader);
        }
        else if (kind == KIND::KIND_PS)
        {
            // pixel shader
            pShader = std::make_shared<GfxD3D11PixelShader>(fileName);

            // リソースに登録
            GfxGraphicsResource::Resister(tag, pShader);
        }

        break;  
    }
    case GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12
    {
        if (kind == KIND::KIND_VS)
        {
            // vertex shader
            pShader = std::make_shared<GfxD3D12VertexShader>(fileName);

            // リソースに登録
            GfxGraphicsResource::Resister(tag, pShader);
        }
        else if (kind == KIND::KIND_PS)
        {
            // pixel shader
            pShader = std::make_shared<GfxD3D12PixelShader>(fileName);

            // リソースに登録
            GfxGraphicsResource::Resister(tag, pShader);
        }

        break;
    }

    case GfxGraphicsManager::API_KIND::OPEN_GL: break;
    case GfxGraphicsManager::API_KIND::VULKAN: break;
    default: break;
    }

    return pShader;
}
