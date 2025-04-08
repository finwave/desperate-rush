/**
 * Class implements mouse input device.
 */

#pragma once

#include "IInputDevice.h"

class CInputMouse : public IInputDevice
{
public:
	CInputMouse(void);
	virtual ~CInputMouse(void);

	// Create
	// initialise the input device
	HRESULT Create(	CInputEngine* pEngine,
					CInputEngine::DEVICE* pDevice,
					DWORD dwFlags);

	// Update
	// get the current state of the input device
	HRESULT Update(void);

	// GetButton
	// returns TRUE if specified mouse button is down
	BOOL GetButton(DWORD dwButtonIndex) const;

	// GetState
	// returns reference to mouse state structure
	inline DIMOUSESTATE2& GetState() { return m_State; }

private:
	// CountButtons
	// does what is says
	DWORD CountButtons(void);

	DIMOUSESTATE2	m_State;
};