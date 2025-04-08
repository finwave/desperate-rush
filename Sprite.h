#pragma once

#include <iostream>

// Forward declaration
class CTheApp;

class CSprite
{
public:

	CSprite(void);
	~CSprite(void);

	HRESULT Create(	std::string fileName,
					LPDIRECT3DDEVICE9 pDevice,
					float fDepth);

	void Release();

	void Draw(	int x,
				int y);

	inline void SetDepth(float fDepth) { this->m_fDepth = fDepth; }
	static inline void SetCurrentFilePath(std::string path) { s_CurrentFilePath = path; }

private:

	HRESULT Create(	LPCTSTR fileName,
					LPDIRECT3DDEVICE9 pDevice,
					float fDepth);

	void Render(float x,
				float y,
				float sx,
				float sy,
				float angle,
				unsigned char alpha,
				RECT *rc);

	ID3DXSprite*		m_pSpriteDrawer;
	LPDIRECT3DTEXTURE9	m_sprite;
	float				m_fDepth;

	static std::string	s_CurrentFilePath;
};