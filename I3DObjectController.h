/**
 * Abstract interface to control any
 * I3DObject derived object.
 */

#pragma once

#include "I3DObject.h"

class I3DObjectController
{
public:
	I3DObjectController(void);
	virtual ~I3DObjectController(void);

	/**
	 * Create
	 * @param pObject pointer to object to control
	 */
	virtual void Create(I3DObject* pObject) { m_pObject = pObject; }

	/**
	 * Release
	 * release the controller
	 */
	virtual void Release(void) { m_pObject = NULL; }

	/**
	 * Update
	 * @param fFrametime
	 * @param pExtraData any extra data user wants to pass
	 */
	virtual void Update(float fFrametime, void* pExtraData);

protected:
	I3DObject* m_pObject;
};