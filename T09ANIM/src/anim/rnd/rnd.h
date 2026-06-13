/* FILE NAME: mth.h
 * PURPOSE: 3D render declaration module.
 * PROGRAMMER: VG4
 * DATE: 08.06.2026
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include "glew.h"

#include "def.h"

extern HWND VD6_hRndWnd;                 /* Work window handle */
extern HDC VD6_hRndDC;                   /* Work window memory device context  */
extern INT VD6_RndW, VD6_RndH; /* Work window size */
extern HGLRC VD6_hRndGLRC;

extern DBL
  VD6_RndProjSize,         /* Project plane fit square */
  VD6_RndProjDist,         /* Distance to project plane from viewer (near) */
  VD6_RndProjFarClip;      /* Distance to project far clip plane (far) */

extern MATR
  VD6_RndMatrView,              /* View coordinate system matrix */
  VD6_RndMatrProj,              /* Projection coordinate system matrix */
  VD6_RndMatrVP;                /* Stored (View * Proj) matrix */

extern VEC VD6_RndMatrRight;

/***
 * Primitive support
 ***/

/* Vertex representation type */
typedef struct tagvd6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinates */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} vd6VERTEX;

/* Primitive type */
typedef enum tagvd6PRIM_TYPE
{
  VD6_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  VD6_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  VD6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
} vd6PRIM_TYPE;


/* Primitive representation type */
typedef struct tagvd6PRIM
{
  vd6PRIM_TYPE Type; /* Primitive type */

  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */

  INT NumOfElements; /* Number of indices/vecrtices */

  VEC MinBB, MaxBB;  /* Bound box */

  MATR Trans;   /* Additional transformation matrix */
} vd6PRIM;

VOID VD6_RndInit( HWND hWnd );

VOID VD6_RndClose( VOID );

VOID VD6_RndResize( INT W, INT H );

VOID VD6_RndCopyFrame( VOID );

VOID VD6_RndStart( VOID );

VOID VD6_RndEnd( VOID );

VOID VD6_RndProjSet( VOID );

VOID VD6_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Create primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       vd6PRIM *Pr;
 *   - primitive type:
 *       vd6PRIM_TYPE Type;
 *   - vertex attributes array:
 *       vd6VERTEX *V;
 *   - vertex attributes array size:
 *       INT NoofV;
 *   - primitive vertex index array:
 *       INT *Ind;
 *   - primitive vertex index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID VD6_RndPrimCreate( vd6PRIM *Pr, vd6PRIM_TYPE Type,
                        vd6VERTEX *V, INT NoofV, INT *Ind, INT NoofI );

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

VOID VD6_RndPrimTriMeshAutoNormals( vd6VERTEX *V, INT NoofV, INT *Ind, INT NoofI );

#endif /* __rnd_h_ */

