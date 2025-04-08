#include "MenuObject.h"

CMenuObject::CMenuObject(void)
{
	this->m_eType = eTYPE_OTHER;
	this->m_eShip = eSHIP_NONE;

	this->m_pTheApp = NULL;
	this->m_pMesh = NULL;

	this->m_eMove = eMOVE_STAY;
	this->m_eRotation = eROTATION_NONE;

	this->m_fSpeedCurrent = 0.0f;
	this->m_fMovementPauseTimer = 0.0f;
	this->m_fSelfRotation = 0.0f;

	this->m_fScreenWidth = 0.0f;
	this->m_fScreenHeight = 0.0f;
}

CMenuObject::~CMenuObject(void)
{
}

void CMenuObject::Create(	CTheApp *pTheApp,
							LPD3DXMESH mesh,
							CXFileContainer xFile,
							float fScreenWidth,
							float fScreenHeight,
							eTYPE eType,
							eSHIP eShip)
{
	this->m_pTheApp = pTheApp;

	this->m_eType = eType;
	this->m_eShip = eShip;

	this->m_fScreenWidth = fScreenWidth;
	this->m_fScreenHeight = fScreenHeight;

	SetMoveBorder();
	SetSpeedLimit();

	C3DObject::Create(mesh);

	this->InitTexture(xFile);
}

void CMenuObject::Create(	CTheApp* pTheApp,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fScreenWidth,
							float fScreenHeight,
							eTYPE eType,
							eSHIP eShip)
{
	this->m_pTheApp = pTheApp;

	this->m_eType = eType;
	this->m_eShip = eShip;

	this->m_fScreenWidth = fScreenWidth;
	this->m_fScreenHeight = fScreenHeight;

	SetMoveBorder();
	SetSpeedLimit();

	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}
}

void CMenuObject::Init()
{
	this->Scale();

	switch( this->m_eType )
	{
	// planet
	case eTYPE_PLANET:

		this->m_fSpeedCurrent = 0.04f;
		break;

	// ships
	case eTYPE_SHIP:

		this->ChangeDirection();
		this->ChangeSpeed();
		this->RandomMoveTime();

		break;
	}
}

void CMenuObject::Release(void)
{
	this->m_pTheApp = NULL;
	C3DObject::Release();
}

void CMenuObject::Update(float fFrametime)
{
	static float fSpeedReductionCurrent = 0.0f;
	static float fSpeedIncreaseCurrent = 0.0f;

	this->Rotate(fFrametime);

	if (this->m_eType == eTYPE_SHIP)
	{
		if (this->m_fMovementPauseTimer <= 0.0f)
		{
			// move ship
			this->Move(fFrametime);
		}
		else
		{
			// update move timer
			this->m_fMovementPauseTimer -= fFrametime;
		}
	}

	// update object
	C3DObject::Update(fFrametime);
}

void CMenuObject::Scale()
{
	switch( this->m_eType )
	{
	case eTYPE_PLANET:
		this->SetScaleX(1.9f);
		this->SetScaleY(1.9f);
		this->SetScaleZ(1.9f);
		break;

	case eTYPE_SHIP:
		this->SetScaleX(1.1f);
		this->SetScaleY(1.1f);
		this->SetScaleZ(1.1f);
		break;
	}
}

float CMenuObject::GetDepth()
{
	D3DXVECTOR3 pos = this->GetPosition();
	return pos.z;
}

void CMenuObject::SetDepth(float fDepth)
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.z = fDepth;
	this->SetPosition(pos);
}

void CMenuObject::RotateLeft()
{
	this->SetRotateX(0);
	this->SetRotateY(D3DX_PI / 4.5f);
	this->SetRotateZ(-(D3DX_PI / 2.0f));
}

void CMenuObject::RotateRight()
{
	this->SetRotateX(0);
	this->SetRotateY(-(D3DX_PI / 4.5f));
	this->SetRotateZ(D3DX_PI / 2.0f);
}

void CMenuObject::Rotate(float fFrametime)
{
	switch(this->m_eType)
	{
	case eTYPE_PLANET:

		this->m_fSelfRotation += fFrametime * this->m_fSpeedCurrent;
		this->SetRotateY(this->m_fSelfRotation);

		break;
	}
}

