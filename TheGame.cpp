#include "LerpUtils.h"
#include "TheGame.h"

CTheGame::CTheGame(void)
{
	this->m_pTheApp = NULL;
	this->m_pState = NULL;

	this->m_pResourceGame = NULL;
	this->m_pJoystick = NULL;

	this->m_pLevel = NULL;

	this->m_pGameSettings = NULL;

	this->m_pPlayer = NULL;
	this->m_pPlayerMinigunLeft = NULL;
	this->m_pPlayerMinigunRight = NULL;
	this->m_pPlayerController = NULL;
	this->m_iVolumePlayerMinigunShoot = 0;
	this->m_iVolumePlayerMinigunTurn = 0;
	this->m_iVolumePlayerCannon = 0;
	this->m_iVolumePlayerBlast = 0;
	this->m_iVolumePlayerVelocityAfterburn = 0;

	this->m_pWeaponPlayerFront = NULL;
	this->m_pWeaponPlayerDiagonal = NULL;
	this->m_pWeaponDrone = NULL;
	this->m_pWeaponSniper = NULL;

	this->m_pEnemyDroneStrike = NULL;
	this->m_pEnemySniperStrike = NULL;
	this->m_pEnemyRollerStrike = NULL;
	//this->m_pEnemyGuardStrike = NULL;

	this->m_pEnemyBoss1Core = NULL;
	this->m_pEnemyBoss1Frame = NULL;
	this->m_pEnemyBoss1LaserLeft = NULL;
	this->m_pEnemyBoss1LaserRight = NULL;
	this->m_pEnemyBoss1ScatterLeft = NULL;
	this->m_pEnemyBoss1ScatterRight = NULL;
	this->m_pEnemyBoss1Cannon = NULL;

	this->m_pLaunchEnemies = NULL;
	this->m_pStrikeEnemies = NULL;

	this->m_pSpriteBackgroundBottom = NULL;
	this->m_pSpriteBackgroundMiddle = NULL;
	this->m_pSpriteBackgroundTop = NULL;

	this->m_pSpriteLevelTitleSpace = NULL;
	this->m_pSpriteBossWarningSpace = NULL;

	this->m_pSpritePlayerAfterburn = NULL;
	this->m_pSpriteInfoPlayerCannonChargeSmall = NULL;
	this->m_pSpriteInfoPlayerCannonChargeMedium = NULL;
	this->m_pSpriteInfoPlayerCannonChargeLarge = NULL;
	this->m_pSpriteInfoPlayerCannonBeamCenter = NULL;
	this->m_pSpriteInfoPlayerCannonBeamLeft = NULL;
	this->m_pSpriteInfoPlayerCannonBeamRight = NULL;

	this->m_pSpritePlayerBlast = NULL;

	this->m_pSpriteEnemyAfterburn = NULL;

	this->m_pSpriteBoss1CannonCharge = NULL;
	this->m_pSpriteBoss1CannonShoot = NULL;

	this->m_pSpriteExplosionPlayer = NULL;
	this->m_pSpriteExplosionDrone = NULL;
	this->m_pSpriteExplosionSniper = NULL;
	this->m_pSpriteExplosionRoller = NULL;
	this->m_pSpriteExplosionGuard = NULL;
	this->m_pSpriteExplosionBossBig = NULL;
	this->m_pSpriteExplosionBossPart = NULL;
	this->m_pSpriteExplosionBossChain1 = NULL;
	this->m_pSpriteExplosionBossChain2 = NULL;
	this->m_pSpriteExplosionBossChain3 = NULL;

	this->m_pSpriteInfoPlayerLives = NULL;
	this->m_pSpriteInfoPlayerBlasts = NULL;
	this->m_pSpriteInfoPlayerHealth = NULL;
	this->m_pSpriteInfoPlayerCannon = NULL;

	this->m_pSpriteGameOverText = NULL;
	this->m_pSpriteGameWonText = NULL;

#ifdef SHADOWS
	this->m_pShadowVolumes = NULL;
#endif

	this->m_pXFile = NULL;
	this->m_pHudObject = NULL;
	this->m_pNumbersScore = NULL;
	this->m_pNumbersTime = NULL;

	this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_READY;
	this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_SMALL;
	this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_CENTER;
	this->m_ePlayerCannonBeamPrevious = ePLAYER_CANNON_BEAM_RIGHT;

	this->m_fDepthFades = 0.0f;
	this->m_fDepthBackgroundBottom = 1.0f;
	this->m_fDepthBackgroundMiddle = 0.99f;
	this->m_fDepthBackgroundTop = 0.98f;

	this->m_fPauseFadeIn = 0.017f;
	this->m_fPauseFadeOut = 0.02f;
	this->m_fPauseFadeInFirst = 0.1f;
	this->m_fPauseFadeOutLast = 0.08f;

	this->m_bFadeIn = false;
	this->m_bFadeOut = false;
	this->m_bFadeOutMusic = true;
	this->m_bLevelIntro = false;
	this->m_bPlayerEnter = false;
	this->m_bPlayerMoveAway = false;
	this->m_bPlayerAfterburn = false;
	this->m_bPlayAfterburnSound = false;

	this->m_bBossWarning = false;
	this->m_bBossDestroyed = false;

	this->m_bFleetLaunch = false;
	this->m_bFleetStrike = false;

	this->m_bEnemyReinforcementSending = false;

	this->m_fEnemyLaunchCounter = 0.0f;
	this->m_fEnemyStrikeCounter = 0.0f;

	this->m_fEnemyReinforcementSendTime = 0.0f;
	this->m_fEnemyReinforcementSendCounter = 0.0f;

	this->m_fEnemyReinforcementCounterDepth2 = 0.0f;
	this->m_fEnemyReinforcementCounterDepth3 = 0.0f;
	this->m_fEnemyReinforcementCounterDepth4 = 0.0f;
	this->m_fEnemyReinforcementCounterDepth5 = 0.0f;

	this->m_fEnemyReinforcementRandTimeDepth2 = 0.0f;
	this->m_fEnemyReinforcementRandTimeDepth3 = 0.0f;
	this->m_fEnemyReinforcementRandTimeDepth4 = 0.0f;
	this->m_fEnemyReinforcementRandTimeDepth5 = 0.0f;

	this->m_iFleetLaunch = 0;
	this->m_iFleetStrike = 0;

	this->m_iEnemiesLaunch = 0;
	this->m_iEnemiesStrike = 0;
	this->m_iObstaclesPassed = 0;

	this->m_iMaxEnemies = 0;

	this->m_iExplosionMoveSpeed = 0;
	this->m_fExplosionMovePause = 0;

	this->m_iVelocityPixels = 0;
	this->m_fVelocityTimeMargin = 0.0f;

	this->m_fBossWarningStartTimer = 0.0f;
	this->m_fBossWarningEndTimer = 0.0f;
	this->m_fBossWarningTextTimer = 0.0f;
	this->m_iBossWarningTextIndex = 0;
	this->m_bBossWarningFadeOut = false;

	this->m_fEndSuccessStartTimer = 2.0f;
	this->m_fEndSuccessTextTimer = 0.1f;
	this->m_iEndSuccessTextIndex = 0;

	this->m_iExtraLives = 0;

	this->m_bCheckHighScore = false;

	this->m_bCannonDamageBoss = true;

	this->m_fCannonChargeTime = 0.71f;
	this->m_fCannonChargeCounter = this->m_fCannonChargeTime;
	this->m_iCannonChargeTexture = 1;
	this->m_iCannonBeamTexture = 1;

	this->m_fSpriteShowCannonChargeTime = 0.005f;
	this->m_fSpriteShowCannonBeamTime = 0.04f;
	this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;
	this->m_fSpriteShowCannonBeamCounter = this->m_fSpriteShowCannonBeamTime;

	this->m_fMinigunRotationTime = 0.0f;
	this->m_fMinigunFireTime = 0.0f;
	this->m_fBlastButtonTimer = 0.0f;

	this->m_fBlastActiveTime = (float)TIME_PLAYER_BLAST;
	this->m_fBlastActiveCounter = this->m_fBlastActiveTime;
	
	this->m_fPlayerEnterTimer = 0.0f;
	this->m_fPlayerBlinkTimer = 0.0f;

	this->m_fEnemyExplosionSoundTimer = 0.0f;

	this->m_fGameOverTimer = 1.5f;
	this->m_fDepth = 50.0f;
	this->m_fGameTime = 0.0f;
	this->m_iVolumeSoundEffect = 0;

	this->m_bFreezeQuit = false;

	this->m_FadeInLevelTime = 0x04000000;
	this->m_FadeOutLevelTime = 0x04000000;
	this->m_FadeOutQuitTime = 0x03000000;

	this->m_bInitialized = false;

	this->m_bLoadContainerNumberScore = true;
	this->m_bLoadContainerNumberTime = true;
	this->m_bLoadContainerHudObject = true;

	this->m_iContainerNumberScoreStep = 0;
	this->m_iContainerNumberTimeStep = 0;
	this->m_bContainerHudObjectStep = 0;

	this->m_bLoadTemplateShip = true;
	this->m_bLoadTemplateShipCollisionMesh = true;
	this->m_bLoadTemplateWeapon = true;
	this->m_bLoadTemplateWeaponCollisionMesh = true;

	this->m_iTemplateShipStep = 0;
	this->m_iTemplateShipCollisionMeshStep = 0;
	this->m_iTemplateWeaponStep = 0;
	this->m_iTemplateWeaponCollisionMeshStep = 0;

	this->m_bLoadExplosions = true;

	this->m_iGameState = -1;
	this->m_iGameStatePrevious = -1;
	this->m_iGameStateEnd = 0;

	SwitchGameState(GAME_STATE_INIT_LEVEL);
}

CTheGame::~CTheGame(void)
{
}

HRESULT CTheGame::Create(	CTheApp* pTheApp,
							IState* pState,
							DWORD dwState)
{
	if(!this->m_bInitialized)
	{
		this->m_fScreenWidth = pState->GetScreenWidth();
		this->m_fScreenHeight = pState->GetScreenHeight();
		this->m_fScreenPixelWidth = pState->GetScreenPixelWidth();
		this->m_fScreenPixelHeight = pState->GetScreenPixelHeight();

		this->m_pTheApp = pTheApp;
		this->m_pState = pState;

		this->m_pResourceGame = this->m_pTheApp->GetResourceGame();
		this->m_pJoystick = this->m_pTheApp->GetJoystick();

		/** SETTINGS **/

		this->m_pGameSettings = new CGameSettings();

		if( !this->m_pGameSettings )
		{
			return E_OUTOFMEMORY;
		}

		this->m_pGameSettings->Create();

		// initialize sound effect volume
		this->InitVolumeSoundEffect();

		/** LEVELS **/

		this->m_pLevel = new CLevel();
		if( !this->m_pLevel )
		{
			return E_OUTOFMEMORY;
		}

		this->m_pLevel->Create(this->m_pTheApp);

		/** DYNAMIC LIGHTING **/
		this->m_pState->GetLights()->InitGamePlayerBlastHigh();
		this->m_pState->GetLights()->InitGamePlayerBlastLow();

		this->m_bInitialized = true;
		this->m_pState->UpdateLoadingBar(1);

		return S_OK;
	}

	/** LOAD RESOURCES TO MEMORY **/

	if (this->m_pState->IsLoadWaitTimer())
	{
		return S_OK;
	}

	HRESULT hres = S_OK;

	if(!this->m_pResourceGame->IsResourcesLoaded())
	{
		// Load all the resources from files (meshes, sprites).
		while (!this->m_pResourceGame->IsResourcesLoaded())
		{
			hres = this->m_pResourceGame->Load();

			if (hres != S_OK)
			{
				return hres;
			}

			if (this->m_pResourceGame->IsMasterZipFileLoaded())
			{
				this->m_pState->UpdateLoadingBar(20);
			}
			else
			{
				this->m_pState->UpdateLoadingBar(1);
			}

			if (this->m_pResourceGame->IsLoadWaitCycle())
			{
				this->m_pResourceGame->SetLoadWaitCycle(false);
				this->m_pState->SetLoadWaitTimer();
				return hres;
			}
		}

		return S_OK;
	}

	if(!this->m_pState->GetMeshLoaded())
	{
		while(this->m_pState->GetMeshSteps() <= this->m_pState->GetMeshStepsMax())
		{
			hres = this->LoadMeshes();

			if (hres != S_OK)
			{
				return hres;
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_pState->IncreaseMeshSteps(1);
		}

		this->m_pState->SetMeshLoaded(true);
		this->m_pState->SetLoadWaitTimer();
		return S_OK;
	}

	if( !this->m_pState->GetSpriteLoaded() )
	{
		while(this->m_pState->GetSpriteSteps() <= this->m_pState->GetSpriteStepsMax())
		{
			this->LoadSprites();
			this->m_pState->UpdateLoadingBar(1);
			this->m_pState->IncreaseSpriteSteps(1);
		}

		this->m_pState->SetSpriteLoaded(true);
		this->m_pState->SetLoadWaitTimer();
		return S_OK;
	}

	// container for score number meshes
	if(this->m_bLoadContainerNumberScore)
	{
		if(this->m_pNumbersScore == NULL)
		{
			this->m_pNumbersScore = new CNumber[LOAD_CONTAINER_NUMBER_MAX];

			if( !this->m_pNumbersScore )
			{
				return E_OUTOFMEMORY;
			}
		}

		while (this->m_iContainerNumberScoreStep < LOAD_CONTAINER_NUMBER_MAX)
		{
			hres = (this->m_pNumbersScore + this->m_iContainerNumberScoreStep)->Create(
				this->m_pXFile[LOAD_MESH_GAME_0 + this->m_iContainerNumberScoreStep].GetMesh(),
				this->m_pXFile[LOAD_MESH_GAME_0 + this->m_iContainerNumberScoreStep],
				this->m_pGameSettings->m_fGameNumberWidth,
				this->m_pGameSettings->m_fGameNumberHeight,
				true,
				CNumber::eNUMBER_TYPE_GAME);

			if (hres != S_OK)
			{
				return hres;
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_iContainerNumberScoreStep++;
		}

		this->m_bLoadContainerNumberScore = false;
		return S_OK;
	}

	// container for time number meshes
	if(this->m_bLoadContainerNumberTime)
	{
		if(this->m_pNumbersTime == NULL)
		{
			this->m_pNumbersTime = new CNumber[LOAD_CONTAINER_NUMBER_MAX];

			if( !this->m_pNumbersTime )
			{
				return E_OUTOFMEMORY;
			}
		}

		while (this->m_iContainerNumberTimeStep < LOAD_CONTAINER_NUMBER_MAX)
		{
			hres = (this->m_pNumbersTime + this->m_iContainerNumberTimeStep)->Create(
				this->m_pXFile[LOAD_MESH_GAME_0 + this->m_iContainerNumberTimeStep].GetMesh(),
				this->m_pXFile[LOAD_MESH_GAME_0 + this->m_iContainerNumberTimeStep],
				this->m_pGameSettings->m_fGameNumberWidth,
				this->m_pGameSettings->m_fGameNumberHeight,
				true,
				CNumber::eNUMBER_TYPE_GAME);

			if (hres != S_OK)
			{
				return hres;
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_iContainerNumberTimeStep++;
		}

		this->m_bLoadContainerNumberTime = false;
		return S_OK;
	}

	// container for HUD meshes
	if(this->m_bLoadContainerHudObject)
	{
		if(this->m_pHudObject == NULL)
		{
			this->m_pHudObject = new CDisplayObject[LOAD_CONTAINER_HUD_MAX];
			if( !this->m_pHudObject )
			{
				return E_OUTOFMEMORY;
			}
		}

		while (this->m_bContainerHudObjectStep < LOAD_CONTAINER_HUD_MAX)
		{
			switch (this->m_bContainerHudObjectStep)
			{
			case LOAD_CONTAINER_HUD_SCORE_TEXT:

				hres = (this->m_pHudObject + this->m_bContainerHudObjectStep)->Create(
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_TEXT_SCORE),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_TEXT_SCORE),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_TEXT_SCORE));
				break;
			}

			if (hres != S_OK)
			{
				return hres;
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_bContainerHudObjectStep++;
		}

		this->m_bLoadContainerHudObject = false;
		return S_OK;
	}

	/** SHIP TEMPLATES **/

	if(this->m_bLoadTemplateShip)
	{
		while (this->m_iTemplateShipStep < LOAD_TEMPLATE_SHIP_MAX)
		{
			switch (this->m_iTemplateShipStep)
			{
			case LOAD_TEMPLATE_SHIP_PLAYER:

				// SHIP

				this->m_pPlayer = new CPlayer();

				if (!this->m_pPlayer)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pPlayer->Create(this->m_pTheApp,
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_PLAYER_FRAME),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_PLAYER_FRAME),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_PLAYER_FRAME),
					this->m_pSpritePlayerBlast,
					this->m_pGameSettings->m_fPlayerWidth,
					this->m_pGameSettings->m_fPlayerHeight,
					this->m_pGameSettings->m_fPlayerSpeed,
					this->m_pGameSettings->m_fPlayerMaxVelocity,
					this->m_pGameSettings->m_iPlayerHealth,
					this->m_pGameSettings->m_iPlayerCannonEnergyMax,
					this->m_pGameSettings->m_iPlayerBlastDamage,
					this->m_pGameSettings->m_iPlayerBlasts);

				if (FAILED(hres))
				{
					return hres;
				}

				// set player's lives count
				this->m_pPlayer->SetLives(this->m_pGameSettings->m_iPlayerLives);

				this->m_pPlayer->SetObjectDepth(0.0f);

				// MINIGUNS

				// create left minigun object
				this->m_pPlayerMinigunLeft = new CPlayerMinigun();

				if (!this->m_pPlayerMinigunLeft)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pPlayerMinigunLeft->Create(this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_PLAYER_MINIGUN),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_PLAYER_MINIGUN),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_PLAYER_MINIGUN),
					CPlayerMinigun::eSIDE_LEFT);

				if (FAILED(hres))
				{
					return hres;
				}

				// create right minigun object
				this->m_pPlayerMinigunRight = new CPlayerMinigun();

				if (!this->m_pPlayerMinigunRight)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pPlayerMinigunRight->Create(this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_PLAYER_MINIGUN),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_PLAYER_MINIGUN),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_PLAYER_MINIGUN),
					CPlayerMinigun::eSIDE_RIGHT);

				if (FAILED(hres))
				{
					return hres;
				}

				// add miniguns to core object
				this->m_pPlayer->AddChild(this->m_pPlayerMinigunRight);
				this->m_pPlayer->AddChild(this->m_pPlayerMinigunLeft);

				// PLAYER CONTROLLER

				this->m_pPlayerController = new CPlayerController(this->m_pTheApp,
					this->m_pTheApp->GetJoystick(),
					this->m_fScreenWidth,
					this->m_fScreenHeight,
					this->m_pGameSettings->m_fPlayerWidth,
					this->m_pGameSettings->m_fPlayerHeight,
					this->m_pGameSettings->m_fPlayerSpeed);

				if (!this->m_pPlayerController)
				{
					return E_OUTOFMEMORY;
				}

				this->m_pPlayerController->Create(this->m_pPlayer);

				// player ship control keys
				this->m_pTheApp->GetConfig().SetVkeys();

				break;

			case LOAD_TEMPLATE_SHIP_LAUNCH_DRONE:
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ENEMY_DRONE_1;
					IEnemy::eENEMY_DEPTH eDepth = IEnemy::eENEMY_DEPTH_1;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ENEMY_DRONE_2;
						eDepth = IEnemy::eENEMY_DEPTH_2;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ENEMY_DRONE_3;
						eDepth = IEnemy::eENEMY_DEPTH_3;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ENEMY_DRONE_4;
						eDepth = IEnemy::eENEMY_DEPTH_4;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ENEMY_DRONE_5;
						eDepth = IEnemy::eENEMY_DEPTH_5;
						break;
					}

					CEnemyDrone* templateObject = new CEnemyDrone(
						IEnemy::eTYPE_DRONE,
						IEnemy::eBEHAVIOUR_LAUNCH);

					if (!templateObject)
					{
						return E_OUTOFMEMORY;
					}

					templateObject->SetDepth(eDepth);

					hres = templateObject->Create(
						this->m_pTheApp, this->m_pGameSettings,
						this->m_pResourceGame->GetMesh(mapKey),
						this->m_pResourceGame->GetMaterial(mapKey),
						this->m_pResourceGame->GetTexture(mapKey),
						this->m_pSpriteEnemyAfterburn,
						this->m_iVolumeSoundEffect);

					if (FAILED(hres))
					{
						return hres;
					}

					m_vTemplateEnemyDroneLaunch.push_back(templateObject);
				}
			}
				break;

			case LOAD_TEMPLATE_SHIP_LAUNCH_SNIPER:
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ENEMY_SNIPER_1;
					IEnemy::eENEMY_DEPTH eDepth = IEnemy::eENEMY_DEPTH_1;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ENEMY_SNIPER_2;
						eDepth = IEnemy::eENEMY_DEPTH_2;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ENEMY_SNIPER_3;
						eDepth = IEnemy::eENEMY_DEPTH_3;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ENEMY_SNIPER_4;
						eDepth = IEnemy::eENEMY_DEPTH_4;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ENEMY_SNIPER_5;
						eDepth = IEnemy::eENEMY_DEPTH_5;
						break;
					}

					CEnemySniper* templateObject = new CEnemySniper(
						IEnemy::eTYPE_SNIPER,
						IEnemy::eBEHAVIOUR_LAUNCH);

					if (!templateObject)
					{
						return E_OUTOFMEMORY;
					}

					templateObject->SetDepth(eDepth);

					hres = templateObject->Create(
						this->m_pTheApp, this->m_pGameSettings,
						this->m_pResourceGame->GetMesh(mapKey),
						this->m_pResourceGame->GetMaterial(mapKey),
						this->m_pResourceGame->GetTexture(mapKey),
						this->m_pSpriteEnemyAfterburn,
						this->m_iVolumeSoundEffect);

					if (FAILED(hres))
					{
						return hres;
					}

					m_vTemplateEnemySniperLaunch.push_back(templateObject);
				}
			}
				break;

			case LOAD_TEMPLATE_SHIP_LAUNCH_ROLLER:
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ENEMY_ROLLER_1;
					IEnemy::eENEMY_DEPTH eDepth = IEnemy::eENEMY_DEPTH_1;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ENEMY_ROLLER_2;
						eDepth = IEnemy::eENEMY_DEPTH_2;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ENEMY_ROLLER_3;
						eDepth = IEnemy::eENEMY_DEPTH_3;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ENEMY_ROLLER_4;
						eDepth = IEnemy::eENEMY_DEPTH_4;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ENEMY_ROLLER_5;
						eDepth = IEnemy::eENEMY_DEPTH_5;
						break;
					}

					CEnemyRoller* templateObject = new CEnemyRoller(
						IEnemy::eTYPE_ROLLER,
						IEnemy::eBEHAVIOUR_LAUNCH);

					if (!templateObject)
					{
						return E_OUTOFMEMORY;
					}

					templateObject->SetDepth(eDepth);

					hres = templateObject->Create(
						this->m_pTheApp, this->m_pGameSettings,
						this->m_pResourceGame->GetMesh(mapKey),
						this->m_pResourceGame->GetMaterial(mapKey),
						this->m_pResourceGame->GetTexture(mapKey),
						this->m_pSpriteEnemyAfterburn,
						this->m_iVolumeSoundEffect);

					if (FAILED(hres))
					{
						return hres;
					}

					m_vTemplateEnemyRollerLaunch.push_back(templateObject);
				}
			}
				break;

			case LOAD_TEMPLATE_SHIP_LAUNCH_VANGUARD:
			{
				/*
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ENEMY_VANGUARD_1;
					IEnemy::eENEMY_DEPTH eDepth = IEnemy::eENEMY_DEPTH_1;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ENEMY_VANGUARD_2;
						eDepth = IEnemy::eENEMY_DEPTH_2;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ENEMY_VANGUARD_3;
						eDepth = IEnemy::eENEMY_DEPTH_3;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ENEMY_VANGUARD_4;
						eDepth = IEnemy::eENEMY_DEPTH_4;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ENEMY_VANGUARD_5;
						eDepth = IEnemy::eENEMY_DEPTH_5;
						break;
					}

					CEnemyGuard* templateObject = new CEnemyGuard(
						IEnemy::eTYPE_GUARD,
						IEnemy::eBEHAVIOUR_LAUNCH);

					if (!templateObject)
					{
						return E_OUTOFMEMORY;
					}

					templateObject->SetDepth(eDepth);

					hres = templateObject->Create(
						this->m_pTheApp, this->m_pGameSettings,
						this->m_pResourceGame->GetMesh(mapKey),
						this->m_pResourceGame->GetMaterial(mapKey),
						this->m_pResourceGame->GetTexture(mapKey),
						this->m_pSpriteEnemyAfterburn,
						this->m_iVolumeSoundEffect);

					if (FAILED(hres))
					{
						return hres;
					}

					m_vTemplateEnemyGuardLaunch.push_back(templateObject);
				}
				*/
			}
				break;

			case LOAD_TEMPLATE_SHIP_STRIKE_DRONE:

				this->m_pEnemyDroneStrike = new CEnemyDrone(
					IEnemy::eTYPE_DRONE,
					IEnemy::eBEHAVIOUR_STRIKE);

				if (!this->m_pEnemyDroneStrike)
				{
					return E_OUTOFMEMORY;
				}

				this->m_pEnemyDroneStrike->SetDepth(IEnemy::eENEMY_DEPTH_1);

				hres = this->m_pEnemyDroneStrike->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_ENEMY_DRONE_1),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_ENEMY_DRONE_1),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_ENEMY_DRONE_1),
					this->m_pSpriteEnemyAfterburn,
					this->m_iVolumeSoundEffect);

				if (FAILED(hres))
				{
					return hres;
				}

				break;

			case LOAD_TEMPLATE_SHIP_STRIKE_SNIPER:

				this->m_pEnemySniperStrike = new CEnemySniper(
					IEnemy::eTYPE_SNIPER,
					IEnemy::eBEHAVIOUR_STRIKE);

				if (!this->m_pEnemySniperStrike)
				{
					return E_OUTOFMEMORY;
				}

				this->m_pEnemySniperStrike->SetDepth(IEnemy::eENEMY_DEPTH_1);

				hres = this->m_pEnemySniperStrike->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_ENEMY_SNIPER_1),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_ENEMY_SNIPER_1),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_ENEMY_SNIPER_1),
					this->m_pSpriteEnemyAfterburn,
					this->m_iVolumeSoundEffect);

				if (FAILED(hres))
				{
					return hres;
				}

				break;

			case LOAD_TEMPLATE_SHIP_STRIKE_ROLLER:

				this->m_pEnemyRollerStrike = new CEnemyRoller(
					IEnemy::eTYPE_ROLLER,
					IEnemy::eBEHAVIOUR_STRIKE);

				if (!this->m_pEnemyRollerStrike)
				{
					return E_OUTOFMEMORY;
				}

				this->m_pEnemyRollerStrike->SetDepth(IEnemy::eENEMY_DEPTH_1);

				hres = this->m_pEnemyRollerStrike->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_ENEMY_ROLLER_1),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_ENEMY_ROLLER_1),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_ENEMY_ROLLER_1),
					this->m_pSpriteEnemyAfterburn,
					this->m_iVolumeSoundEffect);

				if (FAILED(hres))
				{
					return hres;
				}

				break;

			case LOAD_TEMPLATE_SHIP_STRIKE_VANGUARD:

				/*
				this->m_pEnemyGuardStrike = new CEnemyGuard(
					IEnemy::eTYPE_GUARD,
					IEnemy::eBEHAVIOUR_STRIKE);

				if (!this->m_pEnemyGuardStrike)
				{
					return E_OUTOFMEMORY;
				}

				this->m_pEnemyGuardStrike->SetDepth(IEnemy::eDEPTH_1);

				hres = this->m_pEnemyGuardStrike->Create(this->m_pTheApp,
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_ENEMY_VANGUARD_1),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_ENEMY_VANGUARD_1),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_ENEMY_VANGUARD_1),
					this->m_pSpriteEnemyAfterburn,
					this->m_iVolumeSoundEffect);

				if (FAILED(hres))
				{
					return hres;
				}
				*/

				break;
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_iTemplateShipStep++;
		}

		m_bLoadTemplateShip = false;
		return S_OK;
	}

	if(this->m_bLoadTemplateShipCollisionMesh)
	{
		while (this->m_iTemplateShipCollisionMeshStep < LOAD_TEMPLATE_SHIP_COLLISION_MESH_MAX)
		{
			if (this->m_iTemplateShipCollisionMeshStep == LOAD_TEMPLATE_SHIP_COLLISION_MESH_PLAYER)
			{
				hres = this->m_pPlayer->CreateCollisionMesh();

				if (FAILED(hres))
				{
					return hres;
				}
			}
			else
			{
				hres = this->CreateCollisionMeshEnemies();

				if (FAILED(hres))
				{
					return hres;
				}
			}

			this->m_pState->UpdateLoadingBar(1);
			this->m_iTemplateShipCollisionMeshStep++;
		}

		this->m_bLoadTemplateShipCollisionMesh = false;
		return S_OK;
	}

	/** BULLET TEMPLATES **/

	if(this->m_bLoadTemplateWeapon)
	{
		while (this->m_iTemplateWeaponStep < LOAD_TEMPLATE_WEAPON_MAX)
		{
			switch (this->m_iTemplateWeaponStep)
			{
			case LOAD_TEMPLATE_WEAPON_ARRAYS:

				if (CWeapon::s_SpritesGame.size() == 0)
				{
					for (int i = CResources::SPRITE_GAME_BULLET_FIRST; i <= CResources::SPRITE_GAME_BULLET_LAST; i++)
					{
						CWeapon::s_SpritesGame.push_back(this->m_pResourceGame->GetSprite(i));
					}
				}

				break;

			case LOAD_TEMPLATE_WEAPON_PLAYER:

				// Player minigun (front)

				this->m_pWeaponPlayerFront = new CWeaponPlayerFront();

				if (!this->m_pWeaponPlayerFront)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pWeaponPlayerFront->Create(this->m_pTheApp->GetDevice(),
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pGameSettings->m_fPlayerBulletMinigunWidth,
					this->m_pGameSettings->m_fPlayerBulletMinigunHeight,
					this->m_pPlayer->GetMinigunSpeed(),
					this->m_pPlayer->GetMinigunDamage(),
					CWeapon::eBULLET_TYPE_PLAYER_FRONT);

				if (FAILED(hres))
				{
					return hres;
				}

				this->m_pWeaponPlayerFront->SetVisible(false);

				// Player minigun (diagonal)

				this->m_pWeaponPlayerDiagonal = new CWeaponPlayerDiagonal();

				if (!this->m_pWeaponPlayerDiagonal)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pWeaponPlayerDiagonal->Create(this->m_pTheApp->GetDevice(),
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
					this->m_pGameSettings->m_fPlayerBulletMinigunWidth,
					this->m_pGameSettings->m_fPlayerBulletMinigunHeight,
					this->m_pPlayer->GetMinigunSpeed(),
					this->m_pPlayer->GetMinigunDamage(),
					CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL);

				if (FAILED(hres))
				{
					return hres;
				}

				this->m_pWeaponPlayerDiagonal->SetVisible(false);

				break;

			case LOAD_TEMPLATE_WEAPON_DRONE:

				this->m_pWeaponDrone = new CWeaponEnemyDrone();

				if (!this->m_pWeaponDrone)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pWeaponDrone->Create(this->m_pTheApp->GetDevice(),
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_DRONE),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_DRONE),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_DRONE),
					this->m_pGameSettings->m_fEnemyDroneBulletWidth,
					this->m_pGameSettings->m_fEnemyDroneBulletHeight,
					this->m_pGameSettings->m_fEnemyDroneBulletSpeed,
					this->m_pGameSettings->m_iEnemyDroneBulletDamage,
					CWeapon::eBULLET_TYPE_ENEMY_DRONE);

				if (FAILED(hres))
				{
					return hres;
				}

				this->m_pWeaponDrone->SetOwner(CWeapon::eOWNER_ENEMY);
				this->m_pWeaponDrone->SetVisible(false);

				break;

			case LOAD_TEMPLATE_WEAPON_SNIPER:

				this->m_pWeaponSniper = new CWeaponEnemySniper();

				if (!this->m_pWeaponSniper)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pWeaponSniper->Create(this->m_pTheApp->GetDevice(),
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_SNIPER),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_SNIPER),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_SNIPER),
					this->m_pGameSettings->m_fEnemySniperBulletWidth,
					this->m_pGameSettings->m_fEnemySniperBulletHeight,
					this->m_pGameSettings->m_fEnemySniperBulletSpeed,
					this->m_pGameSettings->m_iEnemySniperBulletDamage,
					CWeapon::eBULLET_TYPE_ENEMY_SNIPER);

				if (FAILED(hres))
				{
					return hres;
				}

				this->m_pWeaponSniper->SetOwner(CWeapon::eOWNER_ENEMY);
				this->m_pWeaponSniper->SetVisible(false);

				break;

			case LOAD_TEMPLATE_WEAPON_ROLLER:

				this->m_pWeaponRoller = new CWeaponEnemyRoller();

				if (!this->m_pWeaponRoller)
				{
					return E_OUTOFMEMORY;
				}

				hres = this->m_pWeaponRoller->Create(this->m_pTheApp->GetDevice(),
					this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_ROLLER),
					this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_ROLLER),
					this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_ROLLER),
					this->m_pGameSettings->m_fEnemyRollerBulletWidth,
					this->m_pGameSettings->m_fEnemyRollerBulletHeight,
					this->m_pGameSettings->m_fEnemyRollerBulletSpeed,
					this->m_pGameSettings->m_iEnemyRollerBulletDamage,
					CWeapon::eBULLET_TYPE_ENEMY_ROLLER);

				if (FAILED(hres))
				{
					return hres;
				}

				this->m_pWeaponRoller->SetOwner(CWeapon::eOWNER_ENEMY);
				this->m_pWeaponRoller->SetVisible(false);

				break;
			}

			this->m_iTemplateWeaponStep++;
			this->m_pState->UpdateLoadingBar(1);
		}

		this->m_bLoadTemplateWeapon = false;
		return S_OK;
	}

	if(this->m_bLoadTemplateWeaponCollisionMesh)
	{
		while (this->m_iTemplateWeaponCollisionMeshStep < LOAD_TEMPLATE_WEAPON_COLLISION_MESH_MAX)
		{
			hres = this->CreateCollisionMeshWeapons();

			if (FAILED(hres))
			{
				return hres;
			}

			this->m_iTemplateWeaponCollisionMeshStep++;
			this->m_pState->UpdateLoadingBar(1);
		}

		this->m_bLoadTemplateWeaponCollisionMesh = false;
		return S_OK;
	}

	/** EXPLOSION TEMPLATES **/

	if(this->m_bLoadExplosions)
	{
		m_pExplosions = new CExplosions();

		hres = m_pExplosions->Create(this->m_pTheApp,
									this->m_pSpriteExplosionPlayer,
									this->m_pSpriteExplosionDrone,
									this->m_pSpriteExplosionSniper,
									this->m_pSpriteExplosionRoller,
									this->m_pSpriteExplosionBossBig,
									this->m_pSpriteExplosionBossPart,
									this->m_pSpriteExplosionBossChain1,
									this->m_pSpriteExplosionBossChain2,
									this->m_pSpriteExplosionBossChain3,
									//this->m_pSpriteExplosionGuard,
									RESOURCES_SPRITE_GAME_EXPLOSION_PLAYER,
									RESOURCES_SPRITE_GAME_EXPLOSION_DRONE,
									RESOURCES_SPRITE_GAME_EXPLOSION_SNIPER,
									RESOURCES_SPRITE_GAME_EXPLOSION_ROLLER,
									RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_BIG,
									RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_PART,
									RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_1,
									RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_2,
									RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_3,
									//RESOURCES_SPRITE_GAME_EXPLOSION_GUARD,
									this->m_fScreenWidth, 
									this->m_fScreenHeight);

		this->m_pState->UpdateLoadingBar(1);
		this->m_bLoadExplosions = false;
		return hres;
	}

	// Load sound files
	if (this->m_pTheApp->IsLoadGameSoundFiles())
	{
		CZipManager* zipManager = this->m_pTheApp->GetZipManager();

		// Unpack "game sounds" ZIP resource file.
		if (!zipManager->IsExistResourceFile("music/level_1.mp3"))
		{
			zipManager->UnpackMasterZipFileWithTarget("data_2", "data5");
			zipManager->UnpackChildZipFile("data5");
		}

		this->m_pTheApp->SetLoadGameSoundFiles(false);

		if (FAILED(hres))
		{
			return hres;
		}

		this->m_pState->UpdateLoadingBar(1);
		this->m_pState->SetLoadWaitTimer();
		return hres;
	}

	this->m_pState->SetStateLoaded(true);
	//this->m_pTheApp->SetLoadingScreen(false);

	return S_OK;
}

void CTheGame::Render(void)
{
	const float fFrametime = this->m_pTheApp->GetFrameTime();

	static bool bLevelTitleIn = true;
	static bool bLevelTitleStay = false;
	static bool bLevelTitleOut = false;

	static int iCountBossChainExplosions = 0;
	static float fPauseBossChainExplosion = 0.0f;
	static float fPauseBossPartExplosion = 0.0f;
	static float fPauseBossBigExplosion = 0.0f;
	static int iSoundBossChainExplosion = 1;

	static float fTimerLevelTitle = (float)TIMER_LEVEL_TITLE;

	static bool bBackgroundSpeedChange;

	static float fBackgroundSpeedChangePause = 0.0f;
	static bool bBackgroundSpeedChangeReinforcements = true;
	static bool bBackgroundSpeedChangeObstacles = true;
	static bool bBackgroundSpeedChangeAfterburn;

	// these local static variables are used in game outro state
	static float fPauseOutroMinigunsRotation = 1.0f;

	/* INIT AND LOAD LEVEL */

	if(this->m_iGameState == GAME_STATE_INIT_LEVEL)
	{
		this->m_pLevel->ReadLevel();

		this->m_iLoadLevelAsteroidStep = 0;
		this->m_iLoadLevelAsteroidCollisionMeshStep = 0;
		this->m_iLoadLevelStep = 0;

		SwitchGameState(GAME_STATE_LOAD_LEVEL);

		return;
	}
	else if(this->m_iGameState == GAME_STATE_LOAD_LEVEL)
	{
		bool increaseStep = true;

		switch(this->m_iLoadLevelStep)
		{
		case LOAD_LEVEL_DEFAULT_VALUES:

			bLevelTitleIn = true;
			bLevelTitleStay = false;
			bLevelTitleOut = false;

			iCountBossChainExplosions = 0;
			fPauseBossChainExplosion = 0.0f;
			fPauseBossPartExplosion = 0.0f;
			fPauseBossBigExplosion = 0.0f;
			iSoundBossChainExplosion = 1;

			fTimerLevelTitle = (float)TIMER_LEVEL_TITLE;

			fBackgroundSpeedChangePause = 0.0f;
			bBackgroundSpeedChangeReinforcements = true;
			bBackgroundSpeedChangeObstacles = true;

			fPauseOutroMinigunsRotation = 1.0f;

			this->m_bFadeIn = true;
			this->m_bFadeOut = true;

			break;

		case LOAD_LEVEL_DYNAMIC_LIGHT:

			this->m_pState->GetLights()->InitGameMain(this->m_pLevel->GetLevelNumber());
			this->m_pState->GetLights()->SetGameMain(true);

			break;

		case LOAD_LEVEL_RESET_ENEMY_VALUES_1:

			this->m_iFleetLaunch = 0;
			this->m_iFleetStrike = 0;
			this->m_bFleetLaunch = false;
			this->m_bFleetStrike = false;
			this->m_bEnemyReinforcementSending = false;

			this->m_iReinforcementsMax = 0;
			this->m_iReinforcementCount = 0;
			this->m_iReinforcementLeft = 0;

			this->m_fEnemyReinforcementSendTime = this->m_pLevel->GetRandReinforcementAppearTime();
			this->m_fEnemyReinforcementSendCounter = 0.0f;

			this->m_fEnemyReinforcementCounterDepth2 = 0.0f;
			this->m_fEnemyReinforcementCounterDepth3 = 0.0f;
			this->m_fEnemyReinforcementCounterDepth4 = 0.0f;
			this->m_fEnemyReinforcementCounterDepth5 = 0.0f;

			this->m_fEnemyReinforcementRandTimeDepth2 = this->m_pLevel->GetRandReinforcementSendTime();
			this->m_fEnemyReinforcementRandTimeDepth3 = this->m_pLevel->GetRandReinforcementSendTime();
			this->m_fEnemyReinforcementRandTimeDepth4 = this->m_pLevel->GetRandReinforcementSendTime();
			this->m_fEnemyReinforcementRandTimeDepth5 = this->m_pLevel->GetRandReinforcementSendTime();

			break;

		case LOAD_LEVEL_CLEAR_ENEMIES:

			this->ClearLaunchEnemies();
			this->ClearStrikeEnemies();
			this->m_pReinforcements.Clear();

			break;

		case LOAD_LEVEL_CLEAR_OBSTACLES:

			this->ClearLevelObstacles();
			this->m_pObstacleEnemies.Clear();

			break;

		case LOAD_LEVEL_CLEAR_BULLETS:
			
			this->ClearBullets(true);

			break;

		case LOAD_LEVEL_CLEAR_EXPLOSIONS:

			this->m_pExplosions->Clear();

			break;

		case LOAD_LEVEL_CLEAR_PARTICLES:

			//this->m_pParticles.Clear();

			break;

		case LOAD_LEVEL_PREPARE_ENEMIES_LAUNCH:
			
			this->PrepareLaunchEnemies();

			break;

		case LOAD_LEVEL_PREPARE_ENEMIES_STRIKE:

			this->PrepareStrikeEnemies();

			break;

		case LOAD_LEVEL_PREPARE_ENEMIES_FLEET:
			
			this->PrepareReinforcements();

			break;

		case LOAD_LEVEL_INIT_OBSTACLES:
			
			this->InitLevelObstacles();

			switch(this->m_pLevel->GetLevelNumber())
			{
			case 2:
			case 3:

				if(this->m_iLoadLevelAsteroidStep < LOAD_LEVEL_ASTEROID_MAX)
				{
					increaseStep = false;
				}

				break;
			}

			break;

		case LOAD_LEVEL_COLLISION_MESH_OBSTACLES:

			this->CreateCollisionMeshObstacles();

			switch(this->m_pLevel->GetLevelNumber())
			{
			case 2:
			case 3:

				if(this->m_iLoadLevelAsteroidCollisionMeshStep < LOAD_LEVEL_ASTEROID_MAX)
				{
					increaseStep = false;
				}

				break;
			}

			break;

		case LOAD_LEVEL_PREPARE_OBSTACLES:
			
			this->PrepareObstacles();

			break;

		case LOAD_LEVEL_RESET_ENEMY_VALUES_2:

			// launch enemies count
			this->m_iEnemiesLaunch = 0;
			// strike enemies count
			this->m_iEnemiesStrike = 0;
			// reset passed obstacles count
			this->m_iObstaclesPassed = 0;

			// enemy launch counter
			this->m_fEnemyLaunchCounter = this->m_pLevel->GetFirstEnemyLaunch();
			// enemy strike counter
			this->m_fEnemyStrikeCounter = this->m_pLevel->GetFirstEnemyStrike();

			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;
			this->m_fEnemyExplosionSoundTimer = 0.0f;

			break;

		case LOAD_LEVEL_INIT_BOSS:
			
			this->InitLevelBoss();

			break;

		case LOAD_LEVEL_RESET_BOSS_VALUES:

			this->m_bBossWarning = true;

			this->m_fBossWarningStartTimer = 0.65f;
			this->m_fBossWarningEndTimer = 0.6f;
			this->m_fBossWarningTextTimer = 0.015f;
			this->m_iBossWarningTextIndex = 0;
			this->m_bBossWarningFadeOut = false;
			
			this->m_bBossDestroyed = false;

			break;

		case LOAD_LEVEL_BACKGROUND:

			this->LoadSpritesBackground();

			break;

		case LOAD_LEVEL_SET_PLAYER_VALUES:

			// reset player cannon values
			this->PlayerResetCannon();
			// reset player's hit sound timer
			this->m_pPlayer->ResetHitSoundTimer();
			// reset player's velocity values
			this->m_pPlayer->SetLevelStartVelocityControls();

			break;

		case LOAD_LEVEL_MUSIC:
			
			this->LoadMusicLevel();

			break;

		case LOAD_LEVEL_MUSIC_BOSS:
			
			this->LoadMusicBoss();

			break;

		case LOAD_LEVEL_INTRO:

			SwitchGameState(GAME_STATE_LEVEL_INTRO);

			break;
		}

		if(increaseStep)
		{
			this->m_iLoadLevelStep++;
		}

		if(this->m_iLoadLevelStep == LOAD_LEVEL_STEPS_MAX)
		{
			this->m_pTheApp->SetLoadingScreen(false);
		}
		else
		{
			this->m_pState->UpdateLoadingBar(1);
		}

		return;
	}

	this->CheckMusicEnd();
	this->ResetSoundExplosionEnemy(fFrametime);
	this->m_pPlayer->ResetHitSound(fFrametime);

	this->CheckExtraLife();
	this->CheckQuitGame(fFrametime);
	
	this->RenderBackgrounds();

	switch(this->m_iGameState)
	{
	case GAME_STATE_LEVEL_INTRO:

		this->RenderObstacles(fFrametime, false);
		this->RenderStatistics(fFrametime);

		// fades in, player enters the level and level title is shown
		if(this->m_bLevelIntro)
		{	
			// update fade-in
			if(this->m_bFadeIn)
			{
				if(!this->m_pState->GetFading()->UpdateFading())
				{
					this->m_bFadeIn = false;
					this->PlaySoundPlayerAfterburn();
				}

				this->m_pState->GetFading()->RenderFading();
			}
			else
			{
				// fade-in has finished,
				// player can enter current level
				this->UpdatePlayer(fFrametime);
				this->RenderPlayer(fFrametime);
			}

			// player enter movement is finished
			if(!this->m_bPlayerEnter)
			{
				// display level title (moves in)
				if(bLevelTitleIn)
				{
					// level title finished moving in
					if(!this->RenderLevelTitleIn())
					{
						bLevelTitleIn = false;
						bLevelTitleStay = true;

						// start level music
						this->PlayMusicLevel();
					}
				}
				// display level title (stays still)
				else if(bLevelTitleStay)
				{
					this->RenderLevelTitle();

					if(fTimerLevelTitle > 0.0f)
					{	
						fTimerLevelTitle -= fFrametime;
					}
					else
					{
						bLevelTitleStay = false;
						bLevelTitleOut = true;
					}
				}
				// display level title (moves out)
				else if(bLevelTitleOut)
				{
					// level title finished moving out
					if(!this->RenderLevelTitleOut())
					{
						// display mission info
						if(!this->RenderMissionInfo())
						{
							bLevelTitleOut = false;
							this->m_bLevelIntro = false;
							this->m_bPlayAfterburnSound = true;
						}
					}
				}
			}
		}
		else
		{
			this->UpdatePlayer(fFrametime);
			this->RenderPlayer(fFrametime);

			if( this->m_pLevel->IsObstaclesFirst() )
			{
				SwitchGameState(GAME_STATE_PLAY_OBSTACLES);
			}
			else
			{
				SwitchGameState(GAME_STATE_PLAY_ENEMIES);
			}

			if( this->m_pLevel->GetLaunchFirst() )
			{
				this->m_bFleetLaunch = true;
			}
			else if( this->m_pLevel->GetStrikeFirst() )
			{
				this->m_bFleetStrike = true;
			}

			// reset level title display timer
			fTimerLevelTitle = (float)TIMER_LEVEL_TITLE;
			bLevelTitleIn = true;
			bLevelTitleStay = false;
			bLevelTitleOut = false;

			this->m_pTheApp->CheckKeyPushes();
		}

		break;

	// enemy attacks
	case GAME_STATE_PLAY_ENEMIES:

		// send enemy reinforcements
		if(this->m_fEnemyReinforcementSendCounter >= this->m_fEnemyReinforcementSendTime)
		{
			if(!this->m_bEnemyReinforcementSending)
			{
				this->m_bEnemyReinforcementSending = true;
			}
		}
		else
		{
			this->m_fEnemyReinforcementSendCounter += fFrametime;
		}

		// no more enemy fleets left
		if(!this->m_bFleetLaunch && !this->m_bFleetStrike)
		{
			this->CollisionBulletVsBorder();

			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateEnemies();
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);

			if(this->m_pPlayer->IsAlive() && !this->m_bPlayerEnter)
			{
				SwitchGameState(GAME_STATE_VELOCITY_DECREASE);
			}
		}
		// enemy fleets still left
		else
		{
			if(this->m_bFleetLaunch)
			{
				// send a new launch enemy
				this->EnemyLaunch(fFrametime);
			}
			else if(this->m_bFleetStrike)
			{
				// send a new strike enemy
				this->EnemyStrike(fFrametime);
			}

			this->PlayerShooting(fFrametime);
			this->EnemyShooting();

			this->CollisionPlayerVsEnemy();
			this->CollisionPlayerCannonVsEnemy(fFrametime);
			this->CollisionPlayerCannonVsEnemyBullet();
			this->CollisionBulletVsBorder();
			this->CollisionBulletVsPlayer();
			this->CollisionBulletVsEnemy();

			this->ClearEnemies();
			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateEnemies();
			this->UpdateReinforcements(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderActiveEnemies(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);
			this->RenderObstacles(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);
		}

		this->RenderStatistics(fFrametime);

		break;

	// level has obstacles and maybe enemies
	case GAME_STATE_PLAY_OBSTACLES:

		// player has passed all the generated obstacles
		if(m_pObstaclesDepth1.IsEmpty() || (this->m_iObstaclesPassed == m_iObstaclesMax))
		{
			this->PlayerShooting(fFrametime);
			this->EnemyShooting();

			this->CollisionPlayerVsObstacle();
			this->CollisionEnemyVsObstacle();
			this->CollisionPlayerVsEnemy();
			this->CollisionPlayerCannonVsEnemy(fFrametime);
			this->CollisionPlayerCannonVsEnemyBullet();
			this->CollisionBulletVsObstacle();
			this->CollisionBulletVsPlayer();
			this->CollisionBulletVsEnemy();
			this->CollisionBulletVsBorder();

			this->ClearObstacles();
			this->ClearEnemies();
			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateEnemies();
			this->UpdateReinforcements(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderObstacles(fFrametime, false);
			this->RenderObstacleEnemies(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);

			SwitchGameState(GAME_STATE_WAIT_OBSTACLES);
		}
		else
		{
			this->PlayerShooting(fFrametime);
			this->EnemyShooting();

			this->CollisionPlayerVsObstacle();
			this->CollisionEnemyVsObstacle();
			this->CollisionPlayerVsEnemy();
			this->CollisionPlayerCannonVsEnemy(fFrametime);
			this->CollisionPlayerCannonVsEnemyBullet();
			this->CollisionBulletVsObstacle();
			this->CollisionBulletVsPlayer();
			this->CollisionBulletVsEnemy();
			this->CollisionBulletVsBorder();

			this->ClearObstacles();
			this->ClearEnemies();
			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateEnemies();
			this->UpdateReinforcements(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderObstacles(fFrametime, false);
			this->RenderObstacleEnemies(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);
		}

		this->RenderStatistics(fFrametime);

		break;

	// wait for all the obstacles to pass by
	case GAME_STATE_WAIT_OBSTACLES:

		if( this->m_pObstaclesDepth1.IsEmpty() && 
			this->m_pObstacleEnemies.IsEmpty() )
		{
			this->PlayerShooting(fFrametime);
			this->EnemyShooting();

			this->CollisionPlayerCannonVsEnemyBullet();
			this->CollisionBulletVsPlayer();
			this->CollisionBulletVsBorder();

			this->ClearObstacles();
			this->ClearEnemies();
			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateReinforcements(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderObstacles(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);

			SwitchGameState(GAME_STATE_VELOCITY_DECREASE);
		}
		else
		{
			this->PlayerShooting(fFrametime);
			this->EnemyShooting();

			this->CollisionPlayerVsObstacle();
			this->CollisionEnemyVsObstacle();
			this->CollisionPlayerVsEnemy();
			this->CollisionPlayerCannonVsEnemy(fFrametime);
			this->CollisionPlayerCannonVsEnemyBullet();
			this->CollisionBulletVsObstacle();
			this->CollisionBulletVsPlayer();
			this->CollisionBulletVsEnemy();
			this->CollisionBulletVsBorder();

			this->ClearObstacles();
			this->ClearEnemies();
			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateEnemies();
			this->UpdateReinforcements(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderObstacles(fFrametime, false);
			this->RenderObstacleEnemies(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);
		}

		this->RenderStatistics(fFrametime);

		break;

	case GAME_STATE_VELOCITY_DECREASE:

		this->PlayerShooting(fFrametime);
		this->EnemyShooting();

		this->CollisionPlayerVsEnemy();
		this->CollisionPlayerCannonVsEnemy(fFrametime);
		this->CollisionPlayerCannonVsEnemyBullet();
		this->CollisionBulletVsPlayer();
		this->CollisionBulletVsEnemy();
		this->CollisionBulletVsBorder();

		this->ClearObstacles();
		this->ClearEnemies();
		this->ClearBullets(false);
		this->ClearParticles();

		this->UpdatePlayer(fFrametime);
		this->UpdateReinforcements(fFrametime);
		this->UpdateBullets(fFrametime);
		this->UpdateExplosions(fFrametime);

		this->RenderObstacles(fFrametime, false);
		this->RenderReinforcements(fFrametime, false);

		this->RenderPlayer(fFrametime);
		this->RenderBullets(fFrametime, false);
		this->RenderExplosions();
		this->RenderParticles(fFrametime, false);
		this->RenderPlayerCannon(fFrametime, false);

		this->RenderStatistics(fFrametime);

		if(!this->m_pPlayer->IsMinBoost())
		{
			this->m_pPlayer->DecreaseBoost(fFrametime);
		}
		else
		{
			switch(this->m_pLevel->GetLevelNumber())
			{
			case 1:
				if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
					this->m_iGameStateNext = GAME_STATE_BOSS_INTRO;
				break;

			case 2:
				if(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES)
					this->m_iGameStateNext = GAME_STATE_PLAY_ENEMIES;
				else if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
					this->m_iGameStateNext = GAME_STATE_BOSS_INTRO;
				break;

			case 3:
				if(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES)
					this->m_iGameStateNext = GAME_STATE_BOSS_INTRO;
				else if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
					this->m_iGameStateNext = GAME_STATE_PLAY_OBSTACLES;
				break;
			}

			bBackgroundSpeedChange = true;
			fBackgroundSpeedChangePause = 0.0f;

			SwitchGameState(GAME_STATE_SPEED_CHANGE);
		}

		break;

	// background speed changes
	case GAME_STATE_SPEED_CHANGE:

		this->PlayerShooting(fFrametime);

		this->CollisionBulletVsPlayer();

		this->ClearObstacles();
		this->ClearEnemies();
		this->ClearBullets(false);
		this->ClearParticles();

		this->UpdatePlayer(fFrametime);
		this->UpdateReinforcements(fFrametime);
		this->UpdateBullets(fFrametime);
		this->UpdateExplosions(fFrametime);

		this->RenderObstacles(fFrametime, false);
		this->RenderReinforcements(fFrametime, false);

		this->RenderPlayer(fFrametime);
		this->RenderBullets(fFrametime, false);
		this->RenderExplosions();
		this->RenderParticles(fFrametime, false);
		this->RenderPlayerCannon(fFrametime, false);

		// change background speed step by step
		if(	bBackgroundSpeedChange && this->m_pPlayer->IsAlive() && !this->m_bPlayerEnter)
		{
			if(fBackgroundSpeedChangePause > 0.0f)
			{
				fBackgroundSpeedChangePause -= fFrametime;
			}
			else
			{
				fBackgroundSpeedChangePause = 0.30f;

				int iBackgroundTopSpeed = 0;
				int iBackgroundTopPause = 0;

				switch(this->m_iGameStateNext)
				{
				case GAME_STATE_PLAY_ENEMIES:

					iBackgroundTopSpeed = this->m_pLevel->GetBackgroundTopSpeedEnemies();
					iBackgroundTopPause = this->m_pLevel->GetBackgroundTopPauseEnemies();

					break;

				case GAME_STATE_PLAY_OBSTACLES:

					iBackgroundTopSpeed = this->m_pLevel->GetBackgroundTopSpeedObstacles();
					iBackgroundTopPause = this->m_pLevel->GetBackgroundTopPauseObstacles();

					break;

				case GAME_STATE_BOSS_INTRO:

					iBackgroundTopSpeed = this->m_pLevel->GetBackgroundTopSpeedBoss();
					iBackgroundTopPause = this->m_pLevel->GetBackgroundTopPauseBoss();

					break;
				}

				// increase "top" speed
				if(this->m_pSpriteBackgroundTop->GetSpeed() < iBackgroundTopSpeed)
				{
					bBackgroundSpeedChangeAfterburn = true;
					this->m_pSpriteBackgroundTop->IncreaseSpeed();
				}
				// decrease "top" speed
				else if(this->m_pSpriteBackgroundTop->GetSpeed() > iBackgroundTopSpeed)
				{
					bBackgroundSpeedChangeAfterburn = false;
					this->m_pSpriteBackgroundTop->DecreaseSpeed();
				}
				// increase "top" pause
				if(this->m_pSpriteBackgroundTop->GetMaxPause() < iBackgroundTopPause)
				{
					bBackgroundSpeedChangeAfterburn = false;
					this->m_pSpriteBackgroundTop->IncreaseMaxPause();
				}
				// decrease "top" pause
				else if(this->m_pSpriteBackgroundTop->GetMaxPause() > iBackgroundTopPause)
				{
					bBackgroundSpeedChangeAfterburn = true;
					this->m_pSpriteBackgroundTop->DecreaseMaxPause();
				}

				// background speed change is finished
				if(	(this->m_pSpriteBackgroundTop->GetSpeed() == iBackgroundTopSpeed) && 
					(this->m_pSpriteBackgroundTop->GetMaxPause() == iBackgroundTopPause))
				{
					bBackgroundSpeedChange = false;
					this->m_pSpriteBackgroundTop->SetDefaultSpeed(iBackgroundTopSpeed);
				}
			}

			if(bBackgroundSpeedChangeAfterburn)
			{
				this->RenderPlayerAfterburn(false);
			}
			if(this->m_bPlayAfterburnSound && bBackgroundSpeedChangeAfterburn)
			{
				this->PlaySoundPlayerAfterburn();
				this->m_bPlayAfterburnSound = false;
			}
		}
		// go to next game state
		else
		{
			bBackgroundSpeedChangeReinforcements = true;
			bBackgroundSpeedChangeObstacles = true;

			this->m_bPlayAfterburnSound = true;

			this->NormalSpeedReinforcement();
			this->NormalSpeedObstacle();

			SwitchGameState(this->m_iGameStateNext);
		}

		this->RenderStatistics(fFrametime);

		// change sent reinforcements / obstacles speed
		switch(this->m_iGameStatePrevious)
		{
		case GAME_STATE_PLAY_ENEMIES:

			if(bBackgroundSpeedChangeReinforcements)
			{
				bBackgroundSpeedChangeReinforcements = false;
				//this->IncreaseSpeedReinforcement();
			}

			break;

		case GAME_STATE_WAIT_OBSTACLES:

			if(bBackgroundSpeedChangeObstacles)
			{
				bBackgroundSpeedChangeObstacles = false;
				this->IncreaseSpeedObstacle();
			}

			break;
		}

		break;

	case GAME_STATE_BOSS_INTRO:

		this->PlayerShooting(fFrametime);

		// fade-out level music
		if(this->m_bFadeOutMusic)
		{
			if( !this->FadeOutMusicLevel(fFrametime) )
			{
				this->m_bFadeOutMusic = false;
				// stop and free level music
				this->StopMusicLevel();
			}
		}

		if(this->m_bBossWarning)
		{
			this->CollisionBulletVsBorder();

			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);

			if(this->m_fBossWarningStartTimer <= 0.0f)
			{
				this->RenderBossWarning(fFrametime, false);
			}
			else
			{
				this->m_fBossWarningStartTimer -= fFrametime;

				if(this->m_fBossWarningStartTimer <= 0.0f)
				{
					// play sound effect
					this->m_pTheApp->GetWave(SOUND_BOSS_INTRO_WARNING).Play(
						FALSE, 0, this->m_pTheApp->GetVolumeSoundEffect());
				}
			}

			if(!this->m_bBossWarning)
			{
				// play boss music
				this->PlayMusicBoss();
			}
		}
		else
		{
			this->CollisionPlayerVsBoss();
			this->CollisionBulletVsBorder();

			this->ClearBullets(false);
			this->ClearParticles();

			this->UpdatePlayer(fFrametime);
			this->UpdateBoss(fFrametime);
			this->UpdateBullets(fFrametime);
			this->UpdateExplosions(fFrametime);

			this->RenderBoss(fFrametime, false);
			this->RenderReinforcements(fFrametime, false);

			this->RenderPlayer(fFrametime);
			this->RenderBullets(fFrametime, false);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, false);
			this->RenderPlayerCannon(fFrametime, false);

			// Boss enter scene has ended
			if( !this->CheckBossEnter() )
			{
				this->m_bFadeOutMusic = true;
				this->m_pTheApp->CheckKeyPushes();

				SwitchGameState(GAME_STATE_BOSS_ACTION);
			}
		}

		this->RenderStatistics(fFrametime);

		break;

	case GAME_STATE_BOSS_ACTION:

		this->PlayerShooting(fFrametime);

		this->CollisionPlayerVsBoss();
		this->CollisionPlayerCannonVsBoss(fFrametime);
		this->CollisionPlayerCannonVsBossBullet();
		this->CollisionBulletVsPlayer();
		this->CollisionBulletVsBoss();
		this->CollisionBulletVsBorder();

		this->ClearBullets(false);
		this->ClearParticles();

		this->UpdatePlayer(fFrametime);
		this->UpdateBoss(fFrametime);
		this->UpdateBullets(fFrametime);
		this->UpdateExplosions(fFrametime);

		this->RenderBoss(fFrametime, false);
		this->RenderReinforcements(fFrametime, false);

		this->RenderPlayer(fFrametime);
		this->RenderBullets(fFrametime, false);
		this->RenderExplosions();
		this->RenderParticles(fFrametime, false);
		this->RenderPlayerCannon(fFrametime, false);

		if( this->m_bBossDestroyed )
		{
			switch(this->m_pLevel->GetLevelNumber())
			{
			case 1:
				iCountBossChainExplosions = EXPLOSION_CHAIN_REPEATS_BOSS_1;

				fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_1,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_1);

				fPauseBossPartExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_PART_TIMER_MIN_BOSS_1,
					(float)EXPLOSION_PART_TIMER_MAX_BOSS_1);

				break;

			case 2:
				iCountBossChainExplosions = EXPLOSION_CHAIN_REPEATS_BOSS_2;

				fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_2,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_2);

				fPauseBossPartExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_PART_TIMER_MIN_BOSS_2,
					(float)EXPLOSION_PART_TIMER_MAX_BOSS_2);

				break;

			case 3:
				iCountBossChainExplosions = EXPLOSION_CHAIN_REPEATS_BOSS_3;

				fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_3,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_3);

				fPauseBossPartExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_PART_TIMER_MIN_BOSS_3,
					(float)EXPLOSION_PART_TIMER_MAX_BOSS_3);

				break;
			}

			SwitchGameState(GAME_STATE_BOSS_CHAIN_EXPLOSION);
		}

		this->RenderStatistics(fFrametime);

		break;

	case GAME_STATE_BOSS_CHAIN_EXPLOSION:

		this->PlayerShooting(fFrametime);

		this->CollisionPlayerVsBoss();
		this->CollisionPlayerCannonVsBoss(fFrametime);
		this->CollisionPlayerCannonVsBossBullet();
		this->CollisionBulletVsPlayer();
		this->CollisionBulletVsBoss();
		this->CollisionBulletVsBorder();

		this->ClearBullets(false);
		this->ClearParticles();

		this->UpdatePlayer(fFrametime);
		this->UpdateBoss(fFrametime);
		this->UpdateBullets(fFrametime);
		this->UpdateExplosions(fFrametime);

		this->RenderBoss(fFrametime, false);
		this->RenderReinforcements(fFrametime, false);

		this->RenderPlayer(fFrametime);
		this->RenderBullets(fFrametime, false);
		this->RenderExplosions();
		this->RenderParticles(fFrametime, false);
		this->RenderPlayerCannon(fFrametime, false);

		// boss chain and part explosions
		if(fPauseBossChainExplosion <= 0.0f)
		{
			if(iCountBossChainExplosions > 0)
			{
				/* chain explosions */

				iCountBossChainExplosions--;
				this->BossFrameChainExplosion();

				// play sound effect

				if(iSoundBossChainExplosion == 1)
				{
					iSoundBossChainExplosion = 2;
					this->PlaySoundExplosionBossChain(1);
				}
				else
				{
					iSoundBossChainExplosion = 1;
					this->PlaySoundExplosionBossChain(2);
				}

				// new chain explosion timer value
				switch(this->m_pLevel->GetLevelNumber())
				{
				case 1:

					fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_1,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_1);

					break;

				case 2:

					fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_2,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_2);

					break;

				case 3:

					fPauseBossChainExplosion = this->m_pTheApp->RandFloat(
					(float)EXPLOSION_CHAIN_TIMER_MIN_BOSS_3,
					(float)EXPLOSION_CHAIN_TIMER_MAX_BOSS_3);

					break;
				}

				/* part explosions */

				if (fPauseBossPartExplosion <= 0.0f)
				{
					if (this->CheckBossPartExplosion(iCountBossChainExplosions))
					{
						// new chain explosion timer value
						fPauseBossPartExplosion = this->m_pTheApp->RandFloat(
							(float)EXPLOSION_PART_TIMER_MIN_BOSS_1,
							(float)EXPLOSION_PART_TIMER_MAX_BOSS_1);
					}
				}
				else
				{
					fPauseBossPartExplosion -= fFrametime;
				}
			}
			// chain explosions finished
			else
			{
				switch(this->m_pLevel->GetLevelNumber())
				{
				case 1:
					fPauseBossBigExplosion = (float)EXPLOSION_BIG_TIMER_BOSS_1;
					this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1Frame->GetScoreDestroyed());
					break;
				case 2:
					fPauseBossBigExplosion = (float)EXPLOSION_BIG_TIMER_BOSS_2;
					this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1Frame->GetScoreDestroyed());
					break;
				case 3:
					fPauseBossBigExplosion = (float)EXPLOSION_BIG_TIMER_BOSS_3;
					this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1Frame->GetScoreDestroyed());
					break;
				}

				iSoundBossChainExplosion = 1;
				// boss core big explosion
				this->BossFrameBigExplosion();
				// play sound effect
				this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_BIG).Play(FALSE, 0, this->m_iVolumeSoundEffect);

				SwitchGameState(GAME_STATE_BOSS_BIG_EXPLOSION);
			}
		}
		else
		{
			fPauseBossChainExplosion -= fFrametime;
		}

		this->RenderStatistics(fFrametime);

		break;

	case GAME_STATE_BOSS_BIG_EXPLOSION:

		if(this->m_bFadeOutMusic)
		{
			// fade-out boss music
			if( !this->FadeOutMusicBoss(fFrametime) )
			{
				this->m_bFadeOutMusic = false;
				// stop and free music
				this->StopMusicBoss();
			}
		}

		this->CollisionPlayerCannonVsBossBullet();
		this->CollisionBulletVsPlayer();
		this->CollisionBulletVsBorder();

		this->ClearBullets(false);
		this->ClearParticles();

		this->UpdatePlayer(fFrametime);
		this->UpdateBoss(fFrametime);
		this->UpdateBullets(fFrametime);
		this->UpdateExplosions(fFrametime);

		this->RenderBoss(fFrametime, false);
		this->RenderReinforcements(fFrametime, false);

		this->RenderPlayer(fFrametime);
		this->RenderBullets(fFrametime, false);
		this->RenderExplosions();
		this->RenderParticles(fFrametime, false);
		this->RenderPlayerCannon(fFrametime, false);

		if(fPauseBossBigExplosion <= 0.0f)
		{
			// reset player miniguns direction
			if(!this->PlayerResetMiniguns())
			{
				// need to leave some positive value to count down,
				// so that "player move away" gets activated
				fPauseOutroMinigunsRotation = 0.05f;
			}

			if(	this->m_pPlayer->IsAlive() && !this->m_bPlayerEnter && !this->m_pPlayer->IsUntouchable())
			{
				SwitchGameState(GAME_STATE_LEVEL_OUTRO);
			}
		}
		else
		{
			fPauseBossBigExplosion -= fFrametime;
		}

		this->RenderStatistics(fFrametime);

		break;

	case GAME_STATE_LEVEL_OUTRO:

		this->UpdatePlayer(fFrametime);

		this->RenderReinforcements(fFrametime, false);
		this->RenderPlayer(fFrametime);

		if(fPauseOutroMinigunsRotation <= 0.0f)
		{
			if(!this->m_bPlayerMoveAway)
			{
				// player has finished the game
				if(this->m_pLevel->GetLevelNumber() == LEVELS_MAX)
				{
					SwitchGameState(GAME_STATE_END_SUCCESS);
				}
				// go to next level
				else
				{
					// render statistics
					this->RenderStatistics(fFrametime);

					// update screen fade-out
					bool bScreenFading = this->m_pState->GetFading()->UpdateFading();
					// render screen fade-out
					this->m_pState->GetFading()->RenderFading();

					// screen fade-out has finished, move to next level
					if(!bScreenFading)
					{
						this->m_bFadeOut = false;
						fPauseOutroMinigunsRotation = 1.0f;

						this->m_pTheApp->SetLoadingScreen(true);
						this->m_pState->InitLoadingScreenValues(LOAD_LEVEL_STEPS_MAX - 1 + 2 * LOAD_LEVEL_ASTEROID_MAX);

						SwitchGameState(GAME_STATE_INIT_LEVEL);
					}
				}
			}
		}
		else
		{
			fPauseOutroMinigunsRotation -= fFrametime;

			if(fPauseOutroMinigunsRotation <= 0.0f)
			{
				this->m_bPlayerMoveAway = true;
			}
		}

		this->RenderStatistics(fFrametime);
		
		break;

	case GAME_STATE_END_SUCCESS:

		this->RenderStatistics(fFrametime);
		this->RenderEndSuccess(fFrametime);

		break;

	case GAME_STATE_END_FAILED:

		this->QuitGameAction(fFrametime);
		this->RenderEndFailed();

		break;

	// player blast is active
	case GAME_STATE_BLAST_ACTIVE:

		if( this->m_fBlastActiveCounter <= 0.0f )
		{
			this->PlayerBlastDeactive();
		}
		else
		{
			// update blast active counter
			this->m_fBlastActiveCounter -= fFrametime;

			// update player's blast lighting
			/*
			this->m_pState->GetLights()->UpdateGamePlayerBlast(
				this->m_pPlayer->GetBlastLight());
			*/

			this->UpdatePlayer(fFrametime);

			// update blast shaking

			if( (this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION))
			{
				this->UpdateBossShake(true, fFrametime);
			}
			else
			{
				this->UpdateEnemiesShake(true, fFrametime);
			}

			this->RenderActiveEnemies(fFrametime, true);
			this->RenderObstacleEnemies(fFrametime, true);
			this->RenderReinforcements(fFrametime, true);
			this->RenderObstacles(fFrametime, true);

			// render boss
			if( (this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION))
			{
				this->RenderBoss(fFrametime, true);
			}

			this->RenderBullets(fFrametime, true);
			this->RenderPlayer(fFrametime);
			this->RenderExplosions();
			this->RenderParticles(fFrametime, true);
		}

		this->RenderStatistics(fFrametime);

		break;

	// player quits the game
	case GAME_STATE_QUIT:

		// update fade-out
		if(this->m_bFadeOut)
		{
			if(!this->m_pState->GetFading()->UpdateFading())
			{
				this->m_bFadeOut = false;
			}
		}

		// music fade-outs
		if(this->m_bFadeOutMusic)
		{
			if(	(this->m_iGameStateEnd != GAME_STATE_END_SUCCESS) && 
				(this->m_iGameStateEnd != GAME_STATE_END_FAILED))
			{
				// fade-out boss music
				if(	(this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO) || 
					(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
					(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
					(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
				{
					
					if( !this->FadeOutMusicBoss(fFrametime) )
					{
						this->m_bFadeOutMusic = false;
						// stop and free music
						this->StopMusicBoss();
					}
				}
				// fade-out level music
				else
				{
					if( !this->FadeOutMusicLevel(fFrametime) )
					{
						this->m_bFadeOutMusic = false;
						// stop and free music
						this->StopMusicLevel();
					}
				}
			}
		}

		this->QuitGameAction(fFrametime);
		this->m_pState->GetFading()->RenderFading();

		if(!this->m_bFadeOut && !this->m_bFadeOutMusic)
		{
			// set player's blast light off
			if(this->m_iGameStatePrevious == GAME_STATE_BLAST_ACTIVE)
			{
				this->m_pState->GetLights()->SetGamePlayerBlast(false, this->m_pPlayer->GetPosition());
			}


			this->m_pState->SetState(STATE_MENUS);

			if(this->m_bCheckHighScore)
			{
				if(this->m_pPlayer->GetScore() > 0)
				{
					// player got a new highscore
					if(this->m_pTheApp->GetHighScore().IsHighScore(this->m_pPlayer->GetScore()))
					{
						this->m_pTheApp->GetHighScore().SetNewScore(this->m_pPlayer->GetScore());
						this->m_pTheApp->GetHighScore().SetNewLevel(this->m_pLevel->GetLevelNumber());
						this->m_pTheApp->GetHighScore().SetNewTime(this->m_fGameTime);

						// go to highscore input screen
						this->m_pState->SetState(STATE_HIGHSCORE);
					}
				}
			}

			// need to prepare new state
			this->m_pState->SetNewState(true);
			// create state first, then initialize it
			this->m_pState->GetApp()->SetCreateState(true);
		}

		break;
	}

	this->UpdateTime(fFrametime);

	if(this->m_iGameState != GAME_STATE_SPEED_CHANGE)
	{
		this->UpdateVelocityTimeMargin(fFrametime);
		this->UpdateVelocityPixels();
		this->UpdateBackgroundVelocity();
		this->UpdateExplosionVelocity();
	}
}

void CTheGame::SwitchGameState(int iNextGameState)
{
	switch (iNextGameState)
	{
	case GAME_STATE_LEVEL_INTRO:

		// set player enter
		this->PlayerSetEnter(iNextGameState);
		this->m_bPlayerEnter = true;

		// set screen fade-in
		this->m_pState->GetFading()->SetFadeIn();
		this->m_pState->GetFading()->SetDefaultFadeStep();
		//this->m_pState->GetFading()->SetFadeStep(m_FadeInLevelTime);

		if (this->m_pLevel->IsObstaclesFirst())
		{
			this->m_pPlayer->SetVelocity(this->m_pLevel->GetPlayerVelocityObstacle());
			this->m_pPlayer->SetBoostMax(this->m_pLevel->GetPlayerBoostMaxObstacle());

			ActivateBackgroundObstacles(TRUE);
		}
		else
		{
			this->m_pPlayer->SetVelocity(this->m_pLevel->GetPlayerVelocityEnemy());
			this->m_pPlayer->SetBoostMax(this->m_pLevel->GetPlayerBoostMaxEnemy());
		}

		this->m_bLevelIntro = true;

		break;

	case GAME_STATE_PLAY_OBSTACLES:

		if (!m_pLevel->IsObstaclesFirst())
		{
			ActivateBackgroundObstacles(TRUE);
		}

		ActivateObstacles(&this->m_pObstaclesDepth1, TRUE);

		this->m_iExplosionMoveSpeed = this->m_pLevel->GetBackgroundTopSpeedObstacles() / 2;
		this->m_fExplosionMovePause = this->m_pLevel->GetBackgroundTopPauseObstacles() * 1.5f;

		this->m_pPlayer->SetVelocityControl(true);
		this->m_pPlayer->SetVerticalControl(false);

		this->m_pPlayer->SetVelocity(this->m_pLevel->GetPlayerVelocityObstacle());
		this->m_pPlayer->SetBoostMax(this->m_pLevel->GetPlayerBoostMaxObstacle());

		// We have just entered the asteroid field.
		if (this->m_iGameState != GAME_STATE_BLAST_ACTIVE)
		{
			this->m_iObstaclesPassed = 0;
		}

		break;

	case GAME_STATE_PLAY_ENEMIES:

		this->m_pPlayer->SetVelocityControl(false);
		this->m_pPlayer->SetVerticalControl(true);

		this->m_pPlayer->SetVelocity(this->m_pLevel->GetPlayerVelocityEnemy());
		this->m_pPlayer->SetBoostMax(this->m_pLevel->GetPlayerBoostMaxEnemy());

		this->m_iExplosionMoveSpeed = this->m_pLevel->GetBackgroundTopSpeedEnemies() / 2;
		this->m_fExplosionMovePause = this->m_pLevel->GetBackgroundTopPauseEnemies() * 1.5f;

		this->m_iMaxEnemies = 0;

		break;

	case GAME_STATE_BOSS_INTRO:

		this->m_pPlayer->SetVelocityControl(false);
		this->m_pPlayer->SetVerticalControl(true);

		this->m_pPlayer->SetVelocity(0.0f);
		this->m_pPlayer->SetBoost(0.0f);

		this->m_iExplosionMoveSpeed = this->m_pLevel->GetBackgroundTopSpeedBoss() / 2;
		this->m_fExplosionMovePause = this->m_pLevel->GetBackgroundTopPauseBoss() * 1.5f;

		this->m_pEnemyBoss1Frame->SetVisible(TRUE);

		break;

	case GAME_STATE_VELOCITY_DECREASE:

		this->m_pPlayer->SetVelocityControl(false);

		break;

	case GAME_STATE_SPEED_CHANGE:

		this->m_bEnemyReinforcementSending = false;
		this->m_fEnemyReinforcementSendCounter = 0.0f;

		break;

	case GAME_STATE_LEVEL_OUTRO:

		// fade out music
		this->m_bFadeOutMusic = true;

		// fade out screen
		this->m_pState->GetFading()->SetFadeOut();
		this->m_pState->GetFading()->SetDefaultFadeStep();
		//this->m_pState->GetFading()->SetFadeStep(m_FadeOutLevelTime);

		break;

	case GAME_STATE_QUIT:

		// fade out screen
		this->m_pState->GetFading()->SetFadeOut();
		this->m_pState->GetFading()->SetDefaultFadeStep();
		//this->m_pState->GetFading()->SetFadeStep(m_FadeOutQuitTime);

		break;

	case GAME_STATE_END_FAILED:

		this->m_pPlayer->SetActive(FALSE);

		// stop and free music
		this->StopMusicAll();

		// play music and sound effect
		this->PlayMusicGameOver();
		this->m_pTheApp->GetWave(SOUND_GAME_OVER).Play(FALSE, 0, this->m_iVolumeSoundEffect);

		this->m_bFadeOutMusic = false;
		this->m_bCheckHighScore = true;

		break;

	case GAME_STATE_END_SUCCESS:

		this->PlayMusicGameOutro();

		this->m_bFadeOutMusic = false;
		this->m_bCheckHighScore = true;

		break;
	}

	this->m_iGameStatePrevious = this->m_iGameState;
	this->m_iGameState = iNextGameState;

	if (this->m_iGameStatePrevious == -1)
	{
		this->m_iGameStatePrevious = this->m_iGameState;
	}
}

void CTheGame::ActivateObstacles(CQueue<CObstacle*>* pObstacles, BOOL bEnable)
{
	pObstacles->SetFirst();
	while (pObstacles->GetCurrent())
	{
		CObstacle* obstacle = pObstacles->GetCurrent();
		obstacle->SetActive(bEnable);

		pObstacles->SetNext();
	}
}

void CTheGame::ActivateBackgroundObstacles(BOOL bEnable)
{
	ActivateObstacles(&this->m_pObstaclesDepth2, bEnable);
	ActivateObstacles(&this->m_pObstaclesDepth3, bEnable);
	ActivateObstacles(&this->m_pObstaclesDepth4, bEnable);
	ActivateObstacles(&this->m_pObstaclesDepth5, bEnable);
}

void CTheGame::QuitGameAction(float fFrametime)
{
	if(!this->m_bFreezeQuit)
	{
		// object generation

		switch(this->m_iGameStatePrevious)
		{
		case GAME_STATE_PLAY_ENEMIES:

			// current fleet is launch
			if(this->m_bFleetLaunch)
			{
				// try to send a new launch enemy
				this->EnemyLaunch(fFrametime);
			}
			else if(this->m_bFleetStrike)
			{
				// try to send a new strike enemy
				this->EnemyStrike(fFrametime);
			}

			break;

		case GAME_STATE_PLAY_OBSTACLES:

			break;
		}

		// shooting action

		if(	(this->m_iGameStateEnd != GAME_STATE_END_SUCCESS) && 
			(this->m_iGameStateEnd != GAME_STATE_END_FAILED))
		{
			this->PlayerShooting(fFrametime);
		}

		this->EnemyShooting();

		// collisions

		this->CollisionBulletVsBorder();

		if(	(this->m_iGameStateEnd != GAME_STATE_END_SUCCESS) && 
			(this->m_iGameStateEnd != GAME_STATE_END_FAILED))
		{
			this->CollisionBulletVsPlayer();
		}

		if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
		{
			this->CollisionBulletVsEnemy();

			if(this->m_iGameStateEnd != GAME_STATE_END_FAILED)
			{
				this->CollisionPlayerVsEnemy();
				this->CollisionPlayerCannonVsEnemy(fFrametime);
				this->CollisionPlayerCannonVsEnemyBullet();
			}
		}
		else if((this->m_iGameStatePrevious == GAME_STATE_PLAY_OBSTACLES) || 
				(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES) )
		{
			this->CollisionEnemyVsObstacle();
			this->CollisionBulletVsObstacle();

			if(this->m_iGameStateEnd != GAME_STATE_END_FAILED)
			{
				this->CollisionPlayerVsEnemy();
				this->CollisionPlayerVsObstacle();
			}
		}
		else if((this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION))
		{
			this->CollisionBulletVsBoss();

			if(this->m_iGameStateEnd != GAME_STATE_END_FAILED)
			{
				this->CollisionPlayerVsBoss();
				this->CollisionPlayerCannonVsBoss(fFrametime);
				this->CollisionPlayerCannonVsBossBullet();
			}
		}

		// clearing

		if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
		{
			this->ClearEnemies();
		}
		
		if( (this->m_iGameStatePrevious == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES) )
		{
			this->ClearEnemies();
			this->ClearObstacles();
		}

		this->ClearBullets(false);
		this->ClearParticles();

		// updates

		this->UpdateBullets(fFrametime);

		if(	(this->m_iGameStateEnd != GAME_STATE_END_SUCCESS) && 
			(this->m_iGameStateEnd != GAME_STATE_END_FAILED))
		{
			this->UpdatePlayer(fFrametime);
		}

		if(	(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES) || 
			(this->m_iGameStatePrevious == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES))
		{
			this->UpdateEnemies();
			this->UpdateReinforcements(fFrametime);
		}

		else if((this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			this->UpdateBoss(fFrametime);
		}

		this->UpdateExplosions(fFrametime);
	}

	// renders

	if(this->m_iGameStatePrevious == GAME_STATE_PLAY_ENEMIES)
	{
		this->RenderActiveEnemies(fFrametime, this->m_bFreezeQuit);
		this->RenderReinforcements(fFrametime, this->m_bFreezeQuit);
	}
	else if((this->m_iGameStatePrevious == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameStatePrevious == GAME_STATE_WAIT_OBSTACLES))
	{
		this->RenderActiveEnemies(fFrametime, this->m_bFreezeQuit);
		this->RenderReinforcements(fFrametime, this->m_bFreezeQuit);
		this->RenderObstacles(fFrametime, this->m_bFreezeQuit);
	}
	else if(this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO)
	{
		this->RenderBoss(fFrametime, this->m_bFreezeQuit);
		this->RenderReinforcements(fFrametime, this->m_bFreezeQuit);

		if(this->m_fBossWarningStartTimer <= 0.0f)
		{
			this->RenderBossWarning(fFrametime, this->m_bFreezeQuit);
		}
	}
	else if((this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO) || 
			(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
	{
		this->RenderBoss(fFrametime, this->m_bFreezeQuit);
		this->RenderReinforcements(fFrametime, this->m_bFreezeQuit);
	}

	if(	(this->m_iGameStateEnd != GAME_STATE_END_SUCCESS) && 
		(this->m_iGameStateEnd != GAME_STATE_END_FAILED))
	{
		this->RenderPlayer(fFrametime);
		this->RenderPlayerCannon(fFrametime, this->m_bFreezeQuit);
	}

	this->RenderBullets(fFrametime, this->m_bFreezeQuit);
	this->RenderExplosions();
	this->RenderParticles(fFrametime, this->m_bFreezeQuit);

	this->RenderStatistics(fFrametime);

	if(this->m_iGameStateEnd == GAME_STATE_END_SUCCESS)
	{
		this->RenderEndSuccess(fFrametime);
	}
	else if(this->m_iGameStateEnd == GAME_STATE_END_FAILED)
	{
		this->RenderEndFailed();
	}

	// Boss enter scene has ended
	if(!this->m_bFreezeQuit)
	{
		if(this->m_iGameStatePrevious == GAME_STATE_BOSS_INTRO)
		{
			if( !this->CheckBossEnter() )
			{
				this->m_iGameStatePrevious = GAME_STATE_BOSS_ACTION;
				this->m_pTheApp->CheckKeyPushes();
			}
		}
	}
}

void CTheGame::Release()
{
	/* PLAYER */

	if (this->m_pPlayer)
	{
		this->m_pPlayer->Release();
		delete this->m_pPlayer;
		this->m_pPlayer = NULL;
	}

	if (this->m_pPlayerController)
	{
		delete this->m_pPlayerController;
		this->m_pPlayerController = NULL;
	}

	/* WEAPONS */

	if (this->m_pWeaponPlayerFront)
	{
		this->m_pWeaponPlayerFront->Release();
		delete this->m_pWeaponPlayerFront;
		this->m_pWeaponPlayerFront = NULL;
	}

	if (this->m_pWeaponPlayerDiagonal)
	{
		this->m_pWeaponPlayerDiagonal->Release();
		delete this->m_pWeaponPlayerDiagonal;
		this->m_pWeaponPlayerDiagonal = NULL;
	}

	if (this->m_pWeaponDrone)
	{
		this->m_pWeaponDrone->Release();
		delete this->m_pWeaponDrone;
		this->m_pWeaponDrone = NULL;
	}

	if (this->m_pWeaponSniper)
	{
		this->m_pWeaponSniper->Release();
		delete this->m_pWeaponSniper;
		this->m_pWeaponSniper = NULL;
	}

	/* LAUNCH ENEMIES */

	for (int i = 0; i < this->m_vTemplateEnemyDroneLaunch.size(); i++)
	{
		this->m_vTemplateEnemyDroneLaunch[i]->Release();
		delete this->m_vTemplateEnemyDroneLaunch[i];
		this->m_vTemplateEnemyDroneLaunch[i] = NULL;
	}

	for (int i = 0; i < this->m_vTemplateEnemySniperLaunch.size(); i++)
	{
		this->m_vTemplateEnemySniperLaunch[i]->Release();
		delete this->m_vTemplateEnemySniperLaunch[i];
		this->m_vTemplateEnemySniperLaunch[i] = NULL;
	}

	for (int i = 0; i < this->m_vTemplateEnemyRollerLaunch.size(); i++)
	{
		this->m_vTemplateEnemyRollerLaunch[i]->Release();
		delete this->m_vTemplateEnemyRollerLaunch[i];
		this->m_vTemplateEnemyRollerLaunch[i] = NULL;
	}

	/*
	for (int i = 0; i < this->m_vTemplateEnemyGuardLaunch.size(); i++)
	{
		this->m_vTemplateEnemyGuardLaunch[i]->Release();
		delete this->m_vTemplateEnemyGuardLaunch[i];
		this->m_vTemplateEnemyGuardLaunch[i] = NULL;
	}
	*/

	/* STRIKE ENEMIES */

	if (this->m_pEnemyDroneStrike)
	{
		this->m_pEnemyDroneStrike->Release();
		delete this->m_pEnemyDroneStrike;
		this->m_pEnemyDroneStrike = NULL;
	}

	if (this->m_pEnemySniperStrike)
	{
		this->m_pEnemySniperStrike->Release();
		delete this->m_pEnemySniperStrike;
		this->m_pEnemySniperStrike = NULL;
	}

	if (this->m_pEnemyRollerStrike)
	{
		this->m_pEnemyRollerStrike->Release();
		delete this->m_pEnemyRollerStrike;
		this->m_pEnemyRollerStrike = NULL;
	}

	/*
	if( this->m_pEnemyGuardStrike )
	{
		this->m_pEnemyGuardStrike->Release();
		delete this->m_pEnemyGuardStrike;
		this->m_pEnemyGuardStrike = NULL;
	}
	*/

	/* BOSSES */

	if (this->m_pEnemyBoss1Frame)
	{
		this->m_pEnemyBoss1Frame->Release();
		delete this->m_pEnemyBoss1Frame;
		this->m_pEnemyBoss1Frame = NULL;
	}

	if (this->m_pEnemyBoss1ScatterLeft)
	{
		this->m_pEnemyBoss1ScatterLeft->Release();
		delete this->m_pEnemyBoss1ScatterLeft;
		this->m_pEnemyBoss1ScatterLeft = NULL;
	}

	if (this->m_pEnemyBoss1ScatterRight)
	{
		this->m_pEnemyBoss1ScatterRight->Release();
		delete this->m_pEnemyBoss1ScatterRight;
		this->m_pEnemyBoss1ScatterRight = NULL;
	}

	if (this->m_pEnemyBoss1Cannon)
	{
		this->m_pEnemyBoss1Cannon->Release();
		delete this->m_pEnemyBoss1Cannon;
		this->m_pEnemyBoss1Cannon = NULL;
	}

	/* OBSTACLES */

	for (int i = 0; i < this->m_vTemplateAsteroidBig.size(); i++)
	{
		this->m_vTemplateAsteroidBig[i]->Release();
		delete this->m_vTemplateAsteroidBig[i];
		this->m_vTemplateAsteroidBig[i] = NULL;
	}

	for (int i = 0; i < this->m_vTemplateAsteroidMedium.size(); i++)
	{
		this->m_vTemplateAsteroidMedium[i]->Release();
		delete this->m_vTemplateAsteroidMedium[i];
		this->m_vTemplateAsteroidMedium[i] = NULL;
	}

	for (int i = 0; i < this->m_vTemplateAsteroidSmall.size(); i++)
	{
		this->m_vTemplateAsteroidSmall[i]->Release();
		delete this->m_vTemplateAsteroidSmall[i];
		this->m_vTemplateAsteroidSmall[i] = NULL;
	}

	/* SPRITES */

	// backgrounds

	if (this->m_pSpriteBackgroundBottom)
	{
		this->m_pSpriteBackgroundBottom->Release();
		delete this->m_pSpriteBackgroundBottom;
		this->m_pSpriteBackgroundBottom = NULL;
	}

	if (this->m_pSpriteBackgroundMiddle)
	{
		this->m_pSpriteBackgroundMiddle->Release();
		delete this->m_pSpriteBackgroundMiddle;
		this->m_pSpriteBackgroundMiddle = NULL;
	}

	if (this->m_pSpriteBackgroundTop)
	{
		this->m_pSpriteBackgroundTop->Release();
		delete this->m_pSpriteBackgroundTop;
		this->m_pSpriteBackgroundTop = NULL;
	}

	/* OTHERS */

#ifdef SHADOWS
	if (this->m_pShadowVolumes)
	{
		delete[] this->m_pShadowVolumes;
		this->m_pShadowVolumes = NULL;
	}
#endif

	if (this->m_pXFile)
	{
		delete[] this->m_pXFile;
		this->m_pXFile = NULL;
	}

	if (this->m_pHudObject)
	{
		for (int i = 0; i < LOAD_CONTAINER_HUD_MAX; i++)
		{
			(this->m_pHudObject + i)->Release();
		}
		delete[] this->m_pHudObject;
		this->m_pHudObject = NULL;
	}

	if (this->m_pNumbersScore)
	{
		for (int i = 0; i < LOAD_CONTAINER_NUMBER_MAX; i++)
		{
			(this->m_pNumbersScore + i)->Release();
		}
		delete[] this->m_pNumbersScore;
		this->m_pNumbersScore = NULL;
	}

	if (this->m_pNumbersTime)
	{
		for (int i = 0; i < LOAD_CONTAINER_NUMBER_MAX; i++)
		{
			(this->m_pNumbersTime + i)->Release();
		}
		delete[] this->m_pNumbersTime;
		this->m_pNumbersTime = NULL;
	}

	if (this->m_pLaunchEnemies)
	{
		this->ClearLaunchEnemies();
	}

	if (this->m_pStrikeEnemies)
	{
		this->ClearStrikeEnemies();
	}

	this->m_pBullets.Clear();
	this->m_pActiveEnemies.Clear();
	this->m_pReinforcements.Clear();
	this->m_pObstacleEnemies.Clear();

	ClearLevelObstacles();

	// explosions
	this->m_pExplosions->Release();
	delete this->m_pExplosions;
	this->m_pExplosions = NULL;

	//this->m_pParticles.Clear();

	/* LEVEL & SETTINGS */

	if (this->m_pLevel)
	{
		this->m_pLevel->Release();
		delete this->m_pLevel;
		this->m_pLevel = NULL;
	}

	if (this->m_pGameSettings)
	{
		delete this->m_pGameSettings;
		this->m_pGameSettings = NULL;
	}

	// stop and free all the music
	this->StopMusicAll();

	this->m_pTheApp = NULL;
	this->m_pState = NULL;
	this->m_pJoystick = NULL;
}

void CTheGame::LoadSprites()
{
	switch( this->m_pState->GetSpriteSteps() )
	{
	// level titles
	case 1:
		this->m_pSpriteLevelTitleSpace = this->m_pResourceGame->GetSpriteLevelTitleSpace();
		break;
	// boss warning
	case 2:
		this->m_pSpriteBossWarningSpace = this->m_pResourceGame->GetSpriteBossWarningSpace();
		break;
	// player afterburn
	case 3:
		this->m_pSpritePlayerAfterburn = this->m_pResourceGame->GetSpriteGamePlayerAfterburn();
		break;
	// player cannon
	case 4:
		this->m_pSpriteInfoPlayerCannonChargeSmall = this->m_pResourceGame->GetSpritePlayerCannonChargeSmall();
		break;
	case 5:
		this->m_pSpriteInfoPlayerCannonChargeMedium = this->m_pResourceGame->GetSpritePlayerCannonChargeMedium();
		break;
	case 6:
		this->m_pSpriteInfoPlayerCannonChargeLarge = this->m_pResourceGame->GetSpritePlayerCannonChargeLarge();
		break;
	case 7:
		this->m_pSpriteInfoPlayerCannonBeamCenter = this->m_pResourceGame->GetSpritePlayerCannonBeamCenter();
		break;
	case 8:
		this->m_pSpriteInfoPlayerCannonBeamLeft = this->m_pResourceGame->GetSpritePlayerCannonBeamLeft();
		break;
	case 9:
		this->m_pSpriteInfoPlayerCannonBeamRight = this->m_pResourceGame->GetSpritePlayerCannonBeamRight();
		break;
	// player blast
	case 10:
		this->m_pSpritePlayerBlast = this->m_pResourceGame->GetSpritePlayerBlast();
		break;
	// enemy afterburn
	case 11:
		this->m_pSpriteEnemyAfterburn = this->m_pResourceGame->GetSpriteEnemyAfterburn();
	// boss sprites
	case 12:
		this->m_pSpriteBoss1CannonCharge = this->m_pResourceGame->GetSpriteBoss1CannonCharge();
		break;
	case 13:
		this->m_pSpriteBoss1CannonShoot = this->m_pResourceGame->GetSpriteBoss1CannonShoot();
		break;
	// explosions
	case 14:
		this->m_pSpriteExplosionPlayer = this->m_pResourceGame->GetSpriteExplosionPlayer();
		break;
	case 15:
		this->m_pSpriteExplosionDrone = this->m_pResourceGame->GetSpriteExplosionDrone();
		break;
	case 16:
		this->m_pSpriteExplosionSniper = this->m_pResourceGame->GetSpriteExplosionSniper();
		break;
	case 17:
		this->m_pSpriteExplosionRoller = this->m_pResourceGame->GetSpriteExplosionRoller();
		break;
	case 18:
		//this->m_pSpriteExplosionGuard = this->m_pResourceGame->GetSpriteExplosionGuard();
		break;
	case 19:
		this->m_pSpriteExplosionBossBig = this->m_pResourceGame->GetSpriteExplosionBossBig();
		break;
	case 20:
		this->m_pSpriteExplosionBossPart = this->m_pResourceGame->GetSpriteExplosionBossPart();
		break;
	case 21:
		this->m_pSpriteExplosionBossChain1 = this->m_pResourceGame->GetSpriteExplosionBossChain1();
		break;
	case 22:
		this->m_pSpriteExplosionBossChain2 = this->m_pResourceGame->GetSpriteExplosionBossChain2();
		break;
	case 23:
		this->m_pSpriteExplosionBossChain3 = this->m_pResourceGame->GetSpriteExplosionBossChain3();
		break;
	// game info
	case 24:
		this->m_pSpriteInfoPlayerLives = this->m_pResourceGame->GetSpriteInfoPlayerLives();
		break;
	case 25:
		this->m_pSpriteInfoPlayerBlasts = this->m_pResourceGame->GetSpriteInfoPlayerBlasts();
		break;
	case 26:
		this->m_pSpriteInfoPlayerHealth = this->m_pResourceGame->GetSpriteInfoPlayerHealth();
		break;
	case 27:
		this->m_pSpriteInfoPlayerCannon = this->m_pResourceGame->GetSpriteInfoPlayerCannon();
		break;
	// game endings
	case 28:
		this->m_pSpriteGameOverText = this->m_pResourceGame->GetSpriteGameOverText();
		break;
	case 29:
		this->m_pSpriteGameWonText = this->m_pResourceGame->GetSpriteGameWonText();
		break;
	}
}

HRESULT CTheGame::LoadSpritesBackground()
{
	HRESULT hres = S_OK;

	// bottom background
	/*
	if(this->m_pSpriteBackgroundBottom)
	{
		this->m_pSpriteBackgroundBottom->Release();
		this->m_pSpriteBackgroundBottom = NULL;
	}

	this->m_pSpriteBackgroundBottom = new CSprite;

	if( !this->m_pSpriteBackgroundBottom )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pSpriteBackgroundBottom->Create(
		"background_bottom.png",
		this->m_pTheApp->GetDevice(),
		this->m_fDepthBackgroundBottom);

	if(FAILED(hres))
	{
		this->m_pState->GetResources()->UnloadInGameBackground();
		return hres;
	}
	*/

	// middle background

	if(this->m_pSpriteBackgroundMiddle)
	{
		this->m_pSpriteBackgroundMiddle->Release();
		delete this->m_pSpriteBackgroundMiddle;
		this->m_pSpriteBackgroundMiddle = NULL;
	}

	this->m_pSpriteBackgroundMiddle = new CSpriteScrolling;

	if( !this->m_pSpriteBackgroundMiddle )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pSpriteBackgroundMiddle->Create(
		"background_middle.png", this->m_pTheApp->GetDevice(),
		CSpriteScrolling::eDIRECTION_DOWN,
		true, this->m_fDepthBackgroundMiddle,
		1024, 2304, 0,0,
		this->m_pLevel->GetBackgroundMiddleSpeed(),
		this->m_pLevel->GetBackgroundMiddlePause());

	if(FAILED(hres))
	{
		return hres;
	}

	// top background

	if(this->m_pSpriteBackgroundTop)
	{
		this->m_pSpriteBackgroundTop->Release();
		delete this->m_pSpriteBackgroundTop;
		this->m_pSpriteBackgroundTop = NULL;
	}

	this->m_pSpriteBackgroundTop = new CSpriteScrolling;

	if( !this->m_pSpriteBackgroundTop )
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pSpriteBackgroundTop->Create(
		"background_top.png", this->m_pTheApp->GetDevice(),
		CSpriteScrolling::eDIRECTION_DOWN,
		true, this->m_fDepthBackgroundTop,
		1024, 2304, 0,0,
		this->m_pLevel->GetBackgroundTopSpeedEnemies(),
		this->m_pLevel->GetBackgroundTopPauseEnemies());

	return hres;
}

HRESULT CTheGame::LoadMeshes()
{
	HRESULT hres = S_OK;
	CResourceMenus* resourceMenus = this->m_pTheApp->GetResourceMenus();

	if(this->m_pState->GetMeshSteps() == 1)
	{
		this->m_pXFile = new CXFileContainer[LOAD_MESH_GAME_MAX];

		if(!this->m_pXFile)
		{
			return E_OUTOFMEMORY;
		}
	}

	switch( this->m_pState->GetMeshSteps() )
	{
	/* NUMBERS */

	case 1:
		this->m_pXFile[LOAD_MESH_GAME_0] = resourceMenus->GetMeshNumber0();
		break;
	case 2:
		this->m_pXFile[LOAD_MESH_GAME_1] = resourceMenus->GetMeshNumber1();
		break;
	case 3:
		this->m_pXFile[LOAD_MESH_GAME_2] = resourceMenus->GetMeshNumber2();
		break;
	case 4:
		this->m_pXFile[LOAD_MESH_GAME_3] = resourceMenus->GetMeshNumber3();
		break;
	case 5:
		this->m_pXFile[LOAD_MESH_GAME_4] = resourceMenus->GetMeshNumber4();
		break;
	case 6:
		this->m_pXFile[LOAD_MESH_GAME_5] = resourceMenus->GetMeshNumber5();
		break;
	case 7:
		this->m_pXFile[LOAD_MESH_GAME_6] = resourceMenus->GetMeshNumber6();
		break;
	case 8:
		this->m_pXFile[LOAD_MESH_GAME_7] = resourceMenus->GetMeshNumber7();
		break;
	case 9:
		this->m_pXFile[LOAD_MESH_GAME_8] = resourceMenus->GetMeshNumber8();
		break;
	case 10:
		this->m_pXFile[LOAD_MESH_GAME_9] = resourceMenus->GetMeshNumber9();
		break;
	}

	return hres;
}

HRESULT CTheGame::InitLevelBoss()
{
	HRESULT hres = S_OK;

	/* RELEASE BOSS */

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 2:
	case 3:

		if( this->m_pEnemyBoss1Frame )
		{
			this->m_pEnemyBoss1Frame->Release();
			delete this->m_pEnemyBoss1Frame;
			this->m_pEnemyBoss1Frame = NULL;
		}
		if( this->m_pEnemyBoss1ScatterLeft )
		{
			this->m_pEnemyBoss1ScatterLeft->Release();
			delete this->m_pEnemyBoss1ScatterLeft;
			this->m_pEnemyBoss1ScatterLeft = NULL;
		}
		if( this->m_pEnemyBoss1ScatterRight )
		{
			this->m_pEnemyBoss1ScatterRight->Release();
			delete this->m_pEnemyBoss1ScatterRight;
			this->m_pEnemyBoss1ScatterRight = NULL;
		}
		if( this->m_pEnemyBoss1Cannon )
		{
			this->m_pEnemyBoss1Cannon->Release();
			delete this->m_pEnemyBoss1Cannon;
			this->m_pEnemyBoss1Cannon = NULL;
		}

		break;
	}

	/* CREATE LEVEL BOSS */

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
	case 2:
	case 3:

		// BOSS 1 FRAME //

		// create object
		this->m_pEnemyBoss1Frame = new CEnemyBoss1Frame(IEnemy::eTYPE_BOSS_1_FRAME,
														IEnemy::eBEHAVIOUR_BOSS);
		if( !this->m_pEnemyBoss1Frame )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1Frame->Create(this->m_pTheApp, this->m_pGameSettings,
												this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_FRAME),
												this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_FRAME),
												this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_FRAME),
												this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// set sound effect volume
		this->m_pEnemyBoss1Frame->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);

		// initialize movement rotation values
		this->m_pEnemyBoss1Frame->InitRotationValues();

		// set starting position
		this->m_pEnemyBoss1Frame->SetPosition(D3DXVECTOR3
			(	0.0f,
				this->m_fScreenHeight + (this->m_pEnemyBoss1Frame->GetHeight() / 2.0f) + 25.0f,
				this->m_pEnemyBoss1Frame->GetDepthValue(5)));

		// set activity
		this->m_pEnemyBoss1Frame->SetActive(TRUE);
		this->m_pEnemyBoss1Frame->SetVisible(FALSE);

		// BOSS 1 CORE //

		this->m_pEnemyBoss1Core = new CEnemyBoss1Core(	IEnemy::eTYPE_BOSS_1_CORE,
														IEnemy::eBEHAVIOUR_BOSS);
		if( !this->m_pEnemyBoss1Core )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1Core->Create(	this->m_pTheApp, this->m_pGameSettings,
												this->m_pTheApp->GetDevice(),
												this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_CORE),
												this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_CORE),
												this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_CORE),
												this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// add to boss 1 frame
		this->m_pEnemyBoss1Frame->AddChild(this->m_pEnemyBoss1Core);
		// set activity
		this->m_pEnemyBoss1Core->SetActive(TRUE);

		// BOSS 1 LASER LEFT //

		// create object
		this->m_pEnemyBoss1LaserLeft = new CEnemyBoss1Laser(IEnemy::eTYPE_BOSS_1_LASER_LEFT,
															IEnemy::eBEHAVIOUR_BOSS,
															CEnemyBoss1Laser::eSIDE_LEFT);
		if( !this->m_pEnemyBoss1LaserLeft )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1LaserLeft->Create(this->m_pTheApp, this->m_pGameSettings,
													this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_LASER_LEFT),
													this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_LASER_LEFT),
													this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_LASER_LEFT),
													this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize weapons
		hres = this->m_pEnemyBoss1LaserLeft->InitWeapons(	this->m_pTheApp,
															this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletWidth,
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletHeight,
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletSpeed,
															this->m_pGameSettings->m_iEnemyBoss1LaserBulletDamage);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize position
		this->m_pEnemyBoss1LaserLeft->InitPosition(this->m_pEnemyBoss1Frame->GetPosition());
		// set sound effect volume
		this->m_pEnemyBoss1LaserLeft->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);
		// set activity
		this->m_pEnemyBoss1LaserLeft->SetActive(TRUE);

		// BOSS 1 LASER RIGHT //

		// create object
		this->m_pEnemyBoss1LaserRight = new CEnemyBoss1Laser(	IEnemy::eTYPE_BOSS_1_LASER_RIGHT,
																IEnemy::eBEHAVIOUR_BOSS,
																CEnemyBoss1Laser::eSIDE_RIGHT);
		if( !this->m_pEnemyBoss1LaserRight )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1LaserRight->Create(	this->m_pTheApp, this->m_pGameSettings,
														this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_LASER_RIGHT),
														this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_LASER_RIGHT),
														this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_LASER_RIGHT),
														this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize weapons
		hres = this->m_pEnemyBoss1LaserRight->InitWeapons(	this->m_pTheApp,
															this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_BOSS_1_LASER),
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletWidth,
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletHeight,
															this->m_pGameSettings->m_fEnemyBoss1LaserBulletSpeed,
															this->m_pGameSettings->m_iEnemyBoss1LaserBulletDamage);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize position
		this->m_pEnemyBoss1LaserRight->InitPosition(this->m_pEnemyBoss1Frame->GetPosition());
		// set sound effect volume
		this->m_pEnemyBoss1LaserRight->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);
		// set activity
		this->m_pEnemyBoss1LaserRight->SetActive(TRUE);

		// BOSS 1 SCATTER LEFT //

		// create object
		this->m_pEnemyBoss1ScatterLeft = new CEnemyBoss1Scatter(IEnemy::eTYPE_BOSS_1_SCATTER_LEFT,
																IEnemy::eBEHAVIOUR_BOSS,
																CEnemyBoss1Scatter::eSIDE_LEFT);
		if( !this->m_pEnemyBoss1ScatterLeft )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1ScatterLeft->Create(	this->m_pTheApp, this->m_pGameSettings,
														this->m_pEnemyBoss1Frame,
														this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize weapons
		hres = this->m_pEnemyBoss1ScatterLeft->InitWeapons(	this->m_pTheApp,
															this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletWidth,
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletHeight,
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletSpeed,
															this->m_pGameSettings->m_iEnemyBoss1ScatterBulletDamage);
		if( FAILED(hres) )
		{
			return hres;
		}

		// set sound effect volume
		this->m_pEnemyBoss1ScatterLeft->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);
		// set activity
		this->m_pEnemyBoss1ScatterLeft->SetActive(TRUE);

		// BOSS 1 SCATTER RIGHT //

		// create object
		this->m_pEnemyBoss1ScatterRight = new CEnemyBoss1Scatter(	IEnemy::eTYPE_BOSS_1_SCATTER_RIGHT,
																	IEnemy::eBEHAVIOUR_BOSS,
																	CEnemyBoss1Scatter::eSIDE_RIGHT);
		if( !this->m_pEnemyBoss1ScatterRight )
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pEnemyBoss1ScatterRight->Create(	this->m_pTheApp, this->m_pGameSettings,
														this->m_pEnemyBoss1Frame,
														this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_SCATTER),
														this->m_iVolumeSoundEffect);
		if( FAILED(hres) )
		{
			return hres;
		}

		// initialize weapons
		hres = this->m_pEnemyBoss1ScatterRight->InitWeapons(this->m_pTheApp,
															this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BULLET_BOSS_1_SCATTER),
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletWidth,
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletHeight,
															this->m_pGameSettings->m_fEnemyBoss1ScatterBulletSpeed,
															this->m_pGameSettings->m_iEnemyBoss1ScatterBulletDamage);
		if( FAILED(hres) )
		{
			return hres;
		}

		// set sound effect volume
		this->m_pEnemyBoss1ScatterRight->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);
		// set activity
		this->m_pEnemyBoss1ScatterRight->SetActive(TRUE);

		// BOSS 1 CANNON //

		// create object
		this->m_pEnemyBoss1Cannon = new CEnemyBoss1Cannon(	IEnemy::eTYPE_BOSS_1_CANNON,
															IEnemy::eBEHAVIOUR_BOSS);
		if( !this->m_pEnemyBoss1Cannon )
		{
			return E_OUTOFMEMORY;
		}

		this->m_pEnemyBoss1Cannon->Create(	this->m_pTheApp, this->m_pGameSettings,
											this->m_pResourceGame->GetMesh(CResources::MODEL_GAME_BOSS_1_CANNON),
											this->m_pResourceGame->GetMaterial(CResources::MODEL_GAME_BOSS_1_CANNON),
											this->m_pResourceGame->GetTexture(CResources::MODEL_GAME_BOSS_1_CANNON),
											this->m_iVolumeSoundEffect);

		// initialize weapons
		this->m_pEnemyBoss1Cannon->InitWeapons(	this->m_pSpriteBoss1CannonCharge,
												this->m_pSpriteBoss1CannonShoot);

		// set sound effect volume
		this->m_pEnemyBoss1Cannon->SetVolumeSoundEffect(this->m_iVolumeSoundEffect);
		// set activity
		this->m_pEnemyBoss1Cannon->SetActive(TRUE);

		break;
	}

	/* COLLISION MODELS */

	hres = this->CreateCollisionMeshBoss();
	if( FAILED(hres) )
	{
		return hres;
	}

	// to make the boss assume it's starting position
	UpdateBoss(0.0f);

	return hres;
}

CObstacle* CTheGame::CreateTemplateObstacle(int mapKey, float objectWidth, float objectHeight)
{
	CObstacle* templateObject = new CObstacle();

	if (!templateObject)
	{
		return NULL;
	}

	templateObject->Create(
		this->m_pTheApp,
		this->m_pResourceGame->GetMesh(mapKey),
		this->m_pResourceGame->GetMaterial(mapKey),
		this->m_pResourceGame->GetTexture(mapKey),
		objectWidth,
		objectHeight,
		this->m_fScreenWidth,
		this->m_fScreenHeight);

	return templateObject;
}

HRESULT CTheGame::InitLevelObstacles()
{
	HRESULT hres = S_OK;

	/** ASTEROIDS **/

	if(	this->m_pLevel->GetLevelNumber() == 2 || 
		this->m_pLevel->GetLevelNumber() == 3)
	{
		switch (this->m_iLoadLevelAsteroidStep)
		{
		case LOAD_LEVEL_ASTEROID_BIG:
		{
			if (m_vTemplateAsteroidBig.size() == 0)
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ASTEROID_BIG_1;
					float objectWidth = this->m_pGameSettings->m_fAsteroidBig1Width;
					float objectHeight = this->m_pGameSettings->m_fAsteroidBig1Height;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ASTEROID_BIG_2;
						objectWidth = this->m_pGameSettings->m_fAsteroidBig2Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidBig2Height;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ASTEROID_BIG_3;
						objectWidth = this->m_pGameSettings->m_fAsteroidBig3Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidBig3Height;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ASTEROID_BIG_4;
						objectWidth = this->m_pGameSettings->m_fAsteroidBig4Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidBig4Height;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ASTEROID_BIG_5;
						objectWidth = this->m_pGameSettings->m_fAsteroidBig5Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidBig5Height;
						break;
					}

					CObstacle* templateObject = CreateTemplateObstacle(mapKey, objectWidth, objectHeight);

					if (templateObject == NULL)
					{
						return E_OUTOFMEMORY;
					}

					m_vTemplateAsteroidBig.push_back(templateObject);
				}
			}
		}
		break;

		case LOAD_LEVEL_ASTEROID_MEDIUM:
		{
			if (m_vTemplateAsteroidMedium.size() == 0)
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ASTEROID_MEDIUM_1;
					float objectWidth = this->m_pGameSettings->m_fAsteroidMedium1Width;
					float objectHeight = this->m_pGameSettings->m_fAsteroidMedium1Height;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ASTEROID_MEDIUM_2;
						objectWidth = this->m_pGameSettings->m_fAsteroidMedium2Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidMedium2Height;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ASTEROID_MEDIUM_3;
						objectWidth = this->m_pGameSettings->m_fAsteroidMedium3Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidMedium3Height;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ASTEROID_MEDIUM_4;
						objectWidth = this->m_pGameSettings->m_fAsteroidMedium4Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidMedium4Height;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ASTEROID_MEDIUM_5;
						objectWidth = this->m_pGameSettings->m_fAsteroidMedium5Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidMedium5Height;
						break;
					}

					CObstacle* templateObject = CreateTemplateObstacle(mapKey, objectWidth, objectHeight);

					if (templateObject == NULL)
					{
						return E_OUTOFMEMORY;
					}

					m_vTemplateAsteroidMedium.push_back(templateObject);
				}
			}
		}
		break;

		case LOAD_LEVEL_ASTEROID_SMALL:
		{
			if (m_vTemplateAsteroidSmall.size() == 0)
			{
				for (int depth = 1; depth <= 5; depth++)
				{
					int mapKey = CResources::MODEL_GAME_ASTEROID_SMALL_1;
					float objectWidth = this->m_pGameSettings->m_fAsteroidSmall1Width;
					float objectHeight = this->m_pGameSettings->m_fAsteroidSmall1Height;

					switch (depth)
					{
					case 2:
						mapKey = CResources::MODEL_GAME_ASTEROID_SMALL_2;
						objectWidth = this->m_pGameSettings->m_fAsteroidSmall2Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidSmall2Height;
						break;
					case 3:
						mapKey = CResources::MODEL_GAME_ASTEROID_SMALL_3;
						objectWidth = this->m_pGameSettings->m_fAsteroidSmall3Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidSmall3Height;
						break;
					case 4:
						mapKey = CResources::MODEL_GAME_ASTEROID_SMALL_4;
						objectWidth = this->m_pGameSettings->m_fAsteroidSmall4Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidSmall4Height;
						break;
					case 5:
						mapKey = CResources::MODEL_GAME_ASTEROID_SMALL_5;
						objectWidth = this->m_pGameSettings->m_fAsteroidSmall5Width;
						objectHeight = this->m_pGameSettings->m_fAsteroidSmall5Height;
						break;
					}

					CObstacle* templateObject = CreateTemplateObstacle(mapKey, objectWidth, objectHeight);

					if (templateObject == NULL)
					{
						return E_OUTOFMEMORY;
					}

					m_vTemplateAsteroidSmall.push_back(templateObject);
				}
			}
		}
		break;
		}

		this->m_iLoadLevelAsteroidStep++;
	}

	return hres;
}

void CTheGame::InitVolumeSoundEffect()
{
	// master sound effect volume

	int iVolume = this->m_pTheApp->GetConfig().GetVolumeSoundEffect();

	if(iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		this->m_iVolumeSoundEffect = (iVolume - 100) * 50;
	}

	// specific sound effect volumes

	if (iVolume == 0)
	{
		this->m_iVolumePlayerMinigunShoot = -10000;
		this->m_iVolumePlayerMinigunTurn = -10000;
		this->m_iVolumePlayerCannon = -10000;
		this->m_iVolumePlayerBlast = -10000;
		this->m_iVolumePlayerVelocityAfterburn = -10000;
	}
	else
	{
		float fVolume = this->m_pGameSettings->m_fVolumePlayerMinigunShoot * (float)iVolume;
		float fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumePlayerMinigunShoot = (int)fExactVolume;

		fVolume = this->m_pGameSettings->m_fVolumePlayerMinigunTurn * (float)iVolume;
		fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumePlayerMinigunTurn = (int)fExactVolume;

		fVolume = this->m_pGameSettings->m_fVolumePlayerCannon * (float)iVolume;
		fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumePlayerCannon = (int)fExactVolume;

		fVolume = this->m_pGameSettings->m_fVolumePlayerBlast * (float)iVolume;
		fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumePlayerBlast = (int)fExactVolume;

		fVolume = this->m_pGameSettings->m_fVolumePlayerVelocityAfterburn * (float)iVolume;
		fExactVolume = (fVolume - 100.0f) * 50.0f;
		this->m_iVolumePlayerVelocityAfterburn = (int)fExactVolume;
	}
}

void CTheGame::LoadMusicLevel()
{
	//START*********** LOAD LEVEL MUSIC *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		// music player is active
		if(this->m_pTheApp->GetMP3Player1().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player1().Stop();
		}

		this->m_pTheApp->GetMP3Player1().Release();

		LPCTSTR resourceFilePath = NULL;

		switch(this->m_pLevel->GetLevelNumber())
		{
		case 1:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/level_1.mp3");
			break;
		case 2:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/level_2.mp3");
			break;
		case 3:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/level_3.mp3");
			break;
		}

		// load level music
		if (resourceFilePath != NULL)
		{
			this->m_pTheApp->GetMP3Player1().Create(resourceFilePath);
			this->m_pTheApp->GetMP3Player1().SetVolume(this->m_pTheApp->GetVolumeMusic());
		}
	}

	//END************* LOAD LEVEL MUSIC *****************//
}

void CTheGame::LoadMusicBoss()
{
	//START*********** LOAD BOSS MUSIC *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		// music player is active
		if(this->m_pTheApp->GetMP3Player2().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player2().Stop();
		}

		this->m_pTheApp->GetMP3Player2().Release();

		LPCTSTR resourceFilePath = NULL;

		switch(this->m_pLevel->GetLevelNumber())
		{
		case 1:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/boss_1.mp3");
			break;
		case 2:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/boss_2.mp3");
			break;
		case 3:
			resourceFilePath = this->m_pResourceGame->GetUnpackedResourceFilePath("music/boss_3.mp3");
			break;
		}

		// load boss music
		if (resourceFilePath != NULL)
		{
			this->m_pTheApp->GetMP3Player2().Create(resourceFilePath);
			this->m_pTheApp->GetMP3Player2().SetVolume(this->m_pTheApp->GetVolumeMusic());
		}
	}

	//END************* LOAD BOSS MUSIC *****************//
}

void CTheGame::CheckMusicEnd()
{
	bool bChangePosition = false;

	if(	(this->m_iGameState == GAME_STATE_BOSS_INTRO) || 
		(this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
		(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
		(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
	{
		if( this->m_pTheApp->GetMP3Player2().IsAtEnd() )
		{
			this->m_pTheApp->GetMP3Player2().Stop();
			bChangePosition = true;
		}
	}
	else
	{
		if( this->m_pTheApp->GetMP3Player1().IsAtEnd() )
		{
			this->m_pTheApp->GetMP3Player1().Stop();
			bChangePosition = true;
		}
	}

	if(bChangePosition)
	{
		this->RestartMusic();
	}
}

void CTheGame::RestartMusic()
{
	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		// restart boss music
		if(	(this->m_iGameState == GAME_STATE_BOSS_INTRO) || 
			(this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			this->m_pTheApp->GetMP3Player2().SetPosition(12.450);
			this->m_pTheApp->GetMP3Player2().Play();
		}
		// restart level music
		else
		{
			this->m_pTheApp->GetMP3Player1().SetPosition(16.1270);
			this->m_pTheApp->GetMP3Player1().Play();
		}

		break;

	case 2:

		// restart boss music
		if(	(this->m_iGameState == GAME_STATE_BOSS_INTRO) || 
			(this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			this->m_pTheApp->GetMP3Player2().SetPosition(92.990);
			this->m_pTheApp->GetMP3Player2().Play();
		}
		// restart level music
		else
		{
			this->m_pTheApp->GetMP3Player1().SetPosition(41.1410);
			this->m_pTheApp->GetMP3Player1().Play();
		}

		break;

	case 3:

		// restart boss music
		if(	(this->m_iGameState == GAME_STATE_BOSS_INTRO) || 
			(this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			this->m_pTheApp->GetMP3Player2().SetPosition(95.935);
			this->m_pTheApp->GetMP3Player2().Play();
		}
		// restart level music
		else
		{
			this->m_pTheApp->GetMP3Player1().SetPosition(47.290);
			this->m_pTheApp->GetMP3Player1().Play();
		}

		break;
	}
}

void CTheGame::PlayMusicLevel()
{
	//START************ PLAY MUSIC LEVEL *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		this->m_pTheApp->GetMP3Player1().Play();
	}

	//END************** PLAY MUSIC LEVEL *****************//
}

void CTheGame::PlayMusicBoss()
{
	//START************ PLAY MUSIC LEVEL *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		this->m_pTheApp->GetMP3Player2().Play();
	}

	//END************** PLAY MUSIC LEVEL *****************//
}

void CTheGame::PlayMusicGameOutro()
{
	//START************ PLAY ENDING MUSIC *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		//this->m_pTheApp->GetMP3Player().Create(_T("music\\outro.mp3"));
		//this->m_pTheApp->GetMP3Player().Play();
	}

	//END************** PLAY ENDING MUSIC *****************//
}

void CTheGame::PlayMusicGameOver()
{
	//START************** PLAY GAME OVER MUSIC *******************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		//this->m_pTheApp->GetMP3Player().Create(_T("music\\game_over.mp3"));
		//this->m_pTheApp->GetMP3Player().Play();
	}

	//END**************** PLAY GAME OVER MUSIC *******************//
}

bool CTheGame::FadeOutMusicLevel(float fFrametime)
{
	bool bFadeOutMusic = true;

	// fade out music
	if(this->m_pTheApp->VolumeMusicFadeOut(fFrametime))
	{
		// set music volume
		this->m_pTheApp->GetMP3Player1().SetVolume( this->m_pTheApp->GetVolumeMusic() );
	}
	// fade out finished
	else
	{
		// set music volume, it's now back to original volume
		this->m_pTheApp->GetMP3Player1().SetVolume( this->m_pTheApp->GetVolumeMusic() );
		this->m_pTheApp->GetMP3Player2().SetVolume( this->m_pTheApp->GetVolumeMusic() );

		bFadeOutMusic = false;
	}

	return bFadeOutMusic;
}

bool CTheGame::FadeOutMusicBoss(float fFrametime)
{
	bool bFadeOutMusic = true;

	// fade out music
	if(this->m_pTheApp->VolumeMusicFadeOut(fFrametime))
	{
		// set music volume
		this->m_pTheApp->GetMP3Player2().SetVolume( this->m_pTheApp->GetVolumeMusic() );
	}
	// fade out finished
	else
	{
		// set music volume, it's now back to original volume
		this->m_pTheApp->GetMP3Player1().SetVolume( this->m_pTheApp->GetVolumeMusic() );
		this->m_pTheApp->GetMP3Player2().SetVolume( this->m_pTheApp->GetVolumeMusic() );

		bFadeOutMusic = false;
	}

	return bFadeOutMusic;
}

void CTheGame::StopMusicLevel()
{
	//START*********** STOP MUSIC LEVEL *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		// music player 1 is active
		if(this->m_pTheApp->GetMP3Player1().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player1().Stop();
			// set music volume, to make sure it's back in original volume (after fade-out)
			this->m_pTheApp->GetMP3Player1().SetVolume( this->m_pTheApp->GetVolumeMusic() );
		}
	}

	//END************* STOP MUSIC LEVEL *****************//
}

void CTheGame::StopMusicBoss()
{
	//START*********** STOP MUSIC BOSS *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		// music player 2 is active
		if(this->m_pTheApp->GetMP3Player2().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player2().Stop();
			// set music volume, to make sure it's back in original volume (after fade-out)
			this->m_pTheApp->GetMP3Player2().SetVolume( this->m_pTheApp->GetVolumeMusic() );
		}
	}

	//END************* STOP MUSIC BOSS *****************//
}

void CTheGame::StopMusicAll()
{
	//START*********** STOP MUSIC ALL *****************//

	// music has volume
	if(this->m_pTheApp->GetConfig().GetVolumeMusic() > 0)
	{
		// music player 1 is active
		if(this->m_pTheApp->GetMP3Player1().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player1().Stop();
		}
		// music player 2 is active
		if(this->m_pTheApp->GetMP3Player2().GetState() == 1)
		{
			// stop current music
			this->m_pTheApp->GetMP3Player2().Stop();
		}
	}

	//END************* STOP MUSIC ALL *****************//
}

void CTheGame::PlaySoundPlayerAfterburn()
{
	if (this->m_iGameState == GAME_STATE_LEVEL_INTRO)
	{
		this->m_pTheApp->GetWave(SOUND_PLAYER_ENTER_AFTERBURN).Play(FALSE, 0, this->m_iVolumeSoundEffect);
	}
	else if (this->m_iGameState == GAME_STATE_LEVEL_OUTRO)
	{
		this->m_pTheApp->GetWave(SOUND_PLAYER_LEAVE_AFTERBURN).Play(FALSE, 0, this->m_iVolumeSoundEffect);
	}
	else
	{
		this->m_pTheApp->GetWave(SOUND_PLAYER_LEAVE_AFTERBURN).Play(FALSE, 0, this->m_iVolumePlayerVelocityAfterburn);
	}
}

void CTheGame::PlaySoundPlayerCannonCharge()
{
	//START******** PLAY SOUND PLAYER CANNON CHARGE ********//

	this->m_pTheApp->GetWave(SOUND_SHOOT_PLAYER_CANNON_CHARGE).Play(
		FALSE, 0, this->m_iVolumePlayerCannon);

	//END********** PLAY SOUND PLAYER CANNON CHARGE ********//
}

void CTheGame::PlaySoundPlayerCannonBeam()
{
	//START******** PLAY SOUND PLAYER CANNON BEAM ********//

	this->m_pTheApp->GetWave(SOUND_SHOOT_PLAYER_CANNON_BEAM).Play(
		FALSE, 0, this->m_iVolumePlayerCannon);

	//END********** PLAY SOUND PLAYER CANNON BEAM ********//
}

void CTheGame::PlaySoundFirePlayerMinigun()
{
	//START********** PLAY SOUND PLAYER MINIGUN **********//

	DWORD soundId = SOUND_SHOOT_PLAYER_MINIGUN_1;

	switch (this->m_pPlayer->GetMinigunSound())
	{
	case CPlayer::eMINIGUN_SOUND_BOOST_0_QUIET:
	case CPlayer::eMINIGUN_SOUND_BOOST_1_QUIET:
	case CPlayer::eMINIGUN_SOUND_BOOST_2_QUIET:
	case CPlayer::eMINIGUN_SOUND_BOOST_3_QUIET:
	case CPlayer::eMINIGUN_SOUND_BOOST_4_QUIET:
	case CPlayer::eMINIGUN_SOUND_BOOST_5_QUIET:
		soundId = SOUND_SHOOT_PLAYER_MINIGUN_2;
		break;
	}

	this->m_pTheApp->GetWave(soundId).Play(FALSE, NEXT_FREE_DUPLICATE, m_iVolumePlayerMinigunShoot);
	this->m_pPlayer->ChangeMinigunSound();

	//END************ PLAY SOUND PLAYER MINIGUN **********//
}

void CTheGame::PlaySoundFireEnemy(IEnemy* pEnemy)
{
	//START********** PLAY SOUND FIRE ENEMY **********//

	switch( pEnemy->GetType() )
	{
	case IEnemy::eTYPE_DRONE:

		switch( pEnemy->GetFiringSound() )
		{
		case IEnemy::eSOUND_FIRING_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_DRONE_1).Play(	FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;

		case IEnemy::eSOUND_FIRING_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_DRONE_2).Play(	FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;
		}
		break;

	case IEnemy::eTYPE_SNIPER:

		switch( pEnemy->GetFiringSound() )
		{
		case IEnemy::eSOUND_FIRING_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_SNIPER_1).Play(FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;

		case IEnemy::eSOUND_FIRING_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_SNIPER_2).Play(FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;
		}
		break;
	/*
	case IEnemy::eTYPE_ROLLER:

		switch( pEnemy->GetFiringSound() )
		{
		case IEnemy::eSOUND_FIRING_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_1).Play(FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;

		case IEnemy::eSOUND_FIRING_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_ROLLER_2).Play(FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;
		}
		break;

	case IEnemy::eTYPE_GUARD:

		switch( pEnemy->GetFiringSound() )
		{
		case IEnemy::eSOUND_FIRING_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_GUARD_1).Play(	FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;

		case IEnemy::eSOUND_FIRING_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_SHOOT_GUARD_2).Play(	FALSE,
																NEXT_FREE_DUPLICATE,
																this->m_iVolumeSoundEffect);
			break;
		}
		break;
		*/
	}

	pEnemy->ChangeFiringSound();

	//END************ PLAY SOUND FIRE ENEMY **********//
}

void CTheGame::PlaySoundHitPlayer()
{
	//START********** PLAY SOUND HIT PLAYER **********//

	switch( this->m_pPlayer->GetHitSound() )
	{
	case CPlayer::eHIT_SOUND_NORMAL:

		this->m_pTheApp->GetWave(SOUND_HIT_PLAYER_1).Play(	FALSE,
															NEXT_FREE_DUPLICATE,
															this->m_iVolumeSoundEffect);
		break;

	case CPlayer::eHIT_SOUND_QUIET:

		this->m_pTheApp->GetWave(SOUND_HIT_PLAYER_2).Play(	FALSE,
															NEXT_FREE_DUPLICATE,
															this->m_iVolumeSoundEffect);
		break;
	}

	this->m_pPlayer->ChangeHitSound();

	//END************ PLAY SOUND HIT PLAYER **********//
}

void CTheGame::PlaySoundHitEnemy(IEnemy* pEnemy)
{
	//START********** PLAY SOUND HIT ENEMY **********//

	switch( pEnemy->GetHitSound() )
	{
	case IEnemy::eSOUND_HIT_NORMAL:

		this->m_pTheApp->GetWave(SOUND_HIT_ENEMY_1).Play(	FALSE,
															NEXT_FREE_DUPLICATE,
															this->m_iVolumeSoundEffect);
		break;

	case IEnemy::eSOUND_HIT_QUIET:

		this->m_pTheApp->GetWave(SOUND_HIT_ENEMY_2).Play(	FALSE,
															NEXT_FREE_DUPLICATE,
															this->m_iVolumeSoundEffect);
		break;
	}

	pEnemy->ChangeHitSound();

	//END************ PLAY SOUND HIT ENEMY **********//
}

void CTheGame::PlaySoundHitBoss(IEnemy* pEnemy)
{
	//START********** PLAY SOUND HIT BOSS **********//

	switch( pEnemy->GetHitSound() )
	{
	case IEnemy::eSOUND_HIT_NORMAL:

		this->m_pTheApp->GetWave(SOUND_HIT_BOSS_1).Play(FALSE,
														NEXT_FREE_DUPLICATE,
														this->m_iVolumeSoundEffect);
		break;

	case IEnemy::eSOUND_HIT_QUIET:

		this->m_pTheApp->GetWave(SOUND_HIT_BOSS_2).Play(FALSE,
														NEXT_FREE_DUPLICATE,
														this->m_iVolumeSoundEffect);
		break;
	}

	pEnemy->ChangeHitSound();

	//END************ PLAY SOUND HIT BOSS **********//
}

void CTheGame::PlaySoundExplosionEnemy(IEnemy* pEnemy)
{
	//START********** PLAY SOUND EXPLOSION ENEMY **********//

	switch(pEnemy->GetType())
	{
	case IEnemy::eTYPE_DRONE:

		switch(this->m_eExplosionEnemy)
		{
		case eEXPLOSION_ENEMY_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_DRONE_1).Play(	FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_1;

			break;

		case eEXPLOSION_ENEMY_NORMAL_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_DRONE_2).Play(	FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_DRONE_3).Play(	FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_DRONE_4).Play(	FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;

			break;
		}

		break;

	case IEnemy::eTYPE_SNIPER:

		switch(this->m_eExplosionEnemy)
		{
		case eEXPLOSION_ENEMY_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_SNIPER_1).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_1;

			break;

		case eEXPLOSION_ENEMY_NORMAL_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_SNIPER_2).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_SNIPER_3).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_SNIPER_4).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;

			break;
		}

		break;

	case IEnemy::eTYPE_ROLLER:

		switch(this->m_eExplosionEnemy)
		{
		case eEXPLOSION_ENEMY_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_ROLLER_1).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);

			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_1;

			break;

		case eEXPLOSION_ENEMY_NORMAL_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_ROLLER_2).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);

			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_ROLLER_3).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_ROLLER_4).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;

			break;
		}

		break;
	/*
	case IEnemy::eTYPE_GUARD:

		switch(this->m_eExplosionEnemy)
		{
		case eEXPLOSION_ENEMY_NORMAL_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_GUARD_1).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_1;

			break;

		case eEXPLOSION_ENEMY_NORMAL_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_GUARD_2).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_QUIET_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_1:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_GUARD_3).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_2;

			break;

		case eEXPLOSION_ENEMY_QUIET_2:

			this->m_pTheApp->GetWave(SOUND_EXPLOSION_GUARD_4).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;

			break;
		}

		break;
	*/
	}

	//END************ PLAY SOUND EXPLOSION ENEMY **********//
}

void CTheGame::PlaySoundExplosionBossChain(int iWave)
{
	switch(iWave)
	{
	case 1:
		this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
		break;

	case 2:
		this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_2).Play(FALSE,
																	NEXT_FREE_DUPLICATE,
																	this->m_iVolumeSoundEffect);
		break;
	}
}

void CTheGame::PlaySoundExplosionBossPart()
{
	this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_PART).Play(	FALSE, 0,
																this->m_iVolumeSoundEffect);
}

void CTheGame::ResetSoundExplosionEnemy(float fFrametime)
{
	//START********** RESET SOUND EXPLOSION ENEMY **********//

	if(this->m_eExplosionEnemy != eEXPLOSION_ENEMY_NORMAL_1)
	{
		if(this->m_fEnemyExplosionSoundTimer <= 0.0f)
		{
			this->m_fEnemyExplosionSoundTimer = TIMER_SOUND_EXPLOSION_ENEMY;
			this->m_eExplosionEnemy = eEXPLOSION_ENEMY_NORMAL_1;

		}
		else
		{
			this->m_fEnemyExplosionSoundTimer -= fFrametime;
		}
	}

	//END************ RESET SOUND EXPLOSION ENEMY **********//
}


void CTheGame::CheckQuitGame(float fFrametime)
{
	bool bCheckJoystick = false;
	bool bCheckKeyboard = true;

	DWORD buttons = 0;

	if(SUCCEEDED(this->m_pJoystick->Update()))
	{
		bCheckJoystick = true;
	}

	if(this->m_iGameState != GAME_STATE_QUIT)
	{
		if(this->m_iGameState == GAME_STATE_END_SUCCESS)
		{
			if(this->m_fGameOverTimer <= 0.0f)
			{
				// joystick has priority over keyboard
				if(bCheckJoystick)
				{
					buttons = this->m_pJoystick->GetButtonCount();

					for(DWORD i = 0; i < buttons; i++)
					{
						if(this->m_pJoystick->GetButton(i))
						{
							// ends loop
							i = buttons;

							bCheckKeyboard = false;
							this->m_pTheApp->CheckKeyPushes();

							this->m_iGameStateEnd = GAME_STATE_END_SUCCESS;
							SwitchGameState(GAME_STATE_QUIT);
						}
					}
				}
				if(bCheckKeyboard)
				{
					if(	( ::GetAsyncKeyState(VK_SPACE) ) || 
						( ::GetAsyncKeyState(VK_RETURN) ) || 
						( ::GetAsyncKeyState(VK_ESCAPE) ))
					{
						this->m_pTheApp->CheckKeyPushes();

						this->m_iGameStateEnd = GAME_STATE_END_SUCCESS;
						SwitchGameState(GAME_STATE_QUIT);
					}
				}
			}
			else
			{
				this->m_fGameOverTimer -= fFrametime;
			}
		}
		else if(this->m_iGameState == GAME_STATE_END_FAILED)
		{
			if(this->m_fGameOverTimer <= 0.0f)
			{
				// joystick has priority over keyboard
				if(bCheckJoystick)
				{
					buttons = this->m_pJoystick->GetButtonCount();

					for(DWORD i = 0; i < buttons; i++)
					{
						if(this->m_pJoystick->GetButton(i))
						{
							// ends loop
							i = buttons;

							bCheckKeyboard = false;
							SwitchGameState(GAME_STATE_QUIT);
							
							
						}
					}
				}
				if(bCheckKeyboard)
				{
					if(	( ::GetAsyncKeyState(VK_SPACE) ) || 
						( ::GetAsyncKeyState(VK_RETURN) ) || 
						( ::GetAsyncKeyState(VK_ESCAPE) ))
					{
						SwitchGameState(GAME_STATE_QUIT);
					}
				}
			}
			else
			{
				this->m_fGameOverTimer -= fFrametime;
			}
		}
		else
		{
			if(this->m_iGameState != GAME_STATE_LEVEL_INTRO)
			{
				// quits a game when 'ESC' key is pressed
				if( ::GetAsyncKeyState(VK_ESCAPE) )
				{
					this->m_bFreezeQuit = true;
					this->m_pTheApp->CheckKeyPushes();

					SwitchGameState(GAME_STATE_QUIT);
				}
			}
		}
	}
}

void CTheGame::CheckGameOver()
{
	//START********* CHECK GAME OVER *******************//

	if( this->m_pPlayer->GameOver() )
	{
		this->m_iGameStateEnd = GAME_STATE_END_FAILED;
		SwitchGameState(GAME_STATE_END_FAILED);
	}

	//END********* CHECK GAME OVER *******************//
}

bool CTheGame::CheckBossEnter()
{
	bool bEnter = true;

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		if( !this->m_pEnemyBoss1Frame->IsEnter() )
		{
			this->m_pEnemyBoss1LaserLeft->SetEnter(false);
			this->m_pEnemyBoss1LaserRight->SetEnter(false);
			this->m_pEnemyBoss1ScatterLeft->SetEnter(false);
			this->m_pEnemyBoss1ScatterRight->SetEnter(false);
			this->m_pEnemyBoss1Cannon->SetEnter(false);

			bEnter = false;
		}

		break;

	case 2:

		if( !this->m_pEnemyBoss1Frame->IsEnter() )
		{
			this->m_pEnemyBoss1LaserLeft->SetEnter(false);
			this->m_pEnemyBoss1LaserRight->SetEnter(false);
			this->m_pEnemyBoss1ScatterLeft->SetEnter(false);
			this->m_pEnemyBoss1ScatterRight->SetEnter(false);
			this->m_pEnemyBoss1Cannon->SetEnter(false);

			bEnter = false;
		}

		break;

	case 3:

		if( !this->m_pEnemyBoss1Frame->IsEnter() )
		{
			this->m_pEnemyBoss1LaserLeft->SetEnter(false);
			this->m_pEnemyBoss1LaserRight->SetEnter(false);
			this->m_pEnemyBoss1ScatterLeft->SetEnter(false);
			this->m_pEnemyBoss1ScatterRight->SetEnter(false);
			this->m_pEnemyBoss1Cannon->SetEnter(false);

			bEnter = false;
		}
	}

	return bEnter;
}

void CTheGame::CheckExtraLife()
{
	//START********* CHECK EXTRA LIFE ****************//

	bool extraLife = false;

	switch(this->m_iExtraLives)
	{
	case 0:
		if(this->m_pPlayer->GetScore() >= 10000)
		{
			extraLife = true;
		}
		break;
	case 1:
		if(this->m_pPlayer->GetScore() >= 25000)
		{
			extraLife = true;
		}
		break;
	case 2:
		if(this->m_pPlayer->GetScore() >= 50000)
		{
			extraLife = true;
		}
		break;
	case 3:
		if(this->m_pPlayer->GetScore() >= 100000)
		{
			extraLife = true;
		}
		break;
	case 4:
		if(this->m_pPlayer->GetScore() >= 150000)
		{
			extraLife = true;
		}
		break;
	case 5:
		if(this->m_pPlayer->GetScore() >= 200000)
		{
			extraLife = true;
		}
		break;
	}

	if(extraLife)
	{
		this->m_iExtraLives++;
		this->m_pPlayer->ExtraLife();

		// play sound effect
		this->m_pTheApp->GetWave(SOUND_GAIN_LIFE).Play(FALSE, 0);
	}

	//END*********** CHECK EXTRA LIFE ****************//
}


void CTheGame::PlayerSetEnter(int currentGameState)
{
	m_fPlayerEnterMoveTimer = 0;

	// player health to max
	this->m_pPlayer->SetHealth(this->m_pGameSettings->m_iPlayerHealth);
	// reset player cannon energy
	this->m_pPlayer->ResetCannonEnergy();
	// reset player's local matrix to default
	this->m_pPlayer->SetDefaultMatrix();

	// set player enter starting position
	this->m_pPlayer->SetPosition(
		D3DXVECTOR3(
			this->m_pGameSettings->m_fPlayerEnterPositionX,
			this->m_pGameSettings->m_fPlayerEnterPositionY,
			0.0f));

	// player enter while level intro
	if (currentGameState == GAME_STATE_LEVEL_INTRO)
	{
		this->m_pPlayer->SetUntouchable(false);
		this->m_fPlayerBlinkTimer = 0.0f;
	}
	// player enter after destroyed
	else
	{
		this->m_pPlayer->SetDestroyed(false);
		this->m_pPlayer->SetUntouchable(true);
		this->m_fPlayerBlinkTimer = 0.03f;
		// play sound effect
		this->m_pTheApp->GetWave(SOUND_PLAYER_ENTER).Play(FALSE, 0);
	}

	// cannon can damage enemies again
	this->EnablePlayerCannonDamage();
}

void CTheGame::PlayerMoveEnter(float fFrametime)
{
	this->m_fPlayerEnterMoveTimer += fFrametime;
	this->m_fPlayerEnterMoveTimer = min(this->m_fPlayerEnterMoveTimer, PLAYER_ENTER_MOVE_DURATION);

	float delta = m_fPlayerEnterMoveTimer / PLAYER_ENTER_MOVE_DURATION;
	this->m_bPlayerAfterburn = (delta <= PLAYER_ENTER_AFTERBURN_END_DELTA);

	if (this->m_bPlayerAfterburn)
	{
		this->RenderPlayerAfterburn(false);
	}

	D3DXVECTOR3 pos = this->m_pPlayer->GetPosition();

	float currentPosY = LerpUtils::CalculateEasingPosition(
		LerpUtils::eEASING_LOGIC::EaseOutBack, this->m_pGameSettings->m_fPlayerEnterPositionY,
		this->m_pGameSettings->m_fPlayerGamePositionY, this->m_fPlayerEnterMoveTimer, PLAYER_ENTER_MOVE_DURATION);

	pos.y = currentPosY;
	this->m_pPlayer->SetPosition(pos);

	if (this->m_fPlayerEnterMoveTimer == PLAYER_ENTER_MOVE_DURATION)
	{
		this->m_bPlayerEnter = false;
		// reset player cannon
		this->PlayerResetCannon();
	}
}

void CTheGame::PlayerMoveAway(float fFrametime)
{
	static bool bSound = true;
	static float fSpeedIncrease = 0.05f;

	float fFrameSpeed = 0.0f;

	D3DXVECTOR3 pos = this->m_pPlayer->GetPosition();

	if (pos.y < (this->m_fScreenHeight + 50.0f))
	{
		this->RenderPlayerAfterburn(false);

		fFrameSpeed = (fFrametime * (this->m_pPlayer->GetSpeed() / 2.0f)) + fSpeedIncrease;
		fSpeedIncrease += 0.05f;

		pos.y += fFrameSpeed;
		this->m_pPlayer->SetPosition(pos);

		// play sound effect
		if (bSound)
		{
			bSound = false;
			this->PlaySoundPlayerAfterburn();
		}
	}
	else
	{
		fSpeedIncrease = 0.05f;
		bSound = true;

		this->m_bPlayerMoveAway = false;
	}
}

void CTheGame::PlayerDestroyed()
{
	// stop cannon sounds
	this->m_pTheApp->GetWave(SOUND_SHOOT_PLAYER_CANNON_CHARGE).Stop(0);
	this->m_pTheApp->GetWave(SOUND_SHOOT_PLAYER_CANNON_BEAM).Stop(0);

	this->m_pPlayer->SetDestroyed(true);
	this->m_pPlayer->SetHealth(0);

	this->m_pPlayer->LoseLife();
	this->m_pPlayer->ResetBoost();

	this->m_fPlayerEnterTimer = 2.0f;

	this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_READY;

	// play sound effect
	this->m_pTheApp->GetWave(SOUND_EXPLOSION_PLAYER).Play(	FALSE, 0,
															this->m_iVolumeSoundEffect);

	this->CheckGameOver();
}


void CTheGame::PlayerBlastActive()
{
	// activate player blast effect
	this->m_pPlayer->SetBlast(true);
	//this->m_pState->GetLights()->SetGamePlayerBlast(true, this->m_pPlayer->GetPosition());
	
	// set boss blast shaking
	if( (this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
		(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION))
	{
		if (this->m_pEnemyBoss1Frame->IsActive())
		{
			this->m_pEnemyBoss1Frame->SetBlastShake();
		}
	}

	// set blast shake: active enemies
	this->m_pActiveEnemies.SetFirst();
	while (this->m_pActiveEnemies.GetCurrent())
	{
		IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

		if (pEnemy->IsActive())
		{
			pEnemy->SetBlastShake();
		}

		this->m_pActiveEnemies.SetNext();
	}

	// set blast shake: obstacle enemies
	this->m_pObstacleEnemies.SetFirst();
	while (this->m_pObstacleEnemies.GetCurrent())
	{
		IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

		if (pEnemy->IsActive())
		{
			float enemyInsideScreenBorder = this->m_fScreenHeight + pEnemy->GetHeight() / 2.0f;

			if ((pEnemy->GetPosition().y < enemyInsideScreenBorder) &&
				(pEnemy->GetPosition().y > -enemyInsideScreenBorder))
			{
				pEnemy->SetBlastShake();
			}
		}

		this->m_pObstacleEnemies.SetNext();
	}

	// play sound effect
	this->m_pTheApp->GetWave(SOUND_SHOOT_PLAYER_BLAST).Play(FALSE, 0, this->m_iVolumePlayerBlast);

	SwitchGameState(GAME_STATE_BLAST_ACTIVE);
}

void CTheGame::PlayerBlastDeactive()
{
	// deactivate player blast effect
	this->m_pPlayer->SetBlast(false);
	//this->m_pState->GetLights()->SetGamePlayerBlast(false, this->m_pPlayer->GetPosition());

	bool bEnemyExplosion = false;

	// damage to the boss
	if( this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION )
	{
		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			if( this->m_pEnemyBoss1Frame->Destroyed(this->m_pPlayer->GetBlastDamage()) )
			{
				this->m_bBossDestroyed = true;
			}
			else
			{
				this->m_pPlayer->IncreaseScore((this->m_pEnemyBoss1Frame->GetScoreDestroyed() / 3));
			}
		}

#ifdef GAME_BOSS_PARTS_DAMAGE

		if( this->m_pEnemyBoss1LaserLeft->IsActive() )
		{
			if( this->m_pEnemyBoss1LaserLeft->Destroyed(this->m_pPlayer->GetBlastDamage()) )
			{
				this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserLeft->GetScoreDestroyed());
				// enemy explosion
				this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
				// play sound effect
				this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
					(FALSE, 0, this->m_iVolumeSoundEffect);
			}
			else
			{
				this->m_pPlayer->IncreaseScore((this->m_pEnemyBoss1LaserLeft->GetScoreDestroyed() / 3));
			}
		}

		if( this->m_pEnemyBoss1LaserRight->IsActive() )
		{
			if( this->m_pEnemyBoss1LaserRight->Destroyed(this->m_pPlayer->GetBlastDamage()) )
			{
				this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserRight->GetScoreDestroyed());
				// enemy explosion
				this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
				// play sound effect
				this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
					(FALSE, 0, this->m_iVolumeSoundEffect);
			}
			else
			{
				this->m_pPlayer->IncreaseScore((this->m_pEnemyBoss1LaserRight->GetScoreDestroyed() / 3));
			}
		}

		if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
		{
			if( this->m_pEnemyBoss1ScatterLeft->Destroyed(this->m_pPlayer->GetBlastDamage()) )
			{
				this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterLeft->GetScoreDestroyed());
				// enemy explosion
				this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
				// play sound effect
				this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
					(FALSE, 0, this->m_iVolumeSoundEffect);
			}
			else
			{
				this->m_pPlayer->IncreaseScore((this->m_pEnemyBoss1ScatterLeft->GetScoreDestroyed() / 3));
			}
		}

		if( this->m_pEnemyBoss1ScatterRight->IsActive() )
		{
			if( this->m_pEnemyBoss1ScatterRight->Destroyed(this->m_pPlayer->GetBlastDamage()) )
			{
				this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterRight->GetScoreDestroyed());
				// enemy explosion
				this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
				// play sound effect
				this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
					(FALSE, 0, this->m_iVolumeSoundEffect);
			}
			else
			{
				this->m_pPlayer->IncreaseScore((this->m_pEnemyBoss1ScatterRight->GetScoreDestroyed() / 3));
			}
		}

#endif
	}

	// damage to active enemies (launch, strike)
	this->m_pActiveEnemies.SetFirst();
	while (this->m_pActiveEnemies.GetCurrent())
	{
		IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

		if (pEnemy->IsActive())
		{
			pEnemy->SetTimedExplosion();
		}

		this->m_pActiveEnemies.SetNext();
	}

	// damage to obstacle enemies
	this->m_pObstacleEnemies.SetFirst();
	while (this->m_pObstacleEnemies.GetCurrent())
	{
		IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

		if (pEnemy->IsActive())
		{
			float enemyInsideScreenBorder = this->m_fScreenHeight + pEnemy->GetHeight() / 2.0f;

			if ((pEnemy->GetPosition().y < enemyInsideScreenBorder) &&
				(pEnemy->GetPosition().y > -enemyInsideScreenBorder))
			{
				pEnemy->SetTimedExplosion();
			}
		}

		this->m_pObstacleEnemies.SetNext();
	}

	// destroy bullets
	this->ClearBullets(true);

	// reset blast activity timer
	this->m_fBlastActiveCounter = this->m_fBlastActiveTime;

	// go back to previous game state
	SwitchGameState(this->m_iGameStatePrevious);
}

void CTheGame::PlayerShooting(float fFrametime)
{
	//START********** PLAYER SHOOTING ********************

	bool bInputMinigun = false;
	bool bInputFireMode = false;
	bool bInputCannon = false;
	bool bInputBlast = false;
	bool bCheckJoystick = false;
	bool bCheckKeyboard = true;

	if (SUCCEEDED(this->m_pJoystick->Update()))
	{
		bCheckJoystick = true;
	}

	if (bCheckJoystick)
	{
		DWORD buttons = this->m_pJoystick->GetButtonCount();

		// read minigun button
		if (this->m_pJoystick->GetButton(0))
		{
			bInputMinigun = true;
		}
		if (buttons > 1)
		{
			// read fire mode button
			if (this->m_pJoystick->GetButton(1))
			{
				bInputFireMode = true;
			}
			if (buttons > 2)
			{
				// read cannon button
				if (this->m_pJoystick->GetButton(2))
				{
					bInputCannon = true;
				}
				if (buttons > 3)
				{
					// read blast button
					if (this->m_pJoystick->GetButton(3))
					{
						bInputBlast = true;
					}
				}
			}
		}
		if (bInputMinigun || bInputFireMode || bInputCannon || bInputBlast)
		{
			// joystick has priority over keyboard
			bCheckKeyboard = false;
		}
	}
	if (bCheckKeyboard)
	{
		// read minigun button
		if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyMinigun()))
		{
			bInputMinigun = true;
		}
		// read fire mode button
		if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyMode()))
		{
			bInputFireMode = true;
		}
		// read cannon button
		if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyCannon()))
		{
			bInputCannon = true;
		}
		// read blast button
		if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyBlast()))
		{
			bInputBlast = true;
		}
	}

	// updates button timers to avoid
	//accidental multiple button presses
	if (this->m_fBlastButtonTimer > 0.0f)
	{
		this->m_fBlastButtonTimer -= fFrametime;
	}

	/* updates minigun countdown values */

	// minigun rotation
	if (this->m_fMinigunRotationTime > 0.0f)
	{
		this->m_fMinigunRotationTime -= fFrametime;
	}
	// minigun firing
	if (this->m_fMinigunFireTime > 0.0f)
	{
		this->m_fMinigunFireTime -= fFrametime;
	}

	// player minigun rotation is finished
	// minigun can be rotated again
	if (this->m_fMinigunRotationTime <= 0.0f)
	{
		// set miniguns rotation 'true'
		this->m_pPlayer->SetMinigunRotation(true);
	}

	// player pushes blast button
	if (bInputBlast)
	{
		bool bAllowed = false;

		if (PlayerShootPossible())
		{
			// player cannon non-active
			if (this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_CHARGE &&
				this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_BEAM)
			{
				// checks timer to avoid multiple button presses
				if (this->m_fBlastButtonTimer <= 0)
				{
					// player has blasts available
					if (this->m_pPlayer->GetBlasts() > 0)
					{
						bAllowed = true;
					}
				}
			}
		}

		// blast can be detonated
		if (bAllowed)
		{
			// activate blast effect
			this->PlayerBlastActive();

			// decrease blast count
			this->m_pPlayer->DecreaseBlasts();
			// to avoid multiple button presses
			this->m_fBlastButtonTimer = 1.0f;
		}
	}

	// player pushes cannon button
	if (bInputCannon)
	{
		bool bAllowed = false;

		if (PlayerShootPossible())
		{
			if (this->m_ePlayerCannonState == ePLAYER_CANNON_STATE_READY)
			{
				bAllowed = true;
			}
		}

		// cannon can be fired
		if (bAllowed)
		{
			// start cannon charge animation
			this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_CHARGE;
		}
	}

	// player pushes fire mode button (minigun rotation)
	if (bInputFireMode)
	{
		bool bAllowed = false;

		if (!this->m_pPlayer->IsDestroyed())
		{
			// player cannon non-active
			if (this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_CHARGE &&
				this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_BEAM)
			{
				// minigun can be rotated
				if (this->m_pPlayer->GetMinigunRotation())
				{
					bAllowed = true;
				}
			}
		}

		if (bAllowed)
		{
			if (this->m_pPlayer->GetMinigunMode() == 0)
			{
				// play minigun rotation sound
				this->m_pTheApp->GetWave(SOUND_PLAYER_MINIGUN_TURN_DIAGONAL).Play(FALSE, 0, m_iVolumePlayerMinigunTurn);
				this->m_pPlayer->SetMinigunMode(1);
			}
			else if (this->m_pPlayer->GetMinigunMode() == 1)
			{
				// play minigun rotation sound
				this->m_pTheApp->GetWave(SOUND_PLAYER_MINIGUN_TURN_FRONT).Play(FALSE, 0, m_iVolumePlayerMinigunTurn);
				this->m_pPlayer->SetMinigunMode(0);
			}

			// start minigun rotations
			this->m_pPlayerMinigunLeft->SetRotation(true);
			this->m_pPlayerMinigunRight->SetRotation(true);

			// start the countdown for the miniguns
			// rotation to be usable again
			this->m_fMinigunRotationTime = 0.4f;

			// miniguns can't be rotated (mode button)
			// rotation is already in progress
			this->m_pPlayer->SetMinigunRotation(false);

			// resets minigun sound
			this->m_pPlayer->ResetMinigunSound();
		}
	}

	// player pushes minigun button
	if (bInputMinigun)
	{
		bool bAllowed = false;

		if (PlayerShootPossible())
		{
			// player cannon non-active
			if (this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_CHARGE &&
				this->m_ePlayerCannonState != ePLAYER_CANNON_STATE_BEAM)
			{
				// minigun can be fired
				if ((this->m_fMinigunFireTime <= 0.0f) &&
					(this->m_fMinigunRotationTime <= 0.0f))
				{
					bAllowed = true;
				}
			}
		}

		if (bAllowed)
		{
			// front firing mode
			if (this->m_pPlayer->GetMinigunMode() == 0)
			{
				CWeapon* weapon = new CWeaponPlayerFront();

				if (weapon)
				{
					weapon->Create(this->m_pTheApp->GetDevice(),
						this->m_pWeaponPlayerFront->GetMesh(),
						this->m_pWeaponPlayerFront->GetMeshDataArray(),
						this->m_pWeaponPlayerFront->GetWidth(),
						this->m_pWeaponPlayerFront->GetHeight(),
						this->m_pPlayer->GetMinigunSpeed(),
						this->m_pPlayer->GetMinigunDamage(),
						this->m_pWeaponPlayerFront->GetBulletType());

					// mesh to mesh collision model

					weapon->GetBulletLeft()->SetCollisionMesh(this->m_pWeaponPlayerFront->GetBulletLeft()->GetCollisionMesh());
					weapon->GetBulletRight()->SetCollisionMesh(this->m_pWeaponPlayerFront->GetBulletRight()->GetCollisionMesh());

					weapon->SetMatrix(this->m_pPlayer);

					// sets minigun bullet placement (inner / outer)

					if (this->m_pPlayer->GetMinigunBulletPlace() == 0)
					{
						weapon->SetBulletPlace(CWeapon::eBULLET_PLACE_INNER);
					}
					else if (this->m_pPlayer->GetMinigunBulletPlace() == 1)
					{
						weapon->SetBulletPlace(CWeapon::eBULLET_PLACE_OUTER);
					}

					weapon->InitPosition();
					weapon->SetObjectDepth(this->m_pPlayerMinigunLeft->GetObjectDepth());

					weapon->SetVisible(true);
					this->m_pBullets.Push(weapon);

					// play minigun firing sound
					this->PlaySoundFirePlayerMinigun();
				}
			}

			// diagonal firing mode
			else if (this->m_pPlayer->GetMinigunMode() == 1)
			{
				CWeapon* weapon = new CWeaponPlayerDiagonal();

				if (weapon)
				{
					weapon->Create(this->m_pTheApp->GetDevice(),
						this->m_pWeaponPlayerDiagonal->GetMesh(),
						this->m_pWeaponPlayerDiagonal->GetMeshDataArray(),
						this->m_pWeaponPlayerDiagonal->GetWidth(),
						this->m_pWeaponPlayerDiagonal->GetHeight(),
						this->m_pPlayer->GetMinigunSpeed(),
						this->m_pPlayer->GetMinigunDamage(),
						this->m_pWeaponPlayerDiagonal->GetBulletType());

					// mesh to mesh collision model

					weapon->GetBulletLeft()->SetCollisionMesh(this->m_pWeaponPlayerDiagonal->GetBulletLeft()->GetCollisionMesh());
					weapon->GetBulletRight()->SetCollisionMesh(this->m_pWeaponPlayerDiagonal->GetBulletRight()->GetCollisionMesh());

					weapon->SetMatrix(this->m_pPlayer);

					// sets minigun bullet placement (inner / outer)

					if (this->m_pPlayer->GetMinigunBulletPlace() == 0)
					{
						weapon->SetBulletPlace(CWeapon::eBULLET_PLACE_INNER);
					}
					else if (this->m_pPlayer->GetMinigunBulletPlace() == 1)
					{
						weapon->SetBulletPlace(CWeapon::eBULLET_PLACE_OUTER);
					}

					weapon->InitPosition();
					weapon->SetObjectDepth(this->m_pPlayerMinigunLeft->GetObjectDepth());

					weapon->SetVisible(true);
					this->m_pBullets.Push(weapon);

					// play minigun firing sound
					this->PlaySoundFirePlayerMinigun();
				}
			}

			// change minigun bullet placement (inner / outer) 
			// for the next bullet to use

			if (this->m_pPlayer->GetMinigunBulletPlace() == 0)
			{
				this->m_pPlayer->SetMinigunBulletPlace(1);
			}
			else if (this->m_pPlayer->GetMinigunBulletPlace() == 1)
			{
				this->m_pPlayer->SetMinigunBulletPlace(0);
			}

			// start the countdown for the minigun firing to be available again
			this->m_fMinigunFireTime = this->m_pPlayer->GetMinigunFirerate();
		}
	}

	//END************ PLAYER SHOOTING ********************
}

bool CTheGame::PlayerShootPossible()
{
	//START******** PLAYER SHOOT POSSIBLE ****************

	if (this->m_pPlayer->IsDestroyed() || this->m_bPlayerEnter ||
		(this->m_iGameState == GAME_STATE_LEVEL_INTRO) ||
		(this->m_iGameState == GAME_STATE_LEVEL_OUTRO )||
		(this->m_iGameState == GAME_STATE_LOAD_LEVEL))
	{
		return false;
	}

	return true;

	//END********** PLAYER SHOOT POSSIBLE ****************
}

bool CTheGame::PlayerCannonLineOfFireEnemies(IEnemy* pEnemy)
{
	//START********* PLAYER CANNON LINE OF FIRE ENEMIES *********

	bool bHit = false;
	bool bBossCore = false;

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_BOSS) 
	{
		if(pEnemy->GetType() == IEnemy::eTYPE_BOSS_1_CORE)
		{
			bBossCore = true;
		}
	}

	posA = this->m_pPlayer->GetPosition();

	if(bBossCore)
	{
		// we get boss core position from boss frame position
		switch(this->m_pLevel->GetLevelNumber())
		{
		case 1:

			posB = this->m_pEnemyBoss1Frame->GetPosition();

			posB.y -= 15.0f;
			posB.z -= 12.0f;

			break;

		case 2:

			posB = this->m_pEnemyBoss1Frame->GetPosition();

			posB.y -= 15.0f;
			posB.z -= 12.0f;

			break;

		case 3:

			posB = this->m_pEnemyBoss1Frame->GetPosition();

			posB.y -= 15.0f;
			posB.z -= 12.0f;

			break;
		}
	}
	else
	{
		posB = pEnemy->GetPosition();
	}

	float fLeftSide;
	float fRightSide;

	if(bBossCore)
	{
		switch(this->m_pLevel->GetLevelNumber())
		{
		case 1:

			fLeftSide = posB.x - 5.0f;
			fRightSide = posB.x + 5.0f;

			break;

		case 2:

			fLeftSide = posB.x - 5.0f;
			fRightSide = posB.x + 5.0f;

			break;

		case 3:

			fLeftSide = posB.x - 5.0f;
			fRightSide = posB.x + 5.0f;

			break;
		}
	}
	else
	{
		float widthB = pEnemy->GetWidth();

		fLeftSide = posB.x - (widthB / 2);
		fRightSide = posB.x + (widthB / 2);
	}

	if(( posA.x >= fLeftSide ) && 
		( posA.x <= fRightSide ))
	{
		if( posA.y < posB.y )
		{
			bHit = true;
		}
	}

	return bHit;

	//END*********** PLAYER CANNON LINE OF FIRE ENEMIES *********
}

bool CTheGame::PlayerCannonLineOfFireBullets(CWeapon* bullet)
{
	//START********* PLAYER CANNON LINE OF FIRE BULLETS *********

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float widthB;

	float fBulletLeftSide;
	float fBulletRightSide;

	bool bHit;

	posA = this->m_pPlayer->GetPosition();
	posB = bullet->GetPosition();
	widthB = bullet->GetWidth();

	fBulletLeftSide = posB.x - (widthB / 2);
	fBulletRightSide = posB.x + (widthB / 2);

	bHit = false;

	if(( ((posA.x + 2.0f) > fBulletLeftSide ) && 
		  ((posA.x + 2.0f) < fBulletRightSide) ) || 
		( ((posA.x - 2.0f) > fBulletLeftSide ) && 
		  ((posA.x - 2.0f) < fBulletRightSide) ) || 
		( ((posA.x + 2.0f) == fBulletLeftSide) || 
		  ((posA.x + 2.0f) == fBulletRightSide) || 
		  ((posA.x - 2.0f) == fBulletLeftSide) || 
		  ((posA.x - 2.0f) == fBulletRightSide) ))
	{
		if( posA.y < posB.y )
		{
			bHit = true;
		}
	}

	return bHit;

	//END*********** PLAYER CANNON LINE OF FIRE BULLETS *********
}

bool CTheGame::PlayerResetMiniguns()
{
	//START*********** PLAYER RESET MINIGUNS *****************

	bool bRotation = false;

	if(this->m_pPlayer->GetMinigunMode() == 1)
	{
		// play minigun rotation sound
		this->m_pTheApp->GetWave(SOUND_PLAYER_MINIGUN_TURN_FRONT).Play(FALSE, 0, m_iVolumePlayerMinigunTurn);
		this->m_pPlayer->SetMinigunMode(0);

		// start minigun rotations
		this->m_pPlayerMinigunLeft->SetRotation(true);
		this->m_pPlayerMinigunRight->SetRotation(true);

		bRotation = true;
	}

	return bRotation;

	//END************* PLAYER RESET MINIGUNS *****************
}

void CTheGame::PlayerResetCannon()
{
	//START*********** PLAYER RESET CANNON *****************

	// Player cannon charge //

	// reset active cannon charge texture
	this->m_iCannonChargeTexture = 1;
	// reset overall cannon charge time counter
	this->m_fCannonChargeCounter = this->m_fCannonChargeTime;
	// reset individual cannon charge sprites time
	this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;
	// reset cannon charge sprite size value
	this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_SMALL;
	// cannon can hurt bosses
	this->m_bCannonDamageBoss = true;

	//END************* PLAYER RESET CANNON *****************
}

void CTheGame::PlayerExplosion()
{
	//START************ PLAYER EXPLOSION **************

	this->m_pExplosions->AddExplosion(	CExplosion::eEXPLOSION_TYPE_PLAYER,
										this->m_iExplosionMoveSpeed,
										this->m_fExplosionMovePause,
										this->m_pPlayer->GetPosition());

	//END************** PLAYER EXPLOSION **************
}


IEnemy* CTheGame::GenerateEnemies(	CLevel::eFLEET_TYPE eFleetType,
									CLevel::eSHIP_TYPE eShipType)
{
	//START************ GENERATE ENEMIES *************

	IEnemy* pEnemy = NULL;

	float fStrikeSpeedModifier = this->m_pTheApp->RandFloat(
		this->m_pGameSettings->m_fEnemyStrikeSpeedMultiplierMin,
		this->m_pGameSettings->m_fEnemyStrikeSpeedMultiplierMax);

	switch (eFleetType)
	{
	case CLevel::eFLEET_TYPE_LAUNCH:

		switch (eShipType)
		{
		case CLevel::eSHIP_TYPE_DRONE:
		{
			CEnemyDrone* templateObj = m_vTemplateEnemyDroneLaunch[0];

			pEnemy = new CEnemyDrone(
				templateObj->GetType(),
				templateObj->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					templateObj->GetMesh(),
					templateObj->GetMeshDataArray(),
					templateObj->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetDefaultMatrix(templateObj->GetDefaultMatrix());
			}
		}
		break;

		case CLevel::eSHIP_TYPE_SNIPER:
		{
			CEnemySniper* templateObj = m_vTemplateEnemySniperLaunch[0];

			pEnemy = new CEnemySniper(
				templateObj->GetType(),
				templateObj->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					templateObj->GetMesh(),
					templateObj->GetMeshDataArray(),
					templateObj->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetDefaultMatrix(templateObj->GetDefaultMatrix());
			}
		}
		break;

		case CLevel::eSHIP_TYPE_ROLLER:
		{
			CEnemyRoller* templateObj = m_vTemplateEnemyRollerLaunch[0];

			pEnemy = new CEnemyRoller(
				templateObj->GetType(),
				templateObj->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					templateObj->GetMesh(),
					templateObj->GetMeshDataArray(),
					templateObj->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->InitWeapons(this->m_pTheApp,
					this->m_pWeaponRoller->GetMesh(),
					this->m_pWeaponRoller->GetMeshDataArray(),
					this->m_pGameSettings->m_fEnemyRollerBulletWidth,
					this->m_pGameSettings->m_fEnemyRollerBulletHeight,
					this->m_pGameSettings->m_fEnemyRollerBulletSpeed,
					this->m_pGameSettings->m_iEnemyRollerBulletDamage);

				pEnemy->SetDefaultMatrix(templateObj->GetDefaultMatrix());
			}
		}
		break;

		case CLevel::eSHIP_TYPE_GUARD:
		{
			/*
			CEnemyGuard* templateObj = m_vTemplateEnemyGuardLaunch[0];

			pEnemy = new CEnemyGuard(
				templateObj->GetType(),
				templateObj->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					templateObj->GetMesh(),
					templateObj->GetMeshDataArray(),
					templateObj->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetDefaultMatrix(templateObj->GetDefaultMatrix());
			}
			*/
		}
		break;
		}

		break;

	case CLevel::eFLEET_TYPE_STRIKE:

		switch (eShipType)
		{
		case CLevel::eSHIP_TYPE_DRONE:

			pEnemy = new CEnemyDrone(
				this->m_pEnemyDroneStrike->GetType(),
				this->m_pEnemyDroneStrike->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pEnemyDroneStrike->GetMesh(),
					this->m_pEnemyDroneStrike->GetMeshDataArray(),
					this->m_pEnemyDroneStrike->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetSpeed(fStrikeSpeedModifier * this->m_pEnemyDroneStrike->GetSpeed());
				pEnemy->SetDefaultMatrix(this->m_pEnemyDroneStrike->GetDefaultMatrix());
			}
			break;

		case CLevel::eSHIP_TYPE_SNIPER:

			pEnemy = new CEnemySniper(
				this->m_pEnemySniperStrike->GetType(),
				this->m_pEnemySniperStrike->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pEnemySniperStrike->GetMesh(),
					this->m_pEnemyDroneStrike->GetMeshDataArray(),
					this->m_pEnemySniperStrike->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetSpeed(fStrikeSpeedModifier * this->m_pEnemySniperStrike->GetSpeed());
				pEnemy->SetDefaultMatrix(this->m_pEnemySniperStrike->GetDefaultMatrix());
			}
			break;

		case CLevel::eSHIP_TYPE_ROLLER:

			pEnemy = new CEnemyRoller(
				this->m_pEnemyRollerStrike->GetType(),
				this->m_pEnemyRollerStrike->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pEnemyRollerStrike->GetMesh(),
					this->m_pEnemyDroneStrike->GetMeshDataArray(),
					this->m_pEnemyRollerStrike->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->InitWeapons(this->m_pTheApp,
					this->m_pWeaponRoller->GetMesh(),
					this->m_pWeaponRoller->GetMeshDataArray(),
					this->m_pGameSettings->m_fEnemyRollerBulletWidth,
					this->m_pGameSettings->m_fEnemyRollerBulletHeight,
					this->m_pGameSettings->m_fEnemyRollerBulletSpeed,
					this->m_pGameSettings->m_iEnemyRollerBulletDamage);

				pEnemy->SetSpeed(fStrikeSpeedModifier * this->m_pEnemyRollerStrike->GetSpeed());
				pEnemy->SetDefaultMatrix(this->m_pEnemyRollerStrike->GetDefaultMatrix());
			}
			break;

		case CLevel::eSHIP_TYPE_GUARD:
			/*
			pEnemy = new CEnemyGuard(
				this->m_pEnemyGuardStrike->GetType(),
				this->m_pEnemyGuardStrike->GetBehaviour());

			if (pEnemy)
			{
				pEnemy->Create(
					this->m_pTheApp, this->m_pGameSettings,
					this->m_pEnemyGuardStrike->GetMesh(),
					this->m_pEnemyDroneStrike->GetMeshDataArray(),
					this->m_pEnemyGuardStrike->GetSpriteAfterburn(),
					this->m_iVolumeSoundEffect);

				pEnemy->SetSpeed(fStrikeSpeedModifier * this->m_pEnemyGuardStrike->GetSpeed());
				pEnemy->SetDefaultMatrix(this->m_pEnemyGuardStrike->GetDefaultMatrix());
			}
			*/
			break;
		}

		break;
	}

	if (pEnemy)
	{
		pEnemy->InitRotationValues();

		// enemy strike afterburn and sound
		if (pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE)
		{
			// Afterburn effect
			if ((eShipType == CLevel::eSHIP_TYPE_DRONE) || (eShipType == CLevel::eSHIP_TYPE_SNIPER))
			{
				switch (this->m_pTheApp->RandInt(1, 4))
				{
				case 1:
					pEnemy->SetSoundStrikeAfterburn(IEnemy::eSOUND_STRIKE_AFTERBURN_3);
					break;
				case 2:
					pEnemy->SetSoundStrikeAfterburn(IEnemy::eSOUND_STRIKE_AFTERBURN_1);
					break;
				case 3:
					pEnemy->SetSoundStrikeAfterburn(IEnemy::eSOUND_STRIKE_AFTERBURN_2);
					break;
				case 4:
					pEnemy->SetSoundStrikeAfterburn(IEnemy::eSOUND_STRIKE_AFTERBURN_4);
					break;
				}
			}
			else
			{
				pEnemy->SetAfterburn(false);
			}
		}

		/* COLLISION MODEL */
		this->CreateCollisionMeshEnemies(pEnemy);
	}

	return pEnemy;

	//END************** GENERATE ENEMIES *************
}


void CTheGame::ClearLaunchEnemies()
{
	// clear launch fleets
	delete [] this->m_pLaunchEnemies;
	this->m_pLaunchEnemies = NULL;
}

void CTheGame::ClearStrikeEnemies()
{
	// clear strike fleets
	delete [] this->m_pStrikeEnemies;
	this->m_pStrikeEnemies = NULL;
}

void CTheGame::ClearLevelObstacles()
{
	this->m_pObstaclesDepth1.Clear();
	this->m_pObstaclesDepth2.Clear();
	this->m_pObstaclesDepth3.Clear();
	this->m_pObstaclesDepth4.Clear();
	this->m_pObstaclesDepth5.Clear();
}

void CTheGame::PrepareLaunchEnemies()
{
	// address to array holding all the enemy launch fleet sizes of the current level
	int* pLaunchFleetSize = this->m_pLevel->GetLaunchFleetSize();

	if (pLaunchFleetSize)
	{
		// creates new launch fleets
		this->m_pLaunchEnemies = new CQueue<IEnemy*>[this->m_pLevel->GetFleetsLaunch()];

		// goes through all the launch fleets
		for (int i = 0; i < this->m_pLevel->GetFleetsLaunch(); i++)
		{
			// get current launch fleet's size
			int iFleetSize = pLaunchFleetSize[i];

			// selects all enemy ships to be put in the current launch fleet
			for (int j = 0; j < iFleetSize; j++)
			{
				IEnemy* pEnemy = this->GenerateEnemies(CLevel::eFLEET_TYPE_LAUNCH, this->m_pLevel->GetLaunchShip());

				if (pEnemy)
				{
					this->m_pLaunchEnemies[i].Push(pEnemy);
				}
			}
		}
	}
}

void CTheGame::PrepareStrikeEnemies()
{
	// address to array holding all the enemy strike fleet sizes of the current level
	int* pStrikeFleetSize = this->m_pLevel->GetStrikeFleetSize();

	if (pStrikeFleetSize)
	{
		// creates new strike fleets
		this->m_pStrikeEnemies = new CQueue<IEnemy*>[this->m_pLevel->GetFleetsStrike()];

		// goes through all the strike fleets
		for (int i = 0; i < this->m_pLevel->GetFleetsStrike(); i++)
		{
			// get current strike fleet's size
			int iFleetSize = pStrikeFleetSize[i];

			// selects all enemy ships to be put on the current strike fleet
			for (int j = 0; j < iFleetSize; j++)
			{
				IEnemy* pEnemy = this->GenerateEnemies(CLevel::eFLEET_TYPE_STRIKE, this->m_pLevel->GetStrikeShip());

				if (pEnemy)
				{
					this->m_pStrikeEnemies[i].Push(pEnemy);
				}
			}
		}
	}
}

void CTheGame::PrepareReinforcements()
{
	switch( this->m_pLevel->GetLevelNumber() )
	{
	case 1:
		this->m_iReinforcementsMax = GAME_REINFORCEMENTS_LEVEL_1;
		break;
	case 2:
		this->m_iReinforcementsMax = GAME_REINFORCEMENTS_LEVEL_2;
		break;
	case 3:
		this->m_iReinforcementsMax = GAME_REINFORCEMENTS_LEVEL_3;
		break;
	}

	for (int i = 0; i < this->m_iReinforcementsMax;)
	{
		IEnemy* pEnemy;

		pEnemy = this->GenerateEnemies(CLevel::eFLEET_TYPE_LAUNCH, this->m_pLevel->GetReinforcementShip());

		if (pEnemy)
		{
			pEnemy->SetBehaviour(IEnemy::eBEHAVIOUR_REINFORCEMENT);
			pEnemy->SetReinforcementAction(IEnemy::eREINFORCEMENT_ACTION_WAIT);
			this->m_pReinforcements.Push(pEnemy);

			i++;
		}
	}
}

void CTheGame::PrepareObstacles()
{
	m_iObstaclesMax = 0;
	int obstacles = this->m_pLevel->GetObstacles();

	if (obstacles == 0)
	{
		return;
	}

	float addedObstacleMaxPosY = 0;

	float fPosX = 0;
	float fPosY = 0;

	bool generateObstacles;
		
	// obstacle depth
	int maxDepth = 5;

	for (int currentDepth = 1; currentDepth <= maxDepth; currentDepth++)
	{
		fPosY = this->m_fScreenHeight + 60.0f;

		// background asteroids
		if (currentDepth > 1)
		{
			// showing them during the level intro
			if (this->m_pLevel->IsObstaclesFirst())
			{
				fPosY = -this->m_fScreenHeight;
			}

			fPosY += (maxDepth * 10.0f) / currentDepth;
		}

		generateObstacles = true;

		while (generateObstacles)
		{
			CObstacle* obstacle = NULL;
			IEnemy* enemy = NULL;

			switch (currentDepth)
			{
			case 1:

				if (IsGenerateObstacleEnemy())
				{
					enemy = GenerateObstacleEnemy(fPosY);
				}

				if (enemy != NULL)
				{
					fPosY += enemy->GetHeight();
					this->m_pObstacleEnemies.Push(enemy);
				}
				else
				{
					obstacle = GenerateObstacle(fPosY, currentDepth);

					if (obstacle != NULL)
					{
						fPosY += 2.0f * obstacle->GetHeight();
						this->m_pObstaclesDepth1.Push(obstacle);

						m_iObstaclesMax++;

						if (m_iObstaclesMax == obstacles)
						{
							addedObstacleMaxPosY = fPosY;
							generateObstacles = false;
						}
					}
				}

				break;

			case 2:

				obstacle = GenerateObstacle(fPosY, currentDepth);

				if (obstacle != NULL)
				{
					fPosY += 6.0f * obstacle->GetHeight();
					this->m_pObstaclesDepth2.Push(obstacle);

					float speedMultiplier = this->m_pGameSettings->m_fObstacleSpeed2 / this->m_pGameSettings->m_fObstacleSpeed1;

					if (fPosY >= (speedMultiplier * addedObstacleMaxPosY))
					{
						generateObstacles = false;
					}
				}

				break;

			case 3:

				obstacle = GenerateObstacle(fPosY, currentDepth);

				if (obstacle != NULL)
				{
					fPosY += 5.0f * obstacle->GetHeight();
					this->m_pObstaclesDepth3.Push(obstacle);

					float speedMultiplier = this->m_pGameSettings->m_fObstacleSpeed2 / this->m_pGameSettings->m_fObstacleSpeed1;

					if (fPosY >= (speedMultiplier * addedObstacleMaxPosY))
					{
						generateObstacles = false;
					}
				}

				break;

			case 4:

				obstacle = GenerateObstacle(fPosY, currentDepth);

				if (obstacle != NULL)
				{
					fPosY += 4.0f * obstacle->GetHeight();
					this->m_pObstaclesDepth4.Push(obstacle);

					float speedMultiplier = this->m_pGameSettings->m_fObstacleSpeed2 / this->m_pGameSettings->m_fObstacleSpeed1;

					if (fPosY >= (speedMultiplier * addedObstacleMaxPosY))
					{
						generateObstacles = false;
					}
				}

				break;

			case 5:

				obstacle = GenerateObstacle(fPosY, currentDepth);

				if (obstacle != NULL)
				{
					fPosY += 3.0f * obstacle->GetHeight();
					this->m_pObstaclesDepth5.Push(obstacle);

					float speedMultiplier = this->m_pGameSettings->m_fObstacleSpeed2 / this->m_pGameSettings->m_fObstacleSpeed1;

					if (fPosY >= (speedMultiplier * addedObstacleMaxPosY))
					{
						generateObstacles = false;
					}
				}

				break;
			}
		}
	}
}

CObstacle* CTheGame::GenerateObstacle(float fPosY, int iDepth)
{
	//START******* GENERATE OBSTACLE **********

	// creates a new obstacle and checks that it 
	// doesn't collide with existing obstacles or enemies
	int maxTryOuts = 10;

	for (int i = 0; i < maxTryOuts; i++)
	{
		CObstacle* obstacle = GenerateObstacleType(iDepth);

		if (obstacle)
		{
			CObstacle::eOBSTACLE_DEPTH eDepth = CObstacle::eOBSTACLE_DEPTH_1;
			float fSpeed = this->m_pGameSettings->m_fObstacleSpeed1;

			switch (iDepth)
			{
			case 2:
				eDepth = CObstacle::eOBSTACLE_DEPTH_2;
				fSpeed = this->m_pGameSettings->m_fObstacleSpeed2;
				break;
			case 3:
				eDepth = CObstacle::eOBSTACLE_DEPTH_3;
				fSpeed = this->m_pGameSettings->m_fObstacleSpeed3;
				break;
			case 4:
				eDepth = CObstacle::eOBSTACLE_DEPTH_4;
				fSpeed = this->m_pGameSettings->m_fObstacleSpeed4;
				break;
			case 5:
				eDepth = CObstacle::eOBSTACLE_DEPTH_5;
				fSpeed = this->m_pGameSettings->m_fObstacleSpeed5;
				break;
			}

			obstacle->InitObstacle(eDepth);
			obstacle->SetSpeed(fSpeed);

			/* COLLISION MODEL*/
			this->CreateCollisionMeshObstacles(obstacle);

			D3DXVECTOR3 pos = obstacle->GetPosition();

			pos.y = fPosY;

			float fBorderLeft = -this->m_fScreenWidth + (obstacle->GetWidth() / 2);
			float fBorderRight = this->m_fScreenWidth - (obstacle->GetWidth() / 2);

			bool bCollision = false;

			// generate a random obstacle x-axel position
			pos.x = this->m_pTheApp->RandFloat(fBorderLeft, fBorderRight);
			obstacle->SetPosition(pos);

			// checks collision against obstacles
			if (this->IsBoxCollisionObstacleVsObstacle(obstacle, iDepth))
			{
				bCollision = true;
			}
			// checks collision against obstacle enemies
			if (!bCollision && (iDepth > 1) && this->m_pLevel->IsObstacleEnemies())
			{
				if (this->IsBoxCollisionObstacleVsEnemies(obstacle))
				{
					bCollision = true;
				}
			}

			if (bCollision)
			{
				obstacle = NULL;
			}
			else
			{
				obstacle->SetActive(FALSE);
				return obstacle;
			}
		}
	}

	return NULL;

	//END********* GENERATE OBSTACLE ************
}

CObstacle* CTheGame::GenerateObstacleType(int iDepth)
{
	//START***** GENERATE OBSTACLE TYPE *********

	CObstacle* obstacle = new CObstacle();

	LPD3DXMESH mesh = this->m_vTemplateAsteroidBig[0]->GetMesh();
	std::vector<C3DObject::MESHDATA>& meshData = this->m_vTemplateAsteroidBig[0]->GetMeshDataArray();
	float objectWidth = this->m_vTemplateAsteroidBig[0]->GetWidth();
	float objectHeight = this->m_vTemplateAsteroidBig[0]->GetHeight();
	CObstacle::eTYPE obstacleType = this->m_vTemplateAsteroidBig[0]->GetType();

	int sizeType = this->m_pTheApp->RandInt(1, 3);
	int asteroidType = this->m_pTheApp->RandInt(0, 4);

	switch (sizeType)
	{
		// big asteroid
	case 1:
	{
		mesh = this->m_vTemplateAsteroidBig[asteroidType]->GetMesh();
		meshData = this->m_vTemplateAsteroidBig[asteroidType]->GetMeshDataArray();
		objectWidth = this->m_vTemplateAsteroidBig[asteroidType]->GetWidth();
		objectHeight = this->m_vTemplateAsteroidBig[asteroidType]->GetHeight();
		obstacleType = this->m_vTemplateAsteroidBig[asteroidType]->GetType();
	}
	break;

	// medium asteroid
	case 2:
	{
		mesh = this->m_vTemplateAsteroidMedium[asteroidType]->GetMesh();
		meshData = this->m_vTemplateAsteroidMedium[asteroidType]->GetMeshDataArray();
		objectWidth = this->m_vTemplateAsteroidMedium[asteroidType]->GetWidth();
		objectHeight = this->m_vTemplateAsteroidMedium[asteroidType]->GetHeight();
		obstacleType = this->m_vTemplateAsteroidMedium[asteroidType]->GetType();
	}
	break;

	// small asteroid
	case 3:
	{
		mesh = this->m_vTemplateAsteroidSmall[asteroidType]->GetMesh();
		meshData = this->m_vTemplateAsteroidSmall[asteroidType]->GetMeshDataArray();
		objectWidth = this->m_vTemplateAsteroidSmall[asteroidType]->GetWidth();
		objectHeight = this->m_vTemplateAsteroidSmall[asteroidType]->GetHeight();
		obstacleType = this->m_vTemplateAsteroidSmall[asteroidType]->GetType();
	}
	break;
	}

	obstacle->Create(this->m_pTheApp, mesh, meshData, objectWidth, objectHeight, this->m_fScreenWidth, this->m_fScreenHeight);
	obstacle->SetType(obstacleType);

	return obstacle;

	//END******* GENERATE OBSTACLE TYPE ***********
}

bool CTheGame::IsGenerateObstacleEnemy()
{
	bool bEnemy = false;

	if (this->m_pLevel->IsObstacleEnemies())
	{
		int random = this->m_pTheApp->RandInt(1, 8);

		switch (this->m_pLevel->GetLevelNumber())
		{
		case 2:
		{
			switch (random)
			{
			case 1:
				bEnemy = false;
				break;
			case 2:
				bEnemy = true;
				break;
			case 3:
				bEnemy = false;
				break;
			case 4:
				bEnemy = true;
				break;
			case 5:
				bEnemy = false;
				break;
			case 6:
				bEnemy = true;
				break;
			case 7:
				bEnemy = false;
				break;
			case 8:
				bEnemy = false;
				break;
			}
		}
		break;

		default:
		{
			switch (random)
			{
			case 1:
				bEnemy = false;
				break;
			case 2:
				bEnemy = true;
				break;
			case 3:
				bEnemy = false;
				break;
			case 4:
				bEnemy = true;
				break;
			case 5:
				bEnemy = false;
				break;
			case 6:
				bEnemy = true;
				break;
			case 7:
				bEnemy = true;
				break;
			case 8:
				bEnemy = true;
				break;
			}
		}
		break;
		}
	}

	return bEnemy;
}

bool CTheGame::IsBoxCollisionObstacleVsEnemies(CObstacle* obstacle)
{
	// Checks if a given obstacle collides with "obstacle enemy" fleet

	this->m_pObstacleEnemies.SetFirst();
	while (this->m_pObstacleEnemies.GetCurrent())
	{
		IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

		if (pEnemy->IsActive())
		{
			// bounding box collision
			if (this->IsBoxCollision(obstacle->GetPosition(),
				obstacle->GetWidth() + 8.0f,
				obstacle->GetHeight() + 8.0f,
				pEnemy->GetPosition(),
				pEnemy->GetWidth() + 8.0f,
				pEnemy->GetHeight() + 8.0f))
			{
				return true;
			}
		}

		this->m_pObstacleEnemies.SetNext();
	}

	return false;
}

bool CTheGame::IsBoxCollisionEnemyVsObstacles(IEnemy* pEnemy)
{
	this->m_pObstaclesDepth1.SetFirst();
	while (this->m_pObstaclesDepth1.GetCurrent())
	{
		CObstacle* pObstacle = this->m_pObstaclesDepth1.GetCurrent();

		// bounding box collision
		if (this->IsBoxCollision(pEnemy->GetPosition(),
			pEnemy->GetWidth() + 8.0f,
			pEnemy->GetHeight() + 8.0f,
			pObstacle->GetPosition(),
			pObstacle->GetWidth() + 8.0f,
			pObstacle->GetHeight() + 8.0f))
		{
			return true;
		}

		this->m_pObstaclesDepth1.SetNext();
	}

	return false;
}

bool CTheGame::IsBoxCollisionObstacleVsObstacle(CObstacle* pObstacle, int iDepth)
{
	CObstacle* pOther = NULL;

	switch (iDepth)
	{
	case 1:

		this->m_pObstaclesDepth1.SetFirst();
		while (this->m_pObstaclesDepth1.GetCurrent())
		{
			pOther = this->m_pObstaclesDepth1.GetCurrent();

			if (pOther->IsActive())
			{
				// bounding box collision
				if (this->IsBoxCollision(pObstacle->GetPosition(),
					pObstacle->GetWidth() + 8.0f,
					pObstacle->GetHeight() + 8.0f,
					pOther->GetPosition(),
					pOther->GetWidth() + 8.0f,
					pOther->GetHeight() + 8.0f))
				{
					return true;
				}
			}

			this->m_pObstaclesDepth1.SetNext();
		}

		break;

	case 2:

		this->m_pObstaclesDepth2.SetFirst();
		while (this->m_pObstaclesDepth2.GetCurrent())
		{
			pOther = this->m_pObstaclesDepth2.GetCurrent();

			if (pOther->IsActive())
			{
				// bounding box collision
				if (this->IsBoxCollision(pObstacle->GetPosition(),
					pObstacle->GetWidth() + 8.0f,
					pObstacle->GetHeight() + 8.0f,
					pOther->GetPosition(),
					pOther->GetWidth() + 8.0f,
					pOther->GetHeight() + 8.0f))
				{
					return true;
				}
			}

			this->m_pObstaclesDepth2.SetNext();
		}

		break;

	case 3:

		this->m_pObstaclesDepth3.SetFirst();
		while (this->m_pObstaclesDepth3.GetCurrent())
		{
			pOther = this->m_pObstaclesDepth3.GetCurrent();

			if (pOther->IsActive())
			{
				// bounding box collision
				if (this->IsBoxCollision(pObstacle->GetPosition(),
					pObstacle->GetWidth() + 8.0f,
					pObstacle->GetHeight() + 8.0f,
					pOther->GetPosition(),
					pOther->GetWidth() + 8.0f,
					pOther->GetHeight() + 8.0f))
				{
					return true;
				}
			}

			this->m_pObstaclesDepth3.SetNext();
		}

		break;

	case 4:

		this->m_pObstaclesDepth4.SetFirst();
		while (this->m_pObstaclesDepth4.GetCurrent())
		{
			pOther = this->m_pObstaclesDepth4.GetCurrent();

			if (pOther->IsActive())
			{
				// bounding box collision
				if (this->IsBoxCollision(pObstacle->GetPosition(),
					pObstacle->GetWidth() + 8.0f,
					pObstacle->GetHeight() + 8.0f,
					pOther->GetPosition(),
					pOther->GetWidth() + 8.0f,
					pOther->GetHeight() + 8.0f))
				{
					return true;
				}
			}

			this->m_pObstaclesDepth4.SetNext();
		}

		break;

	case 5:

		this->m_pObstaclesDepth5.SetFirst();
		while (this->m_pObstaclesDepth5.GetCurrent())
		{
			pOther = this->m_pObstaclesDepth5.GetCurrent();

			if (pOther->IsActive())
			{
				// bounding box collision
				if (this->IsBoxCollision(pObstacle->GetPosition(),
					pObstacle->GetWidth() + 8.0f,
					pObstacle->GetHeight() + 8.0f,
					pOther->GetPosition(),
					pOther->GetWidth() + 8.0f,
					pOther->GetHeight() + 8.0f))
				{
					return true;
				}
			}

			this->m_pObstaclesDepth5.SetNext();
		}

		break;
	}

	return false;
}

IEnemy* CTheGame::GenerateObstacleEnemy(float fPosY)
{
	//START************ OBSTACLE ENEMY **************

	IEnemy* pEnemy = this->GenerateEnemies(	CLevel::eFLEET_TYPE_LAUNCH, this->m_pLevel->GetObstacleShip());

	if (pEnemy)
	{
		pEnemy->InitObstacleEnemy(this->m_pGameSettings->m_fObstacleSpeed1);
		pEnemy->SetActive(TRUE);

		D3DXVECTOR3 pos;

		// checks that the enemy doesn't collide 
		// with existing enemies and obstacles
		int maxTryOuts = 5;

		for (int i = 0; i < maxTryOuts; i++)
		{
			bool bCollision = false;

			// generate a random enemy position
			pos = D3DXVECTOR3(
				this->m_pTheApp->RandFloat(-this->m_fScreenWidth, this->m_fScreenWidth),
				fPosY, 0.0f);

			pEnemy->SetPosition(pos);

			// checks collision against other enemies
			this->m_pObstacleEnemies.SetFirst();
			while (this->m_pObstacleEnemies.GetCurrent())
			{
				// enemy doesn't collide yet
				// otherwise skip collision check
				if (!bCollision)
				{
					IEnemy* pOther = this->m_pObstacleEnemies.GetCurrent();

					// bounding box collision
					if (this->IsBoxCollision(pEnemy->GetPosition(),
						pEnemy->GetWidth() + 8.0f,
						pEnemy->GetHeight() + 8.0f,
						pOther->GetPosition(),
						pOther->GetWidth() + 8.0f,
						pOther->GetHeight() + 8.0f))
					{
						bCollision = true;
					}
				}
				this->m_pObstacleEnemies.SetNext();
			}
			// enemy doesn't collide yet
			if (!bCollision)
			{
				// check collision against obstacles
				if (this->IsBoxCollisionEnemyVsObstacles(pEnemy))
				{
					bCollision = true;
				}
			}

			if (!bCollision)
			{
				return pEnemy;
			}
		}
	}

	if (pEnemy)
	{
		pEnemy = NULL;
	}

	return NULL;

	//END************** OBSTACLE ENEMY **************
}

void CTheGame::EnemyLaunch(float fFrametime)
{
	//START************ ENEMY LAUNCH **************

	static float s_fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.3f);

	static bool s_bFirstEnemy = true;
	static bool s_bLastEnemy = false;
	static bool s_bFirstLaunchFleet = true;

	float fTimeLimit;

	// first enemy...
	if (s_bFirstEnemy)
	{
		this->m_pLaunchEnemies[m_iFleetLaunch].SetFirst();

		// Game is currently in the first launch fleet...
		if (s_bFirstLaunchFleet)
		{
			// and level's first enemy attack is launch fleet
			if (this->m_pLevel->GetLaunchFirst())
			{
				fTimeLimit = this->m_pLevel->GetTimeEnemyLaunch();
				s_bFirstEnemy = false;
			}
			else
			{
				// seamless attack after the last fleet
				fTimeLimit = 0.0f;
			}
		}
		// not in the first launch fleet
		else
		{
			// seamless attack after the last fleet
			fTimeLimit = 0.0f;
		}
	}
	// not first enemy
	else
	{
		fTimeLimit = this->m_pLevel->GetTimeEnemyLaunch() + s_fRandTime;
	}

	// counter reached a required value
	if (this->m_fEnemyLaunchCounter >= (fTimeLimit - this->m_fVelocityTimeMargin))
	{
		// currently less than max enemies on screen
		if (this->m_iMaxEnemies < this->m_pLevel->GetMaxEnemiesScreen())
		{
			IEnemy* pEnemy = this->m_pLaunchEnemies[this->m_iFleetLaunch].GetCurrent();

			if (pEnemy)
			{
				D3DXVECTOR3 pos;
				float fPosY = 0.0f;

				float fBorderLeft = -this->m_fScreenWidth + (pEnemy->GetWidth() / 1.5f);
				float fBorderRight = this->m_fScreenWidth - (pEnemy->GetWidth() / 1.5f);

				switch (pEnemy->GetType())
				{
				case IEnemy::eTYPE_DRONE:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(17.0f, this->m_fScreenHeight);
					break;
				case IEnemy::eTYPE_SNIPER:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(20.0f, this->m_fScreenHeight);
					break;
				case IEnemy::eTYPE_ROLLER:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(35.0f, this->m_fScreenHeight);
					break;
				}

				int iCheckTimes = 0;
				bool bLoop = true;

				// checks that the new enemy doesn't collide with existing obstacles or enemies
				while (bLoop)
				{
					// tries 3 times before stopping
					if (iCheckTimes == 3)
					{
						bLoop = false;
					}
					else
					{
						bool bCollision = false;

						// generate a random enemy position
						pos = D3DXVECTOR3(
							this->m_pTheApp->RandFloat(fBorderLeft + 3.0f, fBorderRight - 3.0f),
							fPosY, 0.0f);

						pEnemy->SetPosition(pos);

						// check collision against obstacles
						this->m_pObstaclesDepth1.SetFirst();
						while (this->m_pObstaclesDepth1.GetCurrent())
						{
							// enemy doesn't collide yet, otherwise skip collision check
							if (!bCollision)
							{
								CObstacle* pObstacle = this->m_pObstaclesDepth1.GetCurrent();

								if (pObstacle->IsActive())
								{
									// bounding box collision
									if (this->IsBoxCollision(pEnemy->GetPosition(),
										pEnemy->GetWidth(),
										pEnemy->GetHeight(),
										pObstacle->GetPosition(),
										pObstacle->GetWidth() + 3.0f,
										pObstacle->GetHeight() + 3.0f))
									{
										bCollision = true;

										/*
										// mesh to mesh collision
										if(this->IsMeshCollision(pEnemy, pObstacle, false, false))
										{
											bCollision = true;
										}
										*/
									}
								}
							}
							this->m_pObstaclesDepth1.SetNext();
						}
						// enemy doesn't collide yet, otherwise skip collision check
						if (!bCollision)
						{
							// checks collision against enemies
							this->m_pActiveEnemies.SetFirst();
							while (this->m_pActiveEnemies.GetCurrent())
							{
								// enemy doesn't collide yet, otherwise skip collision check
								if (!bCollision)
								{
									IEnemy* pOther = this->m_pActiveEnemies.GetCurrent();

									if (pOther->IsActive())
									{
										// bounding box collision
										if (this->IsBoxCollision(pEnemy->GetPosition(),
											pEnemy->GetWidth(),
											pEnemy->GetHeight(),
											pOther->GetPosition(),
											pOther->GetWidth() + 3.0f,
											pOther->GetHeight() + 3.0f))
										{
											bCollision = true;

											/*
											// mesh to mesh collision
											if(this->IsMeshCollision(pEnemy, pOther, false, false))
											{

											}
											*/
										}
									}
								}
								this->m_pActiveEnemies.SetNext();
							}
						}
						if (!bCollision)
						{
							if (!this->ActiveEnemyLineOfFire(pEnemy, false))
							{
								bCollision = true;
							}
						}
						if (bCollision)
						{
							iCheckTimes++;
						}
						else
						{
							bLoop = false;

							pEnemy->SetDepth(IEnemy::eENEMY_DEPTH_1);
							pEnemy->SetActive(TRUE);

							this->m_pActiveEnemies.Push(pEnemy);
							this->m_iMaxEnemies++;

							// current enemy is the last one
							this->m_pLaunchEnemies[m_iFleetLaunch].SetNext();
							if (!this->m_pLaunchEnemies[m_iFleetLaunch].GetCurrent())
							{
								s_bLastEnemy = true;
								this->m_pLaunchEnemies[m_iFleetLaunch].Clear();
							}

							s_fRandTime = this->m_pTheApp->RandFloat(0.0f, 1.0f);
							this->m_fEnemyLaunchCounter = 0.0f;

							if (s_bFirstEnemy)
							{
								s_bFirstEnemy = false;
							}
						}
					}
				}
			}

			// no more enemy ships in the current launch fleet
			if (!pEnemy || s_bLastEnemy)
			{
				this->m_pActiveEnemies.SetFirst();

				// all active enemies have been destroyed
				if (!m_pActiveEnemies.GetCurrent())
				{
					this->m_iFleetLaunch++;

					// game over action is rolling
					if (this->m_iGameState == GAME_STATE_END_FAILED)
					{
						// go back to first active enemies
						if (this->m_iFleetLaunch == this->m_pLevel->GetFleetsLaunch())
						{
							this->m_iFleetLaunch = 0;
						}
					}

					this->m_bFleetLaunch = false;
					this->m_bFleetStrike = false;

					s_bFirstEnemy = true;
					s_bLastEnemy = false;
					s_bFirstLaunchFleet = false;

					// no more launch fleets in this level
					// set value to 'true' for the next level
					if (this->m_iFleetLaunch == this->m_pLevel->GetFleetsLaunch())
					{
						s_bFirstLaunchFleet = true;
					}

					// no more strike fleets left
					if (this->m_iFleetStrike == this->m_pLevel->GetFleetsStrike())
					{
						// launch fleets still left
						if (this->m_iFleetLaunch < this->m_pLevel->GetFleetsLaunch())
						{
							this->m_bFleetLaunch = true;
						}
					}
					// still strike fleets left
					else
					{
						this->m_bFleetStrike = true;
					}
				}
			}
		}
	}
	// updates counter
	else
	{
		this->m_fEnemyLaunchCounter += fFrametime;
	}

	//END************** ENEMY LAUNCH **************
}

void CTheGame::EnemyStrike(float fFrametime)
{
	//START************ ENEMY STRIKE **************

	static float s_fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.2f);

	static bool s_bFirstEnemy = true;
	static bool s_bLastEnemy = false;
	static bool s_bFirstStrikeFleet = true;

	float fTimeLimit;

	// first enemy...
	if (s_bFirstEnemy)
	{
		this->m_pStrikeEnemies[m_iFleetStrike].SetFirst();

		// in the first launch fleet...
		if (s_bFirstStrikeFleet)
		{
			// and level's first enemy attack is launch fleet
			if (this->m_pLevel->GetStrikeFirst())
			{
				fTimeLimit = this->m_pLevel->GetTimeEnemyStrike();
				s_bFirstEnemy = false;
			}
			else
			{
				// seamless attack after the last fleet
				fTimeLimit = 0.0f;
			}
		}
		// not in the first launch fleet
		else
		{
			// seamless attack after the last fleet
			fTimeLimit = 0.0f;
		}
	}
	// not first enemy
	else
	{
		fTimeLimit = this->m_pLevel->GetTimeEnemyStrike() + s_fRandTime;
	}

	// counter reached a required value
	if (this->m_fEnemyStrikeCounter >= (fTimeLimit - this->m_fVelocityTimeMargin))
	{
		// currently less than max enemies on screen
		if (this->m_iMaxEnemies < this->m_pLevel->GetMaxEnemiesScreen())
		{
			IEnemy* pEnemy = this->m_pStrikeEnemies[m_iFleetStrike].GetCurrent();

			if (pEnemy)
			{
				D3DXVECTOR3 pos;
				float fPosY = 0.0f;

				switch (pEnemy->GetType())
				{
				case IEnemy::eTYPE_DRONE:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(17.0f, this->m_fScreenHeight);
					break;
				case IEnemy::eTYPE_SNIPER:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(20.0f, this->m_fScreenHeight);
					break;
				case IEnemy::eTYPE_ROLLER:
					fPosY = this->m_fScreenHeight + this->m_pTheApp->RandFloat(35.0f, this->m_fScreenHeight);
					break;
				}

				int iCheckTimes = 0;
				bool bLoop = true;

				// checks that the enemy doesn't collide 
				// with existing enemies and obstacles
				while (bLoop)
				{
					// tries 3 times before stopping
					if (iCheckTimes == 3)
					{
						bLoop = false;
					}
					else
					{
						bool bCollision = false;

						// generate a random enemy position
						pos = D3DXVECTOR3(
							this->m_pTheApp->RandFloat(-this->m_fScreenWidth, this->m_fScreenWidth),
							fPosY, 0.0f);

						pEnemy->SetPosition(pos);

						// checks collision against other enemies

						this->m_pActiveEnemies.SetFirst();
						while (this->m_pActiveEnemies.GetCurrent())
						{
							// enemy doesn't collide yet
							// otherwise skip collision check
							if (!bCollision)
							{
								IEnemy* pOther = this->m_pActiveEnemies.GetCurrent();

								if (pOther->IsActive())
								{
									// bounding box collision
									if (this->IsBoxCollision(pEnemy->GetPosition(),
										pEnemy->GetWidth(),
										pEnemy->GetHeight(),
										pOther->GetPosition(),
										pOther->GetWidth() + 3.0f,
										pOther->GetHeight() + 3.0f))
									{
										bCollision = true;

										/*
										// mesh to mesh collision
										if(this->IsMeshCollision(pEnemy, pOther, false, false))
										{

										}
										*/
									}
								}
							}
							this->m_pActiveEnemies.SetNext();
						}
						// enemy doesn't collide yet
						if (!bCollision)
						{
							// check line of fire
							if (!this->ActiveEnemyLineOfFire(pEnemy, false))
							{
								bCollision = true;
							}
						}
						if (bCollision)
						{
							iCheckTimes++;
						}
						else
						{
							bLoop = false;

							s_fRandTime = this->m_pTheApp->RandFloat(0.0f, 0.3f);
							this->m_fEnemyStrikeCounter = 0.0f;

							if (s_bFirstEnemy)
							{
								s_bFirstEnemy = false;
							}

							pEnemy->SetDepth(IEnemy::eENEMY_DEPTH_1);
							pEnemy->SetActive(TRUE);

							this->m_pActiveEnemies.Push(pEnemy);
							this->m_iMaxEnemies++;

							// current enemy is the last one
							this->m_pStrikeEnemies[m_iFleetStrike].SetNext();
							if (!this->m_pStrikeEnemies[m_iFleetStrike].GetCurrent())
							{
								s_bLastEnemy = true;
								this->m_pStrikeEnemies[m_iFleetStrike].Clear();
							}
						}
					}
				}
			}

			// no more enemy ships in the current strike fleet
			if (!pEnemy || s_bLastEnemy)
			{
				// no active enemies left
				this->m_pActiveEnemies.SetFirst();
				if (!m_pActiveEnemies.GetCurrent())
				{
					this->m_iFleetStrike++;

					// game over action is rolling
					if (this->m_iGameState == GAME_STATE_END_FAILED)
					{
						// go back to first active enemies
						if (this->m_iFleetStrike == this->m_pLevel->GetFleetsStrike())
						{
							this->m_iFleetStrike = 0;
						}
					}

					this->m_bFleetLaunch = false;
					this->m_bFleetStrike = false;

					s_bFirstEnemy = true;
					s_bLastEnemy = false;
					s_bFirstStrikeFleet = false;

					// no more strike fleets in this level
					// set value to 'true' for the next level
					if (this->m_iFleetStrike == this->m_pLevel->GetFleetsStrike())
					{
						s_bFirstStrikeFleet = true;
					}

					// no more launch fleets left
					if (this->m_iFleetLaunch == this->m_pLevel->GetFleetsLaunch())
					{
						// strike fleets still left
						if (this->m_iFleetStrike < this->m_pLevel->GetFleetsStrike())
						{
							this->m_bFleetStrike = true;
						}
					}
					// still launch fleets left
					else
					{
						this->m_bFleetLaunch = true;
					}
				}
			}
		}
	}
	// updates counter
	else
	{
		this->m_fEnemyStrikeCounter += fFrametime;
	}

	//END************** ENEMY STRIKE **************
}

void CTheGame::EnemyExplosion(IEnemy* pEnemy)
{
	//START************ ENEMY EXPLOSION **************

	CExplosion::eEXPLOSION_TYPE explosionType = CExplosion::eEXPLOSION_TYPE_NONE;

	switch (pEnemy->GetType())
	{
	case IEnemy::eTYPE_DRONE:
		explosionType = CExplosion::eEXPLOSION_TYPE_DRONE;
		break;

	case IEnemy::eTYPE_SNIPER:
		explosionType = CExplosion::eEXPLOSION_TYPE_SNIPER;
		break;

	case IEnemy::eTYPE_ROLLER:
		explosionType = CExplosion::eEXPLOSION_TYPE_ROLLER;
		break;

	//case IEnemy::eTYPE_GUARD:
		//explosionType = CExplosion::eEXPLOSION_TYPE_GUARD;
	//	break;
	};

	if (explosionType != CExplosion::eEXPLOSION_TYPE_NONE)
	{
		m_pExplosions->AddExplosion(explosionType,
									this->m_iExplosionMoveSpeed,
									this->m_fExplosionMovePause,
									pEnemy->GetPosition());
	}

	//END************** ENEMY EXPLOSION **************
}

HRESULT CTheGame::GenerateParticlesBullet(CWeapon* pWeapon, D3DXVECTOR3 vPosition)
{
	/*
	CParticleSystem* particles = new CParticleSystem();

	if(particles)
	{	
		switch(pWeapon->GetBulletType())
		{
		case CWeapon::eBULLET_TYPE_PLAYER_FRONT:
			particles->SetColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL:
			particles->SetColor( D3DXCOLOR( 1.0f, 0.0f, 0.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_ENEMY_DRONE:
			particles->SetColor( D3DXCOLOR( 0.0f, 1.0f, 0.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_ENEMY_SNIPER:
			particles->SetColor( D3DXCOLOR( 0.0f, 0.0f, 1.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_ENEMY_ROLLER:
			particles->SetColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_ENEMY_GUARD:
			particles->SetColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_BOSS_1_LASER:
			particles->SetColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 0.1f ));
			break;

		case CWeapon::eBULLET_TYPE_BOSS_1_SCATTER:
			particles->SetColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 0.1f ));
			break;
		}

		particles->SetTexture( _T("textures\\in-game\\particles\\bullet.tga") );
		particles->SetMaxParticles( 10 );
		particles->SetNumToRelease( 10 );
		particles->SetReleaseInterval( 0.0f );
		particles->SetSize( 0.08f );
		particles->SetLifeCycle( 0.5f );
		particles->SetPosition(vPosition); // position of the emitter
		particles->SetParticleVelocity( D3DXVECTOR3( 0.0f, 7.0f, 0.0f ) );
		particles->SetForces( D3DXVECTOR3(0.0f, -6.0f, 0.0f));
		particles->SetVelocityFactor( 1.3f );
		particles->SetLifeTimer(0.5f);

		// Iniitialize this particle system
		particles->Initialize(this->m_pTheApp->GetDevice());
		particles->SetActive(true);

		this->m_pParticles.Push(particles);
	}
	*/

	return S_OK;
}


void CTheGame::NormalSpeedReinforcement()
{
	this->m_pReinforcements.SetFirst();
	while( this->m_pReinforcements.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();
		pEnemy->SetSpeedChange(false);

		this->m_pReinforcements.SetNext();
	}
}

void CTheGame::IncreaseSpeedReinforcement()
{
	this->m_pReinforcements.SetFirst();
	while( this->m_pReinforcements.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

		if(pEnemy->GetReinforcementAction() == IEnemy::eREINFORCEMENT_ACTION_SENT)
		{
			pEnemy->SetSpeedChange(true);
		}
		this->m_pReinforcements.SetNext();
	}
}

void CTheGame::NormalSpeedObstacle()
{
	this->m_pObstaclesDepth2.SetFirst();
	while(this->m_pObstaclesDepth2.GetCurrent())
	{
		if(this->m_pObstaclesDepth2.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth2.GetCurrent()->SetSpeedChange(false);
		}
		this->m_pObstaclesDepth2.SetNext();
	}

	this->m_pObstaclesDepth3.SetFirst();
	while(this->m_pObstaclesDepth3.GetCurrent())
	{
		if(this->m_pObstaclesDepth3.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth3.GetCurrent()->SetSpeedChange(false);
		}
		this->m_pObstaclesDepth3.SetNext();
	}

	this->m_pObstaclesDepth4.SetFirst();
	while(this->m_pObstaclesDepth4.GetCurrent())
	{
		if(this->m_pObstaclesDepth4.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth4.GetCurrent()->SetSpeedChange(false);
		}
		this->m_pObstaclesDepth4.SetNext();
	}

	this->m_pObstaclesDepth5.SetFirst();
	while(this->m_pObstaclesDepth5.GetCurrent())
	{
		if(this->m_pObstaclesDepth5.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth5.GetCurrent()->SetSpeedChange(false);
		}
		this->m_pObstaclesDepth5.SetNext();
	}
}

void CTheGame::IncreaseSpeedObstacle()
{
	this->m_pObstaclesDepth2.SetFirst();
	while(this->m_pObstaclesDepth2.GetCurrent())
	{
		if(this->m_pObstaclesDepth2.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth2.GetCurrent()->SetSpeedChange(true);
		}
		this->m_pObstaclesDepth2.SetNext();
	}

	this->m_pObstaclesDepth3.SetFirst();
	while(this->m_pObstaclesDepth3.GetCurrent())
	{
		if(this->m_pObstaclesDepth3.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth3.GetCurrent()->SetSpeedChange(true);
		}
		this->m_pObstaclesDepth3.SetNext();
	}

	this->m_pObstaclesDepth4.SetFirst();
	while(this->m_pObstaclesDepth4.GetCurrent())
	{
		if(this->m_pObstaclesDepth4.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth4.GetCurrent()->SetSpeedChange(true);
		}
		this->m_pObstaclesDepth4.SetNext();
	}

	this->m_pObstaclesDepth5.SetFirst();
	while(this->m_pObstaclesDepth5.GetCurrent())
	{
		if(this->m_pObstaclesDepth5.GetCurrent()->IsActive())
		{
			this->m_pObstaclesDepth5.GetCurrent()->SetSpeedChange(true);
		}
		this->m_pObstaclesDepth5.SetNext();
	}
}


void CTheGame::BossFrameChainExplosion()
{
	//START************ BOSS CORE CHAIN EXPLOSION **************

	CExplosion::eEXPLOSION_TYPE explosionType = CExplosion::eEXPLOSION_TYPE_NONE;
	D3DXVECTOR3 pos = this->m_pEnemyBoss1Frame->GetPosition();

	int iRandChainExplosion = this->m_pTheApp->RandInt(1,3);

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		switch(iRandChainExplosion)
		{
		case 1:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_1;
			break;

		case 2:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_2;
			break;

		case 3:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_3;
			break;
		}

		break;

	case 2:

		switch(iRandChainExplosion)
		{
		case 1:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_1;
			break;

		case 2:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_2;
			break;

		case 3:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_3;
			break;
		}

		break;

	case 3:

		switch(iRandChainExplosion)
		{
		case 1:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_1;
			break;

		case 2:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_2;
			break;

		case 3:
			explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_3;
			break;
		}

		break;
	}

	if (explosionType != CExplosion::eEXPLOSION_TYPE_NONE)
	{
		m_pExplosions->AddExplosion(explosionType,
									this->m_iExplosionMoveSpeed,
									this->m_fExplosionMovePause,
									pos);
	}

	//END************** BOSS CORE CHAIN EXPLOSION **************
}

void CTheGame::BossFrameBigExplosion()
{
	//START************ BOSS FRAME BIG EXPLOSION **************

	CExplosion::eEXPLOSION_TYPE explosionType = CExplosion::eEXPLOSION_TYPE_NONE;
	D3DXVECTOR3 pos = this->m_pEnemyBoss1Frame->GetPosition();

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_BIG;
		break;

	case 2:
		explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_BIG;
		break;

	case 3:
		explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_BIG;
		break;
	}

	if (explosionType != CExplosion::eEXPLOSION_TYPE_NONE)
	{
		m_pExplosions->AddExplosion(explosionType,
									this->m_iExplosionMoveSpeed,
									this->m_fExplosionMovePause,
									pos);
	}

	// deactivate boss frame

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		this->m_pEnemyBoss1Frame->SetActive(FALSE);
		break;
	case 2:
		this->m_pEnemyBoss1Frame->SetActive(FALSE);
		break;
	case 3:
		this->m_pEnemyBoss1Frame->SetActive(FALSE);
		break;
	}

	// boss parts also explodes if they are active
	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		// left scatter explosion
		if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
		}
		// right scatter explosion
		if( this->m_pEnemyBoss1ScatterRight->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
		}

		break;

	case 2:

		// left scatter explosion
		if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
		}
		// right scatter explosion
		if( this->m_pEnemyBoss1ScatterRight->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
		}

		break;

	case 3:

		// left scatter explosion
		if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
		}
		// right scatter explosion
		if( this->m_pEnemyBoss1ScatterRight->IsActive() )
		{
			this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
		}

		break;
	}

	// deactivate all the active boss parts
	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		if(this->m_pEnemyBoss1ScatterLeft->IsActive())
		{
			this->m_pEnemyBoss1ScatterLeft->SetActive(FALSE);
		}
		if(this->m_pEnemyBoss1ScatterRight->IsActive())
		{
			this->m_pEnemyBoss1ScatterRight->SetActive(FALSE);
		}

		break;

	case 2:

		if(this->m_pEnemyBoss1ScatterLeft->IsActive())
		{
			this->m_pEnemyBoss1ScatterLeft->SetActive(FALSE);
		}
		if(this->m_pEnemyBoss1ScatterRight->IsActive())
		{
			this->m_pEnemyBoss1ScatterRight->SetActive(FALSE);
		}

		break;

	case 3:

		if(this->m_pEnemyBoss1ScatterLeft->IsActive())
		{
			this->m_pEnemyBoss1ScatterLeft->SetActive(FALSE);
		}
		if(this->m_pEnemyBoss1ScatterRight->IsActive())
		{
			this->m_pEnemyBoss1ScatterRight->SetActive(FALSE);
		}

		break;
	}

	//END************** BOSS FRAME BIG EXPLOSION **************
}

void CTheGame::BossPartExplosion(IEnemy* pEnemy)
{
	//START************ BOSS PART EXPLOSION **************

	CExplosion::eEXPLOSION_TYPE explosionType = CExplosion::eEXPLOSION_TYPE_NONE;
	D3DXVECTOR3 pos = pEnemy->GetPosition();

	switch( pEnemy->GetType() )
	{
	case IEnemy::eTYPE_BOSS_1_LASER_LEFT:
	case IEnemy::eTYPE_BOSS_1_LASER_RIGHT:
	case IEnemy::eTYPE_BOSS_1_SCATTER_LEFT:
	case IEnemy::eTYPE_BOSS_1_SCATTER_RIGHT:
		explosionType = CExplosion::eEXPLOSION_TYPE_BOSS_1_PART;
		break;
	}

	if (explosionType != CExplosion::eEXPLOSION_TYPE_NONE)
	{
		m_pExplosions->AddExplosion(explosionType,
									this->m_iExplosionMoveSpeed,
									this->m_fExplosionMovePause,
									pos);
	}

	if(pEnemy->IsActive())
	{
		pEnemy->SetActive(FALSE);
	}

	//END************** BOSS PART EXPLOSION **************
}

bool CTheGame::CheckBossPartExplosion(int iCountBossChainExplosions)
{
	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
	case 2:
	case 3:

		if( iCountBossChainExplosions == ( int(EXPLOSION_CHAIN_REPEATS_BOSS_1 * 0.8f) ) || 
			iCountBossChainExplosions == ( int(EXPLOSION_CHAIN_REPEATS_BOSS_1 * 0.6f) ) ||
			iCountBossChainExplosions == ( int(EXPLOSION_CHAIN_REPEATS_BOSS_1 * 0.4f) ) ||
			iCountBossChainExplosions == ( int(EXPLOSION_CHAIN_REPEATS_BOSS_1 * 0.2f) ) )
		{
			switch(this->m_pTheApp->RandInt(1,4))
			{
			case 1:

				if(this->m_pEnemyBoss1ScatterRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1LaserRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1LaserLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
					this->PlaySoundExplosionBossPart();
				}

				break;

			case 2:

				if(this->m_pEnemyBoss1LaserRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1LaserLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
					this->PlaySoundExplosionBossPart();
				}

				break;

			case 3:

				if(this->m_pEnemyBoss1ScatterLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
					this->PlaySoundExplosionBossPart();
				}
				
				else if(this->m_pEnemyBoss1LaserRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1LaserLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
					this->PlaySoundExplosionBossPart();
				}

				break;

			case 4:

				if(this->m_pEnemyBoss1LaserLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1LaserRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterRight->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
					this->PlaySoundExplosionBossPart();
				}
				else if(this->m_pEnemyBoss1ScatterLeft->IsActive())
				{
					// explosion
					this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
					this->PlaySoundExplosionBossPart();
				}

				break;
			}

			return true;
		}
		
		break;
	}

	return false;
}

void CTheGame::EnemyShooting()
{
	//START**************** ENEMY SHOOTING ************************

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		// active enemies
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			// roller has it's own shooting function
			if(pEnemy->GetType() != IEnemy::eTYPE_ROLLER)
			{
				if( pEnemy->IsActive() )
				{
					//if( this->ActiveEnemyLineOfFire(pEnemy, false) )
					//{
						if( pEnemy->Shoot() )
						{
							EnemyShoots(pEnemy);
						}
					//}
				}
			}
			this->m_pActiveEnemies.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) ||
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		// obstacle enemies
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			// roller has it's own shooting function
			if(pEnemy->GetType() != IEnemy::eTYPE_ROLLER)
			{
				if(	pEnemy->IsActive() && 
					(pEnemy->GetPosition().y <= this->m_fScreenHeight + pEnemy->GetHeight()))
				{
					if( this->ObstacleEnemyLineOfFire(pEnemy, false) )
					{
						if( pEnemy->Shoot() )
						{
							EnemyShoots(pEnemy);
						}
					}
				}
			}
			this->m_pObstacleEnemies.SetNext();
		}
	}

	//END****************** ENEMY SHOOTING ************************
}

void CTheGame::EnemyShoots(IEnemy* pEnemy)
{
	//START***************** ENEMY SHOOTS *****************

	CWeapon* weapon = NULL;

	switch( pEnemy->GetType() )
	{
	case IEnemy::eTYPE_DRONE:

		weapon = new CWeaponEnemyDrone();

		if(weapon)
		{
			weapon->Create(	this->m_pTheApp->GetDevice(),
							this->m_pWeaponDrone->GetMesh(),
							this->m_pWeaponDrone->GetMeshDataArray(),
							this->m_pWeaponDrone->GetWidth(),
							this->m_pWeaponDrone->GetHeight(),
							this->m_pWeaponDrone->GetSpeed(), 
							this->m_pWeaponDrone->GetDamage(),
							this->m_pWeaponDrone->GetBulletType());
		}

		break;

	case IEnemy::eTYPE_SNIPER:

		weapon = new CWeaponEnemySniper();

		if(weapon)
		{
			weapon->Create(	this->m_pTheApp->GetDevice(),
							this->m_pWeaponSniper->GetMesh(),
							this->m_pWeaponSniper->GetMeshDataArray(),
							this->m_pWeaponSniper->GetWidth(),
							this->m_pWeaponSniper->GetHeight(),
							this->m_pWeaponSniper->GetSpeed(), 
							this->m_pWeaponSniper->GetDamage(),
							this->m_pWeaponSniper->GetBulletType());
		}

		break;
	}
	if(weapon)
	{
		weapon->SetMatrix(pEnemy);
		weapon->InitPosition();

		weapon->SetOwner(CWeapon::eOWNER_ENEMY);
		weapon->SetShipObject(pEnemy);

		weapon->SetVisible(true);
		this->m_pBullets.Push(weapon);

		// play sound effect
		this->PlaySoundFireEnemy(pEnemy);

		/* COLLISION MODEL */
		this->CreateCollisionMeshWeapons(weapon);
	}

	//END******************* ENEMY SHOOTS *****************
}

bool CTheGame::ActiveEnemyLineOfFire(IEnemy* pEnemy, bool bInverse)
{
	//START*********** ACTIVE ENEMY LINE OF FIRE *******************

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	posA = pEnemy->GetPosition();

	float widthB;

	this->m_pActiveEnemies.SetFirst();
	while( this->m_pActiveEnemies.GetCurrent() )
	{
		IEnemy* pOther = this->m_pActiveEnemies.GetCurrent();

		if( pOther->IsActive() )
		{
			// no need to check itself
			if( pEnemy != pOther )
			{
				posB = pOther->GetPosition();
				widthB = pOther->GetWidth();

				float fLeftSide = posB.x - (widthB * 2.0f);
				float fRightSide = posB.x + (widthB * 2.0f);

				if(	(posA.x >= fLeftSide) && 
					(posA.x <= fRightSide))
				{
					// check line from up to down
					if(!bInverse)
					{
						if( posA.y >= posB.y )
						{
							return false;
						}
					}
					// check line from down to up
					else if(bInverse)
					{
						if( posA.y <= posB.y )
						{
							return false;
						}
					}
				}
			}
		}
		this->m_pActiveEnemies.SetNext();
	}

	return true;

	//END************* ACTIVE ENEMY LINE OF FIRE *******************
}

bool CTheGame::ReinforcementLineOfFire(IEnemy* pEnemy, IEnemy* pOther,  bool bInverse)
{
	//START*********** REINFORCEMENT LINE OF FIRE *******************

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	posA = pEnemy->GetPosition();

	float widthB;

	if( pOther->IsActive() )
	{
		// check line from up to down
		if(!bInverse)
		{
			posB = pOther->GetPosition();
			widthB = pOther->GetWidth();

			float fLeftSide = posB.x - (widthB * 2.0f);
			float fRightSide = posB.x + (widthB * 2.0f);

			if(	(posA.x >= fLeftSide) && 
				(posA.x <= fRightSide))
			{
				if( posA.y >= posB.y )
				{
					return false;
				}
			}
		}
		// check line from down to up
		else if(bInverse)
		{
			posB = pOther->GetPosition();
			widthB = pOther->GetWidth();

			float fLeftSide = posB.x - (widthB * 2.0f);
			float fRightSide = posB.x + (widthB * 2.0f);

			if(	(posA.x >= fLeftSide) && 
				(posA.x <= fRightSide))
			{
				if( posA.y <= posB.y )
				{
					return false;
				}
			}
		}
	}

	return true;

	//END************* REINFORCEMENT LINE OF FIRE *******************
}

bool CTheGame::ObstacleEnemyLineOfFire(IEnemy* pEnemy, bool bInverse)
{
	//START*********** OBSTACLE ENEMY LINE OF FIRE *******************

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	posA = pEnemy->GetPosition();

	float widthB;

	this->m_pObstacleEnemies.SetFirst();
	while( this->m_pObstacleEnemies.GetCurrent() )
	{
		IEnemy* pOther = this->m_pObstacleEnemies.GetCurrent();

		if( pOther->IsActive() )
		{
			// no need to check itself
			if( pEnemy != pOther )
			{
				posB = pOther->GetPosition();
				widthB = pOther->GetWidth();

				float fLeftSide = posB.x - (widthB * 2.0f);
				float fRightSide = posB.x + (widthB * 2.0f);

				if(	(posA.x >= fLeftSide) && 
					(posA.x <= fRightSide))
				{
					// check line from up to down
					if(!bInverse)
					{
						if( posA.y >= posB.y )
						{
							return false;
						}
					}
					// check line from down to up
					else if(bInverse)
					{
						if( posA.y <= posB.y )
						{
							return false;
						}
					}
				}
			}
		}
		this->m_pObstacleEnemies.SetNext();
	}

	return true;

	//END************* OBSTACLE ENEMY LINE OF FIRE *******************
}

void CTheGame::EnemyCopyBullets(IEnemy* pEnemy)
{
	CQueue<CWeapon*>* pBullets = pEnemy->GetBullets();

	if( pEnemy->GetType() == IEnemy::eTYPE_ROLLER)
	{
		pBullets->SetFirst();
		while( pBullets->GetCurrent() )
		{
			if( pBullets->GetCurrent()->IsActive() )
			{
				CWeapon* weapon = new CWeaponEnemyRoller();
				weapon = pBullets->GetCurrent();

				this->m_pBullets.Push(weapon);
			}
			pBullets->SetNext();
		}
	}
}

float CTheGame::GetCollisionDamagePlayerVsEnemy(IEnemy* pEnemy)
{
	switch (pEnemy->GetType())
	{
	case IEnemy::eTYPE_DRONE:
		return m_pGameSettings->m_iEnemyDroneShipDamage;
	case IEnemy::eTYPE_SNIPER:
		return m_pGameSettings->m_iEnemySniperShipDamage;
	case IEnemy::eTYPE_ROLLER:
		return m_pGameSettings->m_iEnemyRollerShipDamage;
	case IEnemy::eTYPE_GUARD:
		return m_pGameSettings->m_iEnemyGuardShipDamage;
	}

	return 0;
}

void CTheGame::CollisionPlayerVsBoss()
{
	//START************* PLAYER VS BOSS ***************

	if(	!this->m_pPlayer->IsDestroyed() && 
		!this->m_pPlayer->IsUntouchable() )
	{
		switch( this->m_pLevel->GetLevelNumber() )
		{
		case 1:
		case 2:
		case 3:

			if( this->m_pEnemyBoss1Frame->IsActive() )
			{
				this->m_pEnemyBoss1Frame->CollisionEnemyVsPlayer(this->m_pPlayer);
			}
			if( this->m_pEnemyBoss1LaserLeft->IsActive() )
			{
				this->m_pEnemyBoss1LaserLeft->CollisionEnemyVsPlayer(this->m_pPlayer);
			}
			if( this->m_pEnemyBoss1LaserRight->IsActive() )
			{
				this->m_pEnemyBoss1LaserRight->CollisionEnemyVsPlayer(this->m_pPlayer);
			}
			if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
			{
				this->m_pEnemyBoss1ScatterLeft->CollisionEnemyVsPlayer(this->m_pPlayer);
			}
			if( this->m_pEnemyBoss1ScatterRight->IsActive() )
			{
				this->m_pEnemyBoss1ScatterRight->CollisionEnemyVsPlayer(this->m_pPlayer);
			}
			break;
		}

		// player is destroyed
		if( !this->m_pPlayer->IsAlive() )
		{
			this->PlayerDestroyed();
			this->PlayerExplosion();
		}
	}

	//END*************** PLAYER VS BOSS ***************
}

void CTheGame::CollisionPlayerVsEnemy()
{
	//START************* PLAYER VS ENEMY ***************

	IEnemy* pEnemy = NULL;

	if(	!this->m_pPlayer->IsDestroyed() && 
		!this->m_pPlayer->IsUntouchable() )
	{
		bool bInverseMatrix = false;

		if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
		{
			// active enemies
			this->m_pActiveEnemies.SetFirst();
			while( this->m_pActiveEnemies.GetCurrent() )
			{
				pEnemy = this->m_pActiveEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					// bounding box collision
					if(this->IsBoxCollision(pEnemy->GetPosition(), 
											pEnemy->GetWidth(),
											pEnemy->GetHeight(),
											this->m_pPlayer->GetPosition(),
											this->m_pPlayer->GetWidth() / 2.0f,
											this->m_pPlayer->GetHeight() / 2.0f) )
					{
						// mesh to mesh collision
						//if(this->IsMeshCollision(pEnemy, this->m_pPlayer, bInverseMatrix, false))
						//{

						// Collision damage with enemy ship.
						int damageValue = GetCollisionDamagePlayerVsEnemy(pEnemy);
						this->m_pPlayer->DecreaseHealth(damageValue);

						if (!this->m_pPlayer->IsAlive())
						{
							this->PlayerDestroyed();
							this->PlayerExplosion();
						}
						else
						{
							// play sound effect
							this->PlaySoundExplosionEnemy(pEnemy);
						}

						// launch enemy killed
						if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH )
						{
							this->m_iEnemiesLaunch++;
						}
						// strike enemy killed
						else if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE )
						{
							this->m_iEnemiesStrike++;
						}

						this->EnemyCopyBullets(pEnemy);

						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);

						this->m_iMaxEnemies--;
						//}
					}
				}
				this->m_pActiveEnemies.SetNext();
			}
		}
		else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
				(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
		{
			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				pEnemy = this->m_pObstacleEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					// bounding box collision
					if(this->IsBoxCollision(pEnemy->GetPosition(), 
											pEnemy->GetWidth(),
											pEnemy->GetHeight(),
											this->m_pPlayer->GetPosition(),
											this->m_pPlayer->GetWidth() / 2.0f,
											this->m_pPlayer->GetHeight() / 2.0f) )
					{
						// mesh to mesh collision
						//if(this->IsMeshCollision(pEnemy, this->m_pPlayer, bInverseMatrix, false))
						//{
						
						// Collision damage with enemy ship.
						int damageValue = GetCollisionDamagePlayerVsEnemy(pEnemy);
						this->m_pPlayer->DecreaseHealth(damageValue);

						if (!this->m_pPlayer->IsAlive())
						{
							this->PlayerDestroyed();
							this->PlayerExplosion();
						}
						else
						{
							// play sound effect
							this->PlaySoundExplosionEnemy(pEnemy);
						}

						this->EnemyCopyBullets(pEnemy);

						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);
						//}
					}
				}
				this->m_pObstacleEnemies.SetNext();
			}
		}
	}

	//END*************** PLAYER VS ENEMY ***************
}

void CTheGame::CollisionPlayerCannonVsBoss(float fFrametime)
{
	//START*********** PLAYER CANNON VS BOSS **************

	if(this->m_ePlayerCannonState == ePLAYER_CANNON_STATE_BEAM)
	{
		// Boss scenario
		if(this->m_iGameState == GAME_STATE_BOSS_ACTION)
		{
			switch(this->m_pLevel->GetLevelNumber())
			{
			case 1:
			case 2:
			case 3:
				// enter scene has ended, boss can be damaged
				if( !this->m_pEnemyBoss1Frame->IsEnter() )
				{
					// boss frame
					if(this->m_pEnemyBoss1Frame->IsActive())
					{
						if( this->PlayerCannonLineOfFireEnemies(this->m_pEnemyBoss1Core) )
						{
							// shake boss
							this->UpdateBossShake(false, fFrametime);

							if(this->m_pEnemyBoss1Frame->IsCannonDamage())
							{
								if( this->m_pEnemyBoss1Frame->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
								{
									this->m_bBossDestroyed = true;
								}
								else
								{
									// increase player score (score increase equals cannon damage)
									this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage);
								}
								// only one hit per cannon fire
								this->m_pEnemyBoss1Frame->SetCannonDamage(false);
							}
						}
					}
#ifdef GAME_BOSS_PARTS_DAMAGE
					// laser left
					if(this->m_pEnemyBoss1LaserLeft->IsActive())
					{
						if(this->m_pEnemyBoss1LaserLeft->IsCannonDamage())
						{
							if( this->PlayerCannonLineOfFireEnemies(this->m_pEnemyBoss1LaserLeft) )
							{
								// only one hit per cannon fire
								this->m_pEnemyBoss1LaserLeft->SetCannonDamage(false);

								if( this->m_pEnemyBoss1LaserLeft->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
								{
									this->m_pEnemyBoss1LaserLeft->SetActive(FALSE);
									// enemy explosion
									this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
									// play sound effect
									this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
										(FALSE, 0, this->m_iVolumeSoundEffect);
								}
								else
								{
									// increase player score (score increase equals cannon damage)
									this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage);
								}
							}
						}
					}
					// laser right
					if(this->m_pEnemyBoss1LaserRight->IsActive())
					{
						if(this->m_pEnemyBoss1LaserRight->IsCannonDamage())
						{
							if( this->PlayerCannonLineOfFireEnemies(this->m_pEnemyBoss1LaserRight) )
							{
								// only one hit per cannon fire
								this->m_pEnemyBoss1LaserRight->SetCannonDamage(false);

								if( this->m_pEnemyBoss1LaserRight->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
								{
									this->m_pEnemyBoss1LaserRight->SetActive(FALSE);
									// enemy explosion
									this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
									// play sound effect
									this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
										(FALSE, 0, this->m_iVolumeSoundEffect);
								}
								else
								{
									// increase player score (score increase equals cannon damage)
									this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage);
								}
							}
						}
					}
					// scatter left
					if(this->m_pEnemyBoss1ScatterLeft->IsActive())
					{
						if(this->m_pEnemyBoss1ScatterLeft->IsCannonDamage())
						{
							if( this->PlayerCannonLineOfFireEnemies(this->m_pEnemyBoss1ScatterLeft) )
							{
								// only one hit per cannon fire
								this->m_pEnemyBoss1ScatterLeft->SetCannonDamage(false);

								if( this->m_pEnemyBoss1ScatterLeft->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
								{
									this->m_pEnemyBoss1ScatterLeft->SetActive(FALSE);
									// enemy explosion
									this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
									// play sound effect
									this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
										(FALSE, 0, this->m_iVolumeSoundEffect);
								}
								else
								{
									// increase player score (score increase equals cannon damage)
									this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage);
								}
							}
						}
					}
					// scatter right
					if(this->m_pEnemyBoss1ScatterRight->IsActive())
					{
						if(this->m_pEnemyBoss1ScatterRight->IsCannonDamage())
						{
							if( this->PlayerCannonLineOfFireEnemies(this->m_pEnemyBoss1ScatterRight) )
							{
								// only one hit per cannon fire
								this->m_pEnemyBoss1ScatterRight->SetCannonDamage(false);

								if( this->m_pEnemyBoss1ScatterRight->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
								{
									this->m_pEnemyBoss1ScatterRight->SetActive(FALSE);
									// enemy explosion
									this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
									// play sound effect
									this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
										(FALSE, 0, this->m_iVolumeSoundEffect);
								}
								else
								{
									// increase player score (score increase equals cannon damage)
									this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage);
								}
							}
						}
					}
#endif
				}
				break;
			}
		}
	}

	//END************* PLAYER CANNON VS BOSS **************
}

void CTheGame::CollisionPlayerCannonVsEnemy(float fFrametime)
{
	//START*********** PLAYER CANNON VS ENEMY **************

	if(this->m_ePlayerCannonState == ePLAYER_CANNON_STATE_BEAM)
	{
		if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
		{
			// active enemies
			this->m_pActiveEnemies.SetFirst();
			while( this->m_pActiveEnemies.GetCurrent() )
			{
				IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					if( this->PlayerCannonLineOfFireEnemies(pEnemy) )
					{
						// shake enemy
						this->UpdateEnemiesShake(pEnemy, false, fFrametime);

						if( pEnemy->IsCannonDamage() )
						{
							if( pEnemy->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
							{
								// play sound effect
								this->PlaySoundExplosionEnemy(pEnemy);

								this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());

								// launch enemy killed
								if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH )
								{
									this->m_iEnemiesLaunch++;
								}
								// strike enemy killed
								else if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE )
								{
									this->m_iEnemiesStrike++;
								}

								this->EnemyCopyBullets(pEnemy);

								pEnemy->ResetFleeMovement();
								pEnemy->SetActive(FALSE);

								this->m_iMaxEnemies--;
							}
							else
							{
								// increase player score (score increase equals 1/4 of cannon damage)
								this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage / 4);
							}

							pEnemy->SetCannonDamage(false);
						}
					}
				}
				this->m_pActiveEnemies.SetNext();
			}
		}
		else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
				(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
		{
			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					if( this->PlayerCannonLineOfFireEnemies(pEnemy) )
					{
						// shake enemy
						this->UpdateEnemiesShake(pEnemy, false, fFrametime);

						if( pEnemy->IsCannonDamage() )
						{
							if( pEnemy->Destroyed(this->m_pGameSettings->m_iPlayerCannonDamage) )
							{
								// play sound effect
								this->PlaySoundExplosionEnemy(pEnemy);

								this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());

								this->EnemyCopyBullets(pEnemy);

								pEnemy->ResetFleeMovement();
								pEnemy->SetActive(FALSE);
							}
							else
							{
								// increase player score (score increase equals 1/4 of cannon damage)
								this->m_pPlayer->IncreaseScore(this->m_pGameSettings->m_iPlayerCannonDamage / 4);
							}

							pEnemy->SetCannonDamage(false);
						}
					}
				}
				this->m_pObstacleEnemies.SetNext();
			}
		}
	}

	//END************* PLAYER CANNON VS ENEMY **************
}

void CTheGame::CollisionPlayerCannonVsBossBullet()
{
	//START********* PLAYER CANNON VS BOSS BULLET ************

	if(this->m_ePlayerCannonState == ePLAYER_CANNON_STATE_BEAM)
	{
		if( (this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			switch( this->m_pLevel->GetLevelNumber())
			{
			case 1:
				this->m_pEnemyBoss1Frame->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				break;
			case 2:
				this->m_pEnemyBoss1Frame->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				break;
			case 3:
				this->m_pEnemyBoss1Frame->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1LaserRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterLeft->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				this->m_pEnemyBoss1ScatterRight->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				break;
			}
		}
	}

	//END*********** PLAYER CANNON VS BOSS BULLET ************
}

void CTheGame::CollisionPlayerCannonVsEnemyBullet()
{
	//START********* PLAYER CANNON VS ENEMY BULLET ************

	if(this->m_ePlayerCannonState == ePLAYER_CANNON_STATE_BEAM)
	{
		if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
		{
			// active enemies
			this->m_pActiveEnemies.SetFirst();
			while( this->m_pActiveEnemies.GetCurrent() )
			{
				IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					pEnemy->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				}
				this->m_pActiveEnemies.SetNext();
			}
		}
		else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
				(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
		{
			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					pEnemy->CollisionPlayerCannonVsBullets(this->m_pPlayer);
				}
				this->m_pObstacleEnemies.SetNext();
			}
		}

		// bullets in general queue
		this->m_pBullets.SetFirst();
		while( this->m_pBullets.GetCurrent() )
		{
			if( this->m_pBullets.GetCurrent()->IsActive() )
			{
				if( this->PlayerCannonLineOfFireBullets(this->m_pBullets.GetCurrent()) )
				{
					this->m_pBullets.GetCurrent()->SetActive(FALSE);
				}
			}
			this->m_pBullets.SetNext();
		}
	}

	//END*********** PLAYER CANNON VS ENEMY BULLET ************
}

void CTheGame::CollisionPlayerVsObstacle()
{
	//START*********** PLAYER VS OBSTACLE ***************

	if(	!this->m_pPlayer->IsDestroyed() && 
		!this->m_pPlayer->IsUntouchable() )
	{
		bool bInverseMatrix = false;

		this->m_pObstaclesDepth1.SetFirst();
		while( this->m_pObstaclesDepth1.GetCurrent() )
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth1.GetCurrent();

			if( pObstacle->IsActive() && 
				(pObstacle->GetPosition().y <= (this->m_fScreenHeight + pObstacle->GetHeight() + 17.0f)))
			{
				// bounding box collision
				if( this->IsBoxCollision(	pObstacle->GetPosition(),
											pObstacle->GetWidth(),
											pObstacle->GetHeight(),
											this->m_pPlayer->GetPosition(),
											this->m_pPlayer->GetWidth(),
											this->m_pPlayer->GetHeight()) )
				{
					this->PlayerDestroyed();
					this->PlayerExplosion();
					return;

					/*
					// mesh to mesh collision
					if(this->IsMeshCollision(this->m_pPlayer, pObstacle, bInverseMatrix, false))
					{
						this->PlayerDestroyed();
						this->PlayerExplosion();
						return;
					}
					*/
				}
			}
			else
			{
				return;
			}

			this->m_pObstaclesDepth1.SetNext();
		}
	}

	//END************* PLAYER VS OBSTACLE ***************
}

void CTheGame::CollisionEnemyVsObstacle()
{
	//START*********** ENEMY VS OBSTACLE *************

	bool bInverseMatrix = false;
	float fCheckBorder = this->m_fScreenHeight + (this->m_pGameSettings->m_fAsteroidBig1Height / 2);

	this->m_pObstaclesDepth1.SetFirst();
	while( this->m_pObstaclesDepth1.GetCurrent() )
	{
		CObstacle* pObstacle = this->m_pObstaclesDepth1.GetCurrent();

		if(pObstacle->GetPosition().y > fCheckBorder)
		{
			return;
		}
		else if(pObstacle->IsActive())
		{
			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

				if(	pEnemy->IsActive() && 
					pEnemy->GetPosition().y <= (this->m_fScreenHeight + (pEnemy->GetHeight() / 2)))
				{
					// bounding box collision
					if( this->IsBoxCollision(	pObstacle->GetPosition(),
												pObstacle->GetWidth(),
												pObstacle->GetHeight(),
												pEnemy->GetPosition(),
												pEnemy->GetWidth(),
												pEnemy->GetHeight()) )
					{
						// mesh to mesh collision
						if(this->IsMeshCollision(pEnemy, pObstacle, bInverseMatrix, false))
						{
							pEnemy->ResetFleeMovement();
							pEnemy->SetActive(FALSE);

							// play sound effect
							this->PlaySoundExplosionEnemy(pEnemy);
						}
					}
				}

				this->m_pObstacleEnemies.SetNext();
			}
		}

		this->m_pObstaclesDepth1.SetNext();
	}

	//END************* ENEMY VS OBSTACLE *************
}

void CTheGame::CollisionEnemyVsEnemy()
{
	//START*********** ENEMY VS ENEMY *************

	bool bCollision;
	bool bInverseMatrix = false;

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		// active enemies
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				bCollision = false;

				// compare with other enemies
				this->m_pActiveEnemies.SetFirst();
				while( this->m_pActiveEnemies.GetCurrent() )
				{
					IEnemy* pOther = this->m_pActiveEnemies.GetCurrent();

					if( (pEnemy != pOther) && (pOther->IsActive()) )
					{
						// bounding box collision
						if( this->IsBoxCollision(	pEnemy->GetPosition(),
													pEnemy->GetWidth(),
													pEnemy->GetHeight(),
													pOther->GetPosition(),
													pOther->GetWidth(),
													pOther->GetHeight()) )
						{
							// mesh to mesh collision
							//if(this->IsMeshCollision(pEnemy, pOther, bInverseMatrix, false))
							//{
							// one time to first enemy
							if(!bCollision)
							{
								bCollision = true;

								this->EnemyCopyBullets(pEnemy);

								pEnemy->ResetFleeMovement();
								pEnemy->SetActive(FALSE);

								this->m_iMaxEnemies--;

								// play sound effect
								this->PlaySoundExplosionEnemy(pEnemy);
							}

							this->EnemyCopyBullets(pOther);

							pOther->ResetFleeMovement();
							pOther->SetActive(FALSE);

							this->m_iMaxEnemies--;

							// play sound effect
							this->PlaySoundExplosionEnemy(pOther);
							//}
						}
					}
					this->m_pActiveEnemies.SetNext();
				}
			}

			// find the right place in queue
			this->m_pActiveEnemies.SetFirst();
			while( pEnemy != this->m_pActiveEnemies.GetCurrent() )
			{
				this->m_pActiveEnemies.SetNext();
			}

			this->m_pActiveEnemies.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		// obstacle enemies
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				bCollision = false;

				// compare with other enemies
				this->m_pObstacleEnemies.SetFirst();
				while( this->m_pObstacleEnemies.GetCurrent() )
				{
					IEnemy* pOther = this->m_pObstacleEnemies.GetCurrent();

					if( (pEnemy != pOther) && (pOther->IsActive()) )
					{
						// bounding box collision
						if( this->IsBoxCollision(	pEnemy->GetPosition(),
													pEnemy->GetWidth(),
													pEnemy->GetHeight(),
													pOther->GetPosition(),
													pOther->GetWidth(),
													pOther->GetHeight()) )
						{
							// mesh to mesh collision
							//if(this->IsMeshCollision(pEnemy, pOther, bInverseMatrix, false))
							//{
							// one time to first enemy
							if(!bCollision)
							{
								bCollision = true;

								this->EnemyCopyBullets(pEnemy);

								pEnemy->ResetFleeMovement();
								pEnemy->SetActive(FALSE);

								this->m_iMaxEnemies--;

								// play sound effect
								this->PlaySoundExplosionEnemy(pEnemy);
							}

							this->EnemyCopyBullets(pOther);

							pOther->ResetFleeMovement();
							pOther->SetActive(FALSE);

							this->m_iMaxEnemies--;

							// play sound effect
							this->PlaySoundExplosionEnemy(pOther);
							//}
						}
					}
					this->m_pObstacleEnemies.SetNext();
				}
			}

			// find the right place in queue
			this->m_pObstacleEnemies.SetFirst();
			while( pEnemy != this->m_pObstacleEnemies.GetCurrent() )
			{
				this->m_pObstacleEnemies.SetNext();
			}

			this->m_pObstacleEnemies.SetNext();
		}
	}

	//END************* ENEMY VS ENEMY *************
}

void CTheGame::CollisionBulletVsBoss()
{
	//START********** BULLET VS BOSS **************

	if ((this->m_iGameState != GAME_STATE_BOSS_INTRO) && (this->m_iGameState != GAME_STATE_BOSS_ACTION) &&
		(this->m_iGameState != GAME_STATE_BOSS_CHAIN_EXPLOSION) && (this->m_iGameState != GAME_STATE_QUIT))
	{
		return;
	}

	D3DXVECTOR3* pPos = NULL;
	CWeapon* pBullet = NULL;
	IEnemy* pEnemy = NULL;

	D3DXVECTOR3 posCollision;

	bool bInverseMatrix;
	bool bBossCoreDestroyed = false;

	if (!this->m_pEnemyBoss1Frame->IsActive())
	{
		return;
	}

	// if already hit a boss part in this cycle, then 
	// we don't need to play the sound effect again

	bool bSoundHitBoss1Frame = false;
	bool bSoundHitBoss1LaserLeft = false;
	bool bSoundHitBoss1LaserRight = false;
	bool bSoundHitBoss1ScatterLeft = false;
	bool bSoundHitBoss1ScatterRight = false;

	this->m_pBullets.SetFirst();
	while (this->m_pBullets.GetCurrent())
	{
		switch (this->m_pBullets.GetCurrent()->GetOwner())
		{
		case CWeapon::eOWNER_PLAYER:

			// player minigun (front / dialog)
			if ((this->m_pBullets.GetCurrent()->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_FRONT) ||
				(this->m_pBullets.GetCurrent()->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL))
			{
				pEnemy = this->m_pActiveEnemies.GetCurrent();
				pBullet = this->m_pBullets.GetCurrent();
				pPos = pBullet->GetBulletPosition();

				for (int i = 1; i < 3; i++)
				{
					if (pBullet->BulletVisibility(i))
					{
						I3DObject* pBulletChild = pBullet->GetChildren()[i - 1];

						// BOSS 1: FRAME
						if (this->m_pEnemyBoss1Frame->IsActive())
						{
							// bounding box collision
							if (this->IsBoxCollision(this->m_pEnemyBoss1Frame->GetPosition(),
								this->m_pEnemyBoss1Frame->GetWidth(),
								this->m_pEnemyBoss1Frame->GetHeight(),
								pPos[i],
								pBullet->GetWidth(),
								pBullet->GetHeight()))
							{
								bInverseMatrix = false;

								float bulletDepth = pBulletChild->GetObjectDepth();
								float bossDepth = this->m_pEnemyBoss1Frame->GetObjectDepth();

								// mesh to mesh collision
								if (this->IsMeshCollision(pBulletChild, this->m_pEnemyBoss1Frame, bInverseMatrix, false))
								{
									pBullet->DisableBullet(i);

									// boss can be hurt
									if (this->m_iGameState == GAME_STATE_BOSS_ACTION)
									{
										if (this->m_pEnemyBoss1Frame->Destroyed(pBullet->GetDamage()))
										{
											this->m_bBossDestroyed = true;
										}
										else
										{
											// increase player score (enemy hit score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1Frame->GetScoreHit());
										}

										if (!bSoundHitBoss1Frame)
										{
											// play sound effect
											this->PlaySoundHitBoss(this->m_pEnemyBoss1Frame);
											bSoundHitBoss1Frame = true;
										}
									}
								}
							}
						}

						// BOSS 1: LEFT LASER
						if (this->m_pEnemyBoss1LaserLeft->IsActive())
						{
							// bounding box collision
							if (this->IsBoxCollision(this->m_pEnemyBoss1LaserLeft->GetPosition(),
								this->m_pEnemyBoss1LaserLeft->GetWidth(),
								this->m_pEnemyBoss1LaserLeft->GetHeight(),
								pPos[i],
								pBullet->GetWidth(),
								pBullet->GetHeight()))
							{
								bInverseMatrix = false;

								// mesh to mesh collision
								if (this->IsMeshCollision(pBulletChild, this->m_pEnemyBoss1LaserLeft, bInverseMatrix, false))
								{
									pBullet->DisableBullet(i);

									// boss can be hurt
									if (this->m_iGameState == GAME_STATE_BOSS_ACTION)
									{
#ifdef GAME_BOSS_PARTS_DAMAGE
										if (this->m_pEnemyBoss1LaserLeft->Destroyed(pBullet->GetDamage()))
										{
											// increase player score (enemy destroy score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserLeft->GetScoreDestroyed());
											// enemy is destroyed
											this->m_pEnemyBoss1LaserLeft->SetActive(FALSE);
											// enemy explosion
											this->BossPartExplosion(this->m_pEnemyBoss1LaserLeft);
											// play sound effect
											this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
											(FALSE, 0, this->m_iVolumeSoundEffect);
										}
										else
										{
											// increase player score (enemy hit score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserLeft->GetScoreHit());
										}
#endif
										if (!bSoundHitBoss1LaserLeft)
										{
											// play sound effect
											this->PlaySoundHitBoss(this->m_pEnemyBoss1LaserLeft);
											bSoundHitBoss1LaserLeft = true;
										}
									}
								}
							}
						}

						// BOSS 1: RIGHT LASER
						if (this->m_pEnemyBoss1LaserRight->IsActive())
						{
							// bounding box collision
							if (this->IsBoxCollision(this->m_pEnemyBoss1LaserRight->GetPosition(),
								this->m_pEnemyBoss1LaserRight->GetWidth(),
								this->m_pEnemyBoss1LaserRight->GetHeight(),
								pPos[i],
								pBullet->GetWidth(),
								pBullet->GetHeight()))
							{
								bInverseMatrix = false;

								// mesh to mesh collision
								if (this->IsMeshCollision(pBulletChild, this->m_pEnemyBoss1LaserRight, bInverseMatrix, false))
								{
									pBullet->DisableBullet(i);

									// boss can be hurt
									if (this->m_iGameState == GAME_STATE_BOSS_ACTION)
									{
#ifdef GAME_BOSS_PARTS_DAMAGE
										if (this->m_pEnemyBoss1LaserRight->Destroyed(pBullet->GetDamage()))
										{
											// increase player score (enemy destroy score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserRight->GetScoreDestroyed());
											// enemy is destroyed
											this->m_pEnemyBoss1LaserRight->SetActive(FALSE);
											// enemy explosion
											this->BossPartExplosion(this->m_pEnemyBoss1LaserRight);
											// play sound effect
											this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
											(FALSE, 0, this->m_iVolumeSoundEffect);
										}
										else
										{
											// increase player score (enemy hit score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1LaserRight->GetScoreHit());
										}
#endif
										if (!bSoundHitBoss1LaserRight)
										{
											// play sound effect
											this->PlaySoundHitBoss(this->m_pEnemyBoss1LaserRight);
											bSoundHitBoss1LaserRight = true;
										}
									}
								}
							}
						}

						// BOSS 1: LEFT SCATTER
						if (this->m_pEnemyBoss1ScatterLeft->IsActive())
						{
							// bounding box collision
							if (this->IsBoxCollision(this->m_pEnemyBoss1ScatterLeft->GetPosition(),
								this->m_pEnemyBoss1ScatterLeft->GetWidth(),
								this->m_pEnemyBoss1ScatterLeft->GetHeight(),
								pPos[i],
								pBullet->GetWidth(),
								pBullet->GetHeight()))
							{
								bInverseMatrix = true;

								// mesh to mesh collision
								if (this->IsMeshCollision(pBulletChild, this->m_pEnemyBoss1ScatterLeft, bInverseMatrix, false))
								{
									pBullet->DisableBullet(i);

									// boss can be hurt
									if (this->m_iGameState == GAME_STATE_BOSS_ACTION)
									{
#ifdef GAME_BOSS_PARTS_DAMAGE
										if (this->m_pEnemyBoss1ScatterLeft->Destroyed(pBullet->GetDamage()))
										{
											// increase player score (enemy destroy score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterLeft->GetScoreDestroyed());
											// enemy is destroyed
											this->m_pEnemyBoss1ScatterLeft->SetActive(FALSE);
											// enemy explosion
											this->BossPartExplosion(this->m_pEnemyBoss1ScatterLeft);
											// play sound effect
											this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
											(FALSE, 0, this->m_iVolumeSoundEffect);
										}
										else
										{
											// increase player score (enemy hit score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterLeft->GetScoreHit());
										}
#endif
										if (!bSoundHitBoss1ScatterLeft)
										{
											// play sound effect
											this->PlaySoundHitBoss(this->m_pEnemyBoss1ScatterLeft);
											bSoundHitBoss1ScatterLeft = true;
										}
									}
								}
							}
						}

						// BOSS 1: RIGHT SCATTER
						if (this->m_pEnemyBoss1ScatterRight->IsActive())
						{
							// bounding box collision
							if (this->IsBoxCollision(this->m_pEnemyBoss1ScatterRight->GetPosition(),
								this->m_pEnemyBoss1ScatterRight->GetWidth(),
								this->m_pEnemyBoss1ScatterRight->GetHeight(),
								pPos[i],
								pBullet->GetWidth(),
								pBullet->GetHeight()))
							{
								bInverseMatrix = true;

								// mesh to mesh collision
								if (this->IsMeshCollision(pBulletChild, this->m_pEnemyBoss1ScatterRight, bInverseMatrix, false))
								{
									pBullet->DisableBullet(i);

									// boss can be hurt
									if (this->m_iGameState == GAME_STATE_BOSS_ACTION)
									{
#ifdef GAME_BOSS_PARTS_DAMAGE
										if (this->m_pEnemyBoss1ScatterRight->Destroyed(pBullet->GetDamage()))
										{
											// increase player score (enemy destroy score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterRight->GetScoreDestroyed());
											// enemy is destroyed
											this->m_pEnemyBoss1ScatterRight->SetActive(FALSE);
											// enemy explosion
											this->BossPartExplosion(this->m_pEnemyBoss1ScatterRight);
											// play sound effect
											this->m_pTheApp->GetWave(SOUND_EXPLOSION_BOSS_CHAIN_1).Play
											(FALSE, 0, this->m_iVolumeSoundEffect);
										}
										else
										{
											// increase player score (enemy hit score)
											this->m_pPlayer->IncreaseScore(this->m_pEnemyBoss1ScatterRight->GetScoreHit());
										}
#endif
										if (!bSoundHitBoss1ScatterRight)
										{
											// play sound effect
											this->PlaySoundHitBoss(this->m_pEnemyBoss1ScatterRight);
											bSoundHitBoss1ScatterRight = true;
										}
									}
								}
							}
						}
					}
				}
			}

			break;
		}

		this->m_pBullets.SetNext();
	}

	//END************ BULLET VS BOSS **************
}

void CTheGame::CollisionBulletVsEnemy()
{
	//START********** BULLET VS ENEMY **************

	D3DXVECTOR3* pPos = NULL;
	CWeapon* pBullet = NULL;
	IEnemy* pEnemy = NULL;

	// general bullets

	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		pBullet = this->m_pBullets.GetCurrent();
		pPos = pBullet->GetBulletPosition();

		if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
		{
			// active enemies
			this->m_pActiveEnemies.SetFirst();
			while( this->m_pActiveEnemies.GetCurrent() )
			{
				pEnemy = this->m_pActiveEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					CheckCollisionBulletVsEnemy(pBullet, pEnemy, pPos);
				}
				this->m_pActiveEnemies.SetNext();
			}
		}
		else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
				(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
		{
			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				pEnemy = this->m_pObstacleEnemies.GetCurrent();

				if( pEnemy->IsActive() )
				{
					CheckCollisionBulletVsEnemy(pBullet, pEnemy, pPos);
				}
				this->m_pObstacleEnemies.SetNext();
			}
		}

		this->m_pBullets.SetNext();
	}

	//END************ BULLET VS ENEMY **************
}

void CTheGame::CollisionBulletVsPlayer()
{
	//START********** BULLET VS PLAYER **************

	if(	!this->m_pPlayer->IsDestroyed() && 
		!this->m_pPlayer->IsUntouchable())
	{
		D3DXVECTOR3* pPos = NULL;
		CWeapon* pBullet = NULL;

		// Boss scenario

		if(	((this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
			(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION)) || 
			((this->m_iGameState == GAME_STATE_QUIT) && 
				((this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))))
		{
			switch( this->m_pLevel->GetLevelNumber() )
			{
			case 1:
			case 2:
			case 3:

				if(this->m_pEnemyBoss1Frame->CollisionBulletVsPlayer(this->m_pPlayer))
				{
					this->PlaySoundHitPlayer();
				}
				if(this->m_pEnemyBoss1LaserLeft->CollisionBulletVsPlayer(this->m_pPlayer))
				{
					this->PlaySoundHitPlayer();
				}
				if(this->m_pEnemyBoss1LaserRight->CollisionBulletVsPlayer(this->m_pPlayer))
				{
					this->PlaySoundHitPlayer();
				}
				if(this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsPlayer(this->m_pPlayer))
				{
					this->PlaySoundHitPlayer();
				}
				if(this->m_pEnemyBoss1ScatterRight->CollisionBulletVsPlayer(this->m_pPlayer))
				{
					this->PlaySoundHitPlayer();
				}
				// boss 1 cannon
				if(this->m_pEnemyBoss1Cannon->GetAction() != CEnemyBoss1Cannon::eACTION_WAIT)
				{
					if(this->IsMeshCollision(this->m_pEnemyBoss1Cannon, this->m_pPlayer, false, false))
					{
						this->m_pPlayer->DecreaseHealth(this->m_pEnemyBoss1Cannon->GetDamage());
					}
				}

				break;
			}

			// player is destroyed
			if( !this->m_pPlayer->IsAlive() )
			{
				this->PlayerDestroyed();
				this->PlayerExplosion();
			}
		}

		// Level scenario

		else
		{
			if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
			{
				// active enemies
				this->m_pActiveEnemies.SetFirst();
				while( this->m_pActiveEnemies.GetCurrent() )
				{
					IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

					if( pEnemy->IsActive() )
					{
						if(pEnemy->CollisionBulletVsPlayer(this->m_pPlayer))
						{
							this->PlaySoundHitPlayer();
						}
					}
					this->m_pActiveEnemies.SetNext();
				}
			}
			else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
					(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
			{
				// obstacle enemies
				this->m_pObstacleEnemies.SetFirst();
				while( this->m_pObstacleEnemies.GetCurrent() )
				{
					IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

					if( pEnemy->IsActive() )
					{
						if(pEnemy->CollisionBulletVsPlayer(this->m_pPlayer))
						{
							this->PlaySoundHitPlayer();
						}
					}
					this->m_pObstacleEnemies.SetNext();
				}
			}

			// general bullet queue
			this->m_pBullets.SetFirst();
			while( this->m_pBullets.GetCurrent() )
			{
				pBullet = this->m_pBullets.GetCurrent();
				pPos = pBullet->GetBulletPosition();

				CheckCollisionBulletVsPlayer(pBullet, pPos);

				this->m_pBullets.SetNext();
			}

			// player is destroyed
			if( !this->m_pPlayer->IsAlive() )
			{
				this->PlayerDestroyed();
				this->PlayerExplosion();
			}
		}
	}

	//END************ BULLET VS PLAYER **************
}

void CTheGame::CollisionBulletVsObstacle()
{
	//START************ BULLET VS OBSTACLE ***************

	D3DXVECTOR3* pPos = NULL;
	CWeapon* pBullet = NULL;
	CObstacle* pObstacle = NULL;

	D3DXVECTOR3 posCollision;

	bool bInverseMatrix;

	this->m_pObstaclesDepth1.SetFirst();
	while( this->m_pObstaclesDepth1.GetCurrent() )
	{
		if( this->m_pObstaclesDepth1.GetCurrent()->IsActive() )
		{
			pObstacle = this->m_pObstaclesDepth1.GetCurrent();

			// obstacle enemies
			this->m_pObstacleEnemies.SetFirst();
			while( this->m_pObstacleEnemies.GetCurrent() )
			{
				if( this->m_pObstacleEnemies.GetCurrent()->IsActive() )
				{
					CQueue<CWeapon*>* pBullets = this->m_pObstacleEnemies.GetCurrent()->GetBullets();

					pBullets->SetFirst();
					while( pBullets->GetCurrent() )
					{
						bInverseMatrix = false;

						if( pBullets->GetCurrent()->IsActive() )
						{
							pBullet = pBullets->GetCurrent();
							pPos = pBullet->GetBulletPosition();

							// bounding box collision
							if( this->IsBoxCollision(	pObstacle->GetPosition(),
														pObstacle->GetWidth(),
														pObstacle->GetHeight(),
														pPos[0],
														pBullet->GetWidth(),
														pBullet->GetHeight()) )
							{
								pBullet->DisableBullet(0);

								/*
								// mesh to mesh collision
								if(this->IsMeshCollision(pBullet, pObstacle, bInverseMatrix, false))
								{
									pBullet->DisableBullet(0);
								}
								*/
							}
						}
						pBullets->SetNext();
					}
				}
				this->m_pObstacleEnemies.SetNext();
			}

			// general bullet queue
			this->m_pBullets.SetFirst();
			while( this->m_pBullets.GetCurrent() )
			{
				pBullet = this->m_pBullets.GetCurrent();
				pPos = pBullet->GetBulletPosition();

				switch( pBullet->GetOwner() )
				{
				case CWeapon::eOWNER_PLAYER:

					// player minigun (front / dialog)
					if(	(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_FRONT) || 
						(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL))
					{
						bInverseMatrix = false;

						for(int i = 1; i < 3; i++)
						{
							if( pBullet->BulletVisibility(i) )
							{
								// bounding box collision
								if( this->IsBoxCollision(	pObstacle->GetPosition(),
															pObstacle->GetWidth(),
															pObstacle->GetHeight(),
															pPos[i],
															pBullet->GetWidth(),
															pBullet->GetHeight()) )
								{
									pBullet->DisableBullet(i);

									/*
									I3DObject* pBulletChild = pBullet->GetChildren()[i-1];

									// mesh to mesh collision
									if(this->IsMeshCollision(pBulletChild, pObstacle, bInverseMatrix, false))
									{
										pBullet->DisableBullet(i);
									}
									*/
								}
							}
						}
					}

					break;

				case CWeapon::eOWNER_ENEMY:

					// drone or sniper bullet
					if( (pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_ENEMY_DRONE) || 
						(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_ENEMY_SNIPER))
					{
						bInverseMatrix = false;

						if( pBullet->BulletVisibility(0) )
						{
							// bounding box collision
							if( this->IsBoxCollision(	pObstacle->GetPosition(),
														pObstacle->GetWidth(),
														pObstacle->GetHeight(),
														pPos[0],
														pBullet->GetWidth(),
														pBullet->GetHeight()) )
							{
								pBullet->SetActive(FALSE);

								/*
								// mesh to mesh collision
								if(this->IsMeshCollision(pBullet, pObstacle, bInverseMatrix, false))
								{
									pBullet->SetActive(FALSE);
								}
								*/
							}
						}
					}

					break;
				}
				this->m_pBullets.SetNext();
			}
		}
		this->m_pObstaclesDepth1.SetNext();
	}

	//END************** BULLET VS OBSTACLE ***************
}

void CTheGame::CollisionBulletVsBorder()
{
	//START*********** BULLET VS BORDER *************

	// Boss bullets
	if( (this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
		(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
		(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
	{
		switch(this->m_pLevel->GetLevelNumber())
		{
		case 1:

			this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

			break;

		case 2:

			this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

			break;

		case 3:

			this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
			this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

			break;
		}
	}
	else
	{
		if(	(this->m_iGameState == GAME_STATE_END_FAILED) || 
			(this->m_iGameState == GAME_STATE_QUIT))
		{
			if(	(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
			{
				switch(this->m_pLevel->GetLevelNumber())
				{
				case 1:

					this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

					break;

				case 2:

					this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

					break;

				case 3:

					this->m_pEnemyBoss1Frame->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1LaserRight->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterLeft->CollisionBulletVsBorder();
					this->m_pEnemyBoss1ScatterRight->CollisionBulletVsBorder();

					break;
				}
			}
		}
	}

	CWeapon* pBullet;
	D3DXVECTOR3* pPos;

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		// active enemies
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->CollisionBulletVsBorder();
			}
			this->m_pActiveEnemies.SetNext();
		}
		// reinforcements
		this->m_pReinforcements.SetFirst();
		while( this->m_pReinforcements.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->CollisionBulletVsBorder();
			}
			this->m_pReinforcements.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		// obstacle enemies
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->CollisionBulletVsBorder();
			}
			this->m_pObstacleEnemies.SetNext();
		}
	}

	// general bullet queue
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		pBullet = this->m_pBullets.GetCurrent();
		pPos = pBullet->GetBulletPosition();

		switch( pBullet->GetOwner())
		{
		case CWeapon::eOWNER_PLAYER:

			// player minigun front / diagonal
			if( (pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_FRONT) || 
				(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL))
			{
				for(int i = 0; i < 3; i++)
				{
					// top border collision
					if( pPos[i].y > (this->m_fScreenHeight + 10.0f) )
					{
						this->m_pBullets.GetCurrent()->DisableBullet(i);
					}
				}
			}

			break;

		case CWeapon::eOWNER_ENEMY:

			// top border
			if(	(pPos[0].y > (this->m_fScreenHeight + 15.0f)) && 
				((pBullet->GetDirection() == CWeapon::eDIRECTION_UP) || 
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_LEFT) ||
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_UP_LEFT) || 
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_LEFT_LEFT) || 
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_RIGHT) ||
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_UP_RIGHT) || 
				(pBullet->GetDirection() == CWeapon::eDIRECTION_UP_RIGHT_RIGHT)))
			{
				pBullet->SetActive(FALSE);
			}
			// bottom border
			else if( pPos[0].y < (-this->m_fScreenHeight - 15.0f) )
			{
				pBullet->SetActive(FALSE);
			}
			
			// left border
			else if( pPos[0].x < (-this->m_fScreenWidth - 15.0f) )
			{
				pBullet->SetActive(FALSE);
			}
			// right border
			else if( pPos[0].x > (this->m_fScreenWidth + 15.0f) )
			{
				pBullet->SetActive(FALSE);
			}

			break;
		}

		this->m_pBullets.SetNext();
	}

	//END************* BULLET VS BORDER *************
}

void CTheGame::CheckCollisionBulletVsEnemy(
	CWeapon* pBullet, IEnemy* pEnemy, D3DXVECTOR3* pBPos)
{
	int bulletIndex = 0;
	int bulletCount = 1;

	if(pBullet->GetOwner() == CWeapon::eOWNER_PLAYER)
	{
		// player minigun (front / dialog)
		if(	(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_FRONT) || 
			(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL))
		{
			bulletIndex = 1;
			bulletCount = 3;
		}
	}

	I3DObject* pShipObject = NULL;

	for(int i = bulletIndex; i < bulletCount; i++)
	{
		if( pBullet->BulletVisibility(i) )
		{
			// bounding box collision
			if( this->IsBoxCollision(	pEnemy->GetPosition(),
										pEnemy->GetWidth(),
										pEnemy->GetHeight(),
										pBPos[i],
										pBullet->GetWidth(),
										pBullet->GetHeight()) )
			{
				bool bMeshCollision = false;

				// player minigun (front / dialog)
				if(	(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_FRONT) || 
					(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_PLAYER_DIAGONAL))
				{
					/*
					if(this->IsMeshCollision(
						pBullet->GetChildren()[i-1], pEnemy, true, false))
					{
						bMeshCollision = true;
					}
					*/

					bMeshCollision = true;
				}
				// enemy single bullet
				else if((pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_ENEMY_DRONE) || 
						(pBullet->GetBulletType() == CWeapon::eBULLET_TYPE_ENEMY_SNIPER))
				{
					pShipObject = pBullet->GetShipObject();

					if(	(pShipObject == NULL) || 
						((pShipObject != NULL) && (pBullet->GetShipObject() != pEnemy)))
					{
						if(this->IsMeshCollision(
							pBullet, pEnemy, true, false))
						{
							bMeshCollision = true;
						}
					}
				}

				// mesh to mesh collision
				if(bMeshCollision)
				{
					/* particles */
					/*
					// get collision point
					D3DXVECTOR3 vCollisionPoint = pEnemy->GetPosition();
					vCollisionPoint.x += vPoint.x;
					vCollisionPoint.y += vPoint.y;
					vCollisionPoint.z += vPoint.z;

					this->GenerateParticlesBullet(pBullet, vCollisionPoint);
					*/

					pBullet->DisableBullet(i);

					// instantly kills normal enemy
					if( pBullet->GetDamageType() == CWeapon::TOTAL_DESTRUCTION )
					{
						if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH)
						{
							// launch enemy killed
							this->m_iEnemiesLaunch++;
						}
						else if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE)
						{
							// strike enemy killed
							this->m_iEnemiesStrike++;
						}

						this->EnemyCopyBullets(pEnemy);

						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);

						this->m_iMaxEnemies--;

						// increase player score (enemy destroyed score)
						if(pBullet->GetOwner() == CWeapon::eOWNER_PLAYER)
							this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());

						// play sound effect
						this->PlaySoundExplosionEnemy(pEnemy);
					}
					else
					{
						// enemy is destroyed
						if( pEnemy->Destroyed(this->m_pBullets.GetCurrent()->GetDamage()) )
						{
							if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH)
							{
								// launch enemy killed
								this->m_iEnemiesLaunch++;
							}
							else if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE)
							{
								// strike enemy killed
								this->m_iEnemiesStrike++;
							}

							this->EnemyCopyBullets(pEnemy);

							pEnemy->ResetFleeMovement();
							pEnemy->SetActive(FALSE);

							this->m_iMaxEnemies--;

							// increase player score (enemy destroyed score)
							if(pBullet->GetOwner() == CWeapon::eOWNER_PLAYER)
								this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());

							// play sound effect
							this->PlaySoundExplosionEnemy(pEnemy);
						}
						else
						{
							if(	(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE) && 
								(pEnemy->GetMoveDamageLevel() == IEnemy::eMOVE_DAMAGE_LEVEL_1))
							{
								if( pEnemy->GetAfterburn() )
								{
									pEnemy->SetAfterburn(false);
								}
							}
							// increase player score (enemy hit score)
							if(pBullet->GetOwner() == CWeapon::eOWNER_PLAYER)
								this->m_pPlayer->IncreaseScore(pEnemy->GetScoreHit());
							
							// play sound effect
							this->PlaySoundHitEnemy(pEnemy);
						}
					}
				}
			}
		}
	}
}

void CTheGame::CheckCollisionBulletVsPlayer(
	CWeapon* pBullet, D3DXVECTOR3* pBPos)
{
	if( pBullet->GetOwner() == CWeapon::eOWNER_ENEMY )
	{
		if( pBullet->BulletVisibility(0) )
		{
			// bounding box collision
			if( this->IsBoxCollision(	this->m_pPlayer->GetPosition(),
										this->m_pPlayer->GetWidth() / 2.0f,
										this->m_pPlayer->GetHeight() / 2.0f,
										pBPos[0],
										pBullet->GetWidth(),
										pBullet->GetHeight()) )
			{
				// mesh to mesh collision
				if(this->IsMeshCollision(pBullet, this->m_pPlayer, true, false))
				{
					pBullet->SetActive(FALSE);

					// instantly kills player
					if( pBullet->GetDamageType() == CWeapon::TOTAL_DESTRUCTION )
					{
						this->PlayerDestroyed();
						// player explosion
						this->PlayerExplosion();
					}
					else
					{
						this->m_pPlayer->DecreaseHealth(pBullet->GetDamage());

						if( !this->m_pPlayer->IsAlive() )
						{
							this->PlayerDestroyed();
							this->PlayerExplosion();
						}
						else
						{
							// play sound effect
							this->PlaySoundHitPlayer();
						}
					}
				}
			}
		}
	}
}


void CTheGame::ClearEnemies()
{
	//START********* CLEAR ENEMIES ************

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		// active enemies
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			if( !pEnemy->IsActive() )
			{
				float bottomBorder = this->m_fScreenHeight + (pEnemy->GetHeight() / 2);
				bottomBorder = -1.0f * bottomBorder;

				// enemy explosion, is not active and has not left the screen
				if(pEnemy->GetPosition().y > bottomBorder)
				{
					this->EnemyExplosion(pEnemy);
				}

				this->m_pActiveEnemies.PopCurrent();
			}
			else
			{
				this->m_pActiveEnemies.SetNext();
			}
		}

		// reinforcements
		this->m_pReinforcements.SetFirst();
		while( this->m_pReinforcements.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

			if( !pEnemy->IsActive() )
			{
				// put back to reinforcement reserves
				pEnemy->SetReinforcementAction(IEnemy::eREINFORCEMENT_ACTION_WAIT);
			}

			this->m_pReinforcements.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		// obstacle enemies
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			if( !pEnemy->IsActive() )
			{
				float bottomBorder = this->m_fScreenHeight + (pEnemy->GetHeight() / 2);
				bottomBorder = -1.0f * bottomBorder;

				// enemy explosion, is not active and has not left the screen
				if(pEnemy->GetPosition().y > bottomBorder)
				{
					this->EnemyExplosion(pEnemy);
				}

				this->m_pObstacleEnemies.PopCurrent();
			}
			else
			{
				this->m_pObstacleEnemies.SetNext();
			}
		}
	}

	//END*********** CLEAR ENEMIES ************
}

void CTheGame::ClearObstacles()
{
	//START******** CLEAR OBSTACLES ***********

	if (m_iGameState != GAME_STATE_PLAY_OBSTACLES &&
		m_iGameState != GAME_STATE_WAIT_OBSTACLES)
	{
		return;
	}

	/* depth 1 obstacles */

	this->m_pObstaclesDepth1.SetFirst();
	while( this->m_pObstaclesDepth1.GetCurrent() )
	{
		if( !this->m_pObstaclesDepth1.GetCurrent()->IsActive() )
		{
			this->m_pObstaclesDepth1.PopCurrent();
		}
		else
		{
			this->m_pObstaclesDepth1.SetNext();
		}
	}

	/* depth 2 obstacles */

	this->m_pObstaclesDepth2.SetFirst();
	while( this->m_pObstaclesDepth2.GetCurrent() )
	{
		if( !this->m_pObstaclesDepth2.GetCurrent()->IsActive() )
		{
			this->m_pObstaclesDepth2.PopCurrent();
		}
		else
		{
			this->m_pObstaclesDepth2.SetNext();
		}
	}

	/* depth 3 obstacles */

	this->m_pObstaclesDepth3.SetFirst();
	while( this->m_pObstaclesDepth3.GetCurrent() )
	{
		if( !this->m_pObstaclesDepth3.GetCurrent()->IsActive() )
		{
			this->m_pObstaclesDepth3.PopCurrent();
		}
		else
		{
			this->m_pObstaclesDepth3.SetNext();
		}
	}

	/* depth 4 obstacles */

	this->m_pObstaclesDepth4.SetFirst();
	while( this->m_pObstaclesDepth4.GetCurrent() )
	{
		if( !this->m_pObstaclesDepth4.GetCurrent()->IsActive() )
		{
			this->m_pObstaclesDepth4.PopCurrent();
		}
		else
		{
			this->m_pObstaclesDepth4.SetNext();
		}
	}

	/* depth 5 obstacles */

	this->m_pObstaclesDepth5.SetFirst();
	while( this->m_pObstaclesDepth5.GetCurrent() )
	{
		if( !this->m_pObstaclesDepth5.GetCurrent()->IsActive() )
		{
			this->m_pObstaclesDepth5.PopCurrent();
		}
		else
		{
			this->m_pObstaclesDepth5.SetNext();
		}
	}

	//END********** CLEAR OBSTACLES ***********
}

void CTheGame::ClearBullets(bool bForced)
{
	//START********* CLEAR BULLETS ************

	// boss bullets

	if( (this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
		(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
		(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
	{
		switch( this->m_pLevel->GetLevelNumber())
		{
		case 1:

			this->m_pEnemyBoss1Frame->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

			break;

		case 2:

			this->m_pEnemyBoss1Frame->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

			break;

		case 3:

			this->m_pEnemyBoss1Frame->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
			this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

			break;
		}
	}
	else
	{
		if((this->m_iGameState == GAME_STATE_END_FAILED) || 
			(this->m_iGameState == GAME_STATE_QUIT))
		{
			if(	(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
			{
				switch( this->m_pLevel->GetLevelNumber())
				{
				case 1:

					this->m_pEnemyBoss1Frame->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

					break;

				case 2:

					this->m_pEnemyBoss1Frame->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

					break;

				case 3:

					this->m_pEnemyBoss1Frame->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1LaserRight->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterLeft->ClearBullets(bForced);
					this->m_pEnemyBoss1ScatterRight->ClearBullets(bForced);

					break;
				}
			}
		}
	}

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		// active enemies
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->ClearBullets(bForced);
			}
			this->m_pActiveEnemies.SetNext();
		}
		// reinforcements
		this->m_pReinforcements.SetFirst();
		while( this->m_pReinforcements.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->ClearBullets(bForced);
			}
			this->m_pReinforcements.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		// obstacle enemies
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			if( pEnemy->IsActive() )
			{
				pEnemy->ClearBullets(bForced);
			}
			this->m_pObstacleEnemies.SetNext();
		}
	}

	// general bullet queue
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		CWeapon* pBullet = this->m_pBullets.GetCurrent();

		if(bForced)
		{
			this->m_pBullets.PopCurrent();
		}
		else
		{
			if( !pBullet->IsActive() )
			{
				this->m_pBullets.PopCurrent();
			}
			else
			{
				this->m_pBullets.SetNext();
			}
		}
	}

	//END*********** CLEAR BULLETS ************
}

void CTheGame::ClearParticles()
{
	//START********* CLEAR PARTICLES ************
	/*
	this->m_pParticles.SetFirst();
	while( this->m_pParticles.GetCurrent() )
	{
		if( !this->m_pParticles.GetCurrent()->GetActive() )
		{
			this->m_pParticles.PopCurrent();
		}
		else
		{
			this->m_pParticles.SetNext();
		}
	}
	*/
	//END*********** CLEAR PARTICLES ************
}

void CTheGame::UpdatePlayer(float fFrametime)
{
	//START************ UPDATE PLAYER ******************

	if(this->m_iGameState != GAME_STATE_BLAST_ACTIVE)
	{
		if(this->m_bPlayerEnter)
		{
			// player enter movement
			this->PlayerMoveEnter(fFrametime);
		}
		else if(this->m_bPlayerMoveAway)
		{
			// player away movement
			this->PlayerMoveAway(fFrametime);
		}

		// ignore player movement inputs
		if(	(this->m_iGameState == GAME_STATE_LEVEL_INTRO) || 
			(this->m_iGameState == GAME_STATE_LEVEL_OUTRO) || 
			this->m_bPlayerEnter || this->m_bPlayerMoveAway)
		{
			if(this->m_pPlayerController->GetExecuteInputs())
			{
				// don't execute player movement inputs
				this->m_pPlayerController->SetExecuteInputs(false);
			}
		}
		// notice player movement inputs
		else
		{
			if(!this->m_pPlayerController->GetExecuteInputs())
			{
				// execute player movement inputs
				this->m_pPlayerController->SetExecuteInputs(true);
			}
		}

		this->m_pPlayerController->UpdatePlayer(fFrametime, this->m_pPlayer);

		if(this->m_pPlayer->IsVelocityControl())
		{
			if(this->m_pPlayer->IsBoostIncreaseSound())
			{
				this->m_pPlayer->DisableBoostIncreaseSound();
				this->PlaySoundPlayerAfterburn();
			}
		}
	}

	if(this->m_iGameState == GAME_STATE_BLAST_ACTIVE)
	{
		this->m_pPlayer->Update(false, fFrametime);
	}
	else
	{
		this->m_pPlayer->Update(true, fFrametime);
	}

	//END************** UPDATE PLAYER ******************
}

void CTheGame::UpdateBoss(float fFrametime)
{
	//START************ UPDATE BOSS ******************

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
	case 2:
	case 3:

		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			if(	(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
			{
				this->m_pEnemyBoss1Frame->UpdateShip(	this->m_pEnemyBoss1LaserLeft,
														this->m_pEnemyBoss1LaserRight,
														false,
														fFrametime);

				this->m_pEnemyBoss1Core->UpdateShip(this->m_pEnemyBoss1Frame->GetHealth(),
													fFrametime);

				if( this->m_pEnemyBoss1LaserLeft->IsActive() )
				{
					this->m_pEnemyBoss1LaserLeft->UpdateShip(	this->m_pEnemyBoss1Frame,
																false, true,
																fFrametime);

					if( this->m_pEnemyBoss1LaserRight->IsActive() )
					{
						if(this->m_pEnemyBoss1LaserRight->GetAction() == 
							CEnemyBoss1Laser::eACTION_TURN)
						{
							this->m_pEnemyBoss1LaserRight->SetRotateLaser( 
								this->m_pEnemyBoss1LaserLeft->GetRotateLaser() );
						}

						this->m_pEnemyBoss1LaserRight->SetShootMulti(
							this->m_pEnemyBoss1LaserLeft->GetShootMulti());
					}
				}

				if( this->m_pEnemyBoss1LaserRight->IsActive() )
				{
					if (this->m_pEnemyBoss1LaserLeft->IsActive())
					{
						this->m_pEnemyBoss1LaserRight->UpdateShip(	this->m_pEnemyBoss1Frame,
																	false,
																	true,
																	fFrametime);
					}
					else
					{
						this->m_pEnemyBoss1LaserRight->UpdateShip(	this->m_pEnemyBoss1Frame,
																	false,
																	false,
																	fFrametime);
					}
				}

				if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
				{
					this->m_pEnemyBoss1ScatterLeft->UpdateShip(	this->m_pEnemyBoss1Frame,
																false,
																this->m_fScreenHeight,
																fFrametime);
				}
				if( this->m_pEnemyBoss1ScatterRight->IsActive() )
				{
					this->m_pEnemyBoss1ScatterRight->UpdateShip(this->m_pEnemyBoss1Frame,
																false,
																this->m_fScreenHeight,
																fFrametime);
				}
			}
			else
			{
				this->m_pEnemyBoss1Frame->UpdateShip(	this->m_pEnemyBoss1LaserLeft,
														this->m_pEnemyBoss1LaserRight,
														true,
														fFrametime);

				this->m_pEnemyBoss1Core->UpdateShip(this->m_pEnemyBoss1Frame->GetHealth(),
													fFrametime);

				if( this->m_pEnemyBoss1LaserLeft->IsActive() )
				{
					this->m_pEnemyBoss1LaserLeft->UpdateShip(	this->m_pEnemyBoss1Frame,
																true, true,
																fFrametime);

					if( this->m_pEnemyBoss1LaserRight->IsActive() )
					{
						if(this->m_pEnemyBoss1LaserRight->GetAction() == 
							CEnemyBoss1Laser::eACTION_TURN)
						{
							this->m_pEnemyBoss1LaserRight->SetRotateLaser( 
								this->m_pEnemyBoss1LaserLeft->GetRotateLaser() );
						}

						this->m_pEnemyBoss1LaserRight->SetShootMulti(
							this->m_pEnemyBoss1LaserLeft->GetShootMulti());
					}
				}

				if( this->m_pEnemyBoss1LaserRight->IsActive() )
				{
					if (this->m_pEnemyBoss1LaserLeft->IsActive())
					{
						this->m_pEnemyBoss1LaserRight->UpdateShip(	this->m_pEnemyBoss1Frame,
																	true,
																	true,
																	fFrametime);
					}
					else
					{
						this->m_pEnemyBoss1LaserRight->UpdateShip(	this->m_pEnemyBoss1Frame,
																	true,
																	false,
																	fFrametime);
					}
				}

				if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
				{
					this->m_pEnemyBoss1ScatterLeft->UpdateShip(	this->m_pEnemyBoss1Frame,
																true,
																this->m_fScreenHeight,
																fFrametime);
				}
				if( this->m_pEnemyBoss1ScatterRight->IsActive() )
				{
					this->m_pEnemyBoss1ScatterRight->UpdateShip(this->m_pEnemyBoss1Frame,
																true,
																this->m_fScreenHeight,
																fFrametime);
				}
			}
		}

		if(	(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION) || 
			(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
			(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
		{
			this->m_pEnemyBoss1Cannon->UpdateShip(	this->m_pEnemyBoss1Frame,
													false, fFrametime);
		}
		else
		{
			this->m_pEnemyBoss1Cannon->UpdateShip(	this->m_pEnemyBoss1Frame,
													true, fFrametime);
		}

		break;
	}

	//END************** UPDATE BOSS ******************
}

void CTheGame::UpdateBossShake(bool bBlast, float fFrametime)
{
	//START********* UPDATE BOSS SHAKE *********

	D3DXVECTOR3 posBefore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posAfter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float fChangeX = 0.0f;
	float fChangeY = 0.0f;

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:

		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			posBefore = this->m_pEnemyBoss1Frame->GetPosition();

			if(bBlast)
			{
				this->m_pEnemyBoss1Frame->UpdateBossBlastShake(fFrametime);
				this->m_pEnemyBoss1Frame->UpdateShake(fFrametime);
			}
			else
			{
				this->m_pEnemyBoss1Frame->UpdateBossCannonShake(fFrametime);
			}

			posAfter = this->m_pEnemyBoss1Frame->GetPosition();

			fChangeX = posAfter.x - posBefore.x;
			fChangeY = posAfter.y - posBefore.y;

			if(this->m_pEnemyBoss1ScatterLeft->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterLeft->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterLeft->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterLeft->UpdateShake(fFrametime);
				}
			}
			if(this->m_pEnemyBoss1ScatterRight->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterRight->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterRight->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterRight->UpdateShake(fFrametime);
				}
			}
		}

		break;

	case 2:

		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			posBefore = this->m_pEnemyBoss1Frame->GetPosition();

			if(bBlast)
			{
				this->m_pEnemyBoss1Frame->UpdateBossBlastShake(fFrametime);
				this->m_pEnemyBoss1Frame->UpdateShake(fFrametime);
			}
			else
			{
				this->m_pEnemyBoss1Frame->UpdateBossCannonShake(fFrametime);
			}

			posAfter = this->m_pEnemyBoss1Frame->GetPosition();

			fChangeX = posAfter.x - posBefore.x;
			fChangeY = posAfter.y - posBefore.y;

			if(this->m_pEnemyBoss1ScatterLeft->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterLeft->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterLeft->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterLeft->UpdateShake(fFrametime);
				}
			}
			if(this->m_pEnemyBoss1ScatterRight->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterRight->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterRight->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterRight->UpdateShake(fFrametime);
				}
			}
		}

		break;

	case 3:

		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			posBefore = this->m_pEnemyBoss1Frame->GetPosition();

			if(bBlast)
			{
				this->m_pEnemyBoss1Frame->UpdateBossBlastShake(fFrametime);
				this->m_pEnemyBoss1Frame->UpdateShake(fFrametime);
			}
			else
			{
				this->m_pEnemyBoss1Frame->UpdateBossCannonShake(fFrametime);
			}

			posAfter = this->m_pEnemyBoss1Frame->GetPosition();

			fChangeX = posAfter.x - posBefore.x;
			fChangeY = posAfter.y - posBefore.y;

			if(this->m_pEnemyBoss1ScatterLeft->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterLeft->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterLeft->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterLeft->UpdateShake(fFrametime);
				}
			}
			if(this->m_pEnemyBoss1ScatterRight->IsActive())
			{
				posObject = this->m_pEnemyBoss1ScatterRight->GetPosition();
				posObject.x += fChangeX;
				posObject.y += fChangeY;
				this->m_pEnemyBoss1ScatterRight->SetPosition(posObject);

				if(bBlast)
				{
					this->m_pEnemyBoss1ScatterRight->UpdateShake(fFrametime);
				}
			}
		}

		break;
	}

	//END*********** UPDATE BOSS SHAKE *********
}

void CTheGame::UpdateEnemies()
{
	//START********* UPDATE ENEMIES *********

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			if( this->m_pActiveEnemies.GetCurrent()->IsActive() )
			{
				IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

				// timed explosion
				if( pEnemy->GetTimedExplosion() )
				{
					if( pEnemy->GetHealth() == 0 )
					{
						this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());
						
						// launch enemy killed
						if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH )
						{
							this->m_iEnemiesLaunch++;
						}
						// strike enemy killed
						else if( pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE )
						{
							this->m_iEnemiesStrike++;
						}
						
						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);

						this->m_iMaxEnemies--;

						// play sound effect
						this->PlaySoundExplosionEnemy(pEnemy);
					}
				}
				// launch enemy collisions
				else
				{
					if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH)
					{
						if(!pEnemy->IsEnter())
						{
							pEnemy->MoveAvoidLaunch(&this->m_pActiveEnemies);

							// find the right place in queue
							this->m_pActiveEnemies.SetFirst();
							while(pEnemy != this->m_pActiveEnemies.GetCurrent())
							{
								this->m_pActiveEnemies.SetNext();
							}
						}
					}
				}
			}
			this->m_pActiveEnemies.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES)|| 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			if( this->m_pObstacleEnemies.GetCurrent()->IsActive() )
			{
				IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

				// timed explosion
				if( pEnemy->GetTimedExplosion() )
				{
					if( pEnemy->GetHealth() == 0 )
					{
						this->m_pPlayer->IncreaseScore(pEnemy->GetScoreDestroyed());
						
						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);

						// play sound effect
						this->PlaySoundExplosionEnemy(pEnemy);
					}
				}
				// obstacle enemy collisions
				else
				{
					int fCheckBorder = this->m_fScreenHeight + (pEnemy->GetHeight() / 2);

					if(pEnemy->GetPosition().y <= fCheckBorder)
					{
						pEnemy->MoveAvoidObstacle(&this->m_pObstacleEnemies, &this->m_pObstaclesDepth1);

						// find the right place in queue
						this->m_pObstacleEnemies.SetFirst();
						while(pEnemy != this->m_pObstacleEnemies.GetCurrent())
						{
							this->m_pObstacleEnemies.SetNext();
						}
					}
				}
			}
			this->m_pObstacleEnemies.SetNext();
		}
	}

	//END*********** UPDATE ENEMIES *********
}

void CTheGame::UpdateEnemiesShake(bool bBlast, float fFrametime)
{
	//START********* UPDATE ENEMIES SHAKE *********

	// active enemies
	this->m_pActiveEnemies.SetFirst();
	while( this->m_pActiveEnemies.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

		if( pEnemy->IsActive() )
		{
			if(bBlast)
			{
				pEnemy->UpdateEnemyBlastShake(fFrametime);
				pEnemy->UpdateShake(fFrametime);
			}
			else
			{
				pEnemy->UpdateEnemyCannonShake(fFrametime);
			}
		}
		this->m_pActiveEnemies.SetNext();
	}

	//END*********** UPDATE ENEMIES SHAKE *********
}

void CTheGame::UpdateEnemiesShake(IEnemy* pEnemy, bool bBlast, float fFrametime)
{
	//START********* UPDATE ENEMIES SHAKE *********

	if(bBlast)
	{
		pEnemy->UpdateEnemyBlastShake(fFrametime);
		pEnemy->UpdateShake(fFrametime);
	}
	else
	{
		pEnemy->UpdateEnemyCannonShake(fFrametime);
	}

	//END*********** UPDATE ENEMIES SHAKE *********
}

void CTheGame::UpdateReinforcements(float fFrametime)
{
	//START******* UPDATE FLEET ENEMIES *******

	/* ENEMY FLEET SENDING */

	float fReinforcementSendCounter = 0.0f;
	float fReinforcementSendTime = 0.0f;

	if(this->m_bEnemyReinforcementSending)
	{
		// for each depth (2-5)
		for(int depth = 2; depth <= 5; depth++)
		{
			switch(depth)
			{
			case 2:
				fReinforcementSendCounter = this->m_fEnemyReinforcementCounterDepth2;
				fReinforcementSendTime = this->m_fEnemyReinforcementRandTimeDepth2;
				break;
			case 3:
				fReinforcementSendCounter = this->m_fEnemyReinforcementCounterDepth3;
				fReinforcementSendTime = this->m_fEnemyReinforcementRandTimeDepth3;
				break;
			case 4:
				fReinforcementSendCounter = this->m_fEnemyReinforcementCounterDepth4;
				fReinforcementSendTime = this->m_fEnemyReinforcementRandTimeDepth4;
				break;
			case 5:
				fReinforcementSendCounter = this->m_fEnemyReinforcementCounterDepth5;
				fReinforcementSendTime = this->m_fEnemyReinforcementRandTimeDepth5;
				break;
			}

			// counter reached the send time
			if (fReinforcementSendCounter >= fReinforcementSendTime)
			{
				bool isReserve = false;

				// are there any fleet enemies waiting
				this->m_pReinforcements.SetFirst();
				while(this->m_pReinforcements.GetCurrent())
				{
					if(!isReserve)
					{
						IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

						if(pEnemy->GetReinforcementAction() == IEnemy::eREINFORCEMENT_ACTION_WAIT)
						{
							isReserve = true;
						}
					}
					this->m_pReinforcements.SetNext();
				}

				if(isReserve)
				{
					switch(depth)
					{
					case 2:
						this->m_fEnemyReinforcementCounterDepth2 = 0.0f;
						break;
					case 3:
						this->m_fEnemyReinforcementCounterDepth3 = 0.0f;
						break;
					case 4:
						this->m_fEnemyReinforcementCounterDepth4 = 0.0f;
						break;
					case 5:
						this->m_fEnemyReinforcementCounterDepth5 = 0.0f;
						break;
					}

					int iSelectionIndex = this->m_pTheApp->RandInt(0, this->m_iReinforcementsMax);

					// randomly pick one to be sent from fleet
					for(int j = 0; j < iSelectionIndex; j++)
					{
						this->m_pReinforcements.SetNext();

						if(!this->m_pReinforcements.GetCurrent())
						{
							this->m_pReinforcements.SetFirst();
						}
					}
					if(!this->m_pReinforcements.GetCurrent())
					{
						this->m_pReinforcements.SetFirst();
					}

					bool bFound = false;

					while(!bFound)
					{
						if(this->m_pReinforcements.GetCurrent()->GetReinforcementAction() == 
							IEnemy::eREINFORCEMENT_ACTION_WAIT)
						{
							bFound = true;
						}
						else
						{
							this->m_pReinforcements.SetNext();
							if(!this->m_pReinforcements.GetCurrent())
							{
								this->m_pReinforcements.SetFirst();
							}
						}
					}

					IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();
				
					if(pEnemy)
					{
						int depthIndex = depth - 1;
						IEnemy::eTYPE enemyType = pEnemy->GetType();
						
						pEnemy->SetDepth(depth);

						// choose correct mesh data
						LPD3DXMESH mesh = m_vTemplateEnemyDroneLaunch[depthIndex]->GetMesh();
						std::vector<C3DObject::MESHDATA>& meshData = m_vTemplateEnemyDroneLaunch[depthIndex]->GetMeshDataArray();

						if (enemyType == IEnemy::eTYPE_SNIPER)
						{
							mesh = this->m_vTemplateEnemySniperLaunch[depthIndex]->GetMesh();
							meshData = this->m_vTemplateEnemySniperLaunch[depthIndex]->GetMeshDataArray();
						}
						else if (enemyType == IEnemy::eTYPE_ROLLER)
						{
							mesh = this->m_vTemplateEnemyRollerLaunch[depthIndex]->GetMesh();
							meshData = this->m_vTemplateEnemyRollerLaunch[depthIndex]->GetMeshDataArray();
						}
						else if (enemyType == IEnemy::eTYPE_GUARD)
						{
							//mesh = this->m_vTemplateEnemyGuardLaunch[depthIndex]->GetMesh();
							//meshData = this->m_vTemplateEnemyGuardLaunch[depthIndex]->GetMeshDataArray();
						}

						// set enemy mesh

						pEnemy->C3DObject::Create(mesh);
						pEnemy->ClearMeshData();

						for (DWORD j = 0; j < meshData.size(); j++)
						{
							pEnemy->AddMeshData(meshData[j]);
						}

						D3DXVECTOR3 posThis = pEnemy->GetPosition();

						// starting y-coordinate

						posThis.y = this->m_fScreenHeight + 40.0f;

						bool bLoop = true;
						int iCheckTimes = 0;

						// starting x-coordinate (check collisions)

						while(bLoop)
						{
							// tries 3 times before stopping
							if(iCheckTimes == 3)
							{
								bLoop = false;
							}
							else
							{
								bool bCollision = false;

								posThis.x = this->m_pTheApp->RandFloat( -this->m_fScreenWidth + 5.0f, this->m_fScreenWidth - 5.0f);
								pEnemy->SetPosition(posThis);

								// check collisions with other sent 
								// fleet ships that have the same depth
								this->m_pReinforcements.SetFirst();
								while( this->m_pReinforcements.GetCurrent() )
								{
									if(!bCollision)
									{
										IEnemy* pOther = this->m_pReinforcements.GetCurrent();

										// different ships
										if(pEnemy != pOther)
										{
											if(pOther->GetReinforcementAction() == 
												IEnemy::eREINFORCEMENT_ACTION_SENT)
											{
												// ships have the same depth value
												if(	pEnemy->GetDepth() == pOther->GetDepth())
												{
													if( !this->ReinforcementLineOfFire(pEnemy, pOther, true) )
													{
														bCollision = true;
													}
												}
											}
										}
									}
									this->m_pReinforcements.SetNext();
								}
								if(bCollision)
								{
									iCheckTimes++;
								}
								else
								{
									bLoop = false;

									pEnemy->SetActive(TRUE);
									pEnemy->InitReinforcementSend();

									switch(depth)
									{
									case 2:
										this->m_fEnemyReinforcementRandTimeDepth2 = this->m_pLevel->GetRandReinforcementSendTime();
										break;
									case 3:
										this->m_fEnemyReinforcementRandTimeDepth3 = this->m_pLevel->GetRandReinforcementSendTime();
										break;
									case 4:
										this->m_fEnemyReinforcementRandTimeDepth4 = this->m_pLevel->GetRandReinforcementSendTime();
										break;
									case 5:
										this->m_fEnemyReinforcementRandTimeDepth5 = this->m_pLevel->GetRandReinforcementSendTime();
										break;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				switch(depth)
				{
				case 2:
					this->m_fEnemyReinforcementCounterDepth2 += fFrametime;
					break;
				case 3:
					this->m_fEnemyReinforcementCounterDepth3 += fFrametime;
					break;
				case 4:
					this->m_fEnemyReinforcementCounterDepth4 += fFrametime;
					break;
				case 5:
					this->m_fEnemyReinforcementCounterDepth5 += fFrametime;
					break;
				}
			}
		}
	}

	/* FLEET COLLISIONS */

	// collision against bottom border

	float bottomBorder = this->m_fScreenHeight;
	bottomBorder += 0.15f * this->m_fScreenHeight;
	bottomBorder = -1.0f * bottomBorder;

	this->m_pReinforcements.SetFirst();
	while( this->m_pReinforcements.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

		if( pEnemy->GetReinforcementAction() == IEnemy::eREINFORCEMENT_ACTION_SENT )
		{
			float borderY = bottomBorder - (pEnemy->GetHeight() / 2);

			if( pEnemy->GetPosition().y <= borderY)
			{
				pEnemy->ResetFleeMovement();
				pEnemy->SetActive(FALSE);
			}
		}
		this->m_pReinforcements.SetNext();
	}

	//END********* UPDATE FLEET ENEMIES *******
}

void CTheGame::UpdateBullets(float fFrametime)
{
	//START*************** UPDATE BULLETS *********************

	int velocity = this->m_pPlayer->GetVelocity();

	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			this->m_pBullets.GetCurrent()->Update(fFrametime, velocity);
		}
		this->m_pBullets.SetNext();
	}

	//END***************** UPDATE BULLETS *********************
}

void CTheGame::UpdateExplosions(float fFrametime)
{
	//START************* UPDATE EXPLOSIONS *************

	this->m_pExplosions->Update(fFrametime, this->m_iGameState);

	//END*************** UPDATE EXPLOSIONS *************
}

void CTheGame::UpdateTime(float fFrametime)
{
	//START*********** UPDATE TIMER *****************

	if(	(this->m_iGameState != GAME_STATE_LOAD_LEVEL) && 
		(this->m_iGameState != GAME_STATE_LEVEL_INTRO) && 
		(this->m_iGameState != GAME_STATE_BOSS_BIG_EXPLOSION) && 
		(this->m_iGameState != GAME_STATE_LEVEL_OUTRO) &&  
		(this->m_iGameState != GAME_STATE_END_SUCCESS) && 
		(this->m_iGameState != GAME_STATE_END_FAILED) && 
		(this->m_iGameState != GAME_STATE_QUIT))
	{
		this->m_fGameTime += fFrametime;
	}

	//END************* UPDATE TIMER *****************
}

void CTheGame::UpdateVelocityTimeMargin(float fFrametime)
{
	float velocity = this->m_pPlayer->GetVelocity();
	this->m_fVelocityTimeMargin = velocity * (fFrametime / 8);
}

void CTheGame::UpdateVelocityPixels()
{
	float velocity = this->m_pPlayer->GetVelocity();

	if(	(velocity >= 100.0f) && (velocity <= 149.0f) )
	{
		this->m_iVelocityPixels = 0;
	}
	else if((velocity >= 150.0f) && (velocity <= 199.0f) )
	{
		this->m_iVelocityPixels = 1;
	}
	else if((velocity >= 200.0f) && (velocity <= 249.0f) )
	{
		this->m_iVelocityPixels = 2;
	}
	else if((velocity >= 250.0f) && (velocity <= 299.0f) )
	{
		this->m_iVelocityPixels = 3;
	}
	else if((velocity >= 300.0f) && (velocity <= 349.0f) )
	{
		this->m_iVelocityPixels = 4;
	}
	else if((velocity >= 350.0f) && (velocity <= 399.0f) )
	{
		this->m_iVelocityPixels = 5;
	}
	else if((velocity >= 400.0f) && (velocity <= 449.0f) )
	{
		this->m_iVelocityPixels = 6;
	}
	else if((velocity >= 450.0f) && (velocity <= 499.0f) )
	{
		this->m_iVelocityPixels = 7;
	}
	else if(velocity >= 500.0f)
	{
		this->m_iVelocityPixels = 8;
	}
}

void CTheGame::UpdateBackgroundVelocity()
{
	int speed = 0;

	speed = this->m_pSpriteBackgroundTop->GetDefaultSpeed() + this->m_iVelocityPixels;
	this->m_pSpriteBackgroundTop->SetSpeed(speed);
}

void CTheGame::UpdateExplosionVelocity()
{
	this->m_pExplosions->UpdateVelocity(this->m_iVelocityPixels, this->m_iGameState);
}


void CTheGame::RenderPlayer(float fFrametime)
{
	//START************* RENDER PLAYER *******************

	// player is destroyed
	if( this->m_pPlayer->IsDestroyed() )
	{
		if(this->m_iGameState != GAME_STATE_QUIT)
		{
			this->m_fPlayerEnterTimer -= fFrametime;

			// turn miniguns straight

			if(this->m_pPlayer->GetMinigunMode() == 1)
			{
				this->m_pPlayer->SetMinigunMode(0);
				this->m_pPlayerMinigunLeft->SetRotation(true);
				this->m_pPlayerMinigunRight->SetRotation(true);
			}
			else if(this->m_pPlayer->GetMinigunMode() == 0)
			{
				this->m_pPlayerMinigunLeft->Update(fFrametime);
				this->m_pPlayerMinigunRight->Update(fFrametime);
			}

			if(this->m_fPlayerEnterTimer <= 0.0f)
			{
				this->m_fPlayerEnterTimer = 0.0f;
				this->PlayerSetEnter(m_iGameState);
				this->m_bPlayerEnter = true;
			}
		}
	}
	else
	{
		bool blink;

		static bool visible = true;

		if( this->m_pPlayer->IsUntouchable() )
		{
			blink = true;
		}
		else
		{
			blink = false;
		}

		if(blink)
		{
			if(visible)
			{
				this->m_pPlayer->Render();

				if(this->m_iGameState != GAME_STATE_QUIT)
				{
					this->m_fPlayerBlinkTimer -= fFrametime;
				}

				if(this->m_fPlayerBlinkTimer <= 0.0f)
				{
					this->m_fPlayerBlinkTimer = 0.03f;
					visible = false;
				}
			}
			else
			{
				if(this->m_iGameState != GAME_STATE_QUIT)
				{
					this->m_fPlayerBlinkTimer -= fFrametime;
				}

				if(this->m_fPlayerBlinkTimer <= 0.0f)
				{
					this->m_fPlayerBlinkTimer = 0.03f;
					visible = true;
				}
			}
		}
		else
		{
			this->m_pPlayer->Render();
		}

		if(	this->m_pPlayer->IsVelocityControl() && this->m_pPlayer->IsBoostIncrease())
		{
			this->RenderPlayerAfterburn(false);
		}
	}

	//END*************** RENDER PLAYER *******************
}

void CTheGame::RenderBoss(float fFrametime, bool bFreeze)
{
	// render all active boss parts

	switch( this->m_pLevel->GetLevelNumber() )
	{
	case 1:
	case 2:
	case 3:

		if( this->m_pEnemyBoss1Frame->IsActive() )
		{
			this->m_pEnemyBoss1Frame->Render();
		}
		if( this->m_pEnemyBoss1LaserLeft->IsActive() )
		{
			this->m_pEnemyBoss1LaserLeft->Render();
		}
		if( this->m_pEnemyBoss1LaserRight->IsActive() )
		{
			this->m_pEnemyBoss1LaserRight->Render();
		}
		if( this->m_pEnemyBoss1ScatterLeft->IsActive() )
		{
			this->m_pEnemyBoss1ScatterLeft->Render();
		}
		if( this->m_pEnemyBoss1ScatterRight->IsActive() )
		{
			this->m_pEnemyBoss1ScatterRight->Render();
		}

		this->m_pEnemyBoss1Cannon->Render(	this->m_pEnemyBoss1Frame,
											fFrametime,
											bFreeze);
		break;
	}
}

void CTheGame::RenderActiveEnemies(float fFrametime, bool bFreeze)
{
	//START************ RENDER ACTIVE ENEMIES ******************

	this->m_pActiveEnemies.SetFirst();
	while( this->m_pActiveEnemies.GetCurrent() )
	{
		if( this->m_pActiveEnemies.GetCurrent()->IsActive() )
		{
			IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

			if(!bFreeze)
			{
				// enemy is ready to flee
				if(pEnemy->IsFleeReady())
				{
					// no other enemies in the way
					if( this->ActiveEnemyLineOfFire(pEnemy, false) )
					{
						pEnemy->SetFleeReady(false);
						pEnemy->SetFleeMovement(true);
						pEnemy->SetAfterburn(true);
						pEnemy->SetMovement(IEnemy::eMOVE_DOWN);
					}
				}

				pEnemy->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			this->m_pActiveEnemies.SetFirst();
			while( pEnemy != this->m_pActiveEnemies.GetCurrent() )
			{
				this->m_pActiveEnemies.SetNext();
			}

			this->m_pActiveEnemies.GetCurrent()->Render(this->m_pTheApp->GetDevice());

			// render enemy afterburn
			if(pEnemy->GetType() != IEnemy::eTYPE_ROLLER)
			{
				if( pEnemy->GetAfterburn() )
				{
					if(this->m_iGameState == GAME_STATE_BLAST_ACTIVE)
					{
						pEnemy->RenderEnemyAfterburn(bFreeze, false);
					}
					else
					{
						pEnemy->RenderEnemyAfterburn(bFreeze, true);
					}
				}
			}

			// if enemy reaches bottom of the screen, it will be removed
			if(!bFreeze)
			{
				float bottomBorder = this->m_fScreenHeight + (pEnemy->GetHeight() / 2);
				bottomBorder += 0.15f * this->m_fScreenHeight;
				bottomBorder = -1.0f * bottomBorder;

				if(pEnemy->GetPosition().y <= bottomBorder)
				{
					pEnemy->ResetFleeMovement();
					pEnemy->SetActive(FALSE);

					this->m_iMaxEnemies--;

					if(this->m_iGameState != GAME_STATE_END_FAILED)
					{
						if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_LAUNCH)
						{
							this->m_iEnemiesLaunch++;
						}
						else if(pEnemy->GetBehaviour() == IEnemy::eBEHAVIOUR_STRIKE)
						{
							this->m_iEnemiesStrike++;
						}
					}
				}
			}
		}
		this->m_pActiveEnemies.SetNext();
	}

	//END************** RENDER ACTIVE ENEMIES ******************
}

void CTheGame::RenderReinforcements(float fFrametime, bool bFreeze)
{
	//START********* RENDER FLEET ENEMIES ***************

	this->m_pReinforcements.SetFirst();
	while( this->m_pReinforcements.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pReinforcements.GetCurrent();

		if(pEnemy->GetReinforcementAction() == IEnemy::eREINFORCEMENT_ACTION_SENT)
		{
			if(!bFreeze)
			{
				pEnemy->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			this->m_pReinforcements.SetFirst();
			while( pEnemy != this->m_pReinforcements.GetCurrent() )
			{
				this->m_pReinforcements.SetNext();
			}

			this->m_pReinforcements.GetCurrent()->Render(this->m_pTheApp->GetDevice());

			// render enemy afterburn
			if(pEnemy->GetType() != IEnemy::eTYPE_ROLLER)
			{
				if( pEnemy->GetAfterburn() )
				{
					if(this->m_iGameState == GAME_STATE_BLAST_ACTIVE)
					{
						pEnemy->RenderEnemyAfterburn(bFreeze, false);
					}
					else
					{
						pEnemy->RenderEnemyAfterburn(bFreeze, true);
					}
				}
			}
		}
		this->m_pReinforcements.SetNext();
	}

	//END*********** RENDER REINFORCEMENT ENEMIES ***************
}

void CTheGame::RenderObstacleEnemies(float fFrametime, bool bFreeze)
{
	//START************ RENDER OBSTACLE ENEMIES ******************

	this->m_pObstacleEnemies.SetFirst();
	while( this->m_pObstacleEnemies.GetCurrent() )
	{
		if( this->m_pObstacleEnemies.GetCurrent()->IsActive() )
		{
			IEnemy* pEnemy = this->m_pObstacleEnemies.GetCurrent();

			// update
			if(!bFreeze)
			{
				pEnemy->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if( pEnemy->GetPosition().y <= (this->m_fScreenHeight + (pEnemy->GetHeight() + 17.0f)) )
			{
				this->m_pObstacleEnemies.SetFirst();
				while( pEnemy != this->m_pObstacleEnemies.GetCurrent() )
				{
					this->m_pObstacleEnemies.SetNext();
				}

				this->m_pObstacleEnemies.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// if enemy reaches bottom of the screen, it will be removed
				if(!bFreeze)
				{
					float bottomBorder = this->m_fScreenHeight + (pEnemy->GetHeight() / 2);
					bottomBorder += 0.15f * this->m_fScreenHeight;
					bottomBorder = -1.0f * bottomBorder;

					if (pEnemy->GetPosition().y <= bottomBorder)
					{
						pEnemy->ResetFleeMovement();
						pEnemy->SetActive(FALSE);
					}
				}
			}
		}
		this->m_pObstacleEnemies.SetNext();
	}

	//END************** RENDER OBSTACLE ENEMIES ******************
}

void CTheGame::RenderObstacles(float fFrametime, bool bFreeze)
{
	//START************* RENDER OBSTACLES *******************

	float verticalBorderMargin = 60.0f;

	/* depth 1 obstacles */

	this->m_pObstaclesDepth1.SetFirst();
	while (this->m_pObstaclesDepth1.GetCurrent())
	{
		if (this->m_pObstaclesDepth1.GetCurrent()->IsActive())
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth1.GetCurrent();

			// update
			if (!bFreeze)
			{
				pObstacle->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if (pObstacle->GetPosition().y <= (this->m_fScreenHeight + verticalBorderMargin))
			{
				this->m_pObstaclesDepth1.SetFirst();
				while (pObstacle != this->m_pObstaclesDepth1.GetCurrent())
				{
					this->m_pObstaclesDepth1.SetNext();
				}

				this->m_pObstaclesDepth1.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// obstacle reached bottom of the screen, remove it
				if (!bFreeze && (pObstacle->GetPosition().y < -(this->m_fScreenHeight + verticalBorderMargin)))
				{
					this->m_pObstaclesDepth1.GetCurrent()->SetActive(FALSE);
					this->m_iObstaclesPassed++;
				}
			}
		}
		this->m_pObstaclesDepth1.SetNext();
	}

	/* depth 2 obstacles */

	this->m_pObstaclesDepth2.SetFirst();
	while( this->m_pObstaclesDepth2.GetCurrent() )
	{
		if( this->m_pObstaclesDepth2.GetCurrent()->IsActive() )
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth2.GetCurrent();

			// update
			if(!bFreeze)
			{
				pObstacle->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if( pObstacle->GetPosition().y <= (this->m_fScreenHeight + verticalBorderMargin) )
			{
				this->m_pObstaclesDepth2.SetFirst();
				while( pObstacle != this->m_pObstaclesDepth2.GetCurrent() )
				{
					this->m_pObstaclesDepth2.SetNext();
				}

				this->m_pObstaclesDepth2.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// obstacle reached bottom of the screen, remove it
				if (!bFreeze && (pObstacle->GetPosition().y < -(this->m_fScreenHeight + verticalBorderMargin)))
				{
					this->m_pObstaclesDepth2.GetCurrent()->SetActive(FALSE);
				}
			}
		}
		this->m_pObstaclesDepth2.SetNext();
	}

	/* depth 3 obstacles */

	this->m_pObstaclesDepth3.SetFirst();
	while( this->m_pObstaclesDepth3.GetCurrent() )
	{
		if( this->m_pObstaclesDepth3.GetCurrent()->IsActive() )
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth3.GetCurrent();

			// update
			if(!bFreeze)
			{
				pObstacle->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if( pObstacle->GetPosition().y <= (this->m_fScreenHeight + verticalBorderMargin) )
			{
				this->m_pObstaclesDepth3.SetFirst();
				while( pObstacle != this->m_pObstaclesDepth3.GetCurrent() )
				{
					this->m_pObstaclesDepth3.SetNext();
				}

				this->m_pObstaclesDepth3.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// obstacle reached bottom of the screen, remove it
				if (!bFreeze && (pObstacle->GetPosition().y < -(this->m_fScreenHeight + verticalBorderMargin)))
				{
					this->m_pObstaclesDepth3.GetCurrent()->SetActive(FALSE);
				}
			}
		}
		this->m_pObstaclesDepth3.SetNext();
	}

	/* depth 4 obstacles */

	this->m_pObstaclesDepth4.SetFirst();
	while( this->m_pObstaclesDepth4.GetCurrent() )
	{
		if( this->m_pObstaclesDepth4.GetCurrent()->IsActive() )
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth4.GetCurrent();

			// update
			if(!bFreeze)
			{
				pObstacle->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if( pObstacle->GetPosition().y <= (this->m_fScreenHeight + verticalBorderMargin) )
			{
				this->m_pObstaclesDepth4.SetFirst();
				while( pObstacle != this->m_pObstaclesDepth4.GetCurrent() )
				{
					this->m_pObstaclesDepth4.SetNext();
				}

				this->m_pObstaclesDepth4.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// obstacle reached bottom of the screen, remove it
				if (!bFreeze && (pObstacle->GetPosition().y < -(this->m_fScreenHeight + verticalBorderMargin)))
				{
					this->m_pObstaclesDepth4.GetCurrent()->SetActive(FALSE);
				}
			}
		}
		this->m_pObstaclesDepth4.SetNext();
	}

	/* depth 5 obstacles */

	this->m_pObstaclesDepth5.SetFirst();
	while( this->m_pObstaclesDepth5.GetCurrent() )
	{
		if( this->m_pObstaclesDepth5.GetCurrent()->IsActive() )
		{
			CObstacle* pObstacle = this->m_pObstaclesDepth5.GetCurrent();

			// update
			if(!bFreeze)
			{
				pObstacle->Update(fFrametime, this->m_pPlayer->GetVelocity());
			}

			// render
			if( pObstacle->GetPosition().y <= (this->m_fScreenHeight + verticalBorderMargin) )
			{
				this->m_pObstaclesDepth5.SetFirst();
				while( pObstacle != this->m_pObstaclesDepth5.GetCurrent() )
				{
					this->m_pObstaclesDepth5.SetNext();
				}

				this->m_pObstaclesDepth5.GetCurrent()->Render(this->m_pTheApp->GetDevice());

				// obstacle reached bottom of the screen, remove it
				if (!bFreeze && (pObstacle->GetPosition().y < -(this->m_fScreenHeight + verticalBorderMargin)))
				{
					this->m_pObstaclesDepth5.GetCurrent()->SetActive(FALSE);
				}
			}
		}
		this->m_pObstaclesDepth5.SetNext();
	}

	//END*************** RENDER OBSTACLES *******************
}

void CTheGame::RenderBullets(float fFrametime, bool bFreeze)
{
	//START*************** RENDER BULLETS *********************

	int velocity = this->m_pPlayer->GetVelocity();

	// boss bullets

	if( (this->m_iGameState == GAME_STATE_BOSS_ACTION) || 
		(this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
		(this->m_iGameState == GAME_STATE_BOSS_BIG_EXPLOSION))
	{
		switch( this->m_pLevel->GetLevelNumber())
		{
		case 1:
		case 2:
		case 3:

			this->m_pEnemyBoss1LaserLeft->RenderBullets(bFreeze, fFrametime, velocity);
			this->m_pEnemyBoss1LaserRight->RenderBullets(bFreeze, fFrametime, velocity);
			this->m_pEnemyBoss1ScatterLeft->RenderBullets(bFreeze, fFrametime, velocity);
			this->m_pEnemyBoss1ScatterRight->RenderBullets(bFreeze, fFrametime, velocity);

			break;

		}
	}
	else
	{
		if(	(this->m_iGameState == GAME_STATE_BLAST_ACTIVE) || 
			(this->m_iGameState == GAME_STATE_END_FAILED) || 
			(this->m_iGameState == GAME_STATE_QUIT))
		{
			if(	(this->m_iGameStatePrevious == GAME_STATE_BOSS_ACTION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_CHAIN_EXPLOSION) || 
				(this->m_iGameStatePrevious == GAME_STATE_BOSS_BIG_EXPLOSION))
			{
				switch( this->m_pLevel->GetLevelNumber())
				{
				case 1:
				case 2:
				case 3:

					this->m_pEnemyBoss1LaserLeft->RenderBullets(bFreeze, fFrametime, velocity);
					this->m_pEnemyBoss1LaserRight->RenderBullets(bFreeze, fFrametime, velocity);
					this->m_pEnemyBoss1ScatterLeft->RenderBullets(bFreeze, fFrametime, velocity);
					this->m_pEnemyBoss1ScatterRight->RenderBullets(bFreeze, fFrametime, velocity);

					break;
				}
			}
		}
	}

	// active enemies
	this->m_pActiveEnemies.SetFirst();
	while( this->m_pActiveEnemies.GetCurrent() )
	{
		IEnemy* pEnemy = this->m_pActiveEnemies.GetCurrent();

		if( pEnemy->IsActive() )
		{
			pEnemy->RenderBullets(bFreeze, fFrametime, velocity);
		}

		this->m_pActiveEnemies.SetNext();
	}

	// bullets in general queue
	this->m_pBullets.SetFirst();
	while( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			this->m_pBullets.GetCurrent()->Render(this->m_pTheApp->GetDevice());

			// bullet positions
			D3DXVECTOR3* pPos;

			switch(this->m_pBullets.GetCurrent()->GetOwner() )
			{
			case CWeapon::eOWNER_PLAYER:

				pPos = m_pBullets.GetCurrent()->GetBulletPosition();
				this->m_pBullets.GetCurrent()->DrawSpriteBulletPlayer(	pPos[1],
																		pPos[2],
																		this->m_pBullets.GetCurrent()->BulletVisibility(1),
																		this->m_pBullets.GetCurrent()->BulletVisibility(2) );
				break;

			case CWeapon::eOWNER_ENEMY:

				switch( this->m_pBullets.GetCurrent()->GetBulletType() )
				{
				case CWeapon::eBULLET_TYPE_ENEMY_DRONE:
					this->m_pBullets.GetCurrent()->DrawSpriteBulletDrone();
					break;
				case CWeapon::eBULLET_TYPE_ENEMY_SNIPER:
					this->m_pBullets.GetCurrent()->DrawSpriteBulletSniper();
					break;
				case CWeapon::eBULLET_TYPE_ENEMY_ROLLER:
					this->m_pBullets.GetCurrent()->DrawSpriteBulletRoller();
					break;
				case CWeapon::eBULLET_TYPE_ENEMY_GUARD:
					this->m_pBullets.GetCurrent()->DrawSpriteBulletGuard();
					break;
				}
				break;
			}
		}
		this->m_pBullets.SetNext();
	}

	//END***************** RENDER BULLETS *********************
}

void CTheGame::RenderExplosions()
{
	//START************* RENDER EXPLOSIONS *************

	this->m_pExplosions->Render(this->m_iGameState);

	//END*************** RENDER EXPLOSIONS *************
}

void CTheGame::RenderParticles(float fFrametime, bool bFreeze)
{
	//START************* RENDER PARTICLES *************
	/*
	this->m_pParticles.SetFirst();
	while( this->m_pParticles.GetCurrent() )
	{
		if( this->m_pParticles.GetCurrent()->GetActive() )
		{
			CParticleSystem* pParticle = this->m_pParticles.GetCurrent();

			if(!bFreeze)
			{
				pParticle->Update(fFrametime);
			}

			this->m_pParticles.SetFirst();
			while( pParticle != this->m_pParticles.GetCurrent() )
			{
				this->m_pParticles.SetNext();
			}

			this->m_pParticles.GetCurrent()->Render(this->m_pTheApp->GetDevice());
		}
		this->m_pParticles.SetNext();
	}
	*/
	//END*************** RENDER PARTICLES *************
}

void CTheGame::RenderPlayerAfterburn(bool bFreeze)
{
	static int iPause = 0;

	if(iPause == 0)
	{
		iPause = 3;

		const float fPixelMultiplier = 2.5f;

		// player's current position
		D3DXVECTOR3 pos = this->m_pPlayer->GetPosition();

		float fMoveX = pos.x * fPixelMultiplier;
		float fMoveY = pos.y * fPixelMultiplier;

		fMoveY = fMoveY * -1.0f;

		int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
		int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

		posY += 66;

		this->m_pSpritePlayerAfterburn->Draw(posX, posY);
	}
	else
	{
		if(!bFreeze)
		{
			iPause--;
		}
	}
}

void CTheGame::RenderPlayerCannon(float fFrametime, bool bFreeze)
{
	static bool bPlayChargeSound = true;
	static bool bPlayBeamSound = true;

	static float fRechargePause = 0.0f;
	static float fRechargePauseMax = 0.05f;

	//START************ UPDATE PLAYER CANNON ********************

	switch( this->m_ePlayerCannonState )
	{
	case ePLAYER_CANNON_STATE_READY:

		if(!bPlayChargeSound)
		{
			bPlayChargeSound = true;
		}
		if(!bPlayBeamSound)
		{
			bPlayBeamSound = true;
		}
		break;

	case ePLAYER_CANNON_STATE_CHARGE:

		if( this->m_iGameState != GAME_STATE_BLAST_ACTIVE )
		{
			if(bPlayChargeSound)
			{
				// play sound effect
				this->PlaySoundPlayerCannonCharge();
				bPlayChargeSound = false;
			}
			// render player cannon charge
			this->RenderPlayerCannonCharge(fFrametime, bFreeze);
		}
		break;

	case ePLAYER_CANNON_STATE_BEAM:

		if( this->m_iGameState != GAME_STATE_BLAST_ACTIVE )
		{
			if(bPlayBeamSound)
			{
				// play sound effect
				this->PlaySoundPlayerCannonBeam();
				bPlayBeamSound = false;
			}
			// player cannon has energy left
			if( this->m_pPlayer->GetCannonEnergy() > 0 )
			{
				// render player cannon beam
				this->RenderPlayerCannonBeam(fFrametime, bFreeze);

				// decrease player cannon energy
				if(!bFreeze)
				{
					int iDecrease = int( ceil(100.0f * fFrametime) );
					this->m_pPlayer->DecreaseCannonEnergy(iDecrease);
				}
			}
			// player cannon has depleted it's energy
			else
			{
				// cannon can damage enemies again
				this->EnablePlayerCannonDamage();
				// start recharging player cannon
				this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_RECHARGE;
			}
		}
		break;

	case ePLAYER_CANNON_STATE_RECHARGE:

		// when player blast is active cannon recharge pauses
		// and also if freeze is active
		if( (this->m_iGameState != GAME_STATE_BLAST_ACTIVE) && !bFreeze )
		{
			// player cannon has fully recharged
			if( this->m_pPlayer->IsCannonEnergyMax() )
			{
				// player cannon is ready to be fired again
				this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_READY;

				fRechargePause = 0.0f;
			}
			// recharge cannon
			else
			{
				if(fRechargePause <= 0.0f)
				{
					int iIncrease = 0;

					iIncrease = int( ceil(100.0f * fFrametime) );
					iIncrease = int( ceil(iIncrease * 0.5f) );

					this->m_pPlayer->IncreaseCannonEnergy(iIncrease);

					fRechargePause = fRechargePauseMax;
				}
				else
				{
					fRechargePause -= fFrametime;
				}
			}
		}
		break;
	}

	//END************** UPDATE PLAYER CANNON ********************
}

void CTheGame::RenderPlayerCannonCharge(float fFrametime, bool bFreeze)
{
	//START************ RENDER PLAYER CANNON CHARGE ************

	const float fPixelMultiplier = 2.5f;

	// cannon charging has ended
	if(this->m_fCannonChargeCounter <= 0.0f)
	{
		// reset active cannon charge texture
		this->m_iCannonChargeTexture = 1;
		// reset overall cannon charge time counter
		this->m_fCannonChargeCounter = this->m_fCannonChargeTime;
		// reset individual cannon charge sprites time
		this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;
		// cannon can hurt bosses
		this->m_bCannonDamageBoss = true;
		// reset cannon charge sprite size value
		this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_SMALL;
		// change to cannon beam animation
		this->m_ePlayerCannonState = ePLAYER_CANNON_STATE_BEAM;
	}
	// draw cannon charge sprites
	else
	{
		// player's current position
		D3DXVECTOR3 pos = this->m_pPlayer->GetPosition();

		float fMoveX = pos.x * fPixelMultiplier;
		float fMoveY = pos.y * fPixelMultiplier;

		fMoveY = fMoveY * -1.0f;

		int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
		int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

		posY = posY - 45;

		switch(this->m_ePlayerCannonCharge)
		{
		case ePLAYER_CANNON_CHARGE_SMALL:

			switch(this->m_iCannonChargeTexture)
			{
			case 1:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 0)->Draw(posX, posY);
				break;
			case 2:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 1)->Draw(posX, posY);
				break;
			case 3:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 2)->Draw(posX, posY);
				break;
			case 4:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 3)->Draw(posX, posY);
				break;
			case 5:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 4)->Draw(posX, posY);
				break;
			case 6:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 5)->Draw(posX, posY);
				break;
			case 7:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 6)->Draw(posX, posY);
				break;
			case 8:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 7)->Draw(posX, posY);
				break;
			case 9:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 8)->Draw(posX, posY);
				break;
			case 10:
				(this->m_pSpriteInfoPlayerCannonChargeSmall + 9)->Draw(posX, posY);
				break;
			}

			if(this->m_fSpriteShowCannonChargeCounter <= 0.0f)
			{
				this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;

				if(this->m_iCannonChargeTexture < 10)
				{
					this->m_iCannonChargeTexture++;
				}
				else
				{
					this->m_iCannonChargeTexture = 1;
					this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_MEDIUM;
				}
			}
			else
			{
				if(!bFreeze)
				{
					this->m_fSpriteShowCannonChargeCounter -= fFrametime;
				}
			}

			break;

		case ePLAYER_CANNON_CHARGE_MEDIUM:

			switch(this->m_iCannonChargeTexture)
			{
			case 1:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 0)->Draw(posX, posY);
				break;
			case 2:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 1)->Draw(posX, posY);
				break;
			case 3:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 2)->Draw(posX, posY);
				break;
			case 4:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 3)->Draw(posX, posY);
				break;
			case 5:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 4)->Draw(posX, posY);
				break;
			case 6:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 5)->Draw(posX, posY);
				break;
			case 7:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 6)->Draw(posX, posY);
				break;
			case 8:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 7)->Draw(posX, posY);
				break;
			case 9:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 8)->Draw(posX, posY);
				break;
			case 10:
				(this->m_pSpriteInfoPlayerCannonChargeMedium + 9)->Draw(posX, posY);
				break;
			}

			if(this->m_fSpriteShowCannonChargeCounter <= 0.0f)
			{
				this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;

				if(this->m_iCannonChargeTexture < 10)
				{
					this->m_iCannonChargeTexture++;
				}
				else
				{
					this->m_iCannonChargeTexture = 1;
					this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_LARGE;
				}
			}
			else
			{
				if(!bFreeze)
				{
					this->m_fSpriteShowCannonChargeCounter -= fFrametime;
				}
			}

			break;

		case ePLAYER_CANNON_CHARGE_LARGE:

			switch(this->m_iCannonChargeTexture)
			{
			case 1:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 0)->Draw(posX, posY);
				break;
			case 2:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 1)->Draw(posX, posY);
				break;
			case 3:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 2)->Draw(posX, posY);
				break;
			case 4:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 3)->Draw(posX, posY);
				break;
			case 5:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 4)->Draw(posX, posY);
				break;
			case 6:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 5)->Draw(posX, posY);
				break;
			case 7:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 6)->Draw(posX, posY);
				break;
			case 8:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 7)->Draw(posX, posY);
				break;
			case 9:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 8)->Draw(posX, posY);
				break;
			case 10:
				(this->m_pSpriteInfoPlayerCannonChargeLarge + 9)->Draw(posX, posY);
				break;
			}

			// change shown sprite
			if(this->m_fSpriteShowCannonChargeCounter <= 0.0f)
			{
				this->m_fSpriteShowCannonChargeCounter = this->m_fSpriteShowCannonChargeTime;

				if(this->m_iCannonChargeTexture < 10)
				{
					this->m_iCannonChargeTexture++;
				}
				else
				{
					this->m_iCannonChargeTexture = 1;
					this->m_ePlayerCannonCharge = ePLAYER_CANNON_CHARGE_SMALL;
				}
			}
			else
			{
				if(!bFreeze)
				{
					this->m_fSpriteShowCannonChargeCounter -= fFrametime;
				}
			}

			break;
		}

		// decrease overall cannon charge time
		if(!bFreeze)
		{
			this->m_fCannonChargeCounter -= fFrametime;
		}
	}

	//END************* RENDER PLAYER CANNON CHARGE *************
}

void CTheGame::RenderPlayerCannonBeam(float fFrametime, bool bFreeze)
{
	//START************ RENDER PLAYER CANNON BEAM ************

	const float fPixelMultiplier = 2.5f;
	static bool bBeamToWide = true;

	// cannon energy is full which means 
	// that cannon beam firing has just started
	if(this->m_pPlayer->IsCannonEnergyMax() )
	{
		// reset active cannon beam texture
		this->m_iCannonBeamTexture = 1;
		// reset individual sprites time
		this->m_fSpriteShowCannonBeamCounter = this->m_fSpriteShowCannonBeamTime;
		// reset cannon beam sprite direction values
		this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_CENTER;
		this->m_ePlayerCannonBeamPrevious = ePLAYER_CANNON_BEAM_RIGHT;
	}

	/* draw cannon beam sprites */

	// player's current position
	D3DXVECTOR3 pos = this->m_pPlayer->GetPosition();

	float fMoveX = pos.x * fPixelMultiplier;
	float fMoveY = pos.y * fPixelMultiplier;

	fMoveY = fMoveY * -1.0f;

	int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
	int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

	posX = posX - 22;
	posY = posY - 700;

	switch(this->m_ePlayerCannonBeam)
	{
	case ePLAYER_CANNON_BEAM_CENTER:

		switch(this->m_iCannonBeamTexture)
		{
		case 1:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 0)->Draw(posX, posY);
			break;
		case 2:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 1)->Draw(posX, posY);
			break;
		case 3:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 2)->Draw(posX, posY);
			break;
		case 4:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 3)->Draw(posX, posY);
			break;
		case 5:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 4)->Draw(posX, posY);
			break;
		case 6:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 5)->Draw(posX, posY);
			break;
		case 7:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 6)->Draw(posX, posY);
			break;
		case 8:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 7)->Draw(posX, posY);
			break;
		case 9:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 8)->Draw(posX, posY);
			break;
		case 10:
			(this->m_pSpriteInfoPlayerCannonBeamCenter + 9)->Draw(posX, posY);
			break;
		}

		break;

	case ePLAYER_CANNON_BEAM_LEFT:

		switch(this->m_iCannonBeamTexture)
		{
		case 1:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 0)->Draw(posX, posY);
			break;
		case 2:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 1)->Draw(posX, posY);
			break;
		case 3:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 2)->Draw(posX, posY);
			break;
		case 4:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 3)->Draw(posX, posY);
			break;
		case 5:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 4)->Draw(posX, posY);
			break;
		case 6:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 5)->Draw(posX, posY);
			break;
		case 7:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 6)->Draw(posX, posY);
			break;
		case 8:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 7)->Draw(posX, posY);
			break;
		case 9:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 8)->Draw(posX, posY);
			break;
		case 10:
			(this->m_pSpriteInfoPlayerCannonBeamLeft + 9)->Draw(posX, posY);
			break;
		}

		break;

	case ePLAYER_CANNON_BEAM_RIGHT:

		switch(this->m_iCannonBeamTexture)
		{
		case 1:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 0)->Draw(posX, posY);
			break;
		case 2:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 1)->Draw(posX, posY);
			break;
		case 3:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 2)->Draw(posX, posY);
			break;
		case 4:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 3)->Draw(posX, posY);
			break;
		case 5:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 4)->Draw(posX, posY);
			break;
		case 6:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 5)->Draw(posX, posY);
			break;
		case 7:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 6)->Draw(posX, posY);
			break;
		case 8:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 7)->Draw(posX, posY);
			break;
		case 9:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 8)->Draw(posX, posY);
			break;
		case 10:
			(this->m_pSpriteInfoPlayerCannonBeamRight + 9)->Draw(posX, posY);
			break;
		}

		break;
	}

	// change shown sprite
	if(this->m_fSpriteShowCannonBeamCounter <= 0.0f)
	{
		this->m_fSpriteShowCannonBeamCounter = this->m_fSpriteShowCannonBeamTime;

		// change cannon beam direction
		switch(this->m_ePlayerCannonBeam)
		{
		case ePLAYER_CANNON_BEAM_CENTER:

			switch(this->m_ePlayerCannonBeamPrevious)
			{
			case ePLAYER_CANNON_BEAM_LEFT:
				this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_RIGHT;
				// backup current cannon beam direction
				this->m_ePlayerCannonBeamPrevious = this->m_ePlayerCannonBeam;
				break;
			case ePLAYER_CANNON_BEAM_RIGHT:
				this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_LEFT;
				// backup current cannon beam direction
				this->m_ePlayerCannonBeamPrevious = this->m_ePlayerCannonBeam;
				break;
			}
			break;

		case ePLAYER_CANNON_BEAM_LEFT:
			this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_CENTER;
			break;

		case ePLAYER_CANNON_BEAM_RIGHT:
			this->m_ePlayerCannonBeam = ePLAYER_CANNON_BEAM_CENTER;
			break;
		}

		if(this->m_iCannonBeamTexture == 1)
		{
			bBeamToWide = true;
		}
		else if(this->m_iCannonBeamTexture == 10)
		{
			bBeamToWide = false;
		}

		if(bBeamToWide)
		{
			this->m_iCannonBeamTexture++;
		}
		else
		{
			this->m_iCannonBeamTexture--;
		}
	}
	else
	{
		if(!bFreeze)
		{
			this->m_fSpriteShowCannonBeamCounter -= fFrametime;
		}
	}

	//END************* RENDER PLAYER CANNON BEAM *************
}

void CTheGame::RenderStatistics(float fFrametime)
{
	if(this->m_iGameState != GAME_STATE_LOAD_LEVEL)
	{
		if(this->m_iGameState == GAME_STATE_QUIT)
		{
			if(this->m_bFadeOut)
			{
				this->RenderPlayerLives();
				this->RenderPlayerBlasts();
				this->RenderPlayerHealthBar();
				this->RenderPlayerCannonBar();
				this->RenderScore(fFrametime);
				this->RenderTime(fFrametime);
			}
		}
		else
		{
			this->RenderPlayerLives();
			this->RenderPlayerBlasts();
			this->RenderPlayerHealthBar();
			this->RenderPlayerCannonBar();
			this->RenderScore(fFrametime);
			this->RenderTime(fFrametime);
		}
	}
}

void CTheGame::RenderPlayerLives()
{
	//START******* RENDER PLAYER LIVES ************

	int iLives = this->m_pPlayer->GetLives();

	if (iLives < 0)
		iLives = 0;

	int iBaseX = this->m_pGameSettings->m_iPlayerLivesBasePositionX;
	int iBaseY = this->m_pGameSettings->m_iPlayerLivesBasePositionY;
	int iNumberX = this->m_pGameSettings->m_iPlayerLivesNumberPositionX;
	int iNumberY = this->m_pGameSettings->m_iPlayerLivesNumberPositionY;

	// base layer
	(this->m_pSpriteInfoPlayerLives + 10)->Draw(iBaseX,iBaseY);
	// number of lives
	(this->m_pSpriteInfoPlayerLives + iLives)->Draw(iNumberX,iNumberY);

	//END********* RENDER PLAYER LIVES ************
}

void CTheGame::RenderPlayerBlasts()
{
	//START******* RENDER PLAYER BLASTS ************

	int iBlasts = this->m_pPlayer->GetBlasts();

	int iBaseX = this->m_pGameSettings->m_iPlayerBlastsBasePositionX;
	int iBaseY = this->m_pGameSettings->m_iPlayerBlastsBasePositionY;
	int iNumberX = this->m_pGameSettings->m_iPlayerBlastsNumberPositionX;
	int iNumberY = this->m_pGameSettings->m_iPlayerBlastsNumberPositionY;

	// base layer
	(this->m_pSpriteInfoPlayerBlasts + 10)->Draw(iBaseX,iBaseY);
	// number of blasts
	(this->m_pSpriteInfoPlayerBlasts + iBlasts)->Draw(iNumberX,iNumberY);

	//END********* RENDER PLAYER BLASTS ************
}

void CTheGame::RenderPlayerHealthBar()
{
	//START******* RENDER PLAYER HEALTH BAR **********

	int iHealth = this->m_pPlayer->GetHealth();

	int iBarX = this->m_pGameSettings->m_iPlayerHealthBarPositionX;
	int iBarY = this->m_pGameSettings->m_iPlayerHealthBarPositionY;
	int iMeterX = this->m_pGameSettings->m_iPlayerHealthMeterPositionX;
	int iMeterY = this->m_pGameSettings->m_iPlayerHealthMeterPositionY;

	// health units
	for(int i = 1; i <= iHealth; i++)
	{
		if(i == 1)
		{
			(this->m_pSpriteInfoPlayerHealth + 0)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 2)
		{
			(this->m_pSpriteInfoPlayerHealth + 1)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 3)
		{
			(this->m_pSpriteInfoPlayerHealth + 2)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 4)
		{
			(this->m_pSpriteInfoPlayerHealth + 3)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 97)
		{
			(this->m_pSpriteInfoPlayerHealth + 5)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 98)
		{
			(this->m_pSpriteInfoPlayerHealth + 6)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 99)
		{
			(this->m_pSpriteInfoPlayerHealth + 7)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 100)
		{
			(this->m_pSpriteInfoPlayerHealth + 8)->Draw(iMeterX,
													iMeterY);
		}
		else
		{
			(this->m_pSpriteInfoPlayerHealth + 4)->Draw(iMeterX,
													iMeterY);
		}

		if(i == 1)
		{
			iMeterX = iMeterX + 4;
		}
		else
		{
			iMeterX = iMeterX + 2;
		}
	}

	// health bar
	(this->m_pSpriteInfoPlayerHealth + 9)->Draw(iBarX,iBarY);

	//END********* RENDER PLAYER HEALTH BAR **********
}

void CTheGame::RenderPlayerCannonBar()
{
	//START******* RENDER PLAYER CANNON BAR **********

	int iCannonEnergy = this->m_pPlayer->GetCannonEnergy();

	int iBarX = this->m_pGameSettings->m_iPlayerCannonBarPositionX;
	int iBarY = this->m_pGameSettings->m_iPlayerCannonBarPositionY;
	int iMeterX = this->m_pGameSettings->m_iPlayerCannonMeterPositionX;
	int iMeterY = this->m_pGameSettings->m_iPlayerCannonMeterPositionY;

	// cannon energy units
	for(int i = 1; i <= iCannonEnergy; i++)
	{
		if(i == 1)
		{
			(this->m_pSpriteInfoPlayerCannon + 0)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 2)
		{
			(this->m_pSpriteInfoPlayerCannon + 1)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 3)
		{
			(this->m_pSpriteInfoPlayerCannon + 2)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 4)
		{
			(this->m_pSpriteInfoPlayerCannon + 3)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 5)
		{
			(this->m_pSpriteInfoPlayerCannon + 4)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 6)
		{
			(this->m_pSpriteInfoPlayerCannon + 5)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 7)
		{
			(this->m_pSpriteInfoPlayerCannon + 6)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 194)
		{
			(this->m_pSpriteInfoPlayerCannon + 8)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 195)
		{
			(this->m_pSpriteInfoPlayerCannon + 9)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 196)
		{
			(this->m_pSpriteInfoPlayerCannon + 10)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 197)
		{
			(this->m_pSpriteInfoPlayerCannon + 11)->Draw(iMeterX,
													iMeterY);
		}
		else if(i == 198)
		{
			(this->m_pSpriteInfoPlayerCannon + 12)->Draw(	iMeterX,
														iMeterY);
		}
		else if(i == 199)
		{
			(this->m_pSpriteInfoPlayerCannon + 13)->Draw(	iMeterX,
														iMeterY);
		}
		else if(i == 200)
		{
			(this->m_pSpriteInfoPlayerCannon + 14)->Draw(	iMeterX,
														iMeterY);
		}
		else
		{
			(this->m_pSpriteInfoPlayerCannon + 7)->Draw(iMeterX,
													iMeterY);
		}

		if(i == 1)
		{
			iMeterX = iMeterX + 3;
		}
		else
		{
			iMeterX = iMeterX + 1;
		}
	}

	// cannon bar
	(this->m_pSpriteInfoPlayerCannon + 15)->Draw(iBarX,iBarY);

	//END********* RENDER PLAYER CANNON BAR **********
}

void CTheGame::RenderScore(float fFrametime)
{
	//START******* RENDER PLAYER SCORE **********

	char* pPointer;
	char* sScore = NULL;
	sScore = this->m_pPlayer->GetScoreString();
	pPointer = sScore;

	D3DXVECTOR3 pos;

	pos = D3DXVECTOR3(	this->m_fScreenWidth - 62.0f,
						this->m_fScreenHeight - 19.8f,
						-1000.0f);

	(this->m_pHudObject + LOAD_CONTAINER_HUD_SCORE_TEXT)->SetPosition(pos);
	(this->m_pHudObject + LOAD_CONTAINER_HUD_SCORE_TEXT)->Update(fFrametime);
	(this->m_pHudObject + LOAD_CONTAINER_HUD_SCORE_TEXT)->Render(this->m_pTheApp->GetDevice());

	pos = D3DXVECTOR3(	this->m_fScreenWidth - 39.0f,
						this->m_fScreenHeight - 20.0f,
						-1000.0f);

	while( (*pPointer) != NULL )
	{
		(this->m_pNumbersScore + ((*pPointer) - '0'))->SetPosition(pos);
		(this->m_pNumbersScore + ((*pPointer) - '0'))->Update(fFrametime);
		(this->m_pNumbersScore + ((*pPointer) - '0'))->Render(this->m_pTheApp->GetDevice());
		pos.x += (this->m_pNumbersScore + ((*pPointer) - '0'))->GetWidth();
		
		pPointer++;
	}

	delete []sScore;
	sScore = NULL;

	//END********* RENDER PLAYER SCORE **********
}

void CTheGame::RenderTime(float fFrametime)
{
	//START********* RENDER TIME ************

	char* pPointer;
	char* sTime = NULL;
	sTime = this->GetTimeString();
	pPointer = sTime;

	D3DXVECTOR3 pos;
	float fPosX = 0.0f;

	pos.y = this->m_fScreenHeight - 20.0f;
	pos.z = -1000.0f;

	if(	(this->m_fGameTime >= 9.5f) && 
		(this->m_fGameTime < 99.5f))
	{
		fPosX -= this->m_pGameSettings->m_fGameNumberWidth * 0.5f;
	}
	else if((this->m_fGameTime >= 99.5f) && 
			(this->m_fGameTime < 999.5f))
	{
		fPosX -= this->m_pGameSettings->m_fGameNumberWidth;
	}
	else if((this->m_fGameTime >= 999.5f) && 
			(this->m_fGameTime < 9999.5f))
	{
		fPosX -= this->m_pGameSettings->m_fGameNumberWidth * 1.5f;
	}

	pos.x = fPosX;

	while( (*pPointer) != NULL )
	{
		(this->m_pNumbersTime + ((*pPointer) - '0'))->SetPosition(pos);
		(this->m_pNumbersTime + ((*pPointer) - '0'))->Update(fFrametime);
		(this->m_pNumbersTime + ((*pPointer) - '0'))->Render(this->m_pTheApp->GetDevice());
		pos.x += (this->m_pNumbersTime + ((*pPointer) - '0'))->GetWidth();
		
		pPointer++;
	}

	delete []sTime;
	sTime = NULL;

	/*
	this->m_pTheApp->BeginText();

	TCHAR tMsg[256];

	_stprintf_s(tMsg, _T("Boost: %f"), this->m_pPlayer->GetBoost());

	this->m_pTheApp->DrawText(	10,
								700,
								tMsg,
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	this->m_pTheApp->EndText();
	*/

	//END*********** RENDER TIME ************
}

void CTheGame::RenderLevelTitle()
{
	int iTextPosX = 362;
	int iTextPosY = 355;
	int iBoxPosX = 306;
	int iBoxPosY = 341;

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		(this->m_pSpriteLevelTitleSpace + 0)->Draw(iTextPosX, iTextPosY);
		break;
	case 2:
		(this->m_pSpriteLevelTitleSpace + 1)->Draw(iTextPosX, iTextPosY);
		break;
	case 3:
		(this->m_pSpriteLevelTitleSpace + 2)->Draw(iTextPosX, iTextPosY);
		break;
	}
	(this->m_pSpriteLevelTitleSpace + 6)->Draw(iBoxPosX, iBoxPosY);
}

bool CTheGame::RenderLevelTitleIn()
{
	static int iTextPosX = -302;
	static int iTextPosY = 355;
	static int iBoxPosX = 1025;
	static int iBoxPosY = 341;

	const int iMovementSpeedText = 20;
	const int iMovementSpeedBox = 21;

	//const int iMovementSpeedText = 14;
	//const int iMovementSpeedBox = 15;

	bool bMovingIn = true;

	// draw sprites

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		(this->m_pSpriteLevelTitleSpace + 0)->Draw(iTextPosX, iTextPosY);
		break;
	case 2:
		(this->m_pSpriteLevelTitleSpace + 1)->Draw(iTextPosX, iTextPosY);
		break;
	case 3:
		(this->m_pSpriteLevelTitleSpace + 2)->Draw(iTextPosX, iTextPosY);
		break;
	}
	(this->m_pSpriteLevelTitleSpace + 6)->Draw(iBoxPosX, iBoxPosY);

	// reached destination
	if( (iTextPosX == 362) && (iBoxPosX == 306) )
	{
		iTextPosX = -302;
		iBoxPosX = 1025;
		bMovingIn = false;
	}

	// move sprites

	if(iTextPosX < 362)
	{
		if( (iTextPosX + iMovementSpeedText) > 362 )
		{
			iTextPosX = 362;
		}
		else
		{
			iTextPosX += iMovementSpeedText;
		}
	}
	if(iBoxPosX > 306)
	{
		if( (iBoxPosX - iMovementSpeedBox) < 306 )
		{
			iBoxPosX = 306;
		}
		else
		{
			iBoxPosX -= iMovementSpeedBox;
		}
	}

	return bMovingIn;
}

bool CTheGame::RenderLevelTitleOut()
{
	static int iTextPosX = 362;
	static int iTextPosY = 355;
	static int iBoxPosX = 306;
	static int iBoxPosY = 341;

	const int iMovementSpeedText = 30;
	const int iMovementSpeedBox = 31;

	//const int iMovementSpeedText = 16;
	//const int iMovementSpeedBox = 17;

	bool bMovingOut = true;

	// draw sprites

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		(this->m_pSpriteLevelTitleSpace + 0)->Draw(iTextPosX, iTextPosY);
		break;
	case 2:
		(this->m_pSpriteLevelTitleSpace + 1)->Draw(iTextPosX, iTextPosY);
		break;
	case 3:
		(this->m_pSpriteLevelTitleSpace + 2)->Draw(iTextPosX, iTextPosY);
		break;
	}
	(this->m_pSpriteLevelTitleSpace + 6)->Draw(iBoxPosX, iBoxPosY);

	// reached destination
	if( (iBoxPosX == -412) && (iTextPosX == 1025) )
	{
		iTextPosX = 362;
		iBoxPosX = 306;
		bMovingOut = false;
	}

	// move sprites

	if(iBoxPosX > -412)
	{
		if( (iBoxPosX - iMovementSpeedBox) < -412 )
		{
			iBoxPosX = -412;
		}
		else
		{
			iBoxPosX -= iMovementSpeedBox;
		}
	}
	if(iTextPosX < 1025)
	{
		if( (iTextPosX + iMovementSpeedText) > 1025 )
		{
			iTextPosX = 1025;
		}
		else
		{
			iTextPosX += iMovementSpeedText;
		}
	}

	

	return bMovingOut;
}

bool CTheGame::RenderMissionInfo()
{
	return false;
}

bool CTheGame::RenderBossWarning(float fFrametime, bool bFreeze)
{
	int iPosX = 267;
	int iPosY = 350;

	if(this->m_fBossWarningTextTimer <= 0.0f)
	{
		// increase or decrease text sprite array index

		if(this->m_bBossWarningFadeOut)
		{
			// fade out finished
			if(this->m_iBossWarningTextIndex == -1)
			{
				// end boss warning
				if(this->m_fBossWarningEndTimer <= 0.0f)
				{
					this->m_bBossWarning = false;
					return false;
				}
				else
				{
					this->m_fBossWarningEndTimer -= fFrametime;
				}
			}
			else
			{
				this->m_iBossWarningTextIndex--;
				this->m_fBossWarningTextTimer = 0.06f;
			}
		}
		else
		{
			this->m_iBossWarningTextIndex++;
			this->m_fBossWarningTextTimer = 0.015f;
		}

		// reached last sprite, start fade out
		if(this->m_iBossWarningTextIndex == 9)
		{
			this->m_bBossWarningFadeOut = true;
			this->m_fBossWarningTextTimer = 0.8f;
		}
	}
	else if(!bFreeze)
	{
		this->m_fBossWarningTextTimer -= fFrametime;
	}

	// render sprites
	if(	(this->m_iBossWarningTextIndex >= 0) && 
		(this->m_iBossWarningTextIndex <= 9))
	{
		// level type (1-3: space, 4-6: planet)
		if(	(this->m_pLevel->GetLevelNumber() == 1) || 
			(this->m_pLevel->GetLevelNumber() == 2) || 
			(this->m_pLevel->GetLevelNumber() == 3))
		{
			this->m_pSpriteBossWarningSpace[this->m_iBossWarningTextIndex].Draw(iPosX,iPosY);
		}
	}

	return true;
}

void CTheGame::RenderEndSuccess(float fFrametime)
{
	int iPosX = 206;
	int iPosY = 320;

	if(this->m_fEndSuccessStartTimer <= 0.0f)
	{
		if(this->m_iEndSuccessTextIndex < 19)
		{
			if(this->m_fEndSuccessTextTimer <= 0.0f)
			{
				this->m_fEndSuccessTextTimer = 0.1f;
				// increase array index
				this->m_iEndSuccessTextIndex++;
			}
			else
			{
				this->m_fEndSuccessTextTimer -= fFrametime;
			}
		}

		// render sprites
		if(	(this->m_iEndSuccessTextIndex >= 0) && 
			(this->m_iEndSuccessTextIndex <= 19))
		{
			this->m_pSpriteGameWonText[this->m_iEndSuccessTextIndex].Draw(iPosX,iPosY);
		}
	}
	else
	{
		this->m_fEndSuccessStartTimer -= fFrametime;
	}
}

void CTheGame::RenderEndFailed()
{
	this->m_pSpriteGameOverText->Draw(285,354);
}

void CTheGame::RenderBackgrounds()
{
	if(this->m_iGameState != GAME_STATE_LOAD_LEVEL)
	{
		// draw bottom background
		//this->m_pSpriteBackgroundBottom->Draw(0,0);

		// game action is frozen
		if(this->m_iGameState == GAME_STATE_BLAST_ACTIVE)
		{
			// draw top 1 background
			this->m_pSpriteBackgroundMiddle->Draw(true);
			// draw top 2 background
			this->m_pSpriteBackgroundTop->Draw(true);
		}
		// game action is active		
		else
		{
			if(this->m_iGameState == GAME_STATE_QUIT)
			{
				if(this->m_bFadeOut)
				{
					// draw top 1 background
					this->m_pSpriteBackgroundMiddle->Draw(this->m_bFreezeQuit);
					// draw top 2 background
					this->m_pSpriteBackgroundTop->Draw(this->m_bFreezeQuit);
				}
			}
			else
			{
				// draw top 1 background
				this->m_pSpriteBackgroundMiddle->Draw(false);
				// draw top 2 background
				this->m_pSpriteBackgroundTop->Draw(false);
			}
		}
	}
}


void CTheGame::EnablePlayerCannonDamage()
{
	// cannon can damage enemies

	if(this->m_iGameState == GAME_STATE_PLAY_ENEMIES)
	{
		this->m_pActiveEnemies.SetFirst();
		while( this->m_pActiveEnemies.GetCurrent() )
		{
			if( this->m_pActiveEnemies.GetCurrent()->IsActive() )
			{
				this->m_pActiveEnemies.GetCurrent()->SetCannonDamage(true);
			}
			this->m_pActiveEnemies.SetNext();
		}
	}
	else if((this->m_iGameState == GAME_STATE_PLAY_OBSTACLES) || 
			(this->m_iGameState == GAME_STATE_WAIT_OBSTACLES))
	{
		this->m_pObstacleEnemies.SetFirst();
		while( this->m_pObstacleEnemies.GetCurrent() )
		{
			if( this->m_pObstacleEnemies.GetCurrent()->IsActive() )
			{
				this->m_pObstacleEnemies.GetCurrent()->SetCannonDamage(true);
			}
			this->m_pObstacleEnemies.SetNext();
		}
	}
	else if(this->m_iGameState == GAME_STATE_BOSS_ACTION || 
			this->m_iGameState == GAME_STATE_BOSS_CHAIN_EXPLOSION)
	{
		switch(this->m_pLevel->GetLevelNumber())
		{
		// Level 1
		case 1:
		case 2:
		case 3:

			this->m_pEnemyBoss1Frame->SetCannonDamage(true);
			
			if(this->m_pEnemyBoss1LaserLeft->IsActive())
			{
				this->m_pEnemyBoss1LaserLeft->SetCannonDamage(true);
			}
			if(this->m_pEnemyBoss1LaserRight->IsActive())
			{
				this->m_pEnemyBoss1LaserRight->SetCannonDamage(true);
			}
			if(this->m_pEnemyBoss1ScatterLeft->IsActive())
			{
				this->m_pEnemyBoss1ScatterLeft->SetCannonDamage(true);
			}
			if(this->m_pEnemyBoss1ScatterRight->IsActive())
			{
				this->m_pEnemyBoss1ScatterRight->SetCannonDamage(true);
			}

			break;
		}
	}
}


char* CTheGame::GetTimeString()
{
	char* sTime = NULL;
	sTime = new char[128];

	sprintf_s(sTime, 128, "%0.0f", this->m_fGameTime);

	return sTime;
}


bool CTheGame::IsBoxCollision(const D3DXVECTOR3& pos1, float fWidth, float fHeight, const D3DXVECTOR3& pos2){
	
	// i want to find out if point is somewhere between squares boundaries
	if( (pos1.x - fWidth / 2.0f < pos2.x) && ( pos1.x + fWidth / 2.0f > pos2.x) )
	{
		if( (pos1.y - fHeight / 2.0f < pos2.y) && ( pos1.y + fHeight / 2.0f > pos2.x) )
		{
			return true;
		}
	}
	return false;
}

bool CTheGame::IsBoxCollision(const D3DXVECTOR3& pos1, float fWidth1, float fHeight1, const D3DXVECTOR3& pos2, float fWidth2, float fHeight2)
{
	// 2 vectors indicating positions
	// of objects A and B

	D3DXVECTOR3 posA = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 posB = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	// width and height of
	// objects A and B

	float fWidthA;
	float fHeightA;

	float fWidthB;
	float fHeightB;

	bool bSameX = false;

	// object 1 and 2 are on the same X-coordinate 
	if( pos1.x == pos2.x )
	{
		bSameX = true;
	}

	// we set object A to be the one on the left side of object B
	// so object A is always the one more on the left side

	// object A is parameter object 1
	else if( pos1.x < pos2.x )
	{
		posA = pos1;
		fWidthA = fWidth1;
		fHeightA = fHeight1;

		posB = pos2;		
		fWidthB = fWidth2;
		fHeightB = fHeight2;
	}
	// object A is parameter object 2
	else if( pos2.x < pos1.x )
	{
		posA = pos2;
		fWidthA = fWidth2;
		fHeightA = fHeight2;

		posB = pos1;
		fWidthB = fWidth1;
		fHeightB = fHeight1;
	}

	// object 1 and 2 are on the same X-coordinate 
	if(bSameX)
	{
		// object 1 is on top of object 2
		if( pos1.y > pos2.y )
		{
			// if the bottom side of object 1
			// penetrates the top side of object 2
			// then we have definite collision
			if( (pos1.y - (fHeight1 / 2)) < (pos2.y + (fHeight2 / 2)) )
			{
				return true;
			}
		}
		// object 1 is below object 2
		else if( pos1.y < pos2.y )
		{
			// if the top side of object 1
			// penetrates the bottom side of object 2
			// then we have definite collision
			if( (pos1.y + (fHeight1 / 2)) > (pos2.y - (fHeight2 / 2)) )
			{
				return true;
			}
		}
		// object 1 and 2 have the same Y-axis coordinate
		else if( pos1.y == pos2.y )
		{
				return true;
		}
	}

	// right side of object A
	// penetrates the left side of object B
	// we have possible collision
	else if( (posA.x + (fWidthA / 2)) > (posB.x - (fWidthB / 2)) )
	{
		// object A is on top of object B
		if( posA.y > posB.y )
		{
			// if the bottom side of object A
			// penetrates the top side of object B
			// then we have definite collision
			if( (posA.y - (fHeightA / 2)) < (posB.y + (fHeightB / 2)) )
			{
				return true;
			}
		}
		// object A is below object B
		else if( posA.y < posB.y )
		{
			// if the top side of object A
			// penetrates the bottom side of object B
			// then we have definite collision
			if( (posA.y + (fHeightA / 2)) > (posB.y - (fHeightB / 2)) )
			{
				return true;
			}
		}
		// object A and B have the same Y-axis coordinate
		else if( posA.y == posB.y )
		{
				return true;
		}
	}

	return false;
}

bool CTheGame::IsMeshCollision(I3DObject* pObject1, I3DObject* pObject2, bool bInverseMatrix, bool bDepth)
{
	pObject1->UpdateCollisionMesh(bInverseMatrix);
	pObject2->UpdateCollisionMesh(bInverseMatrix);

	return pObject1->IsMeshCollision(pObject2->GetCollisionMesh(), bDepth);
}

HRESULT CTheGame::CreateCollisionMeshBoss()
{
	HRESULT hres = S_OK;

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
	case 2:
	case 3:

		hres = this->m_pEnemyBoss1Frame->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}
		hres = this->m_pEnemyBoss1LaserLeft->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}
		hres = this->m_pEnemyBoss1LaserRight->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}
		hres = this->m_pEnemyBoss1ScatterLeft->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}
		hres = this->m_pEnemyBoss1ScatterRight->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}
		hres = this->m_pEnemyBoss1Cannon->CreateCollisionMesh();
		if( FAILED(hres) )
		{
			return hres;
		}

		break;
	}

	return hres;
}

HRESULT CTheGame::CreateCollisionMeshEnemies()
{
	HRESULT hres = S_OK;

	switch (this->m_iTemplateShipCollisionMeshStep)
	{
	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_DRONE:

		for (int i = 0; i < this->m_vTemplateEnemyDroneLaunch.size(); i++)
		{
			hres = this->m_vTemplateEnemyDroneLaunch[i]->CreateCollisionMesh();
		}
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_SNIPER:

		for (int i = 0; i < this->m_vTemplateEnemySniperLaunch.size(); i++)
		{
			hres = this->m_vTemplateEnemySniperLaunch[i]->CreateCollisionMesh();
		}
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_ROLLER:

		for (int i = 0; i < this->m_vTemplateEnemyRollerLaunch.size(); i++)
		{
			hres = this->m_vTemplateEnemyRollerLaunch[i]->CreateCollisionMesh();
		}
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_LAUNCH_GUARD:
		/*
		for (int i = 0; i < this->m_vTemplateEnemyGuardLaunch.size(); i++)
		{
			hres = this->m_vTemplateEnemyGuardLaunch[i]->CreateCollisionMesh();
		}
		*/
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_DRONE:
		hres = this->m_pEnemyDroneStrike->CreateCollisionMesh();
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_SNIPER:
		hres = this->m_pEnemySniperStrike->CreateCollisionMesh();
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_ROLLER:
		hres = this->m_pEnemyRollerStrike->CreateCollisionMesh();
		break;

	case LOAD_TEMPLATE_SHIP_COLLISION_MESH_STRIKE_GUARD:
		//hres = this->m_pEnemyGuardStrike->CreateCollisionMesh();
		break;
	}

	return hres;
}

void CTheGame::CreateCollisionMeshEnemies(IEnemy* pEnemy)
{
	switch (pEnemy->GetType())
	{
	case IEnemy::eTYPE_DRONE:

		switch (pEnemy->GetBehaviour())
		{
		case IEnemy::eBEHAVIOUR_LAUNCH:
			pEnemy->SetCollisionMesh(m_vTemplateEnemyDroneLaunch[0]->GetCollisionMesh());
			break;

		case IEnemy::eBEHAVIOUR_STRIKE:
			pEnemy->SetCollisionMesh(this->m_pEnemyDroneStrike->GetCollisionMesh());
			break;
		}

		break;

	case IEnemy::eTYPE_SNIPER:

		switch (pEnemy->GetBehaviour())
		{
		case IEnemy::eBEHAVIOUR_LAUNCH:
			pEnemy->SetCollisionMesh(m_vTemplateEnemySniperLaunch[0]->GetCollisionMesh());
			break;

		case IEnemy::eBEHAVIOUR_STRIKE:
			pEnemy->SetCollisionMesh(this->m_pEnemySniperStrike->GetCollisionMesh());
			break;
		}

		break;

	case IEnemy::eTYPE_ROLLER:

		switch (pEnemy->GetBehaviour())
		{
		case IEnemy::eBEHAVIOUR_LAUNCH:
			pEnemy->SetCollisionMesh(this->m_vTemplateEnemyRollerLaunch[0]->GetCollisionMesh());
			break;

		case IEnemy::eBEHAVIOUR_STRIKE:
			pEnemy->SetCollisionMesh(this->m_pEnemyRollerStrike->GetCollisionMesh());
			break;
		}

		break;

	case IEnemy::eTYPE_GUARD:
		/*
		switch(pEnemy->GetBehaviour())
		{
		case IEnemy::eBEHAVIOUR_LAUNCH:
			pEnemy->SetCollisionMesh(this->m_vTemplateEnemyGuardLaunch[0]->GetCollisionMesh());
			break;

		case IEnemy::eBEHAVIOUR_STRIKE:
			pEnemy->SetCollisionMesh(this->m_pEnemyGuardStrike->GetCollisionMesh());
			break;
		}
		*/
		break;
	}
}

HRESULT CTheGame::CreateCollisionMeshWeapons()
{
	HRESULT hres = S_OK;

	switch(this->m_iTemplateWeaponCollisionMeshStep)
	{
	case LOAD_TEMPLATE_WEAPON_COLLISION_MESH_PLAYER_FRONT:

		hres = this->m_pWeaponPlayerFront->GetBulletLeft()->CreateCollisionMesh();

		if (FAILED(hres))
		{
			return hres;
		}

		hres = this->m_pWeaponPlayerFront->GetBulletRight()->CreateCollisionMesh();

		break;

	case LOAD_TEMPLATE_WEAPON_COLLISION_MESH_PLAYER_DIAGONAL:

		hres = this->m_pWeaponPlayerDiagonal->GetBulletLeft()->CreateCollisionMesh();

		if (FAILED(hres))
		{
			return hres;
		}

		hres = this->m_pWeaponPlayerDiagonal->GetBulletRight()->CreateCollisionMesh();

		break;

	case LOAD_TEMPLATE_WEAPON_COLLISION_MESH_DRONE:

		hres = this->m_pWeaponDrone->CreateCollisionMesh();
		
		break;

	case LOAD_TEMPLATE_WEAPON_COLLISION_MESH_SNIPER:
		
		hres = this->m_pWeaponSniper->CreateCollisionMesh();

		break;
	}

	return hres;
}

void CTheGame::CreateCollisionMeshWeapons(CWeapon* pWeapon)
{
	switch(pWeapon->GetBulletType())
	{
	case CWeapon::eBULLET_TYPE_ENEMY_DRONE:

		pWeapon->SetCollisionMesh(this->m_pWeaponDrone->GetCollisionMesh());

		break;

	case CWeapon::eBULLET_TYPE_ENEMY_SNIPER:

		pWeapon->SetCollisionMesh(this->m_pWeaponSniper->GetCollisionMesh());

		break;
	}
}

HRESULT CTheGame::CreateCollisionMeshObstacles()
{
	HRESULT hres = S_OK;

	switch(this->m_pLevel->GetLevelNumber())
	{
	case 1:
		break;

	case 2:
	case 3:

		switch(this->m_iLoadLevelAsteroidCollisionMeshStep)
		{
		case LOAD_LEVEL_ASTEROID_BIG:
		
			for (int i = 0; i < this->m_vTemplateAsteroidBig.size(); i++)
			{
				hres = this->m_vTemplateAsteroidBig[i]->CreateCollisionMesh();
			}
			break;

		case LOAD_LEVEL_ASTEROID_MEDIUM:

			for (int i = 0; i < this->m_vTemplateAsteroidMedium.size(); i++)
			{
				hres = this->m_vTemplateAsteroidMedium[i]->CreateCollisionMesh();
			}
			break;

		case LOAD_LEVEL_ASTEROID_SMALL:

			for (int i = 0; i < this->m_vTemplateAsteroidSmall.size(); i++)
			{
				hres = this->m_vTemplateAsteroidSmall[i]->CreateCollisionMesh();
			}
			break;
		}

		if( FAILED(hres) )
		{
			return hres;
		}

		this->m_iLoadLevelAsteroidCollisionMeshStep++;

		break;
	}

	return hres;
}

void CTheGame::CreateCollisionMeshObstacles(CObstacle* pObstacle)
{
	switch(pObstacle->GetType())
	{
	case CObstacle::eTYPE_ASTEROID_BIG_1:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidBig[0]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_BIG_2:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidBig[1]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_BIG_3:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidBig[2]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_BIG_4:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidBig[3]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_BIG_5:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidBig[4]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_MEDIUM_1:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidMedium[0]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_MEDIUM_2:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidMedium[1]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_MEDIUM_3:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidMedium[2]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_MEDIUM_4:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidMedium[3]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_MEDIUM_5:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidMedium[4]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_SMALL_1:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidSmall[0]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_SMALL_2:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidSmall[1]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_SMALL_3:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidSmall[2]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_SMALL_4:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidSmall[3]->GetCollisionMesh());
		break;

	case CObstacle::eTYPE_ASTEROID_SMALL_5:
		pObstacle->SetCollisionMesh(this->m_vTemplateAsteroidSmall[4]->GetCollisionMesh());
		break;
	}
}

void CTheGame::ShowText(LPCTSTR text, int x, int y)
{
	//this->m_pTheApp->BeginText();
	//this->m_pTheApp->DrawText(x, y, text, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//this->m_pTheApp->EndText();
}

#ifdef SHADOWS
HRESULT CTheGame::BuildShadowVolumes()
{
	HRESULT hres = S_OK;

	if( this->m_pShadowVolumes )
	{
		delete [] this->m_pShadowVolumes;
		this->m_pShadowVolumes = NULL;
	}

	D3DXMATRIX matrix;
	D3DXVECTOR3 vecLight;

	int iLightCount = this->m_pState->GetLights()->GetLightCount();
	int* iLightIndex = this->m_pState->GetLights()->GetLightIndex();
	int iMeshCount = 0;

	// each shadow casting mesh will be processed with each light source
	// so we have (lights * meshes) number of shadow volumes

	// shadow casting meshes include:
	// player ship, active enemies, 
	// arriving reinforcements and obstacles

	// player ship
	iMeshCount++;

	// count active enemies
	this->m_pActiveEnemies.SetFirst();
	while( this->m_pActiveEnemies.GetCurrent() )
	{
		if( this->m_pActiveEnemies.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pActiveEnemies.SetNext();
	}
	// count arriving enemy reinforcements
	this->m_pReinforcementEnemies.SetFirst();
	while( this->m_pReinforcementEnemies.GetCurrent() )
	{
		if( this->m_pReinforcementEnemies.GetCurrent()->IsActive() )
		{
			if(this->m_pReinforcementEnemies.GetCurrent()->GetReinforcementAction()
				== IEnemy::eREINFORCEMENT_ACTION_ARRIVE)
			{
				iMeshCount++;
			}
		}
		this->m_pReinforcementEnemies.SetNext();
	}

	// count depth 1 obstacles
	this->m_pObstaclesDepth1.SetFirst();
	while( this->m_pObstaclesDepth1.GetCurrent() )
	{
		if( this->m_pObstaclesDepth1.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pObstaclesDepth1.SetNext();
	}
	// count depth 2 obstacles
	this->m_pObstaclesDepth2.SetFirst();
	while( this->m_pObstaclesDepth2.GetCurrent() )
	{
		if( this->m_pObstaclesDepth2.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pObstaclesDepth2.SetNext();
	}
	// count depth 3 obstacles
	this->m_pObstaclesDepth3.SetFirst();
	while( this->m_pObstaclesDepth3.GetCurrent() )
	{
		if( this->m_pObstaclesDepth3.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pObstaclesDepth3.SetNext();
	}
	// count depth 4 obstacles
	this->m_pObstaclesDepth4.SetFirst();
	while( this->m_pObstaclesDepth4.GetCurrent() )
	{
		if( this->m_pObstaclesDepth4.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pObstaclesDepth4.SetNext();
	}
	// count depth 5 obstacles
	this->m_pObstaclesDepth5.SetFirst();
	while( this->m_pObstaclesDepth5.GetCurrent() )
	{
		if( this->m_pObstaclesDepth5.GetCurrent()->IsActive() )
		{
			iMeshCount++;
		}
		this->m_pObstaclesDepth5.SetNext();
	}
	
	
	this->m_pShadowVolumes = new CShadowVolume[iLightCount * iMeshCount];

	int iShadowVolumeIndex = 0;

	// process all the active light sources
	// for each object we transform the light into model space
	for(int i = 0; i < iLightCount; i++)
	{
		D3DLIGHT9 light;

		// get the current light
		this->m_pTheApp->GetDevice()->GetLight(iLightIndex[i], &light);

		// light source is point-type
		if ( light.Type == D3DLIGHT_POINT )
		{
			/* player ship */

			D3DXMatrixInverse( &matrix, NULL, &this->m_pPlayer->GetWorldMatrix() );

			//multiply the lights position, to go from world->model space
			vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
			vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
			vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

			this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
			this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pPlayer->GetWorldMatrix());

			hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pPlayer->GetMesh(), vecLight );
			if(FAILED(hres))
			{
				return hres;
			}

			iShadowVolumeIndex++;

			/* active enemies */

			this->m_pActiveEnemies.SetFirst();
			while( this->m_pActiveEnemies.GetCurrent() )
			{
				if( this->m_pActiveEnemies.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pActiveEnemies.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pActiveEnemies.SetNext();
			}

			/* arriving enemy reinforcements */

			this->m_pReinforcementEnemies.SetFirst();
			while( this->m_pReinforcementEnemies.GetCurrent() )
			{
				if( this->m_pReinforcementEnemies.GetCurrent()->IsActive() )
				{
					if(this->m_pReinforcementEnemies.GetCurrent()->GetReinforcementAction()
						== IEnemy::eREINFORCEMENT_ACTION_ARRIVE)
					{
						I3DObject* pObject = this->m_pReinforcementEnemies.GetCurrent();

						D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

						//multiply the lights position, to go from world->model space
						vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
						vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
						vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

						this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
						this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

						hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
						if(FAILED(hres))
						{
							return hres;
						}

						iShadowVolumeIndex++;
					}
				}
				this->m_pReinforcementEnemies.SetNext();
			}

			/* depth 1 obstacles */

			this->m_pObstaclesDepth1.SetFirst();
			while( this->m_pObstaclesDepth1.GetCurrent() )
			{
				if( this->m_pObstaclesDepth1.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pObstaclesDepth1.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pObstaclesDepth1.SetNext();
			}

			/* depth 2 obstacles */

			this->m_pObstaclesDepth2.SetFirst();
			while( this->m_pObstaclesDepth2.GetCurrent() )
			{
				if( this->m_pObstaclesDepth2.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pObstaclesDepth2.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pObstaclesDepth2.SetNext();
			}

			/* depth 3 obstacles */

			this->m_pObstaclesDepth3.SetFirst();
			while( this->m_pObstaclesDepth3.GetCurrent() )
			{
				if( this->m_pObstaclesDepth3.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pObstaclesDepth3.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pObstaclesDepth3.SetNext();
			}

			/* depth 4 obstacles */

			this->m_pObstaclesDepth4.SetFirst();
			while( this->m_pObstaclesDepth4.GetCurrent() )
			{
				if( this->m_pObstaclesDepth4.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pObstaclesDepth4.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pObstaclesDepth4.SetNext();
			}

			/* depth 5 obstacles */

			this->m_pObstaclesDepth5.SetFirst();
			while( this->m_pObstaclesDepth5.GetCurrent() )
			{
				if( this->m_pObstaclesDepth5.GetCurrent()->IsActive() )
				{
					I3DObject* pObject = this->m_pObstaclesDepth5.GetCurrent();

					D3DXMatrixInverse( &matrix, NULL, &pObject->GetWorldMatrix() );

					//multiply the lights position, to go from world->model space
					vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
					vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
					vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

					this->m_pShadowVolumes[iShadowVolumeIndex].Reset();
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(pObject->GetWorldMatrix());

					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(pObject->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					iShadowVolumeIndex++;
				}
				this->m_pObstaclesDepth5.SetNext();
			}
		}
	}

	this->m_pState->SetShadowCount(iShadowVolumeIndex);

	delete [] iLightIndex;
	iLightIndex = NULL;

	return hres;
}
#endif
