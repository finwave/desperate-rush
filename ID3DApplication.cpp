/**
 * An abstract class implements Direct3D version 9
 * initialisation and main loop.
 */

#include "ID3DApplication.h"

ID3DApplication::ID3DApplication(void)
{
	// init the members
	this->m_pD3D = NULL;
	this->m_pDevice = NULL;
	::memset(&this->m_Present, 0, sizeof(D3DPRESENT_PARAMETERS));

	this->m_default_eye.x = 0.0f;
	this->m_default_eye.y = 0.0f;
	this->m_default_eye.z = -50.0f;

	this->m_default_at.x = 0.0f;
	this->m_default_at.y = 0.0f;
	this->m_default_at.z = 0.0f;

	this->m_default_up.x = 0.0f;
	this->m_default_up.y = 1.0f;
	this->m_default_up.z = 0.0f;

	// text drawing members
	this->m_pSprite = NULL;
	this->m_pFont = NULL;
	this->m_iTextHeight = 0;

	this->m_b2SidedStencils = false;
	this->m_dwMaxAntialiasing = 0;
}


ID3DApplication::~ID3DApplication(void)
{
}


HRESULT ID3DApplication::Create(	int iWidth,
									int iHeight,
									int iBPP,
									BOOL bWindowed,
									LPCTSTR strTitle,
									DWORD dwFlags)
{
	if(!CreateAppWindow(	iWidth,
							iHeight,
							bWindowed,
							strTitle))
	{
		return E_FAIL;
	}

	// create D3D object
	this->m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION);
	if(!this->m_pD3D)
	{
		return E_FAIL;
	}


	// initialise the present parameters
	HRESULT hres;
	this->m_Present.hDeviceWindow = GetWindow();

	// initialise automatic z-buffering
	this->m_Present.EnableAutoDepthStencil = TRUE;

	if(IsWindowed())
	{
		this->m_Present.BackBufferWidth = GetWindowRect().right;
		this->m_Present.BackBufferHeight = GetWindowRect().bottom;
		this->m_Present.Windowed = TRUE;
		this->m_Present.BackBufferCount = 1;

		// get the desktop display mode
		D3DDISPLAYMODE dm;
		this->m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
		this->m_Present.BackBufferFormat = dm.Format;
	}
	else
	{
		// init fullscreen present parameters
		this->m_Present.BackBufferWidth = iWidth;
		this->m_Present.BackBufferHeight = iHeight;

		// bits per pixel
		switch (iBPP)
		{
		case 8:
			// forget about it... too old school for us
			return E_FAIL;
			break;

		case 16:
			this->m_Present.BackBufferFormat = D3DFMT_R5G6B5;
			break;

		case 24:
			// not supported by our engine
			return E_FAIL;
			break;

		case 32:
			this->m_Present.BackBufferFormat = D3DFMT_X8R8G8B8;
			break;

		default:
			// unknown bits per pixel value
			return E_FAIL;
		}
	}

	/* stencil */

#ifdef SHADOWS

	if( this->m_pD3D->CheckDepthStencilMatch(	D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										this->m_Present.BackBufferFormat,
										this->m_Present.BackBufferFormat,
										D3DFMT_D24FS8 ) != D3D_OK )
	{
		if(	this->m_pD3D->CheckDepthStencilMatch(	D3DADAPTER_DEFAULT,
											D3DDEVTYPE_HAL,
											this->m_Present.BackBufferFormat,
											this->m_Present.BackBufferFormat,
											D3DFMT_D24S8 ) != D3D_OK )
		{
			if ( this->m_pD3D->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,
												D3DDEVTYPE_HAL,
												this->m_Present.BackBufferFormat,
												this->m_Present.BackBufferFormat,
												D3DFMT_D24X4S4 ) != D3D_OK )
			{
				hres = this->m_pD3D->CheckDepthStencilMatch(	D3DADAPTER_DEFAULT,
														D3DDEVTYPE_HAL,
														this->m_Present.BackBufferFormat,
														this->m_Present.BackBufferFormat,
														D3DFMT_D24FS8 );
				if(FAILED(hres))
				{
					return hres;
				}
				else
				{
					//support for a d15s1 buffer
					this->m_Present.AutoDepthStencilFormat = D3DFMT_D15S1;
				}
			}
			else
			{
				//support for a d24x4s4 buffer
				this->m_Present.AutoDepthStencilFormat = D3DFMT_D24X4S4;
			}
		}
		else
		{
			//support for a d24s8 buffer
			this->m_Present.AutoDepthStencilFormat = D3DFMT_D24S8;
		}
	}
	else
	{
		//support for a d24fs8 buffer
		this->m_Present.AutoDepthStencilFormat = D3DFMT_D24FS8;
	}

