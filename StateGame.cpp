/**
 * This class implements
 * game application "game" state.
 */

#include "StateGame.h"

CStateGame::CStateGame(void)
{
	m_dwNextState = STATE_RUNNING;
	this->m_pTheGame = NULL;
}

CStateGame::~CStateGame(void)
{
}

HRESULT CStateGame::Create(	CTheApp* pApp,
							DWORD dwState)
{
	this->m_pTheGame = new CTheGame;
	if (!this->m_pTheGame)
	{
		return E_OUTOFMEMORY;
	}

	HRESULT hres;

	this->m_iMeshSteps = 1;
	this->m_iSpriteSteps = 1;

	this->m_iMeshStepsMax = LOAD_MESH_GAME_MAX;
	this->m_iSpriteStepsMax = LOAD_SPRITES_GAME_MAX;

	this->m_iStepsMax = this->m_iMeshStepsMax + this->m_iSpriteStepsMax;

	this->m_iStepsMax += INIT_STEP_MAX;
	this->m_iStepsMax += LOAD_CONTAINER_MAX;
	this->m_iStepsMax += LOAD_TEMPLATE_MAX;
	this->m_iStepsMax += LOAD_LEVEL_STEPS_MAX;

	// explosions
	this->m_iStepsMax += 1;

	// game sounds
	if (pApp->IsLoadGameSoundFiles())
	{
		this->m_iStepsMax += 1;
	}

	CResourceGame* resourceGame = pApp->GetResourceGame();

	pApp->SetLoadingScreen(false);

	if (!resourceGame->IsResourcesLoaded())
	{
		// show the loading screen during this state loading
		pApp->SetLoadingScreen(true);

		this->m_iStepsMax += resourceGame->GetStepsMax();
		// zip file loading steps (20 + 1)
		this->m_iStepsMax += 21;
	}

	resourceGame->SetMeshFilePath("models/game/");
	resourceGame->SetSpriteFilePath("textures/game/");

	// remember to call base class implementation
	// to properly initialise the state.
	hres = IState::Create(pApp, dwState);
	if( FAILED(hres) )
	{
		return hres;
	}

	return hres;
}

HRESULT CStateGame::InitState(DWORD dwState)
{
	HRESULT hres;

	// create the actual in-game object
	hres = this->m_pTheGame->Create(this->GetApp(), this, dwState);

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

void CStateGame::Release()
{
	if(this->m_pTheGame)
	{
		this->m_pTheGame->Release();
		delete this->m_pTheGame;
		this->m_pTheGame = NULL;
	}

	// remember to call base class implementation
	// to properly release the state.
	//IState::Release();
}

DWORD CStateGame::Update(float fFrametime)
{
	IState::Update(fFrametime);
	return m_dwNextState;
}

void CStateGame::Render()
{
	// build a left-handed orthographic projection matrix
	this->BuildProjection();
	// render all the game action
	this->m_pTheGame->Render();
}

#ifdef SHADOWS
CShadowVolume* CStateGame::GetShadowVolumes()
{
	return this->m_pTheGame->GetShadowVolumes();
}
#endif
