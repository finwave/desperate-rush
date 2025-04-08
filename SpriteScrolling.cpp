#include "TheApp.h"
#include "TextUtils.h"
#include "SpriteScrolling.h"

std::string CSpriteScrolling::s_CurrentFilePath = "";

CSpriteScrolling::CSpriteScrolling(void)
{
	this->m_pSpriteDrawer = NULL;
	this->m_sprite = NULL;

	this->m_eDirection = eDIRECTION_DOWN;

	this->m_bRepeat = false;
	this->m_bOutOfBorder = false;

	this->m_fDepth = 0.0f;

	// game resolution is 1024x768
	this->m_iScreenWidth = 1024;
	this->m_iScreenHeight = 768;

	this->m_iOffset1 = 0;
	this->m_iOffset2 = 0;

	this->m_iSpriteWidth = 0;
	this->m_iSpriteHeight = 0;
	this->m_iStartPositionX = 0;
	this->m_iStartPositionY = 0;
	this->m_iPositionX = 0;
	this->m_iPositionY = 0;
	this->m_iSpeed = 0;
	this->m_iDefaultSpeed = 0;
	this->m_iMaxPause = 0;
	this->m_iPause = 0;
}

CSpriteScrolling::~CSpriteScrolling(void)
{
}

HRESULT CSpriteScrolling::Create(	std::string fileName,
									LPDIRECT3DDEVICE9 pDevice,
									eDIRECTION eDirection,
									bool bRepeat,
									float fDepth,
									int iSpriteWidth,
									int iSpriteHeight,
									int iPositionX,
									int iPositionY,
									int iSpeed,
									int iMaxPause)
{
	HRESULT hres;
	LPCTSTR filePath = TextUtils::CombineStrings_LPCTSTR(CSpriteScrolling::s_CurrentFilePath, fileName);

	this->m_eDirection = eDirection;
	this->m_bRepeat = bRepeat;

	this->m_fDepth = fDepth;

	this->m_iSpriteWidth = iSpriteWidth;
	this->m_iSpriteHeight = iSpriteHeight;

	this->m_iStartPositionX = iPositionX;
	this->m_iStartPositionY = iPositionY;
	this->m_iPositionX = iPositionX;
	this->m_iPositionY = iPositionY;

	this->m_iSpeed = iSpeed;
	this->m_iDefaultSpeed = iSpeed;
	this->m_iMaxPause = iMaxPause;
	this->m_iPause = this->m_iMaxPause;

	hres = D3DXCreateSprite(pDevice, &m_pSpriteDrawer);
	if (FAILED(hres))
	{
		return hres;
	}

	hres = D3DXCreateTextureFromFileEx(
		pDevice,
		filePath,
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

	if (FAILED(hres))
	{
		// failed to load sprite
		return hres;
	}

	return S_OK;
}

void CSpriteScrolling::Release()
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

void CSpriteScrolling::Draw(bool bForcedStop)
{
	// moves sprite only one time to designated direction
	// doesn't repeat sprite movement
	if(!this->m_bRepeat)
	{
		if(!this->m_bOutOfBorder)
		{
			// check if sprite is moved out of border
			switch(this->m_eDirection)
			{
			case eDIRECTION_UP:

				if( (m_iStartPositionY - this->m_iOffset1) < -(this->m_iSpriteHeight) )
				{
					this->m_bOutOfBorder = true;
				}
				break;

			case eDIRECTION_DOWN:

				if( (m_iStartPositionY + this->m_iOffset1) > m_iScreenHeight )
				{
					this->m_bOutOfBorder = true;
				}
				break;

			case eDIRECTION_LEFT:

				if( (m_iStartPositionX - this->m_iOffset1) < -(this->m_iSpriteWidth) )
				{
					this->m_bOutOfBorder = true;
				}
				break;

			case eDIRECTION_RIGHT:

				if( (m_iStartPositionX + this->m_iOffset1) > m_iScreenWidth )
				{
					this->m_bOutOfBorder = true;
				}
				break;
			}

			// render sprite
			this->RenderNonRepeat(1.00f, 1.00f, 0, 255);
		}
	}

	// repeat sprite movement towards designated direction
	// selects rectangular areas of the sprite to display
	// sprite width/height needs to be larger than the screen width/height

	else if(this->m_bRepeat)
	{
		RECT rct;
		// position of the sprite to be drawn
		D3DXVECTOR3 pos;
		pos.z = this->m_fDepth;

		switch(this->m_eDirection)
		{
		case eDIRECTION_UP:

			// x-coordinate value doesn't change
			pos.x = this->m_iStartPositionX;

			rct.left = 0;
			rct.right = this->m_iSpriteWidth;


			// first offset is higher than sprite height - screen height
			if( this->m_iOffset1 > (this->m_iSpriteHeight - this->m_iScreenHeight) )
			{
				if( this->m_iPause == 0 )
				{
					if(!bForcedStop)
					{
						// increment second offset
						this->m_iOffset2 += this->m_iSpeed;
					}
				}

				// top sprite

				rct.top = this->m_iOffset1;
				rct.bottom = this->m_iSpriteHeight;

				pos.y = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);

				// bottom sprite

				rct.top = 0;
				rct.bottom = this->m_iScreenHeight + this->m_iOffset2;

				pos.y = this->m_iScreenHeight - this->m_iOffset2;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}
			else
			{
				// top sprite

				rct.top = this->m_iOffset1;
				rct.bottom = this->m_iScreenHeight + this->m_iOffset1;

				pos.y = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}

			break;

		case eDIRECTION_DOWN:

			// x-coordinate value doesn't change
			pos.x = this->m_iStartPositionX;

			rct.left = 0;
			rct.right = this->m_iSpriteWidth;

			// first offset is higher than sprite height - screen height
			if( this->m_iOffset1 > (this->m_iSpriteHeight - this->m_iScreenHeight) )
			{
				if( this->m_iPause == 0 )
				{
					if(!bForcedStop)
					{
						// increment second offset
						this->m_iOffset2 += this->m_iSpeed;
					}
				}

				// bottom sprite

				rct.top = 0;
				rct.bottom = this->m_iScreenHeight - this->m_iOffset2;

				pos.y = this->m_iOffset2;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);

				// top sprite

				rct.top = this->m_iSpriteHeight - this->m_iOffset2 - 1;
				rct.bottom = this->m_iSpriteHeight;

				pos.y = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}
			else
			{
				// bottom sprite

				rct.top = (this->m_iSpriteHeight - this->m_iScreenHeight) - this->m_iOffset1;
				rct.bottom = this->m_iSpriteHeight - this->m_iOffset1;

				pos.y = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}

			break;

		case eDIRECTION_LEFT:

			// y-coordinate value doesn't change
			pos.y = this->m_iStartPositionY;

			rct.top = 0;
			rct.bottom = this->m_iSpriteHeight;

			// first offset is higher than sprite width - screen width
			if( this->m_iOffset1 > (this->m_iSpriteWidth - this->m_iScreenWidth) )
			{
				if( this->m_iPause == 0 )
				{
					if(!bForcedStop)
					{
						// increment second offset
						this->m_iOffset2 += this->m_iSpeed;
					}
				}

				// left sprite

				rct.left = this->m_iOffset1;
				rct.right = this->m_iSpriteWidth;

				pos.x = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);

				// right sprite

				rct.left = 0;
				rct.right = this->m_iOffset2;

				pos.x = this->m_iScreenWidth - this->m_iOffset2;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}
			else
			{
				// left sprite

				rct.left = this->m_iOffset1;
				rct.right = this->m_iScreenWidth + this->m_iOffset1;

				pos.x = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}

			break;

		case eDIRECTION_RIGHT:

			// y-coordinate value doesn't change
			pos.y = this->m_iStartPositionY;

			rct.top = 0;
			rct.bottom = this->m_iSpriteHeight;

			// first offset is higher than sprite width - screen width
			if( this->m_iOffset1 > (this->m_iSpriteWidth - this->m_iScreenWidth) )
			{
				if( this->m_iPause == 0 )
				{
					if(!bForcedStop)
					{
						// increment second offset
						this->m_iOffset2 += this->m_iSpeed;
					}
				}

				// right sprite

				rct.left = 0;
				rct.right = this->m_iScreenWidth - this->m_iOffset2;

				pos.x = this->m_iOffset2;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);

				// left sprite

				rct.left = this->m_iSpriteWidth - this->m_iOffset2 - 1;
				rct.right = this->m_iSpriteWidth;

				pos.x = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}
			else
			{
				// right sprite

				rct.left = (this->m_iSpriteWidth - this->m_iScreenWidth) - this->m_iOffset1;
				rct.right = this->m_iSpriteWidth - this->m_iOffset1;

				pos.x = 0;

				// render sprite
				this->RenderRepeat(&rct, &pos, 255);
			}

			break;
		}
	}

	if( this->m_iPause == 0 )
	{
		// reset pause to max value
		this->m_iPause = this->m_iMaxPause;

		// non-repeating sprite
		if(!this->m_bRepeat)
		{
			if(!bForcedStop)
			{
				this->m_iOffset1 += this->m_iSpeed;
			}

			// update sprite position
			switch(this->m_eDirection)
			{
			case eDIRECTION_UP:
				this->m_iPositionY = m_iStartPositionY - this->m_iOffset1;
				break;

			case eDIRECTION_DOWN:
				this->m_iPositionY = m_iStartPositionY + this->m_iOffset1;
				break;

			case eDIRECTION_LEFT:
				this->m_iPositionX = m_iStartPositionX - this->m_iOffset1;
				break;

			case eDIRECTION_RIGHT:
				this->m_iPositionX = m_iStartPositionX + this->m_iOffset1;
				break;
			}
		}
		// repeating sprite
		else
		{
			// sprite moving up or down
			if(	(this->m_eDirection == eDIRECTION_UP) || 
					(this->m_eDirection == eDIRECTION_DOWN) )
			{
				// increment first offset
				if( (this->m_iOffset1 + this->m_iSpeed) >= (this->m_iSpriteHeight - this->m_iSpeed) )
				{
					this->m_iOffset1 = 0;
					this->m_iOffset2 = 0;
				}
				else
				{
					if(!bForcedStop)
					{
						this->m_iOffset1 += this->m_iSpeed;
					}
				}
			}
			// sprite moving left or right
			else if(	(this->m_eDirection == eDIRECTION_LEFT) || 
						(this->m_eDirection == eDIRECTION_RIGHT) )
			{
				// increment first offset
				if( (this->m_iOffset1 + this->m_iSpeed) >= (this->m_iSpriteWidth - this->m_iSpeed) )
				{
					this->m_iOffset1 = 0;
					this->m_iOffset2 = 0;
				}
				else
				{
					if(!bForcedStop)
					{
						this->m_iOffset1 += this->m_iSpeed;
					}
				}
			}
		}
	}
	else
	{
		if(!bForcedStop)
		{
			// decrease pause
			this->m_iPause--;
		}
	}
}

