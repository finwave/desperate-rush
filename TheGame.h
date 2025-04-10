#pragma once

// LOAD DEFINES

#define INIT_STEP_MAX										1

#define	LOAD_MESH_GAME_0									0
#define	LOAD_MESH_GAME_1									1
#define	LOAD_MESH_GAME_2									2
#define	LOAD_MESH_GAME_3									3
#define	LOAD_MESH_GAME_4									4
#define	LOAD_MESH_GAME_5									5
#define	LOAD_MESH_GAME_6									6
#define	LOAD_MESH_GAME_7									7
#define	LOAD_MESH_GAME_8									8
#define	LOAD_MESH_GAME_9									9

#define	LOAD_MESH_GAME_MAX									10

#define LOAD_SPRITES_GAME_MAX								29

#define LOAD_CONTAINER_NUMBER_0								0
#define LOAD_CONTAINER_NUMBER_1								1
#define LOAD_CONTAINER_NUMBER_2								2
#define LOAD_CONTAINER_NUMBER_3								3
#define LOAD_CONTAINER_NUMBER_4								4
#define LOAD_CONTAINER_NUMBER_5								5
#define LOAD_CONTAINER_NUMBER_6								6
#define LOAD_CONTAINER_NUMBER_7								7
#define LOAD_CONTAINER_NUMBER_8								8
#define LOAD_CONTAINER_NUMBER_9								9

#define LOAD_CONTAINER_NUMBER_MAX							10

#define LOAD_CONTAINER_HUD_SCORE_TEXT						0
#define LOAD_CONTAINER_HUD_MAX								1

#define LOAD_CONTAINER_MAX									2 * LOAD_CONTAINER_NUMBER_MAX + LOAD_CONTAINER_HUD_MAX;

#define LOAD_TEMPLATE_SHIP_PLAYER							0
#define LOAD_TEMPLATE_SHIP_LAUNCH_DRONE						1
#define LOAD_TEMPLATE_SHIP_LAUNCH_SNIPER					2
#define LOAD_TEMPLATE_SHIP_LAUNCH_ROLLER					3
#define LOAD_TEMPLATE_SHIP_LAUNCH_VANGUARD					4
#define LOAD_TEMPLATE_SHIP_STRIKE_DRONE						5
#define LOAD_TEMPLATE_SHIP_STRIKE_SNIPER					6
#define LOAD_TEMPLATE_SHIP_STRIKE_ROLLER					7
#define LOAD_TEMPLATE_SHIP_STRIKE_VANGUARD					8

#define LOAD_TEMPLATE_SHIP_MAX								9

#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_PLAYER			0
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_DRONE		1
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_SNIPER		2
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_ROLLER		3
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_GUARD		4
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_DRONE		5
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_SNIPER		6
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_ROLLER		7
#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_GUARD		8

#define LOAD_TEMPLATE_SHIP_COLLISION_MESH_MAX				9

#define LOAD_TEMPLATE_WEAPON_ARRAYS							0
#define LOAD_TEMPLATE_WEAPON_PLAYER							1
#define LOAD_TEMPLATE_WEAPON_DRONE							2
#define LOAD_TEMPLATE_WEAPON_SNIPER							3
#define LOAD_TEMPLATE_WEAPON_ROLLER							4

#define LOAD_TEMPLATE_WEAPON_MAX							5

#define LOAD_TEMPLATE_WEAPON_COLLISION_MESH_PLAYER_FRONT	0
#define LOAD_TEMPLATE_WEAPON_COLLISION_MESH_PLAYER_DIAGONAL	1
#define LOAD_TEMPLATE_WEAPON_COLLISION_MESH_DRONE			2
#define LOAD_TEMPLATE_WEAPON_COLLISION_MESH_SNIPER			3

#define LOAD_TEMPLATE_WEAPON_COLLISION_MESH_MAX				4

#define LOAD_TEMPLATE_MAX									LOAD_TEMPLATE_SHIP_MAX + LOAD_TEMPLATE_SHIP_COLLISION_MESH_MAX + LOAD_TEMPLATE_WEAPON_MAX + LOAD_TEMPLATE_WEAPON_COLLISION_MESH_MAX;

// LEVEL LOAD STEPS

