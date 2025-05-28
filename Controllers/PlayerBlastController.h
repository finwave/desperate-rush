#pragma once

#define SPRITE_PLAYER_BLAST_UP			1
#define SPRITE_PLAYER_BLAST_DOWN		3
#define SPRITE_PLAYER_BLAST_LEFT		7
#define SPRITE_PLAYER_BLAST_RIGHT		2
#define SPRITE_PLAYER_BLAST_UP_LEFT		4
#define SPRITE_PLAYER_BLAST_UP_RIGHT	0
#define SPRITE_PLAYER_BLAST_DOWN_LEFT	6
#define SPRITE_PLAYER_BLAST_DOWN_RIGHT	5

// Forward declaration
class CTheApp;
class C3DObject;
class CSprite;

class CPlayerBlastController
{
public:

	enum eBLAST_LIGHT
	{
		eBLAST_LIGHT_HIGH,
		eBLAST_LIGHT_LOW
	};

	CPlayerBlastController(void);
	~CPlayerBlastController(void);

	void Init(CTheApp* pTheApp, C3DObject* pPlayerObject, CSprite* pSpriteBlast);
	void Release(void);

	void Update(float fFrametime);
	void Render();

	void Activate();

	inline bool IsBlastActive() { return this->m_bBlastActive; }
	inline int GetBlastAmount() { return this->m_iBlastAmount; }

	inline void IncreaseBlastAmount() { this->m_iBlastAmount++; }
	inline void DecreaseBlastAmount() { this->m_iBlastAmount--; }

	inline eBLAST_LIGHT GetBlastLight() { return this->m_eBlastLight; }

private:

	// matches with sprite array indexes
	enum eBEAM_DIRECTION
	{
		UpRight,
		Up,
		Right,
		Down,
		UpLeft,
		DownRight,
		DownLeft,
		Left,
		Invalid
	};

	bool ReserveBeamDirection(eBEAM_DIRECTION eDirection);

	CTheApp*		m_pTheApp;
	C3DObject*		m_pPlayerObject;
	CSprite*		m_pSpriteBlast;

	eBEAM_DIRECTION* m_eBeamDirections;
	eBLAST_LIGHT	m_eBlastLight;

	float			m_fBlastBeamTimer;
	int				m_iBlastAmount;

	float			m_fBlastActiveTimer;
	bool			m_bBlastActive;

	const int		DIRECTION_TRYOUT_MAX = 40;
};