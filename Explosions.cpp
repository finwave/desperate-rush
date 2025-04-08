#include "Explosions.h"

CExplosions::CExplosions()
{
	this->m_iMaxPlayer = 1;
	this->m_iMaxDrone = 5;
	this->m_iMaxSniper = 5;
	this->m_iMaxRoller = 5;
	//this->m_iMaxGuard = 5;
	this->m_iMaxBoss1Big = 1;
	this->m_iMaxBoss1Part = 4;
	this->m_iMaxBoss1Chain1 = 5;
	this->m_iMaxBoss1Chain2 = 5;
	this->m_iMaxBoss1Chain3 = 5;

	this->m_pExplosionPlayer = NULL;
	this->m_pExplosionDrone = NULL;
	this->m_pExplosionSniper = NULL;
	this->m_pExplosionRoller = NULL;
	//this->m_pExplosionGuard = NULL;
	this->m_pExplosionBoss1Big = NULL;
	this->m_pExplosionBoss1Part = NULL;
	this->m_pExplosionBoss1Chain1 = NULL;
	this->m_pExplosionBoss1Chain2 = NULL;
	this->m_pExplosionBoss1Chain3 = NULL;
}

CExplosions::~CExplosions(void)
{
}

HRESULT CExplosions::Create(CTheApp* pTheApp,
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
							float fScreenHeight)
{
	HRESULT hres = S_OK;

	this->m_pTheApp = pTheApp;

	float fDrawPause = 0.013f;

	this->m_pExplosionPlayer = new CExplosion[this->m_iMaxPlayer];
	if( !m_pExplosionPlayer )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxPlayer; i++ )
	{
		(m_pExplosionPlayer + i)->Create(pTheApp,
										pSpriteExplosionPlayer,
										CExplosion::eEXPLOSION_TYPE_PLAYER,
										iSpriteCountPlayer,
										fDrawPause,
										fScreenWidth,
										fScreenHeight);
	}

	this->m_pExplosionDrone = new CExplosion[this->m_iMaxDrone];
	if( !m_pExplosionDrone )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxDrone; i++ )
	{
		(m_pExplosionDrone + i)->Create(pTheApp,
										pSpriteExplosionDrone,
										CExplosion::eEXPLOSION_TYPE_DRONE,
										iSpriteCountDrone,
										fDrawPause,
										fScreenWidth,
										fScreenHeight);
	}

	this->m_pExplosionSniper = new CExplosion[this->m_iMaxSniper];
	if( !m_pExplosionSniper )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxSniper; i++ )
	{
		(m_pExplosionSniper + i)->Create(pTheApp,
										pSpriteExplosionSniper,
										CExplosion::eEXPLOSION_TYPE_SNIPER,
										iSpriteCountSniper,
										fDrawPause,
										fScreenWidth,
										fScreenHeight);
	}

	this->m_pExplosionRoller = new CExplosion[this->m_iMaxRoller];
	if( !m_pExplosionRoller )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxRoller; i++ )
	{
		(m_pExplosionRoller + i)->Create(pTheApp,
										pSpriteExplosionRoller,
										CExplosion::eEXPLOSION_TYPE_ROLLER,
										iSpriteCountRoller,
										fDrawPause,
										fScreenWidth,
										fScreenHeight);
	}

	/*
	this->m_pExplosionGuard = new CExplosion[this->m_iMaxGuard];
	if( !m_pExplosionGuard )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxGuard; i++ )
	{
		(m_pExplosionGuard + i)->Create(pTheApp,
										pSpriteExplosionGuard,
										CExplosion::eEXPLOSION_TYPE_GUARD,
										iSpriteCountGuard,
										fDrawPause,
										fScreenWidth,
										fScreenHeight);
	}
	*/

	this->m_pExplosionBoss1Big = new CExplosion[this->m_iMaxBoss1Big];
	if( !m_pExplosionBoss1Big )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxBoss1Big; i++ )
	{
		(m_pExplosionBoss1Big + i)->Create(	pTheApp,
											pSpriteExplosionBoss1Big,
											CExplosion::eEXPLOSION_TYPE_BOSS_1_BIG,
											iSpriteCountBoss1Big,
											fDrawPause,
											fScreenWidth,
											fScreenHeight);
	}

	this->m_pExplosionBoss1Part = new CExplosion[this->m_iMaxBoss1Part];
	if( !m_pExplosionBoss1Part )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxBoss1Part; i++ )
	{
		(m_pExplosionBoss1Part + i)->Create(pTheApp,
											pSpriteExplosionBoss1Part,
											CExplosion::eEXPLOSION_TYPE_BOSS_1_PART,
											iSpriteCountBoss1Part,
											fDrawPause,
											fScreenWidth,
											fScreenHeight);
	}

	this->m_pExplosionBoss1Chain1 = new CExplosion[this->m_iMaxBoss1Chain1];
	if( !m_pExplosionBoss1Chain1 )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxBoss1Chain1; i++ )
	{
		(m_pExplosionBoss1Chain1 + i)->Create(	pTheApp,
												pSpriteExplosionBoss1Chain1,
												CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_1,
												iSpriteCountBoss1Chain1,
												fDrawPause,
												fScreenWidth,
												fScreenHeight);
	}

	this->m_pExplosionBoss1Chain2 = new CExplosion[this->m_iMaxBoss1Chain2];
	if( !m_pExplosionBoss1Chain2 )
	{
		return E_OUTOFMEMORY;
	}
	
	for( int i = 0; i < this->m_iMaxBoss1Chain1; i++ )
	{
		(m_pExplosionBoss1Chain2 + i)->Create(	pTheApp,
												pSpriteExplosionBoss1Chain2,
												CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_2,
												iSpriteCountBoss1Chain2,
												fDrawPause,
												fScreenWidth,
												fScreenHeight);
	}

	this->m_pExplosionBoss1Chain3 = new CExplosion[this->m_iMaxBoss1Chain3];
	if( !m_pExplosionBoss1Chain3 )
	{
		return E_OUTOFMEMORY;
	}

	for( int i = 0; i < this->m_iMaxBoss1Chain3; i++ )
	{
		(m_pExplosionBoss1Chain3 + i)->Create(	pTheApp,
												pSpriteExplosionBoss1Chain3,
												CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_3,
												iSpriteCountBoss1Chain3,
												fDrawPause,
												fScreenWidth,
												fScreenHeight);
	}

	return hres;
}

