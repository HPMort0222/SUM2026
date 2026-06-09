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
      GLB_GlobalTime, GLB_GlobalDeltaTime, /* Global time and interframe interval */
      GLB_Time, GLB_DeltaTime,             /* Time with pause and interframe interval */
      GLB_FPS;                             /* Frames per second value */
BOOL
    GLB_IsPause;                           /* Pause flag */

VOID GLB_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;

  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

  PauseTime = 0;
  FrameCounter = 0;
  GLB_IsPause = FALSE;
  GLB_Time = GLB_DeltaTime = 0;
  GLB_FPS = 30;
}

VOID GLB_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  GLB_GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GLB_GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    GLB_DeltaTime = GLB_DeltaTime;
  }
  else
  {
    GLB_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }

  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    GLB_FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}