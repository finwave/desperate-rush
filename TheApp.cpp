/**
 * A concrete game application class.
 * Uses virtualized state machine to
 * create application states.
 */

#include "TextUtils.h"
#include "TheApp.h"

// include application states
#include "StateIntro.h"
#include "StateMenus.h"
#include "StateGame.h"
#include "StateHighScore.h"

CTheApp::CTheApp(void)
{
	// MP3 player requires to manually initialise COM objects
	::CoInitialize(NULL);

	// initialise member variables
	this->m_pState = NULL;
	this->m_dwFirstState = STATE_MENUS;
	this->m_pVBBackground = NULL;

	this->m_iTextY = 0;

	this->m_iCurrentMouseX = 500;
	this->m_iCurrentMouseY = 302;
	this->m_iCurrentMouseZ = 0;

	UpdatePreviousMousePos();

#ifdef SHADOWS
	this->m_pShadowVolumes = NULL;
#endif

	this->m_iMenuSoundLoadIndex = 0;
	this->m_iMenuSoundLoadStepCounter = 0;

	this->m_bLoadGameSoundFiles = true;

	this->m_bShowLoadingScreen = false;
	this->m_bCreateState = true;

	this->m_pCamera = NULL;

	this->m_iMousePosX = 0;
	this->m_iMousePosY = 0;
	this->m_iMousePosZ = 0;
}

CTheApp::~CTheApp(void)
{
	// MP3 player requires to manually uninitialise COM objects
	::CoUninitialize();
}

HRESULT CTheApp::OnCreate(void)
{
	HRESULT hres;

	// initialise the input engine
	hres = this->m_InputEngine.Create(GetWindow());

	if(FAILED(hres))
	{
		::MessageBox(	GetWindow(),
						_T("Failed to create input engine"),
						_T("ERROR!"),
						MB_OK);
		return hres;
	}

	this->m_ZipManager.Initialize();
	this->m_ResourceMenus.Init(this, &m_ZipManager);
	this->m_ResourceGame.Init(this, &m_ZipManager);
	this->m_ResourceHighScore.Init(this, &m_ZipManager);

	// get installed input devices into the array
	this->m_InputEngine.GetKeyboards(&m_arrInputDevices);
	this->m_InputEngine.GetMice(&m_arrInputDevices);
	this->m_InputEngine.GetJoysticks(&m_arrInputDevices);

	// create default keyboard
	this->m_Keyboard.Create(&m_InputEngine, NULL, 0);

	// create default mouse
	this->m_Mouse.Create(&m_InputEngine, NULL, 0);

	// initialise mouse coordinates
	if(IsWindowed())
	{
		POINT mousepos;
		::GetCursorPos(&mousepos);
		::ScreenToClient(GetWindow(), &mousepos);
		this->m_iCurrentMouseX = mousepos.x;
		this->m_iCurrentMouseY = mousepos.y;
	}

	hres = CreateJoystick();

	if(FAILED(hres))
	{
		::MessageBox(	GetWindow(),
						_T("Failed to create joystick"),
						_T("ERROR"),
						MB_OK);
	}

	// initialise the music manager
	this->m_pMusicManager = new CMusicManager();
	this->m_pMusicManager->Init(this);

	// initialise the sound engine
	hres = this->m_SoundEngine.Create(GetWindow(), 44100, 16, 2, 0);

	if(FAILED(hres))
	{
		::MessageBox(	GetWindow(),
						_T("Failed to create sound engine"),
						_T("ERROR!"),
						MB_OK);
		return hres;
	}

	// create vb for background
	hres = GetDevice()->CreateVertexBuffer(	4 * sizeof(TRANSLITVERTEX),
											0,
											TRANSLITVERTEX::GetFVF(),
											D3DPOOL_MANAGED,
											&m_pVBBackground,
											NULL);

	if(FAILED(hres))
	{
		ErrorMessage(hres);
		return hres;
	}

	SetBackgroundQuad();

	// hide mouse cursor
	GetDevice()->ShowCursor(FALSE);
	
	// generate random seed
	this->m_fRandomSeed = static_cast<unsigned int>(time(NULL));

	// create camera interface
	this->m_pCamera = new Camera();
	this->m_pCamera->Init(this->GetDevice());

	return S_OK;
}

