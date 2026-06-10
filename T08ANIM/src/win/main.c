/* Donik Vasilisa, 10-6, 06.06.2026 */

#include <time.h>

#include "anim/rnd/rnd.h"

#define WND_CLASS_NAME "My super-puper proj"

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg,
                               WPARAM wparam,LPARAM lparam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInctance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;
  MATR m;

  m = MatrView(VecSet(0, 0, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));

  SetDbgMemHooks();

  /* Windows Class Register */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDI_QUESTION);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpfnWndProc = MyWindowFunc;
  wc.hInstance = hInstance;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "ERROR REG WIN CLASS", "ERROR", MB_OK);
    return 0;
  }

  /* Create Windows */
  hWnd = CreateWindow(WND_CLASS_NAME, "Press me..", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
    1500, 100, 500, 300, NULL, NULL, hInstance, NULL);

  /* Main Program Loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 50, 0);
  return 0;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static vd6PRIM Pr, Pr1;

  switch (Msg)
  {
  case WM_CREATE:
    VD6_RndInit(hWnd);

    SetTimer(hWnd, 50, 1, NULL);
    if (VD6_RndPrimCreate(&Pr, 4, 6))
    {
      Pr.V[0].P = VecSet(0, 0, 0);
      Pr.V[1].P = VecSet(2, 0, 0);
      Pr.V[2].P = VecSet(0, 2, 0);
      Pr.V[3].P = VecSet( 2, 2, 0);

      Pr.I[0] = 0;
      Pr.I[1] = 1;
      Pr.I[2] = 2;

      Pr.I[3] = 2;
      Pr.I[4] = 1;
      Pr.I[5] = 3;
    }
    VD6_RndPrimCreateSphere(&Pr1, 1, 30, 15);
    return 0;

  case WM_SIZE:
    VD6_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  case WM_TIMER:
    VD6_RndStart();
    VD6_RndPrimDraw(&Pr, MatrRotateY(30 * clock() / 1000));
    VD6_RndPrimDraw(&Pr1, MatrRotateY(60 * clock() / 1000));
    VD6_RndEnd();

    hDC = GetDC(hWnd);
    VD6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    VD6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    VD6_RndPrimFree(&Pr1);
    VD6_RndPrimFree(&Pr);
    VD6_RndClose();
    PostQuitMessage(0);
    KillTimer(hWnd, 30);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' func */

