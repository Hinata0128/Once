#include "CSceneBase.h"

CSceneBase::CSceneBase()
	: m_pMesh	(nullptr)
	, m_pDx11	(CDirectX11::GetInstance())
	, m_pDx9	(CDirectX9::GetInstance())
	, m_hWnd	(nullptr)
	, m_Score	(0)
	, m_Count	(0)
{
}
