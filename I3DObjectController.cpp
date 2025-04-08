/**
 * Abstract interface to control any
 * I3DObject derived object.
 */

#include "I3DObjectController.h"

I3DObjectController::I3DObjectController(void)
{
	m_pObject = NULL;
}

I3DObjectController::~I3DObjectController(void)
{
}

void I3DObjectController::Update(float fFrametime, void* pExtraData)
{
}
