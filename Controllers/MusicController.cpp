#include "../TheApp.h"
#include "MusicController.h"

CMusicController::CMusicController()
{
	this->m_pApp = NULL;
	this->m_eMusicType = Generic;

	this->m_iOriginalPlayerVolume = 0;
	this->m_bSingleLoadOnly = false;
	this->m_bIsFadeOut = false;
}

CMusicController::~CMusicController()
{
}

void CMusicController::Init(CTheApp* pApp, MusicType musicType)
{
	this->m_pApp = pApp;
	this->m_eMusicType = musicType;
}

void CMusicController::Release()
{
	// release mp3 player
	ReleaseMusic();
}

void CMusicController::Update(float fFrametime)
{
	if (this->m_bIsFadeOut)
	{
		UpdateMusicFadeOut(fFrametime);
	}

	UpdateMusicLoop(0.0);
}

void CMusicController::LoadMusic(LPCTSTR sFilePath)
{
	if (!this->m_bSingleLoadOnly || !this->m_MusicPlayer.IsCreated())
	{
		ReleaseMusic();
		this->m_MusicPlayer.Create(sFilePath);
		ResetMusicVolume();
	}
}

void CMusicController::SetMusicVolume(int iVolume)
{
	this->m_iOriginalPlayerVolume = iVolume;
	this->m_MusicPlayer.SetVolume(iVolume);
}

void CMusicController::PlayMusic()
{
	this->m_MusicPlayer.Play();
}

void CMusicController::PauseMusic()
{
	this->m_MusicPlayer.Pause();
}

void CMusicController::StopMusic()
{
	this->m_MusicPlayer.Stop();
}

void CMusicController::ReleaseMusic()
{
	this->m_MusicPlayer.Stop();
	this->m_MusicPlayer.Release();
}

void CMusicController::ResetMusicVolume()
{
	int configVolume = this->m_pApp->GetConfig().GetVolumeMusic();
	int playerVolume = ChangeToMusicPlayerVolume(configVolume);
	this->m_MusicPlayer.SetVolume(playerVolume);
	this->m_iOriginalPlayerVolume = playerVolume;
}

int CMusicController::ChangeToMusicPlayerVolume(int configVolume)
{
	int iVolume;

	if (configVolume == 0)
	{
		iVolume = -10000;
	}
	else
	{
		iVolume = (configVolume - 100) * 50;
	}

	return iVolume;
}

int CMusicController::ChangeToConfigVolume(int playerVolume)
{
	int iVolume;

	if (playerVolume == -10000)
	{
		iVolume = 0;
	}
	else
	{
		iVolume = playerVolume;
		iVolume /= 50;
		iVolume += 100;
	}

	return iVolume;
}

void CMusicController::UpdateMusicLoop(double dStartPos)
{
	if (this->m_MusicPlayer.IsAtEnd())
	{
		this->m_MusicPlayer.Stop();
		this->m_MusicPlayer.SetPosition(dStartPos);
		this->m_MusicPlayer.Play();
	}
}

void CMusicController::UpdateMusicFadeOut(float fFrametime)
{
	static float fChangeVolumeTimer = 0.0f;
	static int iFadeOutVolume = 0;
	static bool bStart = true;

	if (bStart)
	{
		fChangeVolumeTimer = VOLUME_FADE_STEP_DURATION;

		int playerVolume = this->m_MusicPlayer.GetVolume();
		iFadeOutVolume = ChangeToConfigVolume(playerVolume);

		bStart = false;
	}

	// decrease current volume
	if (iFadeOutVolume > 0)
	{
		if (fChangeVolumeTimer <= 0.0f)
		{
			fChangeVolumeTimer = VOLUME_FADE_STEP_DURATION;
			iFadeOutVolume -= 8;
			iFadeOutVolume = max(iFadeOutVolume, 0);
		}
		else
		{
			fChangeVolumeTimer -= fFrametime;
		}
	}

	// fade out finished
	if (iFadeOutVolume <= 0)
	{
		bStart = true;
		this->m_bIsFadeOut = false;

		StopMusic();
		// reset player volume
		this->m_MusicPlayer.SetVolume(this->m_iOriginalPlayerVolume);
	}
	else
	{
		int playerVolume = ChangeToMusicPlayerVolume(iFadeOutVolume);
		this->m_MusicPlayer.SetVolume(playerVolume);
	}
}