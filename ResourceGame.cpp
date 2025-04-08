#include "TheApp.h"
#include "TextUtils.h"
#include "ResourceGame.h"

CResourceGame::CResourceGame()
{
	this->m_bZipFileStepLoaded = false;
	this->m_bipFileStepWaited = false;
	this->m_bGameAsteroidsLoaded = false;
	this->m_bGameBossesLoaded = false;
	this->m_bGameBulletsLoaded = false;
	this->m_bGameEnemiesLoaded = false;
	this->m_bGamePlayerLoaded = false;
	this->m_bGameTextLoaded = false;

	this->m_fDepthGameAfterburn = 0.2f;
	this->m_fDepthGamePlayerCannon = 0.2f;
	this->m_fDepthGamePlayerBlast = 0.2f;
	this->m_fDepthGameBoss1Cannon = 0.2f;
	this->m_fDepthGameBullets = 0.7f;
	this->m_fDepthGameExplosion = 0.2f;
	this->m_fDepthGameInfo = 0.1f;
}

void CResourceGame::Init(CTheApp* pApp, CZipManager* pZipManager)
{
	CResources::Init(pApp, pZipManager);

	this->m_iMeshStepsMax += MESH_GAME_ASTEROIDS + MESH_GAME_BOSSES +
		MESH_GAME_BULLETS + MESH_GAME_ENEMIES + MESH_GAME_PLAYER + MESH_GAME_TEXT;

	this->m_iSpriteStepsMax += SPRITE_GAME;
}

