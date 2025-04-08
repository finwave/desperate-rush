/**
 * Abstract 3D object interface implements
 * parent->children hierarchy and provides
 * basic movement and orientation interface.
 */

#include "I3DObject.h"

I3DObject::I3DObject(void)
{
	// init members
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mLocal);

	m_pParent = NULL;
	m_pCollisionMesh = NULL;

	m_vVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAcceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bActive = TRUE;
	m_bVisible = TRUE;

	this->m_bTransform = FALSE;

	m_fRotateX = 0.0f;
	m_fRotateY = 0.0f;
	m_fRotateZ = 0.0f;

	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;
}


I3DObject::~I3DObject(void)
{
}


void I3DObject::Release(void)
{
	for (DWORD i = 0; i < this->m_arrChildren.size(); i++)
	{
		I3DObject* pObject = this->m_arrChildren[i];
		pObject->Release();
		delete pObject;
		pObject = NULL;
	}

	m_arrChildren.clear();
}

void I3DObject::ReleaseCollisionMesh(void)
{
	if(this->m_pCollisionMesh)
	{
		delete this->m_pCollisionMesh;
		this->m_pCollisionMesh = NULL;
	}
}

void I3DObject::Update(float fFrametime)
{
	if (this->m_bTransform)
	{
		this->m_bTransform = FALSE;
		SetTransform();
	}

	if(IsActive())
	{
		// add velocity to our position
		m_mLocal._41 += m_vVelocity.x * fFrametime;
		m_mLocal._42 += m_vVelocity.y * fFrametime;
		m_mLocal._43 += m_vVelocity.z * fFrametime;

		// add acceleration to velocity
		m_vVelocity.x += m_vAcceleration.x * fFrametime;
		m_vVelocity.y += m_vAcceleration.y * fFrametime;
		m_vVelocity.z += m_vAcceleration.z * fFrametime;

		if(m_pParent)
		{
			// we have parent object:
			// multiply our local matrix with parent
			// world to create combined world transformation.
			D3DXMatrixMultiply( &m_mWorld,
								&m_mLocal,
								&m_pParent->m_mWorld );
		}
		else
		{
			// we don't have the parent object, therefore
			// the 'World' is our parent. Copy our local matrix
			// to world matrix.
			::memcpy(&m_mWorld, &m_mLocal, sizeof(D3DXMATRIX));
		}
	}

	// update children
	DWORD i;
	for (i=0; i<m_arrChildren.size(); i++)
	{
		m_arrChildren[i]->Update(fFrametime);
	}
}

void I3DObject::AddChild(I3DObject* pObject)
{
	// add child to array
	m_arrChildren.push_back(pObject);

	// link to parent
	pObject->m_pParent = this;
}

void I3DObject::SetRotateX(float x)
{
	this->m_fRotateX = x;
	this->m_bTransform = TRUE;
}

void I3DObject::SetRotateY(float y)
{
	this->m_fRotateY = y;
	this->m_bTransform = TRUE;
}

void I3DObject::SetRotateZ(float z)
{
	this->m_fRotateZ = z;
	this->m_bTransform = TRUE;
}

void I3DObject::SetScaleX(float x)
{
	this->m_fScaleX = x;
	this->m_bTransform = TRUE;
}

void I3DObject::SetScaleY(float y)
{
	this->m_fScaleY = y;
	this->m_bTransform = TRUE;
}

void I3DObject::SetScaleZ(float z)
{
	this->m_fScaleZ = z;
	this->m_bTransform = TRUE;
}

void I3DObject::SetScale(int depth)
{
	float scale = 1.0f;

	switch(depth)
	{
	case 1:
		scale = 1.0f;
		break;
	case 2:
		scale = 0.8f;
		break;
	case 3:
		scale = 0.7f;
		break;
	case 4:
		scale = 0.6f;
		break;
	case 5:
		scale = 0.5f;
		break;
	}

	this->m_fScaleX = scale;
	this->m_fScaleY = scale;
	this->m_fScaleZ = scale;

	this->m_bTransform = TRUE;
}

void I3DObject::SetTransform()
{
	D3DXVECTOR3 pos = GetPosition();

	D3DXMATRIX mRotationX;
	D3DXMATRIX mRotationY;
	D3DXMATRIX mRotationZ;
	D3DXMATRIX mRotation;
	D3DXMATRIX mScale;

	D3DXMatrixIdentity(&mRotationX);
	D3DXMatrixIdentity(&mRotationY);
	D3DXMatrixIdentity(&mRotationZ);
	D3DXMatrixIdentity(&mRotation);
	D3DXMatrixIdentity(&mScale);

	D3DXMatrixRotationX(&mRotationX, this->m_fRotateX);
	D3DXMatrixRotationY(&mRotationY, this->m_fRotateY);
	D3DXMatrixRotationZ(&mRotationZ, this->m_fRotateZ);

	D3DXMatrixScaling(&mScale, this->m_fScaleX, this->m_fScaleY, this->m_fScaleZ);

	D3DXMatrixMultiply(&mRotation, &mRotationY, &mRotationZ);
	D3DXMatrixMultiply(&m_mLocal, &mRotation, &mRotationX);
	D3DXMatrixMultiply(&m_mLocal, &m_mLocal, &mScale);

	SetPosition(pos);
}