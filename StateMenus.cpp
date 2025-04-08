/**
 * This class implements
 * game application "menus" state.
 */

#include "TextUtils.h"
#include "StateMenus.h"

CStateMenus::CStateMenus(void)
{
	this->m_eMenus = Main;
	this->m_eInputDevice = Mouse;
	this->m_eKeyboardMenuBrowse = Main_New_Game;

	this->m_dwNextState = STATE_RUNNING;

	this->m_pShips.Clear();

#ifdef SHADOWS
	this->m_pShadowVolumes = NULL;
#endif

	this->m_pResourceMenus = NULL;
	this->m_pResourceHighScores = NULL;

	this->m_pMouse = NULL;
	this->m_pJoystick = NULL;

	this->m_pXFile = NULL;

#ifdef MENUS_PLANET
	this->m_pPlanet = NULL;
#endif

	this->m_pPlayer = NULL;
	this->m_pDrone1 = NULL;
	this->m_pDrone2 = NULL;
	this->m_pSniper1 = NULL;
	this->m_pSniper2 = NULL;
	this->m_pRoller1 = NULL;
	this->m_pRoller2 = NULL;
	this->m_pBoss1Frame = NULL;
	this->m_pBoss1ScatterLeft = NULL;
	this->m_pBoss1ScatterRight = NULL;

	this->m_pLetters = NULL;
	this->m_pNumbers = NULL;

	this->m_pSpriteCursor = NULL;

#ifdef MENUS_FOG
	this->m_pSpriteFogBack = NULL;
	this->m_pSpriteFogFront = NULL;
#endif

	this->m_pSpriteStarsFront = NULL;
	this->m_pSpriteStarsBack = NULL;
	this->m_pSpriteMenuBackground = NULL;

	this->m_pSpriteMenuTitleMain = NULL;
	this->m_pSpriteMenuTitleHighscore = NULL;

	this->m_pSpriteMenuMain = NULL;
	this->m_pSpriteMenuOptions = NULL;
	this->m_pSpriteMenuInput = NULL;
	this->m_pSpriteMenuAudio = NULL;
	this->m_pSpriteMenuDisplay = NULL;
	this->m_pSpriteMenuHighscore = NULL;

	this->m_pSpriteAudioBarBorder = NULL;
	this->m_pSpriteAudioBarMeter = NULL;
	this->m_pSpriteVideoAntialiasingBarBorder = NULL;
	this->m_pSpriteVideoAntialiasingBar2x = NULL;
	this->m_pSpriteVideoAntialiasingBar46x = NULL;
	this->m_pSpriteVideoAntialiasingBar8x = NULL;

	this->m_pSpriteArrowInput = NULL;
	this->m_pSpriteArrowAntialiasingNormalLeft = NULL;
	this->m_pSpriteArrowAntialiasingNormalRight = NULL;
	this->m_pSpriteArrowAntialiasingGlowLeft = NULL;
	this->m_pSpriteArrowAntialiasingGlowRight = NULL;
	this->m_pSpriteArrowAntialiasingHideLeft = NULL;
	this->m_pSpriteArrowAntialiasingHideRight = NULL;

	this->m_pSpriteSpecularLightingOn = NULL;
	this->m_pSpriteSpecularLightingOnGlow = NULL;
	this->m_pSpriteSpecularLightingOff = NULL;
	this->m_pSpriteSpecularLightingOffGlow = NULL;

	this->m_pSpriteMessageInputEmpty = NULL;
	this->m_pSpriteMessageInputKey = NULL;
	this->m_pSpriteMessageRestart = NULL;
	this->m_pSpriteMessageOK1 = NULL;
	this->m_pSpriteMessageOK2 = NULL;

	this->m_pSpriteUnderlineAudio = NULL;
	this->m_pSpriteUnderlineBack = NULL;
	this->m_pSpriteUnderlineDefault = NULL;
	this->m_pSpriteUnderlineExit = NULL;
	this->m_pSpriteUnderlineHighscore = NULL;
	this->m_pSpriteUnderlineInput = NULL;
	this->m_pSpriteUnderlineNewgame = NULL;
	this->m_pSpriteUnderlineOptions = NULL;
	this->m_pSpriteUnderlineDisplay = NULL;

#ifdef MENU_CREDITS
	this->m_pSpriteUnderlineCredits = NULL;

	this->m_pSpriteCreditsBackLayer = NULL;
	this->m_pSpriteCreditsText = NULL;
#endif

	this->m_pSpriteVersion = NULL;

	this->m_bFadeOutMusic = true;
	this->m_fPauseFadeOut = 0.025f;
	this->m_fPauseFadeOutLast = 0.1f;

	this->m_fLetterWidth = 7.4f;
	this->m_fNumberWidth = 7.4f;

	this->m_bMessageBoxEmpty = false;
	this->m_bMessageBoxKey = false;

	this->m_bChangeSpecularity = false;
	this->m_bDisplayChangesExit = false;

	this->m_iTextX = 0;
	this->m_iTextY = 0;
	this->m_iControlInput = 0;

	this->m_fBoxKeyTimer = 0.0f;
	this->m_fSoundBarNoiseTimer = 0.0f;

	this->m_bIsClickPause = false;

	ResetPlayerInput();
}

CStateMenus::~CStateMenus(void)
{
}

HRESULT CStateMenus::Create(CTheApp* pApp,
							DWORD dwState)
{
	HRESULT hres;

	this->m_iMeshSteps = 1;
	this->m_iSpriteSteps = 1;

	this->m_iMeshStepsMax = LOAD_MESH_MENUS_MAX;
	this->m_iSpriteStepsMax = LOAD_SPRITE_MENUS_MAX;
	this->m_iStepsMax = this->m_iMeshStepsMax + this->m_iSpriteStepsMax;

	this->m_pResourceMenus = pApp->GetResourceMenus();
	this->m_pResourceHighScores = pApp->GetResourceHighScore();

	pApp->SetLoadingScreen(false);

	// menu screen resources
	if(!this->m_pResourceMenus->IsResourcesLoaded())
	{
		// show the loading screen during this state loading
		pApp->SetLoadingScreen(true);

		this->m_iStepsMax += this->m_pResourceMenus->GetStepsMax();
		// zip file loading step (10 + 1)
		this->m_iStepsMax += 11;
	}

	// highscore screen resources
	if (!this->m_pResourceHighScores->IsResourcesLoaded())
	{
		this->m_iStepsMax += this->m_pResourceHighScores->GetStepsMax();
	}

	// menu sounds
	if (pApp->IsLoadMenuSoundFiles())
	{
		this->m_iStepsMax += 1;
	}

	this->m_pResourceMenus->SetSpriteFilePath("textures/loading/");
	hres = this->m_pResourceMenus->LoadSpriteLoadingScreen();

	if( FAILED(hres) )
	{
		return hres;
	}

	this->m_pResourceMenus->SetMeshFilePath("models/menus/");
	this->m_pResourceMenus->SetSpriteFilePath("textures/menus/");

	// remember to call base class implementation
	// to properly initialise the state.
	hres = IState::Create(pApp, dwState);

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

HRESULT CStateMenus::InitState(DWORD dwState)
{
	if (this->IsLoadWaitTimer())
	{
		return S_OK;
	}

	/** LOAD RESOURCES TO MEMORY **/

	HRESULT hres = S_OK;

	// Load menu resources from files (meshes, sprites).
	if(!this->m_pResourceMenus->IsResourcesLoaded())
	{
		while (!this->m_pResourceMenus->IsResourcesLoaded())
		{
			hres = this->m_pResourceMenus->Load();

			if (hres != S_OK)
			{
				return hres;
			}

			if (this->m_pResourceMenus->IsMasterZipFileLoaded())
			{
				this->UpdateLoadingBar(10);
			}
			else
			{
				this->UpdateLoadingBar(1);
			}

			if (this->m_pResourceMenus->IsResourcesLoaded())
			{
				this->m_pResourceHighScores->SetMeshFilePath("models/highscore/");
				this->m_pResourceHighScores->SetSpriteFilePath("textures/highscore/");
			}

			if (this->m_pResourceMenus->IsLoadWaitCycle())
			{
				this->m_pResourceMenus->SetLoadWaitCycle(false);
				this->SetLoadWaitTimer();
				return hres;
			}
		}
		
		this->SetLoadWaitTimer();
		return S_OK;
	}

	// Load highscore resources from files (meshes, sprites).
	if (!this->m_pResourceHighScores->IsResourcesLoaded())
	{
		while (!this->m_pResourceHighScores->IsResourcesLoaded())
		{
			hres = this->m_pResourceHighScores->Load();

			if (hres != S_OK)
			{
				return hres;
			}

			this->UpdateLoadingBar(1);

			if (this->m_pResourceHighScores->IsLoadWaitCycle())
			{
				this->m_pResourceHighScores->SetLoadWaitCycle(false);
				this->SetLoadWaitTimer();
				return hres;
			}
		}

		this->SetLoadWaitTimer();
		return S_OK;
	}

	// Load menu sounds.
	if (this->m_pApp->IsLoadMenuSoundFiles())
	{
		CZipManager* zipManager = this->m_pApp->GetZipManager();

		// Unpack "menu sounds" ZIP resource file.
		if (!zipManager->IsExistResourceFile("music/title.mp3") ||
			!zipManager->IsExistResourceFile("sound/menu_start.wav"))
		{
			zipManager->UnpackMasterZipFileWithTarget("data_2", "data3");
			zipManager->UnpackChildZipFile("data3");
		}

		hres = this->m_pApp->LoadSoundFiles();
		this->m_pApp->SetLoadMenuSoundFiles(false);

		if (FAILED(hres))
		{
			return hres;
		}

		this->UpdateLoadingBar(1);
		this->SetLoadWaitTimer();
		return S_OK;
	}

	// Add menu meshes into a reference array.
	if(!this->m_bMeshLoaded)
	{
		while(this->m_iMeshSteps <= this->m_iMeshStepsMax)
		{
			hres = this->LoadMeshes();

			if (hres != S_OK)
			{
				return hres;
			}

			this->UpdateLoadingBar(1);
			this->m_iMeshSteps++;
		}

		this->m_bMeshLoaded = true;
		this->SetLoadWaitTimer();
		return S_OK;
	}

	// Set sprite references.
	if(!this->m_bSpriteLoaded)
	{
		while(this->m_iSpriteSteps <= this->m_iSpriteStepsMax)
		{
			this->LoadSprites();
			this->UpdateLoadingBar(1);
			this->m_iSpriteSteps++;
		}

		this->m_bSpriteLoaded = true;
		this->SetLoadWaitTimer();
		return S_OK;
	}

	/**  LOADED NECESSARY RESOURCES **/
	// NO MORE LOADING SCREEN UPDATES //

	if (!this->m_StateInitialized)
	{
		this->m_pMouse = this->GetApp()->GetMouse();
		this->m_pJoystick = this->GetApp()->GetJoystick();

		this->m_iAntialiasingCurrent = (int)this->GetApp()->GetConfig().GetAntialiasing();

		/** HIGH SCORES **/

		this->GetApp()->GetHighScore().Load();

		if (!this->GetApp()->GetHighScore().IsEmpty())
		{
			this->GetApp()->GetHighScore().SortScores();
		}

		/** DYNAMIC LIGHTING **/

		this->m_pLights->InitMenusMain();
		this->m_pLights->SetMenusMain(true);

		/** 3D OBJECTS **/

		// container for letter meshes
		this->m_pLetters = new CLetter[DISPLAY_LETTER_COUNT_MENUS];
		if (!this->m_pLetters)
		{
			return E_OUTOFMEMORY;
		}

		for (int i = 0; i < DISPLAY_LETTER_COUNT_MENUS; i++)
		{
			hres = (this->m_pLetters + i)->Create(this->m_pXFile[i].GetMesh(),
				this->m_pXFile[i],
				this->m_fLetterWidth,
				10.0f,
				false,
				CLetter::eLETTER_TYPE_MENUS);
			if (FAILED(hres))
			{
				return hres;
			}
		}

		// container for number meshes
		this->m_pNumbers = new CNumber[DISPLAY_NUMBER_COUNT_MENUS];
		if (!this->m_pNumbers)
		{
			return E_OUTOFMEMORY;
		}

		for (int i = 0; i < DISPLAY_NUMBER_COUNT_MENUS; i++)
		{
			hres = (this->m_pNumbers + i)->Create(this->m_pXFile[i + 26].GetMesh(),
				this->m_pXFile[i + 26],
				this->m_fNumberWidth,
				10.0f,
				false,
				CNumber::eNUMBER_TYPE_MENUS);
			if (FAILED(hres))
			{
				return hres;
			}
		}

		// Planet
#ifdef MENUS_PLANET

		this->m_pPlanet = new CMenuObject();

		if (!this->m_pPlanet)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pPlanet->Create(this->GetApp(),
			this->m_pXFile[LOAD_MESH_MENUS_PLANET].GetMesh(),
			this->m_pXFile[LOAD_MESH_MENUS_PLANET],
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			0.0f,
			CMenuObject::eTYPE_PLANET,
			CMenuObject::eSHIP_NONE,
			false);

		this->m_pPlanet->Init();

		// set starting position
		this->m_pPlanet->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

#endif

		// Player ship

		this->m_pPlayer = new CMenuObject();

		if (!this->m_pPlayer)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pPlayer->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_PLAYER);

		this->m_pPlayer->Init();
		this->m_pPlayer->SetDepth(this->m_pPlayer->GetDepthValue(1));

		// Drone ships

		this->m_pDrone1 = new CMenuObject();

		if (!this->m_pDrone1)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pDrone1->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_DRONE);

		this->m_pDrone1->Init();
		this->m_pDrone1->SetDepth(this->m_pDrone1->GetDepthValue(2));

		this->m_pDrone2 = new CMenuObject();

		if (!this->m_pDrone2)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pDrone2->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_DRONE_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_DRONE);

		this->m_pDrone2->Init();
		this->m_pDrone2->SetDepth(this->m_pDrone2->GetDepthValue(3));

		// Sniper ships

		this->m_pSniper1 = new CMenuObject();

		if (!this->m_pSniper1)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pSniper1->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_SNIPER);

		this->m_pSniper1->Init();
		this->m_pSniper1->SetDepth(this->m_pSniper1->GetDepthValue(4));

		this->m_pSniper2 = new CMenuObject();

		if (!this->m_pSniper2)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pSniper2->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_SNIPER_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_SNIPER);

		this->m_pSniper2->Init();
		this->m_pSniper2->SetDepth(this->m_pSniper2->GetDepthValue(5));

		// Roller ships

		this->m_pRoller1 = new CMenuObjectRoller();

		if (!this->m_pRoller1)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pRoller1->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_ROLLER);

		this->m_pRoller1->Init();
		this->m_pRoller1->SetDepth(this->m_pRoller1->GetDepthValue(6));

		this->m_pRoller2 = new CMenuObjectRoller();

		if (!this->m_pRoller2)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pRoller2->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_ENEMY_ROLLER_1),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_ROLLER);

		this->m_pRoller2->Init();
		this->m_pRoller2->SetDepth(this->m_pRoller2->GetDepthValue(7));

		// Boss frame

		this->m_pBoss1Frame = new CMenuObject();

		if (!this->m_pBoss1Frame)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pBoss1Frame->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_BOSS_1_FRAME),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_BOSS_1_FRAME),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_BOSS_1_FRAME),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_BOSS_1);

		this->m_pBoss1Frame->Init();

		float bossDepth = this->m_pBoss1Frame->GetDepthValue(9);
		this->m_pBoss1Frame->SetDepth(bossDepth);

		// Boss scatter turret (child objects)

		this->m_pBoss1ScatterLeft = new CMenuBoss1Scatter();

		if (!this->m_pBoss1ScatterLeft)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pBoss1ScatterRight = new CMenuBoss1Scatter();

		if (!this->m_pBoss1ScatterRight)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pBoss1ScatterLeft->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_BOSS_1_SCATTER_LEFT);

		this->m_pBoss1ScatterRight->Create(this->GetApp(),
			this->m_pResourceMenus->GetMesh(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_pResourceMenus->GetMaterial(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_pResourceMenus->GetTexture(CResources::MODEL_GAME_BOSS_1_SCATTER),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_MENUS_BOSS_1_SCATTER_RIGHT);

		this->m_pBoss1ScatterLeft->Init();
		this->m_pBoss1ScatterRight->Init();

		this->m_pBoss1ScatterLeft->SetDepth(bossDepth);
		this->m_pBoss1ScatterRight->SetDepth(bossDepth);

		// add ships to queue
		this->m_pShips.Push(m_pPlayer);
		this->m_pShips.Push(m_pDrone1);
		this->m_pShips.Push(m_pDrone2);
		this->m_pShips.Push(m_pSniper1);
		this->m_pShips.Push(m_pSniper2);
		this->m_pShips.Push(m_pRoller1);
		this->m_pShips.Push(m_pRoller2);
		this->m_pShips.Push(m_pBoss1Frame);

		this->m_StateInitialized = true;
		this->SetLoadWaitTimer();
		return S_OK;
	}

	if (this->m_StateInitialized)
	{
		// load menu music
		LPCTSTR resourceFilePath = this->m_pResourceMenus->GetUnpackedResourceFilePath("music/title.mp3");
		this->GetApp()->GetMP3Player1().Create(resourceFilePath);

		// current music configuration has volume set up
		if (this->GetApp()->GetConfig().GetVolumeMusic() > 0)
		{
			// play menu music
			this->GetApp()->GetMP3Player1().SetVolume(this->GetApp()->GetVolumeMusic());
			this->GetApp()->GetMP3Player1().Play();
		}

		// updates mouse device clearing the movement
		this->m_pMouse->Update();
		// sets mouse starting position
		this->GetApp()->SetMouseX(512);
		this->GetApp()->SetMouseY(384);

		this->SetStateLoaded(true);
	}

	return S_OK;
}

