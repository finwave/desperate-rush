/**
 * This class implements an simple DirectInput
 * wrapper. Class is capable of retreiving
 * information about attached input devices.
 */

#include "InputEngine.h"

CInputEngine::CInputEngine(void)
{
	m_pDI = NULL;
	m_hWnd = NULL;
}


CInputEngine::~CInputEngine(void)
{

}


// Create
// initialise input engine
// hWnd is application main window handle
HRESULT CInputEngine::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	return DirectInput8Create(	::GetModuleHandle(NULL),
								0x800,
								IID_IDirectInput8,
								(void**)&m_pDI,
								NULL);
}


// Release
// release input engine
void CInputEngine::Release(void)
{
	if(m_pDI)
	{
		m_pDI->Release();
		m_pDI = NULL;
	}
	m_hWnd = NULL;
}


// GetKeyboards
// get all attached keyboard devices
// returns number of devices found
int CInputEngine::GetKeyboards(std::vector<DEVICE>* parrDevices)
{
	if(m_pDI == NULL)
	{
		return 0;
	}

	m_pDI->EnumDevices(	DI8DEVCLASS_KEYBOARD,
						EnumDevicesCallback,
						parrDevices,
						DIEDFL_ATTACHEDONLY);
	return parrDevices->size();
}


// GetMice
// get all attached mouse devices
// returns number of devices found
int CInputEngine::GetMice(std::vector<DEVICE>* parrDevices)
{
	if(m_pDI == NULL)
	{
		return 0;
	}

	m_pDI->EnumDevices(	DI8DEVCLASS_POINTER,
						EnumDevicesCallback,
						parrDevices,
						DIEDFL_ATTACHEDONLY);
	return parrDevices->size();
}


// GetJoysticks
// Get all attached joystick devices. Returns number of devices found.
int CInputEngine::GetJoysticks(std::vector<DEVICE>* parrDevices)
{
	if(m_pDI == NULL)
	{
		return 0;
	}

	m_pDI->EnumDevices(	DI8DEVCLASS_GAMECTRL,
						EnumDevicesCallback,
						parrDevices,
						DIEDFL_ATTACHEDONLY);
	return parrDevices->size();
}



// EnumDevicesCallback
// Static callback is called by DirectInput when input device has been found.
int CInputEngine::EnumDevicesCallback(LPCDIDEVICEINSTANCE pInstance, void* pParameter)
{
	// get the parameter array
	std::vector<DEVICE>* parrDevices = (std::vector<DEVICE>*)pParameter;

	// copy input device information into the new
	// DEVICE structure
	DEVICE	device;
	::memcpy(&device.gdDevice, &pInstance->guidInstance, sizeof(GUID));
	::memset(device.strName, 0, sizeof(TCHAR) * 256);
	::_tcscpy_s(device.strName, pInstance->tszProductName);

	parrDevices->push_back(device);
	return DIENUM_CONTINUE;
}
