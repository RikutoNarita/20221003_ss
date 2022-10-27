// �C���N���[�h
#include <CoreSystem/Input.h>
#include <Win_Window.h>
#include <memory.h>

// ���C�u���������N
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// �O���[�o���ϐ�
LPDIRECTINPUT8       lpDI           = nullptr;  // DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 lpKeyboard     = nullptr;  // �L�[�{�[�h�f�o�C�X
LPDIRECTINPUTDEVICE8 lpMousewDevice = nullptr;  // �}�E�X�f�o�C�X

// �ÓI�����o�ϐ�
CInput* CInput::m_pInstance = nullptr;

//------------------------------------------------------------------------------
/// �R���X�g���N�^
///
/// \return void
//------------------------------------------------------------------------------
CInput::CInput()
{
    // �����o�ϐ��̏�����
    SecureZeroMemory(m_currentKeyState, sizeof(m_currentKeyState));
    SecureZeroMemory(m_prevKeyState, sizeof(m_prevKeyState));
    m_mousePos = DirectX::XMFLOAT2(0.0f, 0.0f);
    m_currentMouseState = {};
    m_prevMouseState = {};
}

//------------------------------------------------------------------------------
/// �f�X�g���N�^
///
/// \return void
//------------------------------------------------------------------------------
CInput::~CInput()
{
}