HRESULT CTheApp::LoadSoundFiles()
{
	HRESULT hres;
	std::string resourcePath;

	int volumeSoundEffect = GetVolumeSoundEffect();

	// load the wave files

	DWORD dwDuplicates = 0;

	if (this->m_iMenuSoundLoadIndex >= FIRST_DUPLICATE_SOUND)
	{
		dwDuplicates = DUPLICATE_SOUND_BUFFER;
	}

	resourcePath = this->m_ZipManager.GetResourceFilePath(waveFilenames[this->m_iMenuSoundLoadIndex].c_str());
	LPCTSTR strFilename = TextUtils::StringToLPCWSTR(resourcePath);

	hres = this->m_Waves[this->m_iMenuSoundLoadIndex].Load(&m_SoundEngine, strFilename,
		dwDuplicates, DSBCAPS_CTRLVOLUME);

	if (FAILED(hres))
	{
		ErrorMessage(hres);
		return hres;
	}

	// set volume of sound effect
	this->m_Waves[this->m_iMenuSoundLoadIndex].SetVolume(volumeSoundEffect, dwDuplicates);

	this->m_iMenuSoundLoadIndex++;
	this->m_iMenuSoundLoadStepCounter++;

	return S_OK;
}

bool CTheApp::IsMenuSoundLoadWaitCycle()
{
	if (this->m_iMenuSoundLoadStepCounter >= SOUND_FILES_LOAD_STEPS_WAIT)
	{
		this->m_iMenuSoundLoadStepCounter = 0;
		return true;
	}

	return false;
}

void CTheApp::OnRelease(void)
{
	// release background vertices
	if(this->m_pVBBackground)
	{
		this->m_pVBBackground->Release();
		this->m_pVBBackground = NULL;
	}

	// release application state
	if(this->m_pState)
	{
		this->m_pState->Release();
		delete m_pState;
		this->m_pState = NULL;
	}

#ifdef SHADOWS
	// release shadow volumes
	if(this->m_pShadowVolumes)
	{
		this->m_pShadowVolumes = NULL;
	}
#endif

	// release all wave files
	for (int i = 0; i < NUM_WAVES; i++)
	{
		this->m_Waves[i].Release();
	}

	// release sound engine
	this->m_SoundEngine.Release();

	// release music manager
	if (this->m_pMusicManager)
	{
		this->m_pMusicManager->Release();
		delete this->m_pMusicManager;
		this->m_pMusicManager = NULL;
	}

	// clear the device array
	this->m_arrInputDevices.clear();

	this->m_Joystick.Release();
	this->m_Mouse.Release();
	this->m_Keyboard.Release();

	// release the input engine
	this->m_InputEngine.Release();
}

