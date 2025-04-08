/**
 * Class implements keyboard input device.
 */

#include "InputKeyboard.h"


CInputKeyboard::CInputKeyboard(void)
{
	// init the members
	::memset(m_byKeys, 0, 256);
}


CInputKeyboard::~CInputKeyboard(void)
{
}


// Create
// initialise the input device
HRESULT CInputKeyboard::Create(	CInputEngine* pEngine,
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

	gdDevice = GUID_SysKeyboard;
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
	m_pDevice->SetDataFormat(&c_dfDIKeyboard);
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

	m_dwButtonCount = 256;

	// acquire the input device
	m_pDevice->Acquire();
	::memset(m_byKeys, 0, 256);
	return S_OK;
}


// Update
// get the current state of the input device
HRESULT CInputKeyboard::Update(void)
{
	if(m_pDevice == NULL)
	{
		// invalid user error...
		return E_FAIL;
	}

	HRESULT hres;

	// ask keyboard state
	hres = m_pDevice->GetDeviceState(256, m_byKeys);
	if(FAILED(hres))
	{
		// if getting the device state fails, most likely
		// another application has gained the input device
		// focus, and we have lost it...

		// try to acquire the device back to us
		m_pDevice->Acquire();

		// ask device state again
		hres = m_pDevice->GetDeviceState(256, m_byKeys);
		if(FAILED(hres))
		{
			// can't get the focus back...
			// nothing much we can do about it...
			::memset(m_byKeys, 0, 256);
			return hres;
		}
	}
	return S_OK;
}

// Scan2VIrtual
// convert a DirectInput Scan Code to a virtual-key code
UINT CInputKeyboard::Scan2VIrtual(DWORD scanCode)
{
	UINT virtualKey;
	static HKL layout = GetKeyboardLayout(0);

	virtualKey = MapVirtualKeyEx(scanCode, 1, layout);

	return virtualKey;
}