#define LOAD_LEVEL_ASTEROID_BIG								0
#define LOAD_LEVEL_ASTEROID_MEDIUM							1
#define LOAD_LEVEL_ASTEROID_SMALL							2
#define LOAD_LEVEL_ASTEROID_MAX								3

#define LOAD_LEVEL_DEFAULT_VALUES							0
#define LOAD_LEVEL_DYNAMIC_LIGHT							1
#define LOAD_LEVEL_RESET_ENEMY_VALUES_1						2
#define LOAD_LEVEL_CLEAR_ENEMIES							3
#define LOAD_LEVEL_CLEAR_OBSTACLES							4
#define LOAD_LEVEL_CLEAR_BULLETS							5
#define LOAD_LEVEL_CLEAR_EXPLOSIONS							6
#define LOAD_LEVEL_CLEAR_PARTICLES							7
#define LOAD_LEVEL_PREPARE_ENEMIES_LAUNCH					8
#define LOAD_LEVEL_PREPARE_ENEMIES_STRIKE					9
#define LOAD_LEVEL_PREPARE_ENEMIES_FLEET					10
#define LOAD_LEVEL_INIT_OBSTACLES							11
#define LOAD_LEVEL_COLLISION_MESH_OBSTACLES					12
#define LOAD_LEVEL_PREPARE_OBSTACLES						13
#define LOAD_LEVEL_RESET_ENEMY_VALUES_2						14
#define LOAD_LEVEL_INIT_BOSS								15
#define LOAD_LEVEL_RESET_BOSS_VALUES						16
#define LOAD_LEVEL_BACKGROUND								17
#define LOAD_LEVEL_SET_PLAYER_VALUES						18
#define LOAD_LEVEL_MUSIC									19
#define LOAD_LEVEL_MUSIC_BOSS								20
#define LOAD_LEVEL_INTRO									21

#define LOAD_LEVEL_STEPS_MAX								22

// SPRITE COUNTS

#define SPRITE_COUNT_BULLETS_PLAYER							3

// BOSS BEHAVIOUR DEFINES

#define GAME_BOSS_PARTS_DAMAGE

// BOSS EXPLOSION VALUES

#define EXPLOSION_CHAIN_REPEATS_BOSS_1						18
#define EXPLOSION_CHAIN_REPEATS_BOSS_2						18
#define EXPLOSION_CHAIN_REPEATS_BOSS_3						18

#define EXPLOSION_CHAIN_TIMER_MIN_BOSS_1					0.02
#define EXPLOSION_CHAIN_TIMER_MAX_BOSS_1					0.3
#define EXPLOSION_CHAIN_TIMER_MIN_BOSS_2					0.02
#define EXPLOSION_CHAIN_TIMER_MAX_BOSS_2					0.3
#define EXPLOSION_CHAIN_TIMER_MIN_BOSS_3					0.02
#define EXPLOSION_CHAIN_TIMER_MAX_BOSS_3					0.3

#define EXPLOSION_PART_TIMER_MIN_BOSS_1						0.01
#define EXPLOSION_PART_TIMER_MAX_BOSS_1						0.05
#define EXPLOSION_PART_TIMER_MIN_BOSS_2						0.01
#define EXPLOSION_PART_TIMER_MAX_BOSS_2						0.05
#define EXPLOSION_PART_TIMER_MIN_BOSS_3						0.01
#define EXPLOSION_PART_TIMER_MAX_BOSS_3						0.05

#define EXPLOSION_BIG_TIMER_BOSS_1							4.0
#define EXPLOSION_BIG_TIMER_BOSS_2							4.0
#define EXPLOSION_BIG_TIMER_BOSS_3							4.0

// MISC VALUES

#define TIME_PLAYER_BLAST									0.8
#define TIMER_LEVEL_TITLE									0.8
#define TIMER_SOUND_EXPLOSION_ENEMY							6

// ENEMY FLEET VALUES

#define GAME_REINFORCEMENTS_LEVEL_1							20
#define GAME_REINFORCEMENTS_LEVEL_2							20
#define GAME_REINFORCEMENTS_LEVEL_3							20

