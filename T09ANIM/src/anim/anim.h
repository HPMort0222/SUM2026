#include "rnd/rnd.h"
#include "timer.h"

typedef struct tagvd6ANIM vd6ANIM;
typedef struct tagvd6UNIT vd6UNIT;

#define UNIT_BASE_FIELDS \
  VOID (*Init)( vd6UNIT *Uni, vd6ANIM *Ani );      \
  VOID (*Close)( vd6UNIT *Uni, vd6ANIM *Ani );     \
  VOID (*Response)( vd6UNIT *Uni, vd6ANIM *Ani );  \
  VOID (*Render)( vd6UNIT *Uni, vd6ANIM *Ani )

#define VD6_MAX_UNITS 3000

extern vd6UNIT * Units[VD6_MAX_UNITS];
extern vd6ANIM VD6_Anim;
extern INT NumOfUnits;

typedef struct tagvd6UNIT
{
  UNIT_BASE_FIELDS;
};

typedef struct tagvd6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  DBL Shift, Scale;

  vd6UNIT * Units[VD6_MAX_UNITS];
  INT NumOfUnits;

  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */

  BOOL
    IsPause;                     /* Pause flag */

  BYTE Keys[256];
  BYTE KeysClick[256];
  BYTE KeysOld[256];

  INT Mx, My, Mz, Mdx, Mdy, Mdz;
};

extern vd6ANIM VD6_Anim;

VOID VD6_AnimInit( HWND hWnd );

VOID VD6_AnimClose( VOID );

VOID VD6_AnimResize( INT W, INT H );

VOID VD6_AnimCopyFrame( HDC hDC );

VOID VD6_AnimRender( VOID );

VOID VD6_AnimAddUnit( vd6UNIT *Uni );

VOID VD6_AnimExit( VOID );

vd6UNIT * VD6_AnimUnitCreate( INT Size );
