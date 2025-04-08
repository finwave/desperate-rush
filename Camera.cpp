#include "Camera.h"

Camera::Camera(void)
{
	this->m_fDeltaX = 0.0f;
	this->m_fDeltaY = 0.0f;
	this->m_fDeltaZ = 0.0f;

	this->m_default_eye.x = 0.0f;
	this->m_default_eye.y = 0.0f;
	this->m_default_eye.z = -50.0f;

	this->m_default_at.x = 0.0f;
	this->m_default_at.y = 0.0f;
	this->m_default_at.z = 0.0f;

	this->m_default_up.x = 0.0f;
	this->m_default_up.y = 1.0f;
	this->m_default_up.z = 0.0f;
}

Camera::~Camera(void)
{
}

void Camera::Init(LPDIRECT3DDEVICE9 pDevice)
{
	// set initial camera position

	D3DXMatrixLookAtLH(&m_view, &m_default_eye, &m_default_at, &m_default_up);
	pDevice->SetTransform(D3DTS_VIEW, &m_view);
}

void Camera::Update(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX mRotation;
	D3DXMatrixIdentity(&mRotation);

	D3DXMATRIX mRotationX;
	D3DXMatrixIdentity(&mRotationX);
	D3DXMatrixRotationX(&mRotationX, this->m_fDeltaY / 100);

	D3DXMATRIX mRotationZ;
	D3DXMatrixIdentity(&mRotationZ);
	D3DXMatrixRotationZ(&mRotationZ, this->m_fDeltaX / 100);

	D3DXMatrixMultiply(&mRotation, &mRotationX, &mRotationZ);

	D3DXMatrixMultiply(&m_view, &mRotation, &m_view);

	pDevice->SetTransform(D3DTS_VIEW, &m_view);
}

void Camera::UpdateDelta(int iDeltaX, int iDeltaY, int iDeltaZ)
{
	this->m_fDeltaX = iDeltaX;
	this->m_fDeltaY = iDeltaY;
	this->m_fDeltaZ = iDeltaZ;
}