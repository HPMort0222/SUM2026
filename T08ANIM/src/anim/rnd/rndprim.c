/* Donik Vasilisa, 10-6, 06.06.2026 */
#include <string.h>
#include <time.h>

#include "rnd.h"

VOID VD6_RndPrimFree( vd6PRIM *Pr )
{
  free(Pr->V);
  memset(Pr, 0, sizeof(vd6VERTEX));  /* <-- <string.h>, WinAPI, ZeroMemory */
}

BOOL VD6_RndPrimCreate( vd6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(vd6PRIM));
  size = sizeof(vd6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);
  return TRUE;
}

VOID VD6_RndPrimDraw( vd6PRIM *Pr, MATR World )
{
  INT i, t = clock() / CLOCKS_PER_SEC;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, VD6_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  /* Build vertex projects */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * VD6_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * VD6_RndFrameH / 2);
  }

  SelectObject(VD6_hRndDCFrame, GetStockObject(BLACK_PEN));
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(VD6_hRndDCFrame, pnts[Pr->I[i + 0]].x, pnts[Pr->I[i + 0]].y, NULL);
    LineTo(VD6_hRndDCFrame, pnts[Pr->I[i + 1]].x,   pnts[Pr->I[i + 1]].y);
    LineTo(VD6_hRndDCFrame, pnts[Pr->I[i + 2]].x,   pnts[Pr->I[i + 2]].y);
    LineTo(VD6_hRndDCFrame, pnts[Pr->I[i + 0]].x,   pnts[Pr->I[i + 0]].y);
  }

  free(pnts);
}

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
BOOL VD6_RndPrimCreateSphere( vd6PRIM *Pr, DBL R, INT W, INT H )
{
  INT i, j, k;
  DBL theta, phi;

  if (!VD6_RndPrimCreate(Pr, W * H, (H - 1) * (W - 1) * 2 * 3))
    return FALSE;

  /* Fill vertex array */
  for (k = 0, i = 0, theta = 0; i < H; i++, theta += PI / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * PI / (W - 1))
      Pr->V[k++].P = VecSet(R * sin(theta) * sin(phi),
                            R * cos(theta),
                            R * sin(theta) * cos(phi));

  /* Fill vertex array */
  for (k = 0, i = 0; i < H - 1; i++)
    for (j = 0; j < W - 1; j++)
    {
      /* bottom-left */
      Pr->I[k++] = i * W + j;
      Pr->I[k++] = i * W + j + 1;
      Pr->I[k++] = (i + 1) * W + j;
      /* top-right */
      Pr->I[k++] = (i + 1) * W + j;
      Pr->I[k++] = i * W + j + 1;
      Pr->I[k++] = (i + 1) * W + j + 1;
    }
  return TRUE;
} /* End of 'VD6_RndPrimCreateSphere' function */