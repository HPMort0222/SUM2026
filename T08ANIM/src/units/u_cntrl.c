#include "stdio.h"

#include "units.h"

typedef struct tagvd6UNIT_CONTROL vd6UNIT_CONTROL;

typedef struct tagvd6UNIT_CONTROL
{
  UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitInit( vd6UNIT_CONTROL *Uni, vd6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);

  Uni->Speed = 10;
} /* End of 'VD6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitResponse( vd6UNIT_CONTROL *Uni, vd6ANIM *Ani )
{
  VEC d;

  /*
  if (Ani->Keys[VK_CONTROL] && Ani->Keys['F'])
    VG4_AnimFlipFullScreen();
  */

  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));

  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(d, Ani->GlobalDeltaTime * (Uni->Speed + 10 * Ani->Keys[VK_SHIFT]) *
      10 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN] + Ani->Mdz)));

  Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(VD6_RndMatrRight, Ani->Keys[VK_RIGHT] * (Uni->Speed + 3 * Ani->Keys[VK_SHIFT])));
  Uni->CamLoc = VecSubVec(Uni->CamLoc, VecMulNum(VD6_RndMatrRight, Ani->Keys[VK_LEFT] * (Uni->Speed + 3 * Ani->Keys[VK_SHIFT])));

  VD6_RndCamSet(Uni->CamLoc, Uni->CamAt, VecSet(0, 1, 0));

} /* End of 'VD6_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitRender( vd6UNIT_CONTROL *Uni, vd6ANIM *Ani )
{
  CHAR Buf[102];

  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(0, 0, 0));
  TextOut(Ani->hDC, Ani->W - 200, 30, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));

} /* End of 'VD6_UnitClose' function */

static VOID VD6_UnitClose( vd6UNIT_CONTROL *Uni, vd6ANIM *Ani )
{
} /* End of 'VG4_UnitClose' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vd6UNIT *) pointer to created unit.
 */
vd6UNIT * VD6_AnimUnitCreateControl( VOID )
{
  vd6UNIT_CONTROL *Uni;

  /* Memory allocation */
  if ((Uni = (vd6UNIT_CONTROL *)VD6_AnimUnitCreate(sizeof(vd6UNIT_CONTROL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)VD6_UnitInit;
  Uni->Response = (VOID *)VD6_UnitResponse;
  Uni->Render = (VOID *)VD6_UnitRender;

  return (vd6UNIT *)Uni;
} /* End of 'VD6_AnimUnitCreate' function */
