#include "Player.h"

CPlayer::CPlayer(void)
{
	this->m_bDestroyed = false;

	this->m_eHitSound = eHIT_SOUND_NORMAL;

	this->m_fUntouchable = 0.0f;
	this->m_iHealth = 0;
	this->m_iHealthMax = 0;

	// minigun can be turned
	m_bMinigunRotation = true;

	// minigun firing mode is set to front fire
	// at the start of a new game
	this->m_iMinigunMode = 0;

	// minigun bullet place is set to inner
	// at the start of a new game
	this->m_iMinigunBulletPlace = 0;

	// sets minigun boost level starting value
	this->m_iMinigunLevel = 0;
	this->SetMinigunSpecs();

	this->m_iCannonEnergyMax = 0;
	this->m_iCannonEnergy = 0;

	this->m_iBlasts = 0;
	this->m_iBlastDamage = 0;

	this->m_fBlastBeamTime = 0.035f;
	this->m_fBlastBeamCounter = 0.0f;

	this->m_bBlast = false;

	this->m_bBlastBeamUp = false;
	this->m_bBlastBeamDown = false;
	this->m_bBlastBeamLeft = false;
	this->m_bBlastBeamRight = false;
	this->m_bBlastBeamUpLeft = false;
	this->m_bBlastBeamUpRight = false;
	this->m_bBlastBeamDownLeft = false;
	this->m_bBlastBeamDownRight = false;

	this->m_bShield = false;

	this->m_iScore = 0;

	this->m_fHitSoundTimer = 0.0f;

	this->m_fScreenPixelWidth = 1024.0f;
	this->m_fScreenPixelHeight = 768.0f;

	this->m_fVelocity = 0.0f;
	this->m_fBoostClock = 0.0f;
	this->m_fBoostSpeed = 1.5f;
}

CPlayer::~CPlayer(void)
{
}

HRESULT CPlayer::Create(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						CSprite* pSpriteBlast,
						float fShipWidth,
						float fShipHeight,
						float fSpeed,
						float fMaxVelocity,
						int iHealth,
						int iCannonEnergy,
						int iBlastDamage,
						int iBlasts)
{
	// get default matrix
	this->m_mDefault = this->GetLocalMatrix();

	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	this->m_pTheApp = pTheApp;
	this->m_pSpriteBlast = pSpriteBlast;
	this->m_fShipWidth = fShipWidth;
	this->m_fShipHeight = fShipHeight;
	this->m_fSpeed = fSpeed;
	this->m_bBoostIncrease = true;
	this->m_iHealth = iHealth;
	this->m_iHealthMax = iHealth;
	this->m_iCannonEnergyMax = iCannonEnergy;
	this->m_iCannonEnergy = this->m_iCannonEnergyMax;
	this->m_iBlastDamage = iBlastDamage;
	this->m_iBlasts = iBlasts;

	return S_OK;
}

void CPlayer::Release(void)
{
	C3DObject::Release();
}

void CPlayer::Update(bool bUpdate,
					 float fFrametime)
{
	if(this->m_fUntouchable > 0.0f)
	{
		this->m_fUntouchable -= fFrametime;

		if(this->m_fUntouchable < 0.0f)
		{
			this->m_fUntouchable = 0.0f;
		}
	}
	if(this->m_bBlast)
	{
		this->UpdateBlast(fFrametime);
	}
	if(this->m_bBoostSoundCheck)
	{
		this->UpdateBoostSound();
	}

	if(bUpdate)
	{
		C3DObject::Update(fFrametime);
	}
}

void CPlayer::Render()
{
	C3DObject::Render(this->m_pTheApp->GetDevice());

	if(this->m_bBlast)
	{
		this->RenderBlast();
	}
}

void CPlayer::SetUntouchable(bool bUntouchable)
{
	if(bUntouchable)
	{
		this->m_fUntouchable = 3.0f;
	}
	else
	{
		this->m_fUntouchable = 0.0f;
	}
}

char* CPlayer::GetScoreString(void)
{
	char* sReturn = NULL;
	sReturn = new char[128];
	
	sprintf_s(sReturn,128, "%d", this->m_iScore);

	return sReturn;
}

char* CPlayer::GetShipHealth(void)
{
	char* sReturn = NULL;
	sReturn = new char[128];

	if( this->m_iHealth < 0 )
	{
		sprintf_s(sReturn,128, "0");
	}
	else
	{
		sprintf_s(sReturn,128, "%0.0f", this->m_iHealth);
	}

	return sReturn;
}

void CPlayer::IncreaseHealth(int iHealth)
{
	this->m_iHealth += iHealth;

	if(this->m_iHealth > this->m_iHealthMax)
	{
		this->m_iHealth = this->m_iHealthMax;
	}
}

void CPlayer::DecreaseHealth(int iDamage)
{ 
	if( this->m_fUntouchable == 0.0f )
	{
		this->m_iHealth -= iDamage; 
	}
}

void CPlayer::IncreaseMinigunLevel()
{
	if(this->m_iMinigunLevel < 6)
	{
		this->m_iMinigunLevel++;
		SetMinigunSpecs();
	}
}