#endif

#ifndef SHADOWS

	// force z-buffer in 16bit format, without stencil bits
	this->m_Present.AutoDepthStencilFormat = D3DFMT_D16;

#endif


	D3DCAPS9 caps;
	this->m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	// sets antialiasing before creating Direct3D device

	if(!this->SetAntialiasing())
	{
		if(IsWindowed())
		{
			this->m_Present.SwapEffect = D3DSWAPEFFECT_COPY;
		}
		else
		{
			this->m_Present.SwapEffect = D3DSWAPEFFECT_FLIP;
		}
	}
	else
	{
		// when using antialiasing, this value must be set
		this->m_Present.SwapEffect = D3DSWAPEFFECT_DISCARD;
	}

	// create Direct3D device
	// use the fallback mechanism to select best possible device.
	hres = this->m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										this->GetWindow(),
										D3DCREATE_HARDWARE_VERTEXPROCESSING,
										&this->m_Present,
										&this->m_pDevice);
	if(FAILED(hres))
	{
		hres = this->m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT,
											D3DDEVTYPE_HAL,
											this->GetWindow(),
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&this->m_Present,
											&this->m_pDevice);
	}
	if(FAILED(hres))
	{
		hres = this->m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											this->GetWindow(),
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&this->m_Present,
											&this->m_pDevice);
	}
	if(FAILED(hres))
	{
		// failed to create any kind of device...
		Release();
		return hres;
	}

	SetDeviceDefaults();

	// turn device antialiasing on if needed
	if(this->m_Config.GetAntialiasing() != CConfig::eANTIALIASING_0X)
	{
		this->m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	}

	this->m_b2SidedStencils = ( ( caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED ) != 0 );


	// create d3dx sprite object for text drawing
	hres = D3DXCreateSprite(this->m_pDevice, &this->m_pSprite);
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	// init the font
	hres = SetTextFont(NULL);
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	// initialise the timer
	GetTimer().Create();

	// call pure virtual OnCreate function
	hres = OnCreate();
	if(FAILED(hres))
	{
		Release();
		return hres;
	}

	SetActive(TRUE);
	return S_OK;
}


void ID3DApplication::Release(void)
{
	if(this->m_pDevice)
	{
		// call pure virtual OnRelease
		OnRelease();

		// release text writing objects
		if(this->m_pFont)
		{
			this->m_pFont->Release();
			this->m_pFont = NULL;
		}
		if(this->m_pSprite)
		{
			this->m_pSprite->Release();
			this->m_pSprite = NULL;
		}

		this->m_pDevice->Release();
		this->m_pDevice = NULL;

		if(this->m_pD3D)
		{
			this->m_pD3D->Release();
			this->m_pD3D = NULL;
		}
	}
}


void ID3DApplication::DoFlip(void)
{
	if(!IsActive())
	{
		return;
	}

	IApplication::DoFlip();

	HRESULT hres;
	hres = this->m_pDevice->Present(NULL, NULL, NULL, NULL);
	if(FAILED(hres))
	{
		hres = this->m_pDevice->TestCooperativeLevel();
		if(FAILED(hres))
		{
			// device is in lost state, and all video
			// memory resources must be reloaded.
			OnDeviceLost();

			this->m_pDevice->Reset(&this->m_Present);
			SetDeviceDefaults();

			if(FAILED(OnRestore()))
			{
				Release();
			}
		}
	}
}


