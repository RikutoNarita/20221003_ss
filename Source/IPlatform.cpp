//==============================================================================
// Filename: IPlatform.h
// Description: プラットフォームの基底クラス
// Copyright (C) 2013 Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <IPlatform.h>
#include <Platfrom_Windows_Impl.h>

// 静的メンバ
std::unique_ptr<IPlatform> IPlatform::m_pPlatform;
IPlatform::Description IPlatform::m_desc;

//------------------------------------------------------------------------------
/// ウィンドウ作成
/// 
/// \param[in] kind APIの種類
/// \param[in] desc プラットフォームの設定項目
/// 
/// \return 
//------------------------------------------------------------------------------
IPlatform* IPlatform::Make(API_KIND kind, Description desc)
{
	m_desc = desc;

	switch (kind)
	{
	case API_KIND::DIRECT3D_11:
	case API_KIND::DIRECT3D_12:
		m_pPlatform = std::make_unique<PlatformWindows>();
		break;
	case API_KIND::OPEN_GL:
	case API_KIND::VULKAN:
		break;
	default:
		break;
	}

	m_pPlatform->Init(m_desc);

	return m_pPlatform.get();
}