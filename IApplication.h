/**
 * An abstract class implements basic
 * features of game application, including
 * window handling etc.
 */

#pragma once

// include all windows specific stuff
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Timer.h"
#include "ZipManager.h"


class IApplication
{
public:
	IApplication(void);
	virtual ~IApplication(void);

	/**
	 * Create
	 * initialise application main window with given parameters
	 * @param iWidth screen resolution width
	 * @param iHeight screen resolution height
	 * @param iBPP bits per pixel (16 or 32)
	 * @param bWindowed TRUE if started in windowed mode
	 * @param strTitle application title text
	 * @param dwFlags additional startup flags
	 * @return S_OK, or system wide error code
	 */
	HRESULT Create(	int iWidth,
					int iHeight,
					int iBPP,
					BOOL bWindowed,
					LPCTSTR strTitle,
					DWORD dwFlags);

	/**
	 * Release
	 * release application resources and shutdown
	 */
	virtual void Release(void);

	/**
	 * Close
	 * close application by sending the WM_CLOSE
	 * message to main window
	 */
	void Close(void);

	/**
	 * Run
	 * application message pump and main loop.
	 * Returns when application has closed.
	 * @return value from WM_QUIT message
	 */
	int Run(void);


	/**
	 * DoFlip
	 * function performs one screen update
	 */
	virtual void DoFlip(void);



	/* --------------------------------------------
	 * PURE VIRTUALS
	 */

	/**
	 * OnCreate
	 * called when application initialisation is ready
	 * This is a perfect place to initialise all game
	 * specific resources, textures, sounds, whatever...
	 * @return S_OK, or error code. If error code is returned
	 * application will shutdown.
	 */
	virtual HRESULT OnCreate(void) = 0;

	/**
	 * OnRelease
	 * called when application is about to shutdown
	 * This is a perfect place to free all game specific
	 * resources.
	 */
	virtual void OnRelease(void) = 0;

	/**
	 * OnFlip
	 * Application main loop, called just before graphics
	 * are transferred to screen.
	 */
	virtual void OnFlip(void) = 0;




	/**
	 * GetWindow
	 * @return application main window handle
	 */
	inline HWND GetWindow() { return m_hWnd; }

	/**
	 * IsActive
	 * @return TRUE if application is active and updating
	 */
	inline BOOL IsActive() const { return m_bActive; }

	/**
	 * SetActive
	 * @param bSet TRUE to activate application, or FALSE
	 */
	void SetActive(BOOL bSet);

	/**
	 * IsWindowed
	 * @return TRUE if application is running in windowed mode
	 */
	inline BOOL IsWindowed() const { return m_bWindowed; }

	/**
	 * GetScreenRect
	 * @return screen rectangle, related to desktop
	 */
	inline RECT& GetScreenRect() { return m_rcScreen; }

	/**
	 * GetWindowRect
	 * @return window rectangle (0, 0, width, height)
	 */
	inline RECT& GetWindowRect() { return m_rcWindow; }

	/**
	 * GetTimer
	 * @return reference to application timer
	 */
	inline CTimer& GetTimer() { return m_Timer; }

	/**
	 * GetFrameTime
	 * @return number of seconds passed since last frame (frame delta)
	 */
	inline float GetFrameTime() const { return m_Timer.GetElapsedSeconds(); }

	/**
	 * RandInt
	 * @return random integer in between iLow and iHigh
	 */
	static int RandInt(int iLow, int iHigh);

	/**
	 * RandFloat
	 * @return random float in between fLow and fHigh
	 */
	static float RandFloat(float fLow, float fHigh);

protected:
	/**
	 * CreateAppWindow
	 * create application main window
	 * @param iWidth screen resolution width
	 * @param iHeight screen resolution height
	 * @param bWindowed TRUE if started in windowed mode
	 * @param strTitle application title text
	 * @return TRUE if successful
	 */
	BOOL CreateAppWindow(	int iWidth,
							int iHeight,
							BOOL bWindowed,
							LPCTSTR strTitle);

	/**
	 * OnMessage
	 * virtual message handler, handles all window messages
	 * @param iMessage message identifier
	 * @param wParam parameter from windows
	 * @param lParam parameter from windows
	 * @return TRUE if message was handled and no default processing
	 *			is necessary. If FALSE, DefWindowProc is called
	 */
	virtual BOOL OnMessage(	UINT iMessage, 
							WPARAM wParam,
							LPARAM lParam);

	/**
	 * OnSize
	 * virtual handler for window resize messages
	 * @param dwType type of resize, see WIN32 API help
	 * @param iWidth new width of the window
	 * @param iHeight new height of the window
	 */
	virtual void OnSize(DWORD dwType, int iWidth, int iHeight);

	/**
	 * OnMove
	 * virtual handler for window move messages
	 * @param iX new window position
	 * @param iY new window position
	 */
	virtual void OnMove(int iX, int iY);

	/**
	 * OnKeyDown
	 * virtual keyboard message handler
	 * @param dwKey key code from windows
	 */
	virtual void OnKeyDown(DWORD dwKey);

	/**
	 * OnKeyUp
	 * virtual keyboard message handler
	 * @param dwKey key code from windows
	 */
	virtual void OnKeyUp(DWORD dwKey);

	/**
	 * OnChar
	 * virtual handler for processed keyboard messages
	 * @param c character entered by user
	 */
	virtual void OnChar(TCHAR c);

	/**
	 * UpdateRectangles
	 * update screen and window rectangles with
	 * current window size and position
	 */
	void UpdateRectangles(void);

private:
	/**
	 * WndProc
	 * Static window procedure function
	 */
	static long WINAPI WndProc(	HWND hWnd,
								UINT iMessage,
								WPARAM wParam,
								LPARAM lParam);

	// application main window
	HWND			m_hWnd;

	// is application running in windowed mode
	BOOL			m_bWindowed;

	// is application active
	BOOL			m_bActive;

	// screen rectangle, where window is related
	// to desktop
	RECT			m_rcScreen;

	// window rectangle, just a size of our window
	// drawable area (0, 0, width, height)
	RECT			m_rcWindow;

	// application frame timer
	CTimer			m_Timer;
};