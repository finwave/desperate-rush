/**
 * Concrete 3D object class using D3DX meshes.
 */

#pragma once

#include "I3DObject.h"

class C3DObject : public I3DObject
{
public:

	// struct for storing object materials
	struct MESHDATA
	{
		D3DMATERIAL9*		pMaterial;
		LPDIRECT3DTEXTURE9	pTexture;
	};

	C3DObject(void);
	virtual ~C3DObject(void);

	/**
	 * Create
	 * initialise 3d object from given mesh
	 * @param pMesh
	 */
	void Create(LPD3DXMESH pMesh);

	/**
	 * Release
	 * release object and children. This
	 * function does NOT release the mesh or
	 * materials
	 */
	virtual void Release(void);

	/**
	 * Render
	 * render the 3d object
	 * @param pDevice device to use for rendering
	 */
	virtual void Render(LPDIRECT3DDEVICE9 pDevice);

	/**
	 * AddMeshData
	 * add new mesh data structure to array
	 */
	void AddMeshData(MESHDATA& meshData);
	void AddMeshData(D3DMATERIAL9* material, LPDIRECT3DTEXTURE9 texture);
	void ClearMeshData();

	virtual HRESULT CreateCollisionMesh();
	virtual HRESULT CreateCollisionMesh(LPD3DXMESH pMesh);

	virtual void UpdateCollisionMesh(bool bInverseMatrix);
	virtual bool IsMeshCollision(CollisionModel3D* pCollisionMesh, bool bDepth);

	/**
	 * GetMeshDataArray
	 * @return reference to mesh data array
	 */
	inline std::vector<MESHDATA>& GetMeshDataArray() { return m_arrMeshData; }

	virtual LPD3DXMESH GetMesh();
	virtual int TrianglesInMesh();

	virtual void SetDefaultMatrix();
	virtual void SetDefaultMatrix(D3DXMATRIX mDefault);

	float GetObjectDepth();
	virtual void SetObjectDepth(float fDepth);

	float GetDepthValue(int depthLevel);

protected:

	// an array of mesh materials and textures
	std::vector<MESHDATA> m_arrMeshData;
	// the mesh object
	LPD3DXMESH m_pMesh;
};