void CTheApp::OnFlip(void)
{
	static DWORD dwState = this->m_dwFirstState;

	// close the application
	if(dwState == STATE_EXIT_APP)
	{
		Close();
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// clear buffers
	ClearBuffers(pDevice);

	// state is not yet created
	if( !this->m_pState || this->m_pState->IsNewState() )
	{
		if(dwState != STATE_RUNNING)
		{
			// create new state & show loading screen
			if(this->m_bCreateState)
			{
				// change to new state (create state)
				HRESULT hres = ChangeState(dwState);

				if(FAILED(hres))
				{
					ErrorMessage(hres);
					Close();
				}

				// change font
				if(dwState == STATE_GAME)
				{
					hres = SetTextFontParam(-12, 450, 0);

					if(FAILED(hres))
					{
						ErrorMessage(hres);
						Close();
					}
				}

				// new state is created
				this->m_bCreateState = false;

				// all graphics rendering must happen in between
				// BeginScene and EndScene function calls
				if(SUCCEEDED(pDevice->BeginScene()) )
				{
					// show loading screen for this render cycle
					if (this->m_bShowLoadingScreen)
					{
						this->m_pState->DisplayLoadingScreen();
					}

					// EndScene function call
					pDevice->EndScene();
				}
			}
			else
			{
				// all graphics rendering must happen in between
				// BeginScene and EndScene function calls
				if(SUCCEEDED(pDevice->BeginScene()) )
				{
					// show loading screen for this render cycle
					if (this->m_bShowLoadingScreen)
					{
						this->m_pState->DisplayLoadingScreen();
					}

					// state has not finished loading
					if( !this->m_pState->IsStateLoaded() )
					{
						// update state (this updates "load wait timer" value)
						this->m_pState->Update(GetFrameTime());
						// initialize new state by loading resources
						HRESULT hres = this->InitState(dwState);

						if(FAILED(hres))
						{
							ErrorMessage(hres);
							Close();
						}
					}
					else
					{
						// new state is created and initialized
						m_pState->SetNewState(false);

						CheckKeyPushes();

						if (dwState != STATE_GAME)
						{
							// Game state itself is hiding the loading screen.
							// Otherwise we need to hide the loading screen here.
							this->m_bShowLoadingScreen = false;
						}
					}

					// EndScene function call
					pDevice->EndScene();
				}
			}
		}
	}
	// state is created
	else
	{
		// all graphics rendering must happen in between
		// BeginScene and EndScene function calls
		if(SUCCEEDED(pDevice->BeginScene()) )
		{
			if(this->m_bShowLoadingScreen)
			{
				this->m_pState->DisplayLoadingScreen();
			}

			// render state
			this->m_pState->Render();
			// update state
			const float fFrametime = GetFrameTime();
			this->m_pMusicManager->Update(fFrametime);
			dwState = this->m_pState->Update(fFrametime);

			// EndScene function call
			pDevice->EndScene();
		}
	}
}

void CTheApp::OnKeyDown(DWORD dwKey)
{
	// pass key events to current state
	if(this->m_pState)
	{
		this->m_pState->OnKeyDown(dwKey);
	}
}

void CTheApp::OnKeyUp(DWORD dwKey)
{
	// pass key events to current state
	if (this->m_pState)
	{
		this->m_pState->OnKeyUp(dwKey);
	}
}

void CTheApp::OnSize(DWORD dwType, int iWidth, int iHeight)
{
	ID3DApplication::OnSize(dwType, iWidth, iHeight);
	SetBackgroundQuad();
}

HRESULT CTheApp::ChangeState(DWORD dwState)
{
	// delete previous state
	if(this->m_pState)
	{
		this->m_pState->Release();
		delete this->m_pState;
		this->m_pState = NULL;
	}

	HRESULT hres = S_OK;

	// create new state
	switch (dwState)
	{
	case STATE_MENUS:
		this->m_pState = new CStateMenus;
		break;

	case STATE_GAME:
		this->m_pState = new CStateGame;
		break;

	case STATE_HIGHSCORE:
		this->m_pState = new CStateHighScore;
		break;

	default:
		// unknown new state, FATAL ERROR!
		return E_NOTIMPL;
	}

	if (this->m_pState != NULL)
	{
		hres = this->m_pState->Create(this, dwState);
	}

	return hres;
}

HRESULT CTheApp::InitState(DWORD dwState)
{
	HRESULT hres = S_OK;

	// init new state
	switch (dwState)
	{
	case STATE_MENUS:
	case STATE_GAME:
	case STATE_HIGHSCORE:
		hres = this->m_pState->InitState(dwState);
		break;

	default:
		// unknown new state, FATAL ERROR!
		return E_NOTIMPL;
		break;
	}

	return hres;
}

void CTheApp::SetBackgroundQuad()
{
	if(!m_pVBBackground)
	{
		return;
	}

	TRANSLITVERTEX* vertices = NULL;
	m_pVBBackground->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].z = 1.0f;
	vertices[0].rhw = 0.0f;
	vertices[0].tu = 0.0f;
	vertices[0].tv = 0.0f;

	vertices[1].x = (float)GetScreenRect().right;
	vertices[1].y = 0.0f;
	vertices[1].z = 1.0f;
	vertices[1].rhw = 0.0f;
	vertices[1].tu = 1.0f;
	vertices[1].tv = 0.0f;

	vertices[2].x = (float)GetScreenRect().right;
	vertices[2].y = (float)GetScreenRect().bottom;
	vertices[2].z = 1.0f;
	vertices[2].rhw = 0.0f;
	vertices[2].tu = 1.0f;
	vertices[2].tv = 1.0f;

	vertices[3].x = 0.0f;
	vertices[3].y = (float)GetScreenRect().bottom;
	vertices[3].z = 1.0f;
	vertices[3].rhw = 0.0f;
	vertices[3].tu = 0.0f;
	vertices[3].tv = 1.0f;

	vertices[0].dwColor = 0xFFFFFFFF;
	vertices[1].dwColor = 0xFFFFFFFF;
	vertices[2].dwColor = 0xFFFFFFFF;
	vertices[3].dwColor = 0xFFFFFFFF;

	m_pVBBackground->Unlock();
}

