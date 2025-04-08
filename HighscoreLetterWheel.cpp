#include "HighscoreLetterWheel.h"

CHighscoreLetterWheel::CHighscoreLetterWheel()
{
	this->m_eLetterWheel = eLETTER_WHEEL_A;
	this->m_strPlayerName = "";

	this->m_fLetterWheelRotationY = 0.0f;
	this->m_fLetterWheelAdditionScaleValue = 0.0f;

	this->m_bRotateWheelUp = false;
	this->m_bRotateWheelDown = false;
	this->m_bSelectLetter = false;
	this->m_bNameFull = false;
}

CHighscoreLetterWheel::~CHighscoreLetterWheel()
{
}

void CHighscoreLetterWheel::Init()
{
	this->Scale();
	this->InitPosition();
}

void CHighscoreLetterWheel::RenderInputAction(float fFrametime)
{
	// rotates letter wheel upward or downward 
	if (this->m_bRotateWheelUp || this->m_bRotateWheelDown)
	{
		// letter wheel rotation has ended
		if (!RotateLetterWheel(fFrametime, false))
		{
			ChangeSelection();

			if (this->m_bRotateWheelUp)
			{
				this->m_bRotateWheelUp = false;
			}

			else if (this->m_bRotateWheelDown)
			{
				this->m_bRotateWheelDown = false;
			}

		}
	}
	// instantly rotates letter wheel to the end
	else if (this->m_bNameFull)
	{
		if ((this->m_eLetterWheel != eLETTER_WHEEL_DEL) &&
			(this->m_eLetterWheel != eLETTER_WHEEL_END))
		{
			// letter wheel rotation has ended
			if (!RotateLetterWheel(fFrametime, true))
			{
				this->m_eLetterWheel = eLETTER_WHEEL_END;
			}
		}
	}
	// add the currently selected letter to player's name
	else if (this->m_bSelectLetter)
	{
		SelectLetter();
		this->m_bSelectLetter = false;
	}
}

void CHighscoreLetterWheel::Scale()
{
	this->SetScaleX(0.45f);
	this->SetScaleY(0.45f);
	this->SetScaleZ(0.45f);
}

D3DMATERIAL9* CHighscoreLetterWheel::InitMaterial(D3DMATERIAL9* material)
{
	// diffuse reflection

	material->Diffuse.r = 1.0f;
	material->Diffuse.g = 1.0f;
	material->Diffuse.b = 1.0f;
	material->Diffuse.a = 1.0f;

	return material;
}

void CHighscoreLetterWheel::SetLetterWheelRotationY(float angleY)
{
	this->m_fLetterWheelRotationY = D3DX_PI / 6.5f;
	this->SetRotateY(-this->m_fLetterWheelRotationY);
}

void CHighscoreLetterWheel::SetLetterWheelAdditionScaleValue(float value)
{
	this->m_fLetterWheelAdditionScaleValue = value;
	float scaleValue = this->m_fLetterWheelAdditionScaleValue * GetScaleX();

	SetScaleX(scaleValue);
	SetScaleY(scaleValue);
	SetScaleZ(scaleValue);
}

