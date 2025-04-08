#pragma once

#include <iostream>

// Forward declaration
class CTheApp;

class CSpriteScrolling
{
public:
	enum eDIRECTION
	{
		eDIRECTION_UP,
		eDIRECTION_DOWN,
		eDIRECTION_LEFT,
		eDIRECTION_RIGHT
	};

	CSpriteScrolling(void);
	~CSpriteScrolling(void);

	HRESULT Create(	std::string fileName,
					LPDIRECT3DDEVICE9 pDevice,
					eDIRECTION eDirection,
					bool bRepeat,
					float fDepth,
					int iSpriteWidth,
					int iSpriteHeight,
					int iPositionX,
					int iPositionY,
					int iSpeed,
					int iMaxPause);

	void Release();

	void Draw(bool bForcedStop);

	void Reset();

	inline int GetSpeed() { return this->m_iSpeed; }
	inline void SetSpeed(int iSpeed) { this->m_iSpeed = iSpeed; }
	inline void IncreaseSpeed() { this->m_iSpeed++; }
	inline void DecreaseSpeed() { this->m_iSpeed--; }

	inline int GetDefaultSpeed() { return this->m_iDefaultSpeed; }
	inline void SetDefaultSpeed(int iSpeed) { this->m_iDefaultSpeed = iSpeed; }

	inline int GetMaxPause() { return this->m_iMaxPause; }
	inline void SetMaxPause(int iMaxPause) { this->m_iMaxPause = iMaxPause; }
	inline void IncreaseMaxPause() { this->m_iMaxPause++; }
	inline void DecreaseMaxPause() { this->m_iMaxPause--; }

	inline bool IsOutOfBorder() { return this->m_bOutOfBorder = true; }

	inline int GetPositionX() { return this->m_iPositionX; }
	inline int GetPositionY() { return this->m_iPositionY; }

	inline int GetSpriteWidth() { return this->m_iSpriteWidth; }
	inline int GetSpriteHeight() { return this->m_iSpriteHeight; }

	static inline void SetCurrentFilePath(std::string path) { s_CurrentFilePath = path; }

private:

	void RenderNonRepeat(	float sx,
							float sy,
							float angle,
							unsigned char alpha);

	void RenderRepeat(	RECT *rct,
						D3DXVECTOR3 *pos,
						unsigned char alpha);

	ID3DXSprite*		m_pSpriteDrawer;
	LPDIRECT3DTEXTURE9	m_sprite;

	eDIRECTION			m_eDirection;

	bool				m_bRepeat;
	bool				m_bOutOfBorder;

	float				m_fDepth;

	int					m_iScreenWidth;
	int					m_iScreenHeight;

	int					m_iOffset1;
	int					m_iOffset2;

	int					m_iSpriteWidth;
	int					m_iSpriteHeight;
	int					m_iStartPositionX;
	int					m_iStartPositionY;
	int					m_iPositionX;
	int					m_iPositionY;
	int					m_iSpeed;
	int					m_iDefaultSpeed;
	int					m_iMaxPause;
	int					m_iPause;

	static std::string	s_CurrentFilePath;
};