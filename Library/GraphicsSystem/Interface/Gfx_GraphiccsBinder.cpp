#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D11\Gfx_D3D11GraphiccsBinder.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12GraphiccsBinder.h>

GfxGraphicsBinder::Ptr GfxGraphicsBinder::Create(const GfxTag& tag)
{
    GfxGraphicsBinder::Ptr pBinder;

    switch (GRAPHICS->GetAPIKind())
    {
    case GfxGraphicsManager::API_KIND::DIRECT3D_11: // Direct3D 11
    {
        pBinder = std::make_shared<GfxD3D11GraphicsBinder>();
        break;
    }
    case GfxGraphicsManager::API_KIND::DIRECT3D_12: // Direct3D 12
    {
        pBinder = std::make_shared<GfxD3D12GraphicsBinder>();
        break;
    }

    case GfxGraphicsManager::API_KIND::OPEN_GL: break;
    case GfxGraphicsManager::API_KIND::VULKAN: break;
    default: break;
    }

    // 登録
    GfxGraphicsResource::Resister(tag, pBinder);

    return pBinder;
}