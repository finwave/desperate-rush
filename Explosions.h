#pragma once

#define STATE_BOSS_INTRO			6
#define STATE_BOSS_BIG_EXPLOSION	9
#define STATE_BLAST_ACTIVE			14
#define STATE_QUIT					15

#include "TheApp.h"
#include "Explosion.h"

class CExplosions
{
public:

	CExplosions(void);
	~CExplosions(void);

	HRESULT Create(	CTheApp* pTheApp,
					CSprite* pSpriteExplosionPlayer,
					CSprite* pSpriteExplosionDrone,
					CSprite* pSpriteExplosionSniper,
					CSprite* pSpriteExplosionRoller,
					//CSprite* pSpriteExplosionGuard,
					CSprite* pSpriteExplosionBoss1Big,
					CSprite* pSpriteExplosionBoss1Part,
					CSprite* pSpriteExplosionBoss1Chain1,
					CSprite* pSpriteExplosionBoss1Chain2,
					CSprite* pSpriteExplosionBoss1Chain3,
					int iSpriteCountPlayer,
					int iSpriteCountDrone,
					int iSpriteCountSniper,
					int iSpriteCountRoller,
					//int spriteCountGuard,
					int iSpriteCountBoss1Big,
					int iSpriteCountBoss1Part,
					int iSpriteCountBoss1Chain1,
					int iSpriteCountBoss1Chain2,
					int iSpriteCountBoss1Chain3,
					float fScreenWidth,
					float fScreenHeight);

	void Release();

	void AddExplosion(	CExplosion::eEXPLOSION_TYPE eExplosionType,
						int iMoveSpeed,
						float fMovePause,
						D3DXVECTOR3 pos);

	void Clear();

	void Update(float fFrametime, int gameState);
	void Render(int gameState);

	void UpdateVelocity(int iVelocityPixels, int gameState);

private:

	CTheApp*		m_pTheApp;

	// how many explosions are stored

	int				m_iMaxPlayer;
	int				m_iMaxDrone;
	int				m_iMaxSniper;
	int				m_iMaxRoller;
	//int			m_iMaxGuard;
	int				m_iMaxBoss1Big;
	int				m_iMaxBoss1Part;
	int				m_iMaxBoss1Chain1;
	int				m_iMaxBoss1Chain2;
	int				m_iMaxBoss1Chain3;

	CExplosion*		m_pExplosionPlayer;
	CExplosion*		m_pExplosionDrone;
	CExplosion*		m_pExplosionSniper;
	CExplosion*		m_pExplosionRoller;
	//CExplosion*	m_pExplosionGuard;
	CExplosion*		m_pExplosionBoss1Big;
	CExplosion*		m_pExplosionBoss1Part;
	CExplosion*		m_pExplosionBoss1Chain1;
	CExplosion*		m_pExplosionBoss1Chain2;
	CExplosion*		m_pExplosionBoss1Chain3;
};
