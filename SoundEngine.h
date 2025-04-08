/**
 * The sound engine with Direct Sound.
 * 
 * Requires:
 * Project wide define:
 * DIRECTSOUND_VERSION=0x900
 * 
 * Libs:
 * dsound.lib winmm.lib
 */

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <dsound.h>


class CSoundEngine
{
public:
	CSoundEngine(void);
	virtual ~CSoundEngine(void);

	// Create
	// initialise sound engine. Parameters are
	// used to set up the primary mixing buffer
	HRESULT Create(	HWND hWnd,
					DWORD dwFrequency,
					DWORD dwBitsPerSample,
					DWORD dwChannels,
					DWORD dwFlags);

	// Release
	void Release(void);

	// GetMasterVolume
	// returns currently set master volume
	int GetMasterVolume(void);

	// SetMasterVolume
	// set volume of the entire sound system
	// iVolume is value in range 0 to -10000
	// where 0 is maximum volume and -10000 is mute
	void SetMasterVolume(int iVolume);

	// GetDirectSound
	// access to DirectSound object
	inline LPDIRECTSOUND8 GetDirectSound() { return m_pDS; }

	// GetPrimaryBuffer
	// access to primary mixing buffer
	inline LPDIRECTSOUNDBUFFER GetPrimaryBuffer() { return m_pDSBPrimary; }

	// GetWindow
	// returns handle to associated window
	inline HWND GetWindow() { return m_hWnd; }

private:
	LPDIRECTSOUND8			m_pDS;
	LPDIRECTSOUNDBUFFER		m_pDSBPrimary;

	HWND					m_hWnd;
	int						m_iOriginalMasterVolume;
};