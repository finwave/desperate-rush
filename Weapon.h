#pragma once

#include "C3DObject.h"
#include "XFileContainer.h"
#include "Sprite.h"
#include "Resources.h"

class CWeapon : public C3DObject
{
public:

	static std::vector<CSprite> s_SpritesGame;
	static std::vector<CSprite> s_SpritesHighscore;

	enum eOWNER
	{
		eOWNER_PLAYER,
		eOWNER_ENEMY,
		eOWNER_BOSS
	};

	enum eBULLET_TYPE
	{
		eBULLET_TYPE_PLAYER_HIGHSCORE,
		eBULLET_TYPE_PLAYER_FRONT,
		eBULLET_TYPE_PLAYER_DIAGONAL,
		eBULLET_TYPE_ENEMY_DRONE,
		eBULLET_TYPE_ENEMY_SNIPER,
		eBULLET_TYPE_ENEMY_ROLLER,
		eBULLET_TYPE_ENEMY_GUARD,
		eBULLET_TYPE_BOSS_1_LASER,
		eBULLET_TYPE_BOSS_1_SCATTER,
		eBULLET_TYPE_BOSS_1_MISSILE
	};

	enum eDAMAGE_TYPE
	{
		ONLY_SHOTED_OBJECT,
		TOTAL_DESTRUCTION
	};

	enum eSIDE
	{
		eSIDE_LEFT,
		eSIDE_RIGHT
	};

	enum eBULLET_PLACE
	{
		eBULLET_PLACE_INNER,
		eBULLET_PLACE_OUTER,
		eBULLET_PLACE_1,
		eBULLET_PLACE_2,
		eBULLET_PLACE_3,
		eBULLET_PLACE_4
	};

	enum eDIRECTION
	{
		eDIRECTION_UP,
		eDIRECTION_DOWN,
		eDIRECTION_LEFT,
		eDIRECTION_RIGHT,
		eDIRECTION_UP_LEFT,
		eDIRECTION_UP_UP_LEFT,
		eDIRECTION_UP_LEFT_LEFT,
		eDIRECTION_UP_RIGHT,
		eDIRECTION_UP_UP_RIGHT,
		eDIRECTION_UP_RIGHT_RIGHT,
		eDIRECTION_DOWN_LEFT,
		eDIRECTION_DOWN_DOWN_LEFT,
		eDIRECTION_DOWN_LEFT_LEFT,
		eDIRECTION_DOWN_RIGHT,
		eDIRECTION_DOWN_DOWN_RIGHT,
		eDIRECTION_DOWN_RIGHT_RIGHT
	};

	CWeapon(void);
	virtual ~CWeapon(void);

	virtual HRESULT Create( LPDIRECT3DDEVICE9 pDevice,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fWidth,
							float fHeight,
							float fSpeed,
							int iDamage,
							eBULLET_TYPE eBulletType);

	virtual HRESULT Create( LPDIRECT3DDEVICE9 pDevice,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							float fWidth,
							float fHeight,
							float fSpeed,
							int iDamage,
							eBULLET_TYPE eBulletType);

	virtual void Release();

	virtual void Update(float fFrametime, float fPlayerVelocity);

	void DrawSpriteBulletPlayer(
		D3DXVECTOR3 posLeft,
		D3DXVECTOR3 posRight,
		bool bBulletLeft,
		bool bBulletRight);

	void DrawSpriteBulletDrone();
	void DrawSpriteBulletSniper();
	void DrawSpriteBulletRoller();
	void DrawSpriteBulletGuard();
	void DrawSpriteBulletBoss1Laser();
	void DrawSpriteBulletBoss1Scatter();

	D3DXVECTOR3* GetBulletPosition();
	virtual void DisableBullet(int iBullet);

	virtual bool BulletActivity(int iBullet) { return this->m_bActive == TRUE; }
	virtual bool BulletVisibility(int iBullet) { return this->m_bVisible == TRUE; }

	void SetLocalPosition(float x, float y, float z);

	inline void SetOwner(eOWNER eOwner) { this->m_eOwner = eOwner; }
	inline eOWNER GetOwner(void) const { return this->m_eOwner; }

	inline void SetBulletType(eBULLET_TYPE eBulletType) { this->m_eBulletType = eBulletType; }
	inline eBULLET_TYPE GetBulletType(void) const { return this->m_eBulletType; }

	inline void SetDamageType(eDAMAGE_TYPE eDamageType) { this->m_eDamageType = eDamageType; }
	inline eDAMAGE_TYPE GetDamageType(void) const { return this->m_eDamageType; }

	inline void SetSide(eSIDE eSide) { this->m_eSide = eSide; }

	inline void SetBulletPlace(eBULLET_PLACE ePlace) { this->m_eBulletPlace = ePlace; }
	inline eBULLET_PLACE GetBulletPlace(void) const { return this->m_eBulletPlace; }

	inline void SetDirection(eDIRECTION eDirection) { this->m_eDirection = eDirection; }
	inline eDIRECTION GetDirection(void) const { return this->m_eDirection; }

	inline float GetSpeed() { return this->m_fSpeed; }
	inline void SetSpeed(float fSpeed) { this->m_fSpeed = fSpeed; }

	inline int GetDamage() { return this->m_iDamage; }
	inline void SetDamage(int iDamage) { this->m_iDamage = iDamage; }

	inline float GetWidth() { return this->m_fWidth; }
	inline float GetHeight() { return this->m_fHeight; }

	virtual void SetMatrix(C3DObject* pShip);

	virtual void InitDirection();
	virtual void InitPosition();
	virtual void InitRotation();

	virtual CWeapon* GetBulletLeft();
	virtual CWeapon* GetBulletRight();

	I3DObject* GetShipObject() { return this->m_pShipObject; }
	void SetShipObject(I3DObject* object) { this->m_pShipObject = object; }

protected:

	virtual void Create(LPDIRECT3DDEVICE9 pDevice,
						float fWidth,
						float fHeight,
						float fSpeed,
						int iDamage,
						eBULLET_TYPE eBulletType);

	LPDIRECT3DDEVICE9	m_pDevice;

	I3DObject*			m_pShipObject;

	eOWNER				m_eOwner;
	eBULLET_TYPE		m_eBulletType;
	eDAMAGE_TYPE		m_eDamageType;
	eSIDE				m_eSide;
	eBULLET_PLACE		m_eBulletPlace;
	eDIRECTION			m_eDirection;

	float				m_fMove;
	float				m_fWidth;
	float				m_fHeight;
	float				m_fSpeed;
	int					m_iDamage;

	float				m_fScreenPixelWidth;
	float				m_fScreenPixelHeight;
};