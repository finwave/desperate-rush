#pragma once

class CGameSettings
{
public:
	CGameSettings(void);
	virtual ~CGameSettings(void);

	void Create();
	float GetObstacleSpeed(int depth);

	// SOUND VOLUME
	
	float					m_fVolumePlayerMinigunShoot;
	float					m_fVolumePlayerMinigunTurn;
	float					m_fVolumePlayerCannon;
	float					m_fVolumePlayerBlast;
	float					m_fVolumePlayerVelocityAfterburn;

	float					m_fVolumeEnemyShootRoller;

	float					m_fVolumeBossScatter;
	float					m_fVolumeBossLaser;
	float					m_fVolumeBossCannon;

	// PLAYER

	int						m_iPlayerLives;
	int						m_iPlayerHealth;
	float					m_fPlayerWidth;
	float					m_fPlayerHeight;
	float					m_fPlayerSpeed;
	float					m_fPlayerMaxVelocity;

	int						m_iPlayerCannonEnergyMax;
	int						m_iPlayerCannonDamage;
	float					m_fPlayerCannonSpeed;
	float					m_fPlayerCannonTimer;
	int						m_iPlayerBlastDamage;
	int						m_iPlayerBlasts;

	// WEAPONS

	float					m_fPlayerBulletMinigunWidth;
	float					m_fPlayerBulletMinigunHeight;

	float					m_fEnemyDroneBulletWidth;
	float					m_fEnemyDroneBulletHeight;
	float					m_fEnemyDroneBulletSpeed;
	int						m_iEnemyDroneBulletDamage;
	int						m_iEnemyDroneShipDamage;

	float					m_fEnemySniperBulletWidth;
	float					m_fEnemySniperBulletHeight;
	float					m_fEnemySniperBulletSpeed;
	int						m_iEnemySniperBulletDamage;
	int						m_iEnemySniperShipDamage;

	float					m_fEnemyRollerBulletWidth;
	float					m_fEnemyRollerBulletHeight;
	float					m_fEnemyRollerBulletSpeed;
	int						m_iEnemyRollerBulletDamage;
	int						m_iEnemyRollerShipDamage;

	float					m_fEnemyGuardBulletWidth;
	float					m_fEnemyGuardBulletHeight;
	float					m_fEnemyGuardBulletSpeed;
	int						m_iEnemyGuardBulletDamage;
	int						m_iEnemyGuardShipDamage;

	float					m_fEnemyBoss1LaserBulletWidth;
	float					m_fEnemyBoss1LaserBulletHeight;
	float					m_fEnemyBoss1LaserBulletSpeed;
	int						m_iEnemyBoss1LaserBulletDamage;
	float					m_fEnemyBoss1ScatterBulletWidth;
	float					m_fEnemyBoss1ScatterBulletHeight;
	float					m_fEnemyBoss1ScatterBulletSpeed;
	int						m_iEnemyBoss1ScatterBulletDamage;

	float					m_fEnemyBoss1CannonSpeed;
	int						m_iEnemyBoss1CannonDamage;

	// ENEMIES

	int						m_iEnemyDroneHealth;
	float					m_fEnemyDroneWidth;
	float					m_fEnemyDroneHeight;
	float					m_fEnemyDroneEnterSpeed;
	float					m_fEnemyDroneLaunchSpeed;
	float					m_fEnemyDroneLaunchShootTime;
	float					m_fEnemyDroneStrikeSpeed;
	float					m_fEnemyDroneStrikeShootTime;

	int						m_iEnemySniperHealth;
	float					m_fEnemySniperWidth;
	float					m_fEnemySniperHeight;
	float					m_fEnemySniperEnterSpeed;
	float					m_fEnemySniperLaunchSpeed;
	float					m_fEnemySniperLaunchShootTime;
	float					m_fEnemySniperStrikeSpeed;
	float					m_fEnemySniperStrikeShootTime;

	int						m_iEnemyRollerHealth;
	float					m_fEnemyRollerWidth;
	float					m_fEnemyRollerHeight;
	float					m_fEnemyRollerEnterSpeed;
	float					m_fEnemyRollerLaunchSpeed;
	float					m_fEnemyRollerLaunchShootTime;
	float					m_fEnemyRollerStrikeSpeed;
	float					m_fEnemyRollerStrikeShootTime;

	int						m_iEnemyGuardHealth;
	float					m_fEnemyGuardWidth;
	float					m_fEnemyGuardHeight;
	float					m_fEnemyGuardEnterSpeed;
	float					m_fEnemyGuardLaunchSpeed;
	float					m_fEnemyGuardLaunchShootTime;
	float					m_fEnemyGuardStrikeSpeed;
	float					m_fEnemyGuardStrikeShootTime;

	float					m_fEnemyStrikeSpeedMultiplierMin;
	float					m_fEnemyStrikeSpeedMultiplierMax;

	// BOSSES

	float					m_fEnemyBoss1FrameWidth;
	float					m_fEnemyBoss1FrameHeight;
	int						m_iEnemyBoss1FrameHealth;
	float					m_fEnemyBoss1FrameSpeed;
	float					m_fEnemyBoss1FrameShootTime;

	float					m_fEnemyBoss1LaserWidth;
	float					m_fEnemyBoss1LaserHeight;
	int						m_iEnemyBoss1LaserHealth;

	float					m_fEnemyBoss1ScatterWidth;
	float					m_fEnemyBoss1ScatterHeight;
	int						m_iEnemyBoss1ScatterHealth;
	float					m_fEnemyBoss1ScatterSpeed;
	float					m_fEnemyBoss1ScatterShootTime;
	int						m_iEnemyBoss1ScatterShootMultiMax;

	float					m_fEnemyBoss1CannonShootTime;

	// OBSTACLES

	static float			BIG_ASTEROID_WIDTH;
	static float			BIG_ASTEROID_HEIGHT;

	static float			MEDIUM_ASTEROID_WIDTH;
	static float			MEDIUM_ASTEROID_HEIGHT;

	static float			SMALL_ASTEROID_WIDTH;
	static float			SMALL_ASTEROID_HEIGHT;

	// NUMBERS

	float					m_fGameNumberWidth;
	float					m_fGameNumberHeight;

	// POSITIONS

	float					m_fPlayerEnterPositionX;
	float					m_fPlayerEnterPositionY;
	float					m_fPlayerGamePositionX;
	float					m_fPlayerGamePositionY;

	int						m_iPlayerLivesBasePositionX;
	int						m_iPlayerLivesBasePositionY;
	int						m_iPlayerLivesNumberPositionX;
	int						m_iPlayerLivesNumberPositionY;

	int						m_iPlayerBlastsBasePositionX;
	int						m_iPlayerBlastsBasePositionY;
	int						m_iPlayerBlastsNumberPositionX;
	int						m_iPlayerBlastsNumberPositionY;

	int						m_iPlayerHealthBarPositionX;
	int						m_iPlayerHealthBarPositionY;
	int						m_iPlayerHealthMeterPositionX;
	int						m_iPlayerHealthMeterPositionY;

	int						m_iPlayerCannonBarPositionX;
	int						m_iPlayerCannonBarPositionY;
	int						m_iPlayerCannonMeterPositionX;
	int						m_iPlayerCannonMeterPositionY;
};