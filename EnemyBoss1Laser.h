#pragma once

#include "EnemyBoss.h"

// Forward declaration
class CLevel;

class CEnemyBoss1Laser : public CEnemyBoss
{
public:

	enum eSIDE
	{
		eSIDE_LEFT,
		eSIDE_RIGHT
	};

	enum eACTION
	{
		eACTION_READY,
		eACTION_SHOOT_WEAPON
	};

	enum eDIRECTION
	{
		eDIRECTION_FRONT,
		eDIRECTION_DIAGONAL
	};

	CEnemyBoss1Laser(	eTYPE eType,
						eBEHAVIOUR eBehaviour,
						eSIDE eSide);

	virtual ~CEnemyBoss1Laser(void);

	virtual HRESULT Create(	CLevel* pLevel,
							CTheApp* pTheApp,
							IEnemy* pBossFrame,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	void UpdateShip(float fFrametime, bool bShootPossible);
	void UpdatePosition();

	virtual void Render();

	HRESULT InitWeapons(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						float fLaserWidth,
						float fLaserHeight,
						float fLaserSpeed,
						int iLaserDamage);

	HRESULT InitWeapons(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<MESHDATA>& meshData,
						float fLaserWidth,
						float fLaserHeight,
						float fLaserSpeed,
						int iLaserDamage);

	void SetAction(eACTION eAction);

	inline bool IsReady() { return this->IsActive() && (this->m_eAction == eACTION::eACTION_READY); }
	inline bool IsShooting() { return this->IsActive() && (this->m_eAction == eACTION::eACTION_SHOOT_WEAPON); }

	inline void SetDirection(eDIRECTION value) { this->m_eDirection = value; }
	inline void SetShootAmountMax(int value) { this->m_iShootAmountMax = value; }

protected:

	virtual void Init(	CTheApp* pTheApp,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	void ShootWeapons(D3DXVECTOR3 framePos);

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);

	CLevel*		m_pLevel;
	CWeapon*	m_pLaser;
	IEnemy*		m_pBossFrame;

	eSIDE		m_eSide;
	eACTION		m_eAction;

	eDIRECTION m_eDirection;

	float m_fShootBulletTimer;
	int m_iShootAmountCounter;
	int m_iShootAmountMax;
};