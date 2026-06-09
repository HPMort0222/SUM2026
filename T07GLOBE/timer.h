/* Donik Vasilisa, 10-6, 06.06.2026 */
#ifndef __timer_h_
#define __timer_h_

#include <time.h>
#include <windows.h>

extern DOUBLE
           GLB_GlobalTime, GLB_GlobalDeltaTime, /* Global time and interframe interval */
           GLB_Time, GLB_DeltaTime,             /* Time with pause and interframe interval */
           GLB_FPS;                             /* Frames per second value */
extern BOOL
           GLB_IsPause;                         /* Pause flag */

VOID GLB_TimerInit( VOID );

VOID GLB_TimerResponse( VOID );

#endif /* __globe_h_ */
