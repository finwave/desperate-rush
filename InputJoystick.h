/**
 * Class implements joystick input device.
 */

#pragma once

#include "IInputDevice.h"

class CInputJoystick : public IInputDevice
{
public:
	CInputJoystick(void);
	virtual ~CInputJoystick(void);

	// Create
	// initialise the input device
	HRESULT Create(	CInputEngine* pEngine,
					CInputEngine::DEVICE* pDevice,
					DWORD dwFlags);

	// Update
	// get the current state of the input device
	HRESULT Update(void);

	// GetButton
	// returns TRUE if specified joystick button is down
	BOOL GetButton(DWORD dwButtonIndex) const;

	// SetAxisRange
	// set the data range for specific joystick axis
	// dwAxis:
	// DIJOFS_X, DIJOFS_Y, DIJOFS_Z
	void SetAxisRange(DWORD dwAxis, int iMin, int iMax);

	// SetDeadZone
	// adjust joystick deadzone area.
	// iDeadzone parameter is always value in range
	// 0-10000, where 0 is no deadzone, 5000 is 50%
	// deadzone, and so on.
	// dwAxis:
	// DIJOFS_X, DIJOFS_Y, DIJOFS_Z
	void SetDeadZone(DWORD dwAxis, int iDeadzone);

	// GetState
	// returns reference to DIJOYSTATE2 structure.
	// Structure is filled after successfull call to
	// Update
	inline DIJOYSTATE2& GetState() { return m_State; }

	// IsForce
	// returns TRUE if joystick supports force feedback
	inline BOOL IsForce() const { return m_bIsForce; }

	// FFReset
	// reset the force feedback device and
	// disable the autocentering spring
	HRESULT FFReset();

private:
	// CountButtons
	// does what is says
	DWORD CountButtons();

	DIJOYSTATE2				m_State;
	BOOL					m_bIsForce;
};