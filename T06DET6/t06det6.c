/* Donik Vasilisa, 10-6, 01.06.2026 */
#include <stdio.h>
#include <windows.h>
#include <math.h>

typedef DOUBLE DBL;

#define MAX 1000

DBL A[MAX][MAX], prod = 1, det = 0;
INT N, P[MAX];

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);

  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

VOID Swap( DBL *a, DBL *b )
{
  DBL c;

  c = *a;
  *a = *b;
  *b = c;
}

DBL f( VOID )
{
  INT i, y, x, k, max_row, max_col;
  DBL coef;

  det = 1;
  for (i = 0; i < N; i++)
  {
    /* look for maximum matrix element */
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_row = y, max_col = x;

    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }

    /* move max element to [i][i] position */
    if (max_row != i)
    {
      /* Swap max_row and i row (elements/columns: [i..N-1]) */
      for (x = i; x < N; x++)
        Swap(&A[max_row][x], &A[i][x]);
      det = -det;
    }
    
    if (max_col != i)
    {
      /* Swap max_col and i column (elements/columns: [0..N-1]) */
      for (y = i; y < N; y++)
        Swap(&A[y][max_col], &A[y][i]);
      det = -det;
    }
    /* Subtrack from every row k:[i+1..N-1] row [i] multipled by (A[k][i] / A[i][i]) */
    for (k = i + 1; k < N; k++)
    {
      coef = A[k][i] / A[i][i];
      A[k][i] = 0;
      for (x = i + 1; x < N; x++)
        A[k][x] -= A[i][x] * coef;
    }

    det *= A[i][i];
  }

  return det;
}

VOID main( VOID )
{
  DBL Det;

  LoadMatrix("b.txt");
  Det = f();

  printf("%f", Det);
  getchar();
}
