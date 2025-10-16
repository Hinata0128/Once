#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

/*********************************************
*	タイトル画像クラス.
**/

class Title
	: public CSceneBase
{
public:
	Title();
	~Title() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

private: 	
	StaticMesh*	m_pTitle;
	Sprite2D*		m_pSpriteTitle;
	UIObject*		m_pTitleObj;

	bool			m_isTransitioning;       // シーン遷移中フラグ
	int				m_transitionDelayTimer;   // 遷移までのカウントダウンタイマー
	const int		TRANSITION_DELAY_FRAMES = 30; // 例: 30フレーム待つ (約0.5秒)
};