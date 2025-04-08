#include "Number.h"

CNumber::CNumber(void)
{
	this->m_pMesh = NULL;
	this->m_fWidth = 0.0f;
	this->m_fHeight = 0.0f;
	this->m_bMaterial = false;
}

CNumber::~CNumber(void)
{
}

HRESULT CNumber::Create(LPD3DXMESH pMesh,
						CXFileContainer xFile,
						float fWidth,
						float fHeight,
						bool bMaterial,
						eNUMBER_TYPE eNumberType)
{
	this->m_pMesh = pMesh;
	this->m_xFile = xFile;
	this->m_fWidth = fWidth;
	this->m_fHeight = fHeight;
	this->m_bMaterial = bMaterial;
	this->m_eNumberType = eNumberType;

	C3DObject::Create(pMesh);

	if(this->m_bMaterial)
	{
		this->m_Material = this->InitMaterial();
	}

	this->InitTexture();
	this->Scale();

	return S_OK;
}

void CNumber::Release()
{
	C3DObject::Release();
}

void CNumber::Update(float fFrametime)
{
	C3DObject::Update(fFrametime);
}

void CNumber::Scale()
{
	// get object's local matrix to temp matrix
	D3DXMATRIX& mObject = this->GetLocalMatrix();

	// scaling matrix
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);

	switch(this->m_eNumberType)
	{
	case eNUMBER_TYPE_MENUS:

		D3DXMatrixScaling(	&mScale,
							0.75f,
							0.75f,
							0.75f );
		break;

	case eNUMBER_TYPE_GAME:

		D3DXMatrixScaling(	&mScale,
							0.7f,
							0.7f,
							0.7f );
		break;

	case eNUMBER_TYPE_HIGHSCORE:

		D3DXMatrixScaling(	&mScale,
							1.5f,
							1.5f,
							1.5f );
		break;
	}

	D3DXMatrixMultiply(&mObject, &mObject, &mScale);
}

D3DMATERIAL9 CNumber::InitMaterial()
{
	D3DMATERIAL9 material;

	switch(this->m_eNumberType)
	{
	case eNUMBER_TYPE_MENUS:

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

	case eNUMBER_TYPE_GAME:

		// Set the RGBA for diffuse reflection.
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 1.0f;
		material.Diffuse.b = 1.0f;
		material.Diffuse.a = 1.0f;
		// Set the RGBA for ambient reflection.
		material.Ambient.r = 1.0f;
		material.Ambient.g = 1.0f;
		material.Ambient.b = 1.0f;
		material.Ambient.a = 1.0f;
		// Set the color and sharpness of specular highlights.
		material.Specular.r = 0.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 0.0f;
		material.Power = 0.0f;
		// Set the RGBA for emissive color.
		material.Emissive.r = 0.8f;
		material.Emissive.g = 0.8f;
		material.Emissive.b = 0.8f;
		material.Emissive.a = 1.0f;

		break;

	case eNUMBER_TYPE_HIGHSCORE:

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

void CNumber::InitTexture()
{
	MESHDATA data;

	for (DWORD i = 0; i < this->m_xFile.GetMaterialCount(); i++)
	{
		if( this->m_bMaterial )
		{
			data.pMaterial = &this->m_Material;
		}
		else
		{
			data.pMaterial = &this->m_xFile.GetMaterials()[i];
		}
		data.pTexture = this->m_xFile.GetTextures()[i];
		this->AddMeshData(data);
	}
}