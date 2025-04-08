#pragma once

// MESH COUNT
#define MESH_GAME_ASTEROIDS									15
#define MESH_GAME_BOSSES									6
#define MESH_GAME_BULLETS									7
#define MESH_GAME_ENEMIES									20
#define MESH_GAME_PLAYER									2
#define MESH_GAME_TEXT										1

// SPRITE COUNT
#define SPRITE_GAME											695

// MULTI-PART SPRITES
#define SPRITE_GAME_LEVEL_TITLE								7
#define SPRITE_GAME_BOSS_WARNING							10

#define SPRITE_GAME_PLAYER_CANNON_CHARGE_SMALL				10
#define SPRITE_GAME_PLAYER_CANNON_CHARGE_MEDIUM				10
#define SPRITE_GAME_PLAYER_CANNON_CHARGE_LARGE				10
#define SPRITE_GAME_PLAYER_CANNON_BEAM_CENTER				10
#define SPRITE_GAME_PLAYER_CANNON_BEAM_LEFT					10
#define SPRITE_GAME_PLAYER_CANNON_BEAM_RIGHT				10

#define LOAD_SPRITE_GAME_PLAYER_BLAST_UP					1
#define LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN					3
#define LOAD_SPRITE_GAME_PLAYER_BLAST_LEFT					7
#define LOAD_SPRITE_GAME_PLAYER_BLAST_RIGHT					2
#define LOAD_SPRITE_GAME_PLAYER_BLAST_UP_LEFT				4
#define LOAD_SPRITE_GAME_PLAYER_BLAST_UP_RIGHT				0
#define LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN_LEFT				6
#define LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN_RIGHT			5

#define RESOURCES_SPRITE_GAME_PLAYER_BLAST					8

#define LOAD_SPRITE_GAME_ENEMY_AFTERBURN_DRONE				0
#define LOAD_SPRITE_GAME_ENEMY_AFTERBURN_SNIPER				1
#define LOAD_SPRITE_GAME_ENEMY_AFTERBURN_ROLLER				2
#define LOAD_SPRITE_GAME_ENEMY_AFTERBURN_GUARD				3

#define RESOURCES_SPRITE_GAME_ENEMY_AFTERBURN				4

#define RESOURCES_SPRITE_GAME_BOSS_1_CANNON_CHARGE			19
#define RESOURCES_SPRITE_GAME_BOSS_1_CANNON_SHOOT			2

#define LOAD_SPRITE_GAME_BULLET_PLAYER_FRONT				0
#define LOAD_SPRITE_GAME_BULLET_PLAYER_DIAGONAL_LEFT		1
#define LOAD_SPRITE_GAME_BULLET_PLAYER_DIAGONAL_RIGHT		2

#define RESOURCES_SPRITE_GAME_BULLET_PLAYER					3

#define LOAD_SPRITE_GAME_BULLET_DRONE						0
#define LOAD_SPRITE_GAME_BULLET_SNIPER						1
#define LOAD_SPRITE_GAME_BULLET_ROLLER						2
#define LOAD_SPRITE_GAME_BULLET_GUARD						3

#define RESOURCES_SPRITE_GAME_BULLET_ENEMIES				4

#define LOAD_SPRITE_GAME_BULLET_BOSS_1_LASER_FRONT			0
#define LOAD_SPRITE_GAME_BULLET_BOSS_1_LASER_DIAGONAL_LEFT	1
#define LOAD_SPRITE_GAME_BULLET_BOSS_1_LASER_DIAGONAL_RIGHT	2
#define LOAD_SPRITE_GAME_BULLET_BOSS_1_SCATTER				3

#define RESOURCES_SPRITE_GAME_BULLET_BOSS_1					4

#define RESOURCES_SPRITE_GAME_EXPLOSION_PLAYER				50

