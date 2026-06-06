/* Donik Vasilisa, 10-6, 06.06.2026 */

#include "globe.h"

static DBL Ws, Hs;
static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_H];
static INT GLB_Ws, GLB_Hs;

VOID GLB_Init( DBL R )
{
  INT i, j;

  for (i = 0; i < GLB_GRID_H; i++)
  {
    DBL theta = i * PI / (GLB_GRID_H - 1);

    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL phi = j * 2 * PI / (GLB_GRID_W - 1);

      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
  }
}

VOID GLB_Resize( INT Ws, INT Hs )
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;
}

VOID GLB_Draw( HDC hMemDC, DBL Rs )
{
  INT i, j;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      pnts[i][j].x = GLB_Ws / 2 + GLB_Geom[i][j].X;
      pnts[i][j].y = GLB_Hs / 2 + GLB_Geom[i][j].Y;

      Ellipse(hMemDC, pnts[i][j].x - Rs, pnts[i][j].y - Rs,
              pnts[i][j].x + Rs, pnts[i][j].y + Rs);

    }
}
