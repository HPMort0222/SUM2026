/* Donik Vasilisa, 10-6, 06.06.2026 */
#include <windows.h>
#include <math.h>
#include <time.h>

typedef DOUBLE DBL;

#define WND_CLASS_NAME "My super-puper proj"
#define PI 3.14159265
#define GLB_GRID_W 100
#define GLB_GRID_H 100

typedef struct 
{
  DBL X, Y, Z;
} VEC;

VOID GLB_Init( DBL R );

VOID GLB_Resize( INT Ws, INT Hs );

VOID GLB_Draw( HDC hDC, DBL Rs );