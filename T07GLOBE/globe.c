/* Donik Vasilisa, 10-6, 06.06.2026 */
#include <math.h>
#include <time.h>

#include "globe.h"

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_H],
           GLB_NGeom[GLB_GRID_H][GLB_GRID_H];

static DBL Ws, Hs;
static DBL GLB_Ws, GLB_Hs;
static DBL ProjSize = 1, GLB_Wp, GLB_Hp, GLB_ProjDist = 1;

/* Rotate vector around Z axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
static VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
} /* End of 'RotateZ' function */
 
/* Rotate vector around X axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
static VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X;
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  return NewP;
} /* End of 'RotateX' function */

/* Rotate vector around Y axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
static VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  NewP.Z = P.Z * co - P.X * si;
  return NewP;
} /* End of 'RotateY' function */

COLORREF ColorTo255( VEC Color )
{
  INT
    R = Color.X * 255,
    G = Color.Y * 255,
    B = Color.Z * 255;

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

      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);

      GLB_NGeom[i][j].X = sin(theta) * sin(phi);
      GLB_NGeom[i][j].Y = cos(theta);
      GLB_NGeom[i][j].Z = sin(theta) * cos(phi);
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
  DBL t = clock() * 10 / (DBL)CLOCKS_PER_SEC, len;
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  VEC L = {1, 1, 1};

  len = sqrt(L.X * L.X
           + L.Y * L.Y
           + L.Z * L.Z);
  L.X /= len;
  L.Y /= len;
  L.Z /= len;

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL xp, yp;
      VEC P = GLB_Geom[i][j];

      P = RotateX(P, t * 3);
      P = RotateY(P, t * 1);
      P = RotateZ(P, t * 1);

      P.Z -= 1;

      xp = P.X * GLB_ProjDist / -P.Z;
      yp = P.Y * GLB_ProjDist / -P.Z;

      pnts[i][j].x = (INT)(GLB_Ws / 2 + xp * GLB_Ws / GLB_Wp);
      pnts[i][j].y = (INT)(GLB_Hs / 2 - yp * GLB_Hs / GLB_Hp);
    }

  SelectObject(hMemDC, GetStockObject(BLACK_PEN));
  for (i = 0; i < GLB_GRID_H; i++)
  {
    MoveToEx(hMemDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GLB_GRID_W; j++)
      LineTo(hMemDC, pnts[i][j].x, pnts[i][j].y);
  }

  for (j = 0; j < GLB_GRID_W; j++)
  {
    MoveToEx(hMemDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 0; i < GLB_GRID_H; i++)
      LineTo(hMemDC, pnts[i][j].x, pnts[i][j].y);
  }

  for (i = 0; i < GLB_GRID_H - 1; i++)
    for (j = 0; j < GLB_GRID_W - 1; j++)
    {
      VEC N = GLB_NGeom[i][j],
          C = {0.47, 0.8, 0.3};
      DBL nl;
      POINT pnt[4];
      N = RotateX(N, t * 3);
      N = RotateY(N, t * 3);
      N = RotateZ(N, t * 3);

      nl = N.X * L.X
         + N.Y * L.Y
         + N.Z * L.Z;
      if (nl < 0.2)
        nl = 0.2;

      C.X *= nl;
      C.Y *= nl;
      C.Z *= nl;
      SetDCBrushColor(hMemDC, ColorTo255(C));

      pnt[0] = pnts[i][j];
      pnt[1] = pnts[i][j + 1];
      pnt[2] = pnts[i + 1][j + 1];
      pnt[3] = pnts[i + 1][j];

      if ((pnt[0].x - pnt[1].x) * (pnt[0].y + pnt[1].y)
        + (pnt[1].x - pnt[2].x) * (pnt[1].y + pnt[2].y)
        + (pnt[2].x - pnt[3].x) * (pnt[2].y + pnt[3].y)
        + (pnt[3].x - pnt[0].x) * (pnt[3].y + pnt[0].y) >= 0)

        Polygon(hMemDC, pnt, 4);
    }
} /* End of 'GLB_Draw' function */
