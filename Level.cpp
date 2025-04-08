#include "Level.h"

CLevel::CLevel(void)
{
	this->m_pTheApp = NULL;

	this->m_bActive = false;
	this->m_iLevelNumber = 0;

	this->m_fPlayerVelocityEnemy = 0.0f;
	this->m_fPlayerVelocityObstacle = 0.0f;

	this->m_fPlayerBoostMaxEnemy = 0.0f;
	this->m_fPlayerBoostMaxObstacle = 0.0f;

	this->m_fFirstEnemyLaunch = 0.0f;
	this->m_fFirstEnemyStrike = 0.0f;
	this->m_fTimeEnemyLaunch = 0.0f;
	this->m_fTimeEnemyStrike = 0.0f;
	this->m_fTimeObstacleStart = 0.0f;

	this->m_iFleetsLaunch = 0;
	this->m_iFleetsStrike = 0;
	this->m_iMaxEnemiesScreen = 0;
	this->m_iMaxLaunchEnemies = 0;
	this->m_iMaxStrikeEnemies = 0;
	this->m_iLaunchSizeMin = 0;
	this->m_iLaunchSizeMax = 0;
	this->m_iStrikeSizeMin = 0;
	this->m_iStrikeSizeMax = 0;
	this->m_bLaunchFirst = false;
	this->m_bStrikeFirst = false;

	this->m_iObstacles = 0;

	this->m_fObstacleMinMarginY = 0.0f;
	this->m_fObstacleMaxMarginY = 0.0f;

	this->m_bObstaclesFirst = false;
	this->m_bObstacleEnemies = false;

	this->m_iBackgroundMiddleSpeed = 0;
	this->m_iBackgroundMiddlePause = 0;

	this->m_iBackgroundTopSpeedEnemies = 0;
	this->m_iBackgroundTopPauseEnemies = 0;
	this->m_iBackgroundTopSpeedObstacles = 0;
	this->m_iBackgroundTopPauseObstacles = 0;
	this->m_iBackgroundTopSpeedBoss = 0;
	this->m_iBackgroundTopPauseBoss = 0;

	this->m_pLaunchFleetSize = NULL;
	this->m_pStrikeFleetSize = NULL;
}

CLevel::~CLevel(void)
{
}

void CLevel::Create(CTheApp *pTheApp)
{
	this->m_pTheApp = pTheApp;
}

void CLevel::Release()
{
	if(this->m_pLaunchFleetSize)
	{
		delete [] this->m_pLaunchFleetSize;
		this->m_pLaunchFleetSize = NULL;
	}
	if(this->m_pStrikeFleetSize)
	{
		delete [] this->m_pStrikeFleetSize;
		this->m_pStrikeFleetSize = NULL;
	}

	this->m_pTheApp = NULL;
}

