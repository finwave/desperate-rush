#pragma once

#include "TheApp.h"

class CFading
{
public:
	CFading(void);
	~CFading(void);

	void InitFading(CTheApp* pApp);
	void Release();

	HRESULT SetFadeIn();
	HRESULT SetFadeOut();

	bool UpdateFading();
	void RenderFading();

	inline void SetDefaultFadeStep() { this->m_fadeStep = 0x0F000000; }
	inline void SetFadeStep(DWORD fadeStep) { this->m_fadeStep = fadeStep; }
	inline bool IsInitialized() { return this->m_bInitialized; }

private:
	
	HRESULT CreateVertices();

	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;	// The transformed position for the vertex.
		DWORD color;        // The vertex color.
	};

	CTheApp*				m_pApp;

	bool					m_bInitialized;

	bool					m_bFadeIn;
	bool					m_bFadeOut;

	DWORD					m_fadeStep;
	DWORD					m_vertexColor;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
};
