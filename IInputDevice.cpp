/**
 * Abstract class for all input devices.
 */

#include "IInputDevice.h"


IInputDevice::IInputDevice(void)
{
	// init the members
	m_pDevice = NULL;
	m_dwButtonCount = 0;
}


IInputDevice::~IInputDevice(void)
{
}


// Release
// release the input device
void IInputDevice::Release()
{
	if(m_pDevice)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}
