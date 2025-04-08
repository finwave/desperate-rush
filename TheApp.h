/**
 * A concrete game application class.
 * Uses virtualized state machine to 
 * create application states.
 */

#pragma once

#pragma warning(disable : 4995)

#define SHADOW_VOLUME_UPDATE_ALTERNATE
#define SHADOW_VOLUME_COMBINE_FIRST_2_PASSES

#include <time.h>
#include <sstream>

#include "ID3DApplication.h"

// include input engine
#include "InputEngine.h"
#include "InputKeyboard.h"
#include "InputJoystick.h"
#include "InputMouse.h"

// include sound engine
#include "SoundEngine.h"
#include "SoundWave.h"
#include "SoundMP3Player.h"

// include game highscore
#include "HighScore.h"

// include Resource classes
#include "ResourceMenus.h"
#include "ResourceHighScore.h"
#include "ResourceGame.h"

// include zip manager class
#include "ZipManager.h"

// scan code / virtual-key code reference class
#include "KeyReference.h"

// camera controls
#include "Camera.h"

#ifdef SHADOWS
#include "ShadowVolume.h"
#endif

#include "vertices.h"
#include "sounddefines.h"

// forward declaration of the virtual application state
class IState;

class CTheApp : public ID3DApplication
{
public:

	CTheApp(void);
	virtual ~CTheApp(void);

	/**
	 * OnCreate
	 * called when application initialisation is ready
	 * This is a perfect place to initialise all game
	 * specific resources, textures, sounds, whatever...
	 * @return S_OK, or error code. If error code is returned
	 * application will shutdown.
	 */
	virtual HRESULT OnCreate(void);

	/**
	 * OnRelease
	 * called when application is about to shutdown
	 * This is a perfect place to free all game specific
	 * resources.
	 */
	virtual void OnRelease(void);

	/**
	 * OnFlip
	 * Application main loop, called just before graphics
	 * are transferred to screen.
	 */
	virtual void OnFlip(void);

	/**
	 * OnKeyDown
	 * virtual keyboard handler
	 */
	virtual void OnKeyDown(DWORD dwKey);

	/**
	 * OnKeyUp
	 * virtual keyboard handler
	 */
	virtual void OnKeyUp(DWORD dwKey);

	/**
	 * GetRandomSeed
	 * get random seed value
	 * @return unsigned integer value of random seed
	 */
	inline unsigned int GetRandomSeed() { return this->m_fRandomSeed; }

	/**
	 * GetWave
	 * access loaded wave files
	 * @param dwIndex index defined in 'sounddefines.h' file
	 * @return reference to wave object
	 */
	inline CSoundWave& GetWave(DWORD dwIndex) { return m_Waves[dwIndex]; }

	/**
	 * GetMP3Player
	 * @return reference to mp3 player
	 */
	inline CSoundMP3Player& GetMP3Player1() { return m_MP3_1; }

	/**
	 * GetMP3Player2
	 * @return reference to mp3 player
	 */
	inline CSoundMP3Player& GetMP3Player2() { return m_MP3_2; }

	/**
	 * GetKeyboard
	 * @return pointer to keyboard
	 */
	inline CInputKeyboard* GetKeyboard() { return &m_Keyboard; }

	/**
	 * GetJoystick
	 * @return pointer to joystick
	 */
	inline CInputJoystick* GetJoystick() { return &m_Joystick; }

	/**
	 * GetMouse
	 * @return pointer to mouse
	 */
	inline CInputMouse* GetMouse() { return &m_Mouse; }

	/**
	 * GetHighScore
	 * @return reference to highscore
	 */
	inline CHighScore& GetHighScore() { return this->m_HighScores; }

	/**
	 * GetResourceMenus
	 * @return pointer to "menu" resources
	 */
	inline CResourceMenus* GetResourceMenus() { return &this->m_ResourceMenus; }

	/**
	 * GetResourceGame
	 * @return pointer to "game" resources
	 */
	inline CResourceGame* GetResourceGame() { return &this->m_ResourceGame; }

	/**
	 * GetResourceMenus
	 * @return pointer to "highscore" resources
	 */
	inline CResourceHighScore* GetResourceHighScore() { return &this->m_ResourceHighScore; }

	/**
	 * GetZipManager
	 * @return pointer to zip manager
	 */
	inline CZipManager* GetZipManager() { return &this->m_ZipManager; }

	/**
	 * GetBackgroundQuad
	 * @return pointer to background quad vertex array
	 */
	inline TRANSLITVERTEX* GetBackgroundQuad() { return m_Background; }

	/**
	 * GetBackgroundVB
	 * @return background quad vertex buffer
	 */
	inline LPDIRECT3DVERTEXBUFFER9 GetBackgroundVB() { return m_pVBBackground; }

	inline void SetCreateState(bool bCreate) {this->m_bCreateState = bCreate; }

	inline void SetMouseX(int iPosition) { this->m_iCurrentMouseX = iPosition; }
	inline void SetMouseY(int iPosition) { this->m_iCurrentMouseY = iPosition; }
	inline void SetMouseZ(int iPosition) { this->m_iCurrentMouseZ = iPosition; }

