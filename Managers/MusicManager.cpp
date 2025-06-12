#include "../TheApp.h"
#include "MusicManager.h"

CMusicManager::CMusicManager()
{
	this->m_eCurrentMusicType = CMusicController::MusicType::MaxCount;
}

CMusicManager::~CMusicManager()
{
}

void CMusicManager::Init(CTheApp* pApp)
{
	for (int i = 0; i < (int)CMusicController::MusicType::MaxCount; i++)
	{
		CMusicController::MusicType musicType = (CMusicController::MusicType)i;

		CMusicController* pMusicController = new CMusicController();
		pMusicController->Init(pApp, musicType);

		this->m_vMusicController.push_back(pMusicController);
	}
}

void CMusicManager::Release()
{
	for (DWORD i = 0; i < this->m_vMusicController.size(); i++)
	{
		CMusicController* pMusicController = this->m_vMusicController[i];

		if (pMusicController != NULL)
		{
			pMusicController->Release();
			delete pMusicController;
			pMusicController = NULL;
		}
	}

	m_vMusicController.clear();
}

void CMusicManager::Update(float fFrametime)
{
	for (DWORD i = 0; i < this->m_vMusicController.size(); i++)
	{
		this->m_vMusicController[i]->Update(fFrametime);
	}
}

void CMusicManager::LoadMusic(CMusicController::MusicType musicType, LPCTSTR sFilePath)
{
	CMusicController* pMusicController = GetController(musicType);

	if (pMusicController)
	{
		pMusicController->LoadMusic(sFilePath);
	}
}

void CMusicManager::PlayMusic(CMusicController::MusicType musicType)
{
	this->m_eCurrentMusicType = musicType;
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		pMusicController->PlayMusic();
	}
}

void CMusicManager::SetMusicVolume(CMusicController::MusicType musicType, int iVolume)
{
	CMusicController* pMusicController = GetController(musicType);

	if (pMusicController)
	{
		pMusicController->SetMusicVolume(iVolume);
	}
}

void CMusicManager::SetSingleLoadOnly(CMusicController::MusicType musicType)
{
	CMusicController* pMusicController = GetController(musicType);

	if (pMusicController)
	{
		pMusicController->SetSingleLoadOnly();
	}
}

void CMusicManager::PauseMusic()
{
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		pMusicController->PauseMusic();
	}
}

void CMusicManager::StopMusic()
{
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		pMusicController->StopMusic();
	}
}

void CMusicManager::SetMusicFadeOut()
{
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		pMusicController->SetMusicFadeOut();
	}
}

bool CMusicManager::IsMusicFadeOut()
{
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		return pMusicController->IsMusicFadeOut();
	}

	return false;
}

CSoundMP3Player::eSTATE CMusicManager::GetPlayerState()
{
	CMusicController* pMusicController = GetCurrentController();

	if (pMusicController)
	{
		return pMusicController->GetPlayerState();
	}

	return CSoundMP3Player::eSTATE::eSTATE_STOPPED;
}

CMusicController* CMusicManager::GetController(CMusicController::MusicType musicType)
{
	for (DWORD i = 0; i < this->m_vMusicController.size(); i++)
	{
		if (this->m_vMusicController[i]->GetMusicType() == musicType)
		{
			return this->m_vMusicController[i];
		}
	}

	return NULL;
}

CMusicController* CMusicManager::GetCurrentController()
{
	for (DWORD i = 0; i < this->m_vMusicController.size(); i++)
	{
		if (this->m_vMusicController[i]->GetMusicType() == this->m_eCurrentMusicType)
		{
			return this->m_vMusicController[i];
		}
	}

	return NULL;
}