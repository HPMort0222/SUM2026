/* Donik Vasilisa, 10-6, 01.06.2026 */
#include <windows.h>

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
    0, 0, 70, 60, hWnd, (HMENU)31, hInstance, NULL);
  CreateWindow("BUTTON", "Pr3ss me 2 pls..", WS_CHILD | WS_VISIBLE,
    0, 70, 70, 60, hWnd, (HMENU)32, hInstance, NULL);

  /* Main Program Loop */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam )
{
  HDC hDc;
  PAINTSTRUCT pt;
  POINT p;
  CHAR Buf[100];
  SYSTEMTIME time;
  static INT W, H;

  switch (Msg)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == 32)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    /* PostMessage(hWnd, WM_CLOSE, 0, 0); */
    return 0;

  case WM_CLOSE:
    if (MessageBox(hWnd, "Are u sure?", "EXIT", MB_YESNO) == IDNO)
      return 0;
    break;

  case WM_PAINT:
    hDc = BeginPaint(hWnd, &pt);

    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    Ellipse(hDc, p.x - 5, p.y - 5, p.x + 5, p.y + 5);
    SetDCPenColor(hDc, RGB(0, 0, 0));

    GetLocalTime(&time);
    TextOut(hDc, 130, 30, Buf, wsprintf(Buf, "%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond));

    SelectObject(hDc, GetStockObject(GRAY_BRUSH));
    SelectObject(hDc, GetStockObject(BLACK_PEN));
    Rectangle(hDc, 100, H / 3 + 100, W / 3 + 100, 120);

    EndPaint(hWnd, &pt);
    DeleteDC(hDc);
    return 0;

  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 500, NULL);
    break;

  case WM_TIMER:
    InvalidateRect(hWnd, NULL, TRUE);
    break;

  case WM_DESTROY:
    PostQuitMessage(30);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' func */
