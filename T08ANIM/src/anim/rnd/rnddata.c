/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "rnd.h"

HWND VD6_hRndWnd;                 /* Work window handle */
HDC VD6_hRndDCFrame;              /* Work window memory device context  */
HBITMAP VD6_hRndBmFrame;          /* Work window background bitmap handle */
INT VD6_RndFrameW, VD6_RndFrameH; /* Work window size */

DBL
   VD6_RndProjSize = 0.1,         /* Project plane fit square */
   VD6_RndProjDist = 0.1,         /* Distance to project plane from viewer (near) */
   VD6_RndProjFarClip = 300;      /* Distance to project far clip plane (far) */

MATR
    VD6_RndMatrView,              /* View coordinate system matrix */
    VD6_RndMatrProj,              /* Projection coordinate system matrix */
    VD6_RndMatrVP;                /* Stored (View * Proj) matrix */
