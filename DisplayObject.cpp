#include "DisplayObject.h"

CDisplayObject::CDisplayObject(void)
{
}

CDisplayObject::~CDisplayObject(void)
{
}

HRESULT CDisplayObject::Create(	LPD3DXMESH mesh,
	std::vector<D3DMATERIAL9*> materials,
	std::vector<LPDIRECT3DTEXTURE9> textures)
{
	C3DObject::Create(mesh);

	for (DWORD i = 0; i < materials.size(); i++)
	{
		this->AddMeshData(materials[i], textures[i]);
	}

	this->Scale();

	return S_OK;
}

void CDisplayObject::Release()
{
	C3DObject::Release();
}

void CDisplayObject::Update(float fFrametime)
{
	C3DObject::Update(fFrametime);
}

void CDisplayObject::Scale()
{
	// get object's local matrix to temp matrix
	D3DXMATRIX& mObject = this->GetLocalMatrix();

	// scaling matrix
	D3DXMATRIX mScaling;
	D3DXMatrixIdentity(&mScaling);

	D3DXMatrixScaling(	&mScaling,
						0.7f,
						0.7f,
						0.7f );

	D3DXMatrixMultiply(&mObject, &mObject, &mScaling);
}