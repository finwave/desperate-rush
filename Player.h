#pragma once

#define SOUND_TIMER_HIT					1

#define SPRITE_PLAYER_BLAST_UP			1
#define SPRITE_PLAYER_BLAST_DOWN		3
#define SPRITE_PLAYER_BLAST_LEFT		7
#define SPRITE_PLAYER_BLAST_RIGHT		2
#define SPRITE_PLAYER_BLAST_UP_LEFT		4
#define SPRITE_PLAYER_BLAST_UP_RIGHT	0
#define SPRITE_PLAYER_BLAST_DOWN_LEFT	6
#define SPRITE_PLAYER_BLAST_DOWN_RIGHT	5

#include "TheApp.h"
#include "C3DObject.h"
#include "XFileContainer.h"
#include "Sprite.h"

class CPlayer : public C3DObject
{
public:

	enum eMINIGUN_SOUND
	{
		eMINIGUN_SOUND_BOOST_0_NORMAL,
		eMINIGUN_SOUND_BOOST_0_QUIET,
		eMINIGUN_SOUND_BOOST_1_NORMAL,
		eMINIGUN_SOUND_BOOST_1_QUIET,
		eMINIGUN_SOUND_BOOST_2_NORMAL,
		eMINIGUN_SOUND_BOOST_2_QUIET,
		eMINIGUN_SOUND_BOOST_3_NORMAL,
		eMINIGUN_SOUND_BOOST_3_QUIET,
		eMINIGUN_SOUND_BOOST_4_NORMAL,
		eMINIGUN_SOUND_BOOST_4_QUIET,
		eMINIGUN_SOUND_BOOST_5_NORMAL,
		eMINIGUN_SOUND_BOOST_5_QUIET
	};

	enum eHIT_SOUND
	{
		eHIT_SOUND_NORMAL,
		eHIT_SOUND_QUIET
	};

	enum eBLAST_LIGHT
	{
		eBLAST_LIGHT_HIGH,
		eBLAST_LIGHT_LOW
	};

	CPlayer(void);
	virtual ~CPlayer(void);

	/* 
	 * Create
	 * Create mesh and load object from x-file
	 */
	HRESULT Create(	CTheApp* pTheApp,
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
					int iBlasts);

	/*
	 * Clean-up all mess in this class
	 */
	void Release(void);

	void Update(bool bUpdate, 
				float fFrametime);

	void Render();

	inline eMINIGUN_SOUND GetMinigunSound() { return this->m_eMinigunSound; }
	inline eHIT_SOUND GetHitSound() { return this->m_eHitSound; }

	inline bool IsAlive(void) const { return this->m_iHealth > 0; }

	void SetUntouchable(bool bUntouchable);
	inline bool IsUntouchable(void) { return this->m_fUntouchable > 0.0f; }
	
	char* GetScoreString(void);
	char* GetShipHealth(void);
	
	void IncreaseHealth(int iHealth);
	void DecreaseHealth(int iDamage);

	inline float GetWidth(void) const { return this->m_fShipWidth; }
	inline float GetHeight(void) const { return this->m_fShipHeight; }

	inline float GetSpeed() { return this->m_fSpeed; }
	inline float GetVelocity() { return this->m_fVelocity + this->m_fBoost; }
	
	inline void SetVelocity(float velocity) { this->m_fVelocity = velocity; }
	
	inline void SetBoost(float boost) { this->m_fBoost = boost; }
	inline float GetBoost() { return this->m_fBoost; }
	
	void ResetBoost();

	inline void SetBoostMax(float boostMax) { this->m_fBoostMax = boostMax; }

	inline boolean IsMaxBoost() { return this->m_fBoost == this->m_fBoostMax; }
	inline boolean IsMinBoost() { return this->m_fBoost == 0.0f; }

	inline void SetVerticalControl(bool control) { this->m_bVerticalControl = control; }
	inline void SetVelocityControl(bool control) { this->m_bVelocityControl = control; }

	inline bool IsVerticalControl() { return this->m_bVerticalControl; }
	inline bool IsVelocityControl() { return this->m_bVelocityControl; }

	inline bool IsBoostIncrease() { return this->m_bBoostIncrease; }
	inline void DisableBoostIncrease() { this->m_bBoostIncrease = false; }

	inline bool IsBoostIncreaseSound() { return this->m_bBoostIncreaseSound; }
	inline void DisableBoostIncreaseSound() { this->m_bBoostIncreaseSound = false; }
	inline void SetBoostSoundCheck() { this->m_bBoostSoundCheck = true; }

	void IncreaseBoost(float fFrametime);
	void DecreaseBoost(float fFrametime);

	void SetLevelStartVelocityControls();

	inline int GetBlasts() { return this->m_iBlasts; }
	inline void IncreaseBlasts() { this->m_iBlasts++; }
	inline void DecreaseBlasts() { this->m_iBlasts--; }

	inline int GetBlastDamage() { return this->m_iBlastDamage; }

	inline bool IsShield(void) { return this->m_bShield; }
	inline void SetShield(bool bShield) { this->m_bShield = bShield; }

