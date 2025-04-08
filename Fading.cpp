#include "Fading.h"

CFading::CFading(void)
{
	this->m_pApp = NULL;

	this->m_bInitialized = false;

	this->m_bFadeIn = false;
	this->m_bFadeOut = false;

	this->m_pVB = NULL;
}

CFading::~CFading(void)
{
	Release();
}

void CFading::Release()
{
	if( this->m_pVB != NULL )
	{
		this->m_pVB->Release();
	}
}

void CFading::InitFading(CTheApp* pApp)
{
	this->m_pApp = pApp;
	this->m_bInitialized = true;
}

HRESULT CFading::SetFadeIn()
{
	this->m_bFadeIn = true;
	this->m_bFadeOut = false;

	m_vertexColor = 0xFF000000;

	HRESULT hres = CreateVertices();
	return hres;
}

HRESULT CFading::SetFadeOut()
{
	this->m_bFadeIn = false;
	this->m_bFadeOut = true;

	m_vertexColor = 0x00000000;

	HRESULT hres = CreateVertices();
	return hres;
}

bool CFading::UpdateFading()
{
	if(m_bFadeIn)
	{
		if(	((m_vertexColor - this->m_fadeStep) == 0x00000000) || 
			((m_vertexColor - this->m_fadeStep) > (0xff000000 - this->m_fadeStep)))
		{
			m_bFadeIn = false;
			m_vertexColor = 0x00000000;
		}
		else
		{
			m_vertexColor -= this->m_fadeStep;
		}

		CreateVertices();
		return true;
	}
	else if(m_bFadeOut)
	{
		if(	((m_vertexColor + this->m_fadeStep) == 0xff000000) || 
			((m_vertexColor + this->m_fadeStep) < this->m_fadeStep))
		{
			m_bFadeOut = false;
			m_vertexColor = 0xff000000;
		}
		else
		{
			m_vertexColor += this->m_fadeStep;
		}

		CreateVertices();
		return true;
	}

	return false;
}

void CFading::RenderFading()
{
	LPDIRECT3DDEVICE9 device = this->m_pApp->GetDevice();

	// select which vertex format we are using
	device->SetFVF(D3DFVF_CUSTOMVERTEX);

    // select the vertex buffer to display
   device->SetStreamSource(0, this->m_pVB, 0, sizeof(CUSTOMVERTEX));

    // copy the vertex buffer to the back buffer
   device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

HRESULT CFading::CreateVertices()
{
	if( this->m_pVB != NULL )
	{
		this->m_pVB->Release();
		this->m_pVB = NULL;
	}

	HRESULT hres;

	LPDIRECT3DDEVICE9 device = this->m_pApp->GetDevice();

	// create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
		{0.0f, 0.0f, 0.0f, 1.0f, m_vertexColor},
        {1024.0f, 0.0f, 0.0f, 1.0f, m_vertexColor},
        {0.0f, 768.0f, 0.0f, 1.0f, m_vertexColor},
		{0.0f, 768.0f, 0.0f, 1.0f, m_vertexColor},
        {1024.0f, 0.0f, 0.0f, 1.0f, m_vertexColor},
		{1024.0f, 768.0f, 0.0f, 1.0f, m_vertexColor},
    };

    // create a vertex buffer interface called this->m_pVB
    hres = device->CreateVertexBuffer(	6 * sizeof(CUSTOMVERTEX),
										0,
										D3DFVF_CUSTOMVERTEX,
										D3DPOOL_MANAGED,
										&this->m_pVB,
										NULL);
	if( FAILED(hres) )
	{
		return hres;
	}

	// a void pointer
    VOID* pVoid;

    // lock this->m_pVB and load the vertices into it
    hres = this->m_pVB->Lock(0, 0, (void**)&pVoid, 0);

	if( FAILED(hres) )
	{
		return hres;
	}

    memcpy(pVoid, vertices, sizeof(vertices));
    hres = this->m_pVB->Unlock();

	return hres;
}

