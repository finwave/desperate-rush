/**
 * Class implements joystick input device.
 */

#include "InputJoystick.h"

CInputJoystick::CInputJoystick(void)
{
	// initialise the members
	::memset(&m_State, 0, sizeof(DIJOYSTATE2));
	m_bIsForce = FALSE;
}

CInputJoystick::~CInputJoystick(void)
{
}


// Create
// initialise the input device
HRESULT CInputJoystick::Create(	CInputEngine* pEngine,
								CInputEngine::DEVICE* pDevice,
								DWORD dwFlags)
{
	// get the DirectInput object
	LPDIRECTINPUT8	pDI = pEngine->GetInput();
	if(pDI == NULL || pDevice == NULL)
	{
		return E_FAIL;
	}

	HRESULT hres;
	GUID	gdDevice;

	gdDevice = pDevice->gdDevice;

	// create the DirectInput device object
	hres = pDI->CreateDevice(	gdDevice,
								&m_pDevice,
								NULL);
	if(FAILED(hres))
	{
		return hres;
	}

	// set input device data format
	m_pDevice->SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	// set the cooperative level
	if(dwFlags == 0)
	{
		// if user didn't specify any flags, use these as
		// default.

		// DISCL_NONEXCLUSIVE
		// gives access to input device also to other applications
		// DISCL_FOREGROUND
		// we get input from device only when our application
		// is active and in foreground
		dwFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	}
	hres = m_pDevice->SetCooperativeLevel(	pEngine->GetWindow(),
											dwFlags);
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	m_dwButtonCount = CountButtons();

	// check if joystick supports force feedback
	DIDEVCAPS			caps;
	::memset(&caps, 0, sizeof(DIDEVCAPS));
	caps.dwSize = sizeof(DIDEVCAPS);
	m_pDevice->GetCapabilities(&caps);

	m_bIsForce = FALSE;
	if((caps.dwFlags & DIDC_FORCEFEEDBACK))
	{
		m_bIsForce = TRUE;
	}

	// acquire the input device
	m_pDevice->Acquire();
	return S_OK;
}


// Update
// get the current state of the input device
HRESULT CInputJoystick::Update(void)
{
	if(m_pDevice == NULL)
	{
		// invalid user error...
		return E_FAIL;
	}

	HRESULT hres;

	// ask joystick state
	hres = m_pDevice->GetDeviceState(sizeof(DIJOYSTATE2), &m_State);
	if(FAILED(hres))
	{
		// if getting the device state fails, most likely
		// another application has gained the input device
		// focus, and we have lost it...

		// try to acquire the device back to us
		m_pDevice->Acquire();

		// ask device state again
		hres = m_pDevice->GetDeviceState(sizeof(DIJOYSTATE2), &m_State);
		if(FAILED(hres))
		{
			// can't get the focus back...
			// nothing much we can do about it...
			::memset(&m_State, 0, sizeof(DIJOYSTATE2));
			return hres;
		}
	}
	return S_OK;
}


// GetButton
// returns TRUE if specified joystick button is down
BOOL CInputJoystick::GetButton(DWORD dwButtonIndex) const
{
	if(dwButtonIndex >= m_dwButtonCount)
	{
		return FALSE;
	}

	return m_State.rgbButtons[dwButtonIndex] ? TRUE : FALSE;
}



// CountButtons
// does what is says
DWORD CInputJoystick::CountButtons(void)
{
	DIDEVICEOBJECTINSTANCE		didoi;

	::memset(&didoi, 0, sizeof(DIDEVICEOBJECTINSTANCE));
	didoi.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

	DWORD dwButtons = 0;

	// try to get info about 128 mouse buttons
	// if 'GetObjectInfo' fails, that button is not present
	int i;
	for (i=0; i<128; i++)
	{
		if(SUCCEEDED(m_pDevice->GetObjectInfo(	&didoi,
												DIJOFS_BUTTON(i),
												DIPH_BYOFFSET)))
		{
			dwButtons++;
		}
	}
	return dwButtons;
}


// SetAxisRange
// set the data range for specific joystick axis
// dwAxis:
// DIJOFS_X, DIJOFS_Y, DIJOFS_Z
void CInputJoystick::SetAxisRange(DWORD dwAxis, int iMin, int iMax)
{
	if(m_pDevice == NULL)
	{
		return;
	}

	// device must be unacquired when changing settings
	m_pDevice->Unacquire();

	DIPROPRANGE		range;
	::memset(&range, 0, sizeof(DIPROPRANGE));
	range.diph.dwSize = sizeof(DIPROPRANGE);
	range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	range.diph.dwHow = DIPH_BYOFFSET;
	range.diph.dwObj = dwAxis;

	range.lMin = iMin;
	range.lMax = iMax;

	m_pDevice->SetProperty(DIPROP_RANGE, &range.diph);
	m_pDevice->Acquire();
}


// SetDeadZone
// adjust joystick deadzone area.
// iDeadzone parameter is always value in range
// 0-10000, where 0 is no deadzone, 5000 is 50%
// deadzone, and so on.
// dwAxis:
// DIJOFS_X, DIJOFS_Y, DIJOFS_Z
void CInputJoystick::SetDeadZone(DWORD dwAxis, int iDeadzone)
{
	if(m_pDevice == NULL)
	{
		return;
	}

	// device must be unacquired when changing settings
	m_pDevice->Unacquire();

	DIPROPDWORD		range;
	::memset(&range, 0, sizeof(DIPROPDWORD));
	range.diph.dwSize = sizeof(DIPROPDWORD);
	range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	range.diph.dwHow = DIPH_BYOFFSET;
	range.diph.dwObj = dwAxis;

	range.dwData = iDeadzone;

	m_pDevice->SetProperty(DIPROP_DEADZONE, &range.diph);
	m_pDevice->Acquire();
}


// FFReset
// reset the force feedback device and
// disable the autocentering spring
HRESULT CInputJoystick::FFReset()
{
	if(!IsForce() || !m_pDevice)
	{
		return DIERR_UNSUPPORTED;
	}

	HRESULT		hres;
	m_pDevice->Unacquire();

	// turn off the autocentering spring
	DIPROPDWORD			prop;
	::memset(&prop, 0, sizeof(DIPROPDWORD));
	prop.diph.dwSize = sizeof(DIPROPDWORD);
	prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	prop.diph.dwHow = DIPH_DEVICE;

	hres = m_pDevice->SetProperty(DIPROP_AUTOCENTER, &prop.diph);
	if(FAILED(hres))
	{
		return hres;
	}

	// reset the force feedback device
	hres = m_pDevice->SendForceFeedbackCommand(DISFFC_RESET);
	if(FAILED(hres))
	{
		return hres;
	}

	m_pDevice->Acquire();
	return S_OK;
}