void CStateMenus::Release()
{
	/* MESHES */

	this->m_pShips.Clear();

#ifdef MENUS_PLANET
	if( this->m_pPlanet )
	{
		this->m_pPlanet->Release();
		delete this->m_pPlanet;
		this->m_pPlanet = NULL;
	}
#endif

	if( this->m_pPlayer )
	{
		this->m_pPlayer->Release();
		delete this->m_pPlayer;
		this->m_pPlayer = NULL;
	}
	if( this->m_pDrone1 )
	{
		this->m_pDrone1->Release();
		delete this->m_pDrone1;
		this->m_pDrone1 = NULL;
	}
	if( this->m_pDrone2 )
	{
		this->m_pDrone2->Release();
		delete this->m_pDrone2;
		this->m_pDrone2 = NULL;
	}
	if( this->m_pSniper1 )
	{
		this->m_pSniper1->Release();
		delete this->m_pSniper1;
		this->m_pSniper1 = NULL;
	}
	if( this->m_pSniper2 )
	{
		this->m_pSniper2->Release();
		delete this->m_pSniper2;
		this->m_pSniper2 = NULL;
	}
	if( this->m_pRoller1 )
	{
		this->m_pRoller1->Release();
		delete this->m_pRoller1;
		this->m_pRoller1 = NULL;
	}
	if( this->m_pRoller2 )
	{
		this->m_pRoller2->Release();
		delete this->m_pRoller2;
		this->m_pRoller2 = NULL;
	}
	if( this->m_pBoss1Frame )
	{
		this->m_pBoss1Frame->Release();
		delete this->m_pBoss1Frame;
		this->m_pBoss1Frame = NULL;
	}
	if( this->m_pLetters )
	{
		for ( int i = 0; i < DISPLAY_LETTER_COUNT_MENUS; i++ )
		{
			(this->m_pLetters + i)->Release();
		}
		delete [] this->m_pLetters;
		this->m_pLetters = NULL;
	}
	if( this->m_pNumbers )
	{
		for ( int i = 0; i < DISPLAY_NUMBER_COUNT_MENUS; i++ )
		{
			(this->m_pNumbers + i)->Release();
		}
		delete [] this->m_pNumbers;
		this->m_pNumbers = NULL;
	}

	if( this->m_pXFile )
	{
		delete [] this->m_pXFile;
		this->m_pXFile = NULL;
	}

	/* OTHERS */

#ifdef SHADOWS
	if( this->m_pShadowVolumes )
	{
		delete [] this->m_pShadowVolumes;
		this->m_pShadowVolumes = NULL;
	}
#endif

	this->m_pJoystick = NULL;

	// remember to call base class implementation
	// to properly release the state.
	IState::Release();
}

void CStateMenus::OnKeyDown(DWORD dwKey)
{
	if (dwKey == VK_ESCAPE)
	{
		OnBackAction();
	}
	else if (dwKey == VK_RETURN)
	{
		this->m_bInputSelect = true;
		m_eInputDevice = Keyboard;
	}
	else if (dwKey == VK_LEFT)
	{
		m_bInputLeft = true;
		m_eInputDevice = Keyboard;
	}
	else if (dwKey == VK_RIGHT)
	{
		m_bInputRight = true;
		m_eInputDevice = Keyboard;
	}
	else if ((dwKey == VK_UP) || (dwKey == VK_DOWN))
	{
		OnKeyboardMenuBrowse(dwKey);
		m_eInputDevice = Keyboard;
	}
}

DWORD CStateMenus::Update(float fFrametime)
{
	IState::Update(fFrametime);

	if (!IsStateLoaded())
	{
		return S_OK;
	}

	// music has volume
	if (this->GetApp()->GetConfig().GetVolumeMusic() > 0)
	{
		// music has reached it's end, reset position 
		if (this->GetApp()->GetMP3Player1().IsAtEnd())
		{
			this->GetApp()->GetMP3Player1().Stop();
			this->GetApp()->GetMP3Player1().SetPosition(67.829);
			this->GetApp()->GetMP3Player1().Play();
		}
	}

	// if we are in input menu then update boxkey timer
	if (this->m_eMenus == Input)
	{
		this->m_fBoxKeyTimer -= fFrametime;
	}

	// next state to take
	return m_dwNextState;
}

void CStateMenus::Render()
{
	static bool bRenderShips = false;
	static int iFrameCount = 0;

	// starts rendering ships after the counter
	if(iFrameCount < 5)
	{
		iFrameCount++;
		bRenderShips = true;
	}

	float fFrametime = GetApp()->GetFrameTime();

	// build a left-handed orthographic projection matrix
	BuildProjection();

	// update mouse device
	GetApp()->UpdateMouse();

	// update joystick/keyboard controls
	UpdatePlayerInput();

	if (m_eInputDevice == Joystick)
	{
		if (m_bInputUp)
		{
			GetApp()->SetMouseY(GetApp()->GetMouseY() - MOUSE_CURSOR_SPEED);
		}
		if (m_bInputDown)
		{
			GetApp()->SetMouseY(GetApp()->GetMouseY() + MOUSE_CURSOR_SPEED);
		}
		if (m_bInputLeft)
		{
			GetApp()->SetMouseX(GetApp()->GetMouseX() - MOUSE_CURSOR_SPEED);
		}
		if (m_bInputRight)
		{
			GetApp()->SetMouseX(GetApp()->GetMouseX() + MOUSE_CURSOR_SPEED);
		}
	}

	// render background
	RenderBackground();

	// render ship objects
	if(bRenderShips)
	{
		RenderShips(fFrametime);
	}

#ifdef MENUS_PLANET
	// render planet object
	RenderPlanet();
#endif

#ifdef MENUS_FOG
	RenderFog();
#endif

	// render menu title

	if (m_eMenus == Highscore)
	{
		m_pSpriteMenuTitleHighscore->Draw(0, 0);
	}
	else
	{
		m_pSpriteMenuTitleMain->Draw(0, 0);
	}

	// render menu content

	switch(m_eMenus)
	{
	case New_Game:
		RenderNewGame(fFrametime);
		break;

	case Main:
		RenderMain();
		break;

	case Options:
		RenderOptions();
		break;

	case Input:
		RenderInput();
		break;

	case Audio:
		RenderAudio(fFrametime);
		break;

	case Display:
		RenderDisplay();
		break;

	case Highscore:
		RenderHighScore(fFrametime);
		break;

#ifdef MENU_CREDITS
	case Credits:
		RenderCredits();
		break;
#endif

	case Exit:
		RenderExit(fFrametime);
		break;
	}

	// render game version
	RenderGameVersion();

	// render mouse cursor
	if((m_eInputDevice != Keyboard) && (m_eMenus != New_Game) && (m_eMenus != Exit))
	{
		m_pSpriteCursor->Draw(GetApp()->GetMouseX(), GetApp()->GetMouseY());
	}

	ResetPlayerInput();
}

