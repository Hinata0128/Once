#include "GameObject.h"

//コンストラクタ.
GameObject::GameObject()
	: m_vPosition	()
	, m_vRotation	()
	, m_vScale		( 1.0f, 1.0f, 1.0f )
{
}

//デストラクタ.
GameObject::~GameObject()
{
}