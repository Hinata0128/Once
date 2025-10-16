#pragma once
#include "DirectX\DirectX9.h"
#include "DirectX\DirectX11.h"
#include "Sprite3D\Sprite3D.h"
#include "Sprite2D\Sprite2D.h"
#include "SceneManager/SceneManager.h"

/********************************************************************************
*	ゲームクラス.
**/
class Game
{
public:
	Game( HWND hWnd );
	~Game();

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
	Sprite3D*			m_pSpriteGround;
	Sprite3D*			m_pSpriteExplosion;
private:
	//=delete「削除定義」と呼ばれる機能.
	//指定された場合、その関数は呼び出せなくなる.
	Game() = delete;	//デフォルトコンストラクタ禁止.
	Game(const Game&) = delete;
	Game& operator = (const Game& rhs) = delete;

};