void CStateMenus::RenderNewGame(float fFrametime)
{
	bool bScreenFading = this->GetFading()->UpdateFading();

	// fade out music
	if(this->m_bFadeOutMusic)
	{
		if(this->GetApp()->VolumeMusicFadeOut(fFrametime))
		{
			// set music volume
			this->GetApp()->GetMP3Player1().SetVolume( this->GetApp()->GetVolumeMusic() );
		}
		// music fade out finished
		else
		{
			// set music volume, it's now back to original volume
			this->GetApp()->GetMP3Player1().SetVolume( this->GetApp()->GetVolumeMusic() );
			this->GetApp()->GetMP3Player2().SetVolume( this->GetApp()->GetVolumeMusic() );

			// music has volume
			if(this->GetApp()->GetConfig().GetVolumeMusic() > 0)
			{
				// music player is active
				if(this->GetApp()->GetMP3Player1().GetState() == 1)
				{
					// stop music play
					this->GetApp()->GetMP3Player1().Stop();
				}

				// release music
				this->GetApp()->GetMP3Player1().Release();
			}

			this->m_bFadeOutMusic = false;
		}
	}

	// draw menu text
	this->m_pSpriteMenuMain->Draw(0,0);
	// draw game version
	this->RenderGameVersion();
	// draw fade-out
	this->GetFading()->RenderFading();

	if(!bScreenFading && !this->m_bFadeOutMusic)
	{
		// change state
		m_dwNextState = STATE_GAME;
		// need to prepare new state
		this->SetNewState(true);
		// create state first, then initialize it
		this->GetApp()->SetCreateState(true);
	}
}

void CStateMenus::RenderMain()
{
	// mouse cursor is on top of New Game text
	if( (m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Main_New_Game) ||
		(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 394 && GetApp()->GetMouseX() < 630 &&
		this->GetApp()->GetMouseY() > 375 && GetApp()->GetMouseY() < 404) )
	{
		// draw underline
		this->m_pSpriteUnderlineNewgame->Draw(395, 414);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// play "new game" sound effect
			this->GetApp()->GetWave(SOUND_MENU_START).Play(FALSE, 0, 
				this->GetApp()->GetVolumeSoundEffect());

			this->GetFading()->SetFadeOut();
			this->GetFading()->SetDefaultFadeStep();
			//this->GetFading()->SetFadeStep(0x06000000);

			// change menu
			this->m_eMenus = New_Game;
		}
	}

	// mouse cursor is on top of Options text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Main_Options) ||
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 428 && this->GetApp()->GetMouseX() < 596 &&
			this->GetApp()->GetMouseY() > 449 && this->GetApp()->GetMouseY() < 478))
	{
		// draw underline
		this->m_pSpriteUnderlineOptions->Draw(429, 488);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Options;
			m_eKeyboardMenuBrowse = (eKEYBOARD_MENU_BROWSE)((int)eKEYBOARD_MENU_BROWSE::Options_First + 1);
		}
	}

	// mouse cursor is on top of Highscore text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Main_Highscore) ||
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 381 && this->GetApp()->GetMouseX() < 644 &&
			this->GetApp()->GetMouseY() > 522 && this->GetApp()->GetMouseY() < 552))
	{
		// draw underline
		this->m_pSpriteUnderlineHighscore->Draw(405, 562);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// change font
			this->GetApp()->SetTextFontParam(-17, 1000, 0);
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Highscore;
			m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Highscore_Back;
		}
	}

#ifdef MENU_CREDITS
	// mouse cursor is on top of Credits text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Main_Credits) || 
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 434 && this->GetApp()->GetMouseX() < 591 &&
			this->GetApp()->GetMouseY() > 546 && this->GetApp()->GetMouseY() < 577))
	{
		// draw underline
		this->m_pSpriteUnderlineCredits->Draw(434, 586);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Credits;
		}
	}
#endif

	// mouse cursor is on top of Exit text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Main_Exit) || 
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 469 && this->GetApp()->GetMouseX() < 553 &&
			this->GetApp()->GetMouseY() > 673 && this->GetApp()->GetMouseY() < 704))
	{
		// draw underline
		this->m_pSpriteUnderlineExit->Draw(470, 713);

		// select button is pressed
		if(IsValidSelectClick())
		{
			OnBackAction();
		}
	}

	// draw menu text
	this->m_pSpriteMenuMain->Draw(0,0);
}

void CStateMenus::RenderOptions()
{
	// mouse cursor is on top of Input text
	if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Options_Input) ||
		(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 456 && this->GetApp()->GetMouseX() < 568 &&
		this->GetApp()->GetMouseY() > 374 && this->GetApp()->GetMouseY() < 405))
	{
		// draw underline
		this->m_pSpriteUnderlineInput->Draw(457, 414);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// change font
			this->GetApp()->SetTextFontParam(-17, 700, 0);
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Input;
			m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Input_Back;
		}
	}

	// mouse cursor is on top of Audio text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Options_Audio) ||
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 451 && this->GetApp()->GetMouseX() < 575 &&
			this->GetApp()->GetMouseY() > 448 && this->GetApp()->GetMouseY() < 479))
	{
		// draw underline
		this->m_pSpriteUnderlineAudio->Draw(452, 488);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Audio;
			m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Audio_Back;

			m_fSoundBarNoiseTimer = 0.0f;
		}
	}

	// mouse cursor is on top of Display text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Options_Display) ||
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 432 && this->GetApp()->GetMouseX() < 591 &&
			this->GetApp()->GetMouseY() > 522 && this->GetApp()->GetMouseY() < 553))
	{
		// draw underline
		this->m_pSpriteUnderlineDisplay->Draw(433, 562);

		// select button is pressed
		if(IsValidSelectClick())
		{
			// play menu "select" sound
			this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
			// change menu
			this->m_eMenus = Display;
			m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Display_Back;
		}
	}

	// mouse cursor is on top of Back text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Options_Back) ||
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 457 && this->GetApp()->GetMouseX() < 565 &&
			this->GetApp()->GetMouseY() > 675 && this->GetApp()->GetMouseY() < 702))
	{
		// draw underline
		this->m_pSpriteUnderlineBack->Draw(458, 713);

		// select button is pressed
		if(IsValidSelectClick())
		{
			OnBackAction();
		}
	}

	// draw menu text
	this->m_pSpriteMenuOptions->Draw(0,0);
}

void CStateMenus::RenderInput()
{
	this->ShowControls();

	char* pHex = NULL;

	if(this->m_bMessageBoxEmpty)
	{
		// draw message box
		this->m_pSpriteMessageInputEmpty->Draw(432, 422);
		// draw message box OK 1 text
		this->m_pSpriteMessageOK1->Draw(496, 503);

		// mouse cursor is on top of message box OK text
		if((m_eInputDevice == eINPUT_DEVICE::Keyboard) || (m_eInputDevice != eINPUT_DEVICE::Keyboard && 
			this->GetApp()->GetMouseX() > 498 && this->GetApp()->GetMouseX() < 526 &&
			this->GetApp()->GetMouseY() > 505 && this->GetApp()->GetMouseY() < 519))
		{
			// draw message box OK 2 text
			this->m_pSpriteMessageOK2->Draw(496, 503);

			// select button is pressed
			if(IsValidSelectClick())
			{
				// play menu "option" sound
				this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

				this->m_bMessageBoxEmpty = false;
			}
		}
	}
	else
	{
		if (this->m_bMessageBoxKey)
		{
			// draw message box
			this->m_pSpriteMessageInputKey->Draw(432, 450);

			if (this->m_fBoxKeyTimer <= 0.0f)
			{
				pHex = this->GetApp()->GetButtonPress();

				if (pHex != NULL)
				{
					switch (m_iControlInput)
					{
					case 1:
						this->GetApp()->GetConfig().SetStrUp(pHex);
						break;

					case 2:
						this->GetApp()->GetConfig().SetStrDown(pHex);
						break;

					case 3:
						this->GetApp()->GetConfig().SetStrLeft(pHex);
						break;

					case 4:
						this->GetApp()->GetConfig().SetStrRight(pHex);
						break;

					case 5:
						this->GetApp()->GetConfig().SetStrFireMode(pHex);
						break;

					case 6:
						this->GetApp()->GetConfig().SetStrMinigun(pHex);
						break;

					case 7:
						this->GetApp()->GetConfig().SetStrCannon(pHex);
						break;

					case 8:
						this->GetApp()->GetConfig().SetStrBlast(pHex);
						break;
					}

					this->GetApp()->GetConfig().RemoveDuplicate(m_iControlInput);
					m_bMessageBoxKey = false;

					// play menu "option" sound
					this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
				}
			}
		}
		else
		{
			// mouse cursor is on top of Up text
			if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Up) || 
				(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 320 &&
				this->GetApp()->GetMouseY() > 401 && this->GetApp()->GetMouseY() < 421))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 402);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 1;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Down text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Down) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 358 &&
					 this->GetApp()->GetMouseY() > 428 && this->GetApp()->GetMouseY() < 449))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 429);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 2;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Left text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Left) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 337 &&
					 this->GetApp()->GetMouseY() > 457 && this->GetApp()->GetMouseY() < 477))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 458);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 3;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Right text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Right) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 355 &&
					 this->GetApp()->GetMouseY() > 485 && this->GetApp()->GetMouseY() < 505))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 486);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 4;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Fire mode text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Fire_Mode) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 419 &&
					 this->GetApp()->GetMouseY() > 513 && this->GetApp()->GetMouseY() < 533))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 514);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 5;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Minigun text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Minigun) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 389 &&
					 this->GetApp()->GetMouseY() > 541 && this->GetApp()->GetMouseY() < 561))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 542);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 6;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Cannon text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Cannon) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 386 &&
					 this->GetApp()->GetMouseY() > 569 && this->GetApp()->GetMouseY() < 589))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 570);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 7;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Blast text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Key_Blast) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 283 && this->GetApp()->GetMouseX() < 360 &&
					 this->GetApp()->GetMouseY() > 597 && this->GetApp()->GetMouseY() < 617))
			{
				// draw arrow
				this->m_pSpriteArrowInput->Draw(235, 598);

				// select button is pressed
				if (IsValidSelectClick())
				{
					this->m_iControlInput = 8;
					this->m_fBoxKeyTimer = 0.1f;
					this->m_bMessageBoxKey = true;
				}
			}
			// mouse cursor is on top of Back text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Back) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 366 && this->GetApp()->GetMouseX() < 475 &&
					 this->GetApp()->GetMouseY() > 673 && this->GetApp()->GetMouseY() < 704))
			{
				// draw underline
				this->m_pSpriteUnderlineBack->Draw(367, 713);

				// select button is pressed
				if (IsValidSelectClick())
				{
					OnBackAction();
				}
			}
			// mouse cursor is on top of Default text
			else if ((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Input_Default) || 
					(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 558 && this->GetApp()->GetMouseX() < 713 &&
					 this->GetApp()->GetMouseY() > 673 && this->GetApp()->GetMouseY() < 704))
			{
				// draw underline
				this->m_pSpriteUnderlineDefault->Draw(559, 713);

				// select button is pressed
				if (IsValidSelectClick())
				{
					// play menu "option" sound
					this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

					// load default controls
					this->GetApp()->GetConfig().DefaultControls();
				}
			}
		}
	}

	// draw menu text
	this->m_pSpriteMenuInput->Draw(0,0);
}

