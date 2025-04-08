#pragma once

#include "TheApp.h"
#include "Sprite.h"

class CExplosion
{
public:

	enum eEXPLOSION_TYPE
	{
		eEXPLOSION_TYPE_NONE,
		eEXPLOSION_TYPE_PLAYER,
		eEXPLOSION_TYPE_DRONE,
		eEXPLOSION_TYPE_SNIPER,
		eEXPLOSION_TYPE_ROLLER,
		eEXPLOSION_TYPE_GUARD,
		eEXPLOSION_TYPE_BOSS_1_BIG,
		eEXPLOSION_TYPE_BOSS_1_PART,
		eEXPLOSION_TYPE_BOSS_1_CHAIN_1,
		eEXPLOSION_TYPE_BOSS_1_CHAIN_2,
		eEXPLOSION_TYPE_BOSS_1_CHAIN_3
	};

	CExplosion(void);
	virtual ~CExplosion(void);

	void Create(CTheApp* pTheApp,
				CSprite* pSpritesExplosion,
				eEXPLOSION_TYPE eExplosionType,
				int iSpriteCount,
				float fDrawPause,
				float fScreenWidth,
				float fScreenHeight);

	void Init(	int iMoveSpeed,
				float fMovePause,
				D3DXVECTOR3 posStart);

	void Update(float fFrametime);
	void Render();

	inline bool IsActive() { return this->m_bActive; }
	inline void Disable() { this->m_bActive = false; }

	inline void SetSpeed(int iSpeed) { this->m_iMoveSpeed = iSpeed; }
	inline int GetDefaultSpeed() { return this->m_iDefaultSpeed; }

private:

	void InitPosition(D3DXVECTOR3 posStart);

	CTheApp*			m_pTheApp;
	CSprite*			m_pSpritesExplosion;

	D3DXVECTOR3			m_posStart;

	eEXPLOSION_TYPE		m_eExplosionType;

	bool				m_bActive;

	int					m_iSpriteIndex;
	int					m_iSpriteCount;

	int					m_iPosStartX;
	int					m_iPosStartY;
	int					m_iPosY;

	int					m_iMoveSpeed;
	int					m_iDefaultSpeed;

	float				m_fMovePause;
	float				m_fMovePauseMax;

	float				m_fDrawPause;
	float				m_fDrawPauseMax;

	float				m_fScreenWidth;
	float				m_fScreenHeight;	
};