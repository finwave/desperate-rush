#pragma once

#include <cmath>

#include "C3DObject.h"
#include "TheApp.h"
#include "GameSettings.h"
#include "Queue.h"
#include "Sprite.h"
#include "Weapon.h"
#include "Player.h"
#include "Obstacle.h"
#include "XFileContainer.h"

class IEnemy : public C3DObject
{
public:

	enum eTYPE
	{
		eTYPE_DRONE,
		eTYPE_SNIPER,
		eTYPE_ROLLER,
		eTYPE_GUARD,
		eTYPE_BOSS_1_CORE,
		eTYPE_BOSS_1_FRAME,
		eTYPE_BOSS_1_LASER_LEFT,
		eTYPE_BOSS_1_LASER_RIGHT,
		eTYPE_BOSS_1_SCATTER_LEFT,
		eTYPE_BOSS_1_SCATTER_RIGHT,
		eTYPE_BOSS_1_CANNON
	};

	enum eBEHAVIOUR
	{
		eBEHAVIOUR_LAUNCH,
		eBEHAVIOUR_STRIKE,
		eBEHAVIOUR_REINFORCEMENT,
		eBEHAVIOUR_OBSTACLE,
		eBEHAVIOUR_BOSS
	};

	enum eROLLER_ACTION
	{
		eROLLER_ACTION_PASSIVE,
		eROLLER_ACTION_ATTACK
	};

	enum eREINFORCEMENT_ACTION
	{
		eREINFORCEMENT_ACTION_NONE,
		eREINFORCEMENT_ACTION_WAIT,
		eREINFORCEMENT_ACTION_SENT
	};

	enum eSOUND_FIRING
	{
		eSOUND_FIRING_NORMAL_1,
		eSOUND_FIRING_NORMAL_2,
		eSOUND_FIRING_QUIET_1,
		eSOUND_FIRING_QUIET_2
	};

	enum eSOUND_HIT
	{
		eSOUND_HIT_NORMAL,
		eSOUND_HIT_QUIET
	};

	enum eSOUND_STRIKE_AFTERBURN
	{
		eSOUND_STRIKE_AFTERBURN_1,
		eSOUND_STRIKE_AFTERBURN_2,
		eSOUND_STRIKE_AFTERBURN_3,
		eSOUND_STRIKE_AFTERBURN_4
	};

	enum eMOVE
	{
		eMOVE_STAY,
		eMOVE_UP,
		eMOVE_DOWN,
		eMOVE_LEFT,
		eMOVE_RIGHT,
		eMOVE_UP_LEFT,
		eMOVE_UP_RIGHT,
		eMOVE_DOWN_LEFT,
		eMOVE_DOWN_RIGHT
	};

	enum eROTATION_X
	{
		eROTATION_X_NONE,
		eROTATION_X_UP,
		eROTATION_X_DOWN
	};

	enum eROTATION_Z
	{
		eROTATION_Z_NONE,
		eROTATION_Z_LEFT,
		eROTATION_Z_RIGHT
	};

	enum eMOVE_DAMAGE_SIDE
	{
		eMOVE_DAMAGE_SIDE_LEFT,
		eMOVE_DAMAGE_SIDE_RIGHT
	};

	enum eMOVE_DAMAGE_LEVEL
	{
		eMOVE_DAMAGE_LEVEL_0,
		eMOVE_DAMAGE_LEVEL_1,
		eMOVE_DAMAGE_LEVEL_2
	};

	enum eENEMY_DEPTH
	{
		eENEMY_DEPTH_1,
		eENEMY_DEPTH_2,
		eENEMY_DEPTH_3,
		eENEMY_DEPTH_4,
		eENEMY_DEPTH_5
	};


