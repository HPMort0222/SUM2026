#include "anim.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm")

#define VD6_GET_JOYSTIC_AXIS(A) \
 2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1

static BYTE OldKeys[256];
static BYTE JButOld[256];

static VOID KeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(VD6_Anim.Keys);
  for (i = 0; i < 256; i++)
    VD6_Anim.Keys[i] >>= 7;
  memcpy(OldKeys, VD6_Anim.Keys, 256);
}

static VOID KeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(VD6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    VD6_Anim.Keys[i] >>= 7;
    VD6_Anim.KeysClick[i] = VD6_Anim.Keys[i] && !OldKeys[i];
  }

  memcpy(OldKeys, VD6_Anim.Keys, 256);
} 

static VOID MouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(VD6_Anim.hWnd, &pt);

  VD6_Anim.Mx = pt.x;
  VD6_Anim.My = pt.y;

  VD6_MouseWheel = VD6_Anim.Mdz = VD6_Anim.Mz = 0;
}

static VOID MouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(VD6_Anim.hWnd, &pt);

  VD6_Anim.Mdx = pt.x - VD6_Anim.Mx;
  VD6_Anim.Mdy = pt.y - VD6_Anim.My;
}

static VOID JoystickResponse( VOID )
{
   INT i;

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;
 
    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;
 
 
      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          VD6_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          VD6_Anim.JButClick[i] = VD6_Anim.JBut[i] && !JButOld[i];
          JButOld[i] = VD6_Anim.JBut[i];
        }
        /* Axes */
        VD6_Anim.JX = VD6_GET_JOYSTIC_AXIS(X);
        VD6_Anim.JY = VD6_GET_JOYSTIC_AXIS(Y);
        VD6_Anim.JZ = VD6_GET_JOYSTIC_AXIS(Z);
        VD6_Anim.JR = VD6_GET_JOYSTIC_AXIS(R);
        VD6_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}

static VOID JoystickInit( VOID )
{
  JoystickResponse();
}

VOID VD6_AnimInputInit( VOID )
{
  KeyboardInit();
  MouseInit();
  JoystickInit();
}

VOID VD6_AnimInputResponse( VOID )
{
  KeyboardResponse();
  MouseResponse();
  JoystickResponse();
}
