#include "Obstacle.h"

CObstacle::CObstacle(void)
{
	this->m_pTheApp = NULL;

	this->m_fObstacleWidth = 0.0f;
	this->m_fObstacleHeight = 0.0f;

	this->m_fSpeed = 0.0f;

	this->m_fScreenWidth = 0.0f;
	this->m_fScreenHeight = 0.0f;

	this->m_fAngle = 0.0f;
	this->m_fAngleMultiplier = 0.0f;
	this->m_iRotationSelector = 0;

	this->m_bSpeedChange = false;
	this->m_fSpeedChangeMultiplier = 1.05f;
}

CObstacle::~CObstacle(void)
{
}

HRESULT CObstacle::Create(	CTheApp *pTheApp,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight)
{
	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	this->Create(pTheApp, fObstacleWidth, fObstacleHeight, fScreenWidth, fScreenHeight);

	return S_OK;
}

HRESULT CObstacle::Create(	CTheApp *pTheApp,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight)
{
	C3DObject::Create(mesh);

	this->m_arrMeshData = meshData;

	this->Create(pTheApp, fObstacleWidth, fObstacleHeight, fScreenWidth, fScreenHeight);

	return S_OK;
}

HRESULT CObstacle::Create(	CTheApp *pTheApp,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight)
{
	this->m_pTheApp = pTheApp;

	this->m_fObstacleWidth = fObstacleWidth;
	this->m_fObstacleHeight = fObstacleHeight;

	this->m_fScreenWidth = fScreenWidth;
	this->m_fScreenHeight = fScreenHeight;

	this->RotateDown();

	this->m_iRotationSelector = this->m_pTheApp->RandInt(1,8);

	return S_OK;
}

void CObstacle::Release(void)
{
	this->m_pTheApp = NULL;

	C3DObject::Release();
}

void CObstacle::Render(LPDIRECT3DDEVICE9 pDevice)
{
	C3DObject::Render(pDevice);
}

void CObstacle::Update(float fFrametime, float fPlayerVelocity)
{
	// rotate obstacle
	this->Rotate(fFrametime);
	
	// move obstacle
	if(this->m_bSpeedChange)
	{
		this->MoveSpeedChange(fFrametime, fPlayerVelocity);
	}
	else
	{
		this->MoveNormal(fFrametime, fPlayerVelocity);
	}

	// update object
	C3DObject::Update(fFrametime);
}

void CObstacle::InitObstacle(eOBSTACLE_DEPTH eDepth)
{
	this->m_eDepth = eDepth;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch(this->m_eDepth)
	{
	case eOBSTACLE_DEPTH_1:

		this->m_fAngleMultiplier = 0.8f;
		this->SetScale(1);

		break;

	case eOBSTACLE_DEPTH_2:

		//this->m_fObstacleWidth = this->m_fObstacleWidth * 0.6f;
		//this->m_fObstacleHeight = this->m_fObstacleHeight * 0.6f;

		this->m_fAngleMultiplier = 0.45f;
		this->SetScale(2);

		break;

	case eOBSTACLE_DEPTH_3:

		//this->m_fObstacleWidth = this->m_fObstacleWidth * 0.4f;
		//this->m_fObstacleHeight = this->m_fObstacleHeight * 0.4f;

		this->m_fAngleMultiplier = 0.35f;
		this->SetScale(3);

		break;

	case eOBSTACLE_DEPTH_4:

		//this->m_fObstacleWidth = this->m_fObstacleWidth * 0.25f;
		//this->m_fObstacleHeight = this->m_fObstacleHeight * 0.25f;

		this->m_fAngleMultiplier = 0.25f;
		this->SetScale(4);

		break;

	case eOBSTACLE_DEPTH_5:

		//this->m_fObstacleWidth = this->m_fObstacleWidth * 0.05f;
		//this->m_fObstacleHeight = this->m_fObstacleHeight * 0.05f;

		this->m_fAngleMultiplier = 0.15f;
		this->SetScale(5);

		break;
	}

	this->SetPosition(pos);
	this->SetDepth();
}

void CObstacle::RotateUp()
{
	D3DXMatrixRotationYawPitchRoll( &this->GetLocalMatrix(),
									D3DX_PI,
									D3DX_PI / 2,
									0.0f);
}

void CObstacle::RotateDown()
{
	D3DXMatrixRotationX(&this->GetLocalMatrix(), -(D3DX_PI / 2));
}

void CObstacle::Rotate(float fFrametime)
{
	D3DXVECTOR3 pos = this->GetPosition();
	this->m_fAngle += fFrametime * this->m_fAngleMultiplier;

	switch(this->m_iRotationSelector)
	{
	case 1:
		D3DXMatrixRotationY(&this->GetLocalMatrix(), this->m_fAngle);
		break;
	case 2:
		D3DXMatrixRotationYawPitchRoll(&this->GetLocalMatrix(), 15.0f, -this->m_fAngle, 0.0f);
		break;
	case 3:
		D3DXMatrixRotationX(&this->GetLocalMatrix(), -this->m_fAngle);
		break;
	case 4:
		D3DXMatrixRotationYawPitchRoll(&this->GetLocalMatrix(), 15.0f, this->m_fAngle, 0.0f);
		break;
	case 5:
		D3DXMatrixRotationY(&this->GetLocalMatrix(), -this->m_fAngle);
		break;
	case 6:
		D3DXMatrixRotationYawPitchRoll(&this->GetLocalMatrix(), -15.0f, -this->m_fAngle, 0.0f);
		break;
	case 7:
		D3DXMatrixRotationX(&this->GetLocalMatrix(), this->m_fAngle);
		break;
	case 8:
		D3DXMatrixRotationYawPitchRoll(&this->GetLocalMatrix(), -15.0f, this->m_fAngle, 0.0f);
		break;
	}

	this->SetPosition(pos);
}

void CObstacle::MoveNormal(float fFrametime, float fPlayerVelocity)
{
	D3DXVECTOR3 pos = this->GetPosition();

	float fFrameSpeed = fFrametime * (this->m_fSpeed + fPlayerVelocity);
	pos.y -= fFrameSpeed;

	this->SetPosition(pos);
}

void CObstacle::MoveSpeedChange(float fFrametime, float fPlayerVelocity)
{
	D3DXVECTOR3 pos = this->GetPosition();

	float fFrameSpeed = (fFrametime * this->m_fSpeed) * this->m_fSpeedChangeMultiplier;
	pos.y -= fFrameSpeed;

	float fVelocitySpeed = fFrametime * fPlayerVelocity;
	pos.y -= fVelocitySpeed;

	this->SetPosition(pos);

	this->m_fSpeedChangeMultiplier += 3.0f * fFrametime;
}

void CObstacle::SetDepth()
{
	D3DXVECTOR3 pos = this->GetPosition();
	float depth = this->GetDepthValue(1);

	switch(this->m_eDepth)
	{
	case eOBSTACLE_DEPTH_2:
		depth = this->GetDepthValue(6);
		break;

	case eOBSTACLE_DEPTH_3:
		depth = this->GetDepthValue(7);
		break;

	case eOBSTACLE_DEPTH_4:
		depth = this->GetDepthValue(8);
		break;

	case eOBSTACLE_DEPTH_5:
		depth = this->GetDepthValue(9);
		break;
	}

	pos.z = depth;
	this->SetPosition(pos);
}