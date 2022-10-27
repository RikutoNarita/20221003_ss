//==============================================================================
// Filename: Gfx_Tag.h
// Description: グラフィックオブジェクトを識別するタグクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\Gfx_Tag.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \param[in] name タグの名前
/// 
/// \return void
//------------------------------------------------------------------------------
GfxTag::GfxTag(const char* name)
: m_name(name)
{
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxTag::~GfxTag()
{
}

bool GfxTag::operator==(const GfxTag& tag) const
{
    return m_name == tag.m_name;
}
bool GfxTag::operator!=(const GfxTag& tag) const
{
    return m_name != tag.m_name;
}
bool GfxTag::operator<(const GfxTag& tag) const
{
    return m_name < tag.m_name;
}