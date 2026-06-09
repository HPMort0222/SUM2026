/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "globe.h"
#include "timer.h"

#define WND_CLASS_NAME "My super-puper proj"

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg,
                               WPARAM wparam,LPARAM lparam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInctance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

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
  CreateWindow("BUTTON", "Press me..", WS_CHILD | WS_VISIBLE,
    0, 100, 120, 60, hWnd, (HMENU)31, hInstance, NULL);

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
  PAINTSTRUCT pt;
  POINT p;
  CHAR Buf[100];
  SYSTEMTIME time;
  static INT W, H, is_flag = 0;
  static HDC hMemDC;
  static BITMAP bm;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);

    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 50, 1, NULL);

    GLB_TimerInit();
    GLB_Init(0.3);
    break;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    GLB_Resize(W, H);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, W, H);

    ReleaseDC(hWnd, hDc);
    return 0;

  case WM_COMMAND:
    if (LOWORD(wParam) == 31)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;

  case WM_CLOSE:
    if (MessageBox(hWnd, "Are u sure?", "EXIT", MB_YESNO) == IDNO)
      return 0;
    break;

  case WM_ERASEBKGND:
    return 0;

  case WM_PAINT:
    hDc = BeginPaint(hWnd, &pt);
    BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &pt);
    return 0;

  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_TIMER:
    GLB_TimerResponse();
    SelectObject(hMemDC, hBm);

    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SelectObject(hMemDC, GetStockObject(DC_PEN));

    SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
    Rectangle(hMemDC, 0, H, W, 0);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    GLB_Draw(hMemDC, 2.0);

    GetLocalTime(&time);
    TextOut(hMemDC, W / 5, H / 5, Buf, wsprintf(Buf, "%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond));
    TextOut(hMemDC, W / 7, H / 7, Buf, sprintf(Buf, "FPS : %05f", GLB_FPS));
    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    Ellipse(hMemDC, p.x - 5, p.y - 5, p.x + 5, p.y + 5);

    InvalidateRect(hWnd, NULL, FALSE);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' func */
