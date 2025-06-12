#pragma once

#include <vector>
#include "../Controllers/MusicController.h"

// Forward declaration
class CTheApp;

class CMusicManager
{
public:

	CMusicManager(void);
	~CMusicManager(void);

	void Init(CTheApp* pApp);
	void Release();

	void Update(float fFrametime);

	void LoadMusic(CMusicController::MusicType musicType, LPCTSTR sFilePath);
	void PlayMusic(CMusicController::MusicType musicType);
	void SetMusicVolume(CMusicController::MusicType musicType, int iVolume);
	void SetSingleLoadOnly(CMusicController::MusicType musicType);

	void PauseMusic();
	void StopMusic();

	void SetMusicFadeOut();
	bool IsMusicFadeOut();

	CSoundMP3Player::eSTATE GetPlayerState();

private:

	CMusicController* GetController(CMusicController::MusicType musicType);
	CMusicController* GetCurrentController();

	std::vector<CMusicController*> m_vMusicController;
	CMusicController::MusicType m_eCurrentMusicType;
};

