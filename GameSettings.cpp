#include "GameSettings.h"

float CGameSettings::BIG_ASTEROID_WIDTH = 74.0f;
float CGameSettings::BIG_ASTEROID_HEIGHT = 45.0f;

float CGameSettings::MEDIUM_ASTEROID_WIDTH = 50.0f;
float CGameSettings::MEDIUM_ASTEROID_HEIGHT = 36.0f;

float CGameSettings::SMALL_ASTEROID_WIDTH = 20.0f;
float CGameSettings::SMALL_ASTEROID_HEIGHT = 15.0f;

CGameSettings::CGameSettings(void)
{
	// SOUND VOLUME
	
	this->m_fVolumePlayerMinigunShoot = 0.0f;
	this->m_fVolumePlayerMinigunTurn = 0.0f;
	this->m_fVolumePlayerCannon = 0.0f;
	this->m_fVolumePlayerBlast = 0.0f;
	this->m_fVolumePlayerVelocityAfterburn = 0.0f;

	this->m_fVolumeEnemyShootRoller = 0.0f;

	this->m_fVolumeBossScatter = 0.0f;
	this->m_fVolumeBossLaser = 0.0f;
	this->m_fVolumeBossCannon = 0.0f;

	// PLAYER

	this->m_iPlayerLives = 0;
	this->m_iPlayerHealth = 0;
	this->m_fPlayerWidth = 0.0f;
	this->m_fPlayerHeight = 0.0f;
	this->m_fPlayerSpeed = 0.0f;
	this->m_fPlayerMaxVelocity = 0.0f;

	this->m_iPlayerCannonEnergyMax = 0;
	this->m_iPlayerCannonDamage = 0;
	this->m_fPlayerCannonSpeed = 0.0f;
	this->m_fPlayerCannonTimer = 0.0f;
	this->m_iPlayerBlastDamage = 0;
	this->m_iPlayerBlasts = 0;

	// WEAPONS

	this->m_fPlayerBulletMinigunWidth = 0.0f;
	this->m_fPlayerBulletMinigunHeight = 0.0f;

	this->m_fEnemyDroneBulletWidth = 0.0f;
	this->m_fEnemyDroneBulletHeight = 0.0f;
	this->m_fEnemyDroneBulletSpeed = 0.0f;
	this->m_iEnemyDroneBulletDamage = 0;
	this->m_iEnemyDroneShipDamage = 0;

	this->m_fEnemySniperBulletWidth = 0.0f;
	this->m_fEnemySniperBulletHeight = 0.0f;
	this->m_fEnemySniperBulletSpeed = 0.0f;
	this->m_iEnemySniperBulletDamage = 0;
	this->m_iEnemySniperShipDamage = 0;

	this->m_fEnemyRollerBulletWidth = 0.0f;
	this->m_fEnemyRollerBulletHeight = 0.0f;
	this->m_fEnemyRollerBulletSpeed = 0.0f;
	this->m_iEnemyRollerBulletDamage = 0;
	this->m_iEnemyRollerShipDamage = 0;

	this->m_fEnemyGuardBulletWidth = 0.0f;
	this->m_fEnemyGuardBulletHeight = 0.0f;
	this->m_fEnemyGuardBulletSpeed = 0.0f;
	this->m_iEnemyGuardBulletDamage = 0;
	this->m_iEnemyGuardShipDamage = 0;

	this->m_fEnemyBoss1LaserBulletWidth = 0.0f;
	this->m_fEnemyBoss1LaserBulletHeight = 0.0f;
	this->m_fEnemyBoss1LaserBulletSpeed = 0.0f;
	this->m_iEnemyBoss1LaserBulletDamage = 30;
	this->m_fEnemyBoss1ScatterBulletWidth = 0.0f;
	this->m_fEnemyBoss1ScatterBulletHeight = 0.0f;
	this->m_fEnemyBoss1ScatterBulletSpeed = 0.0f;
	this->m_iEnemyBoss1ScatterBulletDamage = 0;

	this->m_fEnemyBoss1CannonSpeed = 0.0f;
	this->m_iEnemyBoss1CannonDamage = 0;

	// ENEMIES

	this->m_iEnemyDroneHealth = 0;
	this->m_fEnemyDroneWidth = 0.0f;
	this->m_fEnemyDroneHeight = 0.0f;
	this->m_fEnemyDroneEnterSpeed = 0.0f;
	this->m_fEnemyDroneLaunchSpeed = 0.0f;
	this->m_fEnemyDroneLaunchShootTime = 0.0f;
	this->m_fEnemyDroneStrikeSpeed = 0.0f;
	this->m_fEnemyDroneStrikeShootTime = 0.0f;

	this->m_iEnemySniperHealth = 0;
	this->m_fEnemySniperWidth = 0.0f;
	this->m_fEnemySniperHeight = 0.0f;
	this->m_fEnemySniperEnterSpeed = 0.0f;
	this->m_fEnemySniperLaunchSpeed = 0.0f;
	this->m_fEnemySniperLaunchShootTime = 0.0f;
	this->m_fEnemySniperStrikeSpeed = 0.0f;
	this->m_fEnemySniperStrikeShootTime = 0.0f;

	this->m_iEnemyRollerHealth = 0;
	this->m_fEnemyRollerWidth = 0.0f;
	this->m_fEnemyRollerHeight = 0.0f;
	this->m_fEnemyRollerEnterSpeed = 0.0f;
	this->m_fEnemyRollerLaunchSpeed = 0.0f;
	this->m_fEnemyRollerLaunchShootTime = 0.0f;
	this->m_fEnemyRollerStrikeSpeed = 0.0f;
	this->m_fEnemyRollerStrikeShootTime = 0.0f;

	this->m_iEnemyGuardHealth = 0;
	this->m_fEnemyGuardWidth = 0.0f;
	this->m_fEnemyGuardHeight = 0.0f;
	this->m_fEnemyGuardEnterSpeed = 0.0f;
	this->m_fEnemyGuardLaunchSpeed = 0.0f;
	this->m_fEnemyGuardLaunchShootTime = 0.0f;
	this->m_fEnemyGuardStrikeSpeed = 0.0f;
	this->m_fEnemyGuardStrikeShootTime = 0.0f;

	this->m_fEnemyStrikeSpeedMultiplierMin = 0.0f;
	this->m_fEnemyStrikeSpeedMultiplierMax = 0.0f;

	// BOSSES

	this->m_fEnemyBoss1FrameWidth = 0.0f;
	this->m_fEnemyBoss1FrameHeight = 0.0f;
	this->m_iEnemyBoss1FrameHealth = 0.0f;
	this->m_fEnemyBoss1FrameSpeed = 0.0f;
	this->m_fEnemyBoss1FrameShootTime = 0.0f;

	this->m_fEnemyBoss1LaserWidth = 0.0f;
	this->m_fEnemyBoss1LaserHeight = 0.0f;
	this->m_iEnemyBoss1LaserHealth = 0;

	this->m_fEnemyBoss1ScatterWidth = 0.0f;
	this->m_fEnemyBoss1ScatterHeight = 0.0f;
	this->m_iEnemyBoss1ScatterHealth = 0;
	this->m_fEnemyBoss1ScatterSpeed = 0.0f;
	this->m_fEnemyBoss1ScatterShootTime = 0.0f;
	this->m_iEnemyBoss1ScatterShootMultiMax = 0;

	this->m_fEnemyBoss1CannonShootTime = 0.0f;

	// NUMBERS

	this->m_fGameNumberWidth = 0.0f;
	this->m_fGameNumberHeight = 0.0f;

	// POSITIONS

	this->m_fPlayerEnterPositionX = 0.0f;
	this->m_fPlayerEnterPositionY = 0.0f;
	this->m_fPlayerGamePositionX = 0.0f;
	this->m_fPlayerGamePositionY = 0.0f;

	this->m_iPlayerLivesBasePositionX = 0;
	this->m_iPlayerLivesBasePositionY = 0;
	this->m_iPlayerLivesNumberPositionX = 0;
	this->m_iPlayerLivesNumberPositionY = 0;

	this->m_iPlayerBlastsBasePositionX = 0;
	this->m_iPlayerBlastsBasePositionY = 0;
	this->m_iPlayerBlastsNumberPositionX = 0;
	this->m_iPlayerBlastsNumberPositionY = 0;

	this->m_iPlayerHealthBarPositionX = 0;
	this->m_iPlayerHealthBarPositionY = 0;
	this->m_iPlayerHealthMeterPositionX = 0;
	this->m_iPlayerHealthMeterPositionY = 0;

	this->m_iPlayerCannonBarPositionX = 0;
	this->m_iPlayerCannonBarPositionY = 0;
	this->m_iPlayerCannonMeterPositionX = 0;
	this->m_iPlayerCannonMeterPositionY = 0;
}

