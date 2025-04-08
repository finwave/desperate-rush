#pragma once

#include "C3DObject.h"
#include "XFileContainer.h"

class CNumber: public C3DObject
{
public:
	enum eNUMBER_TYPE
	{
		eNUMBER_TYPE_MENUS,
		eNUMBER_TYPE_GAME,
		eNUMBER_TYPE_HIGHSCORE
	};

	CNumber(void);
	virtual ~CNumber(void);

	HRESULT Create(	LPD3DXMESH pMesh,
					CXFileContainer xFile,
					float fWidth,
					float fHeight,
					bool bMaterial,
					eNUMBER_TYPE eNumberType);

	virtual void Release();

	void Update(float fFrametime);

	inline float GetWidth(void) { return this->m_fWidth; }
	inline float GetHeight(void) { return this->m_fHeight; }

private:
	void Scale();
	D3DMATERIAL9 InitMaterial();
	void InitTexture();

	D3DMATERIAL9		m_Material;
	LPD3DXMESH			m_pMesh;
	CXFileContainer		m_xFile;

	eNUMBER_TYPE		m_eNumberType;

	float				m_fWidth;
	float				m_fHeight;
	bool				m_bMaterial;
};