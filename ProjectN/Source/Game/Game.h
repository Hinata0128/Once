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
};