/**
 * This file declares basic vertex types.
 */

#pragma once

// include Direct3D for FVF flags
#include <d3dx9.h>

// VERTEX, basic untransformed and unlit vertex type
struct VERTEX
{
	static DWORD GetFVF() { return D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1; }

	float	x, y, z;	// vertex position
	float	nx, ny, nz;	// vertex normal
	float	tv, tu;
};


// LITVERTEX, basic untransformed and lit vertex type
struct LITVERTEX
{
	static DWORD GetFVF() { return D3DFVF_XYZ | D3DFVF_DIFFUSE; }

	float	x, y, z;
	DWORD	dwColor;
};


// TRANSLITVERTEX, basic transformed and lit vertex type
struct TRANSLITVERTEX
{
	static DWORD GetFVF() { return D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1; }

	float	x, y, z;	// vertex position (screen coordinates)
	float	rhw;		// vertex position on view z-axis
	DWORD	dwColor;	// vertex diffuse color
	float	tu, tv;
};