void ID3DApplication::HandleWindowSizeChange(void)
{
	if(IsWindowed() && IsActive() && this->m_pDevice)
	{
		// compare new and old size and reset
		// the 3d device if needed
		if(this->m_Present.BackBufferWidth != (DWORD) GetWindowRect().right ||
			this->m_Present.BackBufferHeight != (DWORD) GetWindowRect().bottom)
		{
			// window size has changed, get the new size
			this->m_Present.BackBufferWidth = GetWindowRect().right;
			this->m_Present.BackBufferHeight = GetWindowRect().bottom;

			OnDeviceLost();

			// reset the device
			this->m_pDevice->Reset(&this->m_Present);
			SetDeviceDefaults();

			if(FAILED(OnRestore()))
			{
				Release();
			}
		}
	}
}


BOOL ID3DApplication::OnMessage(	UINT iMessage,
									WPARAM wParam,
									LPARAM lParam)
{
	BOOL ret = IApplication::OnMessage(iMessage, wParam, lParam);

	switch (iMessage)
	{
	case WM_EXITSIZEMOVE:
		HandleWindowSizeChange();
		break;

	case WM_SIZE:
		if(wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
		{
			HandleWindowSizeChange();
		}
		break;
	}

	return ret;
}


bool ID3DApplication::SetAntialiasing(void)
{
	bool bAntialiasing = false;
	BOOL bWindowed;

	if(IsWindowed())
	{
		bWindowed = TRUE;
	}
	else
	{
		bWindowed = FALSE;
	}

	// get the desktop display mode
	D3DDISPLAYMODE dm;
	this->m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);

	// get the max supported antialiasing
	this->m_pD3D->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT,
												D3DDEVTYPE_HAL,
												dm.Format,
												bWindowed,
												D3DMULTISAMPLE_NONMASKABLE,
												&this->m_dwMaxAntialiasing);

	// sets antialiasing to what it says in the config file
	// but checks checks first if it's supported

	// doesn't set antialiasing if config file's value is not supported
	// this may be due to corrupted config file or hardware change

	switch( this->m_Config.GetAntialiasing() )
	{
	case CConfig::eANTIALIASING_0X:

		this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
		this->m_Present.MultiSampleQuality = 0;

		break;

	case CConfig::eANTIALIASING_2X:

		if(this->m_dwMaxAntialiasing >= 2)
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			this->m_Present.MultiSampleQuality = 2 - 1;

			bAntialiasing = true;
		}
		else
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
			this->m_Present.MultiSampleQuality = 0;

			this->m_Config.SetAntialiasing(CConfig::eANTIALIASING_0X);
		}

		break;

	case CConfig::eANTIALIASING_4X:

		if(this->m_dwMaxAntialiasing >= 4)
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			this->m_Present.MultiSampleQuality = 4 - 1;

			bAntialiasing = true;
		}
		else
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
			this->m_Present.MultiSampleQuality = 0;

			this->m_Config.SetAntialiasing(CConfig::eANTIALIASING_0X);
		}

		break;

	case CConfig::eANTIALIASING_6X:

		if(this->m_dwMaxAntialiasing >= 6)
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			this->m_Present.MultiSampleQuality = 6 - 1;

			bAntialiasing = true;
		}
		else
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
			this->m_Present.MultiSampleQuality = 0;

			this->m_Config.SetAntialiasing(CConfig::eANTIALIASING_0X);
		}

		break;

	case CConfig::eANTIALIASING_8X:

		if(this->m_dwMaxAntialiasing >= 8)
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			this->m_Present.MultiSampleQuality = 8 - 1;

			bAntialiasing = true;
		}
		else
		{
			this->m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
			this->m_Present.MultiSampleQuality = 0;

			this->m_Config.SetAntialiasing(CConfig::eANTIALIASING_0X);
		}

		break;
	}

	return bAntialiasing;
}


