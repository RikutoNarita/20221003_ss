//==============================================================================
// Filename: DirectX.h
// Description: DirectX11 or 12 の管理クラス
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

//! インクルードガード
#ifndef __D3D_MANAGER_H__
#define __D3D_MANAGER_H__

#if 1
//! インクルード
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>

//! マクロ定義
#define D3D (GfxD3DManager::GetInstance())

//! DirectXMathがDirectXのネームスペースにある
using namespace DirectX;
using namespace std;
//! ComPtr(DirectX版のスマートポインタ)
using Microsoft::WRL::ComPtr;

//! クラス定義
class GfxD3DManager
{
public:
    //---------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    /// デストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    ~GfxD3DManager();

    //------------------------------------------------------------------------------
    /// D3Dの初期化
    ///
    /// \return 初期化処理の成否
    //------------------------------------------------------------------------------
    HRESULT Init(HWND hWnd, UINT width, UINT height);

    //------------------------------------------------------------------------------
    /// インスタンス作成
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void CreateInstance();

    //------------------------------------------------------------------------------
    /// インスタンス取得
    ///
    /// \return クラスのインスタンス
    //------------------------------------------------------------------------------
    static GfxD3DManager* GetInstance();

    //------------------------------------------------------------------------------
    /// インスタンス削除
    ///
    /// \return void
    //------------------------------------------------------------------------------
    static void DeleteInstance();


    //------------------------------------------------------------------------------
    /// デバイスの取得
    ///
    /// \return デバイスのポインタ
    //------------------------------------------------------------------------------
    inline ID3D11Device* GetDevice() const
    {
        return m_pDevice.Get();
    }
   
    //------------------------------------------------------------------------------
    /// スワップチェーンの取得
    ///
    /// \return スワップチェーンのポインタ
    //------------------------------------------------------------------------------
    inline IDXGISwapChain* GetSwapChain() const
    {
        return m_pSwapChain.Get();
    }

    //------------------------------------------------------------------------------
    /// デバイスコンテキストの取得
    ///
    /// \return デバイスコンテキストのポインタ
    //------------------------------------------------------------------------------
    inline ID3D11DeviceContext* GetDeviceContext() const
    {
        return m_pDeviceContext.Get();
    }

    //------------------------------------------------------------------------------
    /// 描画の開始(バックバッファ＆Ｚバッファのクリア)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void BeginDraw();

    //------------------------------------------------------------------------------
    /// 描画の修了(バックバッファとフロントバッファの入れ替え)
    ///
    /// \return void
    //------------------------------------------------------------------------------
    void EndDraw();

    //---------------------------------------------------------------------------

private:

    //---------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------
    /// コンストラクタ
    ///
    /// \return void
    //------------------------------------------------------------------------------
    GfxD3DManager();
    
    //---------------------------------------------------------------------------
    
    //---------------------------------------------------------------------------
    static GfxD3DManager* m_pInstance;
    ComPtr<ID3D11Device>            m_pDevice;
    ComPtr<IDXGISwapChain>          m_pSwapChain;
    ComPtr<ID3D11DeviceContext>     m_pDeviceContext;
    ComPtr<ID3D11RenderTargetView>  m_pRentderTarget;
    //ComPtr<ID3D11Texture2D>         m_pTexrure2D ;
    //ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
    //ComPtr<ID3D11RasterizerState>   m_pRasterizerState;
    //ComPtr<ID3D11BlendState>        m_pBlendState;
    //ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pDevice               デバイス
    /// m_pSwapChain            スワップチェーン
    /// m_pDeviceContext        デバイスコンテキスト
    /// m_pTexrure2D            2Dテクスチャ
    /// ID3D11RenderTargetView  レンダーターゲットビュー
    /// m_pDepthStencilView     デプスステンシルビュー
    /// m_pRasterizerState      ラスタライザステート
    /// m_pBlendState           アルファブレンディング
    /// m_pDepthStencilState    デプスステンシルステート
    /// </summary> 
};

#else

//! 列挙体定義
//enum EBlendState {
//    BS_NONE = 0,          //! 半透明合成無し
//    BS_ALPHABLEND,        //! 半透明合成
//    BS_ADDITIVE,          //! 加算合成
//    BS_SUBTRACTION,       //! 減算合成
//
//    MAX_BLENDSTATE
//};
//
//enum ECullMode {
//    CULLMODE_NONE = 0,    //! カリングしない
//    CULLMODE_CW,          //! 前面カリング
//    CULLMODE_CCW,         //! 背面カリング
//
//    MAX_CULLMODE
//};
//
////! プロトタイプ宣言
//HRESULT InitDirectX(HWND hWnd, UINT width, UINT height, bool fullscreen);
//
//ID3D11Device* GetDevice();
//IDXGISwapChain* GetSwapChain();
//ID3D11DeviceContext* GetDeviceContext();
//HRESULT CreateBackBuffer();
//void ReleaseBackBuffer();
//void ReleaseDirectX();
//void SetZBuffer(bool bEnable);
//void SetZWrite(bool bEnable);
//void SetBlendState(int nBlendState);
//void SetCullMode(int nCullMode);
//
//void ClearScreen();
//void Swap();

#endif // 0

#endif //! __D3D_MANAGER_H__