void CLevel::ReadLevel(void)
{
	this->m_iLevelNumber++;

	if(this->m_iLevelNumber <= 3)
	{
		switch( this->m_iLevelNumber )
		{
		case 1:

			this->m_fPlayerVelocityEnemy = 50.0f;
			this->m_fPlayerVelocityObstacle = 0.0f;
			this->m_fPlayerBoostMaxEnemy = 100.0f;
			this->m_fPlayerBoostMaxObstacle = 100.0f;
			this->m_fFirstEnemyLaunch = -0.2f;
			this->m_fFirstEnemyStrike = 0.0f;
			this->m_fTimeEnemyLaunch = 0.0f;
			this->m_fTimeEnemyStrike = 0.13f;
			this->m_fTimeObstacleStart = 0.5f;
			this->m_iMaxEnemiesScreen = 4;
			this->m_iMaxLaunchEnemies = 25;
			this->m_iMaxStrikeEnemies = 25;
			this->m_iLaunchSizeMin = 3;
			this->m_iLaunchSizeMax = 4;
			this->m_iStrikeSizeMin = 4;
			this->m_iStrikeSizeMax = 5;
			this->m_bLaunchFirst = true;
			this->m_bStrikeFirst = false;
			this->m_iObstacles = 0;
			this->m_fObstacleMinMarginY = 45.0f;
			this->m_fObstacleMaxMarginY = 150.0f;
			this->m_bObstaclesFirst = false;
			this->m_bObstacleEnemies = false;
			this->m_iBackgroundMiddleSpeed = 1;
			this->m_iBackgroundMiddlePause = 5;
			this->m_iBackgroundTopSpeedEnemies = 5;
			this->m_iBackgroundTopPauseEnemies = 0;
			this->m_iBackgroundTopSpeedObstacles = 1;
			this->m_iBackgroundTopPauseObstacles = 0;
			this->m_iBackgroundTopSpeedBoss = 1;
			this->m_iBackgroundTopPauseBoss = 2;

			break;

		case 2:

			this->m_fPlayerVelocityEnemy = 50.0f;
			this->m_fPlayerVelocityObstacle = 0.0f;
			this->m_fPlayerBoostMaxEnemy = 100.0f;
			this->m_fPlayerBoostMaxObstacle = 100.0f;
			this->m_fFirstEnemyLaunch = 0.0f;
			this->m_fFirstEnemyStrike = 0.0f;
			this->m_fTimeEnemyLaunch = 0.0f;
			this->m_fTimeEnemyStrike = 0.12f;
			this->m_fTimeObstacleStart = 0.5f;
			this->m_iMaxEnemiesScreen = 5;
			this->m_iMaxLaunchEnemies = 35;
			this->m_iMaxStrikeEnemies = 35;
			this->m_iLaunchSizeMin = 4;
			this->m_iLaunchSizeMax = 5;
			this->m_iStrikeSizeMin = 5;
			this->m_iStrikeSizeMax = 6;
			this->m_bLaunchFirst = false;
			this->m_bStrikeFirst = true;
			this->m_iObstacles = 20;
			this->m_fObstacleMinMarginY = 45.0f;
			this->m_fObstacleMaxMarginY = 150.0f;
			this->m_bObstaclesFirst = true;
			this->m_bObstacleEnemies = true;
			this->m_iBackgroundMiddleSpeed = 1;
			this->m_iBackgroundMiddlePause = 5;
			this->m_iBackgroundTopSpeedEnemies = 5;
			this->m_iBackgroundTopPauseEnemies = 0;
			this->m_iBackgroundTopSpeedObstacles = 1;
			this->m_iBackgroundTopPauseObstacles = 0;
			this->m_iBackgroundTopSpeedBoss = 1;
			this->m_iBackgroundTopPauseBoss = 2;

			break;

		case 3:

			this->m_fPlayerVelocityEnemy = 50.0f;
			this->m_fPlayerVelocityObstacle = 30.0f;
			this->m_fPlayerBoostMaxEnemy = 100.0f;
			this->m_fPlayerBoostMaxObstacle = 100.0f;
			this->m_fFirstEnemyLaunch = -0.2f;
			this->m_fFirstEnemyStrike = 0.0f;
			this->m_fTimeEnemyLaunch = 0.0f;
			this->m_fTimeEnemyStrike = 0.115f;
			this->m_fTimeObstacleStart = 0.5f;
			this->m_iMaxEnemiesScreen = 6;
			this->m_iMaxLaunchEnemies = 45;
			this->m_iMaxStrikeEnemies = 45;
			this->m_iLaunchSizeMin = 5;
			this->m_iLaunchSizeMax = 6;
			this->m_iStrikeSizeMin = 6;
			this->m_iStrikeSizeMax = 7;
			this->m_bLaunchFirst = false;
			this->m_bStrikeFirst = true;
			this->m_iObstacles = 30;
			this->m_fObstacleMinMarginY = 45.0f;
			this->m_fObstacleMaxMarginY = 150.0f;
			this->m_bObstaclesFirst = false;
			this->m_bObstacleEnemies = true;
			this->m_iBackgroundMiddleSpeed = 1;
			this->m_iBackgroundMiddlePause = 5;
			this->m_iBackgroundTopSpeedEnemies = 5;
			this->m_iBackgroundTopPauseEnemies = 0;
			this->m_iBackgroundTopSpeedObstacles = 2;
			this->m_iBackgroundTopPauseObstacles = 1;
			this->m_iBackgroundTopSpeedBoss = 1;
			this->m_iBackgroundTopPauseBoss = 2;

			break;
		}

		this->CalculateLaunchFleets();
		this->CalculateStrikeFleets();

		this->m_bActive = true;
	}
	else
	{
		this->m_bActive = false;
	}
}

