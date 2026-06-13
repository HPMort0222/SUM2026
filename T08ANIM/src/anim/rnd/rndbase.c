/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "rnd.h"

VOID VD6_RndInit( HWND hWnd )
{
  HDC hDC = GetDC(hWnd);

  VD6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);

  VD6_hRndWnd = hWnd;

  VD6_hRndBmFrame = NULL;
  VD6_RndResize(100, 100);
  VD6_RndCamSet(VecSetAll(5), VecSetAll(0), VecSet(0, 1, 0));
}

VOID VD6_RndClose( VOID )
{
  DeleteObject(VD6_hRndBmFrame);
  DeleteDC(VD6_hRndDCFrame);
}

VOID VD6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(VD6_hRndWnd);

  if (VD6_hRndBmFrame != NULL)
    DeleteObject(VD6_hRndBmFrame);
  VD6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(VD6_hRndWnd, hDC);

  SelectObject(VD6_hRndDCFrame, VD6_hRndBmFrame);

  /* сохраняем размеры */
  VD6_RndFrameW = W;
  VD6_RndFrameH = H;

  /* пересчитываем проекию */
  VD6_RndProjSet();
}

VOID VD6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, VD6_RndFrameW, VD6_RndFrameH,
    VD6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID VD6_RndStart( VOID )
{
  SelectObject(VD6_hRndDCFrame, GetStockObject(WHITE_PEN));
  Rectangle(VD6_hRndDCFrame, 0, VD6_RndFrameH, VD6_RndFrameW, 0);
}

VOID VD6_RndEnd( VOID )
{
}

VOID VD6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = VD6_RndProjSize;
  /* Correct aspect ratio */
  if (VD6_RndFrameW > VD6_RndFrameH)
    rx *= (DBL)VD6_RndFrameW / VD6_RndFrameH;
  else
    ry *= (DBL)VD6_RndFrameH / VD6_RndFrameW;
  VD6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      VD6_RndProjDist, VD6_RndProjFarClip);
  VD6_RndMatrVP = MatrMulMatr(VD6_RndMatrView, VD6_RndMatrProj);
}

VOID VD6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VD6_RndMatrView = MatrView(Loc, At, Up);
  VD6_RndMatrRight = MatrRight(Loc, At, Up);
  VD6_RndMatrVP = MatrMulMatr(VD6_RndMatrView, VD6_RndMatrProj);
}

