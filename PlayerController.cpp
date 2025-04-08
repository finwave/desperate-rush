#include "PlayerController.h"

CPlayerController::CPlayerController(CTheApp* pTheApp,
									 CInputJoystick* pJoystick,
									 float fScreenWidth,
									 float fScreenHeight,
									 float fPlayerWidth,
									 float fPlayerHeight,
									 float fPlayerSpeed)
{
	this->m_pTheApp = pTheApp;
	this->m_pJoystick = pJoystick;

	this->m_eMove = eMOVE_STAY;
	this->m_eMoveOld = eMOVE_STAY;

	this->m_bExecuteInputs = true;

	this->m_bMovement = false;
	this->m_bMoveUp = false;
	this->m_bMoveDown = false;
	this->m_bMoveLeft = false;
	this->m_bMoveRight = false;

	this->m_bRotateLeft = false;
	this->m_bRotateRight = false;
	this->m_bRotateStraight = false;
	this->m_bIsStraight = true;
	this->m_bMaxAngle = false;
	this->m_bCheckStraightening = false;

	this->m_fScreenWidth = fScreenWidth;
	this->m_fScreenHeight = fScreenHeight;
	this->m_fPlayerWidth = fPlayerWidth;
	this->m_fPlayerHeight = fPlayerHeight;
	this->m_fPlayerSpeed = fPlayerSpeed;

	this->m_fRotationSpeed = 1.7f;
	this->m_fMaxRotation = 0.65f;

	this->m_fAngleY = 0.0f;
}

CPlayerController::~CPlayerController(void)
{
	this->m_pTheApp = NULL;
	this->m_pJoystick = NULL;
}

