#pragma once

// Forward declaration
class CTheApp;
class CLevel;
class CEnemyBoss1Laser;

class CEnemyBossSideLasersController
{
public:

	CEnemyBossSideLasersController();
	~CEnemyBossSideLasersController(void);

	void Create(CTheApp* pTheApp,
				CLevel* pLevel,
				IEnemy* pBossFrame,
				CEnemyBoss1Laser* pLaserLeft,
				CEnemyBoss1Laser* pLaserRight);

	void Update(float fFrametime, bool bShootPossible);
	void Activate();

	inline bool IsReady() { return (this->m_eAction == eACTION_READY); }

private:

	enum eACTION
	{
		eACTION_READY,
		eACTION_PAUSE,
		eACTION_SELECT_ROTATION,
		eACTION_ROTATE_WEAPONS,
		eACTION_SHOOT_WEAPONS
	};

	enum eDIRECTION
	{
		eDIRECTION_FRONT,
		eDIRECTION_DIAGONAL
	};

	void SetAction(eACTION eAction);
	void SetShootAction(CEnemyBoss1Laser* pLaserWeapon, int shootAmount);

	void InitWeaponRotation();
	void SetFrontRotation();
	void SetDiagonalRotation();

	bool SelectRandomRotation();

	bool RotateWeapons(float fFrametime);
	void UpdateRotation();

	CTheApp* m_pTheApp;
	CLevel* m_pLevel;
	IEnemy* m_pBossFrame;
	CEnemyBoss1Laser* m_pLaserLeft;
	CEnemyBoss1Laser* m_pLaserRight;

	eACTION m_eAction;
	eDIRECTION m_eDirection;

	float m_fPauseTimer;
	float m_fCurrentAngleZ;
	float m_fMaxAngleZ;
};