int CLevel::GetLaunchSize()
{
	int iLaunchSize = 0;

	iLaunchSize = this->m_pTheApp->RandInt(	this->m_iLaunchSizeMin, 
											this->m_iLaunchSizeMax);
	return iLaunchSize;
}

int CLevel::GetStrikeSize()
{
	int iStrikeSize = 0;

	iStrikeSize = this->m_pTheApp->RandInt(	this->m_iStrikeSizeMin, 
											this->m_iStrikeSizeMax);
	return iStrikeSize;
}

CLevel::eSHIP_TYPE CLevel::GetLaunchShip()
{
	eSHIP_TYPE eShipType = eSHIP_TYPE_DRONE;

	switch( this->m_iLevelNumber )
	{
	case 1:

		eShipType = eSHIP_TYPE_SNIPER;
		switch(this->m_pTheApp->RandInt(1,3))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		}

		break;

	case 2:

		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 4:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 5:
			eShipType = eSHIP_TYPE_ROLLER;
			break;
		}

		break;

	case 3:

		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 4:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 5:
			eShipType = eSHIP_TYPE_ROLLER;
			break;
		}

		break;
	}

	return eShipType;
}

CLevel::eSHIP_TYPE CLevel::GetStrikeShip()
{
	eSHIP_TYPE eShipType = eSHIP_TYPE_DRONE;

	switch( this->m_iLevelNumber )
	{
	case 1:

		switch(this->m_pTheApp->RandInt(1,3))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		}

		break;

	case 2:

		switch(this->m_pTheApp->RandInt(1,2))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		}

		break;

	case 3:

		switch(this->m_pTheApp->RandInt(1,2))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		}

		break;
	}

	return eShipType;
}

CLevel::eSHIP_TYPE CLevel::GetObstacleShip()
{
	eSHIP_TYPE eShipType = eSHIP_TYPE_DRONE;

	switch( this->m_iLevelNumber )
	{
	case 1:

		switch(this->m_pTheApp->RandInt(1,3))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		}

		break;

	case 2:

		switch(this->m_pTheApp->RandInt(1,3))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		}

		break;

	case 3:

		switch(this->m_pTheApp->RandInt(1,2))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		}

		break;
	}

	return eShipType;
}

CLevel::eSHIP_TYPE CLevel::GetReinforcementShip()
{
	eSHIP_TYPE eShipType = eSHIP_TYPE_DRONE;

	switch(this->m_iLevelNumber)
	{
	case 1:

		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 4:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 5:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		}

		break;

	case 2:

		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 4:
			eShipType = eSHIP_TYPE_ROLLER;
			break;
		case 5:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		}

		break;

	case 3:

		switch(this->m_pTheApp->RandInt(1,5))
		{
		case 1:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 2:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		case 3:
			eShipType = eSHIP_TYPE_DRONE;
			break;
		case 4:
			eShipType = eSHIP_TYPE_ROLLER;
			break;
		case 5:
			eShipType = eSHIP_TYPE_SNIPER;
			break;
		}

		break;
	}

	return eShipType;
}

