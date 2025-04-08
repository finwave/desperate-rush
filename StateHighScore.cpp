/**
 * This class implements
 * game application "highscore" state.
 */

#include "TextUtils.h"
#include "StateHighScore.h"

CStateHighScore::CStateHighScore(void)
{
	this->m_eState = eSTATE_INPUT;
	this->m_dwNextState = STATE_RUNNING;

#ifdef SHADOWS
	this->m_pShadowVolumes = NULL;
#endif

	this->m_pResourceHighScores = NULL;
	this->m_pJoystick = NULL;

	this->m_pXFile = NULL;

	this->m_pPlayerShip = NULL;
	this->m_pLetterWheel = NULL;

	this->m_pPlayerController = NULL;

	this->m_pLetters = NULL;
	this->m_pNumbers = NULL;

	this->m_pWeaponPlayerHighscore = NULL;

	this->m_pBullets.Clear();

	this->m_pSpriteStarsBack = NULL;
	this->m_pSpriteStarsFront = NULL;
	this->m_pSpriteText = NULL;
	this->m_pSpriteSelectBox = NULL;
	this->m_pSpritePlayerAfterburn = NULL;

	this->m_fLetterWheelPositionFractionX = 0.0f;
	this->m_fLetterWheelPositionFractionY = 0.0f;

	this->m_bFadeOutMusic = true;

	this->m_fDepthFades = 0.0f;
	this->m_fPauseFadeIn = 0.015f;
	this->m_fPauseFadeOut = 0.025f;
	this->m_fPauseFadeInFirst = 0.1f;
	this->m_fPauseFadeOutLast = 0.1f;

	this->m_fLetterWidth = 18.0f;
	this->m_fNumberWidth = 18.0f;

	this->m_fButtonTimer = 0.0f;
	this->m_bButtonTimer = false;

	this->m_pTimerShipPlayerEnter = 0.2f;
}

CStateHighScore::~CStateHighScore(void)
{
}

