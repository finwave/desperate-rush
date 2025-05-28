#pragma once

// Forward declaration
class C3DObject;
class CSprite;

class CShipAfterburnController
{
public:

	enum eSHIP_TYPE
	{
		Player,
		Drone,
		Sniper,
		Roller,
		Guard
	};

	CShipAfterburnController(void);
	~CShipAfterburnController(void);

	void Init(C3DObject* pShipObject, CSprite* pSpriteAfterburn, eSHIP_TYPE eShipType);
	void Release(void);

	void Render(float fFrametime);

private:

	C3DObject* m_pShipObject;
	CSprite* m_pSpriteAfterburn;
	eSHIP_TYPE m_eShipType;

	float m_fPlayerAfterburnFlickerTimer;
	int m_iPlayerAfterburnFlickerMode;
};