void CTheApp::ClearBuffers(LPDIRECT3DDEVICE9 device)
{
	// clear the back buffer and z-buffer
	// displays specified background color
	//MUST CLEAR to BLACK (0,0,0) to stop it interfering with additive lighting
	device->Clear(	0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					0x00000000, 1.0f, 0);
}

float CTheApp::GetScreenWidth()
{
	return m_pState->GetScreenWidth();
}

float CTheApp::GetScreenHeight()
{
	return m_pState->GetScreenHeight();
}

void CTheApp::SetTextY(int iTextY)
{
	this->m_iTextY = iTextY;
}

// CreateJoystick
// intialise the first found joystick device
HRESULT CTheApp::CreateJoystick(void)
{
	// create joystick
	HRESULT hres;
	std::vector<CInputEngine::DEVICE> arrJoysticks;
	m_InputEngine.GetJoysticks(&arrJoysticks);

	if(arrJoysticks.size())
	{
		// at least one joystick found, 
		// create instance from first one.
		hres = m_Joystick.Create(	&m_InputEngine,
									&arrJoysticks[0],
									DISCL_EXCLUSIVE |
									DISCL_BACKGROUND);
		if(FAILED(hres))
		{
			return hres;
		}
		m_Joystick.SetAxisRange(DIJOFS_X, -100, 100);
		m_Joystick.SetAxisRange(DIJOFS_Y, -100, 100);

		// for this example we use 50% of deadzone
		// works very well with digital gamepads
		m_Joystick.SetDeadZone(DIJOFS_X, 5000);
		m_Joystick.SetDeadZone(DIJOFS_Y, 5000);

		arrJoysticks.clear();
	}
	return S_OK;
}

void CTheApp::UpdateKeyboard(void)
{
	DWORD i;
	TCHAR msg[256];

	if(SUCCEEDED(m_Keyboard.Update()))
	{
		for(i=0; i<m_Keyboard.GetButtonCount(); i++)
		{
			if(m_Keyboard.GetButton(i))
			{
				// print the keycode
				_stprintf_s(msg, _T("KEYBOARD: %d DOWN"), i);

				DrawText(	0,
							m_iTextY,
							msg,
							D3DXCOLOR(0, 0, 0, 1.0f));

				m_iTextY += GetTextHeight();
			}
		}
	}

	m_iTextY += GetTextHeight();
}