void CStateMenus::RenderAudio(float fFrametime)
{
	m_fSoundBarNoiseTimer -= fFrametime;

	int iValue;
	int iMinus = 412;
	int invalidBarValue = -1000;
	float fValue;

	// draw audio bars
	this->RenderAudioBars();

	// mouse cursor is on top of music bar
	if( (m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Audio_Music) || 
		(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 400 && this->GetApp()->GetMouseX() < 624 &&
		this->GetApp()->GetMouseY() > 408 && this->GetApp()->GetMouseY() < 423))
	{
		iValue = invalidBarValue;

		// keyboard left/right arrow keys
		if (m_eInputDevice == eINPUT_DEVICE::Keyboard)
		{
			if (m_bInputLeft)
			{

			}
			else if (m_bInputRight)
			{

			}
		}
		// select button is pressed
		else if (this->m_bInputSelect)
		{
			if (this->GetApp()->GetMouseX() > 400 && this->GetApp()->GetMouseX() < 413)
			{
				iValue = 0;
			}
			else if (this->GetApp()->GetMouseX() > 611 && this->GetApp()->GetMouseX() < 624)
			{
				iValue = 100;
			}
			else
			{
				fValue = (this->GetApp()->GetMouseX() - iMinus) / 2;
				// rounds value down
				iValue = floor(fValue);
			}
		}

		// new music volume is different than the current one
		if ((iValue != invalidBarValue) && (iValue != this->GetApp()->GetConfig().GetVolumeMusic()))
		{
			this->GetApp()->GetConfig().SetVolumeMusic(iValue);

			// set music volume
			this->GetApp()->GetMP3Player1().SetVolume( this->GetApp()->GetVolumeMusic() );
			this->GetApp()->GetMP3Player2().SetVolume( this->GetApp()->GetVolumeMusic() );

			// music is stopped or paused
			if(	(this->GetApp()->GetMP3Player1().GetState() == 0) || 
				(this->GetApp()->GetMP3Player1().GetState() == 2))
			{
				if(iValue > 0)
				{
					// play music
					this->GetApp()->GetMP3Player1().Play();
				}
			}
			// music is playing
			else if(this->GetApp()->GetMP3Player1().GetState() == 1)
			{
				if(iValue == 0)
				{
					// pause music
					this->GetApp()->GetMP3Player1().Pause();
				}
			}
		}
	}
	// mouse cursor is on top of sound effect bar
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Audio_Sound) || 
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 400 && this->GetApp()->GetMouseX() < 624 &&
			this->GetApp()->GetMouseY() > 546 && this->GetApp()->GetMouseY() < 561))
	{
		iValue = invalidBarValue;

		// keyboard left/right arrow keys
		if (m_eInputDevice == eINPUT_DEVICE::Keyboard)
		{
			if (m_bInputLeft)
			{

			}
			else if (m_bInputRight)
			{

			}
		}
		// select button is pressed
		else if (this->m_bInputSelect)
		{
			if (this->GetApp()->GetMouseX() > 400 && this->GetApp()->GetMouseX() < 413)
			{
				iValue = 0;
			}
			else if (this->GetApp()->GetMouseX() > 611 && this->GetApp()->GetMouseX() < 624)
			{
				iValue = 100;
			}
			else
			{
				fValue = (this->GetApp()->GetMouseX() - iMinus) / 2;
				// rounds value down
				iValue = floor(fValue);
			}
		}

		if (iValue != invalidBarValue)
		{
			// new sound effect volume is different than the current one
			if(iValue != this->GetApp()->GetConfig().GetVolumeSoundEffect())
			{
				this->GetApp()->GetConfig().SetVolumeSoundEffect(iValue);

				// set volume of sound effects that don't use duplicates
				for (int i = 0; i < FIRST_DUPLICATE_SOUND; i++)
				{
					this->GetApp()->GetWave(i).SetVolume(this->GetApp()->GetVolumeSoundEffect(), 0);
				}

				// set volume of sound effects that use duplicates
				for (int i = FIRST_DUPLICATE_SOUND; i < NUM_WAVES; i++)
				{
					this->GetApp()->GetWave(i).SetVolume(this->GetApp()->GetVolumeSoundEffect(), 1);
				}

				// play menu "select" sound
				if (m_eInputDevice == eINPUT_DEVICE::Keyboard)
				{
					PlaySoundBarNoise(true);
				}
			}

			if (m_eInputDevice != eINPUT_DEVICE::Keyboard)
			{
				PlaySoundBarNoise(false);
			}
		}
	}
	// mouse cursor is on top of Back text
	else if((m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Audio_Back) || 
			(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 457 && this->GetApp()->GetMouseX() < 565 &&
			this->GetApp()->GetMouseY() > 675 && this->GetApp()->GetMouseY() < 702))
	{
		// draw underline
		this->m_pSpriteUnderlineBack->Draw(458, 713);

		// select button is pressed
		if(IsValidSelectClick())
		{
			OnBackAction();
		}
	}

	// draw menu text
	this->m_pSpriteMenuAudio->Draw(0,0);
}

void CStateMenus::RenderDisplay()
{
	/* RESTART MESSAGE BOX */

	if(this->m_bDisplayChangesExit)
	{
		// draw restart box
		this->m_pSpriteMessageRestart->Draw(371,397);

		// draw OK text
		if(this->GetApp()->GetMouseX() > 498 && this->GetApp()->GetMouseX() < 526 && 
			this->GetApp()->GetMouseY() > 480 && this->GetApp()->GetMouseY() < 495)
		{
			this->m_pSpriteMessageOK2->Draw(499,481);
		}
		else
		{
			this->m_pSpriteMessageOK1->Draw(499,481);
		}

		// mouse cursor is on top of OK text
		if(this->GetApp()->GetMouseX() > 498 && this->GetApp()->GetMouseX() < 526 && 
			this->GetApp()->GetMouseY() > 480 && this->GetApp()->GetMouseY() < 495)
		{
			// select button is pressed
			if(IsValidSelectClick())
			{
				this->m_bDisplayChangesExit = false;
				OnBackAction();
			}
		}

		return;
	}

	/* ANTIALIASING */

	bool bShowArrow;

	// draw antialiasing border
	this->m_pSpriteVideoAntialiasingBarBorder->Draw(384,412);

	// draw currently selected antialiasing option

	switch(this->GetApp()->GetConfig().GetAntialiasing())
	{
	case CConfig::eANTIALIASING_2X:
		this->m_pSpriteVideoAntialiasingBar2x->Draw(394,421);
		break;

	case CConfig::eANTIALIASING_4X:
		this->m_pSpriteVideoAntialiasingBar2x->Draw(394,421);
		this->m_pSpriteVideoAntialiasingBar46x->Draw(454,421);
		break;

	case CConfig::eANTIALIASING_6X:
		this->m_pSpriteVideoAntialiasingBar2x->Draw(394,421);
		this->m_pSpriteVideoAntialiasingBar46x->Draw(454,421);
		this->m_pSpriteVideoAntialiasingBar46x->Draw(514,421);
		break;

	case CConfig::eANTIALIASING_8X:
		this->m_pSpriteVideoAntialiasingBar2x->Draw(394,421);
		this->m_pSpriteVideoAntialiasingBar46x->Draw(454,421);
		this->m_pSpriteVideoAntialiasingBar46x->Draw(514,421);
		this->m_pSpriteVideoAntialiasingBar8x->Draw(574,421);
		break;
	}

	// draw arrows

	bShowArrow = false;

	// checks if antialiasing left arrow can be drawn
	if(this->GetApp()->GetConfig().GetAntialiasing() != CConfig::eANTIALIASING_0X)
	{
		bShowArrow = true;
	}

	if(bShowArrow)
	{
		// mouse cursor is on top of left arrow
		if(	this->GetApp()->GetMouseX() > 332 && this->GetApp()->GetMouseX() < 364 && 
			this->GetApp()->GetMouseY() > 420 && this->GetApp()->GetMouseY() < 441)
		{
			// draw glowing left arrow
			this->m_pSpriteArrowAntialiasingGlowLeft->Draw(325,413);

			// select button is pressed
			if(IsValidSelectClick())
			{
				// play menu "option" sound
				this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());;
							
				// change antialiasing option
				switch(this->GetApp()->GetConfig().GetAntialiasing())
				{
				case CConfig::eANTIALIASING_2X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_0X);
					break;

				case CConfig::eANTIALIASING_4X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_2X);
					break;

				case CConfig::eANTIALIASING_6X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_4X);
					break;

				case CConfig::eANTIALIASING_8X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_6X);
					break; 
				}
			}
		}
		else
		{
			// draw normal left arrow
			this->m_pSpriteArrowAntialiasingNormalLeft->Draw(333,421);
		}
	}
	else
	{
		// draw hidden left arrow
		this->m_pSpriteArrowAntialiasingHideLeft->Draw(333,421);
	}

	bShowArrow = false;

	// checks if antialiasing right arrow can be drawn
	if(this->GetApp()->GetConfig().GetAntialiasing() != CConfig::eANTIALIASING_8X)
	{
		if(this->GetApp()->GetConfig().GetAntialiasing() == CConfig::eANTIALIASING_0X)
		{
			if(this->GetApp()->GetMaxAntialiasing() >= 2)
			{
				bShowArrow = true;
			}
		}
		else if(this->GetApp()->GetConfig().GetAntialiasing() == CConfig::eANTIALIASING_2X)
		{
			if(this->GetApp()->GetMaxAntialiasing() >= 4)
			{
				bShowArrow = true;
			}
		}
		else if(this->GetApp()->GetConfig().GetAntialiasing() == CConfig::eANTIALIASING_6X)
		{
			if(this->GetApp()->GetMaxAntialiasing() >= 6)
			{
				bShowArrow = true;
			}
		}
		else if(this->GetApp()->GetConfig().GetAntialiasing() == CConfig::eANTIALIASING_8X)
		{
			if(this->GetApp()->GetMaxAntialiasing() >= 8)
			{
				bShowArrow = true;
			}
		}
	}

	if(bShowArrow)
	{
		// mouse cursor is on top of right arrow
		if(	this->GetApp()->GetMouseX() > 656 && this->GetApp()->GetMouseX() < 688 && 
			this->GetApp()->GetMouseY() > 420 && this->GetApp()->GetMouseY() < 441)
		{
			// draw glowing right arrow
			this->m_pSpriteArrowAntialiasingGlowRight->Draw(649,413);

			// select button is pressed
			if(IsValidSelectClick())
			{
				// play menu "option" sound
				this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
							
				// change antialiasing option
				switch(this->GetApp()->GetConfig().GetAntialiasing())
				{
				case CConfig::eANTIALIASING_0X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_2X);
					break;

				case CConfig::eANTIALIASING_2X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_4X);
					break;

				case CConfig::eANTIALIASING_4X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_6X);
					break;

				case CConfig::eANTIALIASING_6X:
					this->GetApp()->GetConfig().SetAntialiasing(CConfig::eANTIALIASING_8X);
					break; 
				}
			}
		}
		else
		{
			// draw normal right arrow
			this->m_pSpriteArrowAntialiasingNormalRight->Draw(657,421);
		}
	}
	else
	{
		// draw hidden right arrow
		this->m_pSpriteArrowAntialiasingHideRight->Draw(657,421);
	}

	/* SPECULAR LIGHTING */

	// draw currently selected specular lighting option and arrows

	switch(this->GetApp()->GetConfig().GetSpecularLighting())
	{
	case CConfig::eSPECULAR_LIGHTING_OFF:

		// mouse cursor is on top of OFF text
		if(	this->GetApp()->GetMouseX() > 483 && this->GetApp()->GetMouseX() < 539 && 
			this->GetApp()->GetMouseY() > 568 && this->GetApp()->GetMouseY() < 594)
		{
			// draw specular lighting arrows
			this->m_pSpriteSpecularLightingOffGlow->Draw(476,561);

			// select button is pressed
			if(IsValidSelectClick())
			{
				// play menu "option" sound
				this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

				this->GetApp()->GetConfig().SetSpecularLighting(CConfig::eSPECULAR_LIGHTING_ON);

				if(this->m_bChangeSpecularity)
				{
					this->m_bChangeSpecularity = false;
				}
				else if(!this->m_bChangeSpecularity)
				{
					this->m_bChangeSpecularity = true;
				}
			}
		}
		else
		{
			this->m_pSpriteSpecularLightingOff->Draw(484,569);
		}

		break;

	case CConfig::eSPECULAR_LIGHTING_ON:

		// mouse cursor is on top of ON text
		if(	this->GetApp()->GetMouseX() > 487 && this->GetApp()->GetMouseX() < 537 &&
			this->GetApp()->GetMouseY() > 568 && this->GetApp()->GetMouseY() < 594)
		{
			this->m_pSpriteSpecularLightingOnGlow->Draw(479,561);

			// select button is pressed
			if(IsValidSelectClick())
			{
				// play menu "option" sound
				this->GetApp()->GetWave(SOUND_MENU_OPTION).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

				this->GetApp()->GetConfig().SetSpecularLighting(CConfig::eSPECULAR_LIGHTING_OFF);

				if(this->m_bChangeSpecularity)
				{
					this->m_bChangeSpecularity = false;
				}
				else if(!this->m_bChangeSpecularity)
				{
					this->m_bChangeSpecularity = true;
				}
			}
		}
		else
		{
			this->m_pSpriteSpecularLightingOn->Draw(487,569);
		}

		break;
	}

	// mouse cursor is on top of Back text
	if( (m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Display_Back) || 
		(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 457 && this->GetApp()->GetMouseX() < 565 &&
		this->GetApp()->GetMouseY() > 675 && this->GetApp()->GetMouseY() < 702))
	{
		// draw underline
		this->m_pSpriteUnderlineBack->Draw(458,713);

		// select button is pressed
		if(IsValidSelectClick())
		{
			OnBackAction();
		}
	}

	// draw menu text
	this->m_pSpriteMenuDisplay->Draw(0,0);
}

