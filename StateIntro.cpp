/**
 * This class implements
 * game application "intro" state.
 */

#include "StateIntro.h"

CStateIntro::CStateIntro(void)
{
	
	this->m_pSpriteBackground = NULL;
	this->m_dwNextState = STATE_RUNNING;
	this->m_fIntroTimer = 90.0f;
}


CStateIntro::~CStateIntro(void)
{
}


HRESULT CStateIntro::Create(CTheApp* pApp,
							DWORD dwState)
{
	HRESULT hres;

	// remember to call base class implementation
	// to properly initialise the state.
	hres = IState::Create(pApp, dwState);

	if( FAILED(hres) )
	{
		return hres;
	}

	return S_OK;
}

HRESULT CStateIntro::InitState(DWORD dwState)
{
	HRESULT hres;
	LPDIRECT3DDEVICE9 pDevice = this->GetApp()->GetDevice();

	// load the background texture

	this->m_pSpriteBackground = new CSprite();

	if( !this->m_pSpriteBackground )
	{
		return E_OUTOFMEMORY;
	}

	CResourceMenus* resourceMenus = this->GetApp()->GetResourceMenus();
	resourceMenus->SetSpriteFilePath("textures/intro/");

	hres = this->m_pSpriteBackground->Create(
		"background.jpg", pDevice, 0.2f);

	if(FAILED(hres))
	{
		return hres;
	}

	/** MUSIC **/

	// music has volume
	if(this->GetApp()->GetConfig().GetVolumeMusic() > 0)
	{
		// load main music
		LPCTSTR resourceFilePath = resourceMenus->GetUnpackedResourceFilePath("music/intro.mp3");
		this->GetApp()->GetMP3Player1().Create(resourceFilePath);

		// set music volume
		this->GetApp()->GetMP3Player1().SetVolume(this->GetApp()->GetVolumeMusic());
		this->GetApp()->GetMP3Player1().Play();
	}

	this->SetStateLoaded(true);
	this->GetApp()->SetLoadingScreen(false);

	return S_OK;
}


void CStateIntro::Release()
{
	// release background texture
	if(this->m_pSpriteBackground)
	{
		this->m_pSpriteBackground->Release();
		delete this->m_pSpriteBackground;
		this->m_pSpriteBackground = NULL;
	}

	// remember to call base class implementation
	// to properly release the state.
	//IState::Release();
}


DWORD CStateIntro::Update(float fFrametime)
{
	m_fIntroTimer -= fFrametime;

	if(m_fIntroTimer <= 0.0f)
	{
		// go to main menu
		this->m_dwNextState = STATE_MENUS;

		// music has volume
		if(this->GetApp()->GetConfig().GetVolumeMusic() > 0)
		{
			// stop music playback
			GetApp()->GetMP3Player1().Stop();
			// release music
			GetApp()->GetMP3Player1().Release();
		}
	}

	return this->m_dwNextState;
}


void CStateIntro::Render()
{
	// render background
	this->m_pSpriteBackground->Draw(0,0);

	GetApp()->UpdateMouse();

	// left mouse button is pressed
	if(this->GetApp()->GetMouse()->GetButton(0))
	{
		// set intro timer to 0
		this->m_fIntroTimer = 0.0f;
	}
}


void CStateIntro::OnKeyDown(DWORD dwKey)
{
	// end intro
	if(dwKey == VK_ESCAPE || dwKey == VK_RETURN || dwKey == VK_SPACE)
	{
		// set intro timer to 0
		this->m_fIntroTimer = 0.0f;
	}
}
