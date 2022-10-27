//==============================================================================
// Filename: Gfx_GraphicsResourceDefault.h
// Description: デフォルトリソースの生成
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __GRAPHICS_RESOURCE_DEFAULT_H__
#define __GRAPHICS_RESOURCE_DEFAULT_H__
    

#define PS_COLOR    ("ps_color")    
#define PIXEL_2D    ("PS2D")
#define LAMBERT     ("lambert")

#define VERTEX_2D    ("VS2D")
#define VERTEX_3D    ("VS3D")

#define CHECKER         ("tex_cheker")
#define TEX_DEFAULT     ("tex_white")

#define GEOMETORY_CUBE    ("geometory_cube")
#define GEOMETORY_SPRITE  ("geometory_cube")

#define WVP_MATRIX        ("matrix3")
#define CB_DEFAULT        ("cb_default")

// プロトタイプ宣言
void CreateGraphicsResource();

#endif // __GRAPHICS_RESOURCE_H__
