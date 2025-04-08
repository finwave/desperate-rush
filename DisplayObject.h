#pragma once

#include "C3DObject.h"
#include "XFileContainer.h"

class CDisplayObject: public C3DObject
{
public:
	CDisplayObject(void);
	virtual ~CDisplayObject(void);

	HRESULT Create(	LPD3DXMESH mesh,
		std::vector<D3DMATERIAL9*> materials,
		std::vector<LPDIRECT3DTEXTURE9> textures);

	virtual void Release();
	void Update(float fFrametime);

private:
	void Scale();
};