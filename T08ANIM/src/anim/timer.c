/* Donik Vasilisa, 10-6, 06.06.2026 */

#include "timer.h"

static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

DOUBLE
      VD6_GlobalTime, VD6_GlobalDeltaTime, /* Global time and interframe interval */
      VD6_Time, VD6_DeltaTime,             /* Time with pause and interframe interval */
      VD6_FPS;                             /* Frames per second value */
BOOL
    VD6_IsPause;                           /* Pause flag */

VOID VD6_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;

  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

  PauseTime = 0;
  FrameCounter = 0;
  VD6_IsPause = FALSE;
  VD6_Time = VD6_DeltaTime = 0;
  VD6_FPS = 30;
}

VOID VD6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  VD6_GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  VD6_GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (!VD6_IsPause)
  {
    VD6_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    VD6_DeltaTime = VD6_DeltaTime;
  }
  else
  {
    VD6_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }

  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    VD6_FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}