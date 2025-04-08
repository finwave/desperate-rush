/**
 * Concrete 3D object class using D3DX meshes.
 */

#include "C3DObject.h"

C3DObject::C3DObject(void)
{
	this->m_pMesh = NULL;
	this->m_pCollisionMesh = NULL;
}

C3DObject::~C3DObject(void)
{
}

void C3DObject::Create(LPD3DXMESH pMesh)
{
	this->m_pMesh = pMesh;
}

void C3DObject::Release(void)
{
	m_arrMeshData.clear();
	I3DObject::Release();

	this->m_pMesh = NULL;
}

void C3DObject::Render(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsVisible() && m_pMesh)
	{
		// first set the world matrix to device
		pDevice->SetTransform(D3DTS_WORLD, &m_mWorld);

		if(m_arrMeshData.size())
		{
			DWORD i;
			for (i = 0; i < m_arrMeshData.size(); i++)
			{
				MESHDATA& data = m_arrMeshData[i];

				// set the texture
				pDevice->SetTexture(0, data.pTexture);

				// set material
				if(data.pMaterial)
				{
					pDevice->SetMaterial(data.pMaterial);
				}

				// render mesh
				m_pMesh->DrawSubset(i);
			}
		}
		else
		{
			// render the mesh
			m_pMesh->DrawSubset(0);
		}
	}

	// render the children
	DWORD i;
	for (i=0; i<m_arrChildren.size(); i++)
	{
		m_arrChildren[i]->Render(pDevice);
	}
}

void C3DObject::AddMeshData(MESHDATA& meshData)
{
	m_arrMeshData.push_back(meshData);
}

void C3DObject::AddMeshData(D3DMATERIAL9* material, LPDIRECT3DTEXTURE9 texture)
{
	MESHDATA meshData;

	meshData.pMaterial = material;
	meshData.pTexture = texture;

	m_arrMeshData.push_back(meshData);
}

void C3DObject::ClearMeshData()
{
	m_arrMeshData.clear();
}

HRESULT C3DObject::CreateCollisionMesh()
{
	HRESULT hres;

	this->m_pCollisionMesh = newCollisionModel3D();

	DWORD numVertices = this->m_pMesh->GetNumVertices();
	DWORD numFaces = this->m_pMesh->GetNumFaces();
	unsigned nIndices = numFaces * 3;

	BYTE* pVertices = NULL;
	UINT nStride = 0;
	D3DXVECTOR3 *pVertexVectors = NULL;

	WORD* dwIndices;

	// Get the meshes vertex buffer

	LPDIRECT3DVERTEXBUFFER9 pVB;
	hres = this->m_pMesh->GetVertexBuffer(&pVB);
	if( FAILED(hres) )
	{
		return hres;
	}

	// Get the vertex declaration for the mesh

	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	hres = this->m_pMesh->GetDeclaration(Decl);
	if( FAILED(hres) )
	{
		pVB->Release();
		return hres;
	}

	// Lock the vertex buffer
	hres = pVB->Lock(0, 0, (void**)&pVertices, D3DLOCK_READONLY);
	if( FAILED(hres) )
	{
		pVB->Release();
		return hres;
	}

	// Get the size of a single vertex
	nStride = D3DXGetDeclVertexSize(Decl, 0);

	// Process vertices

	pVertexVectors = new D3DXVECTOR3[numVertices];

	for(DWORD i = 0; i < numVertices; ++i)
	{
		// Assume that the position is the first D3DXVECTOR3 in the vertex
		D3DXVECTOR3* pPosition = (D3DXVECTOR3*)pVertices;

		// Do things with pPosition here
		pVertexVectors[i] = pPosition[0];

		// Move on to next vertex
		pVertices += nStride;
	}
	
	// unlock and release vertex buffer
	pVB->Unlock();
	pVB->Release();

	// process mesh indices

	int iIndex;
	D3DXVECTOR3 vertex1;
	D3DXVECTOR3 vertex2;
	D3DXVECTOR3 vertex3;

	this->m_pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&dwIndices);

	for(unsigned i = 0; i < nIndices;)
	{
		iIndex = dwIndices[i];
		vertex1 = pVertexVectors[iIndex];

		iIndex = dwIndices[i+1];
		vertex2 = pVertexVectors[iIndex];

		iIndex = dwIndices[i+2];
		vertex3 = pVertexVectors[iIndex];

		// add triangle to collision model
		this->m_pCollisionMesh->addTriangle(vertex1.x, vertex1.y, vertex1.z,
											vertex2.x, vertex2.y, vertex2.z,
											vertex3.x, vertex3.y,vertex3.z);
		i += 3;
	}

	// unlock index buffer
	this->m_pMesh->UnlockIndexBuffer();

	// finalize collision model
	this->m_pCollisionMesh->finalize();

	if(pVertices)
	{
		pVertices = NULL;
	}
	if(pVertexVectors)
	{
		delete [] pVertexVectors;
		pVertexVectors = NULL;
	}
	if(dwIndices)
	{
		dwIndices = NULL;
	}

	return S_OK;
}

