#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

#include "GameObject/StaticMeshObject/Ground/Ground.h"


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

	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	StaticMesh*		m_pStaticMeshGround;	//�n��.

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	StaticMeshObject* m_pStcMeshObj;

	//�n�ʃN���X.
	Ground*			m_pGround;

};