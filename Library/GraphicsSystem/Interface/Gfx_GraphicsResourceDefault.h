//==============================================================================
// Filename: Gfx_GraphicsResourceDefault.h
// Description: デフォルトリソースの生成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_RESOURCE_DEFAULT_H__
#define __GRAPHICS_RESOURCE_DEFAULT_H__
    
//--- マクロ定義
// pixel shader
#define PS_COLOR    ("ps_color")    
#define PS_TEX      ("PS2D")
#define PS_LAMBERT  ("lambert")
// vertex shader
#define VERTEX_2D    ("VS2D")
#define VERTEX_3D    ("VS3D")
// texture
#define TEX_CHECKER     ("tex_cheker")
#define TEX_DEFAULT     ("tex_white")
// mesh
#define GEOMETORY_CUBE    ("geometory_cube")
#define GEOMETORY_SPRITE  ("geometory_sprite")
#define GEOMETORY_SPHERE  ("geometory_sphere")
// constant buffer
#define WVP_MATRIX        ("matrix3")
#define CB_DEFAULT        ("cb_default")
#define CB_LIGHT            ("light")

//-----------------------------------------------------------------------------
/// デフォルトリソースの作成し
///
/// \return void
//-----------------------------------------------------------------------------
void CreateGraphicsResource();

#endif // __GRAPHICS_RESOURCE_H__
