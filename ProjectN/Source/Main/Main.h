#pragma once
#include <Windows.h>

//�N���X�̑O���錾.
class DirectX9;
class DirectX11;
class Game;

/**************************************************
*	���C���N���X.
**/
class Main
{
public:
	Main();	//�R���X�g���N�^.
	~Main();	//�f�X�g���N�^.

	void Update();		//�X�V����.
	HRESULT Create();	//�\�z����.
	HRESULT LoadData();	//�f�[�^���[�h����.
	void Release();		//�������.
	void Loop();		//���C�����[�v.

	//�E�B���h�E�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y,
		INT width, INT height );

private:
	//�E�B���h�E�֐��i���b�Z�[�W���̏����j.
	static LRESULT CALLBACK MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam );

private:
	HWND			m_hWnd;	//�E�B���h�E�n���h��.
	Game*			m_pGame;
};