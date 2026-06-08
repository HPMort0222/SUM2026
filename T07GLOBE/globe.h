/* Donik Vasilisa, 10-6, 06.06.2026 */
#ifndef __globe_h_
#define __globe_h_

#include <windows.h>
#include "MTH.h"

#define GLB_GRID_W 100
#define GLB_GRID_H 160

#define GLB_MAX(A,B)((A) < (B) ? (B) : (A))
#define GLB_MIN(A,B)((A) < (B) ? (A) : (B))

VOID GLB_Init( DBL R );

VOID GLB_Resize( INT Ws, INT Hs );

VOID GLB_Draw( HDC hDC, DBL Rs );

#endif /* __globe_h_ */