/**
 * Class implements mouse input device.
 */

#include "InputMouse.h"

CInputMouse::CInputMouse(void)
{
	// init the members
	::memset(&m_State, 0, sizeof(DIMOUSESTATE2));
}

CInputMouse::~CInputMouse(void)
{
}

// Create
// initialise the input device
HRESULT CInputMouse::Create(	CInputEngine* pEngine,
								CInputEngine::DEVICE* pDevice,
								DWORD dwFlags)
{
	// get the DirectInput object
	LPDIRECTINPUT8	pDI = pEngine->GetInput();
	if(pDI == NULL)
	{
		return E_FAIL;
	}

	HRESULT hres;
	GUID	gdDevice;

	gdDevice = GUID_SysMouse;
	if(pDevice)
	{
		gdDevice = pDevice->gdDevice;
	}

	// create the DirectInput device object
	hres = pDI->CreateDevice(	gdDevice,
								&m_pDevice,
								NULL);
	if(FAILED(hres))
	{
		return hres;
	}

	// set input device data format
	m_pDevice->SetDataFormat(&c_dfDIMouse2);
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

	// acquire the input device
	m_pDevice->Acquire();
	return S_OK;
}

// Update
// get the current state of the input device
HRESULT CInputMouse::Update(void)
{
	if(m_pDevice == NULL)
	{
		// invalid user error...
		return E_FAIL;
	}

	HRESULT hres;

	// ask mouse state
	hres = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);
	if(FAILED(hres))
	{
		// if getting the device state fails, most likely
		// another application has gained the input device
		// focus, and we have lost it...

		// try to acquire the device back to us
		m_pDevice->Acquire();

		// ask device state again
		hres = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);
		if(FAILED(hres))
		{
			// can't get the focus back...
			// nothing much we can do about it...
			::memset(&m_State, 0, sizeof(DIMOUSESTATE2));
			return hres;
		}
	}
	return S_OK;
}

// GetButton
// returns TRUE if specified mouse button is down
BOOL CInputMouse::GetButton(DWORD dwButtonIndex) const
{
	if(dwButtonIndex >= m_dwButtonCount)
	{
		return FALSE;
	}

	return m_State.rgbButtons[dwButtonIndex] ? TRUE : FALSE;
}

// CountButtons
// does what it says
DWORD CInputMouse::CountButtons(void)
{
	DIDEVICEOBJECTINSTANCE		didoi;

	::memset(&didoi, 0, sizeof(DIDEVICEOBJECTINSTANCE));
	didoi.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

	DWORD dwButtons = 0;

	// try to get info about 8 mouse buttons
	// if 'GetObjectInfo' fails, that button is not present
	int i;
	for (i=0; i<8; i++)
	{
		if(SUCCEEDED(m_pDevice->GetObjectInfo(	&didoi,
												DIMOFS_BUTTON0 + i,
												DIPH_BYOFFSET)))
		{
			dwButtons++;
		}
	}
	return dwButtons;
}