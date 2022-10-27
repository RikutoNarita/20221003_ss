// インクルード
#include <CoreSystem/Input.h>
#include <Win_Window.h>
#include <memory.h>

// ライブラリリンク
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// グローバル変数
LPDIRECTINPUT8       lpDI           = nullptr;  // DirectInputオブジェクト
LPDIRECTINPUTDEVICE8 lpKeyboard     = nullptr;  // キーボードデバイス
LPDIRECTINPUTDEVICE8 lpMousewDevice = nullptr;  // マウスデバイス

// 静的メンバ変数
CInput* CInput::m_pInstance = nullptr;

//------------------------------------------------------------------------------
/// コンストラクタ
///
/// \return void
//------------------------------------------------------------------------------
CInput::CInput()
{
    // メンバ変数の初期化
    SecureZeroMemory(m_currentKeyState, sizeof(m_currentKeyState));
    SecureZeroMemory(m_prevKeyState, sizeof(m_prevKeyState));
    m_mousePos = DirectX::XMFLOAT2(0.0f, 0.0f);
    m_currentMouseState = {};
    m_prevMouseState = {};
}

//------------------------------------------------------------------------------
/// デストラクタ
///
/// \return void
//------------------------------------------------------------------------------
CInput::~CInput()
{
}

//------------------------------------------------------------------------------
/// インスタンスの取得
/// 
/// \return クラスのインスタンス
//------------------------------------------------------------------------------
CInput* CInput::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new CInput();
    }
    return m_pInstance;
}

