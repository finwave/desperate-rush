#include "TheApp.h"
#include "TextUtils.h"
#include "ResourceMenus.h"

CResourceMenus::CResourceMenus()
{
	this->m_bZipFileStepLoaded = false;
	this->m_bipFileStepWaited = false;
	this->m_bIsLoadingScreenSprites = false;
	this->m_bMenusShipsLoaded = false;
	this->m_bMenusTextLoaded = false;
}

void CResourceMenus::Init(CTheApp* pApp, CZipManager* pZipManager)
{
	CResources::Init(pApp, pZipManager);

	this->m_iMeshStepsMax += MESH_MENUS_SHIPS + MESH_MENUS_TEXT;
	this->m_iSpriteStepsMax += SPRITE_MENUS;

	this->m_fDepthMenuText = 0.05f;
	this->m_fDepthMenuUnderline = 0.1f;
}

void CResourceMenus::Release(void)
{
	/* MESHES */

#ifdef MENUS_PLANET
	m_MeshMenusPlanet.Release();
#endif

	m_MeshLetterA.Release();
	m_MeshLetterB.Release();
	m_MeshLetterC.Release();
	m_MeshLetterD.Release();
	m_MeshLetterE.Release();
	m_MeshLetterF.Release();
	m_MeshLetterG.Release();
	m_MeshLetterH.Release();
	m_MeshLetterI.Release();
	m_MeshLetterJ.Release();
	m_MeshLetterK.Release();
	m_MeshLetterL.Release();
	m_MeshLetterM.Release();
	m_MeshLetterN.Release();
	m_MeshLetterO.Release();
	m_MeshLetterP.Release();
	m_MeshLetterQ.Release();
	m_MeshLetterR.Release();
	m_MeshLetterS.Release();
	m_MeshLetterT.Release();
	m_MeshLetterU.Release();
	m_MeshLetterV.Release();
	m_MeshLetterW.Release();
	m_MeshLetterX.Release();
	m_MeshLetterY.Release();
	m_MeshLetterZ.Release();

	m_MeshNumber0.Release();
	m_MeshNumber1.Release();
	m_MeshNumber2.Release();
	m_MeshNumber3.Release();
	m_MeshNumber4.Release();
	m_MeshNumber5.Release();
	m_MeshNumber6.Release();
	m_MeshNumber7.Release();
	m_MeshNumber8.Release();
	m_MeshNumber9.Release();

	/** SPRITES **/

	// Loading Screen

	if (m_pSpriteLoadingScreen)
	{
		m_pSpriteLoadingScreen->Release();
		delete m_pSpriteLoadingScreen;
		m_pSpriteLoadingScreen = NULL;
	}
	if (m_pSpriteLoadingBar)
	{
		for (unsigned int i = 0; i < SPRITE_LOADING_BAR; i++)
		{
			(this->m_pSpriteLoadingBar + i)->Release();
		}
		delete[] this->m_pSpriteLoadingBar;
		this->m_pSpriteLoadingBar = NULL;
	}

	// Menus

	if (m_pSpriteCursor)
	{
		m_pSpriteCursor->Release();
		delete m_pSpriteCursor;
		m_pSpriteCursor = NULL;
	}
#ifdef MENUS_FOG
	if (m_pSpriteFogBack)
	{
		m_pSpriteFogBack->Release();
		delete m_pSpriteFogBack;
		m_pSpriteFogBack = NULL;
	}
	if (m_pSpriteFogFront)
	{
		m_pSpriteFogFront->Release();
		delete m_pSpriteFogFront;
		m_pSpriteFogFront = NULL;
	}
#endif
	if (m_pSpriteMenuBackground)
	{
		m_pSpriteMenuBackground->Release();
		delete m_pSpriteMenuBackground;
		m_pSpriteMenuBackground = NULL;
	}
	if (m_pSpriteMenuStarsBack)
	{
		m_pSpriteMenuStarsBack->Release();
		delete m_pSpriteMenuStarsBack;
		m_pSpriteMenuStarsBack = NULL;
	}
	if (m_pSpriteMenuStarsFront)
	{
		m_pSpriteMenuStarsFront->Release();
		delete m_pSpriteMenuStarsFront;
		m_pSpriteMenuStarsFront = NULL;
	}

	if (m_pSpriteMenuTitleMain)
	{
		m_pSpriteMenuTitleMain->Release();
		delete m_pSpriteMenuTitleMain;
		m_pSpriteMenuTitleMain = NULL;
	}
	if (m_pSpriteMenuTitleHighscore)
	{
		m_pSpriteMenuTitleHighscore->Release();
		delete m_pSpriteMenuTitleHighscore;
		m_pSpriteMenuTitleHighscore = NULL;
	}

	if (m_pSpriteMenuMain)
	{
		m_pSpriteMenuMain->Release();
		delete m_pSpriteMenuMain;
		m_pSpriteMenuMain = NULL;
	}
	if (m_pSpriteMenuOptions)
	{
		m_pSpriteMenuOptions->Release();
		delete m_pSpriteMenuOptions;
		m_pSpriteMenuOptions = NULL;
	}
	if (m_pSpriteMenuInput)
	{
		m_pSpriteMenuInput->Release();
		delete m_pSpriteMenuInput;
		m_pSpriteMenuInput = NULL;
	}
	if (m_pSpriteMenuAudio)
	{
		m_pSpriteMenuAudio->Release();
		delete m_pSpriteMenuAudio;
		m_pSpriteMenuAudio = NULL;
	}
	if (m_pSpriteMenuDisplay)
	{
		m_pSpriteMenuDisplay->Release();
		delete m_pSpriteMenuDisplay;
		m_pSpriteMenuDisplay = NULL;
	}
	if (m_pSpriteMenuHighscore)
	{
		m_pSpriteMenuHighscore->Release();
		delete m_pSpriteMenuHighscore;
		m_pSpriteMenuHighscore = NULL;
	}

	if (m_pSpriteVideoAntialiasingBarBorder)
	{
		m_pSpriteVideoAntialiasingBarBorder->Release();
		delete m_pSpriteVideoAntialiasingBarBorder;
		m_pSpriteVideoAntialiasingBarBorder = NULL;
	}
	if (m_pSpriteVideoAntialiasingBar2x)
	{
		m_pSpriteVideoAntialiasingBar2x->Release();
		delete m_pSpriteVideoAntialiasingBar2x;
		m_pSpriteVideoAntialiasingBar2x = NULL;
	}
	if (m_pSpriteVideoAntialiasingBarBorder)
	{
		m_pSpriteVideoAntialiasingBar46x->Release();
		delete m_pSpriteVideoAntialiasingBar46x;
		m_pSpriteVideoAntialiasingBar46x = NULL;
	}
	if (m_pSpriteVideoAntialiasingBar8x)
	{
		m_pSpriteVideoAntialiasingBar8x->Release();
		delete m_pSpriteVideoAntialiasingBar8x;
		m_pSpriteVideoAntialiasingBar8x = NULL;
	}

	if (m_pSpriteArrowInput)
	{
		m_pSpriteArrowInput->Release();
		delete m_pSpriteArrowInput;
		m_pSpriteArrowInput = NULL;
	}
	if (m_pSpriteArrowAntialiasingNormalLeft)
	{
		m_pSpriteArrowAntialiasingNormalLeft->Release();
		delete m_pSpriteArrowAntialiasingNormalLeft;
		m_pSpriteArrowAntialiasingNormalLeft = NULL;
	}
	if (m_pSpriteArrowAntialiasingNormalRight)
	{
		m_pSpriteArrowAntialiasingNormalRight->Release();
		delete m_pSpriteArrowAntialiasingNormalRight;
		m_pSpriteArrowAntialiasingNormalRight = NULL;
	}
	if (m_pSpriteArrowAntialiasingGlowLeft)
	{
		m_pSpriteArrowAntialiasingGlowLeft->Release();
		delete m_pSpriteArrowAntialiasingGlowLeft;
		m_pSpriteArrowAntialiasingGlowLeft = NULL;
	}
	if (m_pSpriteArrowAntialiasingGlowRight)
	{
		m_pSpriteArrowAntialiasingGlowRight->Release();
		delete m_pSpriteArrowAntialiasingGlowRight;
		m_pSpriteArrowAntialiasingGlowRight = NULL;
	}
	if (m_pSpriteArrowAntialiasingHideLeft)
	{
		m_pSpriteArrowAntialiasingHideLeft->Release();
		delete m_pSpriteArrowAntialiasingHideLeft;
		m_pSpriteArrowAntialiasingHideLeft = NULL;
	}
	if (m_pSpriteArrowAntialiasingHideRight)
	{
		m_pSpriteArrowAntialiasingHideRight->Release();
		delete m_pSpriteArrowAntialiasingHideRight;
		m_pSpriteArrowAntialiasingHideRight = NULL;
	}

	if (m_pSpriteSpecularLightingOn)
	{
		m_pSpriteSpecularLightingOn->Release();
		delete m_pSpriteSpecularLightingOn;
		m_pSpriteSpecularLightingOn = NULL;
	}
	if (m_pSpriteSpecularLightingOnGlow)
	{
		m_pSpriteSpecularLightingOnGlow->Release();
		delete m_pSpriteSpecularLightingOnGlow;
		m_pSpriteSpecularLightingOnGlow = NULL;
	}
	if (m_pSpriteSpecularLightingOff)
	{
		m_pSpriteSpecularLightingOff->Release();
		delete m_pSpriteSpecularLightingOff;
		m_pSpriteSpecularLightingOff = NULL;
	}
	if (m_pSpriteSpecularLightingOffGlow)
	{
		m_pSpriteSpecularLightingOffGlow->Release();
		delete m_pSpriteSpecularLightingOffGlow;
		m_pSpriteSpecularLightingOffGlow = NULL;
	}

	if (m_pSpriteMessageInputEmpty)
	{
		m_pSpriteMessageInputEmpty->Release();
		delete m_pSpriteMessageInputEmpty;
		m_pSpriteMessageInputEmpty = NULL;
	}
	if (m_pSpriteMessageInputKey)
	{
		m_pSpriteMessageInputKey->Release();
		delete m_pSpriteMessageInputKey;
		m_pSpriteMessageInputKey = NULL;
	}
	if (m_pSpriteMessageRestart)
	{
		m_pSpriteMessageRestart->Release();
		delete m_pSpriteMessageRestart;
		m_pSpriteMessageRestart = NULL;
	}
	if (m_pSpriteMessageOK1)
	{
		m_pSpriteMessageOK1->Release();
		delete m_pSpriteMessageOK1;
		m_pSpriteMessageOK1 = NULL;
	}
	if (m_pSpriteMessageOK2)
	{
		m_pSpriteMessageOK2->Release();
		delete m_pSpriteMessageOK2;
		m_pSpriteMessageOK2 = NULL;
	}

	if (m_pSpriteUnderlineAudio)
	{
		m_pSpriteUnderlineAudio->Release();
		delete m_pSpriteUnderlineAudio;
		m_pSpriteUnderlineAudio = NULL;
	}
	if (m_pSpriteUnderlineBack)
	{
		m_pSpriteUnderlineBack->Release();
		delete m_pSpriteUnderlineBack;
		m_pSpriteUnderlineBack = NULL;
	}
	if (m_pSpriteUnderlineDefault)
	{
		m_pSpriteUnderlineDefault->Release();
		delete m_pSpriteUnderlineDefault;
		m_pSpriteUnderlineDefault = NULL;
	}
	if (m_pSpriteUnderlineDisplay)
	{
		m_pSpriteUnderlineDisplay->Release();
		delete m_pSpriteUnderlineDisplay;
		m_pSpriteUnderlineDisplay = NULL;
	}
	if (m_pSpriteUnderlineExit)
	{
		m_pSpriteUnderlineExit->Release();
		delete m_pSpriteUnderlineExit;
		m_pSpriteUnderlineExit = NULL;
	}
	if (m_pSpriteUnderlineHighscore)
	{
		m_pSpriteUnderlineHighscore->Release();
		delete m_pSpriteUnderlineHighscore;
		m_pSpriteUnderlineHighscore = NULL;
	}
	if (m_pSpriteUnderlineInput)
	{
		m_pSpriteUnderlineInput->Release();
		delete m_pSpriteUnderlineInput;
		m_pSpriteUnderlineInput = NULL;
	}
	if (m_pSpriteUnderlineNewgame)
	{
		m_pSpriteUnderlineNewgame->Release();
		delete m_pSpriteUnderlineNewgame;
		m_pSpriteUnderlineNewgame = NULL;
	}
	if (m_pSpriteUnderlineOptions)
	{
		m_pSpriteUnderlineOptions->Release();
		delete m_pSpriteUnderlineOptions;
		m_pSpriteUnderlineOptions = NULL;
	}

#ifdef MENU_CREDITS
	if (m_pSpriteUnderlineCredits)
	{
		m_pSpriteUnderlineCredits->Release();
		delete m_pSpriteUnderlineCredits;
		m_pSpriteUnderlineCredits = NULL;
	}
	if (m_pSpriteCreditsBackLayer)
	{
		m_pSpriteCreditsBackLayer->Release();
		delete m_pSpriteCreditsBackLayer;
		m_pSpriteCreditsBackLayer = NULL;
	}
	if (m_pSpriteCreditsText)
	{
		m_pSpriteCreditsText->Release();
		delete m_pSpriteCreditsText;
		m_pSpriteCreditsText = NULL;
	}
#endif

	if (m_pSpriteAudioBarBorder)
	{
		m_pSpriteAudioBarBorder->Release();
		delete m_pSpriteAudioBarBorder;
		m_pSpriteAudioBarBorder = NULL;
	}
	if (m_pSpriteAudioBarMeter)
	{
		for (int i = 0; i < SPRITE_MENUS_AUDIO_BAR; i++)
		{
			m_pSpriteAudioBarMeter[i].Release();
		}

		delete[] m_pSpriteAudioBarMeter;
		m_pSpriteAudioBarMeter = NULL;
	}

	if (m_pSpriteVersion)
	{
		m_pSpriteVersion->Release();
		delete m_pSpriteVersion;
		m_pSpriteVersion = NULL;
	}

	// PARENT CLASS

	CResources::Release();
}

