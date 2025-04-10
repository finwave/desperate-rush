/**
 * This class implements
 * game application "menus" state.
 */

#pragma once

// DEFINES

#define LOAD_MESH_MENUS_A						0
#define LOAD_MESH_MENUS_B						1
#define LOAD_MESH_MENUS_C						2
#define LOAD_MESH_MENUS_D						3
#define LOAD_MESH_MENUS_E						4
#define LOAD_MESH_MENUS_F						5
#define LOAD_MESH_MENUS_G						6
#define LOAD_MESH_MENUS_H						7
#define LOAD_MESH_MENUS_I						8
#define LOAD_MESH_MENUS_J						9
#define LOAD_MESH_MENUS_K						10
#define LOAD_MESH_MENUS_L						11
#define LOAD_MESH_MENUS_M						12
#define LOAD_MESH_MENUS_N						13
#define LOAD_MESH_MENUS_O						14
#define LOAD_MESH_MENUS_P						15
#define LOAD_MESH_MENUS_Q						16
#define LOAD_MESH_MENUS_R						17
#define LOAD_MESH_MENUS_S						18
#define LOAD_MESH_MENUS_T						19
#define LOAD_MESH_MENUS_U						20
#define LOAD_MESH_MENUS_V						21
#define LOAD_MESH_MENUS_W						22
#define LOAD_MESH_MENUS_X						23
#define LOAD_MESH_MENUS_Y						24
#define LOAD_MESH_MENUS_Z						25

#define LOAD_MESH_MENUS_0						26
#define LOAD_MESH_MENUS_1						27
#define LOAD_MESH_MENUS_2						28
#define LOAD_MESH_MENUS_3						29
#define LOAD_MESH_MENUS_4						30
#define LOAD_MESH_MENUS_5						31
#define LOAD_MESH_MENUS_6						32
#define LOAD_MESH_MENUS_7						33
#define LOAD_MESH_MENUS_8						34
#define LOAD_MESH_MENUS_9						35

#define LOAD_MESH_MENUS_PLANET					36
#define LOAD_MESH_MENUS_MAX						37

#define LOAD_SPRITE_MENUS_MAX					47

#define MESH_SHADOW_COUNT_MENUS					7

#define DISPLAY_LETTER_COUNT_MENUS				26
#define DISPLAY_NUMBER_COUNT_MENUS				10

#include <vector>
#include <string>

#include "IState.h"
#include "HighScoreItem.h"
#include "XFileContainer.h"
#include "MenuObject.h"
#include "MenuObjectRoller.h"
#include "MenuBoss1Scatter.h"
#include "Letter.h"
#include "Number.h"
#include "Sprite.h"
#include "SpriteScrolling.h"
#include "Queue.h"
#include "InputJoystick.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

class CStateMenus : public IState
{
public:

	CStateMenus(void);
	virtual ~CStateMenus(void);

	virtual HRESULT Create(CTheApp* pApp, DWORD dwState);
	virtual HRESULT InitState(DWORD dwState);

	/**
	 * Release
	 * release main menu resources.
	 */
	virtual void Release();

	/**
	 * Update
	 * update main menu
	 * @param fFrametime application frame time
	 * @return state update value
	 */
	virtual DWORD Update(float fFrametime);

	/**
	 * Render
	 * render main menu
	 */
	virtual void Render();

	/**
	 * OnKeyDown
	 * handle main menu keypresses
	 * @param dwKey keycode of the pressed key
	 */
	virtual void OnKeyDown(DWORD dwKey);

	/**
	 * OnKeyUp
	 * virtual keyboard handler for the application states
	 * @param dwKey keycode of the pressed key
	 */
	virtual void OnKeyUp(DWORD dwKey);

#ifdef SHADOWS
	virtual CShadowVolume* GetShadowVolumes();
#endif

private:

	enum eMENUS
	{
		Main,
		New_Game,
		Options,
		Input,
		Audio,
		Display,
		Highscore,
		Credits,
		Exit
	};

