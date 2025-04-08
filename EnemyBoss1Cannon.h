#pragma once

#define ENEMYBOSS1CANNON_CHARGE_MAX	19
#define ENEMYBOSS1CANNON_SHOOT_MAX	2

#include "EnemyBoss.h"
#include "Sprite.h"

class CEnemyBoss1Cannon : public CEnemyBoss
{
public:

	enum eACTION
	{
		eACTION_WAIT,
		eACTION_CHARGE,
		eACTION_BEAM
	};

	CEnemyBoss1Cannon(	eTYPE eType,
						eBEHAVIOUR eBehaviour);

	virtual ~CEnemyBoss1Cannon(void);

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	virtual void UpdateShip(IEnemy* pBossFrame,
							bool bShootPossible,
							float fFrametime);

	void Render(IEnemy* pBossFrame,
				float fFrametime,
				bool bPause);

	void InitWeapons(	CSprite *pSpriteCannonCharge,
						CSprite *pSpriteCannonBeam);

	inline eACTION GetAction() { return this->m_eAction; }
	inline int GetDamage() { return this->m_iCannonDamage; }

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	bool ChargeCannon(	D3DXVECTOR3 posFrame,
						float fFrametime,
						bool bPause);

	bool ShootCannon(	D3DXVECTOR3 posFrame,
						float fFrametime,
						bool bPause);

	void Scale();
	void ResetPosition();

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);

	CSprite*	m_pSpriteCannonCharge;
	CSprite*	m_pSpriteCannonShoot;

	eACTION		m_eAction;
	int			m_iCannonDamage;
};