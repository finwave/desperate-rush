#pragma once

#include "IEnemy.h"

class CEnemyBoss : public IEnemy
{
public:

	CEnemyBoss(void);
	virtual ~CEnemyBoss(void);

	virtual void Release();
	virtual bool Shoot();
	
	inline void SetVolumeSoundEffect(int iVolume) { this->m_iVolumeSoundEffect = iVolume; }

protected:

	virtual void SetMoveState(void);
};