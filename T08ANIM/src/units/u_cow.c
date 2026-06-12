#include "units.h"

typedef struct tagvd6UNIT_COW vd6UNIT_COW;

typedef struct tagvd6UNIT_COW
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  vd6PRIM Cow;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitInit( vd6UNIT_COW *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimLoad(&Uni->Cow, "./bin/model/cow.obj");
  Uni->Pos = VecSet(10 + rand() * Ani->DeltaTime * 2.4, -10, -10);
} /* End of 'VD6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitResponse( vd6UNIT_COW *Uni, vd6ANIM *Ani )
{
} /* End of 'VD6_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitRender( vd6UNIT_COW *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimDraw(&Uni->Cow, MatrTranslate(VecAddVec(Uni->Pos, VecSet(-10, fabs(sin(5 * Ani->Time)), -10))));
} /* End of 'VD6_UnitClose' function */

static VOID VD6_UnitClose( vd6UNIT_COW *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimFree(&Uni->Cow);
} /* End of 'VG4_UnitClose' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vd6UNIT *) pointer to created unit.
 */
vd6UNIT * VD6_AnimUnitCreateCow( VOID )
{
  vd6UNIT_COW *Uni;

  /* Memory allocation */
  if ((Uni = (vd6UNIT_COW *)VD6_AnimUnitCreate(sizeof(vd6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)VD6_UnitInit;
  Uni->Response = (VOID *)VD6_UnitResponse;
  Uni->Render = (VOID *)VD6_UnitRender;

  return (vd6UNIT *)Uni;
} /* End of 'VD6_AnimUnitCreate' function */
