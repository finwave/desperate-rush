#include "ObjectController.h"

CObjectController::CObjectController(	float fMaxRotationLeft,
										float fMaxRotationRight,
										float fRotationSpeed,
										eTYPE eType)
{
	this->m_eType = eType;
	this->m_eAction = eACTION_NONE;

	this->m_bRotateLeft = false;
	this->m_bRotateRight = false;
	this->m_bRotateStraight = false;
	this->m_bIsStraight = true;

	this->m_fMaxRotationLeft = fMaxRotationLeft;
	this->m_fMaxRotationRight = fMaxRotationRight;
	this->m_fRotationSpeed = fRotationSpeed;

	this->m_fAngle = 0.0f;
}

CObjectController::~CObjectController(void)
{
}

void CObjectController::Update(float fFrametime, 
							   void *pExtraData)
{
	const float fRotation = this->m_fRotationSpeed * fFrametime;

	// get enemy's local matrix to temp matrix
	D3DXMATRIX& mObject = this->m_pObject->GetLocalMatrix();

	D3DXMATRIX mRotation;
	D3DXMatrixIdentity(&mRotation);

	// need to rotate left
	if(this->m_bRotateLeft)
	{
		float fNewAngle = this->m_fAngle + fRotation;

		// default rotation speed is too much
		// enemy will rotate over it's max rotation
		// need to rotate less than default
		if(fNewAngle > this->m_fMaxRotationLeft)
		{
			float fAngleIncrease = this->m_fMaxRotationLeft - this->m_fAngle;

			// rotate to left
			if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
			{
				D3DXMatrixRotationX(&mRotation, fAngleIncrease);
			}

			// update angle
			this->m_fAngle += fAngleIncrease;
		}
		// enemy rotates in default speed (fRotation)
		else
		{
			// rotate to left
			if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
			{
				D3DXMatrixRotationX(&mRotation, fRotation);
			}

			// update angle
			this->m_fAngle += fRotation;
		}
	}
	// need to rotate right
	else if(this->m_bRotateRight)
	{
		float fNewAngle = this->m_fAngle - fRotation;

		// default rotation speed is too much
		// enemy will rotate over it's max rotation
		// need to rotate less than default
		if(fNewAngle < -this->m_fMaxRotationRight)
		{
			float fAngleIncrease = -this->m_fMaxRotationRight - this->m_fAngle;

			// rotate to right
			if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
			{
				D3DXMatrixRotationX(&mRotation, fAngleIncrease);
			}

			// update angle
			this->m_fAngle += fAngleIncrease;
		}
		// enemy rotates in default speed (fRotation)
		else
		{
			// rotate to right
			if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
			{
				D3DXMatrixRotationX(&mRotation, -fRotation);
			}

			// update angle
			this->m_fAngle += -fRotation;
		}
	}
	// straighten enemy
	else if(this->m_bRotateStraight)
	{
		// enemy is not rotated to straight position
		if( this->m_fAngle != 0.0f )
		{
			// straighten to left side
			if( this->m_fAngle < 0.0f)
			{
				// default straightening speed is too much
				// enemy will rotate over it's straight position
				// need to rotate less than default
				if( (this->m_fAngle + fRotation) > 0.0f)
				{
					// fAngle IS negative, so we get a positive angle
					// straightens to left side
					if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
					{
						D3DXMatrixRotationX(&mRotation, -this->m_fAngle);
					}
					// update angle
					this->m_fAngle += -this->m_fAngle;
				}
				// enemy straightens in default speed (fRotation)
				else
				{
					if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
					{
						D3DXMatrixRotationX(&mRotation, fRotation);
					}
					// update angle
					this->m_fAngle += fRotation;
				}
			}
			// straighten to right side
			else if( this->m_fAngle > 0.0f)
			{
				// default straightening speed is too much
				// enemy will rotate over it's straight position
				// need to rotate less than default
				if( (this->m_fAngle - fRotation) < 0.0f)
				{
					// fAngle IS positive, so we get a negative angle
					// straightens to right side
					if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
					{
						D3DXMatrixRotationX(&mRotation, -this->m_fAngle);
					}
					// update angle
					this->m_fAngle += -this->m_fAngle;
				}
				// enemy straightens in default speed (fRotation)
				else
				{
					if(this->m_eType == eTYPE_HIGHSCORE_PLAYER)
					{
						D3DXMatrixRotationX(&mRotation, -fRotation);
					}
					// update angle
					this->m_fAngle += -fRotation;
				}
			}
			// straighten enemy
			D3DXMatrixMultiply(&mObject, &mObject, &mRotation);
		}
		// enemy is rotated to straight position
		else if( this->m_fAngle == 0.0f )
		{
			this->m_bRotateStraight = false;
			this->m_bIsStraight = true;
		}
	}
	// rotate enemy left
	if( this->m_bRotateLeft )
	{
		// not reached max rotation angle
		if( this->m_fAngle < this->m_fMaxRotationLeft)
		{
			if( this->m_bIsStraight )
			{
				this->m_bIsStraight = false;
			}
			// rotate enemy left
			D3DXMatrixMultiply(&mObject, &mObject, &mRotation);
		}
	}
	// rotate enemy right
	else if( this->m_bRotateRight )
	{
		// not reached max rotation angle
		if( this->m_fAngle > -this->m_fMaxRotationRight)
		{
			if( this->m_bIsStraight )
			{
				this->m_bIsStraight = false;
			}
			// rotate enemy right
			D3DXMatrixMultiply(&mObject, &mObject, &mRotation);
		}
	}

	this->CorrectZAxisPosition();
}

void CObjectController::CommitAction(eACTION eAction)
{
	switch(eAction)
	{
	case eACTION_ROLL_LEFT:

		if(!this->m_bRotateLeft)
		{
			this->m_bRotateLeft = true;

			if(this->m_bRotateRight)
			{
				this->m_bRotateRight = false;
			}
		}
		break;

	case eACTION_ROLL_RIGHT:

		if(!this->m_bRotateRight)
		{
			this->m_bRotateRight = true;

			if(this->m_bRotateLeft)
			{
				this->m_bRotateLeft = false;
			}
		}
		break;
	}
}

void CObjectController::StopRotation()
{
	switch (this->m_eType)
	{
	case eTYPE_HIGHSCORE_PLAYER:

		this->m_bRotateLeft = false;
		this->m_bRotateRight = false;
		this->m_bRotateStraight = true;
		this->m_eAction = eACTION_NONE;

		break;
	}
}

bool CObjectController::RotateToStraight()
{
	if (!this->m_bRotateLeft && !this->m_bRotateRight)
	{
		return true;
	}

	return false;
}

void CObjectController::CorrectZAxisPosition()
{
	D3DXVECTOR3 pos = m_pObject->GetPosition();

	switch(this->m_eType)
	{
	case eTYPE_HIGHSCORE_PLAYER:
		pos.z = 0.0f;
		break;
	}

	m_pObject->SetPosition(pos);
}
