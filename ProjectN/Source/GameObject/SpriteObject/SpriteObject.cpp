//#include "SpriteObject.h"
//
//SpriteObject::SpriteObject()
//	: m_pSprite		( nullptr )
//{
//}
//
//SpriteObject::~SpriteObject()
//{
//	DetachSprite();
//}
//
//void SpriteObject::Update()
//{
//	if( m_pSprite == nullptr ){
//		return;
//	}
//}
//
//void SpriteObject::Draw( D3DXMATRIX& View, D3DXMATRIX& Proj )
//{
//	if( m_pSprite == nullptr ){
//		return;
//	}
//
//	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
//	m_pSprite->SetPosition( m_vPosition );
//	m_pSprite->SetRotation( m_vRotation );
//	m_pSprite->SetScale( m_vScale );
//
//	//�����_�����O.
//	m_pSprite->Render( View, Proj );
//}
//
//void SpriteObject::Draw(
//	D3DXMATRIX& View, D3DXMATRIX& Proj)
//{
//	Draw( View, Proj );
//}