#define GAME_REINFORCEMENT_COUNT_MIN_LEVEL_1				2
#define GAME_REINFORCEMENT_COUNT_MAX_LEVEL_1				8
#define GAME_REINFORCEMENT_COUNT_MIN_LEVEL_2				3
#define GAME_REINFORCEMENT_COUNT_MAX_LEVEL_2				16
#define GAME_REINFORCEMENT_COUNT_MIN_LEVEL_3				4
#define GAME_REINFORCEMENT_COUNT_MAX_LEVEL_3				24

// GAME STATES

#define GAME_STATE_LEVEL_INTRO								0
#define GAME_STATE_PLAY_ENEMIES								1
#define GAME_STATE_PLAY_OBSTACLES							2
#define GAME_STATE_WAIT_OBSTACLES							3
#define GAME_STATE_VELOCITY_DECREASE						4
#define GAME_STATE_SPEED_CHANGE								5
#define GAME_STATE_BOSS_INTRO								6
#define GAME_STATE_BOSS_ACTION								7
#define GAME_STATE_BOSS_CHAIN_EXPLOSION						8
#define GAME_STATE_BOSS_BIG_EXPLOSION						9
#define GAME_STATE_LEVEL_OUTRO								10
#define GAME_STATE_INIT_LEVEL								11
#define GAME_STATE_LOAD_LEVEL								12
#define GAME_STATE_END_SUCCESS								13
#define GAME_STATE_END_FAILED								14
#define GAME_STATE_BLAST_ACTIVE								15
#define GAME_STATE_QUIT										16

#include "IState.h"
#include "InputJoystick.h"
#include "Level.h"
#include "I3DObject.h"
#include "Player.h"
#include "PlayerMinigun.h"
#include "PlayerController.h"
#include "EnemyDrone.h"
#include "EnemySniper.h"
#include "EnemyRoller.h"
#include "EnemyGuard.h"
#include "EnemyBoss1Core.h"
#include "EnemyBoss1Frame.h"
#include "EnemyBoss1Laser.h"
#include "EnemyBoss1Scatter.h"
#include "EnemyBoss1Cannon.h"
#include "Explosions.h"
#include "Weapon.h"
#include "WeaponPlayerFront.h"
#include "WeaponPlayerDiagonal.h"
#include "WeaponEnemyDrone.h"
#include "WeaponEnemySniper.h"
#include "Queue.h"
#include "Sprite.h"
#include "SpriteScrolling.h"
#include "Obstacle.h"
#include "GameSettings.h"
#include "Number.h"
#include "DisplayObject.h"
//#include "ParticleEngine.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

class CTheGame
{
public:

	CTheGame(void);
	virtual ~CTheGame(void);

	/*
	 * Create
	 * Connect TheApp with TheGame
	 */
	HRESULT Create(	CTheApp* pTheApp,
					IState* pState,
					DWORD dwState);

	/*
	 * Render
	 * Method invokes all necessary methods to make game playable.
	 */
	void Render(void);

	/*
	 * Release
	 * Let's clean all the mess.
	 */
	void Release();

	inline bool IsInitialized() { return this->m_bInitialized; };

#ifdef SHADOWS
	inline CShadowVolume* GetShadowVolumes() { return this->m_pShadowVolumes; }
#endif

private:

	enum ePLAYER_CANNON_STATE
	{
		ePLAYER_CANNON_STATE_READY,
		ePLAYER_CANNON_STATE_CHARGE,
		ePLAYER_CANNON_STATE_BEAM,
		ePLAYER_CANNON_STATE_RECHARGE
	};

	enum ePLAYER_CANNON_CHARGE
	{
		ePLAYER_CANNON_CHARGE_SMALL,
		ePLAYER_CANNON_CHARGE_MEDIUM,
		ePLAYER_CANNON_CHARGE_LARGE
	};

	enum ePLAYER_CANNON_BEAM
	{
		ePLAYER_CANNON_BEAM_CENTER,
		ePLAYER_CANNON_BEAM_LEFT,
		ePLAYER_CANNON_BEAM_RIGHT
	};

	enum eEXPLOSION_ENEMY
	{
		eEXPLOSION_ENEMY_NORMAL_1,
		eEXPLOSION_ENEMY_NORMAL_2,
		eEXPLOSION_ENEMY_QUIET_1,
		eEXPLOSION_ENEMY_QUIET_2
	};

	void SwitchGameState(int iNextGameState);

