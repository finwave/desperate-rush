#pragma once

#include "C3DObject.h"
#include "XFileContainer.h"

class CPlayerMinigun : public C3DObject
{
public:

	enum eSIDE
	{
		eSIDE_LEFT,
		eSIDE_RIGHT
	};

	CPlayerMinigun(void);
	virtual ~CPlayerMinigun(void);

	/* 
	 * Create
	 * Create mesh and load object from x-file
	 */
	HRESULT Create(	LPD3DXMESH mesh,
					std::vector<D3DMATERIAL9*> materials,
					std::vector<LPDIRECT3DTEXTURE9> textures,
					eSIDE eSide);

	/*
	 * Clean-up all mess in this class
	 */
	void Release(void);

	void Update(float fFrametime);

	inline void SetRotation(bool bRotate) { this->m_bRotateMinigun = bRotate; }

private:

	enum eDIRECTION
	{
		eDIRECTION_FRONT,
		eDIRECTION_DIAGONAL
	};

	void RotateMinigun(float fFrametime);

	void InitPosition();

	LPD3DXMESH			m_pMesh;

	eSIDE				m_eSide;
	eDIRECTION			m_eDirection;

	bool				m_bRotateMinigun;
	
	float				m_fAngle;
	float				m_fAngleMax;
};