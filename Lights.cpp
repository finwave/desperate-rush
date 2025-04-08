#include "Lights.h"

CLights::CLights(CTheApp* pTheApp)
{
	this->m_pTheApp = pTheApp;

	this->m_bLight0 = false;
	this->m_bLight1 = false;
	this->m_bLight2 = false;
	this->m_bLight3 = false;
	this->m_bLight4 = false;
	this->m_bLight5 = false;
	this->m_bLight6 = false;

	this->m_bPlayerBlastUpdateStart = false;

	this->m_iPlayerBlastLight = 0;
}

CLights::~CLights(void)
{
}

void CLights::Release()
{
}

void CLights::InitMenusMain()
{
	D3DLIGHT9 light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	this->m_pTheApp->GetDevice()->GetLight(0, &light);

	light.Type = D3DLIGHT_POINT;

	light.Ambient = D3DXCOLOR(0.35f, 0.35f, 0.35f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	light.Range = 50000.0f;
	light.Falloff = 0;

	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;

	light.Position = D3DXVECTOR3(80.0f, 0.0f, -1200.0f);

	this->m_LightMenusMain = light;
}

void CLights::InitHighscoreMain()
{
	D3DLIGHT9 light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	this->m_pTheApp->GetDevice()->GetLight(0, &light);

	light.Type = D3DLIGHT_POINT;

	light.Ambient = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	light.Range = 50000.0f;
	light.Falloff = 0;

	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;

	light.Position = D3DXVECTOR3(80.0f, 0.0f, -2000.0f);

	this->m_LightHighscoreMain = light;
}

void CLights::InitGameMain(int iLevelNumber)
{
	D3DLIGHT9 light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	this->m_pTheApp->GetDevice()->GetLight(0, &light);

	light.Type = D3DLIGHT_POINT;
	
	light.Range = 2050.0f;
	light.Falloff = 0;

	light.Attenuation0 = 0.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.00000122f;

	float posZ = -1200.0f;

	switch(iLevelNumber)
	{
	case 1:

		light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		light.Position = D3DXVECTOR3(80.0f, -100.0f, posZ);

		break;

	case 2:

		light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		light.Position = D3DXVECTOR3(80.0f, -100.0f, posZ);

		break;

	case 3:

		light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		light.Position = D3DXVECTOR3(80.0f, -100.0f, posZ);

		break;
	}

	this->m_LightGameMain = light;
}

void CLights::InitGamePlayerBlastHigh()
{
	D3DLIGHT9 light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	this->m_pTheApp->GetDevice()->GetLight(0, &light);

	light.Type = D3DLIGHT_POINT;

	light.Ambient = D3DXCOLOR(7.0f, 0.0f, 0.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	light.Range = 400.0f;
	light.Falloff = 0;

	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;

	light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->m_LightGamePlayerBlastHigh = light;
}

void CLights::InitGamePlayerBlastLow()
{
	D3DLIGHT9 light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	this->m_pTheApp->GetDevice()->GetLight(0, &light);

	light.Type = D3DLIGHT_POINT;

	light.Ambient = D3DXCOLOR(3.5f, 0.0f, 0.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	light.Range = 400.0f;
	light.Falloff = 0;

	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;

	light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->m_LightGamePlayerBlastLow = light;
}

void CLights::SetMenusMain(bool bActive)
{
	// activate light
	if(bActive)
	{
		this->m_pTheApp->GetDevice()->SetLight(0, &this->m_LightMenusMain);
		this->m_pTheApp->GetDevice()->LightEnable(0, TRUE);
		this->m_bLight0 = true;
	}
	// deactivate light
	else
	{
		this->m_pTheApp->GetDevice()->LightEnable(0, FALSE);
		this->m_bLight0 = false;
	}
}

void CLights::SetHighscoreMain(bool bActive)
{
	// activate light
	if(bActive)
	{
		this->m_pTheApp->GetDevice()->SetLight(0, &this->m_LightHighscoreMain);
		this->m_pTheApp->GetDevice()->LightEnable(0, TRUE);
		this->m_bLight0 = true;
	}
	// deactivate light
	else
	{
		this->m_pTheApp->GetDevice()->LightEnable(0, FALSE);
		this->m_bLight0 = false;
	}
}

void CLights::SetGameMain(bool bActive)
{
	// activate light
	if(bActive)
	{
		this->m_pTheApp->GetDevice()->SetLight(0, &this->m_LightGameMain);
		this->m_pTheApp->GetDevice()->LightEnable(0, TRUE);
		this->m_bLight0 = true;
	}
	// deactivate light
	else
	{
		this->m_pTheApp->GetDevice()->LightEnable(0, FALSE);
		this->m_bLight0 = false;
	}
}

void CLights::SetGamePlayerBlast(	bool bActive,
									D3DXVECTOR3 posPlayer)
{
	// set light position
	if(bActive)
	{
		posPlayer.z -= 50.0f;

		this->m_LightGamePlayerBlastHigh.Position = posPlayer;
		this->m_LightGamePlayerBlastLow.Position = posPlayer;

		this->m_bPlayerBlastUpdateStart = true;
	}
	// deactivate light
	else
	{
		switch(this->m_iPlayerBlastLight)
		{
		case 1:
			this->m_pTheApp->GetDevice()->LightEnable(1, FALSE);
			this->m_bLight1 = false;
			break;

		case 2:
			this->m_pTheApp->GetDevice()->LightEnable(2, FALSE);
			this->m_bLight2 = false;
			break;

		case 3:
			this->m_pTheApp->GetDevice()->LightEnable(3, FALSE);
			this->m_bLight3 = false;
			break;

		case 4:
			this->m_pTheApp->GetDevice()->LightEnable(4, FALSE);
			this->m_bLight4 = false;
			break;

		case 5:
			this->m_pTheApp->GetDevice()->LightEnable(5, FALSE);
			this->m_bLight5 = false;
			break;

		case 6:
			this->m_pTheApp->GetDevice()->LightEnable(6, FALSE);
			this->m_bLight6 = false;
			break;
		}

		this->m_iPlayerBlastLight = 0;
	}
}

void CLights::UpdateGamePlayerBlast(CPlayer::eBLAST_LIGHT eBlastLight)
{
	if(this->m_bPlayerBlastUpdateStart)
	{
		this->m_bPlayerBlastUpdateStart = false;

		if(!this->m_bLight1)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(1, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(1, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(1, TRUE);

			this->m_iPlayerBlastLight = 1;
			this->m_bLight1 = true;
		}
		else if(!this->m_bLight2)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(2, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(2, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(2, TRUE);

			this->m_iPlayerBlastLight = 2;
			this->m_bLight2 = true;
		}
		else if(!this->m_bLight3)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(3, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(3, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(3, TRUE);

			this->m_iPlayerBlastLight = 3;
			this->m_bLight3 = true;
		}
		else if(!this->m_bLight4)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(4, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(4, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(4, TRUE);

			this->m_iPlayerBlastLight = 4;
			this->m_bLight4 = true;
		}
		else if(!this->m_bLight5)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(5, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(5, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(5, TRUE);

			this->m_iPlayerBlastLight = 5;
			this->m_bLight5 = true;
		}
		else if(!this->m_bLight6)
		{
			switch(eBlastLight)
			{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(6, &this->m_LightGamePlayerBlastHigh);
				break;

			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(6, &this->m_LightGamePlayerBlastLow);
				break;
			}
			
			this->m_pTheApp->GetDevice()->LightEnable(6, TRUE);

			this->m_iPlayerBlastLight = 6;
			this->m_bLight6 = true;
		}
	}
	else
	{
		//this->m_pTheApp->GetDevice()->LightEnable(this->m_iPlayerBlastLight, FALSE);

		switch(eBlastLight)
		{
			case CPlayer::eBLAST_LIGHT_HIGH:
				this->m_pTheApp->GetDevice()->SetLight(	this->m_iPlayerBlastLight, 
														&this->m_LightGamePlayerBlastHigh);
				break;
			
			case CPlayer::eBLAST_LIGHT_LOW:
				this->m_pTheApp->GetDevice()->SetLight(	this->m_iPlayerBlastLight,
														&this->m_LightGamePlayerBlastLow);
				break;
		}

		//this->m_pTheApp->GetDevice()->LightEnable(this->m_iPlayerBlastLight, TRUE);
	}
}

int CLights::GetLightCount()
{
	int iCount = 0;

	if(this->m_bLight0)
	{
		iCount++;
	}
	if(this->m_bLight1)
	{
		iCount++;
	}
	if(this->m_bLight2)
	{
		iCount++;
	}
	if(this->m_bLight3)
	{
		iCount++;
	}
	if(this->m_bLight4)
	{
		iCount++;
	}
	if(this->m_bLight5)
	{
		iCount++;
	}
	if(this->m_bLight6)
	{
		iCount++;
	}

	return iCount;
}

int* CLights::GetLightIndex()
{
	int* pActiveLights;
	int iCount = 0;

	// first count how many lights are active

	if(this->m_bLight0)
	{
		iCount++;
	}
	if(this->m_bLight1)
	{
		iCount++;
	}
	if(this->m_bLight2)
	{
		iCount++;
	}
	if(this->m_bLight3)
	{
		iCount++;
	}
	if(this->m_bLight4)
	{
		iCount++;
	}
	if(this->m_bLight5)
	{
		iCount++;
	}
	if(this->m_bLight6)
	{
		iCount++;
	}

	pActiveLights = new int[iCount];

	// now an index marker
	iCount = 0;

	if(this->m_bLight0)
	{
		pActiveLights[iCount] = 0;
		iCount++;
	}
	if(this->m_bLight1)
	{
		pActiveLights[iCount] = 1;
		iCount++;
	}
	if(this->m_bLight2)
	{
		pActiveLights[iCount] = 2;
		iCount++;
	}
	if(this->m_bLight3)
	{
		pActiveLights[iCount] = 3;
		iCount++;
	}
	if(this->m_bLight4)
	{
		pActiveLights[iCount] = 4;
		iCount++;
	}
	if(this->m_bLight5)
	{
		pActiveLights[iCount] = 5;
		iCount++;
	}
	if(this->m_bLight6)
	{
		pActiveLights[iCount] = 6;
		iCount++;
	}

	return pActiveLights;
}
