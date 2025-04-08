#pragma once

#include "I3DObjectController.h"

class CObjectController : public I3DObjectController
{
public:

	enum eTYPE
	{
		eTYPE_HIGHSCORE_PLAYER
	};

	enum eACTION
	{
		eACTION_NONE,
		eACTION_ROLL_LEFT,
		eACTION_ROLL_RIGHT,
	};

	CObjectController(	float fMaxRotationLeft,
						float fMaxRotationRight,
						float fRotationSpeed,
						eTYPE eType);

	virtual ~CObjectController();

	void Update(float fFrametime, 
				void *pExtraData);

	void CommitAction(eACTION eActionType);
	void StopRotation();

	inline eACTION GetAction() { return this->m_eAction; }
	inline void SetAction(eACTION eAction) { this->m_eAction = eAction; }

	

private:

	bool RotateToStraight();
	void CorrectZAxisPosition();

	eTYPE		m_eType;
	eACTION		m_eAction;

	bool		m_bRotateLeft;
	bool		m_bRotateRight;
	bool		m_bRotateStraight;
	bool		m_bIsStraight;
	bool		m_bMaxAngle;

	float		m_fMaxRotationLeft;
	float		m_fMaxRotationRight;
	float		m_fRotationSpeed;
	float		m_fAngle;

	float		m_fScreenWidth;
	float		m_fScreenHeight;
	float		m_fSpeed;
};