HRESULT CResourceMenus::Load()
{
	if (this->m_bResourcesLoaded)
	{
		return S_OK;
	}

	HRESULT hres = S_OK;
	this->m_iResourcesLoadStepCounter++;

	if (this->m_iResourcesLoadStepCounter >= LOAD_STEPS_WAIT_DEFAULT)
	{
		this->m_bIsLoadWaitCycle = true;
		this->m_iResourcesLoadStepCounter = 0;
	}

	// unpacking zip files
	if (!this->m_bZipFileStepLoaded)
	{
		if (!this->m_pZipManager->IsExistResourceFolder("models/menus") ||
			!this->m_pZipManager->IsExistResourceFolder("textures/menus"))
		{
			this->m_pZipManager->UnpackMasterZipFileWithTarget("data_2", "data2");
			this->m_pZipManager->UnpackChildZipFile("data2");
		}

		this->m_bZipFileStepLoaded = true;
		this->m_bIsLoadWaitCycle = true;

		return hres;
	}

	// child zip file
	if (!this->m_bipFileStepWaited)
	{
		this->m_bipFileStepWaited = true;
		this->m_iResourcesLoadStepCounter = 0;

		return hres;
	}

	// load menu meshes
	if (!this->m_bMenusShipsLoaded)
	{
		hres = this->LoadMeshMenusShips();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_MENUS_SHIPS)
		{
			this->m_bMenusShipsLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	else if (!this->m_bMenusTextLoaded)
	{
		hres = this->LoadMeshMenusText();
		this->m_iMeshSteps++;

		if (this->m_iMeshSteps > MESH_MENUS_TEXT)
		{
			this->m_bMenusTextLoaded = true;
			this->m_iMeshSteps = 1;
		}
	}
	// load menu sprites
	else if (this->m_iSpriteSteps <= this->m_iSpriteStepsMax)
	{
		hres = this->LoadSpriteMenus();
		this->m_iSpriteSteps++;
	}
	else
	{
		this->InitMeshMenus();
		this->m_bResourcesLoaded = true;
	}

	return hres;
}

HRESULT CResourceMenus::LoadMeshMenusShips()
{
	CXFileContainer xFile;

	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	case 1:
		hres = xFile.Create(this->m_pDevice, "player.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: player.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_PLAYER_FRAME, MODEL_TYPE_PLAYER);
		}

		break;

	case 2:

		hres = xFile.Create(this->m_pDevice, "drone.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: drone.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ENEMY_DRONE_1, MODEL_TYPE_ENEMY);
		}

		break;

	case 3:

		hres = xFile.Create(this->m_pDevice, "sniper.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: sniper.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ENEMY_SNIPER_1, MODEL_TYPE_ENEMY);
		}

		break;

	case 4:

		hres = xFile.Create(this->m_pDevice, "roller.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: roller.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_ENEMY_ROLLER_1, MODEL_TYPE_ENEMY);
		}

		break;

	case 5:

		hres = xFile.Create(this->m_pDevice, "boss_1_base.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: boss_1_base.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_BOSS_1_FRAME, MODEL_TYPE_BOSS);
		}

		break;

	case 6:

		hres = xFile.Create(this->m_pDevice, "boss_1_scatter.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: boss_1_scatter.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(xFile, MODEL_GAME_BOSS_1_SCATTER, MODEL_TYPE_BOSS);
		}

		break;

#ifdef MENUS_PLANET
	case 7:

		hres = this->m_MeshMenusPlanet.Create(this->m_pDevice, "planet.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: planet.x\n");
			std::cout << str << std::endl;
		}
		break;
#endif
	}

	return hres;
}