	void ActivateObstacles(CQueue<CObstacle*>* pObstacles, BOOL bEnable);
	void ActivateBackgroundObstacles(BOOL bEnable);

	void QuitGameAction(float fFrametime);

	void LoadSprites();
	HRESULT LoadSpritesBackground();

	HRESULT LoadMeshes();

	HRESULT InitLevelBoss();
	HRESULT InitLevelObstacles();
	CObstacle* CreateTemplateObstacle(int mapKey, float objectWidth, float objectHeight);

	void InitVolumeSoundEffect();

	void LoadMusicLevel();
	void LoadMusicBoss();
	void CheckMusicEnd();
	void RestartMusic();
	void PlayMusicLevel();
	void PlayMusicBoss();
	void PlayMusicGameOutro();
	void PlayMusicGameOver();
	bool FadeOutMusicLevel(float fFrametime);
	bool FadeOutMusicBoss(float fFrametime);
	void StopMusicLevel();
	void StopMusicBoss();
	void StopMusicAll();
	void PlaySoundPlayerAfterburn();
	void PlaySoundPlayerCannonCharge();
	void PlaySoundPlayerCannonBeam();
	void PlaySoundFirePlayerMinigun();
	void PlaySoundFireEnemy(IEnemy* pEnemy);
	void PlaySoundHitPlayer();
	void PlaySoundHitEnemy(IEnemy* pEnemy);
	void PlaySoundHitBoss(IEnemy* pEnemy);
	void PlaySoundExplosionEnemy(IEnemy* pEnemy);
	void PlaySoundExplosionBossChain(int iWave);
	void PlaySoundExplosionBossPart();
	void ResetSoundExplosionEnemy(float fFrametime);

	void CheckQuitGame(float fFrametime);
	void CheckGameOver();
	bool CheckBossEnter();
	void CheckExtraLife();

	void PlayerSetEnter(int currentGameState);
	void PlayerMoveEnter(float fFrametime);
	void PlayerMoveAway(float fFrametime);
	void PlayerDestroyed();
	void PlayerBlastActive();
	void PlayerBlastDeactive();
	void PlayerShooting(float fFrametime);
	bool PlayerShootPossible();
	bool PlayerCannonLineOfFireEnemies(IEnemy* pEnemy);
	bool PlayerCannonLineOfFireBullets(CWeapon* bullet);
	bool PlayerResetMiniguns();
	void PlayerResetCannon();
	void PlayerExplosion();

	IEnemy* GenerateEnemies(CLevel::eFLEET_TYPE eFleetType,
							CLevel::eSHIP_TYPE eShipType);

	void ClearLaunchEnemies();
	void ClearStrikeEnemies();
	void ClearLevelObstacles();
	void PrepareLaunchEnemies();
	void PrepareStrikeEnemies();
	void PrepareReinforcements();
	void PrepareObstacles();

	bool IsGenerateObstacleEnemy();

	CObstacle* GenerateObstacle(float fPosY, int iDepth);
	CObstacle* GenerateObstacleType(int iDepth);

	bool IsBoxCollisionObstacleVsEnemies(CObstacle* obstacle);
	bool IsBoxCollisionEnemyVsObstacles(IEnemy* pEnemy);
	bool IsBoxCollisionObstacleVsObstacle(CObstacle* pObstacle, int iDepth);

	IEnemy* GenerateObstacleEnemy(float fPosY);

	void EnemyLaunch(float fFrametime);
	void EnemyStrike(float fFrametime);
	void EnemyExplosion(IEnemy* pEnemy);

	HRESULT GenerateParticlesBullet(CWeapon* pWeapon, D3DXVECTOR3 vPosition);

	void NormalSpeedReinforcement();
	void IncreaseSpeedReinforcement();
	void NormalSpeedObstacle();
	void IncreaseSpeedObstacle();

	void BossFrameChainExplosion();
	void BossFrameBigExplosion();
	void BossPartExplosion(IEnemy* pEnemy);

	bool CheckBossPartExplosion(int iCountBossChainExplosions);