HRESULT CStateHighScore::Create(CTheApp* pApp,
								DWORD dwState)
{
	HRESULT hres;

	this->m_iMeshSteps = 1;
	this->m_iSpriteSteps = 1;

	this->m_iMeshStepsMax = LOAD_MESH_MAX_HIGHSCORE;
	this->m_iSpriteStepsMax = LOAD_SPRITE_MAX_HIGHSCORE;
	this->m_iStepsMax = this->m_iMeshStepsMax + this->m_iSpriteStepsMax;

	this->m_pResourceHighScores = pApp->GetResourceHighScore();

	pApp->SetLoadingScreen(false);

	// highscore screen resources
	if(!this->m_pResourceHighScores->IsResourcesLoaded())
	{
		// show the loading screen during this state loading
		pApp->SetLoadingScreen(true);

		this->m_iStepsMax += this->m_pResourceHighScores->GetStepsMax();
	}

	this->m_pResourceHighScores->SetMeshFilePath("models/highscore/");
	this->m_pResourceHighScores->SetSpriteFilePath("textures/highscore/");

	// remember to call base class implementation
	// to properly initialise the state.
	hres = IState::Create(pApp, dwState);

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

HRESULT CStateHighScore::InitState(DWORD dwState)
{
	if (this->IsLoadWaitTimer())
	{
		return S_OK;
	}

	/** LOAD RESOURCES TO MEMORY **/

	HRESULT hres = S_OK;

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

	// Add menu meshes into a reference array.
	if (!this->m_bMeshLoaded)
	{
		while (this->m_iMeshSteps <= this->m_iMeshStepsMax)
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
	if (!this->m_bSpriteLoaded)
	{
		while (this->m_iSpriteSteps <= this->m_iSpriteStepsMax)
		{
			this->LoadSprites();
			this->UpdateLoadingBar(1);
			this->m_iSpriteSteps++;
		}

		this->m_bSpriteLoaded = true;
		this->SetLoadWaitTimer();
		return S_OK;
	}

	if (CWeapon::s_SpritesHighscore.size() == 0)
	{
		for (int i = CResources::SPRITE_HIGHSCORE_BULLET_FIRST; i <= CResources::SPRITE_HIGHSCORE_BULLET_LAST; i++)
		{
			CWeapon::s_SpritesHighscore.push_back(this->m_pResourceHighScores->GetSprite(i));
		}
	}

	/**  LOADED NECESSARY RESOURCES **/
	// NO MORE LOADING SCREEN UPDATES //

	if (!this->m_StateInitialized)
	{
		this->m_pJoystick = this->GetApp()->GetJoystick();

		/** DYNAMIC LIGHTING **/

		this->m_pLights->InitHighscoreMain();
		this->m_pLights->SetHighscoreMain(true);

		/** 3D OBJECTS **/

		// container for letter meshes
		this->m_pLetters = new CLetter[DISPLAY_LETTER_COUNT_HIGHSCORE];

		if (!this->m_pLetters)
		{
			return E_OUTOFMEMORY;
		}

		for (int i = 0; i < DISPLAY_LETTER_COUNT_HIGHSCORE; i++)
		{
			hres = (this->m_pLetters + i)->Create(this->m_pXFile[LOAD_MESH_HIGHSCORE_A + i].GetMesh(),
				this->m_pXFile[LOAD_MESH_HIGHSCORE_A + i],
				this->m_fLetterWidth,
				10.0f,
				true,
				CLetter::eLETTER_TYPE_HIGHSCORE);
			if (FAILED(hres))
			{
				return hres;
			}
		}

		// container for number meshes
		this->m_pNumbers = new CNumber[DISPLAY_NUMBER_COUNT_HIGHSCORE];

		if (!this->m_pNumbers)
		{
			return E_OUTOFMEMORY;
		}

		for (int i = 0; i < DISPLAY_NUMBER_COUNT_HIGHSCORE; i++)
		{
			hres = (this->m_pNumbers + i)->Create(this->m_pXFile[LOAD_MESH_HIGHSCORE_0 + i].GetMesh(),
				this->m_pXFile[LOAD_MESH_HIGHSCORE_0 + i],
				this->m_fNumberWidth,
				10.0f,
				true,
				CNumber::eNUMBER_TYPE_HIGHSCORE);
			if (FAILED(hres))
			{
				return hres;
			}
		}

		// Letter wheel

		this->m_pLetterWheel = new CHighscoreLetterWheel();

		if (!this->m_pLetterWheel)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pLetterWheel->Create(this->GetApp(),
			this->m_pXFile[LOAD_MESH_HIGHSCORE_WHEEL].GetMesh(),
			this->m_pXFile[LOAD_MESH_HIGHSCORE_WHEEL],
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_OTHER,
			CMenuObject::eSHIP_NONE);

		this->m_pLetterWheel->Init();
		this->m_pLetterWheel->SetDepth(0.0f);

		// set starting position

		float letterWheelPosX = 50.0f;
		float letterWheelPosY = -60.0f;

		this->m_fLetterWheelPositionFractionX = abs(letterWheelPosX) / this->m_fScreenWidth;
		this->m_fLetterWheelPositionFractionY = abs(letterWheelPosY) / this->m_fScreenHeight;

		this->m_pLetterWheel->SetPosition(D3DXVECTOR3(letterWheelPosX, letterWheelPosY, 0.0f));

		// set extra scale value

		this->m_pLetterWheel->SetLetterWheelAdditionScaleValue(0.85f);

		// set starting rotation

		this->m_pLetterWheel->SetLetterWheelRotationY(D3DX_PI / 6.5f);

		// Player ship

		this->m_pPlayerShip = new CHighscorePlayerShip();

		if (!this->m_pPlayerShip)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pPlayerShip->Create(this->GetApp(),
			this->m_pResourceHighScores->GetMesh(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_pResourceHighScores->GetMaterial(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_pResourceHighScores->GetTexture(CResources::MODEL_GAME_PLAYER_FRAME),
			this->m_fScreenWidth,
			this->m_fScreenHeight,
			CMenuObject::eTYPE_SHIP,
			CMenuObject::eSHIP_NONE);

		this->m_pPlayerShip->SetShipEnterEndPosX(-(letterWheelPosX + 10.0f));
		this->m_pPlayerShip->SetShipPosY(letterWheelPosY + 2.0f);

		this->m_pPlayerShip->Init();
		this->m_pPlayerShip->SetDepth(0.0f);

		// CONTROLLER CLASS //

		this->m_pPlayerController = new CObjectController(
			0.25f, 0.25f, 0.6f, CObjectController::eTYPE_HIGHSCORE_PLAYER);

		if (!this->m_pPlayerController)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pPlayerController->Create(this->m_pPlayerShip);

		/* WEAPONS */

		this->m_pWeaponPlayerHighscore = new CWeaponPlayerHighscore();

		if (!this->m_pWeaponPlayerHighscore)
		{
			return E_OUTOFMEMORY;
		}

		this->m_pWeaponPlayerHighscore->Create(this->GetApp()->GetDevice(),
			this->m_pResourceHighScores->GetMesh(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
			this->m_pResourceHighScores->GetMaterial(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
			this->m_pResourceHighScores->GetTexture(CResources::MODEL_GAME_BULLET_PLAYER_MINIGUN),
			0.0f,
			0.0f,
			380.0f,
			0,
			CWeapon::eBULLET_TYPE_PLAYER_HIGHSCORE);

		this->m_pWeaponPlayerHighscore->SetVisible(false);

		this->m_StateInitialized = true;
		this->SetLoadWaitTimer();
		return S_OK;
	}

	if (this->m_StateInitialized)
	{
		// current music configuration has volume set up
		if (this->GetApp()->GetConfig().GetVolumeMusic() > 0)
		{
			// load highscore music
			LPCTSTR resourceFilePath = this->m_pResourceHighScores->GetUnpackedResourceFilePath("music/highscore.mp3");
			this->GetApp()->GetMP3Player1().Create(resourceFilePath);

			// play highscore music
			this->GetApp()->GetMP3Player1().SetVolume(this->GetApp()->GetVolumeMusic());
			this->GetApp()->GetMP3Player1().Play();
		}

		this->SetStateLoaded(true);
	}

	return S_OK;
}


void CStateHighScore::Release()
{
	/* MESHES */

	if( this->m_pPlayerShip)
	{
		this->m_pPlayerShip->Release();
		delete this->m_pPlayerShip;
		this->m_pPlayerShip = NULL;
	}
	if( this->m_pLetterWheel )
	{
		this->m_pLetterWheel->Release();
		delete this->m_pLetterWheel;
		this->m_pLetterWheel = NULL;
	}
	if( this->m_pLetters )
	{
		for ( int i = 0; i < DISPLAY_LETTER_COUNT_HIGHSCORE; i++ )
		{
			(this->m_pLetters + i)->Release();
		}
		delete [] this->m_pLetters;
		this->m_pLetters = NULL;
	}
	if( this->m_pNumbers )
	{
		for ( int i = 0; i < DISPLAY_NUMBER_COUNT_HIGHSCORE; i++ )
		{
			(this->m_pNumbers + i)->Release();
		}
		delete [] this->m_pNumbers;
		this->m_pNumbers = NULL;
	}
	if( this->m_pWeaponPlayerHighscore )
	{
		this->m_pWeaponPlayerHighscore->Release();
		delete this->m_pWeaponPlayerHighscore;
		this->m_pWeaponPlayerHighscore = NULL;
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

	if( this->m_pPlayerController )
	{
		this->m_pPlayerController->Release();
		delete this->m_pPlayerController;
		this->m_pPlayerController = NULL;
	}

	this->m_pBullets.Clear();

	// remember to call base class implementation
	// to properly release the state.
	IState::Release();
}

DWORD CStateHighScore::Update(float fFrametime)
{
	IState::Update(fFrametime);

	if (!IsStateLoaded())
	{
		return S_OK;
	}

	// update click timer
	if(this->m_bButtonTimer)
	{
		if( this->m_fButtonTimer > 0.0f)
		{
			this->m_fButtonTimer -= fFrametime;

			if( this->m_fButtonTimer <= 0.0f)
			{
				this->m_bButtonTimer = false;
			}
		}
	}

	// music has volume
	if(this->GetApp()->GetConfig().GetVolumeMusic() > 0)
	{
		// music has reached it's end, reset position 
		if(this->GetApp()->GetMP3Player1().IsAtEnd())
		{
			this->GetApp()->GetMP3Player1().Stop();
			GetApp()->GetMP3Player1().SetPosition(0);
			GetApp()->GetMP3Player1().Play();
		}
	}
	// next state to take
	return m_dwNextState;
}


void CStateHighScore::Render()
{
	const float fFrametime = this->GetApp()->GetFrameTime();

	// build a left-handed orthographic projection matrix
	this->BuildProjection();

	// SPRITES

	// render background
	this->m_pSpriteStarsBack->Draw(false);
	this->m_pSpriteStarsFront->Draw(false);

	// render main text
	this->m_pSpriteText->Draw(0, 0);

	// render select box
	RenderSelectBox();

	// MODELS
	
	// render letter wheel
	this->RenderLetterWheel(fFrametime);
	// render player score
	this->RenderPlayerScore(fFrametime);
	// render player name
	this->RenderPlayerName(fFrametime);

	switch(this->m_eState)
	{
	case eSTATE_INPUT:

		this->PlayerInput();

		this->CollisionBulletVsBorder();
		this->ClearBullets();
		this->UpdateBullets(fFrametime);
		this->RenderBullets();
		this->RenderShips(fFrametime);

		this->RenderInputAction(fFrametime);

		break;

	case eSTATE_LEAVE:

		this->CollisionBulletVsBorder();
		this->ClearBullets();
		this->UpdateBullets(fFrametime);
		this->RenderBullets();
		this->RenderShips(fFrametime);

		if (this->m_pPlayerShip->GetActionMode() == CHighscorePlayerShip::eACTION_MODE_EXIT)
		{
			this->GetFading()->SetFadeOut();
			this->GetFading()->SetDefaultFadeStep();

			// change state
			this->m_eState = eSTATE_EXIT;
		}

		break;

	case eSTATE_EXIT:

		this->RenderExit(fFrametime);

		break;
	}
}

void CStateHighScore::CollisionBulletVsBorder()
{
	//START*********** BULLET VS BORDER *************

	this->m_pBullets.SetFirst();
	while ( this->m_pBullets.GetCurrent() )
	{
		switch (this->m_pBullets.GetCurrent()->GetOwner())
		{
		case CWeapon::eOWNER_PLAYER:

			D3DXVECTOR3* pPos;

			switch ( this->m_pBullets.GetCurrent()->GetBulletType() )
			{
			case CWeapon::eBULLET_TYPE_PLAYER_HIGHSCORE:

				pPos = this->m_pBullets.GetCurrent()->GetBulletPosition();

				for (int i = 0; i < 3; i++)
				{
					// right border collision
					if( pPos[i].x > (this->m_fScreenWidth + 5.0f) )
					{
						this->m_pBullets.GetCurrent()->DisableBullet(i);
					}
				}

				break;
			}
		}
		this->m_pBullets.SetNext();
	}

	//END************* BULLET VS BORDER *************
}

void CStateHighScore::ClearBullets()
{
	//START********* CLEAR BULLETS ************

	this->m_pBullets.SetFirst();
	while ( this->m_pBullets.GetCurrent() )
	{
		if( !this->m_pBullets.GetCurrent()->IsActive() )
		{
			this->m_pBullets.PopCurrent();
		}
		this->m_pBullets.SetNext();
	}

	//END*********** CLEAR BULLETS ************
}

void CStateHighScore::UpdateBullets(float fFrametime)
{
	//START*************** UPDATE BULLETS *********************

	this->m_pBullets.SetFirst();
	while ( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			this->m_pBullets.GetCurrent()->Update(fFrametime, 0.0f);
		}
		this->m_pBullets.SetNext();
	}

	//END***************** UPDATE BULLETS *********************
}

void CStateHighScore::RenderInputAction(float fFrametime)
{
	this->m_pLetterWheel->RenderInputAction(fFrametime);
}

void CStateHighScore::RenderExit(float fFrametime)
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

	//this->RenderShips(fFrametime);

	// draw fade-out
	this->GetFading()->RenderFading();

	if(!bScreenFading && !this->m_bFadeOutMusic)
	{
		/* SAVE HIGHSCORE */

		std::string playerName = m_pLetterWheel->GetPlayerName();

		// save new highscore entry along with old ones into the file
		this->GetApp()->GetHighScore().SetNewName(playerName);
		this->GetApp()->GetHighScore().AddHighScore();

		// save highscore data
		this->GetApp()->GetHighScore().Save();

		/* CHANGE GAME STATE */

		// change state
		m_dwNextState = STATE_MENUS;
		// need to prepare new state
		this->SetNewState(true);
		// create state first, then initialize it
		this->GetApp()->SetCreateState(true);
	}
}

void CStateHighScore::RenderSelectBox()
{
	float posX = 0;
	float posY = 0;

	// Calculate position at the middle of the letter wheel.

	D3DXVECTOR3 letterWheelPos = this->m_pLetterWheel->GetPosition();

	float halfScreenWidth = 0.5f * this->m_fScreenPixelWidth;
	float halfScreenHeight = 0.5f * this->m_fScreenPixelHeight;

	posX += halfScreenWidth;
	posY += halfScreenHeight;

	if (letterWheelPos.x != 0)
	{
		float additionX = this->m_fLetterWheelPositionFractionX * halfScreenWidth;

		if (letterWheelPos.x < 0)
		{
			additionX = -additionX;
		}

		posX += additionX;
	}

	if (letterWheelPos.y != 0)
	{
		float additionY = this->m_fLetterWheelPositionFractionY * halfScreenHeight;

		if (letterWheelPos.y > 0)
		{
			additionY = -additionY;
		}

		posY += additionY;
	}

	// Include sprite image pixel size into the calculation.

	float spriteWidth = 63.0f;
	float spriteHeight = 49.0f;

	posX -= 0.5f * spriteWidth;
	posY -= 0.5f * spriteHeight;

	// Add the manual offset.

	float letterWheelExtraScale = this->m_pLetterWheel->GetLetterWheelAdditionScaleValue();
	posX += letterWheelExtraScale * LETTER_BOX_OFFSET_X;
	posY += letterWheelExtraScale * LETTER_BOX_OFFSET_Y;

	this->m_pSpriteSelectBox->Draw(posX, posY);
}

void CStateHighScore::RenderLetterWheel(float fFrametime)
{
	this->m_pLetterWheel->Update(fFrametime);
	this->m_pLetterWheel->Render(this->GetApp()->GetDevice());
}

void CStateHighScore::RenderPlayerScore(float fFrametime)
{
	char* pPointer;
	char* sScore = NULL;

	int iScore = this->GetApp()->GetHighScore().GetNewScore();

	sScore = TextUtils::IntToChar(iScore);
	pPointer = sScore;

	D3DXVECTOR3 pos;
	float fPosX = 0.0f;

	pos.y = 55.0f;
	pos.z = -1000.0f;

	if(	(iScore > 9) && 
		(iScore < 100))
	{
		fPosX -= this->m_fNumberWidth * 0.5f;
	}
	else if((iScore >99) && 
			(iScore < 1000))
	{
		fPosX -= this->m_fNumberWidth;
	}
	else if((iScore >999) && 
			(iScore < 10000))
	{
		fPosX -= this->m_fNumberWidth * 1.5f;
	}
	else if((iScore > 9999) && 
			(iScore < 100000))
	{
		fPosX -= this->m_fNumberWidth * 2.0f;
	}

	pos.x = fPosX;

	while ( (*pPointer) != NULL )
	{
		(this->m_pNumbers + ((*pPointer) - '0'))->SetPosition(pos);
		(this->m_pNumbers + ((*pPointer) - '0'))->Update(fFrametime);
		(this->m_pNumbers + ((*pPointer) - '0'))->Render(this->GetApp()->GetDevice());
		pos.x += this->m_fNumberWidth;
		
		pPointer++;
	}

	delete [] sScore;
	sScore = NULL;
}

void CStateHighScore::RenderPlayerName(float fFrametime)
{
	D3DXVECTOR3 pos;
	float fPosX = 0.0f;

	pos.y = 27.0f;
	pos.z = -1000.0f;

	std::string playerName = m_pLetterWheel->GetPlayerName();
	int iLength = playerName.length();

	switch(iLength)
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

	for(int i = 0; i < iLength; i++)
	{
		if(playerName[i] == 'A')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_A].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_A].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_A].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'B')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_B].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_B].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_B].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'C')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_C].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_C].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_C].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'D')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_D].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_D].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_D].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'E')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_E].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_E].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_E].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'F')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_F].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_F].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_F].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'G')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_G].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_G].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_G].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'H')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_H].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_H].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_H].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'I')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_I].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_I].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_I].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'J')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_J].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_J].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_J].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'K')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_K].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_K].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_K].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'L')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_L].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_L].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_L].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'M')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_M].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_M].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_M].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'N')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_N].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_N].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_N].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'O')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_O].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_O].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_O].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'P')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_P].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_P].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_P].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'Q')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Q].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Q].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Q].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'R')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_R].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_R].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_R].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'S')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_S].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_S].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_S].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'T')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_T].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_T].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_T].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'U')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_U].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_U].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_U].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'V')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_V].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_V].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_V].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'W')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_W].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_W].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_W].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'X')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_X].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_X].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_X].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'Y')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Y].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Y].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Y].Render(this->GetApp()->GetDevice());
		}
		else if(playerName[i] == 'Z')
		{
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Z].SetPosition(pos);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Z].Update(fFrametime);
			this->m_pLetters[LOAD_MESH_HIGHSCORE_Z].Render(this->GetApp()->GetDevice());
		}

		pos.x += this->m_fLetterWidth;
	}
}