//------------------------------------------------------------------------------
/// 入力の終了処理
/// 
/// \return void
//------------------------------------------------------------------------------
void CInput::Uninit()
{
    //    デバイス制御停止
    lpKeyboard->Unacquire();
    lpMousewDevice->Unacquire();

    //    開放
    lpMousewDevice->Release();
    lpKeyboard->Release();
    lpDI->Release();

    //    インスタンス破棄
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

//------------------------------------------------------------------------------
/// 入力の初期化
/// 
/// \return 初期化の成否
//------------------------------------------------------------------------------
HRESULT CInput::Init()
{
    HRESULT ret = S_OK;

    // IDirectInput8の作成
    // (DirectInput8の構築に成功した場合にそのポインタの入るのはLPDIRECTINPUT8の変数のポインタ)
    ret = DirectInput8Create(
    WINDOW->GetInstance(),
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    (LPVOID*)&lpDI, NULL);
    if (FAILED(ret))
    {
        // 作成に失敗
        return ret;
    }

    //    キーボード初期化
    ret = InitKeyBoard();
    if (FAILED(ret))
    {
        return ret;
    }

    //    マウス初期化
    ret = InitMouse();
    if (FAILED(ret))
    {
        return ret;
    }

    return ret;
}

//------------------------------------------------------------------------------
/// キーボード初期化
///
/// \return 初期化の成否
//------------------------------------------------------------------------------
HRESULT CInput::InitKeyBoard()
{
    //    IDirectInputDevice8の取得
    HRESULT ret = lpDI->CreateDevice(
        GUID_SysKeyboard,    //第1引数は入力デバイスのGUID、ここではデフォルトのシステムキーボードということでGUID_SysKeyboardを定義
        &lpKeyboard,        //第2引数には取得したデバイスオブジェクトが入る変数のポインタ
        NULL);
    if (FAILED(ret))
    {
        lpDI->Release();
        return E_FAIL;
    }

    //    入力データ形式のセット
    ret = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(ret)) {
        lpKeyboard->Release();
        lpDI->Release();
        return E_FAIL;
    }

    //    排他制御のセット
    ret = lpKeyboard->SetCooperativeLevel(WINDOW->GetWndHandle(),
        DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    if (FAILED(ret)) {

        lpKeyboard->Release();
        lpDI->Release();
        return E_FAIL;
    }

    // 動作開始
    lpKeyboard->Acquire();

    return ret;
}

//------------------------------------------------------------------------------
/// マウス初期化
///
/// \return 初期化の成否
//------------------------------------------------------------------------------
HRESULT CInput::InitMouse()
{
    //    マウス用にデバイスオブジェクトを作成
    HRESULT ret = lpDI->CreateDevice(
        GUID_SysMouse, 
        &lpMousewDevice, 
        NULL);
    if (FAILED(ret))
    {
        lpDI->Release();
        return E_FAIL;
    }

    //    入力データ形式のセット
    ret = lpMousewDevice->SetDataFormat(&c_dfDIMouse);    // マウス用のデータ・フォーマットを設定
    if (FAILED(ret))
    {
        // データフォーマットに失敗
        return E_FAIL;
    }

    /*    排他制御のセット
    * 
    *   DISCL_EXCLUSIVE    他のアプリケーションはその入力デバイスを取得できない
    *   DISCL_NONEXCLUSIVE 他のアプリケーションでもそのまま入力デバイスの取得ができる
    *
    *   DISCL_FOREGROUND   ウィンドウがバックグラウンドに移動したらデバイスの取得ができない
    *   DISCL_BACKGROUND   ウィンドウが非アクティブ状態でもデバイスが取得できる
    *
    */
    ret = lpMousewDevice->SetCooperativeLevel(WINDOW->GetWndHandle(),
        DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    if (FAILED(ret))
    {
        return E_FAIL;
    }

    //    デバイスの設定
    DIPROPDWORD diprop;
    diprop.diph.dwSize = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj = 0;
    diprop.diph.dwHow = DIPH_DEVICE;
    diprop.dwData = DIPROPAXISMODE_REL;    // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

    ret = lpMousewDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
    if (FAILED(ret))
    {
        // デバイスの設定に失敗
        return E_FAIL;
    }

    //    動作開始
    lpMousewDevice->Acquire();

    return ret;
}

//------------------------------------------------------------------------------
/// 入力の更新処理
/// 
/// \return void
//------------------------------------------------------------------------------
void CInput::Update()
{
    //    キーボード入力更新
    UpdateKeyBoard();

    //    マウス更新
    UpdateMouse();
}

//------------------------------------------------------------------------------
/// キーボード更新
///
/// \return void
//------------------------------------------------------------------------------
void CInput::UpdateKeyBoard()
{
    // キー入力情報の退避
    memcpy_s(m_prevKeyState, KEY_MAX, m_currentKeyState, KEY_MAX);

    // キー入力情報のクリア
    SecureZeroMemory(m_currentKeyState, sizeof(m_currentKeyState));

    // キー入力情報の取得
    HRESULT ret = lpKeyboard->GetDeviceState(sizeof(m_currentKeyState), m_currentKeyState);
    if (FAILED(ret))    // 失敗なら再開させてもう一度取得
    {
        // 動作再開
        lpKeyboard->Acquire();

        // キー入力情報の取得
        lpKeyboard->GetDeviceState(sizeof(m_currentKeyState), m_currentKeyState);
    }
}

//------------------------------------------------------------------------------
/// マウス更新
///
/// \return void
//------------------------------------------------------------------------------
void CInput::UpdateMouse()
{
    // マウス情報の退避
    m_prevMouseState = m_currentMouseState;

    // マウス情報の取得
    HRESULT    hr = lpMousewDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
    if (FAILED(hr))
    {
        // 動作再開
        lpMousewDevice->Acquire();

        // マウス情報を再取得
        hr = lpMousewDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
    }

    // マウス座標を取得する
    POINT p;
    GetCursorPos(&p);

    // スクリーン座標をクライアント座標に変換する
    ScreenToClient(WINDOW->GetWndHandle(), &p);

    // マウスの移動量計算
    m_mousePos = DirectX::XMFLOAT2((float)(p.x - SCREEN_CENTER_X), -(float)(p.y - SCREEN_CENTER_Y));
}


//------------------------------------------------------------------------------
/// キーボードのプレス状態を取得
/// 
/// \param[in] key 入力状態を確認したいキー
/// 
/// \return キーボードのプレス状態
//------------------------------------------------------------------------------
bool CInput::GetKeyPress(unsigned char key)
{
    return (m_currentKeyState[key] & 0x80);
}

//------------------------------------------------------------------------------
/// キーボードのトリガ状態を取得
/// 
/// \param[in] key 入力状態を確認したいキー
/// 
/// \return キーボードのトリガ状態
//------------------------------------------------------------------------------
bool CInput::GetKeyTrigger(unsigned char key)
{
    //    前フレームに押されていない && 現在押されている
    return (m_currentKeyState[key] & 0x80) &&
            !(m_prevKeyState[key] & 0x80);
}

//------------------------------------------------------------------------------
/// キーボードのリリース状態を取得
/// 
/// \param[in] key 入力状態を確認したいキー
/// 
/// \return キーボードのリリース状態
//------------------------------------------------------------------------------
bool CInput::GetKeyRelease(unsigned char key)
{
    //    前フレームに押されている && 現在押されていない
    return ((m_prevKeyState[key] & 0x80) &&
            !(m_currentKeyState[key] & 0x80));
}

//------------------------------------------------------------------------------
/// マウスのプレス状態を取得
/// 
/// \param[in] Btn 入力状態を確認したいボタン
/// 
/// \return マウスのプレス状態
//------------------------------------------------------------------------------
bool CInput::GetMouseButton(MOUSE_BUTTON Btn)
{
    return (m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80);
}

//------------------------------------------------------------------------------
/// マウスのトリガ状態を取得
/// 
/// \param[in] Btn 入力状態を確認したいボタン
/// 
/// \return マウスのトリガ状態
//------------------------------------------------------------------------------
bool CInput::GetMouseTrigger(MOUSE_BUTTON Btn)
{
    //    前フレームにクリックされていない && 現在クリックされている
    return (!(m_prevMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80) &&
            m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80);
    
}

//------------------------------------------------------------------------------
/// マウスのリリース状態を取得
/// 
/// \param[in] Btn 入力状態を確認したいボタン
/// 
/// \return マウスのリリース状態
//------------------------------------------------------------------------------
bool CInput::GetMouseRelease(MOUSE_BUTTON Btn)
{
    //    前フレームにクリックされている && 現在クリックされていない
    return (m_prevMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80 &&
            !(m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80));
}

//------------------------------------------------------------------------------
/// マウス座標の取得
/// 
/// \return マウス座標
//------------------------------------------------------------------------------
DirectX::XMFLOAT2 CInput::GetMousePos() const
{
    return m_mousePos;
}

//------------------------------------------------------------------------------
/// マウスの移動量の取得
/// 
/// \return マウスの移動量
//------------------------------------------------------------------------------
DirectX::XMFLOAT2 CInput::GetMouseVelocity() const
{
    return DirectX::XMFLOAT2((float)m_currentMouseState.lX, (float)-m_currentMouseState.lY);
}