bool CHighscoreLetterWheel::RotateLetterWheel(float fFrametime, bool bRotateToEnd)
{
	const float fFrameSpeedLetter = 0.02f;
	const float fFrameSpeedToEnd = 0.075f;

	static float fAngleFrameNormal = fFrameSpeedLetter;
	static float fAngleFrameFull = fFrameSpeedToEnd;
	static float fAngleMove = 0.0f;

	float fAngleMax = 0.0f;

	// get object's position to temp vector
	D3DXVECTOR3 pos = GetPosition();
	// get object's local matrix to temp matrix
	D3DXMATRIX& mObject = GetLocalMatrix();

	// rotation matrix
	D3DXMATRIX mRotation;
	D3DXMatrixIdentity(&mRotation);

	// rotate back to original y-axel orientation
	D3DXMatrixRotationY(&mRotation, this->m_fLetterWheelRotationY);
	D3DXMatrixMultiply(&mObject, &mObject, &mRotation);

	bool bRotate = true;

	// player name is full, instantly rotate to end
	if (bRotateToEnd)
	{
		fAngleMax = this->m_fLetterWheelAdditionScaleValue * this->RotationAngleFull();

		if (this->m_eLetterWheel < 13)
		{
			D3DXMatrixRotationX(&mRotation, -fAngleFrameFull);
		}
		else
		{
			D3DXMatrixRotationX(&mRotation, fAngleFrameFull);
		}

		fAngleMove += fAngleFrameFull;

		if (fAngleMove == fAngleMax)
		{
			bRotate = false;
			fAngleMove = 0.0f;
			fAngleFrameFull = fFrameSpeedToEnd;
		}
		else if ((fAngleMove + fAngleFrameFull) > fAngleMax)
		{
			fAngleFrameFull = fAngleMax - fAngleMove;
		}

		// rotate along x-axel
		D3DXMatrixMultiply(&mObject, &mObject, &mRotation);
	}
	// player name is not full, normal rotation
	else if (this->m_bRotateWheelUp || this->m_bRotateWheelDown)
	{
		fAngleMax = this->m_fLetterWheelAdditionScaleValue * this->RotationAngleNormal();

		// rotates letter wheel downwards so that the letter 
		// above the current one will be selected
		if (this->m_bRotateWheelDown)
		{
			D3DXMatrixRotationX(&mRotation, -fAngleFrameNormal);
		}
		// rotates letter wheel upwards so that the letter 
		// below the current one will be selected
		else if (this->m_bRotateWheelUp)
		{
			D3DXMatrixRotationX(&mRotation, fAngleFrameNormal);
		}

		fAngleMove += fAngleFrameNormal;

		if (fAngleMove == fAngleMax)
		{
			bRotate = false;
			fAngleMove = 0.0f;
			fAngleFrameNormal = fFrameSpeedLetter;
		}
		else if ((fAngleMove + fAngleFrameNormal) > fAngleMax)
		{
			fAngleFrameNormal = fAngleMax - fAngleMove;
		}

		// rotate along x-axel
		D3DXMatrixMultiply(&mObject, &mObject, &mRotation);
	}

	// rotate back to correct y-axel orientation
	D3DXMatrixRotationY(&mRotation, -this->m_fLetterWheelRotationY);
	D3DXMatrixMultiply(&mObject, &mObject, &mRotation);

	// set position
	SetPosition(pos);

	return bRotate;
}