	IEnemy();
	virtual ~IEnemy();

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect);

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							CSprite* pSpriteAfterburn,
							int iVolumeSoundEffect);

	virtual void Release();

	virtual void Update(float fFrametime, float fPlayerVelocity);
	void UpdateShake(float fFrametime);

	void UpdateBossCannonShake(float fFrametime);
	void UpdateBossBlastShake(float fFrametime);
	void UpdateEnemyCannonShake(float fFrametime);
	void UpdateEnemyBlastShake(float fFrametime);

	void RenderEnemyAfterburn(bool bFreeze, bool bPauseTimer);

	virtual HRESULT InitWeapons(CTheApp* pTheApp,
								LPD3DXMESH mesh,
								std::vector<D3DMATERIAL9*> materials,
								std::vector<LPDIRECT3DTEXTURE9> textures,
								float fBulletWidth,
								float fBulletHeight,
								float fBulletSpeed,
								int iBulletDamage);

	virtual HRESULT InitWeapons(CTheApp* pTheApp,
								LPD3DXMESH mesh,
								std::vector<MESHDATA>& meshData,
								float fBulletWidth,
								float fBulletHeight,
								float fBulletSpeed,
								int iBulletDamage);

	bool Destroyed(int iDamage);

	void InitReinforcementSend();
	void InitObstacleEnemy(float fSpeed);
	void InitScores();
	void InitRotationValues();
	void ChangeFiringSound();
	void ChangeHitSound();

	void SetBlastShake();
	void SetTimedExplosion();
	void ResetTimedExplosion();
	void ResetFleeMovement();

	void GetRandomBonus();

	void ClearBullets(bool bForced);
	void RenderBullets(bool bFreeze, float fFrametime, float playerVelocity);

	bool CollisionBulletVsPlayer(CPlayer* pPlayer);
	void CollisionBulletVsBorder();
	void CollisionEnemyVsPlayer(CPlayer* pPlayer);
	void CollisionPlayerCannonVsBullets(CPlayer* player);

	void MoveAvoidLaunch(CQueue<IEnemy*>* pActiveEnemies);

	void MoveAvoidObstacle(	CQueue<IEnemy*>* pActiveEnemies,
							CQueue<CObstacle*>* pObstacles);

	virtual bool Shoot() = 0;

	inline bool IsEnter() { return this->m_bEnter; }
	inline void SetEnter(bool bEnter) { this->m_bEnter = bEnter; }

	inline bool IsFleeReady() { return this->m_bFleeReady; }
	inline void SetFleeReady(bool bReady) { this->m_bFleeReady = bReady; }
	inline void SetFleeMovement(bool bMovement) { this->m_bFleeMovement = bMovement; }

	inline eSOUND_FIRING GetFiringSound() { return this->m_eSoundFiring; }
	inline eSOUND_HIT GetHitSound() { return this->m_eSoundHit; }

	inline void SetSoundStrikeAfterburn (eSOUND_STRIKE_AFTERBURN eSound) { this->m_eSoundStrikeAfterburn = eSound; }

	inline int GetScoreHit() { return this->m_iScoreHit; }
	inline int GetScoreDestroyed() { return this->m_iScoreDestroyed; }

	inline int GetHealth() { return this->m_iHealth; }
	inline void SetHealth( int iHealth ) { this->m_iHealth = iHealth; }
	inline void SetMaxHealth() { this->m_iHealth = this->m_iHealthMax; }

	inline float GetSpeed() { return this->m_fSpeed; }
	inline void SetSpeed(float fSpeed) { this->m_fSpeed = fSpeed; }
	inline void SetSpeedChange(bool bChange) { this->m_bSpeedChange = bChange; }

	inline float GetWidth() { return this->m_fEnemyWidth; }
	inline float GetHeight() { return this->m_fEnemyHeight; }

	inline void SetType(eTYPE eType) { this->m_eType = eType; }
	inline eTYPE GetType() const { return this->m_eType; }

	inline void SetBehaviour(eBEHAVIOUR eBehaviour) { this->m_eBehaviour = eBehaviour; }
	inline eBEHAVIOUR GetBehaviour() const { return this->m_eBehaviour; }

	inline void SetReinforcementAction(eREINFORCEMENT_ACTION eAction) { this->m_eReinforcementAction = eAction; }
	inline eREINFORCEMENT_ACTION GetReinforcementAction() const { return this->m_eReinforcementAction; }

	inline eMOVE GetMovement() { return this->m_eMove; }
	inline void SetMovement(eMOVE eMove) { this->m_eMove = eMove; }

	inline eMOVE_DAMAGE_LEVEL GetMoveDamageLevel() { return this->m_eMoveDamageLevel; }
	inline void SetMoveDamageLevel(eMOVE_DAMAGE_LEVEL eLevel) { this->m_eMoveDamageLevel = eLevel; }

	inline void SetSpriteAfterburn(CSprite* pAfterburn) { this->m_pSpriteAfterburn = pAfterburn; }
	inline CSprite* GetSpriteAfterburn() { return this->m_pSpriteAfterburn; }

	inline void SetBonus(bool bBonus) { this->m_bBonus = bBonus; }
	inline bool GetBonus() { return this->m_bBonus; }

	inline void SetAfterburn(bool bAfterburn) { this->m_bAfterburn = bAfterburn; }
	inline bool GetAfterburn() { return this->m_bAfterburn; }

	inline bool IsCannonDamage() { return this->m_bCannonDamage; }
	inline void SetCannonDamage(bool bSet) { this->m_bCannonDamage = bSet; }

	inline void SetAfterburnSoundStrike(bool bSound) { this->m_bSoundStrikeAfterburn = bSound; }

	inline float GetAngleX() { return this->m_fAngleX; }
	inline float GetAngleY() { return this->m_fAngleY; }
	inline float GetAngleZ() { return this->m_fAngleZ; }

	inline bool GetTimedExplosion() { return this->m_bTimedExplosion; }

	inline CQueue<CWeapon*>* GetBullets() { return &this->m_pBullets; }

	inline float GetShootTime() { return this->m_fShootTime; }

	inline eENEMY_DEPTH GetDepth() const { return this->m_eDepth; }

	void SetDepth(int depth);
	void SetDepth(eENEMY_DEPTH eDepth);

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

	bool IsBoxCollision(const D3DXVECTOR3& pos1,
						float fWidth1,
						float fHeight1,
						const D3DXVECTOR3& pos2,
						float fWidth2,
						float fHeight2);

	virtual bool IsMeshCollision(	I3DObject* pObject1,
									I3DObject* pObject2,
									bool bInverseMatrix);

	void GenerateRandomShootTime();
	void GenerateRandomEnterSpeed();
	void GenerateRandomMoveTime();
	void GenerateRandomFleeTime();

	virtual void Move(float fFrametime, float fPlayerVelocity);

	virtual void ChangeRotationX() {}
	virtual void ChangeRotationZ() {}

	inline bool GetShootCount() { return this->m_bShootCount; }
	inline void SetShootCount(bool bCount) { this->m_bShootCount = bCount; }

	CQueue<CWeapon*>		m_pBullets;	

	CTheApp*				m_pTheApp;
	CGameSettings*			m_pGameSettings;

	eTYPE					m_eType;
	eBEHAVIOUR				m_eBehaviour;

	eROLLER_ACTION			m_eRollerAction;

	eREINFORCEMENT_ACTION	m_eReinforcementAction;

	eSOUND_FIRING			m_eSoundFiring;
	eSOUND_HIT				m_eSoundHit;
	eSOUND_STRIKE_AFTERBURN	m_eSoundStrikeAfterburn;
	
	eMOVE					m_eMove;
	eMOVE					m_eMoveOld;

	eROTATION_X				m_eRotationX;
	eROTATION_Z				m_eRotationZ;

	eMOVE_DAMAGE_SIDE		m_eMoveDamageSide;
	eMOVE_DAMAGE_LEVEL		m_eMoveDamageLevel;

	bool					m_bEnter;
	bool					m_bFleeReady;
	bool					m_bFleeMovement;
	bool					m_bSpeedSlowDown;

	bool					m_bBoss;
	bool					m_bShootCount;

	bool					m_bBonus;
	bool					m_bAfterburn;
	bool					m_bCannonDamage;

	bool					m_bRotateYLeft;
	bool					m_bRotateYRight;
	bool					m_bRotateYStraight;
	bool					m_bCheckStraighteningY;
	bool					m_bIsStraightY;

	bool					m_bSoundStrikeAfterburn;

	int						m_iVolumeSoundEffect;

	float					m_fScreenWidth;
	float					m_fScreenHeight;
	float					m_fScreenPixelWidth;
	float					m_fScreenPixelHeight;

	const float				SHIP_ENTER_AFTERBURN_END_DELTA = 0.45f;

	float					m_fShipEnterMoveDuration;
	float					m_fShipEnterMoveTimer;
	float					m_fShipEnterStartPosY;
	float					m_fShipEnterEndPosY;
	bool					m_bSetShipEnterDuration;

	float					m_fMovementBorderY;

	float					m_fSpeed;
	float					m_fSpeedDefault;
	float					m_fSpeedDivider;
	float					m_fSpeedChangeMultiplier;

	bool					m_bSpeedChange;

	float					m_fEnemyWidth;
	float					m_fEnemyHeight;

	int						m_iHealth;
	int						m_iHealthMax;
	int						m_iScoreHit;
	int						m_iScoreDestroyed;

	float					m_fMoveTime;
	float					m_fShootTime;
	float					m_fRandShootTime;
	float					m_fShootCounter;
	float					m_fFleeTime;
	float					m_fFleeCounter;
	float					m_fSpeedEnter;
	float					m_fFleeSpeedIncrease;
	float					m_fFleeSpeedMultiplier;

	bool					m_bEnterSound;
	bool					m_bFleeSound;

