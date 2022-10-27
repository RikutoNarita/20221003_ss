//==============================================================================
// Filename: Gfx_GraphicsResource.h
// Description: ���\�[�X���o�C���h����N���X�̃x�[�X�N���X
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// �C���N���[�h�K�[�h
#ifndef __D3D11_GRAPHICS_BINDER_H__
#define __D3D11_GRAPHICS_BINDER_H__

// �C���N���[�h
#include <GraphicsSystem\Interface\Gfx_GraphiccsBinder.h>

// �N���X��`
class GfxD3D11GraphicsBinder : public GfxGraphicsBinder
{
public:
    //struct ResourceData
    //{
    //    GfxGraphicsObjectBase* pbuff;
    //};
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// �R���X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D11GraphicsBinder();

    //------------------------------------------------------------------------------
    /// �f�X�g���N�^
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual ~GfxD3D11GraphicsBinder();

    //------------------------------------------------------------------------------
    /// ���\�[�X��GPU�Ƀo�C���h����
    ///
    /// \return void
    //------------------------------------------------------------------------------
    virtual void Bind(unsigned slot = 0) const final;

    //------------------------------------------------------------------------------
    /// �p�C�v���C���̍\�z
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Start() const final;

    void BindMesh(GfxMeshBuffer* res) final;
    void BindPS(GfxPixelShader* res) final;
    void BindVS(GfxVertexShader* res) final;
    void BindTexture(GfxTexture* res, GfxShader::KIND shader, unsigned slot = 0) final;
    void BindConstantBuffer(GfxConstantBuffer* res, GfxShader::KIND shader, unsigned slot = 0) final;

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    static const UINT MAX_TEXTURE = 1;
    GfxTexture* m_pixelResourceSRV[MAX_TEXTURE];
    GfxTexture* m_vertexResourceSRV[MAX_TEXTURE];
    static const UINT MAX_CONSTANTBUFFER = 4;
    GfxConstantBuffer* m_pixelResourceCB[MAX_CONSTANTBUFFER];
    GfxConstantBuffer* m_vertexResourceCB[MAX_CONSTANTBUFFER];
    //------------------------------------------------------------------------------
    /// <summary>
    /// 
    /// </summary> 
};



#endif // __GRAPHICS_RESOURCE_H__