float CHighscoreLetterWheel::RotationAngleNormal()
{
	float fRotationAngle = 0.0f;

	switch (this->m_eLetterWheel)
	{
	case eLETTER_WHEEL_A:

		if (this->m_bRotateWheelDown)
		{
			if (this->m_strPlayerName == "")
			{
				fRotationAngle = LETTER_ROTATE_Z_DEL + LETTER_ROTATE_DEL_END + LETTER_ROTATE_END_A;
			}
			else
			{
				fRotationAngle = LETTER_ROTATE_END_A;
			}
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_A_B;
		}

		break;

	case eLETTER_WHEEL_B:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_A_B;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_B_C;
		}

		break;

	case eLETTER_WHEEL_C:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_B_C;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_C_D;
		}

		break;

	case eLETTER_WHEEL_D:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_C_D;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_D_E;
		}

		break;

	case eLETTER_WHEEL_E:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_D_E;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_E_F;
		}

		break;

	case eLETTER_WHEEL_F:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_E_F;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_F_G;
		}

		break;

	case eLETTER_WHEEL_G:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_F_G;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_G_H;
		}

		break;

	case eLETTER_WHEEL_H:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_G_H;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_H_I;
		}

		break;

	case eLETTER_WHEEL_I:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_H_I;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_I_J;
		}

		break;

	case eLETTER_WHEEL_J:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_I_J;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_J_K;
		}

		break;

	case eLETTER_WHEEL_K:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_J_K;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_K_L;
		}

		break;

	case eLETTER_WHEEL_L:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_K_L;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_L_M;
		}

		break;

	case eLETTER_WHEEL_M:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_L_M;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_M_N;
		}

		break;

	case eLETTER_WHEEL_N:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_M_N;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_N_O;
		}

		break;

	case eLETTER_WHEEL_O:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_N_O;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_O_P;
		}

		break;

	case eLETTER_WHEEL_P:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_O_P;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_P_Q;
		}

		break;

	case eLETTER_WHEEL_Q:

		if (this->LETTER_ROTATE_P_Q)
		{
			fRotationAngle = 0.2675f;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_Q_R;
		}

		break;

	case eLETTER_WHEEL_R:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_Q_R;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_R_S;
		}

		break;

	case eLETTER_WHEEL_S:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_R_S;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_S_T;
		}

		break;

	case eLETTER_WHEEL_T:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_S_T;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_T_U;
		}

		break;

	case eLETTER_WHEEL_U:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_T_U;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_U_V;
		}

		break;

	case eLETTER_WHEEL_V:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_U_V;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_V_W;
		}

		break;

	case eLETTER_WHEEL_W:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_V_W;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_W_X;
		}

		break;

	case eLETTER_WHEEL_X:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_W_X;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_X_Y;
		}

		break;

	case eLETTER_WHEEL_Y:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_X_Y;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_Y_Z;
		}

		break;

	case eLETTER_WHEEL_Z:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_Y_Z;
		}
		else if (this->m_bRotateWheelUp)
		{
			if (this->m_strPlayerName == "")
			{
				fRotationAngle = LETTER_ROTATE_Z_DEL + LETTER_ROTATE_DEL_END + LETTER_ROTATE_END_A;
			}
			else
			{
				fRotationAngle = LETTER_ROTATE_Z_DEL;
			}
		}

		break;

	case eLETTER_WHEEL_DEL:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_Z_DEL;
		}
		else if (this->m_bRotateWheelUp)
		{
			if (this->m_strPlayerName == "")
			{
				fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_END_A;
			}
			else
			{
				fRotationAngle = LETTER_ROTATE_DEL_END;
			}
		}

		break;

	case eLETTER_WHEEL_END:

		if (this->m_bRotateWheelDown)
		{
			fRotationAngle = LETTER_ROTATE_DEL_END;
		}
		else if (this->m_bRotateWheelUp)
		{
			fRotationAngle = LETTER_ROTATE_END_A;
		}

		break;
	}

	return fRotationAngle;
}

