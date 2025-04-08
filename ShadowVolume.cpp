#include "ShadowVolume.h"

CShadowVolume::CShadowVolume()
{
}

CShadowVolume::~CShadowVolume()
{
}

void CShadowVolume::Reset()
{ 
	this->m_dwNumVertices = 0L; 
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the volume geometry, assumes that stencil buffer is already
//		 configured correctly.
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetFVF(D3DFVF_XYZ);
	pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

    return pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
									this->m_dwNumVertices / 3,
									this->m_pVertices,
									sizeof(D3DXVECTOR3) );
}

//-----------------------------------------------------------------------------
// Name: BuildFromMesh()
// Desc: Takes a mesh as input, and uses it to build a shadowvolume. The
//       technique used considers each triangle of the mesh, and adds it's
//       edges to a temporary list. The edge list is maintained, such that
//       only silohuette edges are kept. Finally, the silohuette edges are
//       extruded to make the shadow volume vertex list.
//-----------------------------------------------------------------------------
HRESULT CShadowVolume::BuildFromMesh(	LPD3DXMESH pMesh, 
										D3DXVECTOR3 vLight)
{
	// Note: the MESHVERTEX format depends on the FVF of the mesh
    struct MESHVERTEX { D3DXVECTOR3 p, n; FLOAT tu, tv; };

    MESHVERTEX* pVertices;
    WORD*       pIndices;

    // Lock the geometry buffers
    pMesh->LockVertexBuffer( 0L, (LPVOID*)&pVertices );
    pMesh->LockIndexBuffer( 0L, (LPVOID*)&pIndices );
    DWORD dwNumFaces = pMesh->GetNumFaces();

    // Allocate a temporary edge list
    WORD* pEdges = new WORD[dwNumFaces*6];

    if( pEdges == NULL )
    {
        pMesh->UnlockVertexBuffer();
        pMesh->UnlockIndexBuffer();
        return E_OUTOFMEMORY;
    }

    DWORD dwNumEdges = 0;

    // For each face
    for(DWORD i = 0; i < dwNumFaces; i++)
    {
        WORD wFace0 = pIndices[ 3 * i + 0 ];
        WORD wFace1 = pIndices[ 3 * i + 1 ];
        WORD wFace2 = pIndices[ 3 * i + 2 ];

        D3DXVECTOR3 v0 = pVertices[ wFace0 ].p;
        D3DXVECTOR3 v1 = pVertices[ wFace1 ].p;
        D3DXVECTOR3 v2 = pVertices[ wFace2 ].p;

        // Transform vertices or transform light?
        D3DXVECTOR3 vCross1(v2-v1);
        D3DXVECTOR3 vCross2(v1-v0);
        D3DXVECTOR3 vNormal;
        D3DXVec3Cross( &vNormal, &vCross1, &vCross2 );

        if( D3DXVec3Dot( &vNormal, &vLight ) >= 0.0f )
        {
            this->AddEdge( pEdges, dwNumEdges, wFace0, wFace1 );
            this->AddEdge( pEdges, dwNumEdges, wFace1, wFace2 );
            this->AddEdge( pEdges, dwNumEdges, wFace2, wFace0 );
        }
    }

    for(DWORD i = 0; i < dwNumEdges; i++)
    {
        D3DXVECTOR3 v1 = pVertices[pEdges[2*i+0]].p;
        D3DXVECTOR3 v2 = pVertices[pEdges[2*i+1]].p;
		D3DXVECTOR3 v3 = v1 - vLight*500;
		D3DXVECTOR3 v4 = v2 - vLight*500;

        // Add a quad (two triangles) to the vertex list
		this->m_pVertices[m_dwNumVertices++] = v1;
        this->m_pVertices[m_dwNumVertices++] = v2;
        this->m_pVertices[m_dwNumVertices++] = v3;

        this->m_pVertices[m_dwNumVertices++] = v2;
        this->m_pVertices[m_dwNumVertices++] = v4;
        this->m_pVertices[m_dwNumVertices++] = v3;
    }

    // Delete the temporary edge list
    delete[] pEdges;

    // Unlock the geometry buffers
    pMesh->UnlockVertexBuffer();
    pMesh->UnlockIndexBuffer();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: AddEdge()
// Desc: Adds an edge to a list of silohuette edges of a shadow volume.
//-----------------------------------------------------------------------------
void CShadowVolume::AddEdge(WORD* pEdges,
							DWORD& dwNumEdges,
							WORD v0,
							WORD v1 )
{
    // Remove interior edges (which appear in the list twice)
    for(DWORD i=0; i < dwNumEdges; i++)
    {
        if( ( pEdges[2*i+0] == v0 && pEdges[2*i+1] == v1 ) ||
            ( pEdges[2*i+0] == v1 && pEdges[2*i+1] == v0 ) )
        {
            if( dwNumEdges > 1 )
            {
                pEdges[2*i+0] = pEdges[2*(dwNumEdges-1)+0];
                pEdges[2*i+1] = pEdges[2*(dwNumEdges-1)+1];
            }

            dwNumEdges--;
            return;
        }
    }

    pEdges[2*dwNumEdges+0] = v0;
    pEdges[2*dwNumEdges+1] = v1;
    dwNumEdges++;
}
