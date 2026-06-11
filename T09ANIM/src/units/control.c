#include <string.h>
#include "units.h"

typedef struct tagvd6UNIT_CNTL vd6UNIT_CNTL;

typedef struct tagvd6UNIT_CNTL
{
  UNIT_BASE_FIELDS;
  VEC CamLoc, CamDir;
  DBL Speed;
  VEC Pos;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitInit( vd6UNIT_CNTL *Uni, vd6ANIM *Ani )
{
  Uni->CamLoc = VecSet(1, 0, 0);
  Uni->CamDir = VecSet(1, 0, 0);

  Uni->Speed = 3;
} /* End of 'VD6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitResponse( vd6UNIT_CNTL *Uni, vd6ANIM *Ani )
{
  INT i;

  GetKeyboardState(Ani->Keys);
  for (i = 0; i < 256; i++)
  {
    Ani->Keys[i] >>= 7;
    Ani->KeysClick[i] = Ani->Keys[i] && !Ani->KeysOld[i];
  }
 
  memcpy(Ani->KeysOld, Ani->Keys, 256);

  /*
  if (Ani->Keys[VK_CONTROL] && Ani->KeysClick['F'])
    VD6_AnimFlipFullScreen();
  */

  if (Ani->KeysClick['p'])
    Ani->IsPause = !Ani->IsPause;

    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->CamDir,
                  Ani->DeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
} /* End of 'VD6_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitRender( vd6UNIT_CNTL *Uni, vd6ANIM *Ani )
{
} /* End of 'VD6_UnitClose' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vd6UNIT *) pointer to created unit.
 */
vd6UNIT * VD6_AnimUnitCreateControl( VOID )
{
  vd6UNIT_CNTL *Uni;

  /* Memory allocation */
  if ((Uni = (vd6UNIT_CNTL *)VD6_AnimUnitCreate(sizeof(vd6UNIT_CNTL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)VD6_UnitInit;
  Uni->Response = (VOID *)VD6_UnitResponse;
  Uni->Render = (VOID *)VD6_UnitRender;

  return (vd6UNIT *)Uni;
} /* End of 'VD6_AnimUnitCreate' function */
