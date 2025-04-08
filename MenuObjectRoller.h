#pragma once

#include "MenuObject.h"

class CMenuObjectRoller :public CMenuObject
{
public:

	CMenuObjectRoller();
	~CMenuObjectRoller();

	virtual void RotateLeft();
	virtual void RotateRight();

protected:

	virtual void Rotate(float fFrametime);
	virtual void ResetSelfRotation();

	virtual D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material);
};