void CResourceGame::Release(void)
{
	// SPRITES

	// level title
	if (this->m_pSpriteLevelTitleSpace)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_LEVEL_TITLE; i++)
		{
			(this->m_pSpriteLevelTitleSpace + i)->Release();
		}
		delete[] this->m_pSpriteLevelTitleSpace;
		this->m_pSpriteLevelTitleSpace = NULL;
	}

	// boss warning
	if (this->m_pSpriteBossWarningSpace)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_BOSS_WARNING; i++)
		{
			(this->m_pSpriteBossWarningSpace + i)->Release();
		}
		delete[] this->m_pSpriteBossWarningSpace;
		this->m_pSpriteBossWarningSpace = NULL;
	}

	// player afterburn
	if (this->m_pSpriteGamePlayerAfterburn)
	{
		this->m_pSpriteGamePlayerAfterburn->Release();
		delete this->m_pSpriteGamePlayerAfterburn;
		this->m_pSpriteGamePlayerAfterburn = NULL;
	}

	// player cannon

	if (this->m_pSpritePlayerCannonChargeSmall)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_CHARGE_SMALL; i++)
		{
			(this->m_pSpritePlayerCannonChargeSmall + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonChargeSmall;
		this->m_pSpritePlayerCannonChargeSmall = NULL;
	}

	if (this->m_pSpritePlayerCannonChargeMedium)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_CHARGE_MEDIUM; i++)
		{
			(this->m_pSpritePlayerCannonChargeMedium + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonChargeMedium;
		this->m_pSpritePlayerCannonChargeMedium = NULL;
	}

	if (this->m_pSpritePlayerCannonChargeLarge)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_CHARGE_LARGE; i++)
		{
			(this->m_pSpritePlayerCannonChargeLarge + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonChargeLarge;
		this->m_pSpritePlayerCannonChargeLarge = NULL;
	}

	if (this->m_pSpritePlayerCannonBeamCenter)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_BEAM_CENTER; i++)
		{
			(this->m_pSpritePlayerCannonBeamCenter + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonBeamCenter;
		this->m_pSpritePlayerCannonBeamCenter = NULL;
	}

	if (this->m_pSpritePlayerCannonBeamLeft)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_BEAM_LEFT; i++)
		{
			(this->m_pSpritePlayerCannonBeamLeft + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonBeamLeft;
		this->m_pSpritePlayerCannonBeamLeft = NULL;
	}

	if (this->m_pSpritePlayerCannonBeamRight)
	{
		for (unsigned int i = 0; i < SPRITE_GAME_PLAYER_CANNON_BEAM_RIGHT; i++)
		{
			(this->m_pSpritePlayerCannonBeamRight + i)->Release();
		}
		delete[] this->m_pSpritePlayerCannonBeamRight;
		this->m_pSpritePlayerCannonBeamRight = NULL;
	}

	// player blast
	if (this->m_pSpritePlayerBlast)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_PLAYER_BLAST; i++)
		{
			(this->m_pSpritePlayerBlast + i)->Release();
		}
		delete[] this->m_pSpritePlayerBlast;
		this->m_pSpritePlayerBlast = NULL;
	}

	// enemy afterburn
	if (this->m_pSpriteEnemyAfterburn)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_ENEMY_AFTERBURN; i++)
		{
			(this->m_pSpriteEnemyAfterburn + i)->Release();
		}
		delete[] this->m_pSpriteEnemyAfterburn;
		this->m_pSpriteEnemyAfterburn = NULL;
	}

	// boss specific sprites

	if (this->m_pSpriteBoss1CannonCharge)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_BOSS_1_CANNON_CHARGE; i++)
		{
			(this->m_pSpriteBoss1CannonCharge + i)->Release();
		}
		delete[] this->m_pSpriteBoss1CannonCharge;
		this->m_pSpriteBoss1CannonCharge = NULL;
	}
	if (this->m_pSpriteBoss1CannonShoot)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_BOSS_1_CANNON_SHOOT; i++)
		{
			(this->m_pSpriteBoss1CannonShoot + i)->Release();
		}
		delete[] this->m_pSpriteBoss1CannonShoot;
		this->m_pSpriteBoss1CannonShoot = NULL;
	}

	// Explosions

	// player explosion
	if (this->m_pSpriteExplosionPlayer)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_PLAYER; i++)
		{
			(this->m_pSpriteExplosionPlayer + i)->Release();
		}
		delete[] this->m_pSpriteExplosionPlayer;
		this->m_pSpriteExplosionPlayer = NULL;
	}
	// drone explosion
	if (this->m_pSpriteExplosionDrone)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_DRONE; i++)
		{
			(this->m_pSpriteExplosionDrone + i)->Release();
		}
		delete[] this->m_pSpriteExplosionDrone;
		this->m_pSpriteExplosionDrone = NULL;
	}
	// sniper explosion
	if (this->m_pSpriteExplosionSniper)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_SNIPER; i++)
		{
			(this->m_pSpriteExplosionSniper + i)->Release();
		}
		delete[] this->m_pSpriteExplosionSniper;
		this->m_pSpriteExplosionSniper = NULL;
	}
	// roller explosion
	if (this->m_pSpriteExplosionRoller)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_ROLLER; i++)
		{
			(this->m_pSpriteExplosionRoller + i)->Release();
		}
		delete[] this->m_pSpriteExplosionRoller;
		this->m_pSpriteExplosionRoller = NULL;
	}
	// guard explosion
	if (this->m_pSpriteExplosionGuard)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_GUARD; i++)
		{
			(this->m_pSpriteExplosionGuard + i)->Release();
		}
		delete[] this->m_pSpriteExplosionGuard;
		this->m_pSpriteExplosionGuard = NULL;
	}
	// boss explosion, big
	if (this->m_pSpriteExplosionBossBig)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_BIG; i++)
		{
			(this->m_pSpriteExplosionBossBig + i)->Release();
		}
		delete[] this->m_pSpriteExplosionBossBig;
		this->m_pSpriteExplosionBossBig = NULL;
	}
	// boss explosion, part
	if (this->m_pSpriteExplosionBossPart)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_PART; i++)
		{
			(this->m_pSpriteExplosionBossPart + i)->Release();
		}
		delete[] this->m_pSpriteExplosionBossPart;
		this->m_pSpriteExplosionBossPart = NULL;
	}
	// boss explosion, chains
	if (this->m_pSpriteExplosionBossChain1)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_1; i++)
		{
			(this->m_pSpriteExplosionBossChain1 + i)->Release();
		}
		delete[] this->m_pSpriteExplosionBossChain1;
		this->m_pSpriteExplosionBossChain1 = NULL;
	}
	if (this->m_pSpriteExplosionBossChain2)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_2; i++)
		{
			(this->m_pSpriteExplosionBossChain2 + i)->Release();
		}
		delete[] this->m_pSpriteExplosionBossChain2;
		this->m_pSpriteExplosionBossChain2 = NULL;
	}
	if (this->m_pSpriteExplosionBossChain3)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_3; i++)
		{
			(this->m_pSpriteExplosionBossChain3 + i)->Release();
		}
		delete[] this->m_pSpriteExplosionBossChain3;
		this->m_pSpriteExplosionBossChain3 = NULL;
	}

	// Game info

	// player lives
	if (this->m_pSpriteInfoPlayerLives)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_INFO_PLAYER_LIVES; i++)
		{
			(this->m_pSpriteInfoPlayerLives + i)->Release();
		}
		delete[] this->m_pSpriteInfoPlayerLives;
		this->m_pSpriteInfoPlayerLives = NULL;
	}
	// player blasts
	if (this->m_pSpriteInfoPlayerBlasts)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_INFO_PLAYER_BLASTS; i++)
		{
			(this->m_pSpriteInfoPlayerBlasts + i)->Release();
		}
		delete[] this->m_pSpriteInfoPlayerBlasts;
		this->m_pSpriteInfoPlayerBlasts = NULL;
	}
	// player health
	if (this->m_pSpriteInfoPlayerHealth)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_INFO_PLAYER_HEALTH; i++)
		{
			(this->m_pSpriteInfoPlayerHealth + i)->Release();
		}
		delete[] this->m_pSpriteInfoPlayerHealth;
		this->m_pSpriteInfoPlayerHealth = NULL;
	}
	// player cannon
	if (this->m_pSpriteInfoPlayerCannon)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_INFO_PLAYER_CANNON; i++)
		{
			(this->m_pSpriteInfoPlayerCannon + i)->Release();
		}
		delete[] this->m_pSpriteInfoPlayerCannon;
		this->m_pSpriteInfoPlayerCannon = NULL;
	}

	// game endings

	if (this->m_pSpriteGameOverText)
	{
		this->m_pSpriteGameOverText->Release();
		delete this->m_pSpriteGameOverText;
		this->m_pSpriteGameOverText = NULL;
	}
	if (this->m_pSpriteGameWonText)
	{
		for (unsigned int i = 0; i < RESOURCES_SPRITE_GAME_WIN_TITLE; i++)
		{
			(this->m_pSpriteGameWonText + i)->Release();
		}
		delete[] this->m_pSpriteGameWonText;
		this->m_pSpriteGameWonText = NULL;
	}

	// PARENT CLASS

	CResources::Release();
}

