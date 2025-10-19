#include "Main.h"
#include "DirectX\\DirectX9.h"
#include "DirectX\\DirectX11.h"
#include "SceneManager/SceneManager.h"
#include "System/Manager/StaticMeshManager/StaticMeshManager.h"
#include "System/Manager/SkinMeshManager/SkinMeshManager.h"
#include "Effect/Effect.h"
#include "Sound/SoundManager.h"


//�E�B���h�E����ʒ����ŋN����L���ɂ���.
//#define ENABLE_WINDOWS_CENTERING

//=================================================
//	�萔.
//=================================================
const TCHAR WND_TITLE[] = _T( "Ones" );
const TCHAR APP_NAME[]	= _T( "Ones" );


/********************************************************************************
*	���C���N���X.
**/
//=================================================
//	�R���X�g���N�^.
//=================================================
Main::Main()
	//���������X�g.
	: m_hWnd	( nullptr )
{
	//�R�}���h�v�����v�g�\��.
	//AllocConsole();
}


//=================================================
//	�f�X�g���N�^.
//=================================================
Main::~Main()
{
	DeleteObject( m_hWnd );
}


//�\�z����.
HRESULT Main::Create()
{
	// DirectX �V���O���g���擾
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();

	//DirectX9�\�z.
	if (FAILED(pDx9->Create(m_hWnd)))
	{
		return E_FAIL;
	}

	//DirectX11�\�z.
	if( FAILED( pDx11->Create( m_hWnd ) ) )
	{
		return E_FAIL;
	}

	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	StaticMeshManager::GetInstance()->Create();
	SkinMeshManager::GetInstance()->Create();

	SceneManager::GetInstance()->SetDx9(pDx9);
	SceneManager::GetInstance()->SetDx11(pDx11);


	//Effect�N���X
	//�����ɏ����Ă����Ȃ��Ƃ����Ȃ�
	//GameMain�ɏ����Ă��������ǐ��LoadDate���ǂݍ��܂���܂�.
	Effect::GetInstance()->Create(
		pDx11->GetDevice(),
		pDx11->GetContext());

	return S_OK;
}

//�X�V����.
void Main::Update()
{
	auto pDx11 = DirectX11::GetInstance();

	SceneManager::GetInstance()->Update();

	//�o�b�N�o�b�t�@���N���A�ɂ���.
	pDx11->ClearBackBuffer();

	//�`�揈��.
	SceneManager::GetInstance()->Draw();

	//��ʂɕ\��.
	pDx11->Present();
}



//�f�[�^���[�h����.
HRESULT Main::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (SoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//Effect�N���X
	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	SceneManager::GetInstance()->Create(m_hWnd);

	return S_OK;
}


//�������.
void Main::Release()
{
	DirectX11::GetInstance()->Release();
	DirectX9::GetInstance()->Release();
}


//���b�Z�[�W���[�v.
void Main::Loop()
{
	//�f�[�^���[�h.
	if( FAILED( LoadData() )){
		return;
	}

	//------------------------------------------------
	//	�t���[�����[�g��������.
	//------------------------------------------------
	float Rate = 0.0f;	//���[�g.
	DWORD sync_old = timeGetTime();			//�ߋ�����.
	DWORD sync_now;							//���ݎ���.

	//���ԏ����̂��߁A�ŏ��P�ʂ�1�~���b�ɕύX.
	timeBeginPeriod( 1 );
	Rate = 1000.0f / static_cast<float>(FPS); //���z���Ԃ��Z�o.

	//���b�Z�[�W���[�v.
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		sync_now = timeGetTime();	//���݂̎��Ԃ��擾.

		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else if( sync_now - sync_old >= Rate )
		{
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			//�X�V����.
			Update();
		}
	}
	//�A�v���P�[�V�����̏I��.
	Release();
}