void CStateMenus::RenderHighScore(float fFrametime)
{
	if(!this->GetApp()->GetHighScore().IsEmpty())
	{
		this->RenderScores(fFrametime);
	}

	// mouse cursor is on top of Back text
	if( (m_eInputDevice == eINPUT_DEVICE::Keyboard && m_eKeyboardMenuBrowse == eKEYBOARD_MENU_BROWSE::Highscore_Back) ||
		(m_eInputDevice != eINPUT_DEVICE::Keyboard && this->GetApp()->GetMouseX() > 457 && this->GetApp()->GetMouseX() < 566 &&
		this->GetApp()->GetMouseY() > 673 && this->GetApp()->GetMouseY() < 704))
	{
		// draw underline
		this->m_pSpriteUnderlineBack->Draw(458, 713);

		// select button is pressed
		if(IsValidSelectClick())
		{
			OnBackAction();
		}
	}

	// draw menu text
	this->m_pSpriteMenuHighscore->Draw(0,0);
}

#ifdef MENU_CREDITS
void CStateMenus::RenderCredits()
{
	this->m_pSpriteCreditsBackLayer->Draw(0,0);
	this->m_pSpriteCreditsText->Draw(false);

	// credits has reached to the end
	if(this->m_pSpriteCreditsText->GetPositionY() < -(this->m_pSpriteCreditsText->GetSpriteHeight()))
	{
		OnBackAction();
	}
	// select button is pressed
	if(IsValidSelectClick())
	{
		OnBackAction();
	}
}
#endif

void CStateMenus::RenderExit(float fFrametime)
{
	bool bScreenFading = this->GetFading()->UpdateFading();

	// fade out music
	if(this->m_bFadeOutMusic)
	{
		if(this->GetApp()->VolumeMusicFadeOut(fFrametime))
		{
			// set music volume
			this->GetApp()->GetMP3Player1().SetVolume( this->GetApp()->GetVolumeMusic() );
		}
		// music fade out finished
		else
		{
			// set music volume, it's now back to original volume
			this->GetApp()->GetMP3Player1().SetVolume( this->GetApp()->GetVolumeMusic() );
			this->GetApp()->GetMP3Player2().SetVolume( this->GetApp()->GetVolumeMusic() );

			// music has volume
			if(this->GetApp()->GetConfig().GetVolumeMusic() > 0)
			{
				// music player is active
				if(this->GetApp()->GetMP3Player1().GetState() == 1)
				{
					// stop music play
					this->GetApp()->GetMP3Player1().Stop();
				}
				// release music
				this->GetApp()->GetMP3Player1().Release();
			}

			this->m_bFadeOutMusic = false;
		}
	}

	// draw menu text
	this->m_pSpriteMenuMain->Draw(0,0);
	// draw game version
	this->RenderGameVersion();
	// draw fade-out
	this->GetFading()->RenderFading();

	if(!bScreenFading && !this->m_bFadeOutMusic)
	{
		// change state
		m_dwNextState = STATE_EXIT_APP;
	}
}

void CStateMenus::RenderAudioBars()
{
	int iMusicX = 400;
	int iMusicY = 397;

	int iSoundEffectX = 400;
	int iSoundEffectY = 535;

	int iVolumeMusic = this->GetApp()->GetConfig().GetVolumeMusic();
	int iVolumeSoundEffect = this->GetApp()->GetConfig().GetVolumeSoundEffect();

	// render audio bar borders
	this->m_pSpriteAudioBarBorder->Draw(iMusicX,iMusicY);
	this->m_pSpriteAudioBarBorder->Draw(iSoundEffectX,iSoundEffectY);

	// render audio bar meters
	if(iVolumeMusic > 0)
	{
		this->m_pSpriteAudioBarMeter[iVolumeMusic - 1].Draw(iMusicX,iMusicY);
	}
	if(iVolumeSoundEffect > 0)
	{
		this->m_pSpriteAudioBarMeter[iVolumeSoundEffect - 1].Draw(iSoundEffectX,iSoundEffectY);
	}
}

void CStateMenus::RenderBackground()
{
	this->m_pSpriteMenuBackground->Draw(0, 0);
	this->m_pSpriteStarsBack->Draw(false);
	this->m_pSpriteStarsFront->Draw(false);
}

void CStateMenus::RenderShips(float fFrametime)
{
	this->m_pShips.SetFirst();
	while ( this->m_pShips.GetCurrent() )
	{
		this->m_pShips.GetCurrent()->Update(fFrametime);
		this->m_pShips.GetCurrent()->Render(this->GetApp()->GetDevice());

		// next ship	
		this->m_pShips.SetNext();
	}

	this->m_pBoss1ScatterLeft->UpdateShip(m_pBoss1Frame, fFrametime);
	this->m_pBoss1ScatterRight->UpdateShip(m_pBoss1Frame, fFrametime);

	this->m_pBoss1ScatterLeft->Render(this->GetApp()->GetDevice());
	this->m_pBoss1ScatterRight->Render(this->GetApp()->GetDevice());
}

void CStateMenus::RenderScores(float fFrametime)
{
	char* pPointer;
	char* sPointer = NULL;

	D3DXVECTOR3 pos;
	float fPosX;

	// starting y-axel position
	pos.y = 20.0f;
	pos.z = -1000.0f;

	std::string strName;
	int iLength;

	int iData;
	float fTimeOrig;

	this->m_Scores = this->GetApp()->GetHighScore().GetScores();
	int size = (int)this->m_Scores.size();

	for (int i = 0; i < size; i++)
	{
		if (i == MAX_HIGHSCORE_ITEMS)
		{
			break;
		}

		/* RENDER RANK */

		// x-axel position
		fPosX = -169.5f;

		iData = i + 1;

		sPointer = TextUtils::IntToChar(iData);
		pPointer = sPointer;

		if (iData == 10)
		{
			fPosX -= this->m_fNumberWidth * 0.5f;
		}

		pos.x = fPosX;

		while ((*pPointer) != NULL)
		{
			(this->m_pNumbers + ((*pPointer) - '0'))->SetPosition(pos);
			(this->m_pNumbers + ((*pPointer) - '0'))->Update(fFrametime);
			(this->m_pNumbers + ((*pPointer) - '0'))->Render(this->GetApp()->GetDevice());
			pos.x += this->m_fNumberWidth;

			pPointer++;
		}

		delete[] sPointer;
		sPointer = NULL;

		/* RENDER NAME */

		// x-axel position
		fPosX = -86.0f;

		strName = this->m_Scores[i].GetName();
		iLength = strName.length();

		switch (iLength)
		{
		case 2:
			fPosX -= this->m_fLetterWidth * 0.5f;
			break;
		case 3:
			fPosX -= this->m_fLetterWidth;
			break;
		case 4:
			fPosX -= this->m_fLetterWidth * 1.5f;
			break;
		case 5:
			fPosX -= this->m_fLetterWidth * 2.0f;
			break;
		case 6:
			fPosX -= this->m_fLetterWidth * 2.5f;
			break;
		case 7:
			fPosX -= this->m_fLetterWidth * 3.0f;
			break;
		case 8:
			fPosX -= this->m_fLetterWidth * 3.5f;
			break;
		}

		pos.x = fPosX;

		for (int j = 0; j < iLength; j++)
		{
			if (strName[j] == 'A')
			{
				this->m_pLetters[LOAD_MESH_MENUS_A].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_A].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_A].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'B')
			{
				this->m_pLetters[LOAD_MESH_MENUS_B].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_B].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_B].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'C')
			{
				this->m_pLetters[LOAD_MESH_MENUS_C].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_C].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_C].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'D')
			{
				this->m_pLetters[LOAD_MESH_MENUS_D].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_D].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_D].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'E')
			{
				this->m_pLetters[LOAD_MESH_MENUS_E].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_E].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_E].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'F')
			{
				this->m_pLetters[LOAD_MESH_MENUS_F].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_F].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_F].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'G')
			{
				this->m_pLetters[LOAD_MESH_MENUS_G].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_G].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_G].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'H')
			{
				this->m_pLetters[LOAD_MESH_MENUS_H].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_H].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_H].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'I')
			{
				this->m_pLetters[LOAD_MESH_MENUS_I].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_I].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_I].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'J')
			{
				this->m_pLetters[LOAD_MESH_MENUS_J].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_J].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_J].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'K')
			{
				this->m_pLetters[LOAD_MESH_MENUS_K].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_K].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_K].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'L')
			{
				this->m_pLetters[LOAD_MESH_MENUS_L].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_L].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_L].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'M')
			{
				this->m_pLetters[LOAD_MESH_MENUS_M].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_M].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_M].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'N')
			{
				this->m_pLetters[LOAD_MESH_MENUS_N].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_N].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_N].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'O')
			{
				this->m_pLetters[LOAD_MESH_MENUS_O].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_O].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_O].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'P')
			{
				this->m_pLetters[LOAD_MESH_MENUS_P].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_P].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_P].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'Q')
			{
				this->m_pLetters[LOAD_MESH_MENUS_Q].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_Q].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_Q].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'R')
			{
				this->m_pLetters[LOAD_MESH_MENUS_R].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_R].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_R].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'S')
			{
				this->m_pLetters[LOAD_MESH_MENUS_S].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_S].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_S].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'T')
			{
				this->m_pLetters[LOAD_MESH_MENUS_T].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_T].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_T].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'U')
			{
				this->m_pLetters[LOAD_MESH_MENUS_U].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_U].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_U].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'V')
			{
				this->m_pLetters[LOAD_MESH_MENUS_V].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_V].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_V].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'W')
			{
				this->m_pLetters[LOAD_MESH_MENUS_W].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_W].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_W].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'X')
			{
				this->m_pLetters[LOAD_MESH_MENUS_X].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_X].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_X].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'Y')
			{
				this->m_pLetters[LOAD_MESH_MENUS_Y].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_Y].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_Y].Render(this->GetApp()->GetDevice());
			}
			else if (strName[j] == 'Z')
			{
				this->m_pLetters[LOAD_MESH_MENUS_Z].SetPosition(pos);
				this->m_pLetters[LOAD_MESH_MENUS_Z].Update(fFrametime);
				this->m_pLetters[LOAD_MESH_MENUS_Z].Render(this->GetApp()->GetDevice());
			}

			pos.x += this->m_fLetterWidth;
		}

		/* RENDER SCORE */

		// x-axel position
		fPosX = 0.0f;

		iData = this->m_Scores[i].GetScore();

		sPointer = TextUtils::IntToChar(iData);
		pPointer = sPointer;

		if ((iData > 9) &&
			(iData < 100))
		{
			fPosX -= this->m_fNumberWidth * 0.5f;
		}
		else if ((iData > 99) &&
			(iData < 1000))
		{
			fPosX -= this->m_fNumberWidth;
		}
		else if ((iData > 999) &&
			(iData < 10000))
		{
			fPosX -= this->m_fNumberWidth * 1.5f;
		}
		else if ((iData > 9999) &&
			(iData < 100000))
		{
			fPosX -= this->m_fNumberWidth * 2.0f;
		}

		pos.x = fPosX;

		while ((*pPointer) != NULL)
		{
			(this->m_pNumbers + ((*pPointer) - '0'))->SetPosition(pos);
			(this->m_pNumbers + ((*pPointer) - '0'))->Update(fFrametime);
			(this->m_pNumbers + ((*pPointer) - '0'))->Render(this->GetApp()->GetDevice());
			pos.x += this->m_fNumberWidth;

			pPointer++;
		}

		delete[] sPointer;
		sPointer = NULL;

		/* RENDER LEVEL */

		// x-axel position
		pos.x = 85.5f;

		iData = this->m_Scores[i].GetLevel();

		sPointer = TextUtils::IntToChar(iData);
		pPointer = sPointer;

		while ((*pPointer) != NULL)
		{
			(this->m_pNumbers + ((*pPointer) - '0'))->SetPosition(pos);
			(this->m_pNumbers + ((*pPointer) - '0'))->Update(fFrametime);
			(this->m_pNumbers + ((*pPointer) - '0'))->Render(this->GetApp()->GetDevice());
			pos.x += this->m_fNumberWidth;

			pPointer++;
		}

		delete[] sPointer;
		sPointer = NULL;

		/* RENDER TIME */

		// x-axel position
		fPosX = 169.0f;

		// get original time
		fTimeOrig = this->m_Scores[i].GetTime();
		// rounds time up
		iData = ceil(fTimeOrig);

		sPointer = TextUtils::IntToChar(iData);
		pPointer = sPointer;

		if ((iData > 9) &&
			(iData < 100))
		{
			fPosX -= this->m_fNumberWidth * 0.5f;
		}
		else if ((iData > 99) &&
			(iData < 1000))
		{
			fPosX -= this->m_fNumberWidth;
		}
		else if ((iData > 999) &&
			(iData < 10000))
		{
			fPosX -= this->m_fNumberWidth * 1.5f;
		}
		else if ((iData > 9999) &&
			(iData < 100000))
		{
			fPosX -= this->m_fNumberWidth * 2.0f;
		}

		pos.x = fPosX;

		while ((*pPointer) != NULL)
		{
			(this->m_pNumbers + ((*pPointer) - '0'))->SetPosition(pos);
			(this->m_pNumbers + ((*pPointer) - '0'))->Update(fFrametime);
			(this->m_pNumbers + ((*pPointer) - '0'))->Render(this->GetApp()->GetDevice());
			pos.x += this->m_fNumberWidth;

			pPointer++;
		}

		delete[] sPointer;
		sPointer = NULL;

		/* CHANGE LINE */
		pos.y -= 12.0f;
	}
}

