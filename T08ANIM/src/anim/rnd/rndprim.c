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
  MATR wvp = MatrMulMatr4(Pr->Trans, World, VD6_RndMatrVP);
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
