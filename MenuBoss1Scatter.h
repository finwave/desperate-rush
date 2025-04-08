#pragma once

#include "MenuObject.h"

class CMenuBoss1Scatter : public CMenuObject
{
public:

	CMenuBoss1Scatter();
	virtual ~CMenuBoss1Scatter(void);

	virtual void Init();

	virtual void UpdateShip(CMenuObject* pBossFrame,
							float fFrametime);

protected:

	void RotateShip(CMenuObject* pBossFrame, float fFrametime);

private:

	void InitPosition(CMenuObject* pBossFrame);

	virtual void Scale();
	virtual D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material);

	float m_fRotationSpeed;
};