/* Donik Vasilisa, 10-6, 01.06.2026 */
#include <windows.h>
#include <math.h>
#include <time.h>

#define WND_CLASS_NAME "My super-puper proj"
#define PI 3.14159265

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg, 
                               WPARAM wparam,LPARAM lparam );

VOID DrawSecHand( HDC hDc, HWND hWnd, POINT *P, INT Xc, INT Yc, INT M, INT L, INT H, INT W )
{
  POINT
    pnt[4] = { {-L, 0}, {-M, -M}, {0, 0}, {-M, M} },
       pnt_res[sizeof(pnt) / sizeof(pnt[0])];

  INT i, N = sizeof(pnt) / sizeof(pnt[0]),
      X, Y, dx = Xc - P->x, dy = Yc - P->y;

  DOUBLE
         angleSec = (time.wSecond + time.wMilliseconds / 1000.0) * 2.0 * PI / 60,
         len = sqrt(dx * dx + dy * dy);

  for (i = 0; i < N; i++)
  {
    pnt_res[i].x = Xc + W / 2 + sin(angleSec) * W / 3;
    pnt_res[i].y = Yc - H / 2 - cos(angleSec) * H / 3;
  }

    SetDCPenColor(hMemDC, RGB(255, 20, 255));
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, p.x, p.y);

  Polygon(hDc, pnt_res, 4);
}

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
  wc.hCursor = LoadCursor(NULL, IDC_APPSTARTING);
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
    0, 0, 120, 60, hWnd, (HMENU)31, hInstance, NULL);

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
  HPEN hPen, hOldpen;
  HDC hDc;
  PAINTSTRUCT pt;
  POINT p;
  CHAR Buf[100];
  SYSTEMTIME time;
  static INT W, H, is_flag = 0;
  static HDC hMemDC, hDCClockface;
  static BITMAP bm;
  static HBITMAP hBm, hBmClockface;
  static HFONT hFnt;

    DOUBLE
        angleMin, angleSec, angleHour;

  switch (Msg)
  {
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

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, W, H);

    ReleaseDC(hWnd, hDc);
    return 0;

  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    hDCClockface = CreateCompatibleDC(hDc);
    hBmClockface = LoadImage(NULL, "Brawl_stars2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(hBmClockface, sizeof(BITMAP), &bm);
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 3, 8, NULL);
    break;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);
    SelectObject(hDCClockface, hBmClockface);
    BitBlt(hMemDC, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, (W + bm.bmWidth) / 2 - 10, (H + bm.bmHeight) / 2 - 10, hDCClockface, 0, 0, SRCCOPY);
    StretchBlt(hMemDC, 0, 0, W, H, hDCClockface, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SelectObject(hMemDC, GetStockObject(DC_PEN));

    GetLocalTime(&time);
    TextOut(hMemDC, W / 5, H / 5, Buf, wsprintf(Buf, "%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond));

    angleMin = (time.wMinute + time.wSecond / 60.0 + time.wMilliseconds / 60000.0) * 2.0 * PI / 60;
    angleHour = (time.wHour + time.wMinute / 60.0 + time.wSecond / 3600.0 + time.wMilliseconds / 3600000.0) / 12.0 * 2 * PI;

    p.x = W / 2 + sin(angleMin) * W / 5;
    p.y = H / 2 - cos(angleMin) * H / 5;

    SetDCPenColor(hMemDC, RGB(25, 20, 25));
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, p.x, p.y);

    p.x = W / 2 + sin(angleHour) * W / 9;
    p.y = H / 2 - cos(angleHour) * H / 9;

    SetDCPenColor(hMemDC, RGB(5, 200, 255));
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, p.x, p.y);

    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    Ellipse(hMemDC, p.x - 5, p.y - 5, p.x + 5, p.y + 5);

    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
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
