#pragma once

#include "MenuObject.h"

class CHighscorePlayerShip : public CMenuObject
{
public:

	enum eACTION_MODE
	{
		eACTION_MODE_NONE,
		eACTION_MODE_ENTER,
		eACTION_MODE_RESPOND,
		eACTION_MODE_LEAVE,
		eACTION_MODE_EXIT
	};

	CHighscorePlayerShip(void);
	~CHighscorePlayerShip(void);

	virtual void Init();
	virtual void Update(float fFrametime);
	virtual void RotateRight();

	bool IsAfterburnEnabled();
	void SetActionMode(eACTION_MODE eActionMode);

	inline eACTION_MODE GetActionMode() { return this->m_eActionMode; }
	inline void SetShipEnterEndPosX(float posX) { this->m_fShipEnterEndPosX = posX; }
	inline void SetShipPosY(float posY) { this->m_fShipPosY = posY; }

protected:

	virtual void ChangeVertical();
	virtual void InitPosition();

	virtual D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material);

private:

	const float		SHIP_ENTER_AFTERBURN_END_DELTA = 0.3f;
	const float		SHIP_ENTER_DURATION = 1.75f;
	const float		SHIP_LEAVE_DURATION = 1.20f;

	eACTION_MODE	m_eActionMode;

	float			m_fShipPosY;

	float			m_fShipMoveTimer;
	float			m_fShipEnterStartPosX;
	float			m_fShipEnterEndPosX;
	float			m_fShipLeaveEndPosX;
};

