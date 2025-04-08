#include "MenuBoss1Scatter.h"

CMenuBoss1Scatter::CMenuBoss1Scatter()
{
	this->m_fRotationSpeed = 0;
}

CMenuBoss1Scatter::~CMenuBoss1Scatter(void)
{
}

void CMenuBoss1Scatter::Init()
{
	switch (this->m_eShip)
	{
	case eSHIP_MENUS_BOSS_1_SCATTER_LEFT:
		this->m_eRotation = eROTATION_LEFT;
		break;

	case eSHIP_MENUS_BOSS_1_SCATTER_RIGHT:
		this->m_eRotation = eROTATION_RIGHT;
		break;
	}

	this->m_fRotationSpeed = 0.85f;
	this->Scale();
}

void CMenuBoss1Scatter::UpdateShip(CMenuObject* pBossFrame, float fFrametime)
{
	this->RotateShip(pBossFrame, fFrametime);
	// set initial position
	this->InitPosition(pBossFrame);

	// update object
	C3DObject::Update(fFrametime);
}

void CMenuBoss1Scatter::RotateShip(CMenuObject* pBossFrame, float fFrametime)
{
	CMenuObject::eMOVE parentMove = pBossFrame->GetMove();

	float rotationX = pBossFrame->GetAngleX();
	float rotationY = pBossFrame->GetAngleY();
	float rotationZ = 0;

	this->m_fSelfRotation += fFrametime * this->m_fRotationSpeed;

	switch (this->m_eRotation)
	{
	case eROTATION_LEFT:
		rotationZ = -this->m_fSelfRotation;
		break;

	case eROTATION_RIGHT:
		rotationZ = this->m_fSelfRotation;
		break;
	}

	this->SetRotateX(D3DX_PI / 4.5f);
	this->SetRotateY(0);
	this->SetRotateZ(rotationZ);
}

void CMenuBoss1Scatter::InitPosition(CMenuObject* pBossFrame)
{
	CMenuObject::eMOVE parentMove = pBossFrame->GetMove();
	D3DXVECTOR3 pos = pBossFrame->GetPosition();
	pos.z -= 30.0f;

	if (parentMove == CMenuObject::eMOVE::eMOVE_RIGHT)
	{
		switch (this->m_eShip)
		{
		case eSHIP_MENUS_BOSS_1_SCATTER_LEFT:
			pos.x -= 18.0f;
			pos.y += 21.0f;
			break;

		case eSHIP_MENUS_BOSS_1_SCATTER_RIGHT:
			pos.x -= 18.0f;
			pos.y -= 21.0f;
			break;
		}
	}
	else if (parentMove == CMenuObject::eMOVE::eMOVE_LEFT)
	{
		switch (this->m_eShip)
		{
		case eSHIP_MENUS_BOSS_1_SCATTER_LEFT:
			pos.x += 18.0f;
			pos.y -= 21.0f;
			break;

		case eSHIP_MENUS_BOSS_1_SCATTER_RIGHT:
			pos.x += 18.0f;
			pos.y += 21.0f;
			break;
		}
	}

	this->SetPosition(pos);
}

void CMenuBoss1Scatter::Scale()
{
	this->SetScaleX(1.1f);
	this->SetScaleY(1.1f);
	this->SetScaleZ(1.1f);
}

D3DMATERIAL9* CMenuBoss1Scatter::InitMaterial(D3DMATERIAL9* material)
{
	// specular lighting
	material->Specular.r = 0.6f;
	material->Specular.g = 0.6f;
	material->Specular.b = 0.6f;
	material->Specular.a = 1.0f;
	material->Power = 8.0f;

	return material;
}
