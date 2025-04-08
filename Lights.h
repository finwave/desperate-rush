#pragma once

#include "TheApp.h"
#include "Player.h"

class CLights
{
public:
	CLights(CTheApp* pTheApp);
	~CLights(void);

	void Release();

	void InitMenusMain();
	void InitHighscoreMain();
	void InitGameMain(int iLevelNumber);
	void InitGamePlayerBlastHigh();
	void InitGamePlayerBlastLow();

	void SetMenusMain(bool bActive);
	void SetHighscoreMain(bool bActive);
	void SetGameMain(bool bActive);
	void SetGamePlayerBlast(bool bActive,
							D3DXVECTOR3 posPlayer);

	void UpdateGamePlayerBlast(CPlayer::eBLAST_LIGHT eBlastLight);

	int GetLightCount();
	int* GetLightIndex();

private:

	CTheApp*		m_pTheApp;

	D3DLIGHT9		m_LightMenusMain;
	D3DLIGHT9		m_LightHighscoreMain;
	D3DLIGHT9		m_LightGameMain;
	D3DLIGHT9		m_LightGamePlayerBlastHigh;
	D3DLIGHT9		m_LightGamePlayerBlastLow;

	D3DLIGHT9		m_LightGamePlayerMinigunFront;
	D3DLIGHT9		m_LightGamePlayerMinigunDiagonal;

	bool			m_bLight0;
	bool			m_bLight1;
	bool			m_bLight2;
	bool			m_bLight3;
	bool			m_bLight4;
	bool			m_bLight5;
	bool			m_bLight6;

	bool			m_bPlayerBlastUpdateStart;

	int				m_iPlayerBlastLight;
};