CGameSettings::~CGameSettings(void)
{
}

void CGameSettings::Create()
{
	// SOUND VOLUME (0.0f - 1.0f)

	this->m_fVolumePlayerMinigunShoot = 0.9f;
	this->m_fVolumePlayerMinigunTurn = 0.9f;
	this->m_fVolumePlayerCannon = 0.93f;
	this->m_fVolumePlayerBlast = 0.93f;
	this->m_fVolumePlayerVelocityAfterburn = 0.8f;

	this->m_fVolumeEnemyShootRoller = 1.0f;

	this->m_fVolumeBossScatter = 0.88f;
	this->m_fVolumeBossLaser = 0.94f;
	this->m_fVolumeBossCannon = 0.9f;

	// PLAYER

	this->m_iPlayerLives = 4;
	this->m_iPlayerHealth = 100;
	this->m_fPlayerWidth = 23.0f;
	this->m_fPlayerHeight = 34.0f;
	this->m_fPlayerSpeed = 125.0f;
	this->m_fPlayerMaxVelocity = 1.75f * this->m_fPlayerSpeed;

	this->m_iPlayerCannonEnergyMax = 200;
	this->m_iPlayerCannonDamage = 75;
	this->m_fPlayerCannonSpeed = 280.0f;
	this->m_fPlayerCannonTimer = 14.0f;
	this->m_iPlayerBlastDamage = 100;
	this->m_iPlayerBlasts = 3;
	
	// WEAPONS

	this->m_fPlayerBulletMinigunWidth = 2.0f;
	this->m_fPlayerBulletMinigunHeight = 2.0f;

	this->m_fEnemyDroneBulletWidth = 5.5f;
	this->m_fEnemyDroneBulletHeight = 5.5f;
	this->m_fEnemyDroneBulletSpeed = 400.0f;
	this->m_iEnemyDroneBulletDamage = 4;
	this->m_iEnemyDroneShipDamage = 50;

	this->m_fEnemySniperBulletWidth = 2.8f;
	this->m_fEnemySniperBulletHeight = 10.0f;
	this->m_fEnemySniperBulletSpeed = 450.0f;
	this->m_iEnemySniperBulletDamage = 6;
	this->m_iEnemySniperShipDamage = 60;

	this->m_fEnemyRollerBulletWidth = 2.5f;
	this->m_fEnemyRollerBulletHeight = 2.5f;
	this->m_fEnemyRollerBulletSpeed = 120.0f;
	this->m_iEnemyRollerBulletDamage = 3;
	this->m_iEnemyRollerShipDamage = 70;

	this->m_fEnemyGuardBulletWidth = 3.5f;
	this->m_fEnemyGuardBulletHeight = 3.5f;
	this->m_fEnemyGuardBulletSpeed = 250.0f;
	this->m_iEnemyGuardBulletDamage = 6;
	this->m_iEnemyGuardShipDamage = 80;

	this->m_fEnemyBoss1LaserBulletWidth = 5.0f;
	this->m_fEnemyBoss1LaserBulletHeight = 5.0f;
	this->m_fEnemyBoss1LaserBulletSpeed = 230.0f;
	this->m_iEnemyBoss1LaserBulletDamage = 3;

	this->m_fEnemyBoss1ScatterBulletWidth = 2.5f;
	this->m_fEnemyBoss1ScatterBulletHeight = 2.5f;
	this->m_fEnemyBoss1ScatterBulletSpeed = 180.0f;
	this->m_iEnemyBoss1ScatterBulletDamage = 5;

	this->m_fEnemyBoss1CannonSpeed = 220.0f;
	this->m_iEnemyBoss1CannonDamage = 200;

	// ENEMIES
	
	this->m_iEnemyDroneHealth = 15;
	this->m_fEnemyDroneWidth = 21.0f;
	this->m_fEnemyDroneHeight = 28.0f;
	this->m_fEnemyDroneEnterSpeed = 0.0075f;
	this->m_fEnemyDroneLaunchSpeed = 95.0f;
	this->m_fEnemyDroneLaunchShootTime = 0.2f;
	this->m_fEnemyDroneStrikeSpeed = 260.0f;
	this->m_fEnemyDroneStrikeShootTime = 0.35f;

	this->m_iEnemySniperHealth = 25;
	this->m_fEnemySniperWidth = 26.0f;
	this->m_fEnemySniperHeight = 35.0f;
	this->m_fEnemySniperEnterSpeed = 0.0070f;
	this->m_fEnemySniperLaunchSpeed = 90.0f;
	this->m_fEnemySniperLaunchShootTime = 0.25f;
	this->m_fEnemySniperStrikeSpeed = 200.0f;
	this->m_fEnemySniperStrikeShootTime = 0.45f;

	this->m_iEnemyRollerHealth = 50;
	this->m_fEnemyRollerWidth = 50.0f;
	this->m_fEnemyRollerHeight = 50.0f;
	this->m_fEnemyRollerEnterSpeed = 0.0056f;
	this->m_fEnemyRollerLaunchSpeed = 70.0f;
	this->m_fEnemyRollerLaunchShootTime = 0.4f;
	this->m_fEnemyRollerStrikeSpeed = 150.0f;
	this->m_fEnemyRollerStrikeShootTime = 0.8f;

	this->m_iEnemyGuardHealth = 70;
	this->m_fEnemyGuardWidth = 10.0f;
	this->m_fEnemyGuardHeight = 10.0f;
	this->m_fEnemyGuardEnterSpeed = 0.0056f;
	this->m_fEnemyGuardLaunchSpeed = 60.0f;
	this->m_fEnemyGuardLaunchShootTime = 0.4f;
	this->m_fEnemyGuardStrikeSpeed = 120.0f;
	this->m_fEnemyGuardStrikeShootTime = 1.2f;

	this->m_fEnemyStrikeSpeedMultiplierMin = 0.95f;
	this->m_fEnemyStrikeSpeedMultiplierMax = 1.0f;

	// BOSSES

	this->m_fEnemyBoss1FrameWidth = 85.0f;
	this->m_fEnemyBoss1FrameHeight = 123.0f;
	this->m_iEnemyBoss1FrameHealth = 1500;
	this->m_fEnemyBoss1FrameSpeed = 70.0f;
	this->m_fEnemyBoss1FrameShootTime = 1.0f;

	this->m_fEnemyBoss1LaserWidth = 60.0f;
	this->m_fEnemyBoss1LaserHeight = 60.0f;
	this->m_iEnemyBoss1LaserHealth = 600;

	this->m_fEnemyBoss1ScatterWidth = 25.0f;
	this->m_fEnemyBoss1ScatterHeight = 25.0f;
	this->m_iEnemyBoss1ScatterHealth = 400;
	this->m_fEnemyBoss1ScatterSpeed = 100.0f;
	this->m_fEnemyBoss1ScatterShootTime = 4.5f;
	this->m_iEnemyBoss1ScatterShootMultiMax = 40;

	this->m_fEnemyBoss1CannonShootTime = 4.0f;

	// NUMBERS

	this->m_fGameNumberWidth = 7.0f;
	this->m_fGameNumberHeight = 10.0f;

	// POSITIONS

	this->m_fPlayerEnterPositionX = 0.0f;
	this->m_fPlayerEnterPositionY = -250.0f;
	this->m_fPlayerGamePositionX = 0.0f;
	this->m_fPlayerGamePositionY = -105.0f;

	this->m_iPlayerLivesBasePositionX = 29;
	this->m_iPlayerLivesBasePositionY = 29;
	this->m_iPlayerLivesNumberPositionX = this->m_iPlayerLivesBasePositionX + 66;
	this->m_iPlayerLivesNumberPositionY = this->m_iPlayerLivesBasePositionY + 13;

	this->m_iPlayerBlastsBasePositionX = 661;
	this->m_iPlayerBlastsBasePositionY = 29;
	this->m_iPlayerBlastsNumberPositionX = this->m_iPlayerBlastsBasePositionX + 66;
	this->m_iPlayerBlastsNumberPositionY = this->m_iPlayerBlastsBasePositionY + 13;

	this->m_iPlayerHealthBarPositionX = 148;
	this->m_iPlayerHealthBarPositionY = 29;
	this->m_iPlayerHealthMeterPositionX = this->m_iPlayerHealthBarPositionX + 5;
	this->m_iPlayerHealthMeterPositionY = this->m_iPlayerHealthBarPositionY + 3;

	this->m_iPlayerCannonBarPositionX = 148;
	this->m_iPlayerCannonBarPositionY = 57;
	this->m_iPlayerCannonMeterPositionX = this->m_iPlayerCannonBarPositionX + 5;
	this->m_iPlayerCannonMeterPositionY = this->m_iPlayerCannonBarPositionY + 3;
}

float CGameSettings::GetObstacleSpeed(int depth)
{
	switch (depth)
	{
	case 2:
		return 15.0f;
	case 3:
		return 11.0f;
	case 4:
		return 7.0f;
	case 5:
		return 3.0f;
	default:
		return 35.0f;
	}
}