void CPlayer::ChangeMinigunSound()
{
	switch(this->m_iMinigunLevel)
	{
		case 0:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_0_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_0_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_0_NORMAL;
			}
			break;

		case 1:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_1_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_1_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_1_NORMAL;
			}
			break;

		case 2:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_2_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_2_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_2_NORMAL;
			}
			break;

		case 3:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_3_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_3_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_3_NORMAL;
			}
			break;

		case 4:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_4_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_4_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_4_NORMAL;
			}
			break;

		case 5:
			if(this->m_eMinigunSound == eMINIGUN_SOUND_BOOST_5_NORMAL)
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_5_QUIET;
			}
			else
			{
				this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_5_NORMAL;
			}
			break;
	}
}

void CPlayer::ChangeHitSound()
{
	switch(this->m_eHitSound)
	{
	case eHIT_SOUND_NORMAL:
		this->m_eHitSound = eHIT_SOUND_QUIET;
		break;
	case eHIT_SOUND_QUIET:
		this->m_eHitSound = eHIT_SOUND_NORMAL;
		break;
	}
}

void CPlayer::ResetMinigunSound()
{
	switch(this->m_iMinigunLevel)
	{
		case 0:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_0_NORMAL;
			break;

		case 1:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_1_NORMAL;
			break;

		case 2:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_2_NORMAL;
			break;

		case 3:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_3_NORMAL;
			break;

		case 4:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_4_NORMAL;
			break;

		case 5:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_5_NORMAL;
			break;
	}
}

void CPlayer::ResetHitSound(float fFrametime)
{
	if(this->m_fHitSoundTimer <= 0.0f)
	{
		this->m_fHitSoundTimer = SOUND_TIMER_HIT;
		this->m_eHitSound = eHIT_SOUND_NORMAL;

	}
	else
	{
		this->m_fHitSoundTimer -= fFrametime;
	}
}

void CPlayer::SetBlast(bool bBlast)
{
	if(bBlast)
	{
		this->m_bBlast = true;
		this->m_eBlastLight = eBLAST_LIGHT_HIGH;
		this->m_fBlastBeamCounter = this->m_fBlastBeamTime;
	}
	else
	{
		this->m_bBlast = false;
	}
}

bool CPlayer::GameOver()
{	
	if( this->m_iLives <= 0 )
	{
		return true;
	}

	return false;
}

void CPlayer::SetMinigunSpecs()
{
	switch(this->m_iMinigunLevel)
	{
		case 0:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_0_NORMAL;
			this->m_iMinigunDamage = 4;
			this->m_fMinigunSpeed = 400.0f;
			this->m_fMinigunFirerate = 0.13f;
			break;

		case 1:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_1_NORMAL;
			this->m_iMinigunDamage = 5;
			this->m_fMinigunSpeed = 403.0f;
			this->m_fMinigunFirerate = 0.125f;
			break;

		case 2:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_2_NORMAL;
			this->m_iMinigunDamage = 6;
			this->m_fMinigunSpeed = 406.0f;
			this->m_fMinigunFirerate = 0.12f;
			break;

		case 3:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_3_NORMAL;
			this->m_iMinigunDamage = 7;
			this->m_fMinigunSpeed = 409.0f;
			this->m_fMinigunFirerate = 0.115f;
			break;

		case 4:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_4_NORMAL;
			this->m_iMinigunDamage = 8;
			this->m_fMinigunSpeed = 412.0f;
			this->m_fMinigunFirerate = 0.11f;
			break;

		case 5:
			this->m_eMinigunSound = eMINIGUN_SOUND_BOOST_5_NORMAL;
			this->m_iMinigunDamage = 9;
			this->m_fMinigunSpeed = 415.0f;
			this->m_fMinigunFirerate = 0.10f;
			break;
	}
}

