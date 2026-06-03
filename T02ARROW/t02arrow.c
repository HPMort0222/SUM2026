/* Donik Vasilisa, 10-6, 01.06.2026 */
#include <windows.h>
#include <math.h>

#define WND_CLASS_NAME "My super-puper proj"

LRESULT CALLBACK MyWindowFunc( HWND hwnd, UINT Msg, 
                               WPARAM wparam,LPARAM lparam );

VOID DrawArrow( HDC hDc, HWND hWnd, POINT *P, INT Xc, INT Yc, INT W, INT L )
{
  POINT
    pnt[4] = { {-L, 0}, {-W, -W}, {0, 0}, {-W, W} },
       pnt_res[sizeof(pnt) / sizeof(pnt[0])];

  INT i, N = sizeof(pnt) / sizeof(pnt[0]),
      X, Y, dx = Xc - P->x, dy = Yc - P->y;

  DOUBLE cosa, sina, len = sqrt(dx * dx + dy * dy);

  X = dx * L / len + Xc;
  Y = dy * L / len + Yc;

  cosa = dx / len,
  sina = dy / len;

  for (i = 0; i < N; i++)
  {
    pnt_res[i].x = Xc + pnt[i].x * cosa + pnt[i].y * sina;
    pnt_res[i].y = Yc - pnt[i].y * cosa + pnt[i].x * sina;
  }

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
  CreateWindow("BUTTON", "Pr3ss me 2 pls..", WS_CHILD | WS_VISIBLE,
    0, 70, 120, 60, hWnd, (HMENU)32, hInstance, NULL);
  CreateWindow("BUTTON", "End pr3ss me 2 pls..", WS_CHILD | WS_VISIBLE,
    0, 140, 120, 60, hWnd, (HMENU)33, hInstance, NULL);
  CreateWindow("BUTTON", "Pr3ss me 2 pls..", WS_CHILD | WS_VISIBLE,
    0, 210, 120, 60, hWnd, (HMENU)34, hInstance, NULL);

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
  INT i, j;
  CHAR Buf[100];
  SYSTEMTIME time;
  static INT W, H, is_flag = 0;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == 31)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    if (LOWORD(wParam) == 32)
      is_flag = 0;
    if (LOWORD(wParam) == 33)
      is_flag = 1;
    if (LOWORD(wParam) == 34)
      is_flag = 2;
    /* PostMessage(hWnd, WM_CLOSE, 0, 0); */
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
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 300, 8, NULL);
    break;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDC, GetStockObject(LTGRAY_BRUSH));
    SelectObject(hMemDC, GetStockObject(BLACK_PEN));
    Rectangle(hMemDC, 0, H, W, 0);
    GetLocalTime(&time);
    TextOut(hMemDC, W / 15, H / 15, Buf, wsprintf(Buf, "%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond));

    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    Ellipse(hMemDC, p.x - 5, p.y - 5, p.x + 5, p.y + 5);

    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));

    if (is_flag == 0)
    for (i = 0; i < 3000; i += 100)
      for (j = 0; j < 3000; j += 100)
        DrawArrow(hMemDC, hWnd, &p, i, j, 15, 40);

    if (is_flag == 1)
      for (i = 1; i < 3000; i += 100)
        for (j = 1; j < 3000; j += 100)
        {
          SelectObject(hMemDC, GetStockObject(DC_BRUSH));
          SelectObject(hMemDC, GetStockObject(DC_PEN));
          SetDCPenColor(hMemDC, RGB(rand() % i, rand() % j, rand() % (i + j)));
          SetDCBrushColor(hMemDC, RGB(rand() % i, rand() % j, rand() % (i + j)));
          DrawArrow(hMemDC, hWnd, &p, rand() % i, rand() % j, 15, 40);
        }

    srand(30);
    if (is_flag == 2)
      for (i = 1; i < 3000; i += 100)
        for (j = 1; j < 3000; j += 100)
          DrawArrow(hMemDC, hWnd, &p, rand() % i, rand() % j, 15, 40);
    
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
