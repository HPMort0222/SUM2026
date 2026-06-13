#include "def.h"

/* Shaders stock maximum size */
#define VD6_MAX_SHADERS 30

/* Shader program store type */
typedef struct tagvd6SHADER
{
  CHAR Name[VD6_MAX_SHADERS]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} vd6SHADER;

/* Array of shaders */
extern vd6SHADER VD6_RndShaders[VD6_MAX_SHADERS];
/* Shadres array store size */
extern INT VD6_RndShadersSize;

VOID VD6_RndResInit( VOID );

VOID VD6_RndResClose( VOID );

/* Shaders initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VD6_RndShdInit( VOID );

/* Shaders deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VD6_RndShdClose( VOID );

/* Update from file all load shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VD6_RndShdUpdate( VOID );