void CSpriteScrolling::Reset()
{
	this->m_iPositionX = this->m_iStartPositionX;
	this->m_iPositionY = this->m_iStartPositionY;

	this->m_iOffset1 = 0;
	this->m_iOffset2 = 0;
	
	this->m_iPause = this->m_iMaxPause;
}

// this method is only meant for non-repeating sprites
void CSpriteScrolling::RenderNonRepeat(	float sx,
										float sy,
										float angle,
										unsigned char alpha)
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

	D3DXMatrixTranslation(	&translate,
							this->m_iPositionX,
							this->m_iPositionY,
							this->m_fDepth);

	D3DXMatrixMultiply(&result, &result, &translate);

	this->m_pSpriteDrawer->SetTransform(&result);
	this->m_pSpriteDrawer->Draw(this->m_sprite, NULL, NULL, NULL, (0xFFFFFF) | (alpha << 24));
	this->m_pSpriteDrawer->End();
}

// this method is only meant for repeating sprites
void CSpriteScrolling::RenderRepeat(RECT *rct,
									D3DXVECTOR3 *pos,
									unsigned char alpha)
{
	this->m_pSpriteDrawer->Begin(D3DXSPRITE_ALPHABLEND);
	this->m_pSpriteDrawer->Draw(this->m_sprite, rct, NULL, pos, (0xFFFFFF) | (alpha << 24));
	this->m_pSpriteDrawer->End();
}
