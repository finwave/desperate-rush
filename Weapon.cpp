#include "Weapon.h"

std::vector<CSprite> CWeapon::s_SpritesGame;
std::vector<CSprite> CWeapon::s_SpritesHighscore;

CWeapon::CWeapon(void)
{
	this->m_eOwner = eOWNER_PLAYER;
	this->m_eDamageType = ONLY_SHOTED_OBJECT;
	this->m_eBulletPlace = eBULLET_PLACE_INNER;

	this->m_fMove = 0.0f;
	this->m_fWidth = 0.0f;
	this->m_fHeight = 0.0f;
	this->m_fSpeed = 0.0f;
	this->m_iDamage = 0;

	this->m_fScreenPixelWidth = 1024.0f;
	this->m_fScreenPixelHeight = 768.0f;
}

CWeapon::~CWeapon(void)
{
}

HRESULT CWeapon::Create(LPDIRECT3DDEVICE9 pDevice,
						LPD3DXMESH mesh,
						std::vector<D3DMATERIAL9*> materials,
						std::vector<LPDIRECT3DTEXTURE9> textures,
						float fWidth,
						float fHeight,
						float fSpeed,
						int iDamage,
						eBULLET_TYPE eBulletType)
{
	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	this->Create(pDevice, fWidth, fHeight, fSpeed, iDamage, eBulletType);

	return S_OK;
}

HRESULT CWeapon::Create(LPDIRECT3DDEVICE9 pDevice,
						LPD3DXMESH mesh,
						std::vector<MESHDATA>& meshData,
						float fWidth,
						float fHeight,
						float fSpeed,
						int iDamage,
						eBULLET_TYPE eBulletType)
{
	C3DObject::Create(mesh);

	this->m_arrMeshData = meshData;

	this->Create(pDevice, fWidth, fHeight, fSpeed, iDamage, eBulletType);

	return S_OK;
}

void CWeapon::Create(LPDIRECT3DDEVICE9 pDevice,
					float fWidth,
					float fHeight,
					float fSpeed,
					int iDamage,
					eBULLET_TYPE eBulletType)
{
	this->m_pDevice = pDevice;

	this->m_fWidth = fWidth;
	this->m_fHeight = fHeight;
	this->m_fSpeed = fSpeed;
	this->m_iDamage = iDamage;

	this->m_eBulletType = eBulletType;
}

void CWeapon::Release()
{
	C3DObject::Release();
}

void CWeapon::Update(float fFrametime, float fPlayerVelocity)
{
	float fMove = this->m_fSpeed * fFrametime;
	D3DXVECTOR3 pos = this->GetPosition();

	switch ( this->m_eOwner )
	{
	case eOWNER_PLAYER:

		if(this->m_eBulletType == eBULLET_TYPE_PLAYER_HIGHSCORE)
		{
			pos.x += fMove;
		}
		else
		{
			pos.y += fMove;
		}

		break;

	case eOWNER_ENEMY:

		// boss bullets will be moved in their own classes
		if( (this->m_eBulletType != eBULLET_TYPE_BOSS_1_LASER) && 
			(this->m_eBulletType != eBULLET_TYPE_BOSS_1_SCATTER))
		{
			pos.y -= fMove;
			pos.y -= fPlayerVelocity * fFrametime;
		}

		break;
	}

	this->SetPosition(pos);

	C3DObject::Update(fFrametime);
}

