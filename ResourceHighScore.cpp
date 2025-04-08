#include "TheApp.h"
#include "ResourceHighscore.h"

CResourceHighScore::CResourceHighScore()
{
	this->m_pSpriteHighscoresStarsBack = NULL;
	this->m_pSpriteHighscoresStarsFront = NULL;
	this->m_pSpriteHighscoresText = NULL;
	this->m_pSpriteHighscoresSelectBox = NULL;
	this->m_pSpriteHighscoresPlayerAfterburn = NULL;
}

void CResourceHighScore::Init(CTheApp* pApp, CZipManager* pZipManager)
{
	CResources::Init(pApp, pZipManager);

	this->m_iMeshStepsMax += MESH_HIGHSCORE;
	this->m_iSpriteStepsMax += SPRITE_HIGHSCORE;
}

void CResourceHighScore::Release(void)
{
	// MESHES

	m_MeshHighscoreShipPlayer.Release();
	m_MeshHighscoreBulletPlayerMinigun.Release();
	m_MeshHighscoreLetterWheel.Release();

	// SPRITES

	if (m_pSpriteHighscoresStarsBack)
	{
		m_pSpriteHighscoresStarsBack->Release();
		delete m_pSpriteHighscoresStarsBack;
		m_pSpriteHighscoresStarsBack = NULL;
	}
	if (m_pSpriteHighscoresStarsFront)
	{
		m_pSpriteHighscoresStarsFront->Release();
		delete m_pSpriteHighscoresStarsFront;
		m_pSpriteHighscoresStarsFront = NULL;
	}

	if (m_pSpriteHighscoresText)
	{
		m_pSpriteHighscoresText->Release();
		delete m_pSpriteHighscoresText;
		m_pSpriteHighscoresText = NULL;
	}
	if (m_pSpriteHighscoresSelectBox)
	{
		m_pSpriteHighscoresSelectBox->Release();
		delete m_pSpriteHighscoresSelectBox;
		m_pSpriteHighscoresSelectBox = NULL;
	}
	if (m_pSpriteHighscoresPlayerAfterburn)
	{
		m_pSpriteHighscoresPlayerAfterburn->Release();
		delete m_pSpriteHighscoresPlayerAfterburn;
		m_pSpriteHighscoresPlayerAfterburn = NULL;
	}

	// PARENT CLASS

	CResources::Release();
}

HRESULT CResourceHighScore::Load()
{
	if (this->m_bResourcesLoaded)
	{
		return S_OK;
	}

	HRESULT hres = S_OK;
	this->m_iResourcesLoadStepCounter++;

	if (m_iResourcesLoadStepCounter >= LOAD_STEPS_WAIT_DEFAULT)
	{
		this->m_bIsLoadWaitCycle = true;
		this->m_iResourcesLoadStepCounter = 0;
	}

	// load highscore meshes
	if (this->m_iMeshSteps <= this->m_iMeshStepsMax)
	{
		if (this->m_iMeshSteps == 1)
		{
			// Unpack "highscore" ZIP resource file.
			if (!this->m_pZipManager->IsExistResourceFolder("models/highscore") ||
				!this->m_pZipManager->IsExistResourceFolder("textures/highscore") ||
				!this->m_pZipManager->IsExistResourceFile("music/highscore.mp3"))
			{
				this->m_pZipManager->UnpackMasterZipFileWithTarget("data_2", "data6");
				this->m_pZipManager->UnpackChildZipFile("data6");
			}
		}

		hres = this->LoadMeshHighscore();
		this->m_iMeshSteps++;
	}
	// load highscore sprites
	else if (this->m_iSpriteSteps <= this->m_iSpriteStepsMax)
	{
		hres = this->LoadSpriteHighscore();
		this->m_iSpriteSteps++;
	}
	else
	{
		this->m_bResourcesLoaded = true;
	}

	return hres;
}

HRESULT CResourceHighScore::LoadMeshHighscore()
{
	char str[128] = "";
	HRESULT hres = S_OK;

	switch (this->m_iMeshSteps)
	{
	case 1:

		hres = m_MeshHighscoreBulletPlayerMinigun.Create(this->m_pDevice, "bullet_player_minigun.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: bullet_player_minigun.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(this->m_MeshHighscoreBulletPlayerMinigun, MODEL_GAME_BULLET_PLAYER_MINIGUN, MODEL_TYPE_BULLET_PLAYER);
		}

		break;

	case 2:

		hres = m_MeshHighscoreLetterWheel.Create(this->m_pDevice, "selector.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: selector.x\n");
			std::cout << str << std::endl;
		}

		break;

	case 3:

		hres = m_MeshHighscoreShipPlayer.Create(this->m_pDevice, "player.x");

		if (FAILED(hres))
		{
			sprintf_s(str, "ERROR: player.x\n");
			std::cout << str << std::endl;
		}
		else
		{
			this->SetMeshData(this->m_MeshHighscoreShipPlayer, MODEL_GAME_PLAYER_FRAME, MODEL_TYPE_HIGHSCORE_PLAYER);
		}

		break;
	}

	return hres;
}

HRESULT CResourceHighScore::LoadSpriteHighscore()
{
	HRESULT hres = S_OK;

	switch (this->m_iSpriteSteps)
	{
	// background stars (back)
	case 1:

		this->m_pSpriteHighscoresStarsBack = new CSpriteScrolling;

		if (!this->m_pSpriteHighscoresStarsBack)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteHighscoresStarsBack->Create(
			"stars_back.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, 1.0f, 2048, 768, 0, 0, 1, 5);

		break;
	// background stars (front)
	case 2:

		this->m_pSpriteHighscoresStarsFront = new CSpriteScrolling;

		if (!this->m_pSpriteHighscoresStarsFront)
		{
			return E_OUTOFMEMORY;
		}

		hres = this->m_pSpriteHighscoresStarsFront->Create(
			"stars_front.png", m_pDevice,
			CSpriteScrolling::eDIRECTION_LEFT,
			true, 0.8f, 2048, 768, -50, 0, 1, 3);

		break;

	// highscore text
	case 3:

		this->m_pSpriteHighscoresText = new CSprite;

		if (!this->m_pSpriteHighscoresText)
		{
			return E_OUTOFMEMORY;
		}

		hres = m_pSpriteHighscoresText->Create(
			"text.png", m_pDevice, 0.1f);

		break;

	// select box
	case 4:

		this->m_pSpriteHighscoresSelectBox = new CSprite;

		if (!this->m_pSpriteHighscoresSelectBox)
		{
			return E_OUTOFMEMORY;
		}

		hres = m_pSpriteHighscoresSelectBox->Create(
			"select_box.png", m_pDevice, 0.1f);

		break;

	// player afterburn
	case 5:

		this->m_pSpriteHighscoresPlayerAfterburn = new CSprite;

		if (!this->m_pSpriteHighscoresPlayerAfterburn)
		{
			return E_OUTOFMEMORY;
		}

		hres = m_pSpriteHighscoresPlayerAfterburn->Create(
			"player_afterburn.png", m_pDevice, 0.1f);

		break;

	// bullets
	case 6:
	{
		CSprite sprite;

		hres = sprite.Create(
			"player_bullet.png", m_pDevice, 0.1f);

		if (hres == S_OK)
		{
			SetSpriteData(sprite, SPRITE_HIGHSCORE_BULLET_PLAYER_MINIGUN);
		}
	}
		break;
	}

	return hres;
}