float CLevel::GetRandReinforcementAppearTime()
{
	float fRandTime = 0.0f;

	switch(this->m_iLevelNumber)
	{
	case 1:
		fRandTime = this->m_pTheApp->RandFloat(0.0f, 2.0f);
		break;
	case 2:
		fRandTime = this->m_pTheApp->RandFloat(0.0f, 2.0f);
		break;
	case 3:
		fRandTime = this->m_pTheApp->RandFloat(0.0f, 2.0f);
		break;
	}

	return fRandTime;
}

float CLevel::GetRandReinforcementSendTime()
{
	float fRandTime = 0.0f;

	switch(this->m_iLevelNumber)
	{
	case 1:
		fRandTime = this->m_pTheApp->RandFloat(4.0f, 12.0f);
		break;
	case 2:
		fRandTime = this->m_pTheApp->RandFloat(3.5f, 11.0f);
		break;
	case 3:
		fRandTime = this->m_pTheApp->RandFloat(3.0f, 10.0f);
		break;
	}

	return fRandTime;
}

float CLevel::GetRandObstacleTime(int iObstacleDepth)
{
	float fRandTime = 0.0f;

	switch(this->m_iLevelNumber)
	{
	case 1:

		switch(iObstacleDepth)
		{
		case 1:
			fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.3f);
			break;

		case 2:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 16.5f);
			break;

		case 3:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 13.5f);
			break;

		case 4:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 11.5f);
			break;

		case 5:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 10.5f);
			break;
		}

		break;

	case 2:

		switch(iObstacleDepth)
		{
		case 1:
			fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.3f);
			break;

		case 2:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 16.5f);
			break;

		case 3:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 13.5f);
			break;

		case 4:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 11.5f);
			break;

		case 5:
			fRandTime = this->m_pTheApp->RandFloat(3.5f, 10.5f);
			break;
		}

		break;

	case 3:

		switch(iObstacleDepth)
		{
		case 1:
			fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.4f);
			break;

		case 2:
			fRandTime = this->m_pTheApp->RandFloat(2.0f, 7.5f);
			break;

		case 3:
			fRandTime = this->m_pTheApp->RandFloat(2.0f, 6.5f);
			break;

		case 4:
			fRandTime = this->m_pTheApp->RandFloat(2.0f, 5.5f);
			break;

		case 5:
			fRandTime = this->m_pTheApp->RandFloat(2.0f, 4.5f);
			break;
		}

		break;
	}

	return fRandTime;
}

void CLevel::CalculateLaunchFleets()
{
	if(this->m_pLaunchFleetSize)
	{
		delete [] this->m_pLaunchFleetSize;
		this->m_pLaunchFleetSize = NULL;
	}

	this->m_pLaunchFleetSize = new int[100];

	int iIndex = 0;
	int iEnemiesLeft = this->m_iMaxLaunchEnemies;

	while(iEnemiesLeft > 0)
	{
		int randFleetSize = this->GetLaunchSize();

		if( (iEnemiesLeft - randFleetSize) < 0 )
		{
			randFleetSize = iEnemiesLeft;
		}

		this->m_pLaunchFleetSize[iIndex] = randFleetSize;

		iEnemiesLeft -= randFleetSize;
		iIndex++;
	}

	this->m_iFleetsLaunch = iIndex;
}

void CLevel::CalculateStrikeFleets()
{
	if(this->m_pStrikeFleetSize)
	{
		delete [] this->m_pStrikeFleetSize;
		this->m_pStrikeFleetSize = NULL;
	}

	this->m_pStrikeFleetSize = new int[100];

	int iIndex = 0;
	int iEnemiesLeft = this->m_iMaxStrikeEnemies;

	while(iEnemiesLeft > 0)
	{
		int randFleetSize = this->GetStrikeSize();

		if( (iEnemiesLeft - randFleetSize) < 0 )
		{
			randFleetSize = iEnemiesLeft;
		}

		this->m_pStrikeFleetSize[iIndex] = randFleetSize;

		iEnemiesLeft -= randFleetSize;
		iIndex++;
	}

	this->m_iFleetsStrike = iIndex;
}