	void EnemyShooting();
	void EnemyShoots(IEnemy* pEnemy);
	bool ActiveEnemyLineOfFire(IEnemy* pEnemy, bool bInverse);
	bool ReinforcementLineOfFire(IEnemy* pEnemy, IEnemy* pOther, bool bInverse);
	bool ObstacleEnemyLineOfFire(IEnemy* pEnemy, bool bInverse);
	void EnemyCopyBullets(IEnemy* pEnemy);

	float GetCollisionDamagePlayerVsEnemy(IEnemy* pEnemy);

	void CollisionPlayerVsBoss();
	void CollisionPlayerVsEnemy();
	void CollisionPlayerCannonVsBoss(float fFrametime);
	void CollisionPlayerCannonVsEnemy(float fFrametime);
	void CollisionPlayerCannonVsBossBullet();
	void CollisionPlayerCannonVsEnemyBullet();
	void CollisionPlayerVsObstacle();
	void CollisionEnemyVsObstacle();
	void CollisionEnemyVsEnemy();
	void CollisionBulletVsBoss();
	void CollisionBulletVsEnemy();
	void CollisionBulletVsPlayer();
	void CollisionBulletVsObstacle();
	void CollisionBulletVsBorder();

	void CheckCollisionBulletVsEnemy(CWeapon* pBullet, IEnemy* pEnemy, D3DXVECTOR3* pBPos);

	void CheckCollisionBulletVsPlayer(CWeapon* pBullet, D3DXVECTOR3* pBPos);

	void ClearEnemies();
	void ClearObstacles();
	void ClearBullets(bool bForced);
	void ClearParticles();

	void UpdatePlayer(float fFrametime);
	void UpdateBoss(float fFrametime);
	void UpdateBossShake(bool bBlast, float fFrametime);
	void UpdateEnemies();
	void UpdateEnemiesShake(bool bBlast, float fFrametime);
	void UpdateEnemiesShake(IEnemy* pEnemy, bool bBlast, float fFrametime);
	void UpdateReinforcements(float fFrametime);
	void UpdateBullets(float fFrametime);
	void UpdateExplosions(float fFrametime);
	void UpdateTime(float fFrametime);

	void UpdateVelocityTimeMargin(float fFrametime);
	void UpdateVelocityPixels();
	void UpdateBackgroundVelocity();
	void UpdateExplosionVelocity();

	void RenderPlayer(float fFrametime);
	void RenderBoss(float fFrametime, bool bFreeze);
	void RenderActiveEnemies(float fFrametime, bool bFreeze);
	void RenderReinforcements(float fFrametime, bool bFreeze);
	void RenderObstacleEnemies(float fFrametime, bool bFreeze);
	void RenderObstacles(float fFrametime, bool bFreeze);
	void RenderBullets(float fFrametime, bool bFreeze);
	void RenderExplosions();
	void RenderParticles(float fFrametime, bool bFreeze);
	void RenderPlayerAfterburn(bool bFreeze);
	void RenderPlayerCannon(float fFrametime, bool bFreeze);
	void RenderPlayerCannonCharge(float fFrametime, bool bFreeze);
	void RenderPlayerCannonBeam(float fFrametime, bool bFreeze);
	void RenderStatistics(float fFrametime);
	void RenderPlayerLives();
	void RenderPlayerBlasts();
	void RenderPlayerHealthBar();
	void RenderPlayerCannonBar();
	void RenderScore(float fFrametime);
	void RenderTime(float fFrametime);
	void RenderLevelTitle();
	bool RenderLevelTitleIn();
	bool RenderLevelTitleOut();
	bool RenderMissionInfo();
	bool RenderBossWarning(float fFrametime, bool bFreeze);
	void RenderEndSuccess(float fFrametime);
	void RenderEndFailed();
	void RenderBackgrounds();

	void EnablePlayerCannonDamage();

	char* GetTimeString();

	bool IsBoxCollision(const D3DXVECTOR3& pos1,
						float fWidth,
						float fHeight,
						const D3DXVECTOR3& pos2);

	bool IsBoxCollision(const D3DXVECTOR3& pos1,
						float fWidth1,
						float fHeight1,
						const D3DXVECTOR3& pos2,
						float fWidth2,
						float fHeight2);

	bool IsMeshCollision(	I3DObject* pObject1,
							I3DObject* pObject2,
							bool bInverseMatrix,
							bool bDepth);

