#pragma once

#include "IEnemy.h"

class CEnemyGuard : public IEnemy
{
public:

	CEnemyGuard(eTYPE eType, eBEHAVIOUR eBehaviour);

	virtual ~CEnemyGuard(void);

	virtual bool Shoot();

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	virtual void Move(float fFrametime, float fPlayerVelocity);
	virtual void SetMoveState(void);
};