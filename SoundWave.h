/**
 * This class implements the wave sound
 * capable of loading itself from the file
 * and to use duplicates to play same sound
 * multiple times simultaneously.
 */

#pragma once

#include "SoundEngine.h"

// use this define as 'dwDuplicate' for 
// play functions to automatically play next
// available duplicate sound
#define NEXT_FREE_DUPLICATE 0x0fffffff


class CSoundWave
{
public:
	CSoundWave(void);
	virtual ~CSoundWave(void);

	// Create
	// create 'empty' sound buffer into the memory
	HRESULT Create(	CSoundEngine* pSoundEngine,
					DWORD dwFrequency,
					DWORD dwBitsPerSample,
					DWORD dwChannels,
					DWORD dwBytes,
					DWORD dwDuplicates,
					DWORD dwFlags);

	// Release
	// release all sound buffers
	void Release(void);

	// Load
	// load wave file into the buffer and create
	// the duplicates
	HRESULT Load(	CSoundEngine* pSoundEngine,
					LPCTSTR strFilename,
					DWORD dwDuplicates,
					DWORD dwFlags);

	// Play
	// play the wave file or its duplicate
	void Play(BOOL bLoop, DWORD dwDuplicate);
	void Play(BOOL bLoop, DWORD dwDuplicate, int iVolume);

	// Stop
	// stop the wave playback
	void Stop(DWORD dwDuplicate);

	// RePlay
	// start wave playback from the beginning of sound
	void RePlay(BOOL bLoop, DWORD dwDuplicate);

	// IsPlaying
	// returns TRUE if certain buffer is playing
	BOOL IsPlaying(DWORD dwDuplicate);

	// IsLooping
	// returns TRUE if wave is playing in looping mode
	BOOL IsLooping(DWORD dwDuplicate);

	// GetPosition
	// returns playback position in milliseconds
	DWORD GetPosition(DWORD dwDuplicate);

	// SetPosition
	// set the playback position in milliseconds
	void SetPosition(DWORD dwPosition, DWORD dwDuplicate);

	// SetFrequency
	// set the playback speed
	// Wave must be created with DSBCAPS_CTRLFREQUENCY flag
	void SetFrequency(DWORD dwFrequency, DWORD dwDuplicate);

	// GetFrequency
	// get the current playback speed
	// Wave must be created with DSBCAPS_CTRLFREQUENCY flag
	DWORD GetFrequency(DWORD dwDuplicate);

	// GetVolume
	// returns current wave playback volume
	// Wave must be created with DSBCAPS_CTRLVOLUME flag
	// volume value is in between 0 to -10000
	// where 0 is max volume, and -10000 is mute
	int GetVolume(DWORD dwDuplicate);

	// SetVolume
	// set wave playback volume
	// Wave must be created with DSBCAPS_CTRLVOLUME flag
	// volume value is in between 0 to -10000
	// where 0 is max volume, and -10000 is mute
	void SetVolume(int iVolume, DWORD dwDuplicate);

	// GetPan
	// returns current playback panning value
	// Wave must be created with DSBCAPS_CTRLPAN flag
	// panning is:
	// -10000		full left
	// 0			center
	// 10000		full right
	int GetPan(DWORD dwDuplicate);

	// SetPan
	// set the playback panning value
	// Wave must be created with DSBCAPS_CTRLPAN flag
	// panning is:
	// -10000		full left
	// 0			center
	// 10000		full right
	void SetPan(int iPan, DWORD dwDuplicate);

	// GetBufferCount
	// returns the number of buffers in this wave
	inline DWORD GetBufferCount() const { return m_dwBufferCount; }

	// GetNextFreeDuplicate
	// returns index of duplicate buffer that
	// is currently not playing. In case of
	// all buffers already playing, return 0
	DWORD GetNextFreeDuplicate(void);

	// SetEffect
	// set some standard environment effects into the wave
	// Wave must be created with DSBCAPS_CTRLFX flag
	HRESULT SetEffect(GUID gdEffect, DWORD dwDuplicate);

private:
	// MillisecondsToBytes
	// converts given time value into the position
	// in sound buffer
	int MillisecondsToBytes(int iMS);

	// BytesToMilliseconds
	// converts given buffer position into the time value
	int BytesToMilliseconds(int iBytes);

	// direct sound buffer(s)
	LPDIRECTSOUNDBUFFER8*	m_ppDSB;
	DWORD					m_dwBufferCount;
};