HRESULT CResourceMenus::LoadMeshMenusText()
{
	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	// LETTERS
	case 1:
		hres = m_MeshLetterA.Create(
			this->m_pDevice, "A_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: A_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 2:
		hres = m_MeshLetterB.Create(
			this->m_pDevice, "B_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: B_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 3:
		hres = m_MeshLetterC.Create(
			this->m_pDevice, "C_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "C_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 4:
		hres = m_MeshLetterD.Create(
			this->m_pDevice, "D_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "D_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 5:
		hres = m_MeshLetterE.Create(
			this->m_pDevice, "E_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "E_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 6:
		hres = m_MeshLetterF.Create(
			this->m_pDevice, "F_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "F_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 7:
		hres = m_MeshLetterG.Create(
			this->m_pDevice, "G_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: G_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 8:
		hres = m_MeshLetterH.Create(
			this->m_pDevice, "H_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: H_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 9:
		hres = m_MeshLetterI.Create(
			this->m_pDevice, "I_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: I_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 10:
		hres = m_MeshLetterJ.Create(
			this->m_pDevice, "J_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: J_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 11:
		hres = m_MeshLetterK.Create(
			this->m_pDevice, "K_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: K_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 12:
		hres = m_MeshLetterL.Create(
			this->m_pDevice, "L_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: L_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 13:
		hres = m_MeshLetterM.Create(
			this->m_pDevice, "M_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: M_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 14:
		hres = m_MeshLetterN.Create(
			this->m_pDevice, "N_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: N_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 15:
		hres = m_MeshLetterO.Create(
			this->m_pDevice, "O_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: O_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 16:
		hres = m_MeshLetterP.Create(
			this->m_pDevice, "P_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: P_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 17:
		hres = m_MeshLetterQ.Create(
			this->m_pDevice, "Q_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: Q_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 18:
		hres = m_MeshLetterR.Create(
			this->m_pDevice, "R_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: R_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 19:
		hres = m_MeshLetterS.Create(
			this->m_pDevice, "S_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: S_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 20:
		hres = m_MeshLetterT.Create(
			this->m_pDevice, "T_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: T_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 21:
		hres = m_MeshLetterU.Create(
			this->m_pDevice, "U_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: U_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 22:
		hres = m_MeshLetterV.Create(
			this->m_pDevice, "V_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: V_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 23:
		hres = m_MeshLetterW.Create(
			this->m_pDevice, "W_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: W_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 24:
		hres = m_MeshLetterX.Create(
			this->m_pDevice, "X_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: X_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 25:
		hres = m_MeshLetterY.Create(
			this->m_pDevice, "Y_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: Y_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 26:
		hres = m_MeshLetterZ.Create(
			this->m_pDevice, "Z_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: Z_white.x\n");
			std::cout << str << std::endl;
		}
		break;

	// NUMBERS
	case 27:
		hres = m_MeshNumber0.Create(
			this->m_pDevice, "0_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 0_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 28:
		hres = m_MeshNumber1.Create(
			this->m_pDevice, "1_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "1_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 29:
		hres = m_MeshNumber2.Create(
			this->m_pDevice, "2_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 2_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 30:
		hres = m_MeshNumber3.Create(
			this->m_pDevice, "3_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 3_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 31:
		hres = m_MeshNumber4.Create(
			this->m_pDevice, "4_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 4_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 32:
		hres = m_MeshNumber5.Create(
			this->m_pDevice, "5_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 5_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 33:
		hres = m_MeshNumber6.Create(
			this->m_pDevice, "6_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 6_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 34:
		hres = m_MeshNumber7.Create(
			this->m_pDevice, "7_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 7_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 35:
		hres = m_MeshNumber8.Create(
			this->m_pDevice, "8_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 8_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	case 36:
		hres = m_MeshNumber9.Create(
			this->m_pDevice, "9_white.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: 9_white.x\n");
			std::cout << str << std::endl;
		}
		break;
	}

	return hres;
}

HRESULT CResourceMenus::LoadSpriteLoadingScreen()
{
	if (this->m_bIsLoadingScreenSprites)
	{
		return S_OK;
	}

	HRESULT hres;

	// Unpack "loading" ZIP resource file.
	if (!this->m_pZipManager->IsExistResourceFolder("textures/loading"))
	{
		this->m_pZipManager->UnpackMasterZipFileWithName("data_1");
	}

	// BACKGROUND

	// Background image

	this->m_pSpriteLoadingScreen = new CSprite;

	if (!this->m_pSpriteLoadingScreen)
	{
		return E_OUTOFMEMORY;
	}

	hres = this->m_pSpriteLoadingScreen->Create(
		"loading_background.png", m_pDevice, 0.3f);

	if (FAILED(hres))
	{
		return hres;
	}

	// LOADING BAR

	// loading bar fill-up

	std::string fileName;
	std::string sNumber;

	this->m_pSpriteLoadingBar = new CSprite[SPRITE_LOADING_BAR];

	if (!this->m_pSpriteLoadingBar)
	{
		return E_OUTOFMEMORY;
	}

	for (int i = 0; i < SPRITE_LOADING_BAR - 1; i++)
	{
		sNumber = TextUtils::IntToString(i + 1);

		fileName = "loading_meter_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteLoadingBar + i)->Create(
			fileName, m_pDevice, 0.2f);

		if (FAILED(hres))
		{
			return hres;
		}
	}

	// loading bar outline

	hres = this->m_pSpriteLoadingBar[SPRITE_LOADING_BAR - 1].Create(
		"loading_bar.png", m_pDevice, 0.2f);

	if (hres != S_OK)
	{
		return hres;
	}

	this->m_bIsLoadingScreenSprites = true;
	return S_OK;
}

HRESULT CResourceMenus::LoadSpriteMenus()
{
	HRESULT hres = S_OK;

	switch (this->m_iSpriteSteps)
	{
	// mouse cursor
	case 1:

		this->m_pSpriteCursor = new CSprite;

		if (!this->m_pSpriteCursor)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteCursor->Create(
			"cursor_blue.png", m_pDevice, 0.01f);

		break;

	// background effects
	case 2:

#ifdef MENUS_FOG
		this->m_pSpriteFogBack = new CSpriteScrolling;

		if (!this->m_pSpriteFogBack)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteFogBack->Create(
			"fog_back.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, 0.1f, 2048, 768, 0, 0, 1, 3);
#endif
		break;

	case 3:

#ifdef MENUS_FOG
		this->m_pSpriteFogFront = new CSpriteScrolling;

		if (!this->m_pSpriteFogFront)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteFogFront->Create(
			"fog_front.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, 0.1f, 2048, 768, -150, 0, 1, 3);
#endif
		break;

	// background images
	case 4:
	{
		float backgroundDepth = 1.0f;
		this->m_pSpriteMenuBackground = new CSprite;

		if (!this->m_pSpriteMenuBackground)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuBackground->Create(
			"background_static.png", m_pDevice, backgroundDepth);

		backgroundDepth = 0.99f;
		this->m_pSpriteMenuStarsBack = new CSpriteScrolling;

		if (!this->m_pSpriteMenuStarsBack)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuStarsBack->Create(
			"background_stars_back.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, backgroundDepth, 2048, 768, 0, 0, 1, 10);
	}
		break;

	case 5:
	{
		float backgroundDepth = 0.98f;
		this->m_pSpriteMenuStarsFront = new CSpriteScrolling;

		if (!this->m_pSpriteMenuStarsFront)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuStarsFront->Create(
			"background_stars_front.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, backgroundDepth, 2048, 768, -50, 0, 1, 8);
	}
		break;

	// background texts
	case 6:

		this->m_pSpriteMenuMain = new CSprite;

		if (!this->m_pSpriteMenuMain)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuMain->Create(
			"menu_main.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 7:

		this->m_pSpriteMenuOptions = new CSprite;

		if (!this->m_pSpriteMenuOptions)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuOptions->Create(
			"menu_options.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 8:

		this->m_pSpriteMenuInput = new CSprite;

		if (!this->m_pSpriteMenuInput)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuInput->Create(
			"menu_input.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 9:

		this->m_pSpriteMenuAudio = new CSprite;

		if (!this->m_pSpriteMenuAudio)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuAudio->Create(
			"menu_audio.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 10:

		this->m_pSpriteMenuDisplay = new CSprite;

		if (!this->m_pSpriteMenuDisplay)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuDisplay->Create(
			"menu_display.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 11:

		this->m_pSpriteMenuHighscore = new CSprite;

		if (!this->m_pSpriteMenuHighscore)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuHighscore->Create(
			"menu_highscore.png", m_pDevice, this->m_fDepthMenuText);

		break;

	case 12:

		this->m_pSpriteMenuTitleMain = new CSprite;

		if (!this->m_pSpriteMenuTitleMain)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuTitleMain->Create(
			"menu_title_main.png", m_pDevice, this->m_fDepthMenuText);

		this->m_pSpriteMenuTitleHighscore = new CSprite;

		if (!this->m_pSpriteMenuTitleHighscore)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMenuTitleHighscore->Create(
			"menu_title_highscore.png", m_pDevice, this->m_fDepthMenuText);

		break;

	// bars
	case 13:

		this->m_pSpriteVideoAntialiasingBarBorder = new CSprite;

		if (!this->m_pSpriteVideoAntialiasingBarBorder)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteVideoAntialiasingBarBorder->Create(
			"bar_antialiasing_border.png", m_pDevice, 0.1f);

		break;

	case 14:

		this->m_pSpriteVideoAntialiasingBar2x = new CSprite;

		if (!this->m_pSpriteVideoAntialiasingBar2x)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteVideoAntialiasingBar2x->Create(
			"bar_antialiasing_2.png", m_pDevice, 0.1f);

		break;

	case 15:

		this->m_pSpriteVideoAntialiasingBar46x = new CSprite;

		if (!this->m_pSpriteVideoAntialiasingBar46x)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteVideoAntialiasingBar46x->Create(
			"bar_antialiasing_4_6.png", m_pDevice, 0.1f);

		break;

	case 16:

		this->m_pSpriteVideoAntialiasingBar8x = new CSprite;

		if (!this->m_pSpriteVideoAntialiasingBar8x)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteVideoAntialiasingBar8x->Create(
			"bar_antialiasing_8.png", m_pDevice, 0.1f);

		break;

	// arrows
	case 17:

		this->m_pSpriteArrowInput = new CSprite;

		if (!this->m_pSpriteArrowInput)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowInput->Create(
			"arrow_input.png", m_pDevice, 0.1f);

		break;

	case 18:

		this->m_pSpriteArrowAntialiasingNormalLeft = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingNormalLeft)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingNormalLeft->Create(
			"arrow_aa_normal_left.png", m_pDevice, 0.1f);

		break;

	case 19:

		this->m_pSpriteArrowAntialiasingNormalRight = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingNormalRight)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingNormalRight->Create(
			"arrow_aa_normal_right.png", m_pDevice, 0.1f);

		break;

	case 20:

		this->m_pSpriteArrowAntialiasingGlowLeft = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingGlowLeft)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingGlowLeft->Create(
			"arrow_aa_glow_left.png", m_pDevice, 0.1f);

		break;

	case 21:

		this->m_pSpriteArrowAntialiasingGlowRight = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingGlowRight)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingGlowRight->Create(
			"arrow_aa_glow_right.png", m_pDevice, 0.1f);

		break;

	case 22:

		this->m_pSpriteArrowAntialiasingHideLeft = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingHideLeft)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingHideLeft->Create(
			"arrow_aa_hide_left.png", m_pDevice, 0.1f);

		break;

	case 23:

		this->m_pSpriteArrowAntialiasingHideRight = new CSprite;

		if (!this->m_pSpriteArrowAntialiasingHideRight)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteArrowAntialiasingHideRight->Create(
			"arrow_aa_hide_right.png", m_pDevice, 0.1f);

		break;

	// on/off messages
	case 24:

		this->m_pSpriteSpecularLightingOn = new CSprite;

		if (!this->m_pSpriteSpecularLightingOn)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteSpecularLightingOn->Create(
			"message_specular_on.png", m_pDevice, 0.1f);

		break;

	case 25:

		this->m_pSpriteSpecularLightingOnGlow = new CSprite;

		if (!this->m_pSpriteSpecularLightingOnGlow)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteSpecularLightingOnGlow->Create(
			"message_specular_on_glow.png", m_pDevice, 0.1f);

		break;

	case 26:

		this->m_pSpriteSpecularLightingOff = new CSprite;

		if (!this->m_pSpriteSpecularLightingOff)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteSpecularLightingOff->Create(
			"message_specular_off.png", m_pDevice, 0.1f);

		break;

	case 27:
		this->m_pSpriteSpecularLightingOffGlow = new CSprite;

		if (!this->m_pSpriteSpecularLightingOffGlow)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteSpecularLightingOffGlow->Create(
			"message_specular_off_glow.png", m_pDevice, 0.1f);

		break;

	// message boxes
	case 28:

		this->m_pSpriteMessageInputEmpty = new CSprite;

		if (!this->m_pSpriteMessageInputEmpty)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMessageInputEmpty->Create(
			"message_input_empty.png", m_pDevice, 0.1f);

		break;

	case 29:

		this->m_pSpriteMessageInputKey = new CSprite;

		if (!this->m_pSpriteMessageInputKey)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMessageInputKey->Create(
			"message_input_key.png", m_pDevice, 0.1f);

		break;

	case 30:

		this->m_pSpriteMessageRestart = new CSprite;

		if (!this->m_pSpriteMessageRestart)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMessageRestart->Create(
			"message_restart.png", m_pDevice, 0.1f);

		break;

	case 31:

		this->m_pSpriteMessageOK1 = new CSprite;

		if (!this->m_pSpriteMessageOK1)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMessageOK1->Create(
			"message_ok_1.png", m_pDevice, 0.1f);

		break;

	case 32:

		this->m_pSpriteMessageOK2 = new CSprite;

		if (!this->m_pSpriteMessageOK2)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteMessageOK2->Create(
			"message_ok_2.png", m_pDevice, 0.1f);

		break;

	// underlines
	case 33:

		this->m_pSpriteUnderlineAudio = new CSprite;

		if (!this->m_pSpriteUnderlineAudio)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineAudio->Create(
			"underline_audio.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 34:

		this->m_pSpriteUnderlineBack = new CSprite;

		if (!this->m_pSpriteUnderlineBack)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineBack->Create(
			"underline_back.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 35:
#ifdef MENU_CREDITS
		this->m_pSpriteUnderlineCredits = new CSprite;

		if (!this->m_pSpriteUnderlineCredits)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineCredits->Create(
			"underline_credits.png", m_pDevice, this->m_fDepthMenuUnderline);
#endif
		break;

	case 36:

		this->m_pSpriteUnderlineDefault = new CSprite;

		if (!this->m_pSpriteUnderlineDefault)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineDefault->Create(
			"underline_default.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 37:

		this->m_pSpriteUnderlineDisplay = new CSprite;

		if (!this->m_pSpriteUnderlineDisplay)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineDisplay->Create(
			"underline_display.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 38:

		this->m_pSpriteUnderlineExit = new CSprite;

		if (!this->m_pSpriteUnderlineExit)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineExit->Create(
			"underline_exit.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 39:

		this->m_pSpriteUnderlineHighscore = new CSprite;

		if (!this->m_pSpriteUnderlineHighscore)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineHighscore->Create(
			"underline_highscore.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 40:

		this->m_pSpriteUnderlineInput = new CSprite;

		if (!this->m_pSpriteUnderlineInput)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineInput->Create(
			"underline_input.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 41:

		this->m_pSpriteUnderlineNewgame = new CSprite;

		if (!this->m_pSpriteUnderlineNewgame)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineNewgame->Create(
			"underline_new_game.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

	case 42:

		this->m_pSpriteUnderlineOptions = new CSprite;

		if (!this->m_pSpriteUnderlineOptions)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteUnderlineOptions->Create(
			"underline_options.png", m_pDevice, this->m_fDepthMenuUnderline);

		break;

#ifdef MENU_CREDITS
	// credits
	case 43:

		this->m_pSpriteCreditsBackLayer = new CSprite;

		if (!this->m_pSpriteCreditsBackLayer)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteCreditsBackLayer->Create(
			"credits_back_layer.png", m_pDevice, 0.02f);

		break;

	case 44:

		this->m_pSpriteCreditsText = new CSpriteScrolling;

		if (!this->m_pSpriteCreditsText)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteCreditsText->Create(
			"credits_text.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_UP,
			false, 0.01f, 1024, 3037, 0, 768, 1, 0);

		break;
#endif

	//game version
	case 45:

		this->m_pSpriteVersion = new CSprite;

		if (!this->m_pSpriteVersion)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteVersion->Create(
			"version.png", m_pDevice, 0.1f);

		break;

	// audio bar border
	case 46:

		this->m_pSpriteAudioBarBorder = new CSprite;

		if (!this->m_pSpriteAudioBarBorder)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteAudioBarBorder->Create(
			"bar_audio_border.png", m_pDevice, 0.1f);

		break;
	}

	// audio bar meter
	if (this->m_iSpriteSteps >= 47)
	{
		if (this->m_iSpriteSteps == 47)
		{
			this->m_pSpriteAudioBarMeter = new CSprite[SPRITE_MENUS_AUDIO_BAR];

			if (!this->m_pSpriteAudioBarMeter)
			{
				return E_OUTOFMEMORY;
			}
		}

		std::string fileName;
		std::string sNumber;
		int iIndex;

		sNumber = TextUtils::IntToString(this->m_iSpriteSteps - 47 + 1);
		iIndex = this->m_iSpriteSteps - 47;

		fileName = "bar_audio_";
		fileName += sNumber;
		fileName += ".png";

		hres = (this->m_pSpriteAudioBarMeter + iIndex)->Create(
			fileName, m_pDevice, 0.1f);
	}

	return hres;
}

void CResourceMenus::InitMeshMenus()
{
	InitMeshMenusPlayer();
	InitMeshMenusEnemies();
	InitMeshMenusBosses();
}

void CResourceMenus::InitMeshMenusPlayer()
{
	RotateEnemy(GetMesh(CResources::MODEL_GAME_PLAYER_FRAME));
}

void CResourceMenus::InitMeshMenusEnemies()
{
	RotateEnemy(GetMesh(CResources::MODEL_GAME_ENEMY_DRONE_1));
	RotateEnemy(GetMesh(CResources::MODEL_GAME_ENEMY_SNIPER_1));
}

void CResourceMenus::InitMeshMenusBosses()
{
	RotateEnemy(GetMesh(CResources::MODEL_GAME_BOSS_1_FRAME));
	RotateEnemy(GetMesh(CResources::MODEL_GAME_BOSS_1_SCATTER));
}