	enum eINPUT_DEVICE
	{
		Mouse,
		Joystick,
		Keyboard
	};

	enum eKEYBOARD_MENU_BROWSE
	{
		Main_First,
		Main_New_Game,
		Main_Options,
		Main_Highscore,
		Main_Exit,
		Main_Last,
		Options_First,
		Options_Input,
		Options_Audio,
		Options_Display,
		Options_Back,
		Options_Last,
		Input_First,
		Input_Key_Up,
		Input_Key_Down,
		Input_Key_Left,
		Input_Key_Right,
		Input_Key_Fire_Mode,
		Input_Key_Minigun,
		Input_Key_Cannon,
		Input_Key_Blast,
		Input_Back,
		Input_Default,
		Input_Last,
		Audio_First,
		Audio_Music,
		Audio_Sound,
		Audio_Back,
		Audio_Last,
		Display_First,
		Display_Antialiasing,
		Display_Specular_Lighting,
		Display_Back,
		Display_Last,
		Highscore_First,
		Highscore_Back,
		Highscore_Last
	};

	void RenderNewGame(float fFrametime);
	void RenderMain();
	void RenderOptions();
	void RenderInput();
	void RenderAudio(float fFrametime);
	void RenderDisplay();
	void RenderHighScore(float fFrametime);
#ifdef MENU_CREDITS
	void RenderCredits();
#endif
	void RenderExit(float fFrametime);

	void RenderAudioBars();
	void RenderBackground();
	void RenderShips(float fFrametime);
	void RenderScores(float fFrametime);
	void RenderGameVersion();

#ifdef MENUS_PLANET
	void RenderPlanet();
#endif

#ifdef MENUS_FOG
	void RenderFog();
#endif

	void OnBackAction();
	void ActivateInputKeyBox();

	void ResetPlayerInput();
	void UpdatePlayerInput();
	bool IsValidSelectClick();

	void OnKeyboardMenuBrowse(DWORD dwKey);
	void PlaySoundBarNoise(bool bIsForced);

	void ShowControls();

	bool CheckHex(char first, char second);
	std::basic_string<TCHAR> DescribeHex(char first, char second);
	char HexToAscii(char first, char second);

	void LoadSprites();
	HRESULT LoadMeshes();

	void ChangeSpecularity();

#ifdef SHADOWS
	HRESULT BuildShadowVolumes();
#endif

	CResourceMenus*			m_pResourceMenus;
	CResourceHighScore*		m_pResourceHighScores;

	CInputMouse*			m_pMouse;
	CInputJoystick*			m_pJoystick;

	eMENUS					m_eMenus;
	eINPUT_DEVICE			m_eInputDevice;
	eKEYBOARD_MENU_BROWSE	m_eKeyboardMenuBrowse;

	DWORD					m_dwNextState;

	// highscore items
	std::vector<CHighScoreItem>	m_Scores;

	CQueue<CMenuObject*>	m_pShips;

#ifdef SHADOWS
	// shadows
	CShadowVolume*			m_pShadowVolumes;
#endif

	// 3d meshes

	CXFileContainer*		m_pXFile;

#ifdef MENUS_PLANET
	CMenuObject*			m_pPlanet;
#endif

	CMenuObject*			m_pPlayer;
	CMenuObject*			m_pDrone1;
	CMenuObject*			m_pDrone2;
	CMenuObject*			m_pSniper1;
	CMenuObject*			m_pSniper2;
	CMenuObjectRoller*		m_pRoller1;
	CMenuObjectRoller*		m_pRoller2;
	CMenuObject*			m_pBoss1Frame;
	CMenuBoss1Scatter*		m_pBoss1ScatterLeft;
	CMenuBoss1Scatter*		m_pBoss1ScatterRight;

	CLetter*				m_pLetters;
	CNumber*				m_pNumbers;

	// 2d sprites

	CSprite*				m_pSpriteCursor;

#ifdef MENUS_FOG
	CSpriteScrolling*		m_pSpriteFogBack;
	CSpriteScrolling*		m_pSpriteFogFront;
#endif
	
