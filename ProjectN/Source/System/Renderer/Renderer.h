#pragma once

#include <iostream>
#include <D3DX9.h>
// D3DXMATRIX, D3DXVECTOR3 の定義を含む

// LIGHT, CAMERA 構造体の定義は外部ファイル（例：ゲーム共通ヘッダー）にあると仮定します。
// 例:
// struct LIGHT { ... };
// struct CAMERA { ... };


/************************************************************************************
*	レンダラークラス.
**/
class Renderer
{
public:
	// デストラクタの実装は .cpp ファイルで行うべきですが、ここでは宣言のみに留めます。
	// シングルトンのため、仮想デストラクタにするとより安全です。
	virtual ~Renderer() = default;

	// シングルトンインスタンスを取得する静的メソッド (C++11以降の推奨パターン)
	static Renderer& GetInstance()
	{
		static Renderer s_instance;
		return s_instance;
	}

	// --- 外部から描画パラメータを設定するメソッド (毎フレーム呼び出す) ---
	void SetDrawParameters(const D3DXMATRIX& view, const D3DXMATRIX& proj, const LIGHT& light, const CAMERA& camera) {
		// ここで型が一致するため、エラーが解消されます。
		m_View = view;
		m_Proj = proj;
		m_Light = light;
		m_Camera = camera;
	}

	// --- 各パラメータを取得するためのゲッター ---
	const D3DXMATRIX& GetView() const { return m_View; }
	const D3DXMATRIX& GetProj() const { return m_Proj; }
	const LIGHT& GetLight() const { return m_Light; }
	const CAMERA& GetCamera() const { return m_Camera; }

private:
	// コンストラクタを private にして外部からの直接生成を禁止
	Renderer() = default;

	// コピー、ムーブを禁止
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:
	// ビュー行列と射影行列の型を D3DXMATRIX に修正
	D3DXMATRIX	m_View;
	D3DXMATRIX	m_Proj;

	CAMERA		m_Camera;
	LIGHT		m_Light;
};