	HRESULT CreateCollisionMeshBoss();
	HRESULT CreateCollisionMeshEnemies();
	void CreateCollisionMeshEnemies(IEnemy* pEnemy);
	HRESULT CreateCollisionMeshWeapons();
	void CreateCollisionMeshWeapons(CWeapon* pWeapon);
	HRESULT CreateCollisionMeshObstacles();
	void CreateCollisionMeshObstacles(CObstacle* pObstacle);

	void ShowText(LPCTSTR text, int x, int y);

#ifdef SHADOWS
	HRESULT BuildShadowVolumes();
#endif

	// pointer to TheApp
	CTheApp*					m_pTheApp;
	// pointer to current IState
	IState*						m_pState;

	CResourceGame*				m_pResourceGame;
	CInputJoystick*				m_pJoystick;

	CLevel*						m_pLevel;
	CGameSettings*				m_pGameSettings;

	CPlayer*					m_pPlayer;
	CPlayerMinigun*				m_pPlayerMinigunLeft;
	CPlayerMinigun*				m_pPlayerMinigunRight;
	CPlayerController*			m_pPlayerController;

	int							m_iVolumePlayerMinigunShoot;
	int							m_iVolumePlayerMinigunTurn;
	int							m_iVolumePlayerCannon;
	int							m_iVolumePlayerBlast;
	int							m_iVolumePlayerVelocityAfterburn;

	CWeaponPlayerFront*			m_pWeaponPlayerFront;
	CWeaponPlayerDiagonal*		m_pWeaponPlayerDiagonal;
	CWeaponEnemyDrone*			m_pWeaponDrone;
	CWeaponEnemySniper*			m_pWeaponSniper;
	CWeaponEnemyRoller*			m_pWeaponRoller;

	std::vector<CEnemyDrone*>	m_vTemplateEnemyDroneLaunch;
	std::vector<CEnemySniper*>	m_vTemplateEnemySniperLaunch;
	std::vector<CEnemyRoller*>	m_vTemplateEnemyRollerLaunch;
	std::vector<CEnemyGuard*>	m_vTemplateEnemyGuardLaunch;

	CEnemyDrone*				m_pEnemyDroneStrike;
	CEnemySniper*				m_pEnemySniperStrike;
	CEnemyRoller*				m_pEnemyRollerStrike;
	//CEnemyGuard*				m_pEnemyGuardStrike;

	CEnemyBoss1Core*			m_pEnemyBoss1Core;
	CEnemyBoss1Frame*			m_pEnemyBoss1Frame;
	CEnemyBoss1Laser*			m_pEnemyBoss1LaserLeft;
	CEnemyBoss1Laser*			m_pEnemyBoss1LaserRight;
	CEnemyBoss1Scatter*			m_pEnemyBoss1ScatterLeft;
	CEnemyBoss1Scatter*			m_pEnemyBoss1ScatterRight;
	CEnemyBoss1Cannon*			m_pEnemyBoss1Cannon;

	std::vector<CObstacle*>		m_vTemplateAsteroidBig;
	std::vector<CObstacle*>		m_vTemplateAsteroidMedium;
	std::vector<CObstacle*>		m_vTemplateAsteroidSmall;

	CExplosions*				m_pExplosions;

	CQueue<CWeapon*>			m_pBullets;
	CQueue<IEnemy*>*			m_pLaunchEnemies;
	CQueue<IEnemy*>*			m_pStrikeEnemies;
	CQueue<IEnemy*>				m_pActiveEnemies;
	CQueue<IEnemy*>				m_pReinforcements;
	CQueue<IEnemy*>				m_pObstacleEnemies;
	CQueue<CObstacle*>			m_pObstaclesDepth1;
	CQueue<CObstacle*>			m_pObstaclesDepth2;
	CQueue<CObstacle*>			m_pObstaclesDepth3;
	CQueue<CObstacle*>			m_pObstaclesDepth4;
	CQueue<CObstacle*>			m_pObstaclesDepth5;
	//CQueue<CParticleEngine*>	m_pParticles;

	/* SPRITES */

