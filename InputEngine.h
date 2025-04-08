/**
 * This class implements an simple DirectInput
 * wrapper. Class is capable of retreiving
 * information about attached input devices.
 * 
 * Requires:
 * Project wide define: DIRECTINPUT_VERSION=0x900
 * libs: dinput8.lib
 */

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <tchar.h>

// the STL vector is used to store found input devices
#include <vector>

class CInputEngine
{
public:
	struct DEVICE
	{
		GUID		gdDevice;
		TCHAR		strName[256];
	};

	CInputEngine(void);
	virtual ~CInputEngine(void);

	// Create
	// initialise input engine
	// hWnd is application main window handle
	HRESULT Create(HWND hWnd);

	// Release
	// release input engine
	void Release(void);

	// GetKeyboards
	// get all attached keyboard devices
	// returns number of devices found
	int GetKeyboards(std::vector<DEVICE>* parrDevices);

	// GetMice
	// get all attached mouse devices
	// returns number of devices found
	int GetMice(std::vector<DEVICE>* parrDevices);

	// GetJoystics
	// get all attached joystick devices
	// returns number of devices found
	int GetJoysticks(std::vector<DEVICE>* parrDevices);

	// GetInput
	// returns DirectInput object
	inline LPDIRECTINPUT8 GetInput() { return m_pDI; }

	// GetWindow
	// returns application main window handle
	inline HWND GetWindow() { return m_hWnd; }

private:
	// EnumDevicesCallback
	// static callback is called by DirectInput when input device
	// has been found
	static int WINAPI EnumDevicesCallback(LPCDIDEVICEINSTANCE pInstance, void* pParameter);

	// The DirectInput object
	LPDIRECTINPUT8			m_pDI;

	// application main window handle
	HWND					m_hWnd;
};