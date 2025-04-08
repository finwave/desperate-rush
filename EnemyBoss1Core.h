#pragma once

#include "EnemyBoss.h"

class CEnemyBoss1Core : public CEnemyBoss
{
public:

	CEnemyBoss1Core(	eTYPE eType,
						eBEHAVIOUR eBehaviour);

	virtual ~CEnemyBoss1Core(void);

	virtual HRESULT Create(	CTheApp* pTheApp,
							CGameSettings* pGameSettings,
							LPDIRECT3DDEVICE9 pDevice,
							LPD3DXMESH mesh,
							std::vector<D3DMATERIAL9*> materials,
							std::vector<LPDIRECT3DTEXTURE9> textures,
							int iVolumeSoundEffect);

	virtual void Release();

	void UpdateShip(int iHealth,
					float fFrametime);

protected:

	virtual void Init(	CTheApp* pTheApp,
						CGameSettings* pGameSettings,
						CSprite* pSpriteAfterburn,
						int iVolumeSoundEffect);

private:

	void InitPosition();

	void InitMaterial();
	void SetMaterial(int iHealth);
	void InitTexture(bool bClear);

	virtual void MoveEnter(float fFrametime, float fPlayerVelocity);

	LPDIRECT3DDEVICE9	m_pDevice;

	std::vector<D3DMATERIAL9*> m_Materials;
	std::vector<LPDIRECT3DTEXTURE9> m_Textures;

	int					m_iHealth;
	int					m_iHealthMax;
};