void CTheApp::UpdateJoystick(void)
{
	TCHAR msg[256];

	if(SUCCEEDED(m_Joystick.Update()))
	{
		// print joystick data
		_stprintf_s(	msg,
						_T("JOY X:%d - Y:%d"),
						m_Joystick.GetState().lX,
						m_Joystick.GetState().lY);
		DrawText(	0, 
					m_iTextY,
					msg,
					D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		m_iTextY += GetTextHeight();

		// print joystick buttons
		DWORD i;
		for (i=0; i<m_Joystick.GetButtonCount(); i++)
		{
			if(m_Joystick.GetButton(i))
			{
				_stprintf_s(	msg,
								_T("JOY BUTTON: %d"),
								i);
				DrawText(	0, 
							m_iTextY,
							msg,
							D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
				m_iTextY += GetTextHeight();
			}
		}
	}
	m_iTextY += GetTextHeight();
}

/*
void CTheApp::UpdateMouse()
{
	// update the mouse
	if(SUCCEEDED(m_Mouse.Update()))
	{
		if (!m_bMouseDrag && m_Mouse.GetButton(0))
		{
			m_bMouseDrag = true;

			m_iMousePosX = m_Mouse.GetState().lX;
			m_iMousePosY = m_Mouse.GetState().lY;
			m_iMousePosZ = m_Mouse.GetState().lZ;
		}
		else if (m_bMouseDrag && !m_Mouse.GetButton(0))
		{
			m_bMouseDrag = false;

			m_iMousePosX = 0;
			m_iMousePosY = 0;
			m_iMousePosZ = 0;
		}

		if (m_bMouseDrag)
		{
			int deltaX = m_iMousePosX - m_Mouse.GetState().lX;
			int deltaY = m_iMousePosY - m_Mouse.GetState().lY;
			int deltaZ = m_iMousePosZ - m_Mouse.GetState().lZ;

			m_iMousePosX = m_Mouse.GetState().lX;
			m_iMousePosY = m_Mouse.GetState().lY;
			m_iMousePosZ = m_Mouse.GetState().lZ;
		}
	}

	UpdateCamera(m_iMousePosX, m_iMousePosY, m_iMousePosZ);
}

void CTheApp::UpdateCamera(int iDeltaX, int iDeltaY, int iDeltaZ)
{
	this->m_pCamera->UpdateDelta(iDeltaX, iDeltaY, iDeltaZ);
	this->m_pCamera->Update(this->GetDevice());
}
*/

void CTheApp::UpdateMouse(void)
{
	// update the mouse
	if(SUCCEEDED(m_Mouse.Update()))
	{
		// increment mouse position based on changes from previous update

		UpdatePreviousMousePos();

		m_iCurrentMouseX += m_Mouse.GetState().lX;
		m_iCurrentMouseY += m_Mouse.GetState().lY;
		m_iCurrentMouseZ += m_Mouse.GetState().lZ;

		// keep mouse coordinates inside our window

		if(m_iCurrentMouseX < 0)
		{
			m_iCurrentMouseX = 0;
		}

		if(m_iCurrentMouseY < 0)
		{
			m_iCurrentMouseY = 0;
		}

		const int iMaxX = GetWindowRect().right - 20;
		if(m_iCurrentMouseX > iMaxX)
		{
			m_iCurrentMouseX = iMaxX;
		}

		const int iMaxY = GetWindowRect().bottom - 20;
		if(m_iCurrentMouseY > iMaxY)
		{
			m_iCurrentMouseY = iMaxY;
		}
	}
}

void CTheApp::UpdatePreviousMousePos()
{
	m_iPreviousMouseX = m_iCurrentMouseX;
	m_iPreviousMouseY = m_iCurrentMouseY;
	m_iPreviousMouseZ = m_iCurrentMouseZ;
}

void CTheApp::UpdateCharCursor(void)
{
	// print 'x' char to act as "virtual" cursor
	DrawText(	m_iCurrentMouseX,
				m_iCurrentMouseY,
				_T("X"),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

char* CTheApp::GetButtonPress(void)
{
	char* pHex = NULL;

	if(SUCCEEDED(m_Keyboard.Update()))
	{
		for(DWORD i = 0; i < m_Keyboard.GetButtonCount(); i++)
		{
			if(m_Keyboard.GetButton(i))
			{
				pHex = m_keyReference.GetHex(i);

				// button pressed is not supported by the game
				// doesn't have a valid hex value in m_keyReference object
				if(pHex[2] == 'Í' || pHex[3] == 'Í')
				{
					pHex = NULL;
				}

				break;
			}
		}
	}

	if (pHex != NULL)
	{
		pHex = TextUtils::SubstrFromChar(pHex, 4);
	}

	return pHex;
}

int CTheApp::GetVolumeMusic()
{
	int iVolume;

	if(this->GetConfig().GetVolumeMusic() == 0)
	{
		iVolume = -10000;
	}
	else
	{
		iVolume = (this->GetConfig().GetVolumeMusic() - 100) * 50;
	}

	return iVolume;
}

int CTheApp::GetVolumeSoundEffect()
{
	int iVolume;

	if(this->GetConfig().GetVolumeSoundEffect() == 0)
	{
		iVolume = -10000;
	}
	else
	{
		iVolume = (this->GetConfig().GetVolumeSoundEffect() - 100) * 50;
	}

	return iVolume;
}

void CTheApp::CheckKeyPushes()
{
	//START********** CHECK CONTROLS *******************//

	// goes through player control keys, existing button 
	// presses are automatically removed from queue
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyMode()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyBlast()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyCannon()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyMinigun()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyUp()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyDown()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyLeft()) ) {}
	if( ::GetAsyncKeyState(this->GetConfig().GetVkeyRight()) ) {}

	// also checks and eliminates following key presses
	if( ::GetAsyncKeyState(VK_ESCAPE) ) {}
	if( ::GetAsyncKeyState(VK_RETURN) ) {}
	if( ::GetAsyncKeyState(VK_UP) ) {}
	if( ::GetAsyncKeyState(VK_DOWN) ) {}

	//END************ CHECK CONTROLS *******************//
}

void CTheApp::HideFile(std::string fileName, bool bHide)
{
	DWORD dwAttrs;
	WCHAR wideFilename[50];

	int nLen = MultiByteToWideChar(	CP_ACP,
									0,
									fileName.c_str(),
									-1,
									NULL,
									NULL);

	MultiByteToWideChar(	CP_ACP,
							0,
							fileName.c_str(),
							-1,
							wideFilename,
							nLen);

	dwAttrs = GetFileAttributes(wideFilename);

	if(dwAttrs != INVALID_FILE_ATTRIBUTES)
	{
		// hide file
		if(bHide)
		{
			if(!(dwAttrs & FILE_ATTRIBUTE_HIDDEN)) 
			{ 
				SetFileAttributes(wideFilename, FILE_ATTRIBUTE_HIDDEN);
			}
		}
		// unhide file
		else
		{
			if(dwAttrs & FILE_ATTRIBUTE_HIDDEN) 
			{ 
				SetFileAttributes(wideFilename, FILE_ATTRIBUTE_NORMAL);
			}
		}
	}
}

void CTheApp::ShowFrames(void)
{
	this->BeginText();

	// draw frame speed
	TCHAR msg[256];
	_stprintf_s(	msg,
					_T("FPS: %.2f"),
					1.0f / GetFrameTime());

	DrawText(	936,
				710,
				msg,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	this->EndText();
}

// Source: https://stackoverflow.com/questions/27090069/check-if-a-string-of-type-char-contains-another-string
bool CTheApp::IsCharPartOf(const char* target, const char* matcher)
{
	int i = 0;
	int j = 0;

	while (target[i] != '\0')
	{
		if (target[i] == matcher[j])
		{
			int init = i;

			while ((target[i] == matcher[j]) && (matcher[j] != '\0'))
			{
				j++;
				i++;
			}

			if (matcher[j] == '\0')
			{
				return true;
			}

			j = 0;
		}

		i++;
	}

	return false;
}

void CTheApp::ErrorMessage(int iError)
{
	std::string hexError = TextUtils::IntToHex(iError);
	std::string strError;

	if(hexError.compare("8000ffff") == 0)
	{
		strError = "Unexpected Error";
	}
	else if(hexError.compare("80004001") == 0)
	{
		strError = "Not Implemented";
	}
	else if(hexError.compare("8007000e") == 0)
	{
		strError = "Out of Memory";
	}
	else if(hexError.compare("80070057") == 0)
	{
		strError = "Invalid Argument";
	}
	else if(hexError.compare("80004002") == 0)
	{
		strError = "No Interface";
	}
	else if(hexError.compare("80004004") == 0)
	{
		strError = "Action Terminated";
	}
	else if(hexError.compare("80004005") == 0)
	{
		strError = "Action Failed";
	}
	else
	{
		strError = "Unknown Error";
	}

	LPCWSTR message = TextUtils::StringToLPCWSTR(strError);
	::MessageBox(GetWindow(), message, _T("ERROR!"), MB_OK);
}

#ifdef SHADOWS
void CTheApp::RenderScene()
{
	LPDIRECT3DDEVICE9 pDevice = this->GetDevice();

	this->GetShadowVolumes();

	int iLightCount = this->m_pState->GetLights()->GetLightCount();
	int* iLightIndex = this->m_pState->GetLights()->GetLightIndex();

#ifdef SHADOW_VOLUME_COMBINE_FIRST_2_PASSES

	//colour buffer ON
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//ambient lighting ON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	pDevice->SetRenderState( D3DRS_AMBIENT, AMBIENT_LIGHT );

	for(int i = 0; i < 10; i++)
	{
		pDevice->LightEnable(i, FALSE);
	}

	//depth buffer ON (write+test)
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//stencil buffer OFF
	pDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );

	//FIRST PASS: render scene to the depth buffer
	this->m_pState->Render();

	//OPTIMISED: all subsequent rendering is subject to this
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

#else
	
	//A. Render the first pass:

	//colour buffer OFF
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//lighting OFF
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//depth buffer ON (write+test)
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//stencil buffer OFF
	pDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );

	//FIRST PASS: render scene to the depth buffer
	this->m_pState->Render();

	//OPTIMISED: all subsequent rendering is subject to this
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

	//B. Render the second pass:

	//colour buffer ON
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//ambient lighting ON
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	pDevice->SetRenderState( D3DRS_AMBIENT, AMBIENT_LIGHT );

	for(int i = 0; i < 10; i++)
	{
		pDevice->LightEnable(i, FALSE);
	}

	//SECOND PASS: render scene to the colour buffer
	this->m_pState->Render();

#endif

	//C. Render all subsequent passes for each light

	// colour buffer OFF
	// ambient lighting OFF
	// depth buffer ON (test ONLY)
	// stencil buffer OFF

	for(int i = 0; i < iLightCount; i++)
	{
		D3DLIGHT9 light;

		// get the current light
		pDevice->GetLight(iLightIndex[i], &light);

		// light source is point-type
		if ( light.Type == D3DLIGHT_POINT )
		{
			//clear stencil buffer
			pDevice->Clear( 0, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

			//turn OFF colour buffer
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

			//disable lighting (not needed for stencil writes!)
			pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

			//turn ON stencil buffer
			pDevice->SetRenderState( D3DRS_STENCILENABLE,	TRUE );
			pDevice->SetRenderState( D3DRS_STENCILFUNC,		D3DCMP_ALWAYS );

			//render shadow volumes

			//OPTIMISED: use support for 2-sided stencil
			if (this->m_b2SidedStencils)
			{
				//USE THE LATEST 1-PASS METHOD
				
				//configure the necessary render states
				pDevice->SetRenderState( D3DRS_STENCILPASS,			D3DSTENCILOP_INCR );
				pDevice->SetRenderState( D3DRS_CULLMODE,			D3DCULL_NONE );
				pDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE, TRUE );

				//render the geometry once to the stencil buffer
				for(int j = 0; j < this->m_pState->GetShadowCount(); j++)
				{
					this->m_pShadowVolumes[j].Render(pDevice);
				}

				//reset any necessary states
				pDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE, FALSE );
			}
			// USE THE TRADITIONAL 2-PASS METHOD
			else
			{
				//set stencil to increment
				pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR );
				//render front faces
				pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
				for(int j = 0; j < this->m_pState->GetShadowCount(); j++)
				{
					this->m_pShadowVolumes[j].Render(pDevice);
				}

				//set stencil to decrement
				pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR );
				//render back faces
				pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
				for(int j = 0; j < this->m_pState->GetShadowCount(); j++)
				{
					this->m_pShadowVolumes[j].Render(pDevice);
				}
				
				pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
			}

			//alter stencil buffer
			pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_GREATER );
			pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );

			//turn on/off lights
			pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
			//turn off ambient light
			pDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0) );
			//turn on CURRENT light, turn off all others
			for(int k = 0; k < 10; k++)
			{
				pDevice->LightEnable(k, k == iLightIndex[i] ? true : false );
			}
				
			//turn ON colour buffer
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				
			//render scene
			this->m_pState->Render();
			
			//reset any necessary render states
			pDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		}
	}
}


void CTheApp::GetShadowVolumes()
{
	static int iShadowUpdateSpeed = 2;

#ifdef SHADOW_VOLUME_UPDATE_ALTERNATE

	// NOTE: setting the value here to anything higher than
	// 3 gives noticably poor results. The frame rate
	// will remain high, but the shadows appear very jerky
	if(iShadowUpdateSpeed >= 1 )
	{
		this->m_pShadowVolumes = this->m_pState->GetShadowVolumes();
		iShadowUpdateSpeed = 0;
	}
	else
	{
		iShadowUpdateSpeed++;
	}

#else
	
	this->m_pShadowVolumes = this->m_pState->GetShadowVolumes();

#endif
}
#endif