private:

	void SetMovementBorders();

	void MoveAvoidEnemy(bool bCollisionTop, bool bCollisionBottom, 
						bool bCollisionLeft, bool bCollisionRight);

	void InitFiringSound();

	void DamageMovement(float fFrametime);

	void Rotate(float fFrametime);
	void CheckMovement();
	bool RotateToStraight();
	void CorrectZAxisPosition();
	void StraightenEnemy();

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);
	virtual void MoveFlee(float fFrametime, float fPlayerVelocity);

	virtual void SetMoveState() = 0;

	void MoveReinforcement(float fFrametime, float fPlayerVelocity);
	void MoveReinforcementSpeedChange(float fFrametime, float fPlayerVelocity);

	CQueue<IEnemy*>			m_pCollisionEnemies;
	CSprite*				m_pSpriteAfterburn;

	bool					m_bBlastShakeUp;
	bool					m_bBlastShakeDown;
	bool					m_bBlastShakeLeft;
	bool					m_bBlastShakeRight;
	bool					m_bBlastShakeUpLeft;
	bool					m_bBlastShakeUpRight;
	bool					m_bBlastShakeDownLeft;
	bool					m_bBlastShakeDownRight;

	bool					m_bTimedExplosion;

	float					m_fTimedExplosionCounter;
	float					m_fTimedExplosionTimer;

	float					m_fMaxRotation;
	float					m_fRotationSpeed;

	float					m_fAngleX;
	float					m_fAngleY;
	float					m_fAngleZ;

	float					m_fDamageMoveCycleTime;
	float					m_fDamageMoveTime;
	float					m_fDamageMoveCycleCounter;

	float					m_fCannonDamageMoveCounter;
	float					m_fBlastDamageMoveCounter;

	int						m_iDamageMoves;
	int						m_iPauseAfterburn;

	eENEMY_DEPTH			m_eDepth;
};