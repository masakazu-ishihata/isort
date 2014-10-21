#include "main.h"

#define N 10
#define rand_uni (rand() / (double)RAND_MAX)
#define dice(n) ( (int)(n * rand_uni) )

int main(void)
{
  int i;
  int *a = (int *)calloc(N, sizeof(int));

  /* initialize array */
  srand((unsigned)time(NULL));
  for(i=0; i<N; i++) a[i] = dice(N);

  /* before */
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* argsort */
  int *p = iargsort(a, N, sizeof(int), int_comp);
  printf("p ="); for(i=0; i<N; i++) printf("%3d", p[i]); printf("\n");

  /* sort by p */
  isort_by(a, N, sizeof(int), p);
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* free */
  free(a);
  free(p);

  return 0;
}