void CStateMenus::RenderGameVersion()
{
	this->m_pSpriteVersion->Draw(957,736);
}

#ifdef MENUS_PLANET
void CStateMenus::RenderPlanet()
{
	this->m_pPlanet->Update(fFrametime);
	this->m_pPlanet->Render(this->GetApp()->GetDevice());
}
#endif

#ifdef MENUS_FOG
void CStateMenus::RenderFog()
{
	this->m_pSpriteFogBack->Draw(false);
	this->m_pSpriteFogFront->Draw(false);
}
#endif

void CStateMenus::OnBackAction()
{
	switch (this->m_eMenus)
	{
	case Main:

		this->GetFading()->SetFadeOut();
		this->GetFading()->SetDefaultFadeStep();
		//this->GetFading()->SetFadeStep(0x05000000);

		// play menu "back" sound
		this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

		this->m_eMenus = Exit;

		break;

	case Options:

		// play menu "back" sound
		this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
		// change menu
		this->m_eMenus = Main;
		m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Main_Options;

		break;

	case Input:

		// there are empty control buttons
		if (this->GetApp()->GetConfig().ButtonEmpty())
		{
			this->m_bMessageBoxEmpty = true;
		}
		// no empty control buttons
		else
		{
			if (!this->m_bMessageBoxKey)
			{
				// save config data (not necessarily changed)
				this->GetApp()->GetConfig().Save();
				// set font to default
				this->GetApp()->SetTextFontDefault();
				// play menu "back" sound
				this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
				// change menu
				this->m_eMenus = Options;
				m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Options_Input;
			}
		}

		break;

	case Audio:

		// play menu "back" sound
		this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
		// save configuration
		this->GetApp()->GetConfig().Save();
		// change menu
		this->m_eMenus = Options;
		m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Options_Audio;

		break;

	case Display:

		// antialiasing changed
		if (this->m_iAntialiasingCurrent != (int)this->GetApp()->GetConfig().GetAntialiasing())
		{
			this->m_iAntialiasingCurrent = (int)this->GetApp()->GetConfig().GetAntialiasing();
			this->m_bDisplayChangesExit = true;

			// move mouse cursor on top of the OK text of message box
			this->GetApp()->SetMouseX(512);
			this->GetApp()->SetMouseY(488);
		}
		else
		{
			// save configuration
			this->GetApp()->GetConfig().Save();

			// play menu "back" sound
			this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());

			// change 3d object's specular settings
			if (this->m_bChangeSpecularity)
			{
				this->ChangeSpecularity();
				this->m_bChangeSpecularity = false;
			}

			// change menu
			this->m_eMenus = Options;
			m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Options_Display;
		}

		break;

	case Highscore:

		// change font to default
		this->GetApp()->SetTextFontDefault();
		// play menu "back" sound
		this->GetApp()->GetWave(SOUND_MENU_BACK).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
		// change menu
		this->m_eMenus = Main;
		m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Main_Highscore;

		break;

	case Credits:

		// reset sprite
#ifdef MENU_CREDITS
		this->m_pSpriteCreditsText->Reset();
#endif
		// change menu
		this->m_eMenus = Main;
		//m_eKeyboardMenuBrowse = eKEYBOARD_MENU_BROWSE::Main_Credits;

		break;
	}
}

void CStateMenus::ResetPlayerInput()
{
	this->m_bIsClickPause = false;

	if (this->m_bInputSelect)
	{
		this->m_bIsClickPause = true;
	}

	this->m_bInputUp = false;
	this->m_bInputDown = false;
	this->m_bInputLeft = false;
	this->m_bInputRight = false;
	this->m_bInputSelect = false;
}

void CStateMenus::UpdatePlayerInput()
{
	if (this->GetApp()->IsMouseMovement() || this->m_pMouse->GetButton(0))
	{
		m_eInputDevice = Mouse;

		if (this->m_pMouse->GetButton(0))
		{
			this->m_bInputSelect = true;
		}

		return;
	}

	bool bCheckKeyboard = true;

	// JOYSTICK DEVICE

	if (SUCCEEDED(this->m_pJoystick->Update()))
	{
		DWORD buttons = this->m_pJoystick->GetButtonCount();
		int iJoystickY = this->m_pJoystick->GetState().lY;
		int iJoystickX = this->m_pJoystick->GetState().lX;

		// read buttons
		for (DWORD i = 0; i < buttons; i++)
		{
			// read select control
			if (this->m_pJoystick->GetButton(i))
			{
				this->m_bInputSelect = true;
				m_eInputDevice = Joystick;
				break;
			}
		}

		// read up control
		if (iJoystickY < 0)
		{
			this->m_bInputUp = true;
			m_eInputDevice = Joystick;
		}
		// read down control
		else if (iJoystickY > 0)
		{
			this->m_bInputDown = true;
			m_eInputDevice = Joystick;
		}

		// read left control
		if (iJoystickX < 0)
		{
			this->m_bInputLeft = true;
			m_eInputDevice = Joystick;
		}
		// read right control
		else if (iJoystickX > 0)
		{
			this->m_bInputRight = true;
			m_eInputDevice = Joystick;
		}
	}
}

bool CStateMenus::IsValidSelectClick()
{
	if (!this->m_bIsClickPause && this->m_bInputSelect)
	{
		return true;
	}

	return false;
}

void CStateMenus::OnKeyboardMenuBrowse(DWORD dwKey)
{
	if (this->m_bMessageBoxKey)
	{
		return;
	}

	if (m_eInputDevice != Keyboard)
	{
		// temporary value
		int intValue = 0;

		switch (m_eMenus)
		{
		case eMENUS::Main:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Main_First;
			intValue += 1;
			break;
		case eMENUS::Options:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Options_First;
			intValue += 1;
			break;
		case eMENUS::Input:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Input_Back;
			break;
		case eMENUS::Audio:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Audio_Back;
			break;
		case eMENUS::Display:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Display_Back;
			break;
		case eMENUS::Highscore:
			intValue = (int)eKEYBOARD_MENU_BROWSE::Highscore_Back;
			break;
		}

		m_eKeyboardMenuBrowse = (eKEYBOARD_MENU_BROWSE)intValue;
	}
	else
	{
		int intValue = (int)m_eKeyboardMenuBrowse;

		switch (dwKey)
		{
		case VK_UP:
			intValue--;
			break;

		case VK_DOWN:
			intValue++;
			break;
		}

		// temporary values
		int minValue = 0;
		int maxValue = 0;

		switch (m_eMenus)
		{
		case eMENUS::Main:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Main_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Main_Last;
			break;
		case eMENUS::Options:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Options_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Options_Last;
			break;
		case eMENUS::Input:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Input_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Input_Last;
			break;
		case eMENUS::Audio:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Audio_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Audio_Last;
			break;
		case eMENUS::Display:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Display_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Display_Last;
			break;
		case eMENUS::Highscore:
			minValue = (int)eKEYBOARD_MENU_BROWSE::Highscore_First;
			maxValue = (int)eKEYBOARD_MENU_BROWSE::Highscore_Last;
			break;
		}

		if (intValue <= minValue)
		{
			intValue = maxValue - 1;
		}
		else if (intValue >= maxValue)
		{
			intValue = minValue + 1;
		}

		m_eKeyboardMenuBrowse = (eKEYBOARD_MENU_BROWSE)intValue;
	}
}

void CStateMenus::PlaySoundBarNoise(bool bIsForced)
{
	if (bIsForced || (m_fSoundBarNoiseTimer <= 0.0f))
	{
		// play menu "select" sound
		this->GetApp()->GetWave(SOUND_MENU_SELECT).Play(FALSE, NEXT_FREE_DUPLICATE, this->GetApp()->GetVolumeSoundEffect());
		m_fSoundBarNoiseTimer = 0.5f;
	}
}