void ID3DApplication::SetDeviceDefaults(void)
{
	if(!this->m_pDevice)
	{
		return;
	}

	// set the basic transformations

	// world transformation
	D3DXMATRIX	world;
	D3DXMatrixIdentity(&world);
	this->m_pDevice->SetTransform(D3DTS_WORLD, &world);

	// set the view transformation (camera)
	D3DXMATRIX	view;
	D3DXMatrixLookAtLH(&view, &m_default_eye, &m_default_at, &m_default_up);
	this->m_pDevice->SetTransform(D3DTS_VIEW, &view);

	// set projection transformation
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(	&projection,
								D3DX_PI * 0.5f, // 90 degrees
								1.0f,			// pixel aspect
								1.0f,			// near clipping plane
								1000.0f);		// far clipping plane
	this->m_pDevice->SetTransform(D3DTS_PROJECTION, &projection);


	// set the basic lights

	D3DLIGHT9	light;
	::memset(&light, 0, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

	this->m_pDevice->SetLight(0, &light);
	this->m_pDevice->LightEnable(0, TRUE);

	this->m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	this->m_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00FFFFFF);


	// set basic material
	D3DMATERIAL9	material;
	::memset(&material, 0, sizeof(D3DMATERIAL9));
	material.Diffuse = D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.25f);
	material.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	this->m_pDevice->SetMaterial(&material);

	//set basic render states

	this->m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	this->m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	this->m_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	switch( this->m_Config.GetSpecularLighting() )
	{
	case CConfig::eSPECULAR_LIGHTING_OFF:
		this->m_pDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
		break;

	case CConfig::eSPECULAR_LIGHTING_ON:
		this->m_pDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
		break;
	}

	this->m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );

	/*
	// set alpha blending states (no transparency)
	this->m_pDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	this->m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	this->m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	*/

	// set alpha blending states (with transparency)

	this->m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	this->m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	this->m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	this->m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);  
	this->m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	this->m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// set default texturing states
	for(int i = 0; i < 8; i++)
	{
		this->m_pDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		this->m_pDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		this->m_pDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		this->m_pDevice->SetSamplerState(i, D3DSAMP_MAXMIPLEVEL, 0);
	}

	//configure stencil modes - saves re-setting them every frame..
	this->m_pDevice->SetRenderState( D3DRS_STENCILENABLE,		FALSE );
	this->m_pDevice->SetRenderState( D3DRS_STENCILZFAIL,		D3DSTENCILOP_KEEP );
	this->m_pDevice->SetRenderState( D3DRS_STENCILFAIL,		D3DSTENCILOP_KEEP );
	this->m_pDevice->SetRenderState( D3DRS_STENCILREF,		0x1 );
	this->m_pDevice->SetRenderState( D3DRS_STENCILMASK,		0xffffffff );
	this->m_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK,	0xffffffff );
	this->m_pDevice->SetRenderState( D3DRS_CCW_STENCILFUNC,	D3DCMP_ALWAYS );
	this->m_pDevice->SetRenderState( D3DRS_CCW_STENCILZFAIL,	D3DSTENCILOP_KEEP );
	this->m_pDevice->SetRenderState( D3DRS_CCW_STENCILFAIL,	D3DSTENCILOP_KEEP );
	this->m_pDevice->SetRenderState( D3DRS_CCW_STENCILPASS,	D3DSTENCILOP_DECR );

	// disable shaders
	this->m_pDevice->SetPixelShader(NULL);
	this->m_pDevice->SetVertexShader(NULL);
}


HRESULT ID3DApplication::OnRestore(void)
{
	if(this->m_pFont)
	{
		this->m_pFont->OnResetDevice();
	}
	if(this->m_pSprite)
	{
		this->m_pSprite->OnResetDevice();
	}
	return S_OK;
}


void ID3DApplication::OnDeviceLost(void)
{
	if(this->m_pFont)
	{
		this->m_pFont->OnLostDevice();
	}
	if(this->m_pSprite)
	{
		this->m_pSprite->OnLostDevice();
	}
}


