#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitInit( vd6UNIT *Uni, vd6ANIM *Ani )
{
} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitClose( vd6UNIT *Uni, vd6ANIM *Ani )
{
} /* End of 'VG4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitResponse( vd6UNIT *Uni, vd6ANIM *Ani )
{
} /* End of 'VG4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vd6UNIT *Uni;
 *   - animation context:
 *       vd6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VD6_UnitRender( vd6UNIT *Uni, vd6ANIM *Ani )
{
} /* End of 'VD6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vd6UNIT *) pointer to created unit.
 */
vd6UNIT * VD6_AnimUnitCreate( INT Size )
{
  vd6UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(vd6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = VD6_UnitInit;
  Uni->Close = VD6_UnitClose;
  Uni->Response = VD6_UnitResponse;
  Uni->Render = VD6_UnitRender;

  return Uni;
} /* End of 'VD6_AnimUnitCreate' function */