	CSpriteScrolling*		m_pSpriteStarsFront;
	CSpriteScrolling*		m_pSpriteStarsBack;
	CSprite*				m_pSpriteMenuBackground;

	CSprite*				m_pSpriteMenuTitleMain;
	CSprite*				m_pSpriteMenuTitleHighscore;

	CSprite*				m_pSpriteMenuMain;
	CSprite*				m_pSpriteMenuOptions;
	CSprite*				m_pSpriteMenuInput;
	CSprite*				m_pSpriteMenuAudio;
	CSprite*				m_pSpriteMenuDisplay;
	CSprite*				m_pSpriteMenuHighscore;

	CSprite*				m_pSpriteVideoAntialiasingBarBorder;
	CSprite*				m_pSpriteVideoAntialiasingBar2x;
	CSprite*				m_pSpriteVideoAntialiasingBar46x;
	CSprite*				m_pSpriteVideoAntialiasingBar8x;

	CSprite*				m_pSpriteArrowInput;
	CSprite*				m_pSpriteArrowAntialiasingNormalLeft;
	CSprite*				m_pSpriteArrowAntialiasingNormalRight;
	CSprite*				m_pSpriteArrowAntialiasingGlowLeft;
	CSprite*				m_pSpriteArrowAntialiasingGlowRight;
	CSprite*				m_pSpriteArrowAntialiasingHideLeft;
	CSprite*				m_pSpriteArrowAntialiasingHideRight;

	CSprite*				m_pSpriteSpecularLightingOn;
	CSprite*				m_pSpriteSpecularLightingOnGlow;
	CSprite*				m_pSpriteSpecularLightingOff;
	CSprite*				m_pSpriteSpecularLightingOffGlow;

	CSprite*				m_pSpriteMessageInputEmpty;
	CSprite*				m_pSpriteMessageInputKey;
	CSprite*				m_pSpriteMessageRestart;
	CSprite*				m_pSpriteMessageOK1;
	CSprite*				m_pSpriteMessageOK2;

	CSprite*				m_pSpriteUnderlineAudio;
	CSprite*				m_pSpriteUnderlineBack;
	CSprite*				m_pSpriteUnderlineDefault;
	CSprite*				m_pSpriteUnderlineDisplay;
	CSprite*				m_pSpriteUnderlineExit;
	CSprite*				m_pSpriteUnderlineHighscore;
	CSprite*				m_pSpriteUnderlineInput;
	CSprite*				m_pSpriteUnderlineNewgame;
	CSprite*				m_pSpriteUnderlineOptions;

#ifdef MENU_CREDITS
	CSprite*				m_pSpriteUnderlineCredits;

	CSprite*				m_pSpriteCreditsBackLayer;
	CSpriteScrolling*		m_pSpriteCreditsText;
#endif

	CSprite*				m_pSpriteVersion;

	CSprite*				m_pSpriteAudioBarBorder;
	CSprite*				m_pSpriteAudioBarMeter;

	bool					m_bFadeOutMusic;
	float					m_fPauseFadeOut;
	float					m_fPauseFadeOutLast;

	float					m_fLetterWidth;
	float					m_fNumberWidth;

	bool					m_bMessageBoxEmpty;
	bool					m_bMessageBoxKey;
	bool					m_bMessageBoxKeyPause;

	int						m_iAntialiasingCurrent;
	bool					m_bChangeSpecularity;
	bool					m_bDisplayChangesExit;

	int						m_iTextX;
	int						m_iTextY;
	int						m_iControlInput;	

	float					m_fBoxKeyTimer;
	float					m_fSoundBarNoiseTimer;

	bool					m_bInputUp;
	bool					m_bInputDown;
	bool					m_bInputLeft;
	bool					m_bInputRight;
	bool					m_bInputSelect;
	bool					m_bIsClickPause;

	const int				MOUSE_CURSOR_SPEED = 4;
	const int				MAX_HIGHSCORE_ITEMS = 10;
};