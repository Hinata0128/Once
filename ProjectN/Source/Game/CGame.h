#pragma once
#include "DirectX\DirectX9.h"
#include "DirectX\DirectX11.h"
#include "Sprite3D\CSprite3D.h"
#include "Sprite2D\CSprite2D.h"
#include "SceneManager/CSceneManager.h"

/********************************************************************************
*	ゲームクラス.
**/
class CGame
{
public:
	CGame( HWND hWnd );
	~CGame();

	void Create();
	HRESULT LoadData();
	void Release();

	void Update();
	void Draw();

	void Init();

private:
	//ウィンドウハンドル.
	HWND				m_hWnd;

	//ゲームで扱うスプライトデータ(使いまわす資源).
	CSprite3D*			m_pSpriteGround;
	CSprite3D*			m_pSpriteExplosion;
private:
	//=delete「削除定義」と呼ばれる機能.
	//指定された場合、その関数は呼び出せなくなる.
	CGame() = delete;	//デフォルトコンストラクタ禁止.
	CGame(const CGame&) = delete;
	CGame& operator = (const CGame& rhs) = delete;

};