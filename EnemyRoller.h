#pragma once

#include "IEnemy.h"
#include "WeaponEnemyRoller.h"

class CEnemyRoller : public IEnemy
{
public:

	CEnemyRoller(eTYPE eType, eBEHAVIOUR eBehaviour);

	virtual ~CEnemyRoller(void);

	virtual void Update(float fFrametime, float fPlayerVelocity);

	HRESULT InitWeapons(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						float fBulletWidth,
						float fBulletHeight,
						float fBulletSpeed,
						int iBulletDamage);

	HRESULT InitWeapons(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<MESHDATA>& meshData,
						float fBulletWidth,
						float fBulletHeight,
						float fBulletSpeed,
						int iBulletDamage);

	virtual bool Shoot();

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

	virtual void ChangeRotationZ();

private:

	void ShootWeapons();

	virtual void Move(float fFrametime, float fPlayerVelocity);
	virtual void SetMoveState(void);

	CWeapon* m_pBullet;

	int m_iVolumeShootRoller;

	/** TIMERS **/

	// fixed time between single multi-shots
	float m_fShootMultiTime;

	// timers to calculate next single multi-shot
	float m_fShootMultiTimer;

	// value to indicate max number of bullets
	// to be shot in one multi-shot session
	int m_iShootMultiMax;
	int m_iShootMulti;

	// value to indicate the number of shots 
	// being shot in the current multi-shot session
	int m_iShootMultiCount;
};