//==============================================================================
// Filename: Gfx_Graphics.h
// Description: 描画管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルード
#include <GraphicsSystem\Interface\IGfx_Graphics.h>
#include <GraphicsSystem\Interface\Gfx_DXManager.h>
//#include <GraphicsSystem\Interface\Gfx_OpenGLManager_Impl.h>

#include <GraphicsSystem\Interface\Gfx_GraphicsResourceDefault.h>

// 静的メンバ
std::unique_ptr<IGfxGraphics> IGfxGraphics::m_pGraphics;
API_KIND     IGfxGraphics::m_eAPIKind;

//------------------------------------------------------------------------------
/// グラフィックスの生成
///
/// \param[in] apiKind APIの種類
/// 
/// \return void
//------------------------------------------------------------------------------
void IGfxGraphics::Create(API_KIND apiKind)
{
	m_eAPIKind = apiKind;

	switch (apiKind)
	{
	case API_KIND::DIRECT3D_11:
	case API_KIND::DIRECT3D_12:
		m_pGraphics = std::make_unique<GfxDXManager>();
		break;
	case API_KIND::OPEN_GL:
		//m_pGraphics = std::make_unique<GfxOpenGL>();
		break;
	case API_KIND::VULKAN:
		break;
	default:
		break;
	}

	// apiの初期化
	m_pGraphics->Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	// デフォルトのリソースの初期化
	CreateGraphicsResource();
}
