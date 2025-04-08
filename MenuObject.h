#pragma once

#include "C3DObject.h"
#include "TheApp.h"
#include "XFileContainer.h"
#include "Queue.h"

class CMenuObject : public C3DObject
{
public:

	enum eTYPE
	{
		eTYPE_PLANET,
		eTYPE_SHIP,
		eTYPE_OTHER
	};

	enum eSHIP
	{
		eSHIP_NONE,
		eSHIP_MENUS_PLAYER,
		eSHIP_MENUS_DRONE,
		eSHIP_MENUS_SNIPER,
		eSHIP_MENUS_ROLLER,
		eSHIP_MENUS_GUARD,
		eSHIP_MENUS_BOSS_1,
		eSHIP_MENUS_BOSS_1_SCATTER_LEFT,
		eSHIP_MENUS_BOSS_1_SCATTER_RIGHT
	};

	enum eMOVE
	{
		eMOVE_STAY,
		eMOVE_RIGHT,
		eMOVE_LEFT
	};

	enum eROTATION
	{
		eROTATION_NONE,
		eROTATION_LEFT,
		eROTATION_RIGHT
	};

	CMenuObject(void);
	virtual ~CMenuObject(void);

	virtual void Create(CTheApp *pTheApp,
						LPD3DXMESH mesh,
						CXFileContainer xFile,
						float fScreenWidth,
						float fScreenHeight,
						eTYPE eType,
						eSHIP eShip);

	virtual void Create(CTheApp* pTheApp,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						float fScreenWidth,
						float fScreenHeight,
						eTYPE eType,
						eSHIP eShip);

	virtual void Init();
	virtual void Release(void);
	virtual void Update(float fFrametime);

	inline eSHIP GetShip() { return this->m_eShip; }
	inline eMOVE GetMove() { return this->m_eMove; }

	float GetDepth();
	void SetDepth(float fDepth);

	virtual void RotateLeft();
	virtual void RotateRight();

protected:

	virtual void Scale();

	virtual void Rotate(float fFrametime);
	virtual void ResetSelfRotation();

	void Move(float fFrametime);
	void ChangeDirection();

	virtual void ChangeVertical();

	void SetMoveBorder();
	void SetSpeedLimit();

	void ChangeSpeed();
	void RandomMoveTime();

	virtual void InitPosition();

	void InitTexture(CXFileContainer xFile);
	virtual D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material);

	CTheApp*		m_pTheApp;

	eTYPE			m_eType;
	eMOVE			m_eMove;
	eROTATION		m_eRotation;
	eSHIP			m_eShip;

	float			m_fScreenWidth;
	float			m_fScreenHeight;

	float			m_fSpeedCurrent;
	float			m_fSpeedMin;
	float			m_fSpeedMax;

	float			m_fSelfRotation;
	float			m_fMovementPauseTimer;

	float			m_fMoveBorderX;
};