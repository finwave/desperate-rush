#pragma once

#include <d3dx9.h>

class Camera
{
public:

	Camera(void);
	~Camera(void);

	void Init(LPDIRECT3DDEVICE9 pDevice);

	void Update(LPDIRECT3DDEVICE9 pDevice);

	void UpdateDelta(int iMouseDeltaX, int iMouseDeltaY, int iMouseDeltaZ);

private:

	D3DXMATRIX	m_view;

	D3DXVECTOR3 m_default_eye;
	D3DXVECTOR3 m_default_at;
	D3DXVECTOR3 m_default_up;

	float		m_fDeltaX;
	float		m_fDeltaY;
	float		m_fDeltaZ;
};
