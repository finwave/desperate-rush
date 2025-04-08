/**
 * This class implements
 * game application "game" state.
 */

#pragma once

#include "IState.h"
#include "TheGame.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

class CStateGame : public IState
{
public:

	CStateGame(void);
	virtual ~CStateGame(void);

	virtual HRESULT Create(	CTheApp* pApp,
							DWORD dwState);

	virtual HRESULT InitState(DWORD dwState);

	/**
	 * Release
	 * release game resources.
	 */
	virtual void Release();

	/**
	 * Update
	 * update game
	 * @param fFrametime application frame time
	 * @return state update value
	 */
	virtual DWORD Update(float fFrametime);


	/**
	 * Render
	 * render game
	 */
	virtual void Render();

	inline void SetState(DWORD dwNextState) { this->m_dwNextState = dwNextState; }

#ifdef SHADOWS
	virtual CShadowVolume* GetShadowVolumes();
#endif

private:

	DWORD						m_dwNextState;
	CTheGame*					m_pTheGame;
};