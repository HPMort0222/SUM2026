/* Donik Vasilisa, 10-6, 06.06.2026 */
#include "timer.h"
#include "anim.h"

static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

VOID VD6_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;

  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

  PauseTime = 0;
  FrameCounter = 0;
  VD6_Anim.IsPause = FALSE;
  VD6_Anim.Time = VD6_Anim.DeltaTime = 0;
  VD6_Anim.FPS = 30;
}

VOID VD6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);

  /* Global time */
  VD6_Anim.GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  VD6_Anim.GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (!VD6_Anim.IsPause)
  {
    VD6_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
    VD6_Anim.DeltaTime = VD6_Anim.GlobalDeltaTime;
  }
  else
  {
    VD6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }

  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > 3 * TimePerSec)
  {
    VD6_Anim.FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}