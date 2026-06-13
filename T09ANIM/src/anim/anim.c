#include "anim.h"

vd6UNIT * Units[VD6_MAX_UNITS];
vd6ANIM VD6_Anim;
INT NumOfUnits;

VOID VD6_AnimInit( HWND hWnd )
{
  memset(&VD6_Anim, 0, sizeof(vd6ANIM));

  VD6_Anim.hWnd = hWnd;
  VD6_RndInit(hWnd);
  VD6_Anim.hDC = VD6_hRndDC;
  VD6_Anim.H = VD6_RndH;
  VD6_Anim.W = VD6_RndW;

  VD6_TimerInit();
  VD6_AnimInputInit();
}

VOID VD6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < VD6_Anim.NumOfUnits; i++)
  {
    VD6_Anim.Units[i]->Close(VD6_Anim.Units[i], &VD6_Anim);
    free(VD6_Anim.Units[i]);
    VD6_Anim.Units[i] = NULL;
  }
  VD6_RndClose();
  memset(&VD6_Anim, 0, sizeof(VD6_Anim));
}

VOID VD6_AnimResize( INT W, INT H )
{
  VD6_RndResize(W, H);
  VD6_Anim.W = W;
  VD6_Anim.W = W;
  VD6_AnimRender();
}

VOID VD6_AnimCopyFrame( VOID )
{
  VD6_RndCopyFrame();
}

VOID VD6_AnimRender( VOID )
{
  INT i;

  VD6_TimerResponse();

  if (VD6_Anim.IsActive)
    VD6_AnimInputResponse();

  for (i = 0; i < VD6_Anim.NumOfUnits; i++)
    VD6_Anim.Units[i]->Response(VD6_Anim.Units[i], &VD6_Anim);

  srand(30);
  VD6_RndStart();
  for (i = 0; i < VD6_Anim.NumOfUnits; i++)
    VD6_Anim.Units[i]->Render(VD6_Anim.Units[i], &VD6_Anim);
  VD6_RndEnd();
}

VOID VD6_AnimAddUnit( vd6UNIT *Uni )
{
  if (VD6_Anim.NumOfUnits < VD6_MAX_UNITS)
    VD6_Anim.Units[VD6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &VD6_Anim);
}

VOID VD6_AnimExit( VOID )
{
}
