#pragma once

#include "EnemyBoss.h"
#include "WeaponBoss1Scatter.h"

class CEnemyBoss1Scatter : public CEnemyBoss
{
public:

	enum eSIDE
	{
		eSIDE_LEFT,
		eSIDE_RIGHT
	};

	CEnemyBoss1Scatter(eTYPE eType,
							eBEHAVIOUR eBehaviour,
							eSIDE eSide);

	virtual ~CEnemyBoss1Scatter(void);

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							IEnemy* pBossFrame,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	void UpdateShip(IEnemy* pBossFrame,
					bool bShootPossible,
					float fBottomBorder,
					float fFrametime);

	virtual void Render();

	virtual HRESULT InitWeapons(CTheApp* pTheApp,
								LPD3DXMESH mesh,
								std::vector<D3DMATERIAL9*> materials,
								std::vector<LPDIRECT3DTEXTURE9> textures,
								float fScatterWidth,
								float fScatterHeight,
								float fScatterSpeed,
								int iScatterDamage);

	virtual HRESULT InitWeapons(CTheApp* pTheApp,
								LPD3DXMESH mesh,
								std::vector<MESHDATA>& meshData,
								float fScatterWidth,
								float fScatterHeight,
								float fScatterSpeed,
								int iScatterDamage);

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	enum eACTION
	{
		eACTION_WAIT,
		eACTION_SHOOT,
		eACTION_RUSH_DOWN,
		eACTION_RUSH_UP
	};

	void ShootWeapons();
	void SetRandAttack();

	void RotateScatter(IEnemy* pBossFrame);

	void SetMovement(eMOVE eMove);

	bool MovementRush(	float fBottomBorder,
						float fFrametime);

	void InitPosition(D3DXVECTOR3 posFrame);

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);

	// weapons

	CWeapon*	m_pBullet;

	eSIDE		m_eSide;
	eACTION		m_eAction;

	float		m_fAngleZ;
	float		m_fRotationIncrease;

	bool		m_bMoveDown;
	float		m_fOriginalYPos;
	float		m_fCurrentYPos;

	/** TIMERS **/

	// fixed time between single multi-shots
	float		m_fShootMultiTime;

	// timers to calculate next single multi-shot
	float		m_fShootMultiTimer;

	// value to indicate max number of bullets
	// to be shot in one multi-shot session
	int			m_iShootMultiMax;
	int			m_iShootMulti;

	// value to indicate the number of shots 
	// being shot in the current multi-shot session
	int			m_iShootMultiCount;
};