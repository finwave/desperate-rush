#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tchar.h>
#include <d3dx9.h>

class CXFileContainer
{
public:

	CXFileContainer(void);
	virtual ~CXFileContainer(void);

	HRESULT Create(LPDIRECT3DDEVICE9 pDevice, std::string fileName);
	void Release();
	void Render(LPDIRECT3DDEVICE9 pDevice);

	inline LPD3DXMESH GetMesh() { return this->m_pMesh; }
	inline DWORD GetMaterialCount() { return this->m_dwNumMaterials; }
	inline D3DMATERIAL9* GetMaterials() { return this->m_pMaterials; }
	inline LPDIRECT3DTEXTURE9* GetTextures() { return this->m_pTextures; }

	inline bool IsInvalid() { return this->m_bIsInvalid; }
	inline void SetIsInvalid() { m_bIsInvalid = true; }

	static inline void SetCurrentFilePath(std::string path) { s_CurrentFilePath = path; }

private:

	LPD3DXMESH				m_pMesh;
	DWORD					m_dwNumMaterials;
	D3DMATERIAL9*			m_pMaterials;
	LPDIRECT3DTEXTURE9*		m_pTextures;
	bool					m_bIsInvalid;

	static std::string	s_CurrentFilePath;
};