	// backgrounds
	CSprite*					m_pSpriteBackgroundBottom;
	CSpriteScrolling*			m_pSpriteBackgroundMiddle;
	CSpriteScrolling*			m_pSpriteBackgroundTop;
	// level titles
	CSprite*					m_pSpriteLevelTitleSpace;
	// boss warning
	CSprite*					m_pSpriteBossWarningSpace;
	// player afterburn
	CSprite*					m_pSpritePlayerAfterburn;
	// player cannon
	CSprite*					m_pSpriteInfoPlayerCannonChargeSmall;
	CSprite*					m_pSpriteInfoPlayerCannonChargeMedium;
	CSprite*					m_pSpriteInfoPlayerCannonChargeLarge;
	CSprite*					m_pSpriteInfoPlayerCannonBeamCenter;
	CSprite*					m_pSpriteInfoPlayerCannonBeamLeft;
	CSprite*					m_pSpriteInfoPlayerCannonBeamRight;
	// player blast
	CSprite*					m_pSpritePlayerBlast;
	// enemy afterburn
	CSprite*					m_pSpriteEnemyAfterburn;
	// boss sprites
	CSprite*					m_pSpriteBoss1CannonCharge;
	CSprite*					m_pSpriteBoss1CannonShoot;
	// explosions
	CSprite*					m_pSpriteExplosionPlayer;
	CSprite*					m_pSpriteExplosionDrone;
	CSprite*					m_pSpriteExplosionSniper;
	CSprite*					m_pSpriteExplosionRoller;
	CSprite*					m_pSpriteExplosionGuard;
	CSprite*					m_pSpriteExplosionBossBig;
	CSprite*					m_pSpriteExplosionBossPart;
	CSprite*					m_pSpriteExplosionBossChain1;
	CSprite*					m_pSpriteExplosionBossChain2;
	CSprite*					m_pSpriteExplosionBossChain3;
	// game info
	CSprite*					m_pSpriteInfoPlayerLives;
	CSprite*					m_pSpriteInfoPlayerBlasts;
	CSprite*					m_pSpriteInfoPlayerHealth;
	CSprite*					m_pSpriteInfoPlayerCannon;
	// game endings
	CSprite*					m_pSpriteGameOverText;
	CSprite*					m_pSpriteGameWonText;

#ifdef SHADOWS
	// shadows
	CShadowVolume*				m_pShadowVolumes;
#endif

	// 3d meshes
	CXFileContainer*			m_pXFile;
	CDisplayObject*				m_pHudObject;
	CNumber*					m_pNumbersScore;
	CNumber*					m_pNumbersTime;

	ePLAYER_CANNON_STATE		m_ePlayerCannonState;
	ePLAYER_CANNON_CHARGE		m_ePlayerCannonCharge;
	ePLAYER_CANNON_BEAM			m_ePlayerCannonBeam;
	ePLAYER_CANNON_BEAM			m_ePlayerCannonBeamPrevious;

	eEXPLOSION_ENEMY			m_eExplosionEnemy;

	float						m_fDepthFades;
	float						m_fDepthBackgroundBottom;
	float						m_fDepthBackgroundMiddle;
	float						m_fDepthBackgroundTop;

	float						m_fPauseFadeIn;
	float						m_fPauseFadeOut;
	float						m_fPauseFadeInFirst;
	float						m_fPauseFadeOutLast;

	bool						m_bFadeIn;
	bool						m_bFadeOut;
	bool						m_bFadeOutMusic;
	bool						m_bLevelIntro;

	const float					PLAYER_ENTER_AFTERBURN_END_DELTA = 0.65f;
	const float					PLAYER_ENTER_MOVE_DURATION = 1.0f;
	float						m_fPlayerEnterMoveTimer;
	bool						m_bPlayerEnter;

	bool						m_bPlayerMoveAway;
	bool						m_bPlayerAfterburn;
	bool						m_bPlayAfterburnSound;
	
	bool						m_bBossWarning;
	bool						m_bBossDestroyed;

	bool						m_bFleetLaunch;
	bool						m_bFleetStrike;

	bool						m_bEnemyReinforcementSending;

	int							m_iReinforcementsMax;
	int							m_iReinforcementCount;
	int							m_iReinforcementLeft;

	float						m_fEnemyLaunchCounter;
	float						m_fEnemyStrikeCounter;

	float						m_fEnemyReinforcementSendTime;
	float						m_fEnemyReinforcementSendCounter;