float CHighscoreLetterWheel::RotationAngleFull()
{
	float fRotationAngle = 0.0f;

	switch (this->m_eLetterWheel)
	{
	case eLETTER_WHEEL_A:
		fRotationAngle = LETTER_ROTATE_END_A;
		break;

	case eLETTER_WHEEL_B:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B;
		break;

	case eLETTER_WHEEL_C:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C;
		break;

	case eLETTER_WHEEL_D:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D;
		break;

	case eLETTER_WHEEL_E:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E;
		break;

	case eLETTER_WHEEL_F:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F;
		break;

	case eLETTER_WHEEL_G:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G;
		break;

	case eLETTER_WHEEL_H:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H;
		break;

	case eLETTER_WHEEL_I:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H + LETTER_ROTATE_H_I;
		break;

	case eLETTER_WHEEL_J:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H + LETTER_ROTATE_H_I + LETTER_ROTATE_I_J;
		break;

	case eLETTER_WHEEL_K:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H + LETTER_ROTATE_H_I + LETTER_ROTATE_I_J + LETTER_ROTATE_J_K;
		break;

	case eLETTER_WHEEL_L:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H + LETTER_ROTATE_H_I + LETTER_ROTATE_I_J + LETTER_ROTATE_J_K +
			LETTER_ROTATE_K_L;
		break;

	case eLETTER_WHEEL_M:
		fRotationAngle = LETTER_ROTATE_END_A + LETTER_ROTATE_A_B + LETTER_ROTATE_B_C + LETTER_ROTATE_C_D + LETTER_ROTATE_D_E +
			LETTER_ROTATE_E_F + LETTER_ROTATE_F_G + LETTER_ROTATE_G_H + LETTER_ROTATE_H_I + LETTER_ROTATE_I_J + LETTER_ROTATE_J_K +
			LETTER_ROTATE_K_L + LETTER_ROTATE_L_M;
		break;

		// middle point

	case eLETTER_WHEEL_N:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T + LETTER_ROTATE_R_S + LETTER_ROTATE_Q_R +
			LETTER_ROTATE_P_Q + LETTER_ROTATE_O_P + LETTER_ROTATE_N_O;
		break;

	case eLETTER_WHEEL_O:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T + LETTER_ROTATE_R_S + LETTER_ROTATE_Q_R +
			LETTER_ROTATE_P_Q + LETTER_ROTATE_O_P;
		break;

	case eLETTER_WHEEL_P:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T + LETTER_ROTATE_R_S + LETTER_ROTATE_Q_R +
			LETTER_ROTATE_P_Q;
		break;

	case eLETTER_WHEEL_Q:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T + LETTER_ROTATE_R_S + LETTER_ROTATE_Q_R;
		break;

	case eLETTER_WHEEL_R:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T + LETTER_ROTATE_R_S;
		break;

	case eLETTER_WHEEL_S:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U + LETTER_ROTATE_S_T;
		break;

	case eLETTER_WHEEL_T:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V + LETTER_ROTATE_T_U;
		break;

	case eLETTER_WHEEL_U:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W + LETTER_ROTATE_U_V;
		break;

	case eLETTER_WHEEL_V:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X +
			LETTER_ROTATE_V_W;
		break;

	case eLETTER_WHEEL_W:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y + LETTER_ROTATE_W_X;
		break;

	case eLETTER_WHEEL_X:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z + LETTER_ROTATE_X_Y;
		break;

	case eLETTER_WHEEL_Y:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL + LETTER_ROTATE_Y_Z;
		break;

	case eLETTER_WHEEL_Z:
		fRotationAngle = LETTER_ROTATE_DEL_END + LETTER_ROTATE_Z_DEL;
		break;
	}

	return fRotationAngle;
}

void CHighscoreLetterWheel::ChangeSelection()
{
	switch (this->m_eLetterWheel)
	{
	case eLETTER_WHEEL_A:

		if (this->m_bRotateWheelDown)
		{
			if (this->m_strPlayerName == "")
			{
				this->m_eLetterWheel = eLETTER_WHEEL_Z;
			}
			else
			{
				this->m_eLetterWheel = eLETTER_WHEEL_END;
			}
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_B;
		}

		break;

	case eLETTER_WHEEL_B:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_A;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_C;
		}

		break;

	case eLETTER_WHEEL_C:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_B;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_D;
		}

		break;

	case eLETTER_WHEEL_D:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_C;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_E;
		}

		break;

	case eLETTER_WHEEL_E:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_D;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_F;
		}

		break;

	case eLETTER_WHEEL_F:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_E;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_G;
		}

		break;

	case eLETTER_WHEEL_G:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_F;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_H;
		}

		break;

	case eLETTER_WHEEL_H:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_G;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_I;
		}

		break;

	case eLETTER_WHEEL_I:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_H;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_J;
		}

		break;

	case eLETTER_WHEEL_J:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_I;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_K;
		}

		break;

	case eLETTER_WHEEL_K:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_J;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_L;
		}

		break;

	case eLETTER_WHEEL_L:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_K;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_M;
		}

		break;

	case eLETTER_WHEEL_M:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_L;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_N;
		}

		break;

	case eLETTER_WHEEL_N:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_M;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_O;
		}

		break;

	case eLETTER_WHEEL_O:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_N;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_P;
		}

		break;

	case eLETTER_WHEEL_P:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_O;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Q;
		}

		break;

	case eLETTER_WHEEL_Q:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_P;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_R;
		}

		break;

	case eLETTER_WHEEL_R:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Q;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_S;
		}

		break;

	case eLETTER_WHEEL_S:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_R;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_T;
		}

		break;

	case eLETTER_WHEEL_T:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_S;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_U;
		}

		break;

	case eLETTER_WHEEL_U:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_T;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_V;
		}

		break;

	case eLETTER_WHEEL_V:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_U;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_W;
		}

		break;

	case eLETTER_WHEEL_W:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_V;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_X;
		}

		break;

	case eLETTER_WHEEL_X:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_W;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Y;
		}

		break;

	case eLETTER_WHEEL_Y:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_X;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Z;
		}

		break;

	case eLETTER_WHEEL_Z:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Y;
		}
		else if (this->m_bRotateWheelUp)
		{
			if (this->m_strPlayerName == "")
			{
				this->m_eLetterWheel = eLETTER_WHEEL_A;
			}
			else
			{
				this->m_eLetterWheel = eLETTER_WHEEL_DEL;
			}
		}

		break;

	case eLETTER_WHEEL_DEL:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_Z;
		}
		else if (this->m_bRotateWheelUp)
		{
			if (this->m_strPlayerName == "")
			{
				this->m_eLetterWheel = eLETTER_WHEEL_A;
			}
			else
			{
				this->m_eLetterWheel = eLETTER_WHEEL_END;
			}
		}

		break;

	case eLETTER_WHEEL_END:

		if (this->m_bRotateWheelDown)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_DEL;
		}
		else if (this->m_bRotateWheelUp)
		{
			this->m_eLetterWheel = eLETTER_WHEEL_A;
		}

		break;
	}
}