	inline void SetMinigunRotation(bool minigunRotation) { this->m_bMinigunRotation = minigunRotation; }
	inline bool GetMinigunRotation() { return this->m_bMinigunRotation; }

	inline void SetMinigunMode(int iMinigunMode) { this->m_iMinigunMode = iMinigunMode; }
	inline int GetMinigunMode() { return this->m_iMinigunMode; }

	inline void SetMinigunBulletPlace(int iMinigunBulletPlace) { this->m_iMinigunBulletPlace = iMinigunBulletPlace; }
	inline int GetMinigunBulletPlace() { return this->m_iMinigunBulletPlace; }

	inline int GetMinigunBoost() { return this->m_iMinigunLevel; }

	inline int GetMinigunDamage() { return this->m_iMinigunDamage; }
	inline float GetMinigunSpeed() { return this->m_fMinigunSpeed; }
	inline float GetMinigunFirerate() { return this->m_fMinigunFirerate; }

	inline int GetCannonEnergy() { return this->m_iCannonEnergy; }
	inline void ResetCannonEnergy() { this->m_iCannonEnergy = this->m_iCannonEnergyMax; }
	inline bool IsCannonEnergyMax() { return this->m_iCannonEnergy == this->m_iCannonEnergyMax; }

	inline void IncreaseScore(int score) { this->m_iScore += score; }
	inline int GetScore() { return this->m_iScore; }

	inline bool IsDestroyed() { return this->m_bDestroyed; }
	inline void SetDestroyed(bool bDestroyed) { this->m_bDestroyed = bDestroyed; }

	inline void SetLives(int iLives) { this->m_iLives = iLives; }
	inline int GetLives() { return this->m_iLives; }
	inline void ExtraLife() { this->m_iLives++; }
	inline void LoseLife() { this->m_iLives--; }

	inline void SetHealth(int iHealth) { this->m_iHealth = iHealth; }
	inline int GetHealth() { return this->m_iHealth; }

	inline void ResetHitSoundTimer() { this->m_fHitSoundTimer = 0.0f; }

	inline eBLAST_LIGHT GetBlastLight() { return this->m_eBlastLight; }

	void IncreaseMinigunLevel();

	void ChangeMinigunSound();
	void ChangeHitSound();
	void ResetMinigunSound();
	void ResetHitSound(float fFrametime);

	void SetBlast(bool bBlast);

	bool GameOver();

	void IncreaseCannonEnergy(int iIncrease);
	void DecreaseCannonEnergy(int iDecrease);

private:

	// sets minigun damage, bullet speed and firing rate
	// according to current boost level
	void SetMinigunSpecs();

	void UpdateBlast(float fFrametime);
	void RenderBlast();

	void UpdateBoostSound();

	CTheApp*		m_pTheApp;
	CSprite*		m_pSpriteBlast;

	eMINIGUN_SOUND	m_eMinigunSound;
	eHIT_SOUND		m_eHitSound;
	eBLAST_LIGHT	m_eBlastLight;

	float			m_fShipWidth;
	float			m_fShipHeight;

	float			m_fUntouchable;

	float			m_fSpeed;
	float			m_fVelocity;

	float			m_fBoost;
	float			m_fBoostMax;
	float			m_fBoostClock;
	float			m_fBoostSpeed;

	bool			m_bVerticalControl;
	bool			m_bVelocityControl;

	bool			m_bBoostIncrease;
	bool			m_bBoostIncreaseSound;
	bool			m_bBoostSoundCheck;

	int				m_iLives;
	int				m_iHealth;
	int				m_iHealthMax;

	bool			m_bDestroyed;

	// indicates whether the miniguns can
	// be turned or not (mode button)
	bool		m_bMinigunRotation;

	// minigun firing mode
	// 0 = front fire, 1 = diagonal fire
	int			m_iMinigunMode;

	// minigun bullet place
	// 0 = inner, 1 = outer
	int			m_iMinigunBulletPlace;

	// minigun boost level (0-5)
	int			m_iMinigunLevel;

	// minigun damage, bullet speed and firing rate
	int			m_iMinigunDamage;
	float		m_fMinigunSpeed;
	float		m_fMinigunFirerate;

	// cannon energy values
	int			m_iCannonEnergyMax;
	int			m_iCannonEnergy;

	// number of blasts available
	int			m_iBlasts;
	// blast damage
	int			m_iBlastDamage;
	// blast timers
	float		m_fBlastBeamTime;
	float		m_fBlastBeamCounter;

	bool		m_bBlast;

	bool		m_bBlastBeamUp;
	bool		m_bBlastBeamDown;
	bool		m_bBlastBeamLeft;
	bool		m_bBlastBeamRight;
	bool		m_bBlastBeamUpLeft;
	bool		m_bBlastBeamUpRight;
	bool		m_bBlastBeamDownLeft;
	bool		m_bBlastBeamDownRight;

	bool		m_bShield;

	int			m_iScore;

	float		m_fHitSoundTimer;

	float		m_fScreenPixelWidth;
	float		m_fScreenPixelHeight;
};