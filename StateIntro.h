/**
 * This class implements
 * game application "intro" state.
 */

#pragma once

#include "IState.h"
#include "Sprite.h"

class CStateIntro : public IState
{
public:
	CStateIntro(void);
	virtual ~CStateIntro(void);

	virtual HRESULT Create(	CTheApp* pApp,
							DWORD dwState);

	virtual HRESULT InitState(DWORD dwState);

	virtual void Release();

	/**
	 * Update
	 * update intro state
	 * @param fFrametime application frame time
	 * @return state update value
	 */
	virtual DWORD Update(float fFrametime);


	/**
	 * Render
	 * render the intro
	 */
	virtual void Render();


	/**
	 * OnKeyDown
	 * handle intro keypresses
	 * @param dwKey keycode of the pressed key
	 */
	virtual void OnKeyDown(DWORD dwKey);

private:
	CSprite*				m_pSpriteBackground;
	DWORD					m_dwNextState;
	float					m_fIntroTimer;
};