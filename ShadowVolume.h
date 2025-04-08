#pragma once

#include <d3dx9.h>

typedef struct mshEdges
{
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 vNorm;
} _mshEdges;

class CShadowVolume
{
public:

	CShadowVolume();
	~CShadowVolume();

	void Create(LPD3DXMESH pMesh);

	void Reset();
	HRESULT Render(LPDIRECT3DDEVICE9 pDevice);

	HRESULT BuildFromMesh(	LPD3DXMESH pMesh, 
							D3DXVECTOR3 vLight);

	inline void SetWorldMatrix(D3DXMATRIX matrix) { this->m_matWorld = matrix; }
	inline DWORD GetTriangles() { return m_dwNumVertices / 3; }

private:

	void AddEdge(	WORD* pEdges,
					DWORD& dwNumEdges,
					WORD v0,
					WORD v1);

	D3DXVECTOR3	m_pVertices[32000]; // Vertex data for rendering shadow volume
    DWORD       m_dwNumVertices;
	D3DXMATRIX	m_matWorld;
};