void CWeapon::DrawSpriteBulletPlayer(	D3DXVECTOR3 posLeft,
										D3DXVECTOR3 posRight,
										bool bBulletLeft,
										bool bBulletRight)
{
	int spriteIndex;

	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosLeftX;
	int iPosRightX;
	int iPosX;
	int iPosY;

	// HIGHSCORE BULLETS
	if(this->m_eBulletType == eBULLET_TYPE_PLAYER_HIGHSCORE)
	{
		spriteIndex = CResources::SPRITE_HIGHSCORE_BULLET_PLAYER_MINIGUN - CResources::SPRITE_HIGHSCORE_BULLET_FIRST;

		if(bBulletLeft)
		{
			fMoveX = posLeft.x * fPixelMultiplier;
			iPosX = ( (this->m_fScreenPixelWidth / 2) - 14.0f) + fMoveX;

			fMoveY = posLeft.y * fPixelMultiplier;
			fMoveY = fMoveY * -1.0f;

			iPosY = ( (this->m_fScreenPixelHeight / 2) - 14.0f) + fMoveY;

			iPosY += 6;

			// draw left bullet
			s_SpritesHighscore.at(spriteIndex).Draw(iPosX, iPosY);
		}
		if(bBulletRight)
		{
			fMoveX = posRight.x * fPixelMultiplier;
			iPosX = ( (this->m_fScreenPixelWidth / 2) - 14.0f) + fMoveX;

			fMoveY = posRight.y * fPixelMultiplier;
			fMoveY = fMoveY * -1.0f;

			iPosY = ( (this->m_fScreenPixelHeight / 2) - 14.0f) + fMoveY;

			iPosY -= 3;

			// draw right bullet
			s_SpritesHighscore.at(spriteIndex).Draw(iPosX, iPosY);
		}
	}
	// GAME BULLETS
	else
	{
		// left bullet x-position

		pos = posLeft;

		fMoveX = pos.x * fPixelMultiplier;
		iPosLeftX = ( (this->m_fScreenPixelWidth / 2) - 11.0f) + fMoveX;

		// right bullet x-position

		pos = posRight;

		fMoveX = pos.x * fPixelMultiplier;
		iPosRightX = ( (this->m_fScreenPixelWidth / 2) - 10.0f) + fMoveX;

		// left and right bullets y-position

		fMoveY = pos.y * fPixelMultiplier;
		fMoveY = fMoveY * -1.0f;

		iPosY = ( (this->m_fScreenPixelHeight / 2) - 14.0f) + fMoveY;

		// fine-tune bullet positions and draw

		switch (this->m_eBulletType)
		{
		case eBULLET_TYPE_PLAYER_FRONT:

			spriteIndex = CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_FRONT - CResources::SPRITE_GAME_BULLET_FIRST;

			switch (this->m_eBulletPlace)
			{
			case eBULLET_PLACE_INNER:

				iPosLeftX += 2;
				iPosRightX -= 1;

				break;

			case eBULLET_PLACE_OUTER:

				iPosLeftX += 4;
				iPosRightX -= 2;
				iPosY += 1;

				break;
			}

			// draw left bullet
			if (bBulletLeft) {
				s_SpritesGame.at(spriteIndex).Draw(iPosLeftX, iPosY);
			}
			// draw right bullet
			if (bBulletRight) {
				s_SpritesGame.at(spriteIndex).Draw(iPosRightX, iPosY);
			}

			break;

		case eBULLET_TYPE_PLAYER_DIAGONAL:

			switch (this->m_eBulletPlace)
			{
			case eBULLET_PLACE_INNER:

				iPosLeftX += 13;
				iPosRightX -= 14;
				iPosY += 1;

				break;

			case eBULLET_PLACE_OUTER:

				iPosLeftX += 7;
				iPosRightX -= 10;
				iPosY += 1;

				break;
			}

			// draw left bullet
			if (bBulletLeft)
			{
				spriteIndex = CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_LEFT - CResources::SPRITE_GAME_BULLET_FIRST;
				s_SpritesGame.at(spriteIndex).Draw(iPosLeftX, iPosY);
			}
			// draw right bullet
			if (bBulletRight)
			{
				spriteIndex = CResources::SPRITE_GAME_BULLET_PLAYER_MINIGUN_RIGHT - CResources::SPRITE_GAME_BULLET_FIRST;
				s_SpritesGame.at(spriteIndex).Draw(iPosRightX, iPosY);
			}

			break;
		}
	}
}

void CWeapon::DrawSpriteBulletDrone()
{
	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	// bullet x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosX = ( (this->m_fScreenPixelWidth / 2) - 12.0f) + fMoveX;

	// bullet y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = ( (this->m_fScreenPixelHeight / 2) - 12.0f) + fMoveY;

	// draw bullet
	int spriteIndex = CResources::SPRITE_GAME_BULLET_DRONE - CResources::SPRITE_GAME_BULLET_FIRST;
	s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);
}

void CWeapon::DrawSpriteBulletSniper()
{
	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	// bullet x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosX = ( (this->m_fScreenPixelWidth / 2) - 14.0f) + fMoveX;

	// bullet y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = ( (this->m_fScreenPixelHeight / 2) - 21.0f) + fMoveY;

	// draw bullet
	int spriteIndex = CResources::SPRITE_GAME_BULLET_SNIPER - CResources::SPRITE_GAME_BULLET_FIRST;
	s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);
}

void CWeapon::DrawSpriteBulletRoller()
{
	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	// bullet x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosX = (this->m_fScreenPixelWidth / 2) + fMoveX;

	// bullet y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = (this->m_fScreenPixelHeight / 2) + fMoveY;

	iPosX -= 12;
	iPosY -= 12;

	// draw bullet
	int spriteIndex = CResources::SPRITE_GAME_BULLET_ROLLER - CResources::SPRITE_GAME_BULLET_FIRST;
	s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);
}

void CWeapon::DrawSpriteBulletGuard()
{
}

void CWeapon::DrawSpriteBulletBoss1Laser()
{
	int spriteIndex;
	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	// bullet x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosX = (this->m_fScreenPixelWidth / 2) + fMoveX;

	// bullet y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = (this->m_fScreenPixelHeight / 2) + fMoveY;

	switch(this->m_eDirection)
	{
	case eDIRECTION_DOWN:

		iPosX -= 13;
		iPosY -= 23;

		// draw bullet
		spriteIndex = CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_DOWN - CResources::SPRITE_GAME_BULLET_FIRST;
		s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);

		break;

	case eDIRECTION_DOWN_LEFT:

		iPosX -= 17;
		iPosY -= 19;

		// draw bullet
		spriteIndex = CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_LEFT - CResources::SPRITE_GAME_BULLET_FIRST;
		s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);

		break;

	case eDIRECTION_DOWN_RIGHT:

		iPosX -= 18;
		iPosY -= 19;

		spriteIndex = CResources::SPRITE_GAME_BULLET_BOSS_1_LASER_RIGHT - CResources::SPRITE_GAME_BULLET_FIRST;
		s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);

		break;
	}
}