HRESULT C3DObject::CreateCollisionMesh(LPD3DXMESH pMesh)
{
	HRESULT hres;

	this->m_pCollisionMesh = newCollisionModel3D();

	DWORD numVertices = pMesh->GetNumVertices();
	DWORD numFaces = pMesh->GetNumFaces();
	unsigned nIndices = numFaces * 3;

	BYTE* pVertices = NULL;
	UINT nStride = 0;
	D3DXVECTOR3 *pVertexVectors = NULL;

	WORD* dwIndices;

	// Get the meshes vertex buffer

	LPDIRECT3DVERTEXBUFFER9 pVB;
	hres = pMesh->GetVertexBuffer(&pVB);
	if( FAILED(hres) )
	{
		return hres;
	}

	// Get the vertex declaration for the mesh

	D3DVERTEXELEMENT9 Decl[MAX_FVF_DECL_SIZE];
	hres = pMesh->GetDeclaration(Decl);
	if( FAILED(hres) )
	{
		pVB->Release();
		return hres;
	}

	// Lock the vertex buffer
	hres = pVB->Lock(0, 0, (void**)&pVertices, D3DLOCK_READONLY);
	if( FAILED(hres) )
	{
		pVB->Release();
		return hres;
	}

	// Get the size of a single vertex
	nStride = D3DXGetDeclVertexSize(Decl, 0);

	// Process vertices

	pVertexVectors = new D3DXVECTOR3[numVertices];

	for(DWORD i = 0; i < numVertices; ++i)
	{
		// Assume that the position is the first D3DXVECTOR3 in the vertex
		D3DXVECTOR3* pPosition = (D3DXVECTOR3*)pVertices;

		// Do things with pPosition here
		pVertexVectors[i] = pPosition[0];

		// Move on to next vertex
		pVertices += nStride;
	}
	
	// unlock and release vertex buffer
	pVB->Unlock();
	pVB->Release();

	// process mesh indices

	int iIndex;
	D3DXVECTOR3 vertex1;
	D3DXVECTOR3 vertex2;
	D3DXVECTOR3 vertex3;

	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&dwIndices);

	for(unsigned i = 0; i < nIndices;)
	{
		iIndex = dwIndices[i];
		vertex1 = pVertexVectors[iIndex];

		iIndex = dwIndices[i+1];
		vertex2 = pVertexVectors[iIndex];

		iIndex = dwIndices[i+2];
		vertex3 = pVertexVectors[iIndex];

		// add triangle to collision model
		this->m_pCollisionMesh->addTriangle(	vertex1.x,
												vertex1.y,
												vertex1.z,
												vertex2.x,
												vertex2.y,
												vertex2.z,
												vertex3.x,
												vertex3.y,
												vertex3.z);
		i += 3;
	}

	// unlock index buffer
	pMesh->UnlockIndexBuffer();

	// finalize collision model
	this->m_pCollisionMesh->finalize();

	if(pVertices)
	{
		pVertices = NULL;
	}
	if(pVertexVectors)
	{
		delete [] pVertexVectors;
		pVertexVectors = NULL;
	}
	if(dwIndices)
	{
		dwIndices = NULL;
	}

	return S_OK;
}

void C3DObject::UpdateCollisionMesh(bool bInverseMatrix)
{
	float fMatrix[16];
	int iIndex = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(bInverseMatrix)
			{
				fMatrix[iIndex] = this->m_mWorld.m[j][i];
			}
			else
			{
				fMatrix[iIndex] = this->m_mWorld.m[i][j];
			}

			iIndex++;
		}
	}

	this->m_pCollisionMesh->setTransform(fMatrix);
}

bool C3DObject::IsMeshCollision(CollisionModel3D* pCollisionMesh, bool bDepth)
{
	bool bCollision = this->m_pCollisionMesh->collision(pCollisionMesh);

	if(bDepth)
	{
		if(bCollision)
		{
			float fCollisionPoint[3];
			for(int i = 0; i < 3; i++)
			{
				fCollisionPoint[i] = 0.0f;
			}

			this->m_pCollisionMesh->getCollisionPoint(fCollisionPoint, false);

			D3DXVECTOR3 vCollisionPoint;

			// no collision detector
			vCollisionPoint.z = -1000.0f;

			vCollisionPoint.x = fCollisionPoint[0];
			vCollisionPoint.y = fCollisionPoint[1];
			vCollisionPoint.z = fCollisionPoint[2];

			if(vCollisionPoint.z = -1000.0f)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return bCollision;
	}
}

LPD3DXMESH C3DObject::GetMesh()
{
	return this->m_pMesh;
}

int C3DObject::TrianglesInMesh()
{
	if (this->m_pMesh)
	{
		return (int)this->m_pMesh->GetNumFaces();
	}
	else
	{
		return 0;
	}
}

void C3DObject::SetDefaultMatrix()
{
	this->GetLocalMatrix() = this->m_mDefault;
}

void C3DObject::SetDefaultMatrix(D3DXMATRIX mDefault)
{
	this->m_mDefault = mDefault;
}

float C3DObject::GetObjectDepth()
{
	return this->GetPosition().z;
}

void C3DObject::SetObjectDepth(float fDepth)
{
	D3DXVECTOR3 pos = this->GetPosition();
	pos.z = fDepth;
	this->SetPosition(pos);
}

float C3DObject::GetDepthValue(int depthLevel)
{
	switch(depthLevel)
	{
	case 1:
		return -800.0f;
	case 2:
		return -600.0f;
	case 3:
		return -400.0f;
	case 4:
		return -200.0f;
	case 5:
		return 0.0f;
	case 6:
		return 200.0f;
	case 7:
		return 400.0f;
	case 8:
		return 600.0f;
	case 9:
		return 800.0f;
	}

	return 0.0f;
}