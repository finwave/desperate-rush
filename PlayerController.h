#pragma once

#include "i3dobjectcontroller.h"
#include "InputJoystick.h"
#include "TheApp.h"
#include "Player.h"

class CPlayerController: public I3DObjectController
{
public:

	CPlayerController(	CTheApp* pTheApp,
						CInputJoystick* pJoystick,
						float fScreenWidth,
						float fScreenHeight,
						float fPlayerWidth,
						float fPlayerHeight,
						float fPlayerSpeed);

	virtual ~CPlayerController(void);

	void UpdatePlayer(float fFrametime, CPlayer* pPlayer);

	inline bool GetExecuteInputs() { return this->m_bExecuteInputs; }
	inline void SetExecuteInputs(bool bExecute) { this->m_bExecuteInputs = bExecute; }

private:

	enum eMOVE
	{
		eMOVE_STAY,
		eMOVE_UP,
		eMOVE_DOWN,
		eMOVE_LEFT,
		eMOVE_RIGHT
	};

	void CheckControlsFirst();
	void CheckControlsLast(CPlayer* pPlayer);
	bool RotateToStraight();
	void CorrectZAxisPosition();

	// pointer to TheApp
	// need player movement controls
	CTheApp*				m_pTheApp;

	CInputJoystick*			m_pJoystick;

	eMOVE					m_eMove;
	eMOVE					m_eMoveOld;

	bool					m_bExecuteInputs;

	bool					m_bMovement;
	bool					m_bMoveUp;
	bool					m_bMoveDown;
	bool					m_bMoveLeft;
	bool					m_bMoveRight;

	bool					m_bRotateLeft;
	bool					m_bRotateRight;
	bool					m_bRotateStraight;
	bool					m_bIsStraight;
	bool					m_bMaxAngle;
	bool					m_bCheckStraightening;

	float					m_fScreenWidth;
	float					m_fScreenHeight;
	float					m_fPlayerWidth;
	float					m_fPlayerHeight;
	float					m_fPlayerSpeed;

	float					m_fRotationSpeed;
	float					m_fMaxRotation;

	float					m_fAngleY;
};