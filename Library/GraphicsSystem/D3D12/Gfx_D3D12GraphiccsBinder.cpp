// インクルード
#include <GraphicsSystem\D3D12\Gfx_D3D12GraphiccsBinder.h>
#include <GraphicsSystem\Interface\Gfx_GraphicsManager.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12PixelShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12VertexShader.h>
#include <GraphicsSystem\D3D12\Gfx_D3D12ConstantBuffer.h>

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12GraphicsBinder::GfxD3D12GraphicsBinder()
{
    m_pDescriptorHeap = std::make_shared<GfxD3D12DescriptorHeap>();
    m_pPipelineState  = std::make_shared<GfxPipelineState>();
    m_pRootSignature  = std::make_shared<GfxD3D12RootSignature>();
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
GfxD3D12GraphicsBinder::~GfxD3D12GraphicsBinder()
{
}

//------------------------------------------------------------------------------
/// リソースをGPUにバインドする
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::Bind(unsigned slot) const
{
    auto pCommandList = GRAPHICS->GetRenderCommand<ID3D12GraphicsCommandList>();

    // パイプラインをセット
    m_pPipelineState->Bind();
    // ルートシグネチャをセット
    m_pRootSignature->Bind();
    // ディスクリプタヒープをセット
    m_pDescriptorHeap->Bind();

    // 頂点バッファ、インデックスバッファのセット
    m_pMesh->Bind();
}

//------------------------------------------------------------------------------
/// パイプラインの構築
///
/// \return void
//------------------------------------------------------------------------------
void GfxD3D12GraphicsBinder::Start() const
{
    // ディスクリプタヒープの生成
    m_pDescriptorHeap->Start();

    // ルートシグネチャの作成
    m_pRootSignature->Create(m_pDescriptorHeap.get());

    // パイプラインの生成
    m_pPipelineState->Create(m_pRootSignature.get());
}


void GfxD3D12GraphicsBinder::BindMesh(GfxMeshBuffer* res)
{
    m_pMesh = res;
}
void GfxD3D12GraphicsBinder::BindPS(GfxPixelShader* res)
{
    m_pPipelineState->BindPS(dynamic_cast<GfxD3D12PixelShader*>(res));
}
void GfxD3D12GraphicsBinder::BindVS(GfxVertexShader* res)
{
    m_pPipelineState->BindVS(dynamic_cast<GfxD3D12VertexShader*>(res));
}

void GfxD3D12GraphicsBinder::BindTexture(GfxTexture* pTex, GfxShader::KIND shader, unsigned slot)
{
    m_pDescriptorHeap->BindSRV(
        slot,
        dynamic_cast<GfxD3D12Texture*>(pTex)->Get(),
        shader);
}

void GfxD3D12GraphicsBinder::BindConstantBuffer(GfxConstantBuffer* pBuff, GfxShader::KIND shader, unsigned slot)
{
    if (shader == GfxShader::KIND::KIND_PS)
    {
        m_pDescriptorHeap->BindCBV(
            slot,
            dynamic_cast<GfxD3D12ConstantBuffer*>(pBuff)->Get(),
            GfxShader::KIND::KIND_PS);
    }
    else
    {
        m_pDescriptorHeap->BindCBV(
            slot,
            dynamic_cast<GfxD3D12ConstantBuffer*>(pBuff)->Get(),
            GfxShader::KIND::KIND_VS);
    }
}
