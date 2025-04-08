#include "PlayerMinigun.h"

CPlayerMinigun::CPlayerMinigun(void)
{
	this->m_pMesh = NULL;

	this->m_eDirection = eDIRECTION_FRONT;

	this->m_bRotateMinigun = false;
	
	this->m_fAngle = 0.0f;
	this->m_fAngleMax = 0.5f;
}

CPlayerMinigun::~CPlayerMinigun(void)
{
}

HRESULT CPlayerMinigun::Create(	LPD3DXMESH mesh,
								std::vector<D3DMATERIAL9*> materials,
								std::vector<LPDIRECT3DTEXTURE9> textures,
								eSIDE eSide)
{
	// get default matrix
	this->m_mDefault = this->GetLocalMatrix();

	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	this->m_eSide = eSide;

	this->m_pMesh = mesh;

	this->InitPosition();

	return S_OK;
}

void CPlayerMinigun::Release(void)
{
	C3DObject::Release();
}

void CPlayerMinigun::InitPosition()
{
	D3DXVECTOR3 pos;

	switch(this->m_eSide)
	{
	// left minigun
	case eSIDE_LEFT:

		// set position
		pos = this->GetPosition();
		pos.x -= 9.382f;
		pos.y -= 7.578f;
		this->SetPosition(pos);

		break;

	// right minigun
	case eSIDE_RIGHT:

		// set position
		pos = this->GetPosition();
		pos.x += 9.382f;
		pos.y -= 7.578f;
		this->SetPosition(pos);

		break;
	}
}

void CPlayerMinigun::Update(float fFrametime)
{
	// rotate minigun
	if(this->m_bRotateMinigun)
	{
		this->RotateMinigun(fFrametime);
		this->InitPosition();
	}

	C3DObject::Update(fFrametime);
}

void CPlayerMinigun::RotateMinigun(float fFrametime)
{
	// rotation speed
	float fRotationSpeed = fFrametime + 0.015f;

	switch(this->m_eDirection)
	{
	// miniguns are pointing in front direction
	case eDIRECTION_FRONT:

		// update rotation angle
		this->m_fAngle += fRotationSpeed;

		if(this->m_fAngle > this->m_fAngleMax)
		{
			this->m_fAngle = this->m_fAngleMax;
		}

		switch(this->m_eSide)
		{
		// left minigun
		case eSIDE_LEFT:

			// rotate minigun
			D3DXMatrixRotationZ(&this->GetLocalMatrix(), this->m_fAngle );

			break;

		// right minigun
		case eSIDE_RIGHT:

			// rotate minigun
			D3DXMatrixRotationZ(&this->GetLocalMatrix(), -this->m_fAngle );
			break;
		}

		// reached max rotation
		if(this->m_fAngle >= this->m_fAngleMax)
		{
			this->m_eDirection = eDIRECTION_DIAGONAL;
			this->m_bRotateMinigun = false;
		}

		break;

	// miniguns are pointing in diagonal direction
	case eDIRECTION_DIAGONAL:

		// update rotation angle
		this->m_fAngle -= fRotationSpeed;

		if(this->m_fAngle < 0.0f)
		{
			this->m_fAngle = 0.0f;
		}

		switch(this->m_eSide)
		{
		// left minigun
		case eSIDE_LEFT:

			// rotate minigun
			D3DXMatrixRotationZ(&this->GetLocalMatrix(), this->m_fAngle );

			break;

		// right minigun
		case eSIDE_RIGHT:

			// rotate minigun
			D3DXMatrixRotationZ(&this->GetLocalMatrix(), -this->m_fAngle );
			break;
		}

		// reached max rotation
		if(this->m_fAngle <= 0.0f)
		{
			this->m_eDirection = eDIRECTION_FRONT;
			this->m_bRotateMinigun = false;
		}

		break;
	}
}