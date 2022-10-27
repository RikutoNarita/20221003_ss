// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>

std::map<GfxTag, GfxGraphicsObjectBase::Ptr> GfxGraphicsResource::m_resources;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsResource::GfxGraphicsResource()
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxGraphicsResource::~GfxGraphicsResource()
{

}

//------------------------------------------------------------------------------
/// リソースの登録
///
/// \param[in] tag
/// \param[in] pResource
/// 
/// \return void
//------------------------------------------------------------------------------
void GfxGraphicsResource::Resister(
    const GfxTag& tag, GfxGraphicsObjectBase::Ptr pResource)
{
    m_resources.insert(std::pair<GfxTag, GfxGraphicsObjectBase::Ptr>(tag, pResource));
}