#define RESOURCES_SPRITE_GAME_EXPLOSION_DRONE				50
#define RESOURCES_SPRITE_GAME_EXPLOSION_SNIPER				49
#define RESOURCES_SPRITE_GAME_EXPLOSION_ROLLER				50
#define RESOURCES_SPRITE_GAME_EXPLOSION_GUARD				1

#define RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_BIG			64
#define RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_PART			49
#define RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_1		64
#define RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_2		65
#define RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_3		62

#define RESOURCES_SPRITE_GAME_INFO_PLAYER_LIVES				11
#define RESOURCES_SPRITE_GAME_INFO_PLAYER_BLASTS			11
#define RESOURCES_SPRITE_GAME_INFO_PLAYER_HEALTH			10
#define RESOURCES_SPRITE_GAME_INFO_PLAYER_CANNON			16

#define RESOURCES_SPRITE_GAME_WIN_TITLE						20

#include "Sprite.h"
#include "Resources.h"

// Forward declaration
class CTheApp;

class CResourceGame : public CResources
{
public:

	CResourceGame();

	virtual void Init(CTheApp* pApp, CZipManager* pZipManager);

	virtual void Release();
	virtual HRESULT Load();

	/* GAME */

	// level titles
	inline CSprite* GetSpriteLevelTitleSpace() { return this->m_pSpriteLevelTitleSpace; }
	// boss warning
	inline CSprite* GetSpriteBossWarningSpace() { return this->m_pSpriteBossWarningSpace; }
	// player afterburn
	inline CSprite* GetSpriteGamePlayerAfterburn() { return this->m_pSpriteGamePlayerAfterburn; }
	// player cannon
	inline CSprite* GetSpritePlayerCannonChargeSmall() { return this->m_pSpritePlayerCannonChargeSmall; }
	inline CSprite* GetSpritePlayerCannonChargeMedium() { return this->m_pSpritePlayerCannonChargeMedium; }
	inline CSprite* GetSpritePlayerCannonChargeLarge() { return this->m_pSpritePlayerCannonChargeLarge; }
	inline CSprite* GetSpritePlayerCannonBeamCenter() { return this->m_pSpritePlayerCannonBeamCenter; }
	inline CSprite* GetSpritePlayerCannonBeamLeft() { return this->m_pSpritePlayerCannonBeamLeft; }
	inline CSprite* GetSpritePlayerCannonBeamRight() { return this->m_pSpritePlayerCannonBeamRight; }
	// player blast
	inline CSprite* GetSpritePlayerBlast() { return this->m_pSpritePlayerBlast; }
	// enemy afterburn
	inline CSprite* GetSpriteEnemyAfterburn() { return this->m_pSpriteEnemyAfterburn; }
	// boss sprites
	inline CSprite* GetSpriteBoss1CannonCharge() { return this->m_pSpriteBoss1CannonCharge; }
	inline CSprite* GetSpriteBoss1CannonShoot() { return this->m_pSpriteBoss1CannonShoot; }
	// explosions
	inline CSprite* GetSpriteExplosionPlayer() { return this->m_pSpriteExplosionPlayer; }
	inline CSprite* GetSpriteExplosionDrone() { return this->m_pSpriteExplosionDrone; }
	inline CSprite* GetSpriteExplosionSniper() { return this->m_pSpriteExplosionSniper; }
	inline CSprite* GetSpriteExplosionRoller() { return this->m_pSpriteExplosionRoller; }
	inline CSprite* GetSpriteExplosionGuard() { return this->m_pSpriteExplosionGuard; }
	inline CSprite* GetSpriteExplosionBossBig() { return this->m_pSpriteExplosionBossBig; }
	inline CSprite* GetSpriteExplosionBossPart() { return this->m_pSpriteExplosionBossPart; }
	inline CSprite* GetSpriteExplosionBossChain1() { return this->m_pSpriteExplosionBossChain1; }
	inline CSprite* GetSpriteExplosionBossChain2() { return this->m_pSpriteExplosionBossChain2; }
	inline CSprite* GetSpriteExplosionBossChain3() { return this->m_pSpriteExplosionBossChain3; }
	// game info
	inline CSprite* GetSpriteInfoPlayerLives() { return this->m_pSpriteInfoPlayerLives; }
	inline CSprite* GetSpriteInfoPlayerBlasts() { return this->m_pSpriteInfoPlayerBlasts; }
	inline CSprite* GetSpriteInfoPlayerHealth() { return this->m_pSpriteInfoPlayerHealth; }
	inline CSprite* GetSpriteInfoPlayerCannon() { return this->m_pSpriteInfoPlayerCannon; }
	// game endings
	inline CSprite* GetSpriteGameOverText() { return this->m_pSpriteGameOverText; }
	inline CSprite* GetSpriteGameWonText() { return this->m_pSpriteGameWonText; }