void CExplosions::Release()
{
	if( this->m_pExplosionPlayer )
	{
		delete [] this->m_pExplosionPlayer;
		this->m_pExplosionPlayer = NULL;
	}
	if( this->m_pExplosionDrone )
	{
		delete [] this->m_pExplosionDrone;
		this->m_pExplosionDrone = NULL;
	}
	if( this->m_pExplosionSniper )
	{
		delete [] this->m_pExplosionSniper;
		this->m_pExplosionSniper = NULL;
	}
	if( this->m_pExplosionRoller )
	{
		delete [] this->m_pExplosionRoller;
		this->m_pExplosionRoller = NULL;
	}
	/*
	if( this->m_pExplosionGuard )
	{
		delete [] this->m_pExplosionGuard;
		this->m_pExplosionGuard = NULL;
	}
	*/
	if( this->m_pExplosionBoss1Big )
	{
		delete [] this->m_pExplosionBoss1Big;
		this->m_pExplosionBoss1Big = NULL;
	}
	if( this->m_pExplosionBoss1Part )
	{
		delete [] this->m_pExplosionBoss1Part;
		this->m_pExplosionBoss1Part = NULL;
	}
	if( this->m_pExplosionBoss1Chain1 )
	{
		delete [] this->m_pExplosionBoss1Chain1;
		this->m_pExplosionBoss1Chain1 = NULL;
	}
	if( this->m_pExplosionBoss1Chain2 )
	{
		delete [] this->m_pExplosionBoss1Chain2;
		this->m_pExplosionBoss1Chain2 = NULL;
	}
	if( this->m_pExplosionBoss1Chain3 )
	{
		delete [] this->m_pExplosionBoss1Chain3;
		this->m_pExplosionBoss1Chain3 = NULL;
	}
}