void CPlayerController::UpdatePlayer(float fFrametime, CPlayer* pPlayer)
{
	this->CheckControlsFirst();

	float fMovementBorder = 0.0f;
	float frameVelocity = 2.0f * ((this->m_fPlayerSpeed * fFrametime) / 1.6f);

	D3DXVECTOR3 pos = this->m_pObject->GetPosition();

	const float fRotation = this->m_fRotationSpeed * fFrametime;

	// player is moving
	if (this->m_bMovement)
	{
		// player is moving forward
		if (this->m_bMoveUp)
		{
			if (pPlayer->IsVelocityControl())
			{
				pPlayer->IncreaseBoost(fFrametime);
			}

			if (pPlayer->IsVerticalControl())
			{
				fMovementBorder = this->m_fScreenHeight - (this->m_fPlayerHeight / 2);
				pos.y += frameVelocity;

				if (pos.y > fMovementBorder)
				{
					pos.y = fMovementBorder;
				}
			}
		}
		// player is moving backward
		else if (this->m_bMoveDown)
		{
			pPlayer->DecreaseBoost(fFrametime);

			/*
			if (pPlayer->IsVelocityControl())
			{
				pPlayer->DecreaseBoost(fFrametime);
			}
			*/

			if (pPlayer->IsVerticalControl())
			{
				fMovementBorder = -this->m_fScreenHeight + (this->m_fPlayerHeight / 2);
				pos.y -= frameVelocity;

				if (pos.y < fMovementBorder)
				{
					pos.y = fMovementBorder;
				}
			}
		}

		// player is moving left
		if (this->m_bMoveLeft)
		{
			fMovementBorder = -this->m_fScreenWidth + (this->m_fPlayerWidth / 2);
			pos.x -= frameVelocity;

			if (pos.x < fMovementBorder)
			{
				pos.x = fMovementBorder;
			}

			if (this->m_bRotateLeft)
			{
				float fNewAngle = this->m_fAngleY + fRotation;

				// default rotation speed is too much
				// player will rotate over it's max rotation
				// need to rotate less than default
				if (fNewAngle > this->m_fMaxRotation)
				{
					float fAngleIncrease = this->m_fMaxRotation - this->m_fAngleY;
					// update angle
					this->m_fAngleY += fAngleIncrease;
				}
				// player rotates in default speed (fRotation)
				else
				{
					// update angle
					this->m_fAngleY += fRotation;
				}
			}
		}
		// player is moving right
		else if (this->m_bMoveRight)
		{
			fMovementBorder = this->m_fScreenWidth - (this->m_fPlayerWidth / 2);
			pos.x += frameVelocity;

			if (pos.x > fMovementBorder)
			{
				pos.x = fMovementBorder;
			}

			if (this->m_bRotateRight)
			{
				float fNewAngle = this->m_fAngleY - fRotation;

				// default rotation speed is too much
				// player will rotate over it's max rotation
				// need to rotate less than default
				if (fNewAngle < -this->m_fMaxRotation)
				{
					float fAngleIncrease = -this->m_fMaxRotation - this->m_fAngleY;
					// update angle
					this->m_fAngleY += fAngleIncrease;
				}
				// player rotates in default speed (fRotation)
				else
				{
					// update angle
					this->m_fAngleY += -fRotation;
				}
			}
		}
	}
	else
	{
		this->m_bRotateStraight = true;
	}

	// update player position
	this->m_pObject->SetPosition(pos);

	// straighten player
	if (this->m_bRotateStraight)
	{
		// player is not rotated to straight position
		if (this->m_fAngleY != 0.0f)
		{
			// sideways direction changed in the middle of straightening
			// start to turn-rotate in the correct direction
			if ((this->m_eMove != this->m_eMoveOld) &&
				(this->m_eMove != eMOVE_STAY) &&
				(this->m_eMove != eMOVE_UP) &&
				(this->m_eMove != eMOVE_DOWN))
			{
				this->m_bRotateStraight = false;

				if (this->m_eMove == eMOVE_LEFT)
				{
					this->m_bRotateLeft = true;
					this->m_bRotateRight = false;
				}
				else if (this->m_eMove == eMOVE_RIGHT)
				{
					this->m_bRotateLeft = false;
					this->m_bRotateRight = true;
				}
			}
			// straighten player
			else
			{
				// straighten to left side
				if (this->m_fAngleY < 0.0f)
				{
					// default straightening speed is too much
					// player will rotate over it's straight position
					// need to rotate less than default
					if ((this->m_fAngleY + fRotation) > 0.0f)
					{
						// fAngle IS negative, so we get a positive angle
						// straightens to left side
						this->m_fAngleY += -this->m_fAngleY;
					}
					// player straightens in default speed (fRotation)
					else
					{
						// update angle
						this->m_fAngleY += fRotation;
					}
				}
				// straighten to right side
				else if (this->m_fAngleY > 0.0f)
				{
					// default straightening speed is too much
					// player will rotate over it's straight position
					// need to rotate less than default
					if ((this->m_fAngleY - fRotation) < 0.0f)
					{
						// fAngle IS positive, so we get a negative angle
						// straightens to right side
						this->m_fAngleY += -this->m_fAngleY;
					}
					// player straightens in default speed (fRotation)
					else
					{
						// update angle
						this->m_fAngleY += -fRotation;
					}
				}
				// straighten player
				this->m_pObject->SetRotateY(this->m_fAngleY);
			}
		}
		// player is rotated to straight position
		else if (this->m_fAngleY == 0.0f)
		{
			// make sure that player is in straight position
			D3DXVECTOR3 vPos = this->m_pObject->GetPosition();
			this->m_pObject->SetDefaultMatrix();
			this->m_pObject->SetPosition(vPos);

			this->m_bRotateStraight = false;
			this->m_bIsStraight = true;

			// start rotating to left or right 
			// if moving in that direction
			if (this->m_eMove == eMOVE_LEFT)
			{
				this->m_bRotateLeft = true;
				this->m_bRotateRight = false;
			}
			else if (this->m_eMove == eMOVE_RIGHT)
			{
				this->m_bRotateRight = true;
				this->m_bRotateLeft = false;
			}
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}

	// rotate player left
	if (this->m_bRotateLeft)
	{
		// not reached max rotation angle
		if (this->m_fAngleY < this->m_fMaxRotation)
		{
			// check if left/right movement has changed
			if (this->RotateToStraight())
			{
				this->m_bRotateLeft = false;
				// start rotating player to straight position
				this->m_bRotateStraight = true;
				// backup the info of current movement
				this->m_eMoveOld = this->m_eMove;
			}
			else
			{
				if (this->m_bIsStraight)
				{
					this->m_bIsStraight = false;
				}
				// rotate player left
				this->m_pObject->SetRotateY(this->m_fAngleY);
			}
		}
		// reached max rotation angle
		else if (this->m_fAngleY == this->m_fMaxRotation)
		{
			this->m_bRotateLeft = false;
			// start player straightening checking
			this->m_bCheckStraightening = true;
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}
	// rotate player right
	else if (this->m_bRotateRight)
	{
		// not reached max rotation angle
		if (this->m_fAngleY > -this->m_fMaxRotation)
		{
			// check if left/right movement has changed
			if (this->RotateToStraight())
			{
				this->m_bRotateRight = false;
				// start rotating player to straight position
				this->m_bRotateStraight = true;
				// backup the info of current movement
				this->m_eMoveOld = this->m_eMove;
			}
			else
			{
				if (this->m_bIsStraight)
				{
					this->m_bIsStraight = false;
				}
				// rotate player right
				this->m_pObject->SetRotateY(this->m_fAngleY);
			}
		}
		// reached max rotation angle
		else if (this->m_fAngleY == -this->m_fMaxRotation)
		{
			this->m_bRotateRight = false;
			// start player straightening checking
			this->m_bCheckStraightening = true;
			// backup the info of current movement
			this->m_eMoveOld = this->m_eMove;
		}
	}

	// player has reached max rotation angle  
	// and is not yet started to rotate straight
	if (this->m_bCheckStraightening)
	{
		if (this->RotateToStraight())
		{
			// end player straightening checking
			this->m_bCheckStraightening = false;
			// start rotating player to straight position
			this->m_bRotateStraight = true;
		}
	}

	this->CheckControlsLast(pPlayer);
	this->CorrectZAxisPosition();

	// backup the info of current movement
	if (this->m_eMoveOld != this->m_eMove)
	{
		this->m_eMoveOld = this->m_eMove;
	}
}

void CPlayerController::CheckControlsFirst()
{
	bool bInputUp = false;
	bool bInputDown = false;
	bool bInputLeft = false;
	bool bInputRight = false;
	bool bCheckJoystick = false;
	bool bCheckKeyboard = true;

	// check straightening first
	if (this->RotateToStraight())
	{
		this->m_bRotateStraight = true;
	}

	if (this->m_bExecuteInputs)
	{
		if (SUCCEEDED(this->m_pJoystick->Update()))
		{
			bCheckJoystick = true;
		}

		if (bCheckJoystick)
		{
			int iJoystickX = this->m_pJoystick->GetState().lX;
			int iJoystickY = this->m_pJoystick->GetState().lY;

			// read forward movement control
			if (iJoystickY < 0)
			{
				bInputUp = true;
			}

			// read backward movement control
			if (iJoystickY > 0)
			{
				bInputDown = true;
			}

			// read left movement control
			if (iJoystickX < 0)
			{
				bInputLeft = true;
			}

			// read right movement control
			if (iJoystickX > 0)
			{
				bInputRight = true;
			}

			// joystick has priority over keyboard
			if (bInputUp || bInputDown || bInputLeft || bInputRight)
			{
				bCheckKeyboard = false;
			}
		}

		if (bCheckKeyboard)
		{
			// read forward movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyUp()))
			{
				bInputUp = true;
			}

			// read backward movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyDown()))
			{
				bInputDown = true;
			}

			// read left movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyLeft()))
			{
				bInputLeft = true;
			}

			// read right movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyRight()))
			{
				bInputRight = true;
			}
		}

		if (bInputUp)
		{
			if (!this->m_bMoveDown)
			{
				this->m_bMoveUp = true;
				this->m_eMove = eMOVE_UP;
			}
			// left and right movement keys are not pressed
			if (!bInputLeft && !bInputRight)
			{
				this->m_bRotateStraight = true;
				this->m_bRotateLeft = false;
				this->m_bRotateRight = false;
				this->m_bMoveLeft = false;
				this->m_bMoveRight = false;
			}
			else
			{
				// left movement key is not pressed
				if (!bInputLeft)
				{
					this->m_bRotateLeft = false;
					this->m_bMoveLeft = false;
				}
				// right movement key is not pressed
				if (!bInputRight)
				{
					this->m_bRotateRight = false;
					this->m_bMoveRight = false;
				}
			}
		}

		if (bInputDown)
		{
			if (!this->m_bMoveUp)
			{
				this->m_bMoveDown = true;
				this->m_eMove = eMOVE_DOWN;
			}
			// left and right movement keys are not pressed
			if (!bInputLeft && !bInputRight)
			{
				this->m_bRotateStraight = true;
				this->m_bRotateLeft = false;
				this->m_bRotateRight = false;
				this->m_bMoveLeft = false;
				this->m_bMoveRight = false;
			}
			else
			{
				// left movement key is not pressed
				if (!bInputLeft)
				{
					this->m_bRotateLeft = false;
					this->m_bMoveLeft = false;
				}
				// right movement key is not pressed
				if (!bInputRight)
				{
					this->m_bRotateRight = false;
					this->m_bMoveRight = false;
				}
			}
		}

		if (bInputLeft)
		{
			if (!this->m_bMoveRight)
			{
				if (this->m_bRotateRight)
				{
					this->m_bRotateRight = false;
				}

				this->m_bMoveLeft = true;
				this->m_eMove = eMOVE_LEFT;

				// player is not rotating to straight position
				if (!this->m_bRotateStraight)
				{
					if (!this->m_bRotateLeft)
					{
						this->m_bRotateLeft = true;
					}
				}
			}
		}

		if (bInputRight)
		{
			if (!this->m_bMoveLeft)
			{
				if (this->m_bRotateLeft)
				{
					this->m_bRotateLeft = false;
				}

				this->m_bMoveRight = true;
				this->m_eMove = eMOVE_RIGHT;

				// player is not rotating to straight position
				if (!this->m_bRotateStraight)
				{
					if (!this->m_bRotateRight)
					{
						this->m_bRotateRight = true;
					}
				}
			}
		}

		if (this->m_bMoveUp || this->m_bMoveDown ||
			this->m_bMoveLeft || this->m_bMoveRight)
		{
			this->m_bMovement = true;
		}
		else if (!this->m_bMoveUp && !this->m_bMoveDown &&
			!this->m_bMoveLeft && !this->m_bMoveRight)
		{
			this->m_bMovement = false;
			this->m_eMove = eMOVE_STAY;
		}
	}
	else
	{
		this->m_bMoveUp = false;
		this->m_bMoveDown = false;
		this->m_bMoveLeft = false;
		this->m_bMoveRight = false;
		this->m_bMovement = false;
		this->m_eMove = eMOVE_STAY;
	}
}

void CPlayerController::CheckControlsLast(CPlayer* pPlayer)
{
	bool bInputUp = false;
	bool bInputDown = false;
	bool bInputLeft = false;
	bool bInputRight = false;
	bool bCheckJoystick = false;
	bool bCheckKeyboard = true;

	if (this->m_bExecuteInputs)
	{
		if (SUCCEEDED(this->m_pJoystick->Update()))
		{
			bCheckJoystick = true;
		}
		if (bCheckJoystick)
		{
			int iJoystickX = this->m_pJoystick->GetState().lX;
			int iJoystickY = this->m_pJoystick->GetState().lY;

			// read forward movement control
			if (iJoystickY < 0)
			{
				bInputUp = true;
			}
			// read backward movement control
			if (iJoystickY > 0)
			{
				bInputDown = true;
			}
			// read left movement control
			if (iJoystickX < 0)
			{
				bInputLeft = true;
			}
			// read right movement control
			if (iJoystickX > 0)
			{
				bInputRight = true;
			}
			// joystick has priority over keyboard
			if (bInputUp || bInputDown || bInputLeft || bInputRight)
			{
				bCheckKeyboard = false;
			}
		}
		if (bCheckKeyboard)
		{
			// read forward movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyUp()))
			{
				bInputUp = true;
			}
			// read backward movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyDown()))
			{
				bInputDown = true;
			}
			// read left movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyLeft()))
			{
				bInputLeft = true;
			}
			// read right movement control
			if (::GetAsyncKeyState(this->m_pTheApp->GetConfig().GetVkeyRight()))
			{
				bInputRight = true;
			}
		}
		if (!bInputUp)
		{
			this->m_bMoveUp = false;

			if (pPlayer->IsVelocityControl())
			{
				pPlayer->DisableBoostIncrease();
				pPlayer->SetBoostSoundCheck();
			}
		}
		if (!bInputDown)
		{
			this->m_bMoveDown = false;
		}
		if (!bInputLeft)
		{
			this->m_bMoveLeft = false;
		}
		if (!bInputRight)
		{
			this->m_bMoveRight = false;
		}
	}
	else
	{
		this->m_bMoveUp = false;
		this->m_bMoveDown = false;
		this->m_bMoveLeft = false;
		this->m_bMoveRight = false;
		this->m_bMovement = false;
		this->m_eMove = eMOVE_STAY;
	}
}

bool CPlayerController::RotateToStraight()
{
	// player was moving leftward
	if (this->m_eMoveOld == eMOVE_LEFT)
	{
		// player starts to move elsewhere than leftward
		if ((this->m_eMove == eMOVE_STAY) ||
			(this->m_eMove == eMOVE_UP) ||
			(this->m_eMove == eMOVE_DOWN) ||
			(this->m_eMove == eMOVE_RIGHT))
		{
			// backup the info of current movement
			// for straightening rotation to activate correctly
			this->m_eMoveOld = this->m_eMove;
			return true;
		}
	}
	// player was moving rightward
	if (this->m_eMoveOld == eMOVE_RIGHT)
	{
		// player starts to move elsewhere than rightward
		if ((this->m_eMove == eMOVE_STAY) ||
			(this->m_eMove == eMOVE_UP) ||
			(this->m_eMove == eMOVE_DOWN) ||
			(this->m_eMove == eMOVE_LEFT))
		{
			// backup the info of current movement
			// for straightening rotation to activate correctly
			this->m_eMoveOld = this->m_eMove;
			return true;
		}
	}
	return false;
	{
	}
}

void CPlayerController::CorrectZAxisPosition()
{
	D3DXVECTOR3 pos;
	pos = this->m_pObject->GetPosition();

	// fix player z-axis position
	pos.z = 0.0f;

	this->m_pObject->SetPosition(pos);
}
