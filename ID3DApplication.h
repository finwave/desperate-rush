/**
 * An abstract class implements Direct3D version 9
 * initialisation and main loop.
 *
 * Requires:
 * Project wide define: DIRECT3D_VERSION=0x900
 * Libraries: dxguid.lib d3d9.lib d3dx9.lib
 */

#pragma once

//#define SHADOWS
#define AMBIENT_LIGHT D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f)

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#include "IApplication.h"
#include "Config.h"

// include Direct3D stuff
#include <d3d9.h>
#include <d3dx9.h>


class ID3DApplication : public IApplication
{
public:
	ID3DApplication(void);
	virtual ~ID3DApplication(void);

	/**
	 * Create
	 * initialise Direct3D application
	 * @param iWidth screen resolution width
	 * @param iHeight screen resolution height
	 * @param iBPP bits per pixel (16 or 32)
	 * @param bWindowed TRUE if started in windowed mode
	 * @param strTitle application title text
	 * @param dwFlags additional startup flags
	 * @return S_OK, or system wide error code
	 */
	HRESULT Create(	int iWidth,
					int iHeight,
					int iBPP,
					BOOL bWindowed,
					LPCTSTR strTitle,
					DWORD dwFlags);

	/**
	 * Release
	 * release Direct3D resources and shutdown
	 */
	virtual void Release(void);

	/**
	 * perform flip operation, copy backbuffer to screen
	 */
	virtual void DoFlip(void);

	/**
	 * OnRestore
	 * virtual handler is called when we are ready to
	 * restore the lost video resources
	 */
	virtual HRESULT OnRestore(void);

	/**
	 * OnDeviceLost
	 * virtual handler is called when video memory resources
	 * have been lost.
	 */
	virtual void OnDeviceLost(void);

	/**
	 * GetD3D
	 * @return pointer to Direct3D object
	 */
	inline LPDIRECT3D9 GetD3D() { return m_pD3D; }

	/**
	 * GetDevice
	 * @return pointer to direct3d device object
	 */
	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }

	/**
	 * SetTextFont
	 * initialise text drawing system with given font
	 * @param pFont pointer to font specs, or NULL to use
	 * default font
	 * @return S_OK, or error code
	 */
	HRESULT SetTextFont(LOGFONT* pFont);

	/**
	 * SetTextFontDefault
	 * initialise text drawing system with default values
	 * @return S_OK, or error code
	 */
	HRESULT SetTextFontDefault();

	/**
	 * SetTextFontParam
	 * initialise text drawing system with given parameters
	 * and default values
	 * @param pFont pointer to font specs, or NULL to use
	 * @param height font height
	 * @param weight font weight (400 = normal, 700 = bold)
	 * @param italic byte defining italic attribute
	 * default font
	 * @return S_OK, or error code
	 */
	HRESULT SetTextFontParam(	int height,
								int weight,
								int italic);

	/**
	 * BeginText
	 * prepare system for text drawing
	 */
	void BeginText(void);

	/**
	 * EndText
	 * call when finished drawing text
	 */
	void EndText(void);

	/**
	 * DrawText
	 * Draw text using 3d device. The BeginText must be called
	 * before alling this function.
	 * @param iX x-coordinate of text (in pixels)
	 * @param iY y-coordinate of text (in pixels)
	 * @param strText text to draw
	 * @param dwColor color of the text in 32bit value
	 */
	void DrawText(int iX, int iY, LPCTSTR strText, DWORD dwColor);

	/**
	 * GetTextRect
	 * computes rectangle that is required with given text
	 * @param iX x-coordinate of text (in pixels)
	 * @param iY y-coordinate of text (in pixels)
	 * @param strText text which rect to compute
	 * @return text rectangle
	 */
	RECT GetTextRect(int iX, int iY, LPCTSTR strText);

	/**
	 * GetTextHeight
	 * @return height on text in pixels
	 */
	inline int GetTextHeight() const { return m_iTextHeight; }

	inline bool Get2SidedStencil() { return this->m_b2SidedStencils; }
	inline DWORD GetMaxAntialiasing() { return this->m_dwMaxAntialiasing; }

	/**
	 * GetConfig
	 * @return reference to config
	 */
	inline CConfig& GetConfig() { return this->m_Config; }

private:
	/**
	 * OnMessage
	 * windows message handler. Interrupt messages relating
	 * to window size change
	 */
	virtual BOOL OnMessage(UINT iMessage, WPARAM wParam, LPARAM lParam);

	/**
	 * HandleWindowSizeChange
	 * function resets the 3d device with current
	 * window size. All device states are lost in
	 * resize operation.
	 */
	void HandleWindowSizeChange(void);

	bool SetAntialiasing(void);

	/**
	 * SetDeviceDefaults
	 * set some basic settings to 3d device to be able to
	 * see something right away
	 */
	void SetDeviceDefaults(void);

	CConfig					m_Config;

	// Direct3D members
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_Present;
	D3DXVECTOR3				m_default_eye;
	D3DXVECTOR3				m_default_at;
	D3DXVECTOR3				m_default_up;

	// variables for text drawing
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;
	int						m_iTextHeight;

	// support for 2-sided stencil
	bool m_b2SidedStencils;

	// variable to represent max antialiasing
	// current hardware can support
	// 0 = 0x, 1 = 2x, 2 = 4x, 3 = 6x, 4 = 8x
	DWORD					m_dwMaxAntialiasing;
};