	inline int GetMouseX() { return this->m_iCurrentMouseX; }
	inline int GetMouseY() { return this->m_iCurrentMouseY; }
	inline int GetMouseZ() { return this->m_iCurrentMouseZ; }

	inline bool IsMouseMovement()
	{
		return ((this->m_iCurrentMouseX != this->m_iPreviousMouseX) ||
			(this->m_iCurrentMouseY != this->m_iPreviousMouseY));
	}

	inline bool IsLoadMenuSoundFiles() { return this->m_bLoadMenuSoundFiles; }
	inline bool IsLoadGameSoundFiles() { return this->m_bLoadGameSoundFiles; }

	inline void SetLoadMenuSoundFiles(bool enable) { this->m_bLoadMenuSoundFiles = enable; }
	inline void SetLoadGameSoundFiles(bool enable) { this->m_bLoadGameSoundFiles = enable; }

	void SetTextY(int iTextY);

	HRESULT CreateJoystick(void);
	void UpdateKeyboard(void);
	void UpdateJoystick(void);
	void UpdateMouse(void);
	void UpdateCharCursor(void);

	HRESULT LoadSoundFiles();

	/**
	 * GetButtonPress
	 * reads a pressed button and returns it as a char array
	 * @return reference to char array containing 
	 * hex decimal of a pressed button 
	 */
	char* GetButtonPress(void);

	void CheckKeyPushes();

	int GetVolumeMusic();
	int GetVolumeSoundEffect();
	bool VolumeMusicFadeOut(float fFrametime);

	/**
	 * HideFile
	 * sets a files hide attribute true
	 * @param fileName name of the file to be hidden
	 */
	void HideFile(std::string fileName, bool bHide);

	/**
	 * ShowFrames
	 * shows frames per second on the upper-right corner of a screen
	 */
	void ShowFrames(void);

	void ClearBuffers(LPDIRECT3DDEVICE9 device);

	float GetScreenWidth(void);
	float GetScreenHeight(void);

	inline void SetLoadingScreen(bool set) { this->m_bShowLoadingScreen = set; }

private:

	/**
	 * OnSize
	 * overrided to set background quad vertices
	 */
	virtual void OnSize(DWORD dwType, int iWidth, int iHeight);

	/**
	 * ChangeState
	 * change application state
	 * @param dwState new state identifier
	 * @return S_OK or error
	 */
	HRESULT ChangeState(DWORD dwState);

	/**
	 * InitState
	 * initialize application state
	 * @param dwState new state identifier
	 * @return S_OK or error
	 */
	HRESULT InitState(DWORD dwState);

	/**
	 * SetBackgroundQuad
	 * get the current screen size and init the
	 * background quad vertices
	 */
	void SetBackgroundQuad();	

	void RenderScene();

	//void UpdateCamera(int iDeltaX, int iDeltaY, int iDeltaZ);

#ifdef SHADOWS
	/**
	 * GetShadowVolumes
	 * gets shadow volumes from current application state
	 */
	void GetShadowVolumes();
#endif

	/**
	 * ErrorMessage
	 * shows an error messge
	 * @param iError HRESULT type of integer
	 */
	void ErrorMessage(int iError);

	bool IsCharPartOf(const char* target, const char* matcher);
	void UpdatePreviousMousePos();

	// pointer to current state object
	IState*							m_pState;

	// vertices for the background quad
	TRANSLITVERTEX					m_Background[4];

	// vertices for the background quad
	LPDIRECT3DVERTEXBUFFER9			m_pVBBackground;

	// sound playback objects
	CSoundEngine					m_SoundEngine;
	CSoundWave						m_Waves[NUM_WAVES];
	CSoundMP3Player					m_MP3_1;
	CSoundMP3Player					m_MP3_2;

	CInputEngine					m_InputEngine;
	std::vector<CInputEngine::DEVICE> m_arrInputDevices;

	CInputKeyboard					m_Keyboard;
	CInputJoystick					m_Joystick;
	CInputMouse						m_Mouse;

	// key codes reference
	CKeyReference					m_keyReference;

	Camera*							m_pCamera;

#ifdef SHADOWS
	// shadow volumes
	CShadowVolume*					m_pShadowVolumes;
#endif

	CHighScore						m_HighScores;
	CResourceMenus					m_ResourceMenus;
	CResourceGame					m_ResourceGame;
	CResourceHighScore				m_ResourceHighScore;
	CZipManager						m_ZipManager;

	// first state to run
	DWORD							m_dwFirstState;

	int								m_iCurrentMouseX;
	int								m_iCurrentMouseY;
	int								m_iCurrentMouseZ;

	int								m_iPreviousMouseX;
	int								m_iPreviousMouseY;
	int								m_iPreviousMouseZ;

	int								m_iTextY;

	bool							m_bCreateState;

	// random seed
	unsigned int					m_fRandomSeed;

	bool							m_bLoadMenuSoundFiles;
	bool							m_bLoadGameSoundFiles;

	bool							m_bShowLoadingScreen;
	bool							m_bMouseDrag;

	int								m_iMousePosX;
	int								m_iMousePosY;
	int								m_iMousePosZ;
};