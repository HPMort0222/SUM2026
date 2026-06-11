/* FILE NAME: mth.h
 * PURPOSE: 3D render declaration module.
 * PROGRAMMER: VG4
 * DATE: 08.06.2026
 */

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

/***
 *  Primitive handle
 ***/

/* Vertex representation type */
typedef struct tagvd6VERTEX
{
  VEC P;  /* Vertex position */
} vd6VERTEX;

/* Primitive representation type */
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

/* Primitive create function.
 * ARGUMENTS:
 *   - primitive to be create:
 *       vg4PRIM *Pr;
 *   - number of vertecis and indices:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL VD6_RndPrimCreate( vd6PRIM *Pr, INT NoofV, INT NoofI );

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be free:
 *       vg4PRIM *Pr;
 * RETURNS: None.
 */
VOID VD6_RndPrimFree( vd6PRIM *Pr );

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive to be draw:
 *       vg4PRIM *Pr;
 *   - transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID VD6_RndPrimDraw( vd6PRIM *Pr, MATR World );

/* Primitive load function.
 * ARGUMENTS:
 *   - primitive to be load:
 *       vg4PRIM *Pr;
 *   - primitve filename (.OBJ):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL VD6_RndPrimLoad( vd6PRIM *Pr, CHAR *FileName );

/* Create sphere primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vg4PRIM *Pr;
 *   - sphere radius:
 *       DBL R;
 *   - split parts counts:
 *       INT W, H;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL VD6_RndPrimCreateSphere( vd6PRIM *Pr, DBL R, INT W, INT H );

BOOL VD6_RndPrimCreateCylinder( vd6PRIM *Pr, DBL R, INT W, INT H );

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive to be load:
 *       vg4PRIM *Pr;
 *   - primitve filename (.OBJ):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FLASE otherwise.
 */
BOOL VD6_RndPrimLoad( vd6PRIM *Pr, CHAR *FileName );

#endif /* __rnd_h_ */