void CStateHighScore::RenderShips(float fFrametime)
{
	if(this->m_pTimerShipPlayerEnter <= 0.0f)
	{
		// update player controller
		this->m_pPlayerController->Update(fFrametime, NULL);
		// update player ship
		this->m_pPlayerShip->Update(fFrametime);
		// render player ship
		this->m_pPlayerShip->Render(this->GetApp()->GetDevice());

		// render player afterburn
		if (this->m_pPlayerShip->IsAfterburnEnabled())
		{
			RenderPlayerAfterburn();
		}
	}
	else
	{
		this->m_pTimerShipPlayerEnter -= fFrametime;
	}
}

void CStateHighScore::RenderPlayerAfterburn()
{
	static int iPause = 0;

	if(iPause == 0)
	{
		iPause = 3;

		const float fPixelMultiplier = 2.5f;

		// player's current position
		D3DXVECTOR3 pos = this->m_pPlayerShip->GetPosition();

		float fMoveX = pos.x * fPixelMultiplier;
		float fMoveY = pos.y * fPixelMultiplier;

		fMoveY = fMoveY * -1.0f;

		int posX = ( (this->m_fScreenPixelWidth / 2) - 38.0f) + fMoveX;
		int posY = ( (this->m_fScreenPixelHeight / 2) - 38.0f) + fMoveY;

		posX -= 89;
		posY += 26;

		this->m_pSpritePlayerAfterburn->Draw(posX, posY);
	}
	else
	{
		iPause--;
	}
}

