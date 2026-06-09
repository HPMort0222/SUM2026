/* Donik Vasilisa, 10-6, 06.06.2026 */
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "globe.h"

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_H],
           GLB_NGeom[GLB_GRID_H][GLB_GRID_H];

static DBL Ws, Hs;
static DBL GLB_Ws, GLB_Hs;
static DBL ProjSize = 1, GLB_Wp, GLB_Hp, GLB_ProjDist = 1;

COLORREF ColorTo255( VEC Color, INT I )
{
  INT
    R = Color.X * 255 * (I % 6) - 70,
    G = Color.Y * 255 * (I % 6) - 70,
    B = Color.Z * 255 * (I % 6) - 70;

  R = GLB_MIN(255, GLB_MAX(0, R));
  G = GLB_MIN(255, GLB_MAX(0, G));
  B = GLB_MIN(255, GLB_MAX(0, B));

  return RGB(R, G, B);
}

VOID GLB_Init( DBL R )
{
  INT i, j;

  for (i = 0; i < GLB_GRID_H; i++)
  {
    DBL theta = i * PI / (GLB_GRID_H - 1);

    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL phi = j * 2 * PI / (GLB_GRID_W - 1);

      GLB_Geom[i][j].X = 0.8 * R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = 0.8 * R * sin(theta) * cos(phi);

      GLB_NGeom[i][j].X = sin(theta) * sin(phi);
      GLB_NGeom[i][j].Y = cos(theta);
      GLB_NGeom[i][j].Z = sin(theta) * cos(phi);
    }
  }

  for (i = 0; i < GLB_GRID_H; i++)
  {
    for (j = 0; j < GLB_GRID_W; j++)
    {
      VEC N1 = VecCrossVec(VecSubVec(GLB_NGeom[i][j + 1], GLB_NGeom[i][j]), VecSubVec(GLB_NGeom[i + 1][j], GLB_NGeom[i][j]));
      VEC N2 = VecCrossVec(VecSubVec(GLB_NGeom[i][j + 1], GLB_NGeom[i][j]), VecSubVec(GLB_NGeom[i + 1][j], GLB_NGeom[i][j]));
      GLB_NGeom[i][j] = VecNeg(VecNormalize(VecAddVec(N1, N2)));
      
    }
  }
} /* End of 'GLB_Init' function */

VOID GLB_Resize( INT Ws, INT Hs )
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;

  if (GLB_Ws >= GLB_Hs)
    GLB_Wp = ProjSize * GLB_Ws / GLB_Hs, GLB_Hp = ProjSize;
  else
    GLB_Hp = ProjSize * GLB_Hs / GLB_Ws, GLB_Wp = ProjSize;
} /* End of 'GLB_Resize' function */

VOID GLB_Draw( HDC hMemDC, DBL Rs )
{
  INT i, j;
  DBL t = clock() / (DBL)CLOCKS_PER_SEC;
  MATR m;
  VEC L, P, N;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];

  L = VecNormalize(VecSet(1, 1, sin(t)));

  m = MatrMulMatr4(MatrRotateX(sin(t)), MatrRotateY(sin(t)), MatrRotateZ(3 * sin(t)), MatrTranslate(VecSet(0, 0, 0)));

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL xp, yp;
      P =  VectorTransform(GLB_Geom[i][j], m);
      P.Z -= 1;

      xp = P.X * GLB_ProjDist / -P.Z;
      yp = P.Y * GLB_ProjDist / -P.Z;

      pnts[i][j].x = (INT)(GLB_Ws / 2 + xp * GLB_Ws / GLB_Wp + 4 * P.Z);
      pnts[i][j].y = (INT)(GLB_Hs / 2 - yp * GLB_Hs / GLB_Hp);
    }

  SelectObject(hMemDC, GetStockObject(DC_BRUSH));
  for (i = 0; i < GLB_GRID_H - 1; i++)
    for (j = 0; j < GLB_GRID_W - 1; j++)
    {
      VEC C = {0.34, 0.21, 0.6};
      DBL nl;
      POINT pnt[4];

      N = VectorTransform(GLB_NGeom[i][j], m);

      nl = VecDotVec(N, L);
      if (nl < 0.2)
        nl = 0.2;

      C = VecMulNum(C, nl);

      pnt[0] = pnts[i][j];
      pnt[1] = pnts[i][j + 1];
      pnt[2] = pnts[i + 1][j + 1];
      pnt[3] = pnts[i + 1][j];

      SetDCBrushColor(hMemDC, ColorTo255(C, i + t * 10));

      if ((pnt[0].x - pnt[1].x) * (pnt[0].y + pnt[1].y)
        + (pnt[1].x - pnt[2].x) * (pnt[1].y + pnt[2].y)
        + (pnt[2].x - pnt[3].x) * (pnt[2].y + pnt[3].y)
        + (pnt[3].x - pnt[0].x) * (pnt[3].y + pnt[0].y) >= 0)
        Polygon(hMemDC, pnt, 4);
    }
} /* End of 'GLB_Draw' function */
