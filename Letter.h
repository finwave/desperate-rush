#pragma once

#include "C3DObject.h"
#include "XFileContainer.h"

class CLetter: public C3DObject
{
public:
	enum eLETTER_TYPE
	{
		eLETTER_TYPE_MENUS,
		eLETTER_TYPE_GAME,
		eLETTER_TYPE_HIGHSCORE
	};

	CLetter(void);
	virtual ~CLetter(void);

	HRESULT Create(	LPD3DXMESH pMesh,
					CXFileContainer xFile,
					float fWidth,
					float fHeight,
					bool bMaterial,
					eLETTER_TYPE eLetterType);

	virtual void Release();
	void Update(float fFrametime);

	inline float GetWidth(void) { return this->m_fWidth; }
	inline float GetHeight(void) { return this->m_fHeight; }

private:
	void Scale();
	D3DMATERIAL9 InitMaterial();
	void InitTexture();

	D3DMATERIAL9		m_pMaterial;
	LPD3DXMESH			m_pMesh;
	CXFileContainer		m_xFile;

	eLETTER_TYPE		m_eLetterType;

	float				m_fWidth;
	float				m_fHeight;
	bool				m_bMaterial;
};