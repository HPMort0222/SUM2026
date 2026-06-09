/* Donik Vasilisa, 10-6, 06.06.2026 */
#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"

extern HWND VD6_hRndWnd;                 /* Work window handle */
extern HDC VD6_hRndDCFrame;              /* Work window memory device context  */
extern HBITMAP VD6_hRndBmFrame;          /* Work window background bitmap handle */
extern INT VD6_RndFrameW, VD6_RndFrameH; /* Work window size */

extern DBL
          VD6_RndProjSize,         /* Project plane fit square */
          VD6_RndProjDist,         /* Distance to project plane from viewer (near) */
          VD6_RndProjFarClip;      /* Distance to project far clip plane (far) */

extern MATR
           VD6_RndMatrView,              /* View coordinate system matrix */
           VD6_RndMatrProj,              /* Projection coordinate system matrix */
           VD6_RndMatrVP;                /* Stored (View * Proj) matrix */

typedef struct tagvd6VERTEX
{
  VEC P;  /* Vertex position */
} vd6VERTEX;

typedef struct tagvd6PRIM
{
  vd6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} vd6PRIM;


VOID VD6_RndInit( HWND hWnd );

VOID VD6_RndClose( VOID );

VOID VD6_RndResize( INT W, INT H );

VOID VD6_RndCopyFrame( HDC hDC );

VOID VD6_RndStart( VOID );

VOID VD6_RndEnd( VOID );

VOID VD6_RndProjSet( VOID );

VOID VD6_RndCamSet( VEC Loc, VEC At, VEC Up );

VOID VD6_RndPrimDraw( vd6PRIM *Pr, MATR World );

VOID VD6_RndPrimFree( vd6PRIM *Pr );

BOOL VD6_RndPrimCreate( vd6PRIM *Pr, INT NoofV, INT NoofI );

#endif /* __rnd_h_ */