void CWeapon::DrawSpriteBulletBoss1Scatter()
{
	const float fPixelMultiplier = 2.5f;

	D3DXVECTOR3 pos;

	float fMoveX;
	float fMoveY;

	int iPosX;
	int iPosY;

	// bullet x-position

	pos = this->GetPosition();

	fMoveX = pos.x * fPixelMultiplier;
	iPosX = (this->m_fScreenPixelWidth / 2) + fMoveX;

	// bullet y-position

	fMoveY = pos.y * fPixelMultiplier;
	fMoveY = fMoveY * -1.0f;

	iPosY = (this->m_fScreenPixelHeight / 2) + fMoveY;

	iPosX -= 12;
	iPosY -= 12;

	// draw bullet
	int spriteIndex = CResources::SPRITE_GAME_BULLET_BOSS_1_SCATTER - CResources::SPRITE_GAME_BULLET_FIRST;
	s_SpritesGame.at(spriteIndex).Draw(iPosX, iPosY);
}

D3DXVECTOR3* CWeapon::GetBulletPosition()
{
	D3DXVECTOR3* pPos;

	switch ( this->GetBulletType() )
	{
	case eBULLET_TYPE_PLAYER_HIGHSCORE:

		pPos = new D3DXVECTOR3[3];

		pPos[0] = this->GetPosition();

		pPos[1] = D3DXVECTOR3(	this->GetPosition().x,
								this->GetPosition().y + 8.0f,
								this->GetPosition().z);

		pPos[2] = D3DXVECTOR3(	this->GetPosition().x,
								this->GetPosition().y - 8.0f,
								this->GetPosition().z);

		break;

	case eBULLET_TYPE_PLAYER_FRONT:

		pPos = new D3DXVECTOR3[3];

		pPos[0] = this->GetPosition();

		switch (this->m_eBulletPlace)
		{
		case eBULLET_PLACE_INNER:

			pPos[1] = D3DXVECTOR3(	this->GetPosition().x - 8.0f,
									this->GetPosition().y,
									this->GetPosition().z);

			pPos[2] = D3DXVECTOR3(	this->GetPosition().x + 8.0f,
									this->GetPosition().y,
									this->GetPosition().z);
			break;	

		case eBULLET_PLACE_OUTER:

			pPos[1] = D3DXVECTOR3(	this->GetPosition().x - 12.0f,
									this->GetPosition().y,
									this->GetPosition().z);

			pPos[2] = D3DXVECTOR3(	this->GetPosition().x + 12.0f,
									this->GetPosition().y,
									this->GetPosition().z);
			break;
		}

		break;

	case eBULLET_TYPE_PLAYER_DIAGONAL:

		pPos = new D3DXVECTOR3[3];

		pPos[0] = this->GetPosition();

		switch (this->m_eBulletPlace)
		{
		case eBULLET_PLACE_INNER:

			pPos[1] = D3DXVECTOR3(	this->GetPosition().x - (this->m_fMove + 18.0f),
									this->GetPosition().y,
									this->GetPosition().z);

			pPos[2] = D3DXVECTOR3(	this->GetPosition().x + (this->m_fMove + 18.0f),
									this->GetPosition().y,
									this->GetPosition().z);
			break;	

		case eBULLET_PLACE_OUTER:

			pPos[1] = D3DXVECTOR3(	this->GetPosition().x - (this->m_fMove + 21.0f),
									this->GetPosition().y,
									this->GetPosition().z);

			pPos[2] = D3DXVECTOR3(	this->GetPosition().x + (this->m_fMove + 21.0f),
									this->GetPosition().y,
									this->GetPosition().z);
			break;
		}

		break;

	default:

		pPos = new D3DXVECTOR3[1];
		pPos[0] = this->GetPosition();

		break;
	}
	
	return pPos;
}

void CWeapon::DisableBullet(int iBullet)
{
	this->SetVisible(FALSE);
	this->SetActive(FALSE);
}

void CWeapon::SetLocalPosition(float x, float y, float z)
{
	this->SetPosition(D3DXVECTOR3(x, y, z));
}

void CWeapon::SetMatrix(C3DObject* pShip) {}

void CWeapon::InitDirection() {}
void CWeapon::InitPosition() {}
void CWeapon::InitRotation() {}

CWeapon* CWeapon::GetBulletLeft()
{
	return NULL;
}
CWeapon* CWeapon::GetBulletRight()
{
	return NULL;
}