void CMenuObject::ResetSelfRotation()
{
	this->m_fSelfRotation = 0;
}

void CMenuObject::Move(float fFrametime)
{
	float fFrameSpeed = fFrametime * this->m_fSpeedCurrent;
	float fMovementBorder = 0.0f;

	D3DXVECTOR3 pos = this->GetPosition();
	bool bResetMovement = false;

	switch( this->m_eMove )
	{
	case eMOVE_RIGHT:

		fMovementBorder = this->m_fScreenWidth + this->m_fMoveBorderX;

		if( (pos.x + fFrameSpeed) < fMovementBorder )
		{
			pos.x += fFrameSpeed;
			this->SetPosition(pos);
		}
		else
		{
			bResetMovement = true;
		}
		break;

	case eMOVE_LEFT:

		fMovementBorder = -this->m_fScreenWidth - this->m_fMoveBorderX;

		if( (pos.x - fFrameSpeed) > fMovementBorder )
		{
			pos.x -= fFrameSpeed;
			this->SetPosition(pos);
		}
		else
		{
			bResetMovement = true;
		}
		break;
	}

	if (bResetMovement)
	{
		this->ChangeDirection();
		this->ChangeVertical();
		this->ChangeSpeed();
		this->RandomMoveTime();
	}
}

void CMenuObject::ChangeDirection()
{
	int iRand;
	D3DXVECTOR3 pos;

	switch( this->m_eMove )
	{
	case eMOVE_STAY:
		this->InitPosition();
		this->ChangeVertical();
		break;

	case eMOVE_RIGHT:

		iRand = this->m_pTheApp->RandInt(1,2);

		switch(iRand)
		{
		case 1:

			this->RotateLeft();
			this->m_eMove = eMOVE_LEFT;

			break;

		case 2:

			pos = this->GetPosition();
			pos.x = -this->m_fScreenWidth - this->m_fMoveBorderX;
			this->SetPosition(pos);

			break;
		}

		break;

	case eMOVE_LEFT:

		iRand = this->m_pTheApp->RandInt(1,2);

		switch(iRand)
		{
		case 1:

			this->RotateRight();
			this->m_eMove = eMOVE_RIGHT;

			break;

		case 2:

			pos = this->GetPosition();
			pos.x = this->m_fScreenWidth + this->m_fMoveBorderX;
			this->SetPosition(pos);

			break;
		}

		break;
	}

	ResetSelfRotation();
}

void CMenuObject::ChangeVertical()
{
	D3DXVECTOR3 pos = this->GetPosition();

	int iUpDown = 0;
	float fRandMove = 0.0f;

	float fBorderUp = this->m_fScreenHeight - 10.0f;
	float fBorderDown = -this->m_fScreenHeight + 10.0f;

	bool bLoop = true;

	while(bLoop)
	{
		iUpDown = this->m_pTheApp->RandInt(1,2);
		fRandMove = this->m_pTheApp->RandFloat(20.0f, 100.0f);

		switch(iUpDown)
		{
		case 1:
			// try to move up first
			if( (pos.y + fRandMove) < fBorderUp )
			{
				bLoop = false;
				pos.y += fRandMove;
			}
			// can't move up, try to move down (should be possible)
			else if( (pos.y - fRandMove) > fBorderDown )
			{
				bLoop = false;
				pos.y -= fRandMove;
			}
			break;
		case 2:
			// try to move down first
			if( (pos.y - fRandMove) > fBorderDown )
			{
				bLoop = false;
				pos.y -= fRandMove;
			}
			// can't move down, try to move up (should be possible)
			else if( (pos.y + fRandMove) < fBorderUp )
			{
				bLoop = false;
				pos.y += fRandMove;
			}
			break;
		}
	}

	this->SetPosition(pos);
}

void CMenuObject::SetMoveBorder()
{
	this->m_fMoveBorderX = 30.0f;

	if (this->m_eShip == eSHIP_MENUS_ROLLER)
	{
		this->m_fMoveBorderX = 40.0f;
	}
	else if (this->m_eShip == eSHIP_MENUS_BOSS_1)
	{
		this->m_fMoveBorderX = 86.0f;
	}
}