void CStateMenus::ShowControls()
{
	m_iTextX = 636;
	m_iTextY = 365;

	std::basic_string<TCHAR> sMsg;
	TCHAR tMsg[256];

	// variables hold hex decimal 
	// representations of game controls
	char* up = new char[4];
	char* down = new char[4];
	char* left = new char[4];
	char* right = new char[4];
	char* mode = new char[4];
	char* minigun = new char[4];
	char* cannon = new char[4];
	char* blast = new char[4];

	// variables hold ascii char 
	// representations of game controls
	char upAscii = NULL;
	char downAscii = NULL;
	char leftAscii = NULL;
	char rightAscii = NULL;
	char modeAscii = NULL;
	char minigunAscii = NULL;
	char cannonAscii = NULL;
	char blastAscii = NULL;

	// get current hex decimal values
	up = this->GetApp()->GetConfig().GetStrUp();
	down = this->GetApp()->GetConfig().GetStrDown();
	left = this->GetApp()->GetConfig().GetStrLeft();
	right = this->GetApp()->GetConfig().GetStrRight();
	mode = this->GetApp()->GetConfig().GetStrMode();
	minigun = this->GetApp()->GetConfig().GetStrMinigun();
	cannon = this->GetApp()->GetConfig().GetStrCannon();
	blast = this->GetApp()->GetConfig().GetStrBlast();

	// checks if hex decimal values
	// represents letter/number ascii

	if(CheckHex(up[2], up[3]))
	{
		upAscii = HexToAscii(up[2], up[3]);
	}

	if(CheckHex(down[2], down[3]))
	{
		downAscii = HexToAscii(down[2], down[3]);
	}

	if(CheckHex(left[2], left[3]))
	{
		leftAscii = HexToAscii(left[2], left[3]);
	}
	
	if(CheckHex(right[2], right[3]))
	{
		rightAscii = HexToAscii(right[2], right[3]);
	}
	
	if(CheckHex(mode[2], mode[3]))
	{
		modeAscii = HexToAscii(mode[2], mode[3]);
	}
	
	if(CheckHex(minigun[2], minigun[3]))
	{
		minigunAscii = HexToAscii(minigun[2], minigun[3]);
	}
	
	if(CheckHex(cannon[2], cannon[3]))
	{
		cannonAscii = HexToAscii(cannon[2], cannon[3]);
	}
	
	if(CheckHex(blast[2], blast[3]))
	{
		blastAscii = HexToAscii(blast[2], blast[3]);
	}


	/* display current game controls on screen */

	this->GetApp()->BeginText();

	// display up key
	if(upAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("UP        %c"),
						upAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("UP        ") + this->DescribeHex(up[2], up[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display down key
	if(downAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("DOWN      %c"),
						downAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("DOWN      ") + this->DescribeHex(down[2], down[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display left key
	if(leftAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("LEFT      %c"),
						leftAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("LEFT      ") + this->DescribeHex(left[2], left[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display right key
	if(rightAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("RIGHT     %c"),
						rightAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("RIGHT     ") + this->DescribeHex(right[2], right[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display mode key
	if(modeAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("FIRE MODE %c"),
						modeAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("FIRE MODE ") + this->DescribeHex(mode[2], mode[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display minigun key
	if(minigunAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("MINIGUN   %c"),
						minigunAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("MINIGUN   ") + this->DescribeHex(minigun[2], minigun[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display cannon key
	if(cannonAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("CANNON    %c"),
						cannonAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("CANNON    ") + this->DescribeHex(cannon[2], cannon[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	m_iTextY += this->GetApp()->GetTextHeight();
	m_iTextY += this->GetApp()->GetTextHeight();

	// display blast key
	if(blastAscii != NULL)
	{
		_stprintf_s(	tMsg,
						_T("BLAST     %c"),
						blastAscii);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									tMsg,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	else
	{
		sMsg = _T("BLAST     ") + this->DescribeHex(blast[2], blast[3]);

		this->GetApp()->DrawText(	m_iTextX,
									m_iTextY,
									sMsg.c_str(),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	this->GetApp()->EndText();
}

bool CStateMenus::CheckHex(char first, char second)
{
	// BACKSPACE key
	if(first == '0' && second == '8')
	{
		return false;
	}

	// TAB key
	else if(first == '0' && second == '9')
	{
		return false;
	}

	// ENTER key
	else if(first == '0' && second == 'D')
	{
		return false;
	}

	// SHIFT key
	else if(first == '1' && second == '0')
	{
		return false;
	}

	// CTRL key
	else if(first == '1' && second == '1')
	{
		return false;
	}

	// ALT key
	else if(first == '1' && second == '2')
	{
		return false;
	}

	// ESC key
	else if(first == '1' && second == 'B')
	{
		return false;
	}

	// SPACEBAR
	else if(first == '2' && second == '0')
	{
		return false;
	}

	// LEFT ARROW key
	else if(first == '2' && second == '5')
	{
		return false;
	}

	// UP ARROW key
	else if(first == '2' && second == '6')
	{
		return false;
	}

	// RIGHT ARROW key
	else if(first == '2' && second == '7')
	{
		return false;
	}

	// DOWN ARROW key
	else if(first == '2' && second == '8')
	{
		return false;
	}

	// + key
	else if(first == 'B' && second == 'B')
	{
		return false;
	}

	// , key
	else if(first == 'B' && second == 'C')
	{
		return false;
	}

	// . key
	else if(first == 'B' && second == 'D')
	{
		return false;
	}

	// - key
	else if(first == 'B' && second == 'E')
	{
		return false;
	}

	// no key
	else if(first == ' ' && second == ' ')
	{
		return false;
	}

	else
	{
		return true;
	}
}

std::basic_string<TCHAR> CStateMenus::DescribeHex(char first, char second)
{
	std::basic_string<TCHAR> key;

	// BACKSPACE key
	if(first == '0' && second == '8')
	{
		key = _T("BACKSPACE");
	}

	// TAB key
	else if(first == '0' && second == '9')
	{
		key = _T("TAB");
	}

	// ENTER key
	else if(first == '0' && second == 'D')
	{
		key = _T("ENTER");
	}

	// SHIFT key
	else if(first == '1' && second == '0')
	{
		key = _T("SHIFT");
	}

	// CTRL key
	else if(first == '1' && second == '1')
	{
		key = _T("CTRL");
	}

	// ALT key
	else if(first == '1' && second == '2')
	{
		key = _T("ALT");
	}

	// ESC key
	else if(first == '1' && second == 'B')
	{
		key = _T("ESC");
	}

	// SPACEBAR
	else if(first == '2' && second == '0')
	{
		key = _T("SPACEBAR");
	}

	// LEFT ARROW key
	else if(first == '2' && second == '5')
	{
		key = _T("LEFT ARROW");
	}

	// UP ARROW key
	else if(first == '2' && second == '6')
	{
		key = _T("UP ARROW");
	}

	// RIGHT ARROW key
	else if(first == '2' && second == '7')
	{
		key = _T("RIGHT ARROW");
	}

	// DOWN ARROW key
	else if(first == '2' && second == '8')
	{
		key = _T("DOWN ARROW");
	}

	// + key
	else if(first == 'B' && second == 'B')
	{
		key = _T("+");
	}

	// , key
	else if(first == 'B' && second == 'C')
	{
		key = _T(",");
	}

	// . key
	else if(first == 'B' && second == 'E')
	{
		key = _T(".");
	}

	// - key
	else if(first == 'B' && second == 'D')
	{
		key = _T("-");
	}

	// no key
	else if(first == ' ' && second == ' ')
	{
		key = _T("");
	}

	return key;
}

char CStateMenus::HexToAscii(char first, char second)
{
	char hex[5], *stop;

	hex[0] = '0';
	hex[1] = 'x';
	hex[2] = first;
	hex[3] = second;
	hex[4] = 0;

	return strtol(hex, &stop, 16);
}

void CStateMenus::LoadSprites()
{
	CResourceMenus* resourceMenus = this->m_pApp->GetResourceMenus();

	switch(this->m_iSpriteSteps)
	{
	// mouse cursor
	case 1:
		this->m_pSpriteCursor = this->m_pResourceMenus->GetSpriteCursor();
		break;
	// background effects
#ifdef MENUS_FOG
	case 2:
		this->m_pSpriteFogBack = this->m_pResourceMenus->GetSpriteFogBack();
		break;
	case 3:
		this->m_pSpriteFogFront = this->m_pResourceMenus->GetSpriteFogFront();
		break;
#endif
	// background images
	case 4:
		this->m_pSpriteMenuBackground = this->m_pResourceMenus->GetSpriteMenuBackground();
		this->m_pSpriteStarsBack = this->m_pResourceMenus->GetSpriteMenuStarsBack();
		break;
	case 5:
		this->m_pSpriteStarsFront = this->m_pResourceMenus->GetSpriteMenuStarsFront();
		break;
	// background texts
	case 6:
		this->m_pSpriteMenuMain = this->m_pResourceMenus->GetSpriteMenuMain();
		break;
	case 7:
		this->m_pSpriteMenuOptions = this->m_pResourceMenus->GetSpriteMenuOptions();
		break;
	case 8:
		this->m_pSpriteMenuInput = this->m_pResourceMenus->GetSpriteMenuInput();
		break;
	case 9:
		this->m_pSpriteMenuAudio = this->m_pResourceMenus->GetSpriteMenuAudio();
		break;
	case 10:
		this->m_pSpriteMenuDisplay = this->m_pResourceMenus->GetSpriteMenuDisplay();
		break;
	case 11:
		this->m_pSpriteMenuHighscore = this->m_pResourceMenus->GetSpriteMenuHighscore();
		break;
	case 12:
		this->m_pSpriteMenuTitleMain = this->m_pResourceMenus->GetSpriteMenuTitleMain();
		this->m_pSpriteMenuTitleHighscore = this->m_pResourceMenus->GetSpriteMenuTitleHighscore();
		break;
		// bars
	case 13:
		this->m_pSpriteVideoAntialiasingBarBorder = this->m_pResourceMenus->GetSpriteVideoAntialiasingBarBorder();
		break;
	case 14:
		this->m_pSpriteVideoAntialiasingBar2x = this->m_pResourceMenus->GetSpriteVideoAntialiasingBar2x();
		break;
	case 15:
		this->m_pSpriteVideoAntialiasingBar46x = this->m_pResourceMenus->GetSpriteVideoAntialiasingBar46x();
		break;
	case 16:
		this->m_pSpriteVideoAntialiasingBar8x = this->m_pResourceMenus->GetSpriteVideoAntialiasingBar8x();
		break;
		// arrows
	case 17:
		this->m_pSpriteArrowInput = this->m_pResourceMenus->GetSpriteArrowInput();
		break;
	case 18:
		this->m_pSpriteArrowAntialiasingNormalLeft = this->m_pResourceMenus->GetSpriteArrowAntialiasingNormalLeft();
		break;
	case 19:
		this->m_pSpriteArrowAntialiasingNormalRight = this->m_pResourceMenus->GetSpriteArrowAntialiasingNormalRight();
		break;
	case 20:
		this->m_pSpriteArrowAntialiasingGlowLeft = this->m_pResourceMenus->GetSpriteArrowAntialiasingGlowLeft();
		break;
	case 21:
		this->m_pSpriteArrowAntialiasingGlowRight = this->m_pResourceMenus->GetSpriteArrowAntialiasingGlowRight();
		break;
	case 22:
		this->m_pSpriteArrowAntialiasingHideLeft = this->m_pResourceMenus->GetSpriteArrowAntialiasingHideLeft();
		break;
	case 23:
		this->m_pSpriteArrowAntialiasingHideRight = this->m_pResourceMenus->GetSpriteArrowAntialiasingHideRight();
		break;
		// on/off messages
	case 24:
		this->m_pSpriteSpecularLightingOn = this->m_pResourceMenus->GetSpriteSpecularLightingOn();
		break;
	case 25:
		this->m_pSpriteSpecularLightingOnGlow = this->m_pResourceMenus->GetSpriteSpecularLightingOnGlow();
		break;
	case 26:
		this->m_pSpriteSpecularLightingOff = this->m_pResourceMenus->GetSpriteSpecularLightingOff();
		break;
	case 27:
		this->m_pSpriteSpecularLightingOffGlow = this->m_pResourceMenus->GetSpriteSpecularLightingOffGlow();
		break;
		// message boxes
	case 28:
		this->m_pSpriteMessageInputEmpty = this->m_pResourceMenus->GetSpriteMessageInputEmpty();
		break;
	case 29:
		this->m_pSpriteMessageInputKey = this->m_pResourceMenus->GetSpriteMessageInputKey();
		break;
	case 30:
		this->m_pSpriteMessageRestart = this->m_pResourceMenus->GetSpriteMessageRestart();
		break;
	case 31:
		this->m_pSpriteMessageOK1 = this->m_pResourceMenus->GetSpriteMessageOK1();
		break;
	case 32:
		this->m_pSpriteMessageOK2 = this->m_pResourceMenus->GetSpriteMessageOK2();
		break;
		// underlines
	case 33:
		this->m_pSpriteUnderlineAudio = this->m_pResourceMenus->GetSpriteUnderlineAudio();
		break;
	case 34:
		this->m_pSpriteUnderlineBack = this->m_pResourceMenus->GetSpriteUnderlineBack();
		break;
	case 35:
#ifdef MENU_CREDITS
		this->m_pSpriteUnderlineCredits = this->m_pResourceMenus->GetSpriteUnderlineCredits();
#endif
		break;
	case 36:
		this->m_pSpriteUnderlineDefault = this->m_pResourceMenus->GetSpriteUnderlineDefault();
		break;
	case 37:
		this->m_pSpriteUnderlineDisplay = this->m_pResourceMenus->GetSpriteUnderlineDisplay();
		break;
	case 38:
		this->m_pSpriteUnderlineExit = this->m_pResourceMenus->GetSpriteUnderlineExit();
		break;
	case 39:
		this->m_pSpriteUnderlineHighscore = this->m_pResourceMenus->GetSpriteUnderlineHighscore();
		break;
	case 40:
		this->m_pSpriteUnderlineInput = this->m_pResourceMenus->GetSpriteUnderlineInput();
		break;
	case 41:
		this->m_pSpriteUnderlineNewgame = this->m_pResourceMenus->GetSpriteUnderlineNewgame();
		break;
	case 42:
		this->m_pSpriteUnderlineOptions = this->m_pResourceMenus->GetSpriteUnderlineOptions();
		break;
		// credits
	case 43:
#ifdef MENU_CREDITS
		this->m_pSpriteCreditsBackLayer = this->m_pResourceMenus->GetSpriteCreditsBackLayer();
#endif
		break;
	case 44:
#ifdef MENU_CREDITS
		this->m_pSpriteCreditsText = this->m_pResourceMenus->GetSpriteCreditsText();
#endif
		break;
		//game version
	case 45:
		this->m_pSpriteVersion = this->m_pResourceMenus->GetSpriteVersion();
		break;
		// audio bar border
	case 46:
		this->m_pSpriteAudioBarBorder = this->m_pResourceMenus->GetSpriteAudioBarBorder();
		break;
		// audio bar meter
	case 47:
		this->m_pSpriteAudioBarMeter = this->m_pResourceMenus->GetSpriteAudioBarMeter();
		break;
	}
}

HRESULT CStateMenus::LoadMeshes()
{
	CResourceMenus* resourceMenus = this->m_pApp->GetResourceMenus();

	if (this->m_pXFile == NULL)
	{
		this->m_pXFile = new CXFileContainer[LOAD_MESH_MENUS_MAX];

		if (!this->m_pXFile)
		{
			return E_OUTOFMEMORY;
		}
	}

	switch(this->m_iMeshSteps)
	{
	/* LETTERS */

	case 1:
		this->m_pXFile[LOAD_MESH_MENUS_A] = this->m_pResourceMenus->GetMeshLetterA();
		break;
	case 2:
		this->m_pXFile[LOAD_MESH_MENUS_B] = this->m_pResourceMenus->GetMeshLetterB();
		break;
	case 3:
		this->m_pXFile[LOAD_MESH_MENUS_C] = this->m_pResourceMenus->GetMeshLetterC();
		break;
	case 4:
		this->m_pXFile[LOAD_MESH_MENUS_D] = this->m_pResourceMenus->GetMeshLetterD();
		break;
	case 5:
		this->m_pXFile[LOAD_MESH_MENUS_E] = this->m_pResourceMenus->GetMeshLetterE();
		break;
	case 6:
		this->m_pXFile[LOAD_MESH_MENUS_F] = this->m_pResourceMenus->GetMeshLetterF();
		break;
	case 7:
		this->m_pXFile[LOAD_MESH_MENUS_G] = this->m_pResourceMenus->GetMeshLetterG();
		break;
	case 8:
		this->m_pXFile[LOAD_MESH_MENUS_H] = this->m_pResourceMenus->GetMeshLetterH();
		break;
	case 9:
		this->m_pXFile[LOAD_MESH_MENUS_I] = this->m_pResourceMenus->GetMeshLetterI();
		break;
	case 10:
		this->m_pXFile[LOAD_MESH_MENUS_J] = this->m_pResourceMenus->GetMeshLetterJ();
		break;
	case 11:
		this->m_pXFile[LOAD_MESH_MENUS_K] = this->m_pResourceMenus->GetMeshLetterK();
		break;
	case 12:
		this->m_pXFile[LOAD_MESH_MENUS_L] = this->m_pResourceMenus->GetMeshLetterL();
		break;
	case 13:
		this->m_pXFile[LOAD_MESH_MENUS_M] = this->m_pResourceMenus->GetMeshLetterM();
		break;
	case 14:
		this->m_pXFile[LOAD_MESH_MENUS_N] = this->m_pResourceMenus->GetMeshLetterN();
		break;
	case 15:
		this->m_pXFile[LOAD_MESH_MENUS_O] = this->m_pResourceMenus->GetMeshLetterO();
		break;
	case 16:
		this->m_pXFile[LOAD_MESH_MENUS_P] = this->m_pResourceMenus->GetMeshLetterP();
		break;
	case 17:
		this->m_pXFile[LOAD_MESH_MENUS_Q] = this->m_pResourceMenus->GetMeshLetterQ();
		break;
	case 18:
		this->m_pXFile[LOAD_MESH_MENUS_R] = this->m_pResourceMenus->GetMeshLetterR();
		break;
	case 19:
		this->m_pXFile[LOAD_MESH_MENUS_S] = this->m_pResourceMenus->GetMeshLetterS();
		break;
	case 20:
		this->m_pXFile[LOAD_MESH_MENUS_T] = this->m_pResourceMenus->GetMeshLetterT();
		break;
	case 21:
		this->m_pXFile[LOAD_MESH_MENUS_U] = this->m_pResourceMenus->GetMeshLetterU();
		break;
	case 22:
		this->m_pXFile[LOAD_MESH_MENUS_V] = this->m_pResourceMenus->GetMeshLetterV();
		break;
	case 23:
		this->m_pXFile[LOAD_MESH_MENUS_W] = this->m_pResourceMenus->GetMeshLetterW();
		break;
	case 24:
		this->m_pXFile[LOAD_MESH_MENUS_X] = this->m_pResourceMenus->GetMeshLetterX();
		break;
	case 25:
		this->m_pXFile[LOAD_MESH_MENUS_Y] = this->m_pResourceMenus->GetMeshLetterY();
		break;
	case 26:
		this->m_pXFile[LOAD_MESH_MENUS_Z] = this->m_pResourceMenus->GetMeshLetterZ();
		break;

	/* NUMBERS */

	case 27:
		this->m_pXFile[LOAD_MESH_MENUS_0] = this->m_pResourceMenus->GetMeshNumber0();
		break;
	case 28:
		this->m_pXFile[LOAD_MESH_MENUS_1] = this->m_pResourceMenus->GetMeshNumber1();
		break;
	case 29:
		this->m_pXFile[LOAD_MESH_MENUS_2] = this->m_pResourceMenus->GetMeshNumber2();
		break;
	case 30:
		this->m_pXFile[LOAD_MESH_MENUS_3] = this->m_pResourceMenus->GetMeshNumber3();
		break;
	case 31:
		this->m_pXFile[LOAD_MESH_MENUS_4] = this->m_pResourceMenus->GetMeshNumber4();
		break;
	case 32:
		this->m_pXFile[LOAD_MESH_MENUS_5] = this->m_pResourceMenus->GetMeshNumber5();
		break;
	case 33:
		this->m_pXFile[LOAD_MESH_MENUS_6] = this->m_pResourceMenus->GetMeshNumber6();
		break;
	case 34:
		this->m_pXFile[LOAD_MESH_MENUS_7] = this->m_pResourceMenus->GetMeshNumber7();
		break;
	case 35:
		this->m_pXFile[LOAD_MESH_MENUS_8] = this->m_pResourceMenus->GetMeshNumber8();
		break;
	case 36:
		this->m_pXFile[LOAD_MESH_MENUS_9] = this->m_pResourceMenus->GetMeshNumber9();
		break;

	case 37:
#ifdef MENUS_PLANET
		this->m_pXFile[LOAD_MESH_MENUS_PLANET] = this->m_pResourceMenus->GetMeshMenusPlanet();
#endif
		break;
	}

	return S_OK;
}

void CStateMenus::ChangeSpecularity()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(mtrl) );

	switch( this->GetApp()->GetConfig().GetSpecularLighting() )
	{
	case CConfig::eSPECULAR_LIGHTING_OFF:

		mtrl.Diffuse = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);
		mtrl.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

		this->GetApp()->GetDevice()->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
		this->GetApp()->GetDevice()->SetMaterial( &mtrl );

		break;

	case CConfig::eSPECULAR_LIGHTING_ON:

		mtrl.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		mtrl.Power = 20;

		this->GetApp()->GetDevice()->SetRenderState( D3DRS_SPECULARENABLE, TRUE );

		this->GetApp()->GetDevice()->SetMaterial( &mtrl );
		this->GetApp()->GetDevice()->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

		break;
	}
}

#ifdef SHADOWS
CShadowVolume* CStateMenus::GetShadowVolumes()
{
	this->BuildShadowVolumes();
	return this->m_pShadowVolumes;
}

HRESULT CStateMenus::BuildShadowVolumes()
{
	HRESULT hres;

	if( this->m_pShadowVolumes )
	{
		delete [] this->m_pShadowVolumes;
		this->m_pShadowVolumes = NULL;
	}

	int iLightCount = this->GetLights()->GetLightCount();
	int* iLightIndex = this->GetLights()->GetLightIndex();

	// each shadow casting mesh will be processed with each light source
	// so we have (lights * meshes) number of shadow volumes
	this->m_pShadowVolumes = new CShadowVolume[iLightCount * MESH_SHADOW_COUNT_MENUS];

	D3DXMATRIX matrix;
	D3DXVECTOR3 vecLight;

	int iShadowVolumeIndex = 0;

	// process all the active light sources
	// for each object we transform the light into model space
	for(int i = 0; i < iLightCount; i++)
	{
		D3DLIGHT9 light;

		// get the current light
		this->GetApp()->GetDevice()->GetLight(iLightIndex[i], &light);

		// light source is point-type
		if ( light.Type == D3DLIGHT_POINT )
		{
			for(int j = 0; j < MESH_SHADOW_COUNT_MENUS; j++)
			{
				//calculate the world->model space transform matrix
				switch(j)
				{
				// planet object
				case 0:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pPlanet->GetWorldMatrix() );
					break;

				// player object
				case 1:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pPlayer->GetWorldMatrix() );
					break;

				// drone 1 object
				case 2:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pDrone1->GetWorldMatrix() );
					break;

				// drone 2 object
				case 3:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pDrone2->GetWorldMatrix() );
					break;

				// sniper 1 object
				case 4:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pSniper1->GetWorldMatrix() );
					break;

				// sniper 2 object
				case 5:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pSniper2->GetWorldMatrix() );
					break;

				// boss 1 object
				case 6:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pBoss1->GetWorldMatrix() );
					break;
				}

				//multiply the lights position, to go from world->model space
				vecLight.x = light.Position.x * matrix._11 + light.Position.y * matrix._21 + light.Position.z * matrix._31 + matrix._41;
				vecLight.y = light.Position.x * matrix._12 + light.Position.y * matrix._22 + light.Position.z * matrix._32 + matrix._42;
				vecLight.z = light.Position.x * matrix._13 + light.Position.y * matrix._23 + light.Position.z * matrix._33 + matrix._43;

				// build shadow volume

				this->m_pShadowVolumes[iShadowVolumeIndex].Reset();

				switch(j)
				{
				// planet object
				case 0:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pPlanet->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pPlanet->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					break;

				// player object
				case 1:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pPlayer->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pPlayer->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}
					
					break;

				// drone 1 object
				case 2:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pDrone1->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pDrone1->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}
					
					break;

				// drone 2 object
				case 3:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pDrone2->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pDrone2->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}
					
					break;

				// sniper 1 object
				case 4:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pSniper1->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pSniper1->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					break;

				// sniper 2 object
				case 5:
					
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pSniper2->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pSniper2->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					break;

				// boss 1 object
				case 6:
					
					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pBoss1->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pBoss1->GetMesh(), vecLight );
					if(FAILED(hres))
					{
						return hres;
					}

					break;
				}

				iShadowVolumeIndex++;
			}
		}
	}

	this->m_iShadowCount = iShadowVolumeIndex;

	delete [] iLightIndex;
	iLightIndex = NULL;

	return S_OK;
}
#endif