//�E�B���h�E�������֐�.
HRESULT Main::InitWindow(
	HINSTANCE hInstance,	//�C���X�^���X.
	INT x, INT y,			//�E�B���h�Ex,y���W.
	INT width, INT height)	//�E�B���h�E��,����.
{
	//�E�B���h�E�̒�`.
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );//������(0��ݒ�).

	wc.cbSize			= sizeof( wc );
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= MsgProc;//WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( nullptr, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( nullptr, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( LTGRAY_BRUSH );
	wc.lpszClassName	= APP_NAME;
	wc.hIconSm			= LoadIcon( nullptr, IDI_APPLICATION );

	//�E�B���h�E�N���X��Windows�ɓo�^.
	if( !RegisterClassEx( &wc ) ) {
		_ASSERT_EXPR( false, _T( "�E�B���h�E�N���X�̓o�^�Ɏ��s" ) );
		return E_FAIL;
	}

	//--------------------------------------.
	//	�E�B���h�E�\���ʒu�̒���.
	//--------------------------------------.
	//���̊֐����ł̂ݎg�p����\���̂������Œ�`.
	struct RECT_WND
	{
		INT x, y, w, h;
		RECT_WND() : x(), y(), w(), h() {}
	} rectWindow;//�����ɕϐ��錾������.

#ifdef ENABLE_WINDOWS_CENTERING
	//�f�B�X�v���C�̕��A�������擾.
	HWND hDeskWnd = nullptr;
	RECT recDisplay;
	hDeskWnd = GetDesktopWindow();
	GetWindowRect( hDeskWnd, &recDisplay );

	//�Z���^�����O.
	rectWindow.x = ( recDisplay.right - width ) / 2;	//�\���ʒux���W.
	rectWindow.y = ( recDisplay.bottom - height ) / 2;	//�\���ʒuy���W.
#endif//ENABLE_WINDOWS_CENTERING

	//--------------------------------------.
	//	�E�B���h�E�̈�̒���.
	//--------------------------------------.
	RECT	rect;		//��`�\����.
	DWORD	dwStyle;	//�E�B���h�E�X�^�C��.
	rect.top = 0;			//��.
	rect.left = 0;			//��.
	rect.right = width;		//�E.
	rect.bottom = height;	//��.
	dwStyle = WS_OVERLAPPEDWINDOW;	//�E�B���h�E���.

	if( AdjustWindowRect(
		&rect,			//(in)��ʃT�C�Y����������`�\����.(out)�v�Z����.
		dwStyle,		//�E�B���h�E�X�^�C��.
		FALSE ) == 0 )	//���j���[�������ǂ����̎w��.
	{
		MessageBox(
			nullptr,
			_T( "�E�B���h�E�̈�̒����Ɏ��s" ),
			_T( "�G���[���b�Z�[�W" ),
			MB_OK );
		return 0;
	}

	//�E�B���h�E�̕���������.
	rectWindow.w = rect.right - rect.left;
	rectWindow.h = rect.bottom - rect.top;

	//�E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APP_NAME,					//�A�v����.
		WND_TITLE,					//�E�B���h�E�^�C�g��.
		dwStyle,					//�E�B���h�E���(����).
		rectWindow.x, rectWindow.y,	//�\���ʒux,y���W.
		rectWindow.w, rectWindow.h,	//�E�B���h�E��,����.
		nullptr,					//�e�E�B���h�E�n���h��.
		nullptr,					//���j���[�ݒ�.
		hInstance,					//�C���X�^���X�ԍ�.
		nullptr );					//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.
	if( !m_hWnd ) {
		_ASSERT_EXPR( false, _T( "�E�B���h�E�쐬���s" ) );
		return E_FAIL;
	}

	//�E�B���h�E�̕\��.
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	return S_OK;
}


//�E�B���h�E�֐��i���b�Z�[�W���̏����j.
LRESULT CALLBACK Main::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{
	switch( uMsg ) {
	case WM_DESTROY://�E�B���h�E���j�����ꂽ�Ƃ�.
		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage( 0 );
		break;

	case WM_KEYDOWN://�L�[�{�[�h�������ꂽ�Ƃ�.
		//�L�[�ʂ̏���.
		switch( static_cast<char>( wParam ) ) {
		case VK_ESCAPE:	//ESC��.
			{
				//�E�B���h�E��j������.
				DestroyWindow( hWnd );
			}
			break;
		}
		break;
	}

	//���C���ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}