void CHighscoreLetterWheel::SelectLetter()
{
	if (!this->m_bNameFull)
	{
		switch (this->m_eLetterWheel)
		{
		case eLETTER_WHEEL_A:
			this->m_strPlayerName += "A";
			break;
		case eLETTER_WHEEL_B:
			this->m_strPlayerName += "B";
			break;
		case eLETTER_WHEEL_C:
			this->m_strPlayerName += "C";
			break;
		case eLETTER_WHEEL_D:
			this->m_strPlayerName += "D";
			break;
		case eLETTER_WHEEL_E:
			this->m_strPlayerName += "E";
			break;
		case eLETTER_WHEEL_F:
			this->m_strPlayerName += "F";
			break;
		case eLETTER_WHEEL_G:
			this->m_strPlayerName += "G";
			break;
		case eLETTER_WHEEL_H:
			this->m_strPlayerName += "H";
			break;
		case eLETTER_WHEEL_I:
			this->m_strPlayerName += "I";
			break;
		case eLETTER_WHEEL_J:
			this->m_strPlayerName += "J";
			break;
		case eLETTER_WHEEL_K:
			this->m_strPlayerName += "K";
			break;
		case eLETTER_WHEEL_L:
			this->m_strPlayerName += "L";
			break;
		case eLETTER_WHEEL_M:
			this->m_strPlayerName += "M";
			break;
		case eLETTER_WHEEL_N:
			this->m_strPlayerName += "N";
			break;
		case eLETTER_WHEEL_O:
			this->m_strPlayerName += "O";
			break;
		case eLETTER_WHEEL_P:
			this->m_strPlayerName += "P";
			break;
		case eLETTER_WHEEL_Q:
			this->m_strPlayerName += "Q";
			break;
		case eLETTER_WHEEL_R:
			this->m_strPlayerName += "R";
			break;
		case eLETTER_WHEEL_S:
			this->m_strPlayerName += "S";
			break;
		case eLETTER_WHEEL_T:
			this->m_strPlayerName += "T";
			break;
		case eLETTER_WHEEL_U:
			this->m_strPlayerName += "U";
			break;
		case eLETTER_WHEEL_V:
			this->m_strPlayerName += "V";
			break;
		case eLETTER_WHEEL_W:
			this->m_strPlayerName += "W";
			break;
		case eLETTER_WHEEL_X:
			this->m_strPlayerName += "X";
			break;
		case eLETTER_WHEEL_Y:
			this->m_strPlayerName += "Y";
			break;
		case eLETTER_WHEEL_Z:
			this->m_strPlayerName += "Z";
			break;
		}

		if (this->m_strPlayerName.length() == 8)
		{
			this->m_bNameFull = true;
		}
	}
}