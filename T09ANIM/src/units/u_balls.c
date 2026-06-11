#include "units.h"

typedef struct tagvd6UNIT_BBALL vd6UNIT_BBALL;

typedef struct tagvd6UNIT_BBALL
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  vd6PRIM Ball;
  DBL Shift, Scale;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitInit( vd6UNIT_BBALL *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimCreateSphere(&Uni->Ball, 1, 18, 8);
  Uni->Pos = VecSet(Rnd1() * 8, 1, Rnd1() * 8);
 
  Uni->Shift = 1 + Rnd0() * 47;
  Uni->Scale = 3 + Rnd1() * 0.5;
} /* End of 'VD6_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitResponse( vd6UNIT_BBALL *Uni, vd6ANIM *Ani )
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
static VOID VD6_UnitRender( vd6UNIT_BBALL *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimDraw(&Uni->Ball, MatrMulMatr(MatrRotateY(60 * clock() / 1000), MatrTranslate(Uni->Pos)));
} /* End of 'VD6_UnitClose' function */

static VOID VD6_UnitClose( vd6UNIT_BBALL *Uni, vd6ANIM *Ani )
{
  VD6_RndPrimFree(&Uni->Ball);
} /* End of 'VG4_UnitClose' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vd6UNIT *) pointer to created unit.
 */
vd6UNIT * VD6_AnimUnitCreateBBalls( VOID )
{
  vd6UNIT_BBALL *Uni;

  /* Memory allocation */
  if ((Uni = (vd6UNIT_BBALL *)VD6_AnimUnitCreate(sizeof(vd6UNIT_BBALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)VD6_UnitInit;
  Uni->Response = (VOID *)VD6_UnitResponse;
  Uni->Render = (VOID *)VD6_UnitRender;

  return (vd6UNIT *)Uni;
} /* End of 'VD6_AnimUnitCreate' function */