void CStateHighScore::RenderBullets()
{
	//START*************** RENDER BULLETS *********************

	this->m_pBullets.SetFirst();
	while ( this->m_pBullets.GetCurrent() )
	{
		if( this->m_pBullets.GetCurrent()->IsActive() )
		{
			this->m_pBullets.GetCurrent()->Render(this->GetApp()->GetDevice());

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
			}
		}
		this->m_pBullets.SetNext();
	}

	//END***************** RENDER BULLETS *********************
}

void CStateHighScore::PlayerInput()
{
	bool bInputUp = false;
	bool bInputDown = false;
	bool bInputSelect = false;
	bool bCheckJoystick = false;
	bool bCheckKeyboard = true;

	if(SUCCEEDED(this->m_pJoystick->Update()))
	{
		bCheckJoystick = true;
	}
	if(bCheckJoystick)
	{
		DWORD buttons = this->m_pJoystick->GetButtonCount();
		int iJoystickY = this->m_pJoystick->GetState().lY;

		// read select control
		if( this->PushButton() )
		{
			// read buttons
			for (DWORD i = 0; i < buttons; i++)
			{
				if(this->m_pJoystick->GetButton(i))
				{
					bInputSelect = true;
					this->m_bButtonTimer = true;

					// ends loop
					i = buttons;
				}
			}
		}
		// read up control
		if(iJoystickY < 0)
		{
			bInputUp = true;
		}
		// read down control
		if(iJoystickY > 0)
		{
			bInputDown = true;
		}

		if(bInputSelect || bInputUp || bInputDown)
		{
			// joystick has priority over keyboard
			bCheckKeyboard = false;
		}
			
	}
	if(bCheckKeyboard)
	{
		// read select control
		if( this->PushButton() )
		{
			if(::GetAsyncKeyState(VK_RETURN))
			{
				bInputSelect = true;
				this->m_bButtonTimer = true;
			}
		}
		// read up control
		if(::GetAsyncKeyState(VK_UP))
		{
			bInputUp = true;
		}
		// read down control
		if(::GetAsyncKeyState(VK_DOWN))
		{
			bInputDown = true;
		}
	}

	if(bInputSelect)
	{
		std::string playerName = this->m_pLetterWheel->GetPlayerName();

		// select letter
		if(!this->m_pLetterWheel->IsRotateWheelDown() && !this->m_pLetterWheel->IsRotateWheelUp())
		{
			if(this->m_pLetterWheel->GetLetterWheel() == CHighscoreLetterWheel::eLETTER_WHEEL_END)
			{
				if(playerName != "")
				{
					// change ship action mode
					this->m_pPlayerShip->SetActionMode(CHighscorePlayerShip::eACTION_MODE_LEAVE);
					// change state
					this->m_eState = eSTATE_LEAVE;
				}
			}
			else if(this->m_pLetterWheel->GetLetterWheel() == CHighscoreLetterWheel::eLETTER_WHEEL_DEL)
			{
				std::string strNewName = "";
				int iLength = playerName.length();

				if(iLength > 0)
				{
					// copy letters except the last one
					for(int i = 0; i < iLength; i++)
					{
						if(i < (iLength - 1))
						{
							strNewName += playerName[i];
						}
					}

					playerName = strNewName;
					this->m_pLetterWheel->SetPlayerName(playerName);

					if(this->m_pLetterWheel->IsNameFull())
					{
						this->m_pLetterWheel->SetNameFull(false);
					}

					// ship actions
					this->ShipActions(VK_RETURN);
				}
			}
			else
			{
				if(!this->m_pLetterWheel->IsNameFull())
				{
					this->m_pLetterWheel->SetSelectLetter(true);
					// ship actions
					this->ShipActions(VK_RETURN);
				}
			}
		}
	}
	if(bInputUp)
	{
		if(!this->m_pLetterWheel->IsSelectLetter() && !this->m_pLetterWheel->IsRotateWheelUp())
		{
			if(!this->m_pLetterWheel->IsRotateWheelDown())
			{
				// if name is full then movement is limited between 'delete' and 'end'
				if(this->m_pLetterWheel->IsNameFull())
				{
					if(this->m_pLetterWheel->GetLetterWheel() == CHighscoreLetterWheel::eLETTER_WHEEL_END)
					{
						this->m_pLetterWheel->SetRotateWheelDown(true);
						// ship actions
						this->ShipActions(VK_UP);
					}
				}
				else
				{
					this->m_pLetterWheel->SetRotateWheelDown(true);
					// ship actions
					this->ShipActions(VK_UP);
				}
			}
		}
	}
	if(bInputDown)
	{
		if(!this->m_pLetterWheel->IsSelectLetter() && !this->m_pLetterWheel->IsRotateWheelDown())
		{
			if(!this->m_pLetterWheel->IsRotateWheelUp())
			{
				// if name is full then movement is 
				// limited between 'delete' and 'end'
				if(this->m_pLetterWheel->IsNameFull())
				{
					if(this->m_pLetterWheel->GetLetterWheel() == CHighscoreLetterWheel::eLETTER_WHEEL_DEL)
					{
						this->m_pLetterWheel->SetRotateWheelUp(true);
						// ship actions
						this->ShipActions(VK_DOWN);
					}
				}
				else
				{
					this->m_pLetterWheel->SetRotateWheelUp(true);
					// ship actions
					this->ShipActions(VK_DOWN);
				}
			}
		}
	}

	if(	!this->m_pLetterWheel->IsRotateWheelUp() && !this->m_pLetterWheel->IsRotateWheelDown())
	{
		// ship actions
		this->m_pPlayerController->StopRotation();
	}
}