HRESULT CResourceGame::Load()
{
	if (this->m_bResourcesLoaded)
	{
		return S_OK;
	}

	HRESULT hres = S_OK;
	this->m_iResourcesLoadStepCounter++;

	if (this->m_iResourcesLoadStepCounter >= LOAD_STEPS_WAIT_GAME)
	{
		this->m_bIsLoadWaitCycle = true;
		this->m_iResourcesLoadStepCounter = 0;
	}

	// unpacking master zip file
	if (!this->m_bZipFileStepLoaded)
	{
		if (!this->m_pZipManager->IsExistResourceFolder("models/game") ||
			!this->m_pZipManager->IsExistResourceFolder("textures/game"))
		{
			this->m_pZipManager->UnpackMasterZipFileWithTarget("data_2", "data4");
			this->m_pZipManager->UnpackChildZipFile("data4");
		}

		this->m_bZipFileStepLoaded = true;
		this->m_bIsLoadWaitCycle = true;

		return hres;
	}

	// unpacking child zip file
	if (!this->m_bipFileStepWaited)
	{
		this->m_bipFileStepWaited = true;
		this->m_iResourcesLoadStepCounter = 0;

		return hres;
	}

	// load game meshes
	if (!m_bGameAsteroidsLoaded)
	{
		hres = this->LoadMeshGameAsteroids();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_ASTEROIDS)
		{
			m_bGameAsteroidsLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!m_bGameBossesLoaded)
	{
		hres = this->LoadMeshGameBosses();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_BOSSES)
		{
			m_bGameBossesLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!m_bGameBulletsLoaded)
	{
		hres = this->LoadMeshGameBullets();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_BULLETS)
		{
			m_bGameBulletsLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!m_bGameEnemiesLoaded)
	{
		hres = this->LoadMeshGameEnemies();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_ENEMIES)
		{
			m_bGameEnemiesLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!m_bGamePlayerLoaded)
	{
		hres = this->LoadMeshGamePlayer();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_PLAYER)
		{
			m_bGamePlayerLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!m_bGameTextLoaded)
	{
		hres = this->LoadMeshGameText();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_GAME_TEXT)
		{
			m_bGameTextLoaded = true;

			// forcing visual update of loading screen
			this->m_bIsLoadWaitCycle = true;
			this->m_iResourcesLoadStepCounter = 0;
		}
	}
	// load game sprites
	else if (this->m_iSpriteSteps <= this->m_iSpriteStepsMax)
	{
		// forcing visual update of loading screen
		if (this->m_iSpriteSteps == 1)
		{
			this->m_bIsLoadWaitCycle = true;
			this->m_iResourcesLoadStepCounter = 0;
		}

		hres = this->LoadSpriteGame();
		this->m_iSpriteSteps++;

		if (this->m_iSpriteSteps > this->m_iSpriteStepsMax)
		{
			this->m_bResourcesLoaded = true;
		}
	}
	else
	{
		this->m_bResourcesLoaded = true;
	}

	if (hres != S_OK)
	{
		std::string debug = "debug";
	}

	return hres;
}

HRESULT CResourceGame::LoadMeshGameAsteroids()
{
	CXFileContainer xFile;

	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	// BIG

	case 1:

		hres = xFile.Create(this->m_pDevice, "asteroid_big_1.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_big_1.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_BIG_1, MODEL_TYPE_ASTEROID);
		}

		break;

	case 2:

		hres = xFile.Create(this->m_pDevice, "asteroid_big_2.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_big_2.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_BIG_2, MODEL_TYPE_ASTEROID);
		}

		break;

	case 3:

		hres = xFile.Create(this->m_pDevice, "asteroid_big_3.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_big_3.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_BIG_3, MODEL_TYPE_ASTEROID);
		}

		break;

	case 4:

		hres = xFile.Create(this->m_pDevice, "asteroid_big_4.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_big_4.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_BIG_4, MODEL_TYPE_ASTEROID);
		}

		break;

	case 5:

		hres = xFile.Create(this->m_pDevice, "asteroid_big_5.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_big_5.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_BIG_5, MODEL_TYPE_ASTEROID);
		}

		break;

	// MEDIUM

	case 6:

		hres = xFile.Create(this->m_pDevice, "asteroid_medium_1.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_medium_1.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_MEDIUM_1, MODEL_TYPE_ASTEROID);
		}

		break;

	case 7:

		hres = xFile.Create(this->m_pDevice, "asteroid_medium_2.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_medium_2.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_MEDIUM_2, MODEL_TYPE_ASTEROID);
		}

		break;

	case 8:

		hres = xFile.Create(this->m_pDevice, "asteroid_medium_3.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_medium_3.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_MEDIUM_3, MODEL_TYPE_ASTEROID);
		}

		break;

	case 9:

		hres = xFile.Create(this->m_pDevice, "asteroid_medium_4.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_medium_4.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_MEDIUM_4, MODEL_TYPE_ASTEROID);
		}

		break;

	case 10:

		hres = xFile.Create(this->m_pDevice, "asteroid_medium_5.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_medium_5.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_MEDIUM_5, MODEL_TYPE_ASTEROID);
		}

		break;

	// SMALL

	case 11:

		hres = xFile.Create(this->m_pDevice, "asteroid_small_1.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_small_1.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_SMALL_1, MODEL_TYPE_ASTEROID);
		}

		break;

	case 12:

		hres = xFile.Create(this->m_pDevice, "asteroid_small_2.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_small_2.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_SMALL_2, MODEL_TYPE_ASTEROID);
		}

		break;

	case 13:

		hres = xFile.Create(this->m_pDevice, "asteroid_small_3.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_small_3.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_SMALL_3, MODEL_TYPE_ASTEROID);
		}

		break;

	case 14:

		hres = xFile.Create(this->m_pDevice, "asteroid_small_4.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_small_4.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_SMALL_4, MODEL_TYPE_ASTEROID);
		}

		break;

	case 15:

		hres = xFile.Create(this->m_pDevice, "asteroid_small_5.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: asteroid_small_5.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ASTEROID_SMALL_5, MODEL_TYPE_ASTEROID);
		}

		break;
	};

	return hres;
}

