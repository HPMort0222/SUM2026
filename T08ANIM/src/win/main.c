/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "def.h"
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
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  PAINTSTRUCT ps;
  static INT W, H;
  static vd6PRIM Pr;

  switch (Msg)
  {
  case WM_CREATE:
    VD6_RndInit(hWnd);

    if (VD6_RndPrimCreate(&Pr, 4, 6))
    {
      Pr.V[0].P = VecSet(0, 0, 0);
      Pr.V[1].P = VecSet(2, 0, 0);
      Pr.V[2].P = VecSet(0, 2, 0);
      Pr.V[3].P = VecSet(2, 2, 0);

      Pr.I[0] = 0;
      Pr.I[1] = 1;
      Pr.I[2] = 2;

      Pr.I[3] = 2;
      Pr.I[4] = 1;
      Pr.I[5] = 3;
    }
    return 0;

  case WM_SIZE:
    VD6_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  case WM_TIMER:
    VD6_RndStart();
    hDc = GetDC(hWnd);
    VD6_RndPrimDraw(&Pr, MatrRotateY(30 * clock() / 1000));
    ReleaseDC(hWnd, hDc);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    VD6_RndCopyFrame(hDc);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    VD6_RndClose();
    VD6_RndPrimFree(&Pr);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' func */

