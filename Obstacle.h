#pragma once

#include "C3DObject.h"
#include "TheApp.h"
#include "XFileContainer.h"

class CObstacle : public C3DObject
{
public:

	enum eTYPE
	{
		eTYPE_ASTEROID_BIG_1,
		eTYPE_ASTEROID_BIG_2,
		eTYPE_ASTEROID_BIG_3,
		eTYPE_ASTEROID_BIG_4,
		eTYPE_ASTEROID_BIG_5,
		eTYPE_ASTEROID_MEDIUM_1,
		eTYPE_ASTEROID_MEDIUM_2,
		eTYPE_ASTEROID_MEDIUM_3,
		eTYPE_ASTEROID_MEDIUM_4,
		eTYPE_ASTEROID_MEDIUM_5,
		eTYPE_ASTEROID_SMALL_1,
		eTYPE_ASTEROID_SMALL_2,
		eTYPE_ASTEROID_SMALL_3,
		eTYPE_ASTEROID_SMALL_4,
		eTYPE_ASTEROID_SMALL_5
	};

	enum eOBSTACLE_DEPTH
	{
		eOBSTACLE_DEPTH_1,
		eOBSTACLE_DEPTH_2,
		eOBSTACLE_DEPTH_3,
		eOBSTACLE_DEPTH_4,
		eOBSTACLE_DEPTH_5
	};

	CObstacle(void);
	virtual ~CObstacle(void);

	virtual HRESULT Create(	CTheApp *pTheApp,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight);

	virtual HRESULT Create(	CTheApp *pTheApp,
							LPD3DXMESH mesh,
							std::vector<MESHDATA>& meshData,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight);

	virtual HRESULT Create(	CTheApp *pTheApp,
							float fObstacleWidth,
							float fObstacleHeight,
							float fScreenWidth,
							float fScreenHeight);

	virtual void Release();

	virtual void Update(float fFrametime, float fPlayerVelocity);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice);

	void InitObstacle(eOBSTACLE_DEPTH eDepth);

	inline float GetWidth() const { return this->m_fObstacleWidth; }
	inline float GetHeight() const { return this->m_fObstacleHeight; }
	inline float GetSpeed() const { return this->m_fSpeed; }

	inline eTYPE GetType() { return this->m_eType; }
	inline void SetType(eTYPE eType) { this->m_eType = eType; }

	inline void SetSpeed(float fSpeed) { this->m_fSpeed = fSpeed; }
	inline void SetSpeedChange(bool bChange) { this->m_bSpeedChange = bChange; }

	inline eOBSTACLE_DEPTH GetDepth() { return this->m_eDepth; }

private:

	void RotateUp();
	void RotateDown();
	void Rotate(float fFrametime);
	void MoveNormal(float fFrametime, float fPlayerVelocity);
	void MoveSpeedChange(float fFrametime, float fPlayerVelocity);

	void SetDepth();

	CTheApp*		m_pTheApp;

	eTYPE			m_eType;
	eOBSTACLE_DEPTH	m_eDepth;

	float			m_fObstacleWidth;
	float			m_fObstacleHeight;

	float			m_fSpeed;

	float			m_fScreenWidth;
	float			m_fScreenHeight;

	float			m_fAngle;
	float			m_fAngleMultiplier;
	int				m_iRotationSelector;

	bool			m_bSpeedChange;
	float			m_fSpeedChangeMultiplier;
};