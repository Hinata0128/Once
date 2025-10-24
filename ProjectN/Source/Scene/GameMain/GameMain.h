#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

#include "GameObject/StaticMeshObject/Ground/Ground.h"
#include "GameObject/SkinMeshObject/Character/Player/Player.h"

#include "Sprite3D/Sprite3D.h"

class Timer;


/*********************************************
*	�Q�[�����C���摜�N���X.
**/

class GameMain
	: public CSceneBase
{
public:
	GameMain();
	~GameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData();

	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Projection();

private:
	//�Q�[���ň����X�v���C�g�f�[�^(�g���܂킷����).
	std::unique_ptr<Sprite3D> m_pSp3D;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	std::unique_ptr<StaticMeshObject> m_pStcMeshObj;

	//�n�ʃN���X.
	std::unique_ptr<Ground>	m_pGround;

	//�v���C���[�N���X.
	std::unique_ptr<Player> m_pPlayer;

};