void CExplosions::AddExplosion(	CExplosion::eEXPLOSION_TYPE eExplosionType,
								int iMoveSpeed,
								float fMovePause,
								D3DXVECTOR3 pos)
{
	switch (eExplosionType)
	{
	case CExplosion::eEXPLOSION_TYPE_PLAYER:

		for( int i = 0; i < this->m_iMaxPlayer; i++ )
		{
			if ( !(m_pExplosionPlayer + i)->IsActive() )
			{
				(m_pExplosionPlayer + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_DRONE:

		for( int i = 0; i < this->m_iMaxDrone; i++ )
		{
			if ( !(m_pExplosionDrone + i)->IsActive() )
			{
				(m_pExplosionDrone + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}
		
		break;

	case CExplosion::eEXPLOSION_TYPE_SNIPER:

		for( int i = 0; i < this->m_iMaxSniper; i++ )
		{
			if ( !(m_pExplosionSniper + i)->IsActive() )
			{
				(m_pExplosionSniper + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_ROLLER:

		for( int i = 0; i < this->m_iMaxRoller; i++ )
		{
			if ( !(m_pExplosionRoller + i)->IsActive() )
			{
				(m_pExplosionRoller + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	/*
	case CExplosion::eEXPLOSION_TYPE_GUARD:

		for( int i = 0; i < this->m_iMaxGuard; i++ )
		{
			if ( !(m_pExplosionGuard + i)->IsActive() )
			{
				(m_pExplosionGuard + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;
	*/

	case CExplosion::eEXPLOSION_TYPE_BOSS_1_BIG:

		for( int i = 0; i < this->m_iMaxBoss1Big; i++ )
		{
			if ( !(m_pExplosionBoss1Big + i)->IsActive() )
			{
				(m_pExplosionBoss1Big + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_BOSS_1_PART:

		for( int i = 0; i < this->m_iMaxBoss1Part; i++ )
		{
			if ( !(m_pExplosionBoss1Part + i)->IsActive() )
			{
				(m_pExplosionBoss1Part + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_1:

		for( int i = 0; i < this->m_iMaxBoss1Chain1; i++ )
		{
			if ( !(m_pExplosionBoss1Chain1 + i)->IsActive() )
			{
				(m_pExplosionBoss1Chain1 + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_2:

		for( int i = 0; i < this->m_iMaxBoss1Chain2; i++ )
		{
			if ( !(m_pExplosionBoss1Chain2 + i)->IsActive() )
			{
				(m_pExplosionBoss1Chain2 + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;

	case CExplosion::eEXPLOSION_TYPE_BOSS_1_CHAIN_3:

		for( int i = 0; i < this->m_iMaxBoss1Chain3; i++ )
		{
			if ( !(m_pExplosionBoss1Chain3 + i)->IsActive() )
			{
				(m_pExplosionBoss1Chain3 + i)->Init(iMoveSpeed, fMovePause, pos);

				return;
			}
		}

		break;
	}
}

void CExplosions::Clear()
{
	for( int i = 0; i < this->m_iMaxPlayer; i++)
	{
		(m_pExplosionPlayer + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxDrone; i++)
	{
		(m_pExplosionDrone + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxSniper; i++)
	{
		(m_pExplosionSniper + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxRoller; i++)
	{
		(m_pExplosionRoller + i)->Disable();
	}
	/*
	for( int i = 0; i < this->m_iMaxGuard; i++)
	{
		(m_pExplosionGuard + i)->Disable();
	}
	*/
	for( int i = 0; i < this->m_iMaxBoss1Big; i++)
	{
		(m_pExplosionBoss1Big + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxBoss1Part; i++)
	{
		(m_pExplosionBoss1Part + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxBoss1Chain1; i++)
	{
		(m_pExplosionBoss1Chain1 + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxBoss1Chain2; i++)
	{
		(m_pExplosionBoss1Chain2 + i)->Disable();
	}
	for( int i = 0; i < this->m_iMaxBoss1Chain3; i++)
	{
		(m_pExplosionBoss1Chain3 + i)->Disable();
	}
}

void CExplosions::Update(float fFrametime, int gameState)
{
	for( int i = 0; i < this->m_iMaxPlayer; i++)
	{
		(m_pExplosionPlayer + i)->Update(fFrametime);
	}

	// small enemies
	if (gameState <= STATE_BOSS_INTRO)
	{
		for( int i = 0; i < this->m_iMaxDrone; i++)
		{
			(m_pExplosionDrone + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxSniper; i++)
		{
			(m_pExplosionSniper + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxRoller; i++)
		{
			(m_pExplosionRoller + i)->Update(fFrametime);
		}
		/*
		for( int i = 0; i < this->m_iMaxGuard; i++)
		{
			(m_pExplosionGuard + i)->Update(fFrametime);
		}
		*/
	}
	// bosses
	else if (gameState > STATE_BOSS_INTRO && 
			gameState <= STATE_BOSS_BIG_EXPLOSION)
	{
		for( int i = 0; i < this->m_iMaxBoss1Big; i++)
		{
			(m_pExplosionBoss1Big + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxBoss1Part; i++)
		{
			(m_pExplosionBoss1Part + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain1; i++)
		{
			(m_pExplosionBoss1Chain1 + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain2; i++)
		{
			(m_pExplosionBoss1Chain2 + i)->Update(fFrametime);
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain3; i++)
		{
			(m_pExplosionBoss1Chain3 + i)->Update(fFrametime);
		}
	}
}

void CExplosions::Render(int gameState)
{
	for( int i = 0; i < this->m_iMaxPlayer; i++)
	{
		(m_pExplosionPlayer + i)->Render();
	}

	// small enemies
	if (gameState <= STATE_BOSS_INTRO || 
		gameState == STATE_BLAST_ACTIVE || 
		gameState == STATE_QUIT)
	{
		for( int i = 0; i < this->m_iMaxDrone; i++)
		{
			(m_pExplosionDrone + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxSniper; i++)
		{
			(m_pExplosionSniper + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxRoller; i++)
		{
			(m_pExplosionRoller + i)->Render();
		}
		/*
		for( int i = 0; i < this->m_iMaxGuard; i++)
		{
			(m_pExplosionGuard + i)->Render();
		}
		*/
	}

	// bosses
	if ((gameState > STATE_BOSS_INTRO && 
		gameState <= STATE_BOSS_BIG_EXPLOSION) || 
		gameState == STATE_BLAST_ACTIVE || 
		gameState == STATE_QUIT)
	{
		for( int i = 0; i < this->m_iMaxBoss1Big; i++)
		{
			(m_pExplosionBoss1Big + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxBoss1Part; i++)
		{
			(m_pExplosionBoss1Part + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain1; i++)
		{
			(m_pExplosionBoss1Chain1 + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain2; i++)
		{
			(m_pExplosionBoss1Chain2 + i)->Render();
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain3; i++)
		{
			(m_pExplosionBoss1Chain3 + i)->Render();
		}
	}
}

void CExplosions::UpdateVelocity(int iVelocityPixels, int gameState)
{
	int speed = 0;

	// small enemies
	if (gameState <= STATE_BOSS_INTRO)
	{
		for( int i = 0; i < this->m_iMaxPlayer; i++)
		{
			if( (m_pExplosionPlayer + i)->IsActive() )
			{
				speed = (m_pExplosionPlayer + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionPlayer + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxDrone; i++)
		{
			if( (m_pExplosionDrone + i)->IsActive() )
			{
				speed = (m_pExplosionDrone + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionDrone + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxSniper; i++)
		{
			if( (m_pExplosionSniper + i)->IsActive() )
			{
				speed = (m_pExplosionSniper + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionSniper + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxRoller; i++)
		{
			if( (m_pExplosionRoller + i)->IsActive() )
			{
				speed = (m_pExplosionRoller + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionRoller + i)->SetSpeed(speed);
			}
		}
		/*
		for( int i = 0; i < this->m_iMaxGuard; i++)
		{
			if( (m_pExplosionGuard + i)->IsActive() )
			{
				speed = (m_pExplosionGuard + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionGuard + i)->SetSpeed(speed);
			}
		}
		*/
	}

	// bosses
	if (gameState > STATE_BOSS_INTRO && 
		gameState <= STATE_BOSS_BIG_EXPLOSION)
	{
		for( int i = 0; i < this->m_iMaxBoss1Big; i++)
		{
			if( (m_pExplosionBoss1Big + i)->IsActive() )
			{
				speed = (m_pExplosionBoss1Big + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionBoss1Big + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxBoss1Part; i++)
		{
			if( (m_pExplosionBoss1Part + i)->IsActive() )
			{
				speed = (m_pExplosionBoss1Part + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionBoss1Part + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain1; i++)
		{
			if( (m_pExplosionBoss1Chain1 + i)->IsActive() )
			{
				speed = (m_pExplosionBoss1Chain1 + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionBoss1Chain1 + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain2; i++)
		{
			if( (m_pExplosionBoss1Chain2 + i)->IsActive() )
			{
				speed = (m_pExplosionBoss1Chain2 + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionBoss1Chain2 + i)->SetSpeed(speed);
			}
		}
		for( int i = 0; i < this->m_iMaxBoss1Chain3; i++)
		{
			if( (m_pExplosionBoss1Chain3 + i)->IsActive() )
			{
				speed = (m_pExplosionBoss1Chain3 + i)->GetDefaultSpeed() + iVelocityPixels;
				(m_pExplosionBoss1Chain3 + i)->SetSpeed(speed);
			}
		}
	}
}
