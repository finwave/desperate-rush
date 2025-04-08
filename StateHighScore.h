/**
 * This class implements
 * game application "highscore" state.
 */

#pragma once

// DEFINES

#define LOAD_MESH_HIGHSCORE_A				0
#define LOAD_MESH_HIGHSCORE_B				1
#define LOAD_MESH_HIGHSCORE_C				2
#define LOAD_MESH_HIGHSCORE_D				3
#define LOAD_MESH_HIGHSCORE_E				4
#define LOAD_MESH_HIGHSCORE_F				5
#define LOAD_MESH_HIGHSCORE_G				6
#define LOAD_MESH_HIGHSCORE_H				7
#define LOAD_MESH_HIGHSCORE_I				8
#define LOAD_MESH_HIGHSCORE_J				9
#define LOAD_MESH_HIGHSCORE_K				10
#define LOAD_MESH_HIGHSCORE_L				11
#define LOAD_MESH_HIGHSCORE_M				12
#define LOAD_MESH_HIGHSCORE_N				13
#define LOAD_MESH_HIGHSCORE_O				14
#define LOAD_MESH_HIGHSCORE_P				15
#define LOAD_MESH_HIGHSCORE_Q				16
#define LOAD_MESH_HIGHSCORE_R				17
#define LOAD_MESH_HIGHSCORE_S				18
#define LOAD_MESH_HIGHSCORE_T				19
#define LOAD_MESH_HIGHSCORE_U				20
#define LOAD_MESH_HIGHSCORE_V				21
#define LOAD_MESH_HIGHSCORE_W				22
#define LOAD_MESH_HIGHSCORE_X				23
#define LOAD_MESH_HIGHSCORE_Y				24
#define LOAD_MESH_HIGHSCORE_Z				25

#define LOAD_MESH_HIGHSCORE_0				26
#define LOAD_MESH_HIGHSCORE_1				27
#define LOAD_MESH_HIGHSCORE_2				28
#define LOAD_MESH_HIGHSCORE_3				29
#define LOAD_MESH_HIGHSCORE_4				30
#define LOAD_MESH_HIGHSCORE_5				31
#define LOAD_MESH_HIGHSCORE_6				32
#define LOAD_MESH_HIGHSCORE_7				33
#define LOAD_MESH_HIGHSCORE_8				34
#define LOAD_MESH_HIGHSCORE_9				35

#define LOAD_MESH_HIGHSCORE_WHEEL			36
#define LOAD_MESH_HIGHSCORE_PLAYER			37
#define	LOAD_MESH_HIGHSCORE_BULLET_PLAYER	38

#define LOAD_MESH_MAX_HIGHSCORE				39

#define MESH_SHADOW_COUNT_HIGHSCORE			2

#define LOAD_SPRITE_MAX_HIGHSCORE			5

#define DISPLAY_LETTER_COUNT_HIGHSCORE		26
#define DISPLAY_NUMBER_COUNT_HIGHSCORE		10

#include <cmath>
#include <string>

#include "IState.h"
#include "InputJoystick.h"
#include "XFileContainer.h"
#include "HighscoreLetterWheel.h"
#include "HighscorePlayerShip.h"
#include "Letter.h"
#include "Number.h"
#include "Sprite.h"
#include "SpriteScrolling.h"
#include "ObjectController.h"
#include "Weapon.h"
#include "WeaponPlayerHighscore.h"
#include "Queue.h"
#include "InputJoystick.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

class CStateHighScore : public IState
{
public:

	CStateHighScore(void);
	virtual ~CStateHighScore(void);

	virtual HRESULT Create(	CTheApp* pApp,
							DWORD dwState);

	virtual HRESULT InitState(DWORD dwState);

	virtual void Release();

	/**
	 * Update
	 * update highscore
	 * @param fFrametime application frame time
	 * @return state update value
	 */
	virtual DWORD Update(float fFrametime);


	/**
	 * Render
	 * render highscore
	 */
	virtual void Render();

#ifdef SHADOWS
	virtual CShadowVolume* GetShadowVolumes();
#endif

private:

	enum eSTATE
	{
		eSTATE_INPUT,
		eSTATE_LEAVE,
		eSTATE_EXIT
	};

	void CollisionBulletVsBorder();
	void ClearBullets();
	void UpdateBullets(float fFrametime);

	void RenderInputAction(float fFrametime);
	void RenderExit(float fFrametime);
	void RenderSelectBox();
	void RenderLetterWheel(float fFrametime);
	void RenderPlayerScore(float fFrametime);
	void RenderPlayerName(float fFrametime);
	void RenderShips(float fFrametime);
	void RenderPlayerAfterburn();
	void RenderBullets();

	void PlayerInput();
	void ShipActions(DWORD dwKey);
	void PlayerShoot();

	HRESULT LoadMeshes();
	void LoadSprites();

#ifdef SHADOWS
	HRESULT BuildShadowVolumes();
#endif

	bool PushButton();

	CResourceHighScore*		m_pResourceHighScores;
	CInputJoystick*			m_pJoystick;

	eSTATE					m_eState;
	DWORD					m_dwNextState;

#ifdef SHADOWS
	// shadows
	CShadowVolume*			m_pShadowVolumes;
#endif

	// 3d meshes

	CXFileContainer*		m_pXFile;

	CHighscorePlayerShip*	m_pPlayerShip;
	CHighscoreLetterWheel*	m_pLetterWheel;

	CObjectController*		m_pPlayerController;

	CLetter*				m_pLetters;
	CNumber*				m_pNumbers;

	CWeaponPlayerHighscore*	m_pWeaponPlayerHighscore;

	CQueue<CWeapon*>		m_pBullets;

	// 2d sprites

	CSpriteScrolling*		m_pSpriteStarsBack;
	CSpriteScrolling*		m_pSpriteStarsFront;

	CSprite*				m_pSpriteText;
	CSprite*				m_pSpriteSelectBox;
	CSprite*				m_pSpritePlayerAfterburn;

	float					m_fLetterWheelPositionFractionX;
	float					m_fLetterWheelPositionFractionY;

	bool					m_bFadeOutMusic;

	float					m_fDepthFades;
	float					m_fPauseFadeIn;
	float					m_fPauseFadeOut;
	float					m_fPauseFadeInFirst;
	float					m_fPauseFadeOutLast;

	float					m_fLetterWidth;
	float					m_fNumberWidth;

	float					m_fButtonTimer;
	bool					m_bButtonTimer;

	// timers
	float					m_pTimerShipPlayerEnter;

	// manual offset of letter box
	const float				LETTER_BOX_OFFSET_X = 84.0f;
	const float				LETTER_BOX_OFFSET_Y = -4.0f;
};