HRESULT ID3DApplication::SetTextFont(LOGFONT* pFont)
{
	LOGFONT lf;
	if(pFont)
	{
		// copy parameter font
		::memcpy(&lf, pFont, sizeof(LOGFONT));
	}
	else
	{
		// init default font
		::memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -12;
		lf.lfWeight = 400;
		lf.lfOutPrecision = 1;
		lf.lfClipPrecision = 2;
		lf.lfQuality = 1;
		lf.lfPitchAndFamily = 49;
		::_tcscpy_s(lf.lfFaceName, _T("Fixedsys"));
	}

	// release previous font
	if(this->m_pFont)
	{
		this->m_pFont->Release();
		this->m_pFont = NULL;
	}

	// create d3dx font
	HRESULT hres;
	hres = D3DXCreateFont(	this->m_pDevice,
							lf.lfHeight,
							lf.lfWidth,
							lf.lfWeight,
							0,
							lf.lfItalic,
							lf.lfCharSet,
							lf.lfOutPrecision,
							lf.lfQuality,
							lf.lfPitchAndFamily,
							lf.lfFaceName,
							&this->m_pFont);
	if(FAILED(hres))
	{
		return hres;
	}

	RECT rcArea = GetTextRect(0, 0, _T("W"));
	this->m_iTextHeight = rcArea.bottom;
	return S_OK;
}

HRESULT ID3DApplication::SetTextFontDefault()
{
	LOGFONT lf;

	// init font with default values
	::memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -12;
	lf.lfWeight = 400;
	lf.lfOutPrecision = 1;
	lf.lfClipPrecision = 2;
	lf.lfQuality = 1;
	lf.lfPitchAndFamily = 49;
	::_tcscpy_s(lf.lfFaceName, _T("Fixedsys"));

	// release previous font
	if(this->m_pFont)
	{
		this->m_pFont->Release();
		this->m_pFont = NULL;
	}

	// create d3dx font
	HRESULT hres;
	hres = D3DXCreateFont(	this->m_pDevice,
							lf.lfHeight,
							lf.lfWidth,
							lf.lfWeight,
							0,
							lf.lfItalic,
							lf.lfCharSet,
							lf.lfOutPrecision,
							lf.lfQuality,
							lf.lfPitchAndFamily,
							lf.lfFaceName,
							&this->m_pFont);
	if(FAILED(hres))
	{
		return hres;
	}

	return S_OK;
}

HRESULT ID3DApplication::SetTextFontParam(	int height,
											int weight,
											int italic)
{
	LOGFONT lf;

	// init font with given parameters
	::memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = height;
	lf.lfWeight = weight;
	lf.lfItalic = italic;
	lf.lfOutPrecision = 1;
	lf.lfClipPrecision = 2;
	lf.lfQuality = 1;
	lf.lfPitchAndFamily = 56;

	// release previous font
	if(this->m_pFont)
	{
		this->m_pFont->Release();
		this->m_pFont = NULL;
	}

	// create d3dx font
	HRESULT hres;
	hres = D3DXCreateFont(	this->m_pDevice,
							lf.lfHeight,
							lf.lfWidth,
							lf.lfWeight,
							0,
							lf.lfItalic,
							lf.lfCharSet,
							lf.lfOutPrecision,
							lf.lfQuality,
							lf.lfPitchAndFamily,
							lf.lfFaceName,
							&this->m_pFont);
	if(FAILED(hres))
	{
		return hres;
	}

	return S_OK;
}


void ID3DApplication::BeginText(void)
{
	if(this->m_pSprite)
	{
		this->m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	}
}


void ID3DApplication::EndText(void)
{
	if(this->m_pSprite)
	{
		this->m_pSprite->End();
	}
}


void ID3DApplication::DrawText(int iX, int iY, LPCTSTR strText, DWORD dwColor)
{
	if(this->m_pFont == NULL || this->m_pSprite == NULL)
	{
		// invalid user error...
		return;
	}

	RECT rcArea = GetTextRect(iX, iY, strText);
	this->m_pFont->DrawText(	this->m_pSprite,
						strText,
						-1,
						&rcArea,
						0,
						dwColor);
}


RECT ID3DApplication::GetTextRect(int iX, int iY, LPCTSTR strText)
{
	RECT rcArea;
	rcArea.left = iX;
	rcArea.top = iY;
	rcArea.right = 0;
	rcArea.bottom = 0;

	this->m_pFont->DrawText(	this->m_pSprite,
						strText,
						-1,
						&rcArea,
						DT_CALCRECT,
						0);
	return rcArea;
}
