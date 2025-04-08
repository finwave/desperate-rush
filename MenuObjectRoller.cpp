#include "MenuObjectRoller.h"

CMenuObjectRoller::CMenuObjectRoller()
{
}

CMenuObjectRoller::~CMenuObjectRoller()
{
}

void CMenuObjectRoller::RotateLeft()
{
	this->SetRotateX(-(D3DX_PI / 4.0f));
	this->SetRotateY(0);
	this->SetRotateZ(0);
}

void CMenuObjectRoller::RotateRight()
{
	this->SetRotateX(-(D3DX_PI / 4.0f));
	this->SetRotateY(0);
	this->SetRotateZ(0);
}

void CMenuObjectRoller::Rotate(float fFrametime)
{
	this->m_fSelfRotation += (fFrametime * this->m_fSpeedCurrent) * 0.025f;

	switch (this->m_eRotation)
	{
	case eROTATION_LEFT:
		this->SetRotateY(this->m_fSelfRotation);
		break;

	case eROTATION_RIGHT:
		this->SetRotateY(-this->m_fSelfRotation);
		break;
	}
}

void CMenuObjectRoller::ResetSelfRotation()
{
	CMenuObject::ResetSelfRotation();

	if (this->m_eShip == eSHIP_MENUS_ROLLER)
	{
		switch (this->m_pTheApp->RandInt(1, 2))
		{
		case 1:
			this->m_eRotation = eROTATION_LEFT;
			break;
		case 2:
			this->m_eRotation = eROTATION_RIGHT;
			break;
		}
	}
}

D3DMATERIAL9* CMenuObjectRoller::InitMaterial(D3DMATERIAL9* material)
{
	// specular lighting

	material->Specular.r = 0.6f;
	material->Specular.g = 0.6f;
	material->Specular.b = 0.6f;
	material->Specular.a = 1.0f;
	material->Power = 3.5f;

	return material;
}