void CStateHighScore::ShipActions(DWORD dwKey)
{
	// commit actions
	if(	(this->m_pPlayerShip->GetActionMode() == CHighscorePlayerShip::eACTION_MODE_ENTER) ||
		(this->m_pPlayerShip->GetActionMode() == CHighscorePlayerShip::eACTION_MODE_RESPOND))
	{
		if(this->m_pPlayerController->GetAction() == CObjectController::eACTION_NONE)
		{
			if(dwKey == VK_UP)
			{
				this->m_pPlayerController->CommitAction(CObjectController::eACTION_ROLL_LEFT);
			}
			else if(dwKey == VK_DOWN)
			{
				this->m_pPlayerController->CommitAction(CObjectController::eACTION_ROLL_RIGHT);
			}
			else if(dwKey == VK_RETURN)
			{
				this->PlayerShoot();
			}
		}
	}
}

void CStateHighScore::PlayerShoot()
{
	CWeapon* weapon = new CWeaponPlayerHighscore();

	if( weapon )
	{
		weapon->Create(	this->GetApp()->GetDevice(),
						this->m_pWeaponPlayerHighscore->GetMesh(),
						this->m_pWeaponPlayerHighscore->GetMeshDataArray(),
						this->m_pWeaponPlayerHighscore->GetWidth(),
						this->m_pWeaponPlayerHighscore->GetHeight(),
						this->m_pWeaponPlayerHighscore->GetSpeed(), 
						this->m_pWeaponPlayerHighscore->GetDamage(),
						this->m_pWeaponPlayerHighscore->GetBulletType());

		weapon->SetMatrix(this->m_pPlayerShip);

		weapon->InitPosition();
		
		weapon->SetVisible(true);
		this->m_pBullets.Push(weapon);

		// play minigun firing sound
		this->GetApp()->GetWave(SOUND_SHOOT_PLAYER_MINIGUN_1).Play(FALSE, NEXT_FREE_DUPLICATE, this->m_iVolumeSoundEffect);
	}
}

