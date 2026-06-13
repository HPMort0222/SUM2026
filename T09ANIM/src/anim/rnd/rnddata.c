/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "rnd.h"

HWND VD6_hRndWnd;                 /* Work window handle */
HDC VD6_hRndDC;              /* Work window memory device context  */
INT VD6_RndW, VD6_RndH; /* Work window size */
HGLRC VD6_hRndGLRC;

DBL
   VD6_RndProjSize = 0.1,         /* Project plane fit square */
   VD6_RndProjDist = 0.1,         /* Distance to project plane from viewer (near) */
   VD6_RndProjFarClip = 300;      /* Distance to project far clip plane (far) */

MATR
    VD6_RndMatrView,              /* View coordinate system matrix */
    VD6_RndMatrProj,              /* Projection coordinate system matrix */
    VD6_RndMatrVP;                /* Stored (View * Proj) matrix */

VEC VD6_RndMatrRight;

INT VD6_MouseWheel;
