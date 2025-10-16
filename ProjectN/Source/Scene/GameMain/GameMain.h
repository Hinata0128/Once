#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

#include "GameObject/StaticMeshObject/Ground/Ground.h"
#include "GameObject/StaticMeshObject/Character/Player/Player.h"
#include "DebugText/DebugText.h"
#include "GameObject/StaticMeshObject/Character/Character.h"


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
	Sprite3D*			m_pSp3D;

	Sprite3D*			m_pSpriteGround;
	Sprite3D*			m_pSpriteExplosion;

	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	StaticMesh*		m_pStaticMeshFighter;	//���@.
	StaticMesh*		m_pStaticMeshGround;	//�n��.
	StaticMesh*		m_pStaticMeshEnemyA;	//�GA.
	StaticMesh*		m_pStaticMeshEnemyB;	//�GB.
	StaticMesh*		m_pStaticMeshBullet;	//�e.
	StaticMesh*		m_pStaticMeshBSohere;	//�o�E���f�B���O�X�t�B�A(�����蔻��p).


	StaticMesh*		m_pGameMain;
	Sprite2D*			m_pSpriteTitle;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	StaticMeshObject* m_pStcMeshObj;


	//�L�����N�^�[�N���X
	Character*			m_pPlayer;

	//�n�ʃN���X.
	Ground*			m_pGround;
	DebugText*			m_pDbgText;	//�f�o�b�N�e�L�X�g.

};