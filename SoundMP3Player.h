/**
 * A simple MP3 player class.
 *
 * Requires:
 * DirectShow component from
 * WindowsPlatform SDK.
 *
 * Libs:
 * strmiids.lib
 * 
 * CoInitialize(NULL) must be called
 * before using this class.
 */

#pragma once

// include the basic windows stuff
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#include <dshow.h>

class CSoundMP3Player
{
public:
	// player state
	enum eSTATE
	{
		eSTATE_STOPPED=0,
		eSTATE_PLAYING,
		eSTATE_PAUSE,
		eSTATE_FORCEDWORD=0xffffffff
	};

	CSoundMP3Player(void);
	virtual ~CSoundMP3Player(void);

	// Create
	// initialise player to play a mp3 file
	HRESULT Create(LPCTSTR strFilePath);

	// Release
	void Release(void);

	// Play
	// start playing the mp3
	void Play(void);

	// Stop
	// stop playing the mp3
	void Stop(void);

	// Pause
	// pause the mp3 playback
	void Pause(void);

	// GetPosition
	// get the playback position
	double GetPosition(void);

	// SetPosition
	// set the playback position
	void SetPosition(double dPosition);

	// GetDuration
	// returns the duration (time) of mp3
	double GetDuration(void);

	// SetVolume
	// set the volume of mp3
	// iVolume parameter is in range of
	// 0 to -10000, where 0 is max volume
	// and -10000 is mute
	void SetVolume(int iVolume);

	// GetVolume
	// returns current mp3 volume
	int GetVolume(void);

	// IsAtEnd
	// returns TRUE if playback has reached the end of file
	BOOL IsAtEnd(void);

	// GetState
	// returns current state of the player
	inline eSTATE GetState() const { return m_eState; }

private:
	IGraphBuilder*		m_pGraph;
	IMediaPosition*		m_pPosition;
	eSTATE				m_eState;
};