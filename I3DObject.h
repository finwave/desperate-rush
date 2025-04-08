/**
 * Abstract 3D object interface implements
 * parent->children hierarchy and provides
 * basic movement and orientation interface.
 */

#pragma once

// include STL vector as a dynamic array
#include <vector>

#include <d3dx9.h>
#include "coldet.h"

class I3DObject
{
public:

	I3DObject(void);
	virtual ~I3DObject(void);

	/**
	 * Release
	 * iterate thru children and call each 'Release'
	 * function. After that, child object pointer is
	 * deleted
	 */
	virtual void Release(void);

	/**
	 * ReleaseCollisionMesh
	 * releases collision mesh properly
	 */
	void ReleaseCollisionMesh(void);

	/**
	 * Update
	 * update object hierarchy
	 * function creates a combined matrix from
	 * parent->child link.
	 * @param fFrametime
	 */
	virtual void Update(float fFrametime);

	/**
	 * Render
	 * pure virtual drawing function
	 * @param pDevice
	 */
	virtual void Render(LPDIRECT3DDEVICE9 pDevice) = 0;


	/**
	 * AddChild
	 * add new child object into the hierarchy
	 * NOTE! ownership of 'pObject' is transferred to
	 * its parent. All children are deleted when parent
	 * is released.
	 * @param pObject object to add
	 */
	void AddChild(I3DObject* pObject);

	virtual HRESULT CreateCollisionMesh() = 0;
	virtual HRESULT CreateCollisionMesh(LPD3DXMESH pMesh) = 0;

	virtual void UpdateCollisionMesh(bool bInverseMatrix) = 0;
	virtual bool IsMeshCollision(CollisionModel3D* pCollisionMesh, bool bDepth) = 0;

	virtual LPD3DXMESH GetMesh() = 0;
	virtual int TrianglesInMesh() = 0;

	virtual void SetDefaultMatrix() = 0;
	virtual void SetDefaultMatrix(D3DXMATRIX mDefault) = 0;

	virtual float GetObjectDepth() = 0;
	virtual void SetObjectDepth(float fDepth) = 0;

	/**
	 * GetParent
	 * @return pointer to parent object or NULL if not set
	 */
	inline I3DObject* GetParent() { return m_pParent; }

	/**
	 * GetChildren
	 * @return reference to child array
	 */
	inline std::vector<I3DObject*>& GetChildren() { return m_arrChildren; }

	/**
	 * GetWorldMatrix
	 * @return reference to object world matrix
	 */
	inline D3DXMATRIX& GetWorldMatrix() { return m_mWorld; }

	/**
	 * GetLocalMatrix
	 * @return reference to object local matrix
	 */
	inline D3DXMATRIX& GetLocalMatrix() { return m_mLocal; }

	/**
	 * GetDefaultMatrix
	 * @return reference to object default matrix
	 */
	inline D3DXMATRIX& GetDefaultMatrix() { return m_mDefault; }

	/**
	 * SetLocalMatrix
	 * @param object local matrix
	 */
	inline void SetLocalMatrix(D3DXMATRIX& mMatrix) { m_mLocal = mMatrix; }

	/**
	 * SetPosition
	 * set position into the local matrix
	 * @param vPos position to set
	 */
	inline void SetPosition(const D3DXVECTOR3& vPos)
	{
		::memcpy(&m_mLocal._41, &vPos.x, sizeof(D3DXVECTOR3));
	}

	/**
	 * GetPosition
	 * @return copy of the object position vector
	 */
	inline D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(&m_mLocal._41); }

	inline float GetScaleX() { return m_fScaleX; }
	inline float GetScaleY() { return m_fScaleY; }
	inline float GetScaleZ() { return m_fScaleZ; }

	/**
	 * movement get/set
	 */
	inline D3DXVECTOR3& GetVelocity() { return m_vVelocity; }
	inline D3DXVECTOR3& GetAcceleration() { return m_vAcceleration; }

	/**
	 * state get/set
	 */
	inline BOOL IsActive() const { return m_bActive; }
	inline BOOL IsVisible() const { return m_bVisible; }
	inline void SetVisible(BOOL bSet) { m_bVisible = bSet; }
	inline void SetActive(BOOL bSet) { m_bActive = bSet; }

	/**
	 * GetCollisionMesh
	 * @return pointer to collision mesh
	 */
	inline CollisionModel3D* GetCollisionMesh() { return m_pCollisionMesh; }

	/**
	 * SetCollisionMesh
	 * @param pointer to collision mesh
	 */
	inline void SetCollisionMesh(CollisionModel3D* pMesh) { this->m_pCollisionMesh = pMesh; }

	inline float GetAngleX() { return this->m_fRotateX; }
	inline float GetAngleY() { return this->m_fRotateY; }
	inline float GetAngleZ() { return this->m_fRotateZ; }

	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);

	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	void SetScale(int depth);

protected:

	// pointer to parent object
	I3DObject* m_pParent;

	// array of children
	std::vector<I3DObject*>	m_arrChildren;

	// collision mesh
	CollisionModel3D* m_pCollisionMesh;

	// 3D object matrices
	// World matrix: where object is related to the world
	// Local matrix: where object is related to its parent
	// Default matrix: object's default position/rotation related to its parent
	D3DXMATRIX m_mWorld;
	D3DXMATRIX m_mLocal;
	D3DXMATRIX m_mDefault;

	// object movement speed vector
	D3DXVECTOR3 m_vVelocity;

	// object acceleration vector
	D3DXVECTOR3 m_vAcceleration;

	// object state flags
	BOOL m_bVisible;
	BOOL m_bActive;
	BOOL m_bTransform;

private:

	void SetTransform();

	float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;

	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
};