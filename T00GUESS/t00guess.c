/* Donik Vasilisa, 10-6, 01.06.2026 */ 
#include <stdio.h>  
#include <windows.h>

#define MAX 100

void main( void )
{
  int a = 100, b = 0, m, d;
  char n[MAX];

  if (MessageBox(NULL, "Guess 1-100", "Start", MB_YESNO) == IDYES)
  {
    while (a != b)
    {
      m = (a + b) / 2;

      sprintf(n, "bolshe %i?", m);
      if ((d = MessageBox(NULL, n, "pupupu", MB_YESNOCANCEL)) == IDYES)
        b = m + 1;
      else if (d == IDNO )
        a = m + 1;
      else
      {
        MessageBox(NULL, "Oh, thats it", "XXX", MB_OK);
        return;
      }
    }

    if (a <=   b)
    {
      MessageBox(NULL, "Ducking liar", "Yes you are", MB_OK);
      return;
      }

  }
  else
  {
    MessageBox(NULL, "Ok:(", "End", MB_OK);
    return;
  }
}