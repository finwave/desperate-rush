#include "WeaponPlayerFront.h"

CWeaponPlayerFront::CWeaponPlayerFront(void)
{
	this->m_pBulletLeft = NULL;
	this->m_pBulletRight = NULL;
}

CWeaponPlayerFront::~CWeaponPlayerFront(void)
{
}

HRESULT CWeaponPlayerFront::Create(	LPDIRECT3DDEVICE9 pDevice,
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

	hres = this->m_pBulletLeft->Create(	pDevice,
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

	this->m_pBulletRight = new CWeapon();
	if( !this->m_pBulletRight )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBulletRight->Create(pDevice,
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

	this->AddChild(this->m_pBulletLeft);
	this->AddChild(this->m_pBulletRight);

	return S_OK;
}

HRESULT CWeaponPlayerFront::Create(	LPDIRECT3DDEVICE9 pDevice,
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

	hres = this->m_pBulletLeft->Create(	pDevice,
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

	this->m_pBulletRight = new CWeapon();
	if( !this->m_pBulletRight )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pBulletRight->Create(pDevice,
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

	this->AddChild(this->m_pBulletLeft);
	this->AddChild(this->m_pBulletRight);

	return S_OK;
}

void CWeaponPlayerFront::Release()
{
	CWeapon::Release();
}

void CWeaponPlayerFront::Update(float fFrametime, float playerVelocity)
{
	// hides parent bullet
	this->SetVisible(false);

	float fMove = this->m_fSpeed * fFrametime;
	this->m_fMove += fMove;

	CWeapon::Update(fFrametime, 0.0f);
}

void CWeaponPlayerFront::DisableBullet(int iBullet)
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

bool CWeaponPlayerFront::BulletActivity(int iBullet)
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

bool CWeaponPlayerFront::BulletVisibility(int iBullet)
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

void CWeaponPlayerFront::SetMatrix(C3DObject* pShip)
{
	// rotations

	D3DXMATRIX mRotationX;

	D3DXMatrixRotationX(&mRotationX, D3DX_PI / 2);

	D3DXMatrixMultiply(	&this->m_pBulletLeft->GetLocalMatrix(),
						&mRotationX,
						&this->m_pBulletLeft->GetLocalMatrix());

	D3DXMatrixMultiply(	&this->m_pBulletRight->GetLocalMatrix(),
						&mRotationX,
						&this->m_pBulletRight->GetLocalMatrix());

	// position
	this->SetPosition( pShip->GetPosition() );
}

void CWeaponPlayerFront::InitPosition()
{
	D3DXVECTOR3 pos;

	pos = this->GetPosition();
	pos.y += 3.0f;
	this->SetPosition(pos);

	switch (this->m_eBulletPlace)
	{
	case eBULLET_PLACE_INNER:

		pos = this->m_pBulletLeft->GetPosition();
		pos.x -= 7.5f;
		this->m_pBulletLeft->SetPosition(pos);

		pos = this->m_pBulletRight->GetPosition();
		pos.x += 7.5f;
		this->m_pBulletRight->SetPosition(pos);

		break;
		
	case eBULLET_PLACE_OUTER:

		pos = this->m_pBulletLeft->GetPosition();
		pos.x -= 11.0f;
		this->m_pBulletLeft->SetPosition(pos);

		pos = this->m_pBulletRight->GetPosition();
		pos.x += 11.0f;
		this->m_pBulletRight->SetPosition(pos);

		break;
	}
}

void CWeaponPlayerFront::SetObjectDepth(float fDepth)
{
	this->m_pBulletLeft->SetObjectDepth(fDepth);
	this->m_pBulletRight->SetObjectDepth(fDepth);

	C3DObject::SetObjectDepth(fDepth);
}
