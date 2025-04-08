/**
 * Abstract application state class.
 * This class is a base for all application
 * states. It provides access to application
 * object and basic methods for updating application.
 */

#pragma once

#include "TheApp.h"
#include "Sprite.h"
#include "Lights.h"
#include "Fading.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

// application state update return values
// the 'Update' function of state returns
// one of these pre-defined values, and depending
// on these, changes the state of the application

#define STATE_RUNNING				0
#define STATE_INTRO					1
#define STATE_MENUS					2
#define STATE_GAME					3
#define STATE_HIGHSCORE				4
#define STATE_EXIT_APP				999

#define ISTATE_RESOURCES_INTRO		1

#define ISTATE_LOADING_BAR_MAX		327

//#define MENUS_PLANET
//#define MENUS_FOG

class IState
{
public:

	IState(void);
	virtual ~IState(void);

	/**
	 * Create
	 * Create state.
	 * @param pApp pointer to initialised application
	 * @return S_OK if successfull
	 */
	virtual HRESULT Create(	CTheApp* pApp,
							DWORD dwState);

	/**
	 * Initialise state. Overriden states should
	 * implement this function to initialise state
	 * resources.
	 * @return S_OK if successfull
	 */
	virtual HRESULT InitState(DWORD dwState) = 0;

	/**
	 * Release
	 * release state resources.
	 */
	virtual void Release();

	/**
	 * Update
	 * Virtual application state update
	 * @param fFrametime application frame time
	 * @return state update value
	 */
	virtual DWORD Update(float fFrametime);


	/**
	 * Render
	 * pure virtual render (draw) function
	 */
	virtual void Render() = 0;


	/**
	 * OnKeyDown
	 * virtual keyboard handler for the application states
	 * @param dwKey keycode of the pressed key
	 */
	virtual void OnKeyDown(DWORD dwKey) {}

	/**
	 * OnKeyUp
	 * virtual keyboard handler for the application states
	 * @param dwKey keycode of the pressed key
	 */
	virtual void OnKeyUp(DWORD dwKey) {}

	virtual inline void SetState(DWORD dwNextState) {}

	virtual void UpdateLoadingBar(int iStepsForward);

#ifdef SHADOWS
	virtual CShadowVolume* GetShadowVolumes() = 0;
#endif

	/**
	 * GetApp
	 * @return pointer to application object
	 */
	inline CTheApp* GetApp() { return m_pApp; }

	/**
	 * GetFading
	 * @return pointer to fading
	 */
	inline CFading* GetFading() { return &m_Fading; }

	void BuildProjection();
	void DisplayLoadingScreen();

	inline CLights* GetLights() { return this->m_pLights; }

	inline void SetNewState(bool bNewState) { this->m_bNewState = bNewState; }
	inline bool IsNewState() { return this->m_bNewState; }

	inline bool IsStateLoaded() { return this->m_bStateLoaded; }
	inline void SetStateLoaded(bool bLoaded) { this->m_bStateLoaded = bLoaded; }

	inline void SetLoadWaitTimer()
	{
		this->m_fLoadWaitTimer = LOAD_STEP_WAIT_TIME;
		this->m_bStartLoadWaitTimer = true;
	}

	inline bool IsLoadWaitTimer() { return (this->m_fLoadWaitTimer > 0); }

	inline bool GetMeshLoaded() { return this->m_bMeshLoaded; }
	inline bool GetSpriteLoaded() { return this->m_bSpriteLoaded; }
	inline void SetMeshLoaded(bool isLoaded) { this->m_bMeshLoaded = isLoaded; }
	inline void SetSpriteLoaded(bool isLoaded) { this->m_bSpriteLoaded = isLoaded; }

	inline void SetStepsMax(int steps) { this->m_iStepsMax = steps; }

	inline int GetMeshSteps() { return this->m_iMeshSteps; }
	inline int GetMeshStepsMax() { return this->m_iMeshStepsMax; }
	inline int GetSpriteSteps() { return this->m_iSpriteSteps; }
	inline int GetSpriteStepsMax() { return this->m_iSpriteStepsMax; }

	inline void IncreaseMeshSteps(int increase) { this->m_iMeshSteps += increase; }
	inline void IncreaseSpriteSteps(int increase) { this->m_iSpriteSteps += increase; }

	void InitLoadingScreenValues(int stepsMax);

	inline float GetScreenWidth() { return m_fScreenWidth; }
	inline float GetScreenHeight() { return m_fScreenHeight; }
	inline float GetScreenPixelWidth() { return m_fScreenPixelWidth; }
	inline float GetScreenPixelHeight() { return m_fScreenPixelHeight; }

#ifdef SHADOWS
	inline int GetShadowCount() { return this->m_iShadowCount; }
	inline void SetShadowCount(int iCount) { this->m_iShadowCount = iCount; }
#endif

protected:

	// sprite functions
	void LoadSpritesLoadingScreen(DWORD dwState);

	static CFading		m_Fading;
	CTheApp*			m_pApp;

	// lights
	CLights*			m_pLights;
	// loading screen
	CSprite*			m_pSpriteLoadingScreen;
	// loading bar
	CSprite*			m_pSpriteLoadingBar;

	bool				m_bMeshLoaded;
	bool				m_bSpriteLoaded;
	bool				m_StateInitialized;
	bool				m_bStateLoaded;

	int					m_iMeshSteps;
	int					m_iSpriteSteps;

	int					m_iStepsMax;
	int					m_iMeshStepsMax;
	int					m_iSpriteStepsMax;

	float				m_fScreenWidth;
	float				m_fScreenHeight;
	float				m_fScreenPixelWidth;
	float				m_fScreenPixelHeight;

	int					m_iVolumeSoundEffect;

#ifdef SHADOWS
	int					m_iShadowCount;
#endif

private:

	void DisplayLoadingBar();
	void InitLoadingBarMultiplier(DWORD dwState);
	void InitVolumeSoundEffect();

	float				m_fDepth;

	int					m_iLoadingBarIndex;
	float				m_fLoadingBarIndex;
	float				m_fLoadingBarMultiplier;

	bool				m_bNewState;

	DWORD				m_iState;

	const float			LOAD_STEP_WAIT_TIME = 0.15f;

	bool				m_bStartLoadWaitTimer;
	float				m_fLoadWaitTimer;
};