HRESULT CResourceGame::LoadMeshGameBosses()
{
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	// Boss 1
	case 1:
		hres = LoadGameEnemyObject("boss_1_frame.x", MODEL_GAME_BOSS_1_FRAME, MODEL_TYPE_BOSS);
		break;

	case 2:
		hres = LoadGameEnemyObject("boss_1_core.x", MODEL_GAME_BOSS_1_CORE, MODEL_TYPE_BOSS);
		break;

	case 3:
		hres = LoadGameEnemyObject("boss_1_laser_left.x", MODEL_GAME_BOSS_1_LASER_LEFT, MODEL_TYPE_BOSS);
		break;

	case 4:
		hres = LoadGameEnemyObject("boss_1_laser_right.x", MODEL_GAME_BOSS_1_LASER_RIGHT, MODEL_TYPE_BOSS);
		break;

	case 5:
		hres = LoadGameEnemyObject("boss_1_scatter.x", MODEL_GAME_BOSS_1_SCATTER, MODEL_TYPE_BOSS);
		break;

	case 6:
		hres = LoadGameEnemyObject("boss_1_cannon.x", MODEL_GAME_BOSS_1_CANNON, MODEL_TYPE_BOSS);
		break;
	};

	return hres;
}

HRESULT CResourceGame::LoadMeshGameBullets()
{
	CXFileContainer xFile;

	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	// PLAYER

	case 1:
		hres = LoadGameObject("bullet_player_minigun.x", MODEL_GAME_BULLET_PLAYER_MINIGUN, MODEL_TYPE_BULLET_PLAYER);
		break;

	// ENEMIES

	case 2:
		hres = LoadGameObject("bullet_enemy_drone.x", MODEL_GAME_BULLET_DRONE, MODEL_TYPE_BULLET_DRONE);
		break;
	case 3:
		hres = LoadGameObject("bullet_enemy_sniper.x", MODEL_GAME_BULLET_SNIPER, MODEL_TYPE_BULLET_SNIPER);
		break;
	case 4:
		hres = LoadGameObject("bullet_enemy_roller.x", MODEL_GAME_BULLET_ROLLER, MODEL_TYPE_BULLET_ROLLER);
		break;
	case 5:
		//hres = LoadGameObject("bullet_enemy_vanguard.x", MODEL_GAME_BULLET_VANGUARD, MODEL_TYPE_BULLET_VANGUARD);
		break;

	// BOSSES

	case 6:
		hres = LoadGameObject("bullet_boss_1_laser.x", MODEL_GAME_BULLET_BOSS_1_LASER, MODEL_TYPE_BULLET_BOSS_1_LASER);
		break;
	case 7:
		hres = LoadGameObject("bullet_boss_1_scatter.x", MODEL_GAME_BULLET_BOSS_1_SCATTER, MODEL_TYPE_BULLET_BOSS_1_SCATTER);
		break;
	};

	return hres;
}

HRESULT CResourceGame::LoadMeshGameEnemies()
{
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	// drone
	case 1:
		hres = LoadGameEnemyObject("enemy_drone.x", MODEL_GAME_ENEMY_DRONE_1, MODEL_TYPE_ENEMY);
		break;
	case 2:
		hres = LoadGameEnemyObject("enemy_drone.x", MODEL_GAME_ENEMY_DRONE_2, MODEL_TYPE_ENEMY);
		break;
	case 3:
		hres = LoadGameEnemyObject("enemy_drone.x", MODEL_GAME_ENEMY_DRONE_3, MODEL_TYPE_ENEMY);
		break;
	case 4:
		hres = LoadGameEnemyObject("enemy_drone.x", MODEL_GAME_ENEMY_DRONE_4, MODEL_TYPE_ENEMY);
		break;
	case 5:
		hres = LoadGameEnemyObject("enemy_drone.x", MODEL_GAME_ENEMY_DRONE_5, MODEL_TYPE_ENEMY);
		break;
	// sniper
	case 6:
		hres = LoadGameEnemyObject("enemy_sniper.x", MODEL_GAME_ENEMY_SNIPER_1, MODEL_TYPE_ENEMY);
		break;
	case 7:
		hres = LoadGameEnemyObject("enemy_sniper.x", MODEL_GAME_ENEMY_SNIPER_2, MODEL_TYPE_ENEMY);
		break;
	case 8:
		hres = LoadGameEnemyObject("enemy_sniper.x", MODEL_GAME_ENEMY_SNIPER_3, MODEL_TYPE_ENEMY);
		break;
	case 9:
		hres = LoadGameEnemyObject("enemy_sniper.x", MODEL_GAME_ENEMY_SNIPER_4, MODEL_TYPE_ENEMY);
		break;
	case 10:
		hres = LoadGameEnemyObject("enemy_sniper.x", MODEL_GAME_ENEMY_SNIPER_5, MODEL_TYPE_ENEMY);
		break;
	// roller
	case 11:
		hres = LoadGameEnemyObject("enemy_roller.x", MODEL_GAME_ENEMY_ROLLER_1, MODEL_TYPE_ENEMY);
		break;
	case 12:
		hres = LoadGameEnemyObject("enemy_roller.x", MODEL_GAME_ENEMY_ROLLER_2, MODEL_TYPE_ENEMY);
		break;
	case 13:
		hres = LoadGameEnemyObject("enemy_roller.x", MODEL_GAME_ENEMY_ROLLER_3, MODEL_TYPE_ENEMY);
		break;
	case 14:
		hres = LoadGameEnemyObject("enemy_roller.x", MODEL_GAME_ENEMY_ROLLER_4, MODEL_TYPE_ENEMY);
		break;
	case 15:
		hres = LoadGameEnemyObject("enemy_roller.x", MODEL_GAME_ENEMY_ROLLER_5, MODEL_TYPE_ENEMY);
		break;
	// vanguard
	case 16:
		//hres = LoadGameEnemyObject("enemy_vanguard.x", MODEL_GAME_ENEMY_VANGUARD_1, MODEL_TYPE_ENEMY);
		break;
	case 17:
		//hres = LoadGameEnemyObject("enemy_vanguard.x", MODEL_GAME_ENEMY_VANGUARD_2, MODEL_TYPE_ENEMY);
		break;
	case 18:
		//hres = LoadGameEnemyObject("enemy_vanguard.x", MODEL_GAME_ENEMY_VANGUARD_3, MODEL_TYPE_ENEMY);
		break;
	case 19:
		//hres = LoadGameEnemyObject("enemy_vanguard.x", MODEL_GAME_ENEMY_VANGUARD_4, MODEL_TYPE_ENEMY);
		break;
	case 20:
		//hres = LoadGameEnemyObject("enemy_vanguard.x", MODEL_GAME_ENEMY_VANGUARD_5, MODEL_TYPE_ENEMY);
		break;
	};

	return hres;
}

