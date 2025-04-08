#pragma once

#include "EnemyBoss.h"
#include "Player.h"
#include "WeaponBoss1Laser.h"

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
		eACTION_WAIT,
		eACTION_TURN,
		eACTION_SHOOT
	};

	CEnemyBoss1Laser(	eTYPE eType,
						eBEHAVIOUR eBehaviour,
						eSIDE eSide);

	virtual ~CEnemyBoss1Laser(void);

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	void UpdateShip(IEnemy* pBossFrame,
					bool bShootPossible,
					bool leftActive,
					float fFrametime);

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

	void InitPosition(D3DXVECTOR3 pos);

	inline eACTION GetAction() { return this->m_eAction; }
	inline void SetAction(eACTION eAction) { this->m_eAction = eAction; }

	inline bool GetRotateLaser() { return this->m_bRotateLaser; }
	inline void SetRotateLaser(bool bRotate) { this->m_bRotateLaser = bRotate; }

	inline int GetShootMulti() { return this->m_iShootMulti; }
	inline void SetShootMulti(int iShootMulti) { this->m_iShootMulti = iShootMulti; }

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	enum eDIRECTION
	{
		eDIRECTION_FRONT,
		eDIRECTION_DIAGONAL
	};

	void RandomTurn();
	void ShootWeapons(D3DXVECTOR3 framePos);
	void RotateLaser(IEnemy* pBossFrame, float fFrametime);

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);

	// weapons

	CWeapon*	m_pLaser;

	eSIDE		m_eSide;
	eACTION		m_eAction;
	eDIRECTION	m_eDirection;

	/** TIMERS **/

	// fixed time between single multi-shots
	// starts to turn open and attack
	float		m_fShootMultiTime;

	// timer to calculate next single multi-shot
	float		m_fShootMultiTimer;

	// value to indicate max number of bullets
	// to be shot in one multi-shot session
	int			m_iShootMultiMax;
	int			m_iShootMulti;

	// value to indicate the number of shots 
	// being shot in the current multi-shot session
	int			m_iShootMultiCount;

	bool		m_bRotateLaser;

	float		m_fAngleZ;
	float		m_fAngleMaxZ;
};