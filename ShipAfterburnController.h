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
		Sniper
	};

	CShipAfterburnController(void);
	virtual ~CShipAfterburnController(void);

	void Init(C3DObject* pShipObject, CSprite* pSpriteAfterburn, eSHIP_TYPE eShipType);
	void Render(float fFrametime);

private:

	C3DObject* m_pShipObject;
	CSprite* m_pSpriteAfterburn;
	eSHIP_TYPE m_eShipType;

	float m_fPlayerAfterburnFlickerTimer;
	int m_iPlayerAfterburnFlickerMode;
};

