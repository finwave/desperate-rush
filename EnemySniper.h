#pragma once

#include "IEnemy.h"

class CEnemySniper : public IEnemy
{
public:

	CEnemySniper(eTYPE eType, eBEHAVIOUR eBehaviour);

	virtual ~CEnemySniper(void);

	virtual bool Shoot();

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

	inline void SetSpeedEnter( float fTime ) { this->m_fSpeedEnter = fTime; }
	inline void SetFleeCounter( float fTime ) { this->m_fFleeCounter = fTime; }
	inline void SetShootCounter( float fTime ) { this->m_fShootCounter = fTime; }
	inline void SetRandShootTime( float fTime ) { this->m_fRandShootTime = fTime; }

private:

	virtual void Move(float fFrametime, float fPlayerVelocity);
	virtual void SetMoveState(void);
};