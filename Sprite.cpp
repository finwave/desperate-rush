#include "TheApp.h"
#include "TextUtils.h"
#include "Sprite.h"

std::string CSprite::s_CurrentFilePath = "";

CSprite::CSprite(void)
{
	this->m_pSpriteDrawer = NULL;
	this->m_sprite = NULL;
	this->m_fDepth = 0.0f;
}

CSprite::~CSprite(void)
{
}

HRESULT CSprite::Create(std::string fileName,
						LPDIRECT3DDEVICE9 pDevice,
						float fDepth)
{
	LPCTSTR filePath = TextUtils::CombineStrings_LPCTSTR(CSprite::s_CurrentFilePath, fileName);
	return Create(filePath, pDevice, fDepth);
}

HRESULT CSprite::Create(LPCTSTR fileName,
						LPDIRECT3DDEVICE9 pDevice,
						float fDepth)
{
	HRESULT hres;

	this->m_fDepth = fDepth;

	hres = D3DXCreateSprite(pDevice, &m_pSpriteDrawer);
	if(FAILED(hres))
	{
		return hres;
	}

	hres = D3DXCreateTextureFromFileEx(
		pDevice,
		fileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
		NULL,
		NULL,
		&m_sprite);

	if(FAILED(hres))
	{
		// failed to load sprite
		return hres;
	}

	return S_OK;
}

void CSprite::Release()
{
	if(this->m_sprite)
	{
		this->m_sprite->Release();
		this->m_sprite = NULL;
	}
	if(this->m_pSpriteDrawer)
	{
		this->m_pSpriteDrawer->Release();
		this->m_pSpriteDrawer = NULL;
	}
}

void CSprite::Draw(	int x,
					int y)
{
	if (this->m_pSpriteDrawer)
	{
		Render(x, y, 1.00f, 1.00f, 0, 255, NULL);
	}
}

void CSprite::Render(float x, float y, float sx, float sy, float angle,
						 unsigned char alpha, RECT *rc)
{
	D3DXMATRIX rotate;
	D3DXMATRIX translate;
	D3DXMATRIX scale;
	D3DXMATRIX result;

	this->m_pSpriteDrawer->Begin(D3DXSPRITE_ALPHABLEND);

	D3DSURFACE_DESC desc;
	this->m_sprite->GetLevelDesc(0, &desc);

	const int halfWidth = desc.Width >> 1;
	const int halfHeight = desc.Height >> 1;

	D3DXMatrixIdentity(&result);

	D3DXMatrixTranslation(&translate, -halfWidth, -halfHeight, 0);
	D3DXMatrixMultiply(&result, &result, &translate);

	D3DXMatrixScaling(&scale, sx, sy, 1.0f);
	D3DXMatrixMultiply(&result, &result, &scale);

	D3DXMatrixRotationZ(&rotate, D3DXToRadian(angle));
	D3DXMatrixMultiply(&result, &result, &rotate);

	D3DXMatrixTranslation(&translate, +halfWidth, +halfHeight, 0);
	D3DXMatrixMultiply(&result, &result, &translate);

	D3DXMatrixTranslation(&translate, x, y, this->m_fDepth);
	D3DXMatrixMultiply(&result, &result, &translate);

	this->m_pSpriteDrawer->SetTransform(&result);
	this->m_pSpriteDrawer->Draw(this->m_sprite, rc, NULL, NULL, (0xFFFFFF) | (alpha << 24));
	this->m_pSpriteDrawer->End();
}
