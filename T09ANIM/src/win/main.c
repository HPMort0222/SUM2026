/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "units/units.h"

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
  INT i;

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

  for (i = 0; i < 10; i++)
    VD6_AnimAddUnit(VD6_AnimUnitCreateBBalls());
  VD6_AnimAddUnit(VD6_AnimUnitCreateCow());
  VD6_AnimAddUnit(VD6_AnimUnitCreateControl());

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
  PAINTSTRUCT pt;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 50, 1, NULL);
    VD6_AnimInit(hWnd);
    return 0;

  case WM_SIZE:
    VD6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  case WM_TIMER:
    VD6_AnimRender();
    VD6_AnimCopyFrame();
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &pt);
    VD6_AnimCopyFrame();
    EndPaint(hWnd, &pt);
    return 0;

  case WM_DESTROY:
    VD6_AnimClose();
    PostQuitMessage(0);
    KillTimer(hWnd, 30);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' func */

