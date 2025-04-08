#include "WeaponPlayerDiagonal.h"

CWeaponPlayerDiagonal::CWeaponPlayerDiagonal(void)
{
	this->m_pBulletLeft = NULL;
	this->m_pBulletRight = NULL;
}

CWeaponPlayerDiagonal::~CWeaponPlayerDiagonal(void)
{
}

HRESULT CWeaponPlayerDiagonal::Create(	LPDIRECT3DDEVICE9 pDevice,
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

HRESULT CWeaponPlayerDiagonal::Create(	LPDIRECT3DDEVICE9 pDevice,
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

void CWeaponPlayerDiagonal::Release()
{
	CWeapon::Release();
}

void CWeaponPlayerDiagonal::Update(float fFrametime, float playerVelocity)
{
	D3DXVECTOR3 pos;

	// hide parent bullet
	this->SetVisible(false);

	float fMoveSide = (this->m_fSpeed * fFrametime) - 1.0f;
	this->m_fMove += fMoveSide;

	pos = this->m_pBulletLeft->GetPosition();
	pos.x -= fMoveSide;
	this->m_pBulletLeft->SetPosition(pos);

	pos = this->m_pBulletRight->GetPosition();
	pos.x += fMoveSide;
	this->m_pBulletRight->SetPosition(pos);

	CWeapon::Update(fFrametime, 0.0f);
}

void CWeaponPlayerDiagonal::DisableBullet(int iBullet)
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

bool CWeaponPlayerDiagonal::BulletActivity(int iBullet)
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

bool CWeaponPlayerDiagonal::BulletVisibility(int iBullet)
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

void CWeaponPlayerDiagonal::SetMatrix(C3DObject* pShip)
{
	// rotations

	D3DXMATRIX mRotationX;

	D3DXMATRIX mRotationZLeft;
	D3DXMATRIX mRotationZRight;

	D3DXMATRIX mRotationXZLeft;
	D3DXMATRIX mRotationXZRight;

	D3DXMatrixRotationX(&mRotationX, -D3DX_PI / 2);

	D3DXMatrixRotationZ(&mRotationZLeft, D3DX_PI / 4);
	D3DXMatrixRotationZ(&mRotationZRight, -(D3DX_PI / 4));

	D3DXMatrixMultiply(	&mRotationXZLeft,
						&mRotationX,
						&mRotationZLeft);

	D3DXMatrixMultiply(	&mRotationXZRight,
						&mRotationX,
						&mRotationZRight);

	D3DXMatrixMultiply(	&this->m_pBulletLeft->GetLocalMatrix(),
						&mRotationXZLeft,
						&this->m_pBulletLeft->GetLocalMatrix());

	D3DXMatrixMultiply(	&this->m_pBulletRight->GetLocalMatrix(),
						&mRotationXZRight,
						&this->m_pBulletRight->GetLocalMatrix());

	// position
	this->SetPosition( pShip->GetPosition() );
}

void CWeaponPlayerDiagonal::InitPosition()
{
	D3DXVECTOR3 pos;

	switch (this->m_eBulletPlace)
	{
	case eBULLET_PLACE_INNER:

		pos = this->m_pBulletLeft->GetPosition();
		pos.x -= 13.2f;
		pos.y += 2.0f;
		this->m_pBulletLeft->SetPosition(pos);

		pos = this->m_pBulletRight->GetPosition();
		pos.x += 13.2f;
		pos.y += 2.0f;
		this->m_pBulletRight->SetPosition(pos);

		break;
		
	case eBULLET_PLACE_OUTER:

		pos = this->m_pBulletLeft->GetPosition();
		pos.x -= 18.2f;
		pos.y += 1.0f;
		this->m_pBulletLeft->SetPosition(pos);

		pos = this->m_pBulletRight->GetPosition();
		pos.x += 18.2f;
		pos.y += 1.0f;
		this->m_pBulletRight->SetPosition(pos);

		break;
	}
}

void CWeaponPlayerDiagonal::SetObjectDepth(float fDepth)
{
	this->m_pBulletLeft->SetObjectDepth(fDepth);
	this->m_pBulletRight->SetObjectDepth(fDepth);

	C3DObject::SetObjectDepth(fDepth);
}
