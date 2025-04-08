#include "Letter.h"

CLetter::CLetter(void)
{
	this->m_pMesh = NULL;
	this->m_fWidth = 0.0f;
	this->m_fHeight = 0.0f;
	this->m_bMaterial = false;
}

CLetter::~CLetter(void)
{
}

HRESULT CLetter::Create(LPD3DXMESH pMesh,
						CXFileContainer xFile,
						float fWidth,
						float fHeight,
						bool bMaterial,
						eLETTER_TYPE eLetterType)
{
	this->m_pMesh = pMesh;
	this->m_xFile = xFile;
	this->m_fWidth = fWidth;
	this->m_fHeight = fHeight;
	this->m_bMaterial = bMaterial;
	this->m_eLetterType = eLetterType;

	C3DObject::Create(pMesh);

	if(this->m_bMaterial)
	{
		this->m_pMaterial = this->InitMaterial();
	}

	this->InitTexture();
	this->Scale();

	return S_OK;
}

void CLetter::Release()
{
	C3DObject::Release();
}

void CLetter::Update(float fFrametime)
{
	C3DObject::Update(fFrametime);
}

void CLetter::Scale()
{
	// get object's local matrix to temp matrix
	D3DXMATRIX& mObject = this->GetLocalMatrix();

	// scaling matrix
	D3DXMATRIX mScaling;
	D3DXMatrixIdentity(&mScaling);

	switch(this->m_eLetterType)
	{
	case eLETTER_TYPE_MENUS:

		D3DXMatrixScaling(	&mScaling,
							0.75f,
							0.75f,
							0.75f );
		break;

	case eLETTER_TYPE_GAME:

		D3DXMatrixScaling(	&mScaling,
							0.7f,
							0.7f,
							0.7f );
		break;

	case eLETTER_TYPE_HIGHSCORE:

		D3DXMatrixScaling(	&mScaling,
							1.5f,
							1.5f,
							1.5f );
		break;
	}

	D3DXMatrixMultiply(&mObject, &mObject, &mScaling);
}

D3DMATERIAL9 CLetter::InitMaterial()
{
	D3DMATERIAL9 material;

	switch(this->m_eLetterType)
	{
	case eLETTER_TYPE_MENUS:

		// Set the RGBA for diffuse reflection.
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 1.0f;
		material.Diffuse.b = 1.0f;
		material.Diffuse.a = 1.0f;
		// Set the RGBA for ambient reflection.
		material.Ambient.r = 0.0f;
		material.Ambient.g = 0.0f;
		material.Ambient.b = 0.0f;
		material.Ambient.a = 0.0f;
		// Set the color and sharpness of specular highlights.
		material.Specular.r = 0.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 0.0f;
		material.Power = 0.0f;
		// Set the RGBA for emissive color.
		material.Emissive.r = 0.0f;
		material.Emissive.g = 0.0f;
		material.Emissive.b = 0.0f;
		material.Emissive.a = 0.0f;

		break;

	case eLETTER_TYPE_GAME:

		// Set the RGBA for diffuse reflection.
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 1.0f;
		material.Diffuse.b = 1.0f;
		material.Diffuse.a = 1.0f;
		// Set the RGBA for ambient reflection.
		material.Ambient.r = 0.0f;
		material.Ambient.g = 0.0f;
		material.Ambient.b = 0.0f;
		material.Ambient.a = 0.0f;
		// Set the color and sharpness of specular highlights.
		material.Specular.r = 0.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 0.0f;
		material.Power = 0.0f;
		// Set the RGBA for emissive color.
		material.Emissive.r = 0.0f;
		material.Emissive.g = 0.0f;
		material.Emissive.b = 0.0f;
		material.Emissive.a = 0.0f;

		break;

	case eLETTER_TYPE_HIGHSCORE:

		// Set the RGBA for diffuse reflection.
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 1.0f;
		material.Diffuse.b = 1.0f;
		material.Diffuse.a = 1.0f;
		// Set the RGBA for ambient reflection.
		material.Ambient.r = 0.0f;
		material.Ambient.g = 0.0f;
		material.Ambient.b = 0.0f;
		material.Ambient.a = 0.0f;
		// Set the color and sharpness of specular highlights.
		material.Specular.r = 0.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 0.0f;
		material.Power = 0.0f;
		// Set the RGBA for emissive color.
		material.Emissive.r = 1.0f;
		material.Emissive.g = 1.0f;
		material.Emissive.b = 1.0f;
		material.Emissive.a = 2.0f;

		break;
	}

	return material;
}

void CLetter::InitTexture()
{
	MESHDATA data;

	for (DWORD i = 0; i < this->m_xFile.GetMaterialCount(); i++)
	{
		if( this->m_bMaterial )
		{
			data.pMaterial = &this->m_pMaterial;
		}
		else
		{
			data.pMaterial = &this->m_xFile.GetMaterials()[i];
		}
		data.pTexture = this->m_xFile.GetTextures()[i];
		this->AddMeshData(data);
	}
}