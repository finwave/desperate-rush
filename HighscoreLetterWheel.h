#pragma once

#include "MenuObject.h"

class CHighscoreLetterWheel :public CMenuObject
{
public:

	enum eLETTER_WHEEL
	{
		eLETTER_WHEEL_A,
		eLETTER_WHEEL_B,
		eLETTER_WHEEL_C,
		eLETTER_WHEEL_D,
		eLETTER_WHEEL_E,
		eLETTER_WHEEL_F,
		eLETTER_WHEEL_G,
		eLETTER_WHEEL_H,
		eLETTER_WHEEL_I,
		eLETTER_WHEEL_J,
		eLETTER_WHEEL_K,
		eLETTER_WHEEL_L,
		eLETTER_WHEEL_M,
		eLETTER_WHEEL_N,
		eLETTER_WHEEL_O,
		eLETTER_WHEEL_P,
		eLETTER_WHEEL_Q,
		eLETTER_WHEEL_R,
		eLETTER_WHEEL_S,
		eLETTER_WHEEL_T,
		eLETTER_WHEEL_U,
		eLETTER_WHEEL_V,
		eLETTER_WHEEL_W,
		eLETTER_WHEEL_X,
		eLETTER_WHEEL_Y,
		eLETTER_WHEEL_Z,
		eLETTER_WHEEL_DEL,
		eLETTER_WHEEL_END
	};

	CHighscoreLetterWheel();
	~CHighscoreLetterWheel();

	virtual void Init();
	void RenderInputAction(float fFrametime);

	void SetLetterWheelRotationY(float angleY);
	void SetLetterWheelAdditionScaleValue(float value);

	bool RotateLetterWheel(float fFrametime, bool bRotateToEnd);
	void ChangeSelection();
	void SelectLetter();

	inline float GetLetterWheelAdditionScaleValue() { return this->m_fLetterWheelAdditionScaleValue; }

	inline std::string GetPlayerName() { return this->m_strPlayerName; }
	inline void SetPlayerName(std::string name) { this->m_strPlayerName = name; }

	inline eLETTER_WHEEL GetLetterWheel() { return m_eLetterWheel; }

	inline bool IsRotateWheelUp() { return this->m_bRotateWheelUp; }
	inline void SetRotateWheelUp(bool value) { this->m_bRotateWheelUp = value; }

	inline bool IsRotateWheelDown() { return this->m_bRotateWheelDown; }
	inline void SetRotateWheelDown(bool value) { this->m_bRotateWheelDown = value; }

	inline bool IsSelectLetter() { return this->m_bSelectLetter; }
	inline void SetSelectLetter(bool value) { this->m_bSelectLetter = value; }

	inline bool IsNameFull() { return this->m_bNameFull; }
	inline void SetNameFull(bool value) { this->m_bNameFull = value; }

protected:

	virtual void Scale();
	virtual D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material);

	float RotationAngleNormal();
	float RotationAngleFull();

private:

	const float LETTER_ROTATE_A_B = 0.245f;
	const float LETTER_ROTATE_B_C = 0.27f;
	const float LETTER_ROTATE_C_D = 0.28f;
	const float LETTER_ROTATE_D_E = 0.28f;
	const float LETTER_ROTATE_E_F = 0.28f;
	const float LETTER_ROTATE_F_G = 0.28f;
	const float LETTER_ROTATE_G_H = 0.28f;
	const float LETTER_ROTATE_H_I = 0.27f;
	const float LETTER_ROTATE_I_J = 0.26f;
	const float LETTER_ROTATE_J_K = 0.255f;
	const float LETTER_ROTATE_K_L = 0.255f;
	const float LETTER_ROTATE_L_M = 0.25f;
	const float LETTER_ROTATE_M_N = 0.243f;
	const float LETTER_ROTATE_N_O = 0.25f;
	const float LETTER_ROTATE_O_P = 0.25f;
	const float LETTER_ROTATE_P_Q = 0.2675f;
	const float LETTER_ROTATE_Q_R = 0.27f;
	const float LETTER_ROTATE_R_S = 0.275f;
	const float LETTER_ROTATE_S_T = 0.27f;
	const float LETTER_ROTATE_T_U = 0.285f;
	const float LETTER_ROTATE_U_V = 0.285f;
	const float LETTER_ROTATE_V_W = 0.275f;
	const float LETTER_ROTATE_W_X = 0.27f;
	const float LETTER_ROTATE_X_Y = 0.25f;
	const float LETTER_ROTATE_Y_Z = 0.27f;
	const float LETTER_ROTATE_Z_DEL = 0.2425f;
	const float LETTER_ROTATE_DEL_END = 0.22f;
	const float LETTER_ROTATE_END_A = 0.2635f;

	eLETTER_WHEEL m_eLetterWheel;
	std::string m_strPlayerName;

	float m_fLetterWheelRotationY;
	float m_fLetterWheelAdditionScaleValue;

	bool m_bRotateWheelUp;
	bool m_bRotateWheelDown;
	bool m_bSelectLetter;
	bool m_bNameFull;
};

