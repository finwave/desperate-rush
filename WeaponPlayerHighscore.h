#pragma once

#include "Weapon.h"

class CWeaponPlayerHighscore : public CWeapon
{
public:
	CWeaponPlayerHighscore(void);
	virtual ~CWeaponPlayerHighscore(void);

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

private:
	LPDIRECT3DDEVICE9	m_pDevice;

	CWeapon*			m_pBulletLeft;
	CWeapon*			m_pBulletRight;
};