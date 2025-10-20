#pragma once

#include <iostream>
#include <D3DX9.h>
// D3DXMATRIX, D3DXVECTOR3 �̒�`���܂�

// LIGHT, CAMERA �\���̂̒�`�͊O���t�@�C���i��F�Q�[�����ʃw�b�_�[�j�ɂ���Ɖ��肵�܂��B
// ��:
// struct LIGHT { ... };
// struct CAMERA { ... };


/************************************************************************************
*	�����_���[�N���X.
**/
class Renderer
{
public:
	// �f�X�g���N�^�̎����� .cpp �t�@�C���ōs���ׂ��ł����A�����ł͐錾�݂̂ɗ��߂܂��B
	// �V���O���g���̂��߁A���z�f�X�g���N�^�ɂ���Ƃ����S�ł��B
	virtual ~Renderer() = default;

	// �V���O���g���C���X�^���X���擾����ÓI���\�b�h (C++11�ȍ~�̐����p�^�[��)
	static Renderer& GetInstance()
	{
		static Renderer s_instance;
		return s_instance;
	}

	// --- �O������`��p�����[�^��ݒ肷�郁�\�b�h (���t���[���Ăяo��) ---
	void SetDrawParameters(const D3DXMATRIX& view, const D3DXMATRIX& proj, const LIGHT& light, const CAMERA& camera) {
		// �����Ō^����v���邽�߁A�G���[����������܂��B
		m_View = view;
		m_Proj = proj;
		m_Light = light;
		m_Camera = camera;
	}

	// --- �e�p�����[�^���擾���邽�߂̃Q�b�^�[ ---
	const D3DXMATRIX& GetView() const { return m_View; }
	const D3DXMATRIX& GetProj() const { return m_Proj; }
	const LIGHT& GetLight() const { return m_Light; }
	const CAMERA& GetCamera() const { return m_Camera; }

private:
	// �R���X�g���N�^�� private �ɂ��ĊO������̒��ڐ������֎~
	Renderer() = default;

	// �R�s�[�A���[�u���֎~
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:
	// �r���[�s��Ǝˉe�s��̌^�� D3DXMATRIX �ɏC��
	D3DXMATRIX	m_View;
	D3DXMATRIX	m_Proj;

	CAMERA		m_Camera;
	LIGHT		m_Light;
};