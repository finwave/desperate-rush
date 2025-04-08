#include "WeaponPlayerHighscore.h"

CWeaponPlayerHighscore::CWeaponPlayerHighscore(void)
{
	this->m_pBulletLeft = NULL;
	this->m_pBulletRight = NULL;
}

CWeaponPlayerHighscore::~CWeaponPlayerHighscore(void)
{
}

HRESULT CWeaponPlayerHighscore::Create(	LPDIRECT3DDEVICE9 pDevice,
										LPD3DXMESH mesh,
										std::vector<D3DMATERIAL9*> materials,
										std::vector<LPDIRECT3DTEXTURE9> textures,
										float fWidth,
										float fHeight,
										float fSpeed,
										int iDamage,
										eBULLET_TYPE eType)
{
	HRESULT hres;
	this->m_pDevice = pDevice;

	hres = CWeapon::Create(	pDevice,
							mesh,
							materials,
							textures,
							fWidth,
							fHeight,
							fSpeed,
							iDamage,
							eType);
	if( FAILED(hres) )
	{
		return hres;
	}

	this->m_pBulletLeft = new CWeapon();
	if( !this->m_pBulletLeft )
	{
		return E_OUTOFMEMORY;
	}

	this->m_pBulletLeft->Create(pDevice,
								mesh,
								materials,
								textures,
								fWidth,
								fHeight,
								fSpeed,
								iDamage,
								eType);

	this->m_pBulletRight = new CWeapon();
	if( !this->m_pBulletRight )
	{
		return E_OUTOFMEMORY;
	}

	this->m_pBulletRight->Create(	pDevice,
									mesh,
									materials,
									textures,
									fWidth,
									fHeight,
									fSpeed,
									iDamage,
									eType);

	this->AddChild(this->m_pBulletLeft);
	this->AddChild(this->m_pBulletRight);

	return S_OK;
}

HRESULT CWeaponPlayerHighscore::Create(	LPDIRECT3DDEVICE9 pDevice,
										LPD3DXMESH mesh,
										std::vector<MESHDATA>& meshData,
										float fWidth,
										float fHeight,
										float fSpeed,
										int iDamage,
										eBULLET_TYPE eType)
{
	HRESULT hres;
	this->m_pDevice = pDevice;

	hres = CWeapon::Create(	pDevice,
							mesh,
							meshData,
							fWidth,
							fHeight,
							fSpeed,
							iDamage,
							eType);
	if( FAILED(hres) )
	{
		return hres;
	}

	this->m_pBulletLeft = new CWeapon();
	if( !this->m_pBulletLeft )
	{
		return E_OUTOFMEMORY;
	}

	this->m_pBulletLeft->Create(pDevice,
								mesh,
								meshData,
								fWidth,
								fHeight,
								fSpeed,
								iDamage,
								eType);

	this->m_pBulletRight = new CWeapon();
	if( !this->m_pBulletRight )
	{
		return E_OUTOFMEMORY;
	}

	this->m_pBulletRight->Create(	pDevice,
									mesh,
									meshData,
									fWidth,
									fHeight,
									fSpeed,
									iDamage,
									eType);

	this->AddChild(this->m_pBulletLeft);
	this->AddChild(this->m_pBulletRight);

	return S_OK;
}

void CWeaponPlayerHighscore::Release()
{
	CWeapon::Release();

	this->m_pBulletLeft = NULL;
	this->m_pBulletRight = NULL;
}

void CWeaponPlayerHighscore::Update(float fFrametime, float playerVelocity)
{
	D3DXVECTOR3 pos;

	// hides parent bullet
	this->SetVisible(false);
	CWeapon::Update(fFrametime, playerVelocity);
	/*
	float fMove = this->m_fSpeed * fFrametime;
	this->m_fMove += fMove;

	pos = this->m_pBulletLeft->GetPosition();
	pos.x -= fMove;
	this->m_pBulletLeft->SetPosition(pos);

	pos = this->m_pBulletRight->GetPosition();
	pos.x -= fMove;
	this->m_pBulletRight->SetPosition(pos);
	*/
}

void CWeaponPlayerHighscore::DisableBullet(int iBullet)
{
	switch(iBullet)
	{
		case 0:
			if( this->BulletActivity(1) || this->BulletActivity(2) )
			{
				this->SetVisible(FALSE);
			}
			else if( !this->BulletActivity(1) && !this->BulletActivity(2) )
			{
				this->SetActive(FALSE);
				this->SetVisible(FALSE);
			}
			break;
		case 1:

			this->m_pBulletLeft->SetActive(FALSE);
			this->m_pBulletLeft->SetVisible(FALSE);
			break;
		case 2:
			this->m_pBulletRight->SetActive(FALSE);
			this->m_pBulletRight->SetVisible(FALSE);
			break;
	}
}

bool CWeaponPlayerHighscore::BulletActivity(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsActive() == TRUE;
			break;
		case 1:
			return this->m_pBulletLeft->IsActive() == TRUE;
			break;
		case 2:
			return this->m_pBulletRight->IsActive() == TRUE;
			break;
	}
	return FALSE;
}

bool CWeaponPlayerHighscore::BulletVisibility(int iBullet)
{ 
	switch(iBullet)
	{
		case 0:
			return this->IsVisible() == TRUE;
			break;
		case 1:
			return this->m_pBulletLeft->IsVisible() == TRUE;
			break;
		case 2:
			return this->m_pBulletRight->IsVisible() == TRUE;
			break;
	}
	return FALSE;
}

void CWeaponPlayerHighscore::SetMatrix(C3DObject* pShip)
{
	// rotation
	D3DXMatrixRotationYawPitchRoll(	&this->GetLocalMatrix(),
									D3DX_PI / 2,
									0.0f,
									D3DX_PI / 4);
	// position
	this->SetPosition( pShip->GetPosition() );
}

void CWeaponPlayerHighscore::InitPosition()
{
	D3DXVECTOR3 pos;

	pos = this->GetPosition();
	pos.x += 15.0f;
	pos.z -= 20.0f;
	this->SetPosition(pos);

	pos = this->m_pBulletLeft->GetPosition();
	pos.y += 9.0f;
	this->m_pBulletLeft->SetPosition(pos);

	pos = this->m_pBulletRight->GetPosition();
	pos.y -= 9.0f;
	this->m_pBulletRight->SetPosition(pos);
}
