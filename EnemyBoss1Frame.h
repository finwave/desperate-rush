#pragma once

#include "EnemyBoss.h"
#include "Controllers/EnemyBossSideLasersController.h"

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

	virtual void UpdateShip(float fFrametime, bool bShootPossible);

	virtual void Render();

	void CreateSideLasersController(CLevel* pLevel,
									CEnemyBoss1Laser* pLaserLeft,
									CEnemyBoss1Laser* pLaserRight);

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

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);
	virtual void Move(float fFrametime, float fPlayerVelocity);

	void BigLaserCharge();
	void BigLaserFire(float fFrametime);
	void SetRandAttack();

	eACTION m_eAction;
	CEnemyBossSideLasersController* m_pEnemyBossSideLasersController;
};