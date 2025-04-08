/**
 * Abstract application state class.
 * This class is a base for all application
 * states. It provides access to application
 * object and basic methods for updating application.
 */

#include "IState.h"

CFading IState::m_Fading;

IState::IState(void)
{
	this->m_pApp = NULL;
	this->m_pLights = NULL;
	this->m_pSpriteLoadingScreen = NULL;
	this->m_pSpriteLoadingBar = NULL;

	this->m_fDepth = 1000.0f;
	this->m_iLoadingBarIndex = -1;
	this->m_fLoadingBarIndex = 0;
	this->m_fLoadingBarMultiplier = 0;

	this->m_bMeshLoaded = false;
	this->m_bSpriteLoaded = false;
	this->m_StateInitialized = false;
	this->m_bStateLoaded = false;

	this->m_bNewState = true;

	this->m_iMeshSteps = 0;
	this->m_iSpriteSteps = 0;

	this->m_iStepsMax = 0;
	this->m_iMeshStepsMax = 0;
	this->m_iSpriteStepsMax = 0;

	this->m_fScreenWidth = 203.0f;
	this->m_fScreenHeight = 152.25f;
	this->m_fScreenPixelWidth = 1024.0f;
	this->m_fScreenPixelHeight = 768.0f;

	this->m_iVolumeSoundEffect = 0;

#ifdef SHADOWS
	this->m_iShadowCount = 0;
#endif

	this->m_bStartLoadWaitTimer = false;
	this->m_fLoadWaitTimer = 0;

	this->m_iState = S_OK;
}

IState::~IState(void)
{
}

HRESULT IState::Create(CTheApp* pApp,
					   DWORD dwState)
{
	this->m_pApp = pApp;
	this->m_iState = dwState;

	if(!this->m_pLights)
	{
		this->m_pLights = new CLights(this->m_pApp);
	}

	InitVolumeSoundEffect();

	/* SPRITES */

	this->LoadSpritesLoadingScreen(dwState);
	this->InitLoadingBarMultiplier(dwState);

	/* FADING */

	if(!m_Fading.IsInitialized())
	{
		m_Fading.InitFading(this->m_pApp);
	}

	return S_OK;
}

void IState::InitLoadingScreenValues(int stepsMax)
{
	this->m_iLoadingBarIndex = -1;
	this->m_fLoadingBarIndex = 0;
	this->m_fLoadingBarMultiplier = 0;

	this->m_iStepsMax = stepsMax;

	this->InitLoadingBarMultiplier(this->m_iState);
}

void IState::Release()
{
	if(this->m_pLights)
	{
		this->m_pLights->Release();
		delete this->m_pLights;
		this->m_pLights = NULL;
	}

	this->m_pApp = NULL;
}

DWORD IState::Update(float fFrametime)
{
	if (this->m_fLoadWaitTimer > 0)
	{
		if (this->m_bStartLoadWaitTimer)
		{
			this->m_bStartLoadWaitTimer = false;
		}
		else
		{
			this->m_fLoadWaitTimer -= fFrametime;
		}
	}

	return S_OK;
}

void IState::BuildProjection()
{
	D3DXMATRIX m;
	D3DXMatrixOrthoLH(	&m,
						(float)this->GetApp()->GetWindowRect().right / 2.50f,
						(float)this->GetApp()->GetWindowRect().bottom / 2.50f,
						-this->m_fDepth,
						this->m_fDepth);

	this->GetApp()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m);
}

void IState::LoadSpritesLoadingScreen(DWORD dwState)
{
	CResourceMenus* resources = this->m_pApp->GetResourceMenus();

	this->m_pSpriteLoadingScreen = resources->GetSpriteLoadingScreen();
	this->m_pSpriteLoadingBar = resources->GetSpriteLoadingBar();
}

void IState::UpdateLoadingBar(int iStepsForward)
{
	this->m_fLoadingBarIndex += iStepsForward * this->m_fLoadingBarMultiplier;
	this->m_iLoadingBarIndex = (int)ceil(this->m_fLoadingBarIndex);

	if(this->m_iLoadingBarIndex > 325)
	{
		this->m_iLoadingBarIndex = 325;
	}
}

void IState::DisplayLoadingScreen()
{
	// background picture
	this->m_pSpriteLoadingScreen->Draw(0,0);
	// loading bar
	DisplayLoadingBar();
}

void IState::DisplayLoadingBar()
{
	int iBarBorderX = 336;
	int iBarBorderY = 665;

	int iBarFillX = iBarBorderX + 13;
	int iBarFillY = iBarBorderY + 13;

	if (this->m_iLoadingBarIndex >= 0)
	{
		this->m_pSpriteLoadingBar[this->m_iLoadingBarIndex].Draw(iBarFillX, iBarFillY);
	}

	this->m_pSpriteLoadingBar[ISTATE_LOADING_BAR_MAX - 1].Draw(iBarBorderX, iBarBorderY);
}

void IState::InitLoadingBarMultiplier(DWORD dwState)
{
	this->m_fLoadingBarMultiplier = (float)(ISTATE_LOADING_BAR_MAX - 1) / (this->m_iStepsMax - 6);
}

void IState::InitVolumeSoundEffect()
{
	int iVolume = this->m_pApp->GetConfig().GetVolumeSoundEffect();

	if (iVolume == 0)
	{
		this->m_iVolumeSoundEffect = -10000;
	}
	else
	{
		this->m_iVolumeSoundEffect = (iVolume - 100) * 50;
	}
}