	// load cycle
	inline bool IsMasterZipFileLoaded() { return (m_bZipFileStepLoaded && !m_bipFileStepWaited); }

private:

	// LOAD METHODS

	HRESULT LoadMeshGameAsteroids();
	HRESULT LoadMeshGameBosses();
	HRESULT LoadMeshGameBullets();
	HRESULT LoadMeshGameEnemies();
	HRESULT LoadMeshGamePlayer();
	HRESULT LoadMeshGameText();
	HRESULT LoadSpriteGame();

	// LOAD CYCLE

	bool m_bZipFileStepLoaded;
	bool m_bipFileStepWaited;
	bool m_bGameAsteroidsLoaded;
	bool m_bGameBossesLoaded;
	bool m_bGameBulletsLoaded;
	bool m_bGameEnemiesLoaded;
	bool m_bGamePlayerLoaded;
	bool m_bGameTextLoaded;
	bool m_bGameLoaded;

	// SPRITE DEPTH

	float m_fDepthGameAfterburn;
	float m_fDepthGamePlayerCannon;
	float m_fDepthGamePlayerBlast;
	float m_fDepthGameBoss1Cannon;
	float m_fDepthGameBullets;
	float m_fDepthGameExplosion;
	float m_fDepthGameInfo;

	// SPRITES

	CSprite* m_pSpriteLevelTitleSpace;
	CSprite* m_pSpriteBossWarningSpace;

	CSprite* m_pSpriteGamePlayerAfterburn;

	CSprite* m_pSpritePlayerCannonChargeSmall;
	CSprite* m_pSpritePlayerCannonChargeMedium;
	CSprite* m_pSpritePlayerCannonChargeLarge;
	CSprite* m_pSpritePlayerCannonBeamCenter;
	CSprite* m_pSpritePlayerCannonBeamLeft;
	CSprite* m_pSpritePlayerCannonBeamRight;

	CSprite* m_pSpritePlayerBlast;

	CSprite* m_pSpriteEnemyAfterburn;

	CSprite* m_pSpriteBoss1CannonCharge;
	CSprite* m_pSpriteBoss1CannonShoot;

	CSprite* m_pSpriteExplosionPlayer;

	CSprite* m_pSpriteExplosionDrone;
	CSprite* m_pSpriteExplosionSniper;
	CSprite* m_pSpriteExplosionRoller;
	CSprite* m_pSpriteExplosionGuard;

	CSprite* m_pSpriteExplosionBossBig;
	CSprite* m_pSpriteExplosionBossPart;
	CSprite* m_pSpriteExplosionBossChain1;
	CSprite* m_pSpriteExplosionBossChain2;
	CSprite* m_pSpriteExplosionBossChain3;

	CSprite* m_pSpriteInfoPlayerLives;
	CSprite* m_pSpriteInfoPlayerBlasts;
	CSprite* m_pSpriteInfoPlayerHealth;
	CSprite* m_pSpriteInfoPlayerCannon;

	CSprite* m_pSpriteGameOverText;
	CSprite* m_pSpriteGameWonText;
};