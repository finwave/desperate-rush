/**
 * Class implements keyboard input device.
 */

#pragma once

#include "IInputDevice.h"

class CInputKeyboard : public IInputDevice
{
public:
	CInputKeyboard(void);
	virtual ~CInputKeyboard(void);

	// Create
	// initialise the input device
	HRESULT Create(	CInputEngine* pEngine,
					CInputEngine::DEVICE* pDevice,
					DWORD dwFlags);

	// Update
	// get the current state of the input device
	HRESULT Update(void);

	// GetButton
	// returns TRUE if specified key is down
	// FALSE otherwise. The dwKey parameter is
	// one of the DirectInput key codes (DIK_)
	inline BOOL GetButton(DWORD dwDIK) const
	{
		return m_byKeys[dwDIK] ? TRUE : FALSE;
	}

	//inline BYTE* GetKeys() { return &this->m_byKeys; }

	// Scan2VIrtual
	// convert a DirectInput Scan Code to a virtual-key code
	static UINT Scan2VIrtual(DWORD scanCode);

private:
	BYTE	m_byKeys[256];
};