//------------------------------------------------------------------------------
/// �C���X�^���X�̎擾
/// 
/// \return �N���X�̃C���X�^���X
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
/// ���͂̏I������
/// 
/// \return void
//------------------------------------------------------------------------------
void CInput::Uninit()
{
    //    �f�o�C�X�����~
    lpKeyboard->Unacquire();
    lpMousewDevice->Unacquire();

    //    �J��
    lpMousewDevice->Release();
    lpKeyboard->Release();
    lpDI->Release();

    //    �C���X�^���X�j��
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

//------------------------------------------------------------------------------
/// ���͂̏�����
/// 
/// \return �������̐���
//------------------------------------------------------------------------------
HRESULT CInput::Init()
{
    HRESULT ret = S_OK;

    // IDirectInput8�̍쐬
    // (DirectInput8�̍\�z�ɐ��������ꍇ�ɂ��̃|�C���^�̓���̂�LPDIRECTINPUT8�̕ϐ��̃|�C���^)
    ret = DirectInput8Create(
    WINDOW->GetInstance(),
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    (LPVOID*)&lpDI, NULL);
    if (FAILED(ret))
    {
        // �쐬�Ɏ��s
        return ret;
    }

    //    �L�[�{�[�h������
    ret = InitKeyBoard();
    if (FAILED(ret))
    {
        return ret;
    }

    //    �}�E�X������
    ret = InitMouse();
    if (FAILED(ret))
    {
        return ret;
    }

    return ret;
}

//------------------------------------------------------------------------------
/// �L�[�{�[�h������
///
/// \return �������̐���
//------------------------------------------------------------------------------
HRESULT CInput::InitKeyBoard()
{
    //    IDirectInputDevice8�̎擾
    HRESULT ret = lpDI->CreateDevice(
        GUID_SysKeyboard,    //��1�����͓��̓f�o�C�X��GUID�A�����ł̓f�t�H���g�̃V�X�e���L�[�{�[�h�Ƃ������Ƃ�GUID_SysKeyboard���`
        &lpKeyboard,        //��2�����ɂ͎擾�����f�o�C�X�I�u�W�F�N�g������ϐ��̃|�C���^
        NULL);
    if (FAILED(ret))
    {
        lpDI->Release();
        return E_FAIL;
    }

    //    ���̓f�[�^�`���̃Z�b�g
    ret = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(ret)) {
        lpKeyboard->Release();
        lpDI->Release();
        return E_FAIL;
    }

    //    �r������̃Z�b�g
    ret = lpKeyboard->SetCooperativeLevel(WINDOW->GetWndHandle(),
        DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    if (FAILED(ret)) {

        lpKeyboard->Release();
        lpDI->Release();
        return E_FAIL;
    }

    // ����J�n
    lpKeyboard->Acquire();

    return ret;
}

//------------------------------------------------------------------------------
/// �}�E�X������
///
/// \return �������̐���
//------------------------------------------------------------------------------
HRESULT CInput::InitMouse()
{
    //    �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
    HRESULT ret = lpDI->CreateDevice(
        GUID_SysMouse, 
        &lpMousewDevice, 
        NULL);
    if (FAILED(ret))
    {
        lpDI->Release();
        return E_FAIL;
    }

    //    ���̓f�[�^�`���̃Z�b�g
    ret = lpMousewDevice->SetDataFormat(&c_dfDIMouse);    // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
    if (FAILED(ret))
    {
        // �f�[�^�t�H�[�}�b�g�Ɏ��s
        return E_FAIL;
    }

    /*    �r������̃Z�b�g
    * 
    *   DISCL_EXCLUSIVE    ���̃A�v���P�[�V�����͂��̓��̓f�o�C�X���擾�ł��Ȃ�
    *   DISCL_NONEXCLUSIVE ���̃A�v���P�[�V�����ł����̂܂ܓ��̓f�o�C�X�̎擾���ł���
    *
    *   DISCL_FOREGROUND   �E�B���h�E���o�b�N�O���E���h�Ɉړ�������f�o�C�X�̎擾���ł��Ȃ�
    *   DISCL_BACKGROUND   �E�B���h�E����A�N�e�B�u��Ԃł��f�o�C�X���擾�ł���
    *
    */
    ret = lpMousewDevice->SetCooperativeLevel(WINDOW->GetWndHandle(),
        DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    if (FAILED(ret))
    {
        return E_FAIL;
    }

    //    �f�o�C�X�̐ݒ�
    DIPROPDWORD diprop;
    diprop.diph.dwSize = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj = 0;
    diprop.diph.dwHow = DIPH_DEVICE;
    diprop.dwData = DIPROPAXISMODE_REL;    // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

    ret = lpMousewDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
    if (FAILED(ret))
    {
        // �f�o�C�X�̐ݒ�Ɏ��s
        return E_FAIL;
    }

    //    ����J�n
    lpMousewDevice->Acquire();

    return ret;
}

//------------------------------------------------------------------------------
/// ���͂̍X�V����
/// 
/// \return void
//------------------------------------------------------------------------------
void CInput::Update()
{
    //    �L�[�{�[�h���͍X�V
    UpdateKeyBoard();

    //    �}�E�X�X�V
    UpdateMouse();
}

//------------------------------------------------------------------------------
/// �L�[�{�[�h�X�V
///
/// \return void
//------------------------------------------------------------------------------
void CInput::UpdateKeyBoard()
{
    // �L�[���͏��̑ޔ�
    memcpy_s(m_prevKeyState, KEY_MAX, m_currentKeyState, KEY_MAX);

    // �L�[���͏��̃N���A
    SecureZeroMemory(m_currentKeyState, sizeof(m_currentKeyState));

    // �L�[���͏��̎擾
    HRESULT ret = lpKeyboard->GetDeviceState(sizeof(m_currentKeyState), m_currentKeyState);
    if (FAILED(ret))    // ���s�Ȃ�ĊJ�����Ă�����x�擾
    {
        // ����ĊJ
        lpKeyboard->Acquire();

        // �L�[���͏��̎擾
        lpKeyboard->GetDeviceState(sizeof(m_currentKeyState), m_currentKeyState);
    }
}

//------------------------------------------------------------------------------
/// �}�E�X�X�V
///
/// \return void
//------------------------------------------------------------------------------
void CInput::UpdateMouse()
{
    // �}�E�X���̑ޔ�
    m_prevMouseState = m_currentMouseState;

    // �}�E�X���̎擾
    HRESULT    hr = lpMousewDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
    if (FAILED(hr))
    {
        // ����ĊJ
        lpMousewDevice->Acquire();

        // �}�E�X�����Ď擾
        hr = lpMousewDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
    }

    // �}�E�X���W���擾����
    POINT p;
    GetCursorPos(&p);

    // �X�N���[�����W���N���C�A���g���W�ɕϊ�����
    ScreenToClient(WINDOW->GetWndHandle(), &p);

    // �}�E�X�̈ړ��ʌv�Z
    m_mousePos = DirectX::XMFLOAT2((float)(p.x - SCREEN_CENTER_X), -(float)(p.y - SCREEN_CENTER_Y));
}


//------------------------------------------------------------------------------
/// �L�[�{�[�h�̃v���X��Ԃ��擾
/// 
/// \param[in] key ���͏�Ԃ��m�F�������L�[
/// 
/// \return �L�[�{�[�h�̃v���X���
//------------------------------------------------------------------------------
bool CInput::GetKeyPress(unsigned char key)
{
    return (m_currentKeyState[key] & 0x80);
}

//------------------------------------------------------------------------------
/// �L�[�{�[�h�̃g���K��Ԃ��擾
/// 
/// \param[in] key ���͏�Ԃ��m�F�������L�[
/// 
/// \return �L�[�{�[�h�̃g���K���
//------------------------------------------------------------------------------
bool CInput::GetKeyTrigger(unsigned char key)
{
    //    �O�t���[���ɉ�����Ă��Ȃ� && ���݉�����Ă���
    return (m_currentKeyState[key] & 0x80) &&
            !(m_prevKeyState[key] & 0x80);
}

//------------------------------------------------------------------------------
/// �L�[�{�[�h�̃����[�X��Ԃ��擾
/// 
/// \param[in] key ���͏�Ԃ��m�F�������L�[
/// 
/// \return �L�[�{�[�h�̃����[�X���
//------------------------------------------------------------------------------
bool CInput::GetKeyRelease(unsigned char key)
{
    //    �O�t���[���ɉ�����Ă��� && ���݉�����Ă��Ȃ�
    return ((m_prevKeyState[key] & 0x80) &&
            !(m_currentKeyState[key] & 0x80));
}

//------------------------------------------------------------------------------
/// �}�E�X�̃v���X��Ԃ��擾
/// 
/// \param[in] Btn ���͏�Ԃ��m�F�������{�^��
/// 
/// \return �}�E�X�̃v���X���
//------------------------------------------------------------------------------
bool CInput::GetMouseButton(MOUSE_BUTTON Btn)
{
    return (m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80);
}

//------------------------------------------------------------------------------
/// �}�E�X�̃g���K��Ԃ��擾
/// 
/// \param[in] Btn ���͏�Ԃ��m�F�������{�^��
/// 
/// \return �}�E�X�̃g���K���
//------------------------------------------------------------------------------
bool CInput::GetMouseTrigger(MOUSE_BUTTON Btn)
{
    //    �O�t���[���ɃN���b�N����Ă��Ȃ� && ���݃N���b�N����Ă���
    return (!(m_prevMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80) &&
            m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80);
    
}

//------------------------------------------------------------------------------
/// �}�E�X�̃����[�X��Ԃ��擾
/// 
/// \param[in] Btn ���͏�Ԃ��m�F�������{�^��
/// 
/// \return �}�E�X�̃����[�X���
//------------------------------------------------------------------------------
bool CInput::GetMouseRelease(MOUSE_BUTTON Btn)
{
    //    �O�t���[���ɃN���b�N����Ă��� && ���݃N���b�N����Ă��Ȃ�
    return (m_prevMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80 &&
            !(m_currentMouseState.rgbButtons[static_cast<int>(Btn)] & 0x80));
}

//------------------------------------------------------------------------------
/// �}�E�X���W�̎擾
/// 
/// \return �}�E�X���W
//------------------------------------------------------------------------------
DirectX::XMFLOAT2 CInput::GetMousePos() const
{
    return m_mousePos;
}

//------------------------------------------------------------------------------
/// �}�E�X�̈ړ��ʂ̎擾
/// 
/// \return �}�E�X�̈ړ���
//------------------------------------------------------------------------------
DirectX::XMFLOAT2 CInput::GetMouseVelocity() const
{
    return DirectX::XMFLOAT2((float)m_currentMouseState.lX, (float)-m_currentMouseState.lY);
}