HRESULT CStateHighScore::LoadMeshes()
{
	if(this->m_iMeshSteps == 1)
	{
		this->m_pXFile = new CXFileContainer[LOAD_MESH_MAX_HIGHSCORE];

		if( !this->m_pXFile )
		{
			return E_OUTOFMEMORY;
		}
	}

	CResourceMenus* resourceMenus = this->m_pApp->GetResourceMenus();
	CResourceHighScore* resourceHighScores = this->m_pApp->GetResourceHighScore();
	
	switch(this->m_iMeshSteps)
	{
		/* LETTERS */

	case 1:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_A] = resourceMenus->GetMeshLetterA();
		break;
	case 2:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_B] = resourceMenus->GetMeshLetterB();
		break;
	case 3:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_C] = resourceMenus->GetMeshLetterC();
		break;
	case 4:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_D] = resourceMenus->GetMeshLetterD();
		break;
	case 5:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_E] = resourceMenus->GetMeshLetterE();
		break;
	case 6:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_F] = resourceMenus->GetMeshLetterF();
		break;
	case 7:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_G] = resourceMenus->GetMeshLetterG();
		break;
	case 8:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_H] = resourceMenus->GetMeshLetterH();
		break;
	case 9:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_I] = resourceMenus->GetMeshLetterI();
		break;
	case 10:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_J] = resourceMenus->GetMeshLetterJ();
		break;
	case 11:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_K] = resourceMenus->GetMeshLetterK();
		break;
	case 12:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_L] = resourceMenus->GetMeshLetterL();
		break;
	case 13:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_M] = resourceMenus->GetMeshLetterM();
		break;
	case 14:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_N] = resourceMenus->GetMeshLetterN();
		break;
	case 15:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_O] = resourceMenus->GetMeshLetterO();
		break;
	case 16:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_P] = resourceMenus->GetMeshLetterP();
		break;
	case 17:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_Q] = resourceMenus->GetMeshLetterQ();
		break;
	case 18:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_R] = resourceMenus->GetMeshLetterR();
		break;
	case 19:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_S] = resourceMenus->GetMeshLetterS();
		break;
	case 20:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_T] = resourceMenus->GetMeshLetterT();
		break;
	case 21:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_U] = resourceMenus->GetMeshLetterU();
		break;
	case 22:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_V] = resourceMenus->GetMeshLetterV();
		break;
	case 23:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_W] = resourceMenus->GetMeshLetterW();
		break;
	case 24:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_X] = resourceMenus->GetMeshLetterX();
		break;
	case 25:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_Y] = resourceMenus->GetMeshLetterY();
		break;
	case 26:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_Z] = resourceMenus->GetMeshLetterZ();
		break;

		/* NUMBERS */

	case 27:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_0] = resourceMenus->GetMeshNumber0();
		break;
	case 28:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_1] = resourceMenus->GetMeshNumber1();
		break;
	case 29:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_2] = resourceMenus->GetMeshNumber2();
		break;
	case 30:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_3] = resourceMenus->GetMeshNumber3();
		break;
	case 31:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_4] = resourceMenus->GetMeshNumber4();
		break;
	case 32:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_5] = resourceMenus->GetMeshNumber5();
		break;
	case 33:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_6] = resourceMenus->GetMeshNumber6();
		break;
	case 34:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_7] = resourceMenus->GetMeshNumber7();
		break;
	case 35:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_8] = resourceMenus->GetMeshNumber8();
		break;
	case 36:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_9] = resourceMenus->GetMeshNumber9();
		break;

	/* SHIPS */

	// Player
	case 37:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_PLAYER] = this->m_pResourceHighScores->GetMeshHighscoreShipPlayer();
		break;

	/* BULLETS */

	case 38:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_BULLET_PLAYER] = this->m_pResourceHighScores->GetMeshHighscoreBulletPlayerMinigun();
		break;

	/* OTHERS */

	// letter wheel
	case 39:
		this->m_pXFile[LOAD_MESH_HIGHSCORE_WHEEL] = this->m_pResourceHighScores->GetMeshHighscoreLetterWheel();
		break;
	}

	return S_OK;
}

