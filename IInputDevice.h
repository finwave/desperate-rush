/**
 * Abstract class for all input devices.
 */

#pragma once

#include "InputEngine.h"

class IInputDevice
{
public:
	IInputDevice(void);
	virtual ~IInputDevice(void);

	// Release
	// release the input device
	virtual void Release();

	// Update
	// pure virtual, get status of the input device
	virtual HRESULT Update() = 0;

	// GetButton
	// returns TRUE if specified input device button is down
	virtual BOOL GetButton(DWORD dwButtonIndex) const = 0;

	// GetDevice
	// returns DirectInput device object
	inline LPDIRECTINPUTDEVICE8 GetDevice() { return m_pDevice; }

	// GetButtonCount
	// returns number of buttons present in device
	inline DWORD GetButtonCount() const { return m_dwButtonCount; }

protected:
	LPDIRECTINPUTDEVICE8		m_pDevice;
	DWORD						m_dwButtonCount;
};