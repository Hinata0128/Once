#include "Title.h"
#include "Sound/SoundManager.h"

Title::Title()
	: CSceneBase				()
	, m_pTitle					( nullptr )
	, m_pSpriteTitle			( nullptr )
	, m_pTitleObj				( nullptr )
	
	, m_isTransitioning			()
	, m_transitionDelayTimer	()
{
	
}

Title::~Title()
{
}

void Title::Initialize()
{
	//�J�ڊ֘A�̃t���O�ƃ^�C�}�[�����Z�b�g
	m_isTransitioning = false;
	m_transitionDelayTimer = 0;
}

void Title::Create()
{
	m_pSpriteTitle = new Sprite2D();

	//�^�C�g���\����.
	Sprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f};

	//�^�C�g���X�v���C�g�ǂݍ���.
	m_pSpriteTitle->Init(
		_T("Data\\Texture\\Title.png"), SSTitle);

	//UIObj���C���X�^���X����.
	m_pTitleObj = new UIObject();

	m_pTitleObj->AttachSprite(*m_pSpriteTitle);
}

void Title::Update()
{
	if (m_isTransitioning)
	{
		m_transitionDelayTimer--; // �^�C�}�[�����炷
		if (m_transitionDelayTimer <= 0)
		{
			SceneManager::GetInstance()->LoadScene(SceneManager::Main); // GameMain�V�[���֑J��
			m_isTransitioning = false; // �t���O�����Z�b�g
			return; // �V�[���J�ڌ�͂��̃t���[���̎c���Update�����̓X�L�b�v
		}
		// �J�ډ��o�����`��͑�����̂ŁADraw() �� Update() �O�ŌĂ΂��O��
		// �����ő��̓��͂�X�V�������~�������̂� return;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		SoundManager::PlaySE(SoundManager::SE_Enter); // SE���Đ�
		m_isTransitioning = true; // �J�ڃt���O�𗧂Ă�
		m_transitionDelayTimer = TRANSITION_DELAY_FRAMES; // �^�C�}�[���J�n
	}
}

void Title::Draw()
{
	m_pTitleObj->Draw();
}