	float						m_fEnemyReinforcementCounterDepth2;
	float						m_fEnemyReinforcementCounterDepth3;
	float						m_fEnemyReinforcementCounterDepth4;
	float						m_fEnemyReinforcementCounterDepth5;

	float						m_fEnemyReinforcementRandTimeDepth2;
	float						m_fEnemyReinforcementRandTimeDepth3;
	float						m_fEnemyReinforcementRandTimeDepth4;
	float						m_fEnemyReinforcementRandTimeDepth5;

	int							m_iFleetLaunch;
	int							m_iFleetStrike;

	int							m_iEnemiesLaunch;
	int							m_iEnemiesStrike;
	int							m_iObstaclesPassed;
	int							m_iObstaclesMax;

	int							m_iMaxEnemies;

	int							m_iExplosionMoveSpeed;
	int							m_fExplosionMovePause;

	int							m_iVelocityPixels;
	float						m_fVelocityTimeMargin;

	float						m_fBossWarningStartTimer;
	float						m_fBossWarningEndTimer;
	float						m_fBossWarningTextTimer;
	int							m_iBossWarningTextIndex;
	bool						m_bBossWarningFadeOut;

	float						m_fEndSuccessStartTimer;
	float						m_fEndSuccessTextTimer;
	int							m_iEndSuccessTextIndex;
	
	int							m_iGameState;
	int							m_iGameStatePrevious;
	int							m_iGameStateNext;
	int							m_iGameStateEnd;

	int							m_iExtraLives;

	bool						m_bCheckHighScore;

	bool						m_bCannonDamageBoss;

	// Player cannon variables

	float						m_fCannonChargeTime;
	float						m_fCannonChargeCounter;
	int							m_iCannonChargeTexture;
	int							m_iCannonBeamTexture;

	float						m_fSpriteShowCannonChargeTime;
	float						m_fSpriteShowCannonBeamTime;
	float						m_fSpriteShowCannonChargeCounter;
	float						m_fSpriteShowCannonBeamCounter;

	// minigun turn time value
	float						m_fMinigunRotationTime;

	// minigun firing time value
	float						m_fMinigunFireTime;

	// timers to avoid accidental multiple button presses
	float						m_fBlastButtonTimer;

	// blast active time
	float						m_fBlastActiveTime;
	// counted towards zero
	float						m_fBlastActiveCounter;

	// timer to wait player appearance after destroyed
	float						m_fPlayerEnterTimer;
	// timer for player ship blinking when untouchable
	float						m_fPlayerBlinkTimer;

	float						m_fEnemyExplosionSoundTimer;
	float						m_fGameOverTimer;
	float						m_fGameTime;
	float						m_fDepth;

	float						m_fScreenWidth;
	float						m_fScreenHeight;
	float						m_fScreenPixelWidth;
	float						m_fScreenPixelHeight;	

	int							m_iVolumeSoundEffect;

	bool						m_bFreezeQuit;

	// fades

	DWORD						m_FadeInLevelTime;
	DWORD						m_FadeOutLevelTime;
	DWORD						m_FadeOutQuitTime;

	/* LOADING STEPS */

	bool						m_bInitialized;

	// containers

	bool						m_bLoadContainerNumberScore;
	bool						m_bLoadContainerNumberTime;
	bool						m_bLoadContainerHudObject;

	int							m_iContainerNumberScoreStep;
	int							m_iContainerNumberTimeStep;
	int							m_bContainerHudObjectStep;

	// templates

	bool						m_bLoadTemplateShip;
	bool						m_bLoadTemplateShipCollisionMesh;
	bool						m_bLoadTemplateWeapon;
	bool						m_bLoadTemplateWeaponCollisionMesh;

	int							m_iTemplateShipStep;
	int							m_iTemplateShipCollisionMeshStep;
	int							m_iTemplateWeaponStep;
	int							m_iTemplateWeaponCollisionMeshStep;

	// explosions

	bool						m_bLoadExplosions;

	// level

	int							m_iLoadLevelAsteroidStep;
	int							m_iLoadLevelAsteroidCollisionMeshStep;

	int							m_iLoadLevelStep;

	// keyboard virtual key values

	int							m_iVkeyMinigun;
	int							m_iVkeyFireMode;
	int							m_iVkeyCannon;
	int							m_iVkeyBlast;
};