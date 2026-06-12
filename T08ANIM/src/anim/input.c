#include "anim.h"

static BYTE OldKeys[256];
INT VD6_MouseWheel;

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

static VOID JoystickInit( VOID )
{
}

static VOID JoystickResponse( VOID )
{
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
