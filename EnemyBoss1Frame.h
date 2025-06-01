#pragma once

#include "EnemyBoss.h"
#include "EnemyBoss1Laser.h"

class CEnemyBoss1Frame : public CEnemyBoss
{
public:

	CEnemyBoss1Frame(eTYPE eType,
					eBEHAVIOUR eBehaviour);

	virtual ~CEnemyBoss1Frame(void);

	virtual HRESULT Create(	CTheApp* pTheApp,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	virtual void UpdateShip(bool bShootPossible, float fFrametime);

	virtual void Render();

	void SetLaserObjects(CEnemyBoss1Laser* pLaserLeft, CEnemyBoss1Laser* pLaserRight);

protected:

	virtual void Init(	CTheApp* pTheApp,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	enum eACTION
	{
		eACTION_WAIT,
		eACTION_SMALL_LASER,
		eACTION_BIG_LASER_CHARGE,
		eACTION_BIG_LASER_FIRE
	};

	void BigLaserCharge();
	void BigLaserFire(float fFrametime);
	void SetRandAttack();

	bool IsSmallLaserReady();

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);
	virtual void Move(float fFrametime, float fPlayerVelocity);

	eACTION			m_eAction;

	CEnemyBoss1Laser* m_pLaserLeft;
	CEnemyBoss1Laser* m_pLaserRight;
};