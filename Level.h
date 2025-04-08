#pragma once

#define LEVELS_MAX		3

#include <windows.h>
#include <d3d9.h>
#include "TheApp.h"

class CLevel
{
public:

	enum eFLEET_TYPE
	{
		eFLEET_TYPE_LAUNCH,
		eFLEET_TYPE_STRIKE,
		eFLEET_TYPE_OBSTACLES
	};

	enum eSHIP_TYPE
	{
		eSHIP_TYPE_DRONE,
		eSHIP_TYPE_SNIPER,
		eSHIP_TYPE_ROLLER,
		eSHIP_TYPE_GUARD
	};

	CLevel(void);
	virtual ~CLevel(void);

	void Release();

	void Create(CTheApp *pTheApp);

	void ReadLevel();

	eSHIP_TYPE GetLaunchShip();
	eSHIP_TYPE GetStrikeShip();
	eSHIP_TYPE GetObstacleShip();
	eSHIP_TYPE GetReinforcementShip();

	float GetRandReinforcementAppearTime();
	float GetRandReinforcementSendTime();
	float GetRandObstacleTime(int iObstacleDepth);

	inline BOOL IsActive() { return this->m_bActive; }
	inline void SetActive(bool bSet) { this->m_bActive = bSet; }

	inline int GetLevelNumber() { return this->m_iLevelNumber; }

	inline float GetPlayerVelocityEnemy() { return this->m_fPlayerVelocityEnemy; }
	inline float GetPlayerVelocityObstacle() { return this->m_fPlayerVelocityObstacle; }

	inline float GetPlayerBoostMaxEnemy() { return this->m_fPlayerBoostMaxEnemy; }
	inline float GetPlayerBoostMaxObstacle() { return this->m_fPlayerBoostMaxObstacle; }

	inline float GetFirstEnemyLaunch() { return this->m_fFirstEnemyLaunch; }
	inline float GetFirstEnemyStrike() { return this->m_fFirstEnemyStrike; }
	inline float GetTimeEnemyLaunch() { return this->m_fTimeEnemyLaunch; }
	inline float GetTimeEnemyStrike() { return this->m_fTimeEnemyStrike; }

	inline int GetFleetsLaunch() { return this->m_iFleetsLaunch; }
	inline int GetFleetsStrike() { return this->m_iFleetsStrike; }
	inline int GetMaxEnemiesScreen() { return this->m_iMaxEnemiesScreen; }
	inline bool GetLaunchFirst() { return this->m_bLaunchFirst; }
	inline bool GetStrikeFirst() { return this->m_bStrikeFirst; }

	inline int* GetLaunchFleetSize() { return this->m_pLaunchFleetSize; }
	inline int* GetStrikeFleetSize() { return this->m_pStrikeFleetSize; }

	inline int GetObstacles() { return this->m_iObstacles; }

	inline float GetObstacleMinMarginY() { return this->m_fObstacleMinMarginY; }
	inline float GetObstacleMaxMarginY() { return this->m_fObstacleMaxMarginY; }
	
	inline bool IsObstaclesFirst() { return this->m_bObstaclesFirst; }
	inline bool IsObstacleEnemies() { return this->m_bObstacleEnemies; }

	inline int GetBackgroundMiddleSpeed() { return this->m_iBackgroundMiddleSpeed; }
	inline int GetBackgroundMiddlePause() { return this->m_iBackgroundMiddlePause; }
	
	inline int GetBackgroundTopSpeedEnemies() { return this->m_iBackgroundTopSpeedEnemies; }
	inline int GetBackgroundTopPauseEnemies() { return this->m_iBackgroundTopPauseEnemies; }

	inline int GetBackgroundTopSpeedObstacles() { return this->m_iBackgroundTopSpeedObstacles; }
	inline int GetBackgroundTopPauseObstacles() { return this->m_iBackgroundTopPauseObstacles; }

	inline int GetBackgroundTopSpeedBoss() { return this->m_iBackgroundTopSpeedBoss; }
	inline int GetBackgroundTopPauseBoss() { return this->m_iBackgroundTopPauseBoss; }

private:

	void CalculateLaunchFleets();
	void CalculateStrikeFleets();

	int GetLaunchSize();
	int GetStrikeSize();

	CTheApp*		m_pTheApp;

	bool			m_bActive;
	int				m_iLevelNumber;

	// PLAYER

	float			m_fPlayerVelocityEnemy;
	float			m_fPlayerVelocityObstacle;

	float			m_fPlayerBoostMaxEnemy;
	float			m_fPlayerBoostMaxObstacle;

	//TIMES

	float			m_fFirstEnemyLaunch;
	float			m_fFirstEnemyStrike;

	float			m_fTimeEnemyLaunch;
	float			m_fTimeEnemyStrike;

	float			m_fTimeObstacleStart;

	//ENEMIES

	int				m_iFleetsLaunch;
	int				m_iFleetsStrike;
	int				m_iMaxEnemiesScreen;
	int				m_iMaxLaunchEnemies;
	int				m_iMaxStrikeEnemies;
	int				m_iLaunchSizeMin;
	int				m_iLaunchSizeMax;
	int				m_iStrikeSizeMin;
	int				m_iStrikeSizeMax;

	bool			m_bLaunchFirst;
	bool			m_bStrikeFirst;

	int*			m_pLaunchFleetSize;
	int*			m_pStrikeFleetSize;

	//OBSTACLES

	int				m_iObstacles;

	float			m_fObstacleMinMarginY;
	float			m_fObstacleMaxMarginY;

	bool			m_bObstaclesFirst;
	bool			m_bObstacleEnemies;

	//BACKGROUNDS

	int				m_iBackgroundMiddleSpeed;
	int				m_iBackgroundMiddlePause;

	int				m_iBackgroundTopSpeedEnemies;
	int				m_iBackgroundTopPauseEnemies;
	int				m_iBackgroundTopSpeedObstacles;
	int				m_iBackgroundTopPauseObstacles;
	int				m_iBackgroundTopSpeedBoss;
	int				m_iBackgroundTopPauseBoss;
};