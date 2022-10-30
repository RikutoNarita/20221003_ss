//==============================================================================
// Filename: Gfx_D3D12DiscriptorHeap.h
// Description: ディスクリプタヒープクラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

// インクルードガード
#ifndef __D3D12_DISCRIPTOR_HEAP_H__
#define __D3D12_DISCRIPTOR_HEAP_H__

// インクルード
#include <GraphicsSystem\Interface\Gfx_GraphicsResource.h>
#include <GraphicsSystem\Interface\Gfx_Shader.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>

// クラス定義
class GfxD3D12DescriptorHeap : GfxGraphicsObject<GfxD3D12DescriptorHeap>
{
    friend class GfxD3D12RootSignature;
public:
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3D12DescriptorHeap();
    
    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3D12DescriptorHeap();

    //------------------------------------------------------------------------------
    /// ディスクリプタヒープの作成
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Create();

    //------------------------------------------------------------------------------
    /// ディスクリプタヒープのバインド
    /// 
    /// \param[in] slot レジスタ番号
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void Bind(
        /*[in]*/
        unsigned int slot = 0) const final;
    
    //------------------------------------------------------------------------------
    /// テクスチャのセット
    ///
    /// \pramga[in] res     テクスチャリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindSRV(
        /*[in]*/
        ID3D12Resource* data,
        /*[in]*/
        GfxShader::KIND visible,
        /*[in]*/
        UINT slot);
    
    //------------------------------------------------------------------------------
    /// 定数バッファのセット
    ///
    /// \pramga[in] res     定数バッファリソース
    /// \pramga[in] shader  シェーダーの種類
    /// \pramga[in] slot    レジスタ番号
    /// 
    /// \return void
    //------------------------------------------------------------------------------
    void BindCBV(
        /*[in]*/
        ID3D12Resource* data,
        /*[in]*/
        GfxShader::KIND visible,
        /*[in]*/
        UINT slot);

    //------------------------------------------------------------------------------
    /// ディスクリプタヒープの取得
    ///
    /// \return ディスクリプタヒープ
    //------------------------------------------------------------------------------
    inline const ID3D12DescriptorHeap* Get() const
    {
        m_pSRVandCSBheap.Get();
    }

    //------------------------------------------------------------------------------

private:
    //------------------------------------------------------------------------------
    static const UINT MAX_ROOT_PARAM = 2;
    static const UINT MAX_DHISCTIPTOR = MAX_ROOT_PARAM * 2; // rootparamer * シェーダーの種類(ps, vs)
    static const UINT MAX_TEXTURE = 1;
    static const UINT MAX_CONSTANTBUFFER = 4;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pSRVandCSBheap;
    D3D12_ROOT_PARAMETER m_rootParameters[MAX_ROOT_PARAM];
    D3D12_DESCRIPTOR_RANGE m_descriptorTableRange[MAX_DHISCTIPTOR];
    ID3D12Resource* m_pixelResourceSRV[MAX_TEXTURE];
    ID3D12Resource* m_vertexResourceSRV[MAX_TEXTURE];
    ID3D12Resource* m_pixelResourceCBV[MAX_CONSTANTBUFFER];
    ID3D12Resource* m_vertexResourceCBV[MAX_CONSTANTBUFFER];
    UINT m_descriptorHandleIncrementSize;
    int m_nNumPixelHeap;
    //------------------------------------------------------------------------------
    /// <summary>
    /// MAX_ROOT_PARAM                  ルートパラメーターの数
    /// MAX_DHISCTIPTOR                 ディスクリプタレンジの数
    /// MAX_TEXTURE                     テクスチャの最大数
    /// MAX_CONSTANTBUFFER              定数バッファの最大数
    /// m_pSRVandCSBheap                ディスクリプタヒープ
    /// m_rootParameters                ルートパラメータ
    /// m_descriptorTableRange          ディスクリプタレンジ
    /// m_pixelResourceSRV              ピクセルシェーダーに送るシェーダーリソースビュー
    /// m_vertexResourceSRV             頂点シェーダーに送るシェーダーリソースビュー
    /// m_pixelResourceCBV              ピクセルシェーダーに送る定数バッファビュー
    /// m_vertexResourceCBV             頂点シェーダーに送る定数バッファビュー
    /// m_descriptorHandleIncrementSize SRV,CBVのインクリメントサイズ格納用
    /// m_nNumPixelHeap                 ピクセルシェーダーに送るリソースの数
    /// </summary> 
};
#endif // __D3D12_DISCRIPTOR_HEAP_H__