void CStateHighScore::LoadSprites()
{
	CResourceHighScore* resourceHighScores = this->m_pApp->GetResourceHighScore();

	switch(this->m_iSpriteSteps)
	{
	// background stars
	case 1:
		this->m_pSpriteStarsBack = this->m_pResourceHighScores->GetSpriteHighscoresStarsBack();
		break;
	case 2:
		this->m_pSpriteStarsFront = this->m_pResourceHighScores->GetSpriteHighscoresStarsFront();
		break;
	// highscore text
	case 3:
		this->m_pSpriteText = this->m_pResourceHighScores->GetSpriteHighscoresText();
		break;
	// select box
	case 4:
		this->m_pSpriteSelectBox = this->m_pResourceHighScores->GetSpriteHighscoresSelectBox();
		break;
	// player afterburn
	case 5:
		this->m_pSpritePlayerAfterburn = this->m_pResourceHighScores->GetSpriteHighscoresPlayerAfterburn();
		break;
	}
}


#ifdef SHADOWS
CShadowVolume* CStateHighScore::GetShadowVolumes()
{
	this->BuildShadowVolumes();
	return this->m_pShadowVolumes;
}

HRESULT CStateHighScore::BuildShadowVolumes()
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
	this->m_pShadowVolumes = new CShadowVolume[iLightCount * MESH_SHADOW_COUNT_HIGHSCORE];

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
			for(int j = 0; j < MESH_SHADOW_COUNT_HIGHSCORE; j++)
			{
				//calculate the world->model space transform matrix
				switch(j)
				{
				// letter wheel object
				case 0:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pLetterWheel->GetWorldMatrix() );
					break;

				// player object
				case 1:
					D3DXMatrixInverse( &matrix, NULL, &this->m_pPlayer->GetWorldMatrix() );
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
				// letter wheel object
				case 0:

					this->m_pShadowVolumes[iShadowVolumeIndex].SetWorldMatrix(this->m_pLetterWheel->GetWorldMatrix());
					
					hres = this->m_pShadowVolumes[iShadowVolumeIndex].BuildFromMesh(this->m_pLetterWheel->GetMesh(), vecLight );
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

bool CStateHighScore::PushButton()
{
	if(this->m_bButtonTimer)
	{
		if(this->m_fButtonTimer <= 0.0f)
		{
			this->m_fButtonTimer = 0.3f;
		}

		return false;
	}
	else
	{
		return true;
	}
}

