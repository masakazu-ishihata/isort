#include "main.h"

#define N 20
#define M 6
#define rand_uni (rand() / (double)RAND_MAX)
#define dice(n) ( (int)(n * rand_uni) )

int main(void)
{
  int i;
  int *a = (int *)calloc(N, sizeof(int));
  int *p = (int *)calloc(N, sizeof(int));

  /* initialize array */
  srand((unsigned)time(NULL));
  for(i=0; i<N; i++) a[i] = dice(M);

  /* before */
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* sort */
  isort(a, N, sizeof(int), int_comp);
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* uniq */
  isort(a, N, sizeof(int), int_comp);
  int u = iuniq(a, N, sizeof(int), int_same);
  printf("u ="); for(i=0; i<u; i++) printf("%3d", a[i]); printf("\n");

  /* sort by random */
  isort_by_random(a, N, sizeof(int));
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* partition */
  int n = 3;
  for(i=0; i<N; i++) p[i] = i % n;
  printf("p ="); for(i=0; i<N; i++) printf("%3d", p[i]); printf("\n");

  isort_by_partition(a, N, sizeof(int), n, p);
  printf("a ="); for(i=0; i<N; i++) printf("%3d", a[i]); printf("\n");

  /* argmax & argmin */
  i = iargmax(a, N, sizeof(int), int_comp);
  printf("argmax = %d, max = %d\n", i, a[i]);

  i = iargmin(a, N, sizeof(int), int_comp);
  printf("argmin = %d, min = %d\n", i, a[i]);

  /* free */
  free(a);
  free(p);

  return 0;
}
