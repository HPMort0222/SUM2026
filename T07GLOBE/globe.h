/* Donik Vasilisa, 10-6, 06.06.2026 */
#ifndef __globe_h_
#define __globe_h_

#include <windows.h>

typedef DOUBLE DBL;

#define PI 3.14159265

#define GLB_GRID_W 20
#define GLB_GRID_H 40

typedef struct 
{
  DBL X, Y, Z;
} VEC;

VOID GLB_Init( DBL R );

VOID GLB_Resize( INT Ws, INT Hs );

VOID GLB_Draw( HDC hDC, DBL Rs );

#endif /* __globe_h_ */