void CPlayer::UpdateBlast(float fFrametime)
{
	if(this->m_fBlastBeamCounter >= this->m_fBlastBeamTime)
	{
		this->m_fBlastBeamCounter = 0.0f;

		this->m_bBlastBeamUp = false;
		this->m_bBlastBeamDown = false;
		this->m_bBlastBeamLeft = false;
		this->m_bBlastBeamRight = false;
		this->m_bBlastBeamUpLeft = false;
		this->m_bBlastBeamUpRight = false;
		this->m_bBlastBeamDownLeft = false;
		this->m_bBlastBeamDownRight = false;

		for(int i = 1; i < 4;)
		{
			switch(this->m_pTheApp->RandInt(0,7))
			{
			case SPRITE_PLAYER_BLAST_UP:

				if(!this->m_bBlastBeamUp)
				{
					this->m_bBlastBeamUp = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_DOWN:

				if(!this->m_bBlastBeamDown)
				{
					this->m_bBlastBeamDown = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_LEFT:

				if(!this->m_bBlastBeamLeft)
				{
					this->m_bBlastBeamLeft = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_RIGHT:

				if(!this->m_bBlastBeamRight)
				{
					this->m_bBlastBeamRight = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_UP_LEFT:

				if(!this->m_bBlastBeamUpLeft)
				{
					this->m_bBlastBeamUpLeft = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_UP_RIGHT:

				if(!this->m_bBlastBeamUpRight)
				{
					this->m_bBlastBeamUpRight = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_DOWN_LEFT:

				if(!this->m_bBlastBeamDownLeft)
				{
					this->m_bBlastBeamDownLeft = true;
					i++;
				}

				break;

			case SPRITE_PLAYER_BLAST_DOWN_RIGHT:

				if(!this->m_bBlastBeamDownRight)
				{
					this->m_bBlastBeamDownRight = true;
					i++;
				}

				break;
			}
		}
	}
	else
	{
		this->m_fBlastBeamCounter += fFrametime;

		if(this->m_fBlastBeamCounter >= this->m_fBlastBeamTime)
		{
			switch(this->m_eBlastLight)
			{
			case eBLAST_LIGHT_LOW:
				this->m_eBlastLight = eBLAST_LIGHT_HIGH;
				break;

			case eBLAST_LIGHT_HIGH:
				this->m_eBlastLight = eBLAST_LIGHT_LOW;
				break;
			}
		}
	}
}

void CPlayer::RenderBlast()
{
	const float fPixelMultiplier = 2.5f;

	float fMoveX;
	float fMoveY;

	int iPosOriginalX;
	int iPosOriginalY;

	int iPosX;
	int iPosY;

	D3DXVECTOR3 pos = this->GetPosition();

	// x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosOriginalX = ( (this->m_fScreenPixelWidth / 2) - 12.0f) + fMoveX;

	// y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosOriginalY = ( (this->m_fScreenPixelHeight / 2) - 12.0f) + fMoveY;

	// draw blast beams

	if(this->m_bBlastBeamUp)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 162;
		iPosY -= 1215;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_UP].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamDown)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 162;
		iPosY += 25;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_DOWN].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamLeft)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 1215;
		iPosY -= 162;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_LEFT].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamRight)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX += 25;
		iPosY -= 162;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_RIGHT].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamUpLeft)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 980;
		iPosY -= 980;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_UP_LEFT].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamUpRight)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 90;
		iPosY -= 980;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_UP_RIGHT].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamDownLeft)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 980;
		iPosY -= 90;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_DOWN_LEFT].Draw(iPosX, iPosY);
	}
	if(this->m_bBlastBeamDownRight)
	{
		iPosX = iPosOriginalX;
		iPosY = iPosOriginalY;

		iPosX -= 90;
		iPosY -= 90;

		this->m_pSpriteBlast[SPRITE_PLAYER_BLAST_DOWN_RIGHT].Draw(iPosX, iPosY);
	}
}

void CPlayer::IncreaseCannonEnergy(int iIncrease)
{
	this->m_iCannonEnergy += iIncrease;

	if(this->m_iCannonEnergy > this->m_iCannonEnergyMax)
	{
		this->m_iCannonEnergy = this->m_iCannonEnergyMax;
	}
}
void CPlayer::DecreaseCannonEnergy(int iDecrease)
{
	this->m_iCannonEnergy -= iDecrease;

	if(this->m_iCannonEnergy < 0)
	{
		this->m_iCannonEnergy = 0;
	}
}

void CPlayer::IncreaseBoost(float fFrametime)
{
	this->m_fBoostClock += fFrametime;

	if(this->m_fBoostClock > this->m_fBoostSpeed)
	{
		this->m_fBoostClock = this->m_fBoostSpeed;
	}

	this->m_fBoost = this->m_fBoostMax * this->m_fBoostClock / this->m_fBoostSpeed;
	this->m_bBoostIncrease = true;

	if(this->m_fBoost >= this->m_fBoostMax)
	{
		this->m_fBoost = this->m_fBoostMax;
		this->m_bBoostIncrease = false;
	}
}

void CPlayer::DecreaseBoost(float fFrametime)
{
	this->m_fBoostClock -= 2 * fFrametime;

	if(this->m_fBoostClock < 0.0f)
	{
		this->m_fBoostClock = 0.0f;
	}

	this->m_fBoost = this->m_fBoostMax * this->m_fBoostClock / this->m_fBoostSpeed;

	if(this->m_fBoost <= 0.0f)
	{
		this->m_fBoost = 0.0f;
	}
}

void CPlayer::SetLevelStartVelocityControls()
{
	this->m_bVerticalControl = false;
	this->m_bVelocityControl = true;
	this->m_bBoostIncrease = false;
	this->m_bBoostIncreaseSound = false;
	this->m_bBoostSoundCheck = true;

	this->m_fBoost = 0.0f;
}

void CPlayer::UpdateBoostSound()
{
	if (this->m_bBoostIncrease && (m_fBoost < m_fBoostMax))
	{
		this->m_bBoostSoundCheck = false;
		this->m_bBoostIncreaseSound = true;
	}
}

void CPlayer::ResetBoost()
{
	this->m_fBoost = 0.0f;
	this->m_fBoostClock = 0.0f;
	this->m_bBoostSoundCheck = true;
}