void CMenuObject::SetSpeedLimit()
{
	switch (this->m_eShip)
	{
	case eSHIP_MENUS_PLAYER:
		this->m_fSpeedMin = 50.0f;
		this->m_fSpeedMax = 100.0f;
		break;
	case eSHIP_MENUS_DRONE:
		this->m_fSpeedMin = 55.0f;
		this->m_fSpeedMax = 105.0f;
		break;
	case eSHIP_MENUS_SNIPER:
		this->m_fSpeedMin = 35.0f;
		this->m_fSpeedMax = 85.0f;
		break;
	case eSHIP_MENUS_ROLLER:
		this->m_fSpeedMin = 30.0f;
		this->m_fSpeedMax = 70.0f;
		break;
	case eSHIP_MENUS_GUARD:
		this->m_fSpeedMin = 27.0f;
		this->m_fSpeedMax = 50.0f;
		break;
	case eSHIP_MENUS_BOSS_1:
		this->m_fSpeedMin = 25.0f;
		this->m_fSpeedMax = 35.0f;
		break;
	}
}

void CMenuObject::ChangeSpeed()
{
	this->m_fSpeedCurrent = this->m_pTheApp->RandFloat(this->m_fSpeedMin, this->m_fSpeedMax);
}

void CMenuObject::RandomMoveTime()
{
	this->m_fMovementPauseTimer = this->m_pTheApp->RandFloat(2.0f, 8.0f);
}

void CMenuObject::InitPosition()
{
	int iRandLeftRight = 0;
	D3DXVECTOR3 pos = this->GetPosition();

	switch( this->m_eType )
	{
	// ships
	case eTYPE_SHIP:

		iRandLeftRight = this->m_pTheApp->RandInt(1,2);

		switch(iRandLeftRight)
		{
		// start from left
		case 1:

			pos.x = -this->m_fScreenWidth - this->m_fMoveBorderX;

			this->RotateRight();
			this->m_eMove = eMOVE_RIGHT;

			break;

		// start from right
		case 2:

			pos.x = this->m_fScreenWidth + this->m_fMoveBorderX;

			this->RotateLeft();
			this->m_eMove = eMOVE_LEFT;
			break;
		}

		break;
	}

	this->SetPosition(pos);
}

void CMenuObject::InitTexture(CXFileContainer xFile)
{
	MESHDATA data;
	D3DMATERIAL9* pMaterial;

	for (DWORD i = 0; i < xFile.GetMaterialCount(); i++)
	{
		
		pMaterial = &xFile.GetMaterials()[i];
		pMaterial = InitMaterial(pMaterial);

		data.pMaterial = pMaterial;

		data.pTexture = xFile.GetTextures()[i];
		this->AddMeshData(data);
	}
}

D3DMATERIAL9* CMenuObject::InitMaterial(D3DMATERIAL9* material)
{
	// specular lighting

	if(this->m_eType == eTYPE_SHIP)
	{
		switch(this->m_eShip)
		{
		case eSHIP_MENUS_PLAYER:

			material->Specular.r = 0.6f;
			material->Specular.g = 0.6f;
			material->Specular.b = 0.6f;
			material->Specular.a = 1.0f;
			material->Power = 4.0f;

			break;

		case eSHIP_MENUS_DRONE:

			material->Specular.r = 0.7f;
			material->Specular.g = 0.7f;
			material->Specular.b = 0.7f;
			material->Specular.a = 1.0f;
			material->Power = 3.5f;

			break;

		case eSHIP_MENUS_SNIPER:

			material->Specular.r = 0.6f;
			material->Specular.g = 0.6f;
			material->Specular.b = 0.6f;
			material->Specular.a = 1.0f;
			material->Power = 4.0f;

			break;

		case eSHIP_MENUS_GUARD:

			material->Specular.r = 0.6f;
			material->Specular.g = 0.6f;
			material->Specular.b = 0.6f;
			material->Specular.a = 1.0f;
			material->Power = 4.0f;

			break;

		case eSHIP_MENUS_BOSS_1:

			material->Specular.r = 0.6f;
			material->Specular.g = 0.6f;
			material->Specular.b = 0.6f;
			material->Specular.a = 1.0f;
			material->Power = 8.0f;

			break;
		}
	}

	return material;
}
