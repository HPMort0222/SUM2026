/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "rnd.h"

#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

VOID VD6_RndInit( HWND hWnd )
{
  INT i, i1[10];
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  VD6_hRndWnd = hWnd;

  /* Prepare frame compatible device contesxt */
  VD6_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(VD6_hRndDC, &pfd);

  DescribePixelFormat(VD6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(VD6_hRndDC, i, &pfd);

  /* OpenGL init: rendering context setup */
  VD6_hRndGLRC = wglCreateContext(VD6_hRndDC);
  wglMakeCurrent(VD6_hRndDC, VD6_hRndGLRC);

  if (glewInit() != GLEW_OK)
  exit(0);

  /* Render parameters setup */
  VD6_RndProjSize = 0.1;
  VD6_RndProjDist = VD6_RndProjSize;
  VD6_RndProjFarClip = 300;
  VD6_RndW = 47;
  VD6_RndH = 47;
  VD6_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));

  wglChoosePixelFormatARB(VD6_hRndDC, PixelAttribs, NULL, 1, i1, &i);
  hRC = wglCreateContextAttribsARB(VD6_hRndDC, NULL, ContextAttribs);

  if (hRC != NULL)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(VD6_hRndGLRC);
    VD6_hRndGLRC = hRC;
    wglMakeCurrent(VD6_hRndDC, VD6_hRndGLRC);
  }

  glEnable(GL_DEPTH_TEST);
}

VOID VD6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(VD6_hRndGLRC);
  ReleaseDC(VD6_hRndWnd, VD6_hRndDC);
}

VOID VD6_RndResize( INT W, INT H )
{
 glViewport(0, 0, W, H);
 
  /* Setup projection */
  VD6_RndW = W;
  VD6_RndH = H;
  VD6_RndProjSet();
}

VOID VD6_RndCopyFrame( VOID )
{
  SwapBuffers(VD6_hRndDC);
}

VOID VD6_RndStart( VOID )
{
  VEC4 ClearColor = {Rnd0(), Rnd0(), Rnd0(), 1};
  FLT DepthClearValue = 1;
 
  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
}

VOID VD6_RndEnd( VOID )
{
  glFinish();
}

VOID VD6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = VD6_RndProjSize;
  /* Correct aspect ratio */
  if (VD6_RndW > VD6_RndH)
    rx *= (DBL)VD6_RndW / VD6_RndH;
  else
    ry *= (DBL)VD6_RndH / VD6_RndW;
  VD6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      VD6_RndProjDist, VD6_RndProjFarClip);
  VD6_RndMatrVP = MatrMulMatr(VD6_RndMatrView, VD6_RndMatrProj);
}

VOID VD6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VD6_RndMatrView = MatrView(Loc, At, Up);
  VD6_RndMatrVP = MatrMulMatr(VD6_RndMatrView, VD6_RndMatrProj);
}