HRESULT CResourceGame::LoadMeshGamePlayer()
{
	CXFileContainer xFile;

	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	case 1:

		hres = xFile.Create(this->m_pDevice, "player_frame.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: player_frame.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->RotatePlayer(xFile.GetMesh());
			this->SetMeshData(xFile, MODEL_GAME_PLAYER_FRAME, MODEL_TYPE_PLAYER);
		}

		break;

	case 2:

		hres = xFile.Create(this->m_pDevice, "player_minigun.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: player_minigun.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->RotatePlayer(xFile.GetMesh());
			this->SetMeshData(xFile, MODEL_GAME_PLAYER_MINIGUN, MODEL_TYPE_PLAYER);
		}

		break;
	};

	return hres;
}

HRESULT CResourceGame::LoadMeshGameText()
{
	CXFileContainer xFile;

	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	case 1:
		hres = xFile.Create(this->m_pDevice, "text_score.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: text_score.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_TEXT_SCORE, MODEL_TYPE_TEXT);
		}
		break;
	}

	return hres;
}

HRESULT CResourceGame::LoadSpriteGame()
{
	CSprite sprite;

	char str[128] = "";
	HRESULT hres = S_OK;

	std::string sNumber;
	std::string fileName;

	int iIndex;
	int baseStep = 0;

	/* level titles */

	// text sprites

	baseStep = 1;

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_LEVEL_TITLE - 2))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteLevelTitleSpace = new CSprite[SPRITE_GAME_LEVEL_TITLE];

			if (!this->m_pSpriteLevelTitleSpace)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "level_title_space_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteLevelTitleSpace + iIndex)->Create(
			fileName, m_pDevice, 0.0f);

		return hres;
	}

	// 6 STEPS GONE

	baseStep = 7;

	// background box
	if (this->m_iSpriteSteps == baseStep)
	{
		iIndex = baseStep - 1;
		fileName = "level_title_space_box.png";

		hres = (this->m_pSpriteLevelTitleSpace + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameInfo);
		return hres;
	}

	// 7 STEPS GONE

	baseStep = 8;

	/* boss warnings */

	// space levels

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_BOSS_WARNING - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteBossWarningSpace = new CSprite[SPRITE_GAME_BOSS_WARNING];
			if (!this->m_pSpriteBossWarningSpace)
			{
				return E_OUTOFMEMORY;
			}
		}

		iIndex = this->m_iSpriteSteps - baseStep;

		switch (iIndex)
		{
		case 0:
			sNumber = TextUtils::IntToString(10);
			break;
		case 1:
			sNumber = TextUtils::IntToString(20);
			break;
		case 2:
			sNumber = TextUtils::IntToString(30);
			break;
		case 3:
			sNumber = TextUtils::IntToString(40);
			break;
		case 4:
			sNumber = TextUtils::IntToString(50);
			break;
		case 5:
			sNumber = TextUtils::IntToString(60);
			break;
		case 6:
			sNumber = TextUtils::IntToString(70);
			break;
		case 7:
			sNumber = TextUtils::IntToString(80);
			break;
		case 8:
			sNumber = TextUtils::IntToString(90);
			break;
		case 9:
			sNumber = TextUtils::IntToString(100);
			break;
		}

		fileName = "boss_alert_space_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteBossWarningSpace + iIndex)->Create(
			fileName, m_pDevice, 0.0f);

		return hres;
	}

	// 17 STEPS GONE

	baseStep = 18;

	/* afterburns */

	// player

	if (this->m_iSpriteSteps == baseStep)
	{
		this->m_pSpriteGamePlayerAfterburn = new CSprite;
		if (!this->m_pSpriteGamePlayerAfterburn)
		{
			return E_OUTOFMEMORY;
		}

		hres = m_pSpriteGamePlayerAfterburn->Create(
			"player_afterburn.png", m_pDevice, this->m_fDepthGameAfterburn);

		return hres;
	}

	// 18 STEPS GONE

	baseStep = 19;

	/* player cannon */

	// small charge

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_CHARGE_SMALL - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonChargeSmall = new CSprite[SPRITE_GAME_PLAYER_CANNON_CHARGE_SMALL];
			if (!this->m_pSpritePlayerCannonChargeSmall)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_charge_small_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonChargeSmall + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 28 STEPS GONE

	baseStep = 29;

	// medium charge

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_CHARGE_MEDIUM - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonChargeMedium = new CSprite[SPRITE_GAME_PLAYER_CANNON_CHARGE_MEDIUM];
			if (!this->m_pSpritePlayerCannonChargeMedium)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_charge_medium_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonChargeMedium + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 38 STEPS GONE

	baseStep = 39;

	// large charge

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_CHARGE_LARGE - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonChargeLarge = new CSprite[SPRITE_GAME_PLAYER_CANNON_CHARGE_LARGE];
			if (!this->m_pSpritePlayerCannonChargeLarge)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_charge_large_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonChargeLarge + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 48 STEPS GONE

	baseStep = 49;

	// center beam

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_BEAM_CENTER - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonBeamCenter = new CSprite[SPRITE_GAME_PLAYER_CANNON_BEAM_CENTER];
			if (!this->m_pSpritePlayerCannonBeamCenter)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_beam_center_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonBeamCenter + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 58 STEPS GONE

	baseStep = 59;

	// left beam

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_BEAM_LEFT - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonBeamLeft = new CSprite[SPRITE_GAME_PLAYER_CANNON_BEAM_LEFT];
			if (!this->m_pSpritePlayerCannonBeamLeft)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_beam_left_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonBeamLeft + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 68 STEPS GONE

	baseStep = 69;

	// right beam

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (SPRITE_GAME_PLAYER_CANNON_BEAM_RIGHT - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerCannonBeamRight = new CSprite[SPRITE_GAME_PLAYER_CANNON_BEAM_RIGHT];
			if (!this->m_pSpritePlayerCannonBeamRight)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "player_beam_right_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpritePlayerCannonBeamRight + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGamePlayerCannon);

		return hres;
	}

	// 78 STEPS GONE

	baseStep = 79;

	/* player blast */

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_PLAYER_BLAST - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpritePlayerBlast = new CSprite[RESOURCES_SPRITE_GAME_PLAYER_BLAST];
			if (!this->m_pSpritePlayerBlast)
			{
				return E_OUTOFMEMORY;
			}
		}

		// load individual blast sprites

		switch (this->m_iSpriteSteps)
		{
		case 79:


			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_UP].Create(
				"player_blast_n.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 80:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN].Create(
				"player_blast_s.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 81:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_LEFT].Create(
				"player_blast_w.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 82:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_RIGHT].Create(
				"player_blast_e.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 83:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_UP_LEFT].Create(
				"player_blast_nw.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 84:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_UP_RIGHT].Create(
				"player_blast_ne.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 85:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN_LEFT].Create(
				"player_blast_sw.png",m_pDevice, this->m_fDepthGamePlayerBlast);

			break;

		case 86:

			hres = this->m_pSpritePlayerBlast[LOAD_SPRITE_GAME_PLAYER_BLAST_DOWN_RIGHT].Create(
				"player_blast_se.png", m_pDevice, this->m_fDepthGamePlayerBlast);

			break;
		}

		return hres;
	}

	// 86 STEPS GONE

	baseStep = 87;

	/* enemy afterburn */

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_ENEMY_AFTERBURN - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteEnemyAfterburn = new CSprite[RESOURCES_SPRITE_GAME_ENEMY_AFTERBURN];
			if (!this->m_pSpriteEnemyAfterburn)
			{
				return E_OUTOFMEMORY;
			}
		}

		// load individual afterburn sprites

		switch (this->m_iSpriteSteps)
		{
		case 87:
			hres = this->m_pSpriteEnemyAfterburn[LOAD_SPRITE_GAME_ENEMY_AFTERBURN_DRONE].Create(
				"drone_afterburn.png", m_pDevice, this->m_fDepthGameAfterburn);
			break;
		case 88:
			hres = this->m_pSpriteEnemyAfterburn[LOAD_SPRITE_GAME_ENEMY_AFTERBURN_SNIPER].Create(
				"sniper_afterburn.png", m_pDevice, this->m_fDepthGameAfterburn);
			break;
		case 89:
			/*
			hres = this->m_pSpriteEnemyAfterburn[LOAD_SPRITE_GAME_ENEMY_AFTERBURN_ROLLER].Create(
				"roller_afterburn.png", m_pDevice, this->m_fDepthGameAfterburn);
			*/
			break;
		case 90:
			/*
			hres = this->m_pSpriteEnemyAfterburn[LOAD_SPRITE_GAME_ENEMY_AFTERBURN_GUARD].Create(
				"guard_afterburn.png", m_pDevice, this->m_fDepthGameAfterburn);
			*/
			break;
		}

		return hres;
	}

	// 90 STEPS GONE

	baseStep = 91;

	/* bosses */

	// Boss 1 cannon charge

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_BOSS_1_CANNON_CHARGE - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteBoss1CannonCharge = new CSprite[RESOURCES_SPRITE_GAME_BOSS_1_CANNON_CHARGE];
			if (!this->m_pSpriteBoss1CannonCharge)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "boss1_main_charge_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteBoss1CannonCharge + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameBoss1Cannon);

		return hres;
	}

	// 109 STEPS GONE

	baseStep = 110;

	// Boss 1 cannon beam

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_BOSS_1_CANNON_SHOOT - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteBoss1CannonShoot = new CSprite[RESOURCES_SPRITE_GAME_BOSS_1_CANNON_SHOOT];
			if (!this->m_pSpriteBoss1CannonShoot)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "boss1_main_shoot_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteBoss1CannonShoot + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameBoss1Cannon);

		return hres;
	}

	// 111 STEPS GONE

	baseStep = 112;

	/* bullets */

	// player bullets

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_BULLET_PLAYER - 1))))
	{
		switch (this->m_iSpriteSteps)
		{
		case 112:

			hres = sprite.Create(
				"bullet_player_n.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_PLAYER_MINIGUN_FRONT);
			}

			break;

		case 113:

			hres = sprite.Create(
				"bullet_player_nw.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_PLAYER_MINIGUN_LEFT);
			}

			break;

		case 114:

			hres = sprite.Create(
				"bullet_player_ne.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_PLAYER_MINIGUN_RIGHT);
			}

			break;
		}

		return hres;
	}

	// 114 STEPS GONE

	baseStep = 115;

	// enemy bullets

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_BULLET_ENEMIES - 1))))
	{
		switch (this->m_iSpriteSteps)
		{
		case 115:

			hres = sprite.Create(
				"bullet_enemy_drone.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_DRONE);
			}

			break;

		case 116:

			hres = sprite.Create(
				"bullet_enemy_sniper.png",
				m_pDevice,
				this->m_fDepthGameBullets);


			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_SNIPER);
			}

			break;

		case 117:

			hres = sprite.Create(
				"bullet_enemy_roller.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_ROLLER);
			}

			break;

		case 118:
			/*
			hres = sprite.Create(
				"bullet_enemy_guard.png",
				m_pDevice,
				this->m_fDepthGameBullets);


			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_VANGUARD);
			}
			*/
			break;
		}

		return hres;
	}

	// 118 STEPS GONE

	baseStep = 119;

	// boss 1 bullets

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_BULLET_BOSS_1 - 1))))
	{
		// load individual boss 1 bullet sprites

		switch (this->m_iSpriteSteps)
		{
		case 119:

			hres = sprite.Create(
				"bullet_boss1_laser_s.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_BOSS_1_LASER_DOWN);
			}

			break;

		case 120:

			hres = sprite.Create(
				"bullet_boss1_laser_sw.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_BOSS_1_LASER_LEFT);
			}

			break;

		case 121:

			hres = sprite.Create(
				"bullet_boss1_laser_se.png",
				m_pDevice,
				this->m_fDepthGameBullets);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_BOSS_1_LASER_RIGHT);
			}

			break;

		case 122:

			hres = sprite.Create(
				"bullet_boss1_scatter.png",
				m_pDevice,
				0.5f);

			if (hres == S_OK) {
				SetSpriteData(sprite, SPRITE_GAME_BULLET_BOSS_1_SCATTER);
			}

			break;
		}

		return hres;
	}

	// 122 STEPS GONE

	baseStep = 123;

	/* explosions */

	// player

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_PLAYER - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionPlayer = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_PLAYER];
			if (!this->m_pSpriteExplosionPlayer)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_player_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionPlayer + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 172 STEPS GONE

	baseStep = 173;

	// drone

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_DRONE - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionDrone = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_DRONE];
			if (!this->m_pSpriteExplosionDrone)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_drone_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionDrone + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 222 STEPS GONE

	baseStep = 223;

	// sniper

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_SNIPER - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionSniper = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_SNIPER];
			if (!this->m_pSpriteExplosionSniper)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_sniper_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionSniper + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 271 STEPS GONE

	baseStep = 272;

	// roller

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_ROLLER - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionRoller = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_ROLLER];
			if (!this->m_pSpriteExplosionRoller)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_roller_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionRoller + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 321 STEPS GONE

	baseStep = 322;

	// guard

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_GUARD - 1))))
	{
		/*
		if(this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionGuard = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_GUARD];
			if( !this->m_pSpriteExplosionGuard )
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_guard_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionGuard + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		*/

		return S_OK;
	}

	// 322 STEPS GONE

	baseStep = 323;

	// bosses

	// big explosion

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_BIG - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionBossBig = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_BIG];
			if (!this->m_pSpriteExplosionBossBig)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_boss1_big_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionBossBig + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 386 STEPS GONE

	baseStep = 387;

	// part explosion

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_PART - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionBossPart = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_PART];
			if (!this->m_pSpriteExplosionBossPart)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_boss1_part_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionBossPart + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 435 STEPS GONE

	baseStep = 436;

	// chain 1 explosion

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_1 - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionBossChain1 = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_1];
			if (!this->m_pSpriteExplosionBossChain1)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_boss1_chain1_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionBossChain1 + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 499 STEPS GONE

	baseStep = 500;

	// chain 2 explosion

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_2 - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionBossChain2 = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_2];
			if (!this->m_pSpriteExplosionBossChain2)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_boss1_chain2_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionBossChain2 + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 564 STEPS GONE

	baseStep = 565;

	// chain 3 explosion

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_3 - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteExplosionBossChain3 = new CSprite[RESOURCES_SPRITE_GAME_EXPLOSION_BOSS_CHAIN_3];
			if (!this->m_pSpriteExplosionBossChain3)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "explosion_boss1_chain3_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteExplosionBossChain3 + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameExplosion);

		return hres;
	}

	// 626 STEPS GONE

	baseStep = 627;

	/* game info */

	// player lives

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_INFO_PLAYER_LIVES - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteInfoPlayerLives = new CSprite[RESOURCES_SPRITE_GAME_INFO_PLAYER_LIVES];
			if (!this->m_pSpriteInfoPlayerLives)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep);
		iIndex = this->m_iSpriteSteps - baseStep;

		if (iIndex < 10)
		{
			fileName = "player_number_";
			fileName += sNumber;
			fileName += ".png";
		}
		else
		{
			fileName = "player_lives.png";
		}

		hres = (this->m_pSpriteInfoPlayerLives + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameInfo);

		return hres;
	}

	// 637 STEPS GONE

	baseStep = 638;

	// player blasts

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_INFO_PLAYER_BLASTS - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteInfoPlayerBlasts = new CSprite[RESOURCES_SPRITE_GAME_INFO_PLAYER_BLASTS];
			if (!this->m_pSpriteInfoPlayerBlasts)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep);
		iIndex = this->m_iSpriteSteps - baseStep;

		if (iIndex < 10)
		{
			fileName = "player_number_";
			fileName += sNumber;
			fileName += ".png";
		}
		else
		{
			fileName = "player_blasts.png";
		}

		hres = (this->m_pSpriteInfoPlayerBlasts + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameInfo);

		return hres;
	}

	// 648 STEPS GONE

	baseStep = 649;

	// player health

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_INFO_PLAYER_HEALTH - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteInfoPlayerHealth = new CSprite[RESOURCES_SPRITE_GAME_INFO_PLAYER_HEALTH];
			if (!this->m_pSpriteInfoPlayerHealth)
			{
				return E_OUTOFMEMORY;
			}
		}

		iIndex = this->m_iSpriteSteps - baseStep;

		switch (this->m_iSpriteSteps)
		{
		case 649:
			fileName = "player_health_1.png";
			break;
		case 650:
			fileName = "player_health_2.png";
			break;
		case 651:
			fileName = "player_health_3.png";
			break;
		case 652:
			fileName = "player_health_4.png";
			break;
		case 653:
			fileName = "player_health_unit.png";
			break;
		case 654:
			fileName = "player_health_97.png";
			break;
		case 655:
			fileName = "player_health_98.png";
			break;
		case 656:
			fileName = "player_health_99.png";
			break;
		case 657:
			fileName = "player_health_100.png";
			break;
		case 658:
			fileName = "player_health_bar.png";
			break;
		}

		hres = (this->m_pSpriteInfoPlayerHealth + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameInfo);

		return hres;
	}

	// 658 STEPS GONE

	baseStep = 659;

	// player cannon

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_INFO_PLAYER_CANNON - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteInfoPlayerCannon = new CSprite[RESOURCES_SPRITE_GAME_INFO_PLAYER_CANNON];
			if (!this->m_pSpriteInfoPlayerCannon)
			{
				return E_OUTOFMEMORY;
			}
		}

		iIndex = this->m_iSpriteSteps - baseStep;

		switch (this->m_iSpriteSteps)
		{
		case 659:
			fileName = "player_cannon_1.png";
			break;
		case 660:
			fileName = "player_cannon_2.png";
			break;
		case 661:
			fileName = "player_cannon_3.png";
			break;
		case 662:
			fileName = "player_cannon_4.png";
			break;
		case 663:
			fileName = "player_cannon_5.png";
			break;
		case 664:
			fileName = "player_cannon_6.png";
			break;
		case 665:
			fileName = "player_cannon_7.png";
			break;
		case 666:
			fileName = "player_cannon_unit.png";
			break;
		case 667:
			fileName = "player_cannon_194.png";
			break;
		case 668:
			fileName = "player_cannon_195.png";
			break;
		case 669:
			fileName = "player_cannon_196.png";
			break;
		case 670:
			fileName = "player_cannon_197.png";
			break;
		case 671:
			fileName = "player_cannon_198.png";
			break;
		case 672:
			fileName = "player_cannon_199.png";
			break;
		case 673:
			fileName = "player_cannon_200.png";
			break;
		case 674:
			fileName = "player_cannon_bar.png";
			break;
		}

		hres = (this->m_pSpriteInfoPlayerCannon + iIndex)->Create(
			fileName, m_pDevice, this->m_fDepthGameInfo);

		return hres;
	}

	// 674 STEPS GONE

	baseStep = 675;

	/* game endings */

	// game over

	if (this->m_iSpriteSteps == baseStep)
	{
		this->m_pSpriteGameOverText = new CSprite;
		if (!this->m_pSpriteGameOverText)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteGameOverText->Create(
			"game_over.png", m_pDevice, 0.0f);

		return hres;
	}

	// 675 STEPS GONE

	baseStep = 676;

	// game won

	if ((this->m_iSpriteSteps >= baseStep) &&
		(this->m_iSpriteSteps <= (baseStep + (RESOURCES_SPRITE_GAME_WIN_TITLE - 1))))
	{
		if (this->m_iSpriteSteps == baseStep)
		{
			this->m_pSpriteGameWonText = new CSprite[RESOURCES_SPRITE_GAME_WIN_TITLE];
			if (!this->m_pSpriteGameWonText)
			{
				return E_OUTOFMEMORY;
			}
		}

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - baseStep + 1);
		iIndex = this->m_iSpriteSteps - baseStep;

		fileName = "game_won_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteGameWonText + iIndex)->Create(
			fileName, m_pDevice, 0.0f);

		return hres;
	}

	// 676 STEPS GONE

	return S_OK;
}
