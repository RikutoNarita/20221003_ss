//==============================================================================
// Filename: Gfx_GraphicsResourceDefault.h
// Description: �f�t�H���g���\�[�X�̐���
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __GRAPHICS_RESOURCE_DEFAULT_H__
#define __GRAPHICS_RESOURCE_DEFAULT_H__
    
//--- �}�N����`
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
/// �f�t�H���g���\�[�X�̍쐬��
///
/// \return void
//-----------------------------------------------------------------------------
void CreateGraphicsResource();

#endif // __GRAPHICS_RESOURCE_H__
