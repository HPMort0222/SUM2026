#ifndef __timer_h_
#define __timer_h_

#include <time.h>

#include "rnd/rnd.h"

extern DOUBLE
           VD6_GlobalTime, VD6_GlobalDeltaTime, /* Global time and interframe interval */
           VD6_Time, VD6_DeltaTime,             /* Time with pause and interframe interval */
           VD6_FPS;                             /* Frames per second value */
extern BOOL
           VD6_IsPause;                         /* Pause flag */

VOID VD6_TimerInit( VOID );

VOID VD6_TimerResponse( VOID );

#endif /* __globe_h_ */
