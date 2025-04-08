#pragma once

#include "Weapon.h"

class CWeaponPlayerFront : public CWeapon
{
public:
	CWeaponPlayerFront(void);
	virtual ~CWeaponPlayerFront(void);

	virtual HRESULT Create(	LPDIRECT3DDEVICE9 pDevice,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fWidth,
							float fHeight,
							float fSpeed,
							int iDamage,
							eBULLET_TYPE eType);

	virtual HRESULT Create(	LPDIRECT3DDEVICE9 pDevice,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							float fWidth,
							float fHeight,
							float fSpeed,
							int iDamage,
							eBULLET_TYPE eType);

	virtual void Update(float fFrametime, float playerVelocity);
	virtual void Release();

	virtual void DisableBullet(int iBullet);
	virtual bool BulletActivity(int iBullet);
	virtual bool BulletVisibility(int iBullet);

	virtual void SetMatrix(C3DObject* pShip);
	virtual void InitPosition();
	virtual void SetObjectDepth(float fDepth);

	inline virtual CWeapon* GetBulletLeft() { return this->m_pBulletLeft; }
	inline virtual CWeapon* GetBulletRight() { return this->m_pBulletRight; }

private:
	LPDIRECT3DDEVICE9	m_pDevice;

	CWeapon*			m_pBulletLeft;
	CWeapon*			m_pBulletRight;
};