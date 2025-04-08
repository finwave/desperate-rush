#include "TextUtils.h"
#include "XFileContainer.h"

std::string CXFileContainer::s_CurrentFilePath = "";

CXFileContainer::CXFileContainer(void)
{
	this->m_dwNumMaterials = 0;
	this->m_pMaterials = NULL;
	this->m_pMesh = NULL;
	this->m_pTextures = NULL;
	this->m_bIsInvalid = false;
}

CXFileContainer::~CXFileContainer(void)
{
	this->m_dwNumMaterials = 0;
	this->m_pMaterials = NULL;
	this->m_pMesh = NULL;
	this->m_pTextures = NULL;
}

HRESULT CXFileContainer::Create(LPDIRECT3DDEVICE9 pDevice, std::string fileName)
{
	HRESULT hres;
	LPD3DXBUFFER pMaterialBuffer = NULL;
	LPCTSTR filePath = TextUtils::CombineStrings_LPCTSTR(CXFileContainer::s_CurrentFilePath, fileName);

	// load object

	hres = D3DXLoadMeshFromX(	filePath,
								D3DXMESH_MANAGED,
								pDevice,
								NULL,
								&pMaterialBuffer,
								NULL,
								&this->m_dwNumMaterials,
								&this->m_pMesh);

	if(FAILED(hres))
	{
		// maybe file not found
		return hres;
	}

	D3DXMATERIAL* pMaterial = (D3DXMATERIAL*)pMaterialBuffer->GetBufferPointer();

	//allocate memory for the materials and textures
	this->m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	this->m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		this->m_pTextures[i] = NULL;
	}

	if(pMaterial == NULL || this->m_pMaterials == NULL || this->m_pTextures == NULL)
	{
		this->Release();
		return E_OUTOFMEMORY;
	}

	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		this->m_pMaterials[i] = pMaterial[i].MatD3D;
		this->m_pMaterials[i].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

		LPSTR textureFileName = pMaterial[i].pTextureFilename;

		if (textureFileName != NULL)
		{
			std::string strTextureFileName = std::string(textureFileName);
			LPCSTR fullTexturePath = TextUtils::CombineStrings_LPCSTR(CXFileContainer::s_CurrentFilePath, strTextureFileName);

			hres = D3DXCreateTextureFromFileA(pDevice, fullTexturePath, &this->m_pTextures[i]);

			if (FAILED(hres))
			{
				this->m_pTextures[i] = NULL;
#ifdef _DEBUG
				if (pMaterial[i].pTextureFilename)
				{
					::OutputDebugString(_T("Failed to load texture"));
					::OutputDebugStringA(pMaterial[i].pTextureFilename);
					::OutputDebugString(_T("\r\n"));
				}
#endif
			}
		}
	}

	return S_OK;
}

void CXFileContainer::Release()
{	
	if(this->m_pTextures)
	{
		for (DWORD i = 0; i < this->m_dwNumMaterials; i++)
		{
			if(this->m_pTextures[i])
			{
				this->m_pTextures[i]->Release();
				this->m_pTextures[i] = NULL;
			}
		}

		delete [] this->m_pTextures;
		this->m_pTextures = NULL;
	}

	if(this->m_pMaterials)
	{
		delete [] this->m_pMaterials;
		this->m_pMaterials = NULL;
	}

	if(this->m_pMesh)
	{
		this->m_pMesh->Release();
		this->m_pMesh = NULL;
	}

	this->m_dwNumMaterials = 0;
}

void CXFileContainer::Render(LPDIRECT3DDEVICE9 pDevice)
{
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		pDevice->SetMaterial(&this->m_pMaterials[i]);
		pDevice->SetTexture(0, this->m_pTextures[i]);
		this->m_pMesh->DrawSubset(i);
	}
}