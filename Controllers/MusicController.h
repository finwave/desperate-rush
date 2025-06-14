#pragma once

// include all windows specific stuff
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../SoundMP3Player.h"

// Forward declaration
class CTheApp;

class CMusicController
{
public:

	enum MusicType
	{
		Generic,
		GameBoss,
		GameOver,
		GameOutro,
		MaxCount
	};

	CMusicController(void);
	~CMusicController(void);

	void Init(CTheApp* pApp, MusicType musicType);
	void Release();

	void Update(float fFrametime);

	void LoadMusic(LPCTSTR sFilePath);
	void SetMusicVolume(int iVolume);

	void PlayMusic();
	void PauseMusic();
	void StopMusic();

	inline MusicType GetMusicType() { return this->m_eMusicType; }
	inline CSoundMP3Player::eSTATE GetPlayerState() { return m_MusicPlayer.GetState(); }

	inline void SetSingleLoadOnly() { this->m_bSingleLoadOnly = true; }
	inline void SetMusicFadeOut() { this->m_bIsFadeOut = true; }
	inline bool IsMusicFadeOut() { return this->m_bIsFadeOut; }

private:

	const float VOLUME_FADE_STEP_DURATION = 0.0255f;

	void ReleaseMusic();
	void ResetMusicVolume();

	int ChangeToMusicPlayerVolume(int configVolume);
	int ChangeToConfigVolume(int playerVolume);

	void UpdateMusicLoop(double dStartPos);
	void UpdateMusicFadeOut(float fFrametime);

	CTheApp* m_pApp;
	CSoundMP3Player m_MusicPlayer;

	MusicType m_eMusicType;

	int m_iOriginalPlayerVolume;
	bool m_bSingleLoadOnly;
	bool m_bIsFadeOut;
};
