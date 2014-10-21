#include "isort.h"

/*------------------------------------*/
/* comparison functions */
/*------------------------------------*/
void isort_set_comp_inside(int (*_comp)(const void *, const void *))
{
  isort_comp_inside = _comp;
}
int isort_comp(const void *_a, const void *_b)
{
  isort_pair *p = (isort_pair *)_a;
  isort_pair *q = (isort_pair *)_b;
  return isort_comp_inside(p->p, q->p);
}
int int_comp(const void *_a, const void *_b)
{
  int *p = (int *)_a;
  int *q = (int *)_b;
  return *p > *q;
}
int double_comp(const void *_a, const void *_b)
{
  double *p = (double *)_a;
  double *q = (double *)_b;
  return *p > *q;
}
int prob_comp(const void *_a, const void *_b)
{
  long double *p = (long double *)_a;
  long double *q = (long double *)_b;
  return *p > *q;
}


/*----------------------------------------------------------------------------*/
/* sort */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* sort _a by _comp */
/*------------------------------------*/
void isort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))
{
  qsort(_a, _n, _d, _comp);
}
/*------------------------------------*/
/* argsort _a by _comp */
/*------------------------------------*/
int *iargsort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))
{
  /* set inside comparison function */
  isort_set_comp_inside(_comp);

  /* pairs */
  int i;
  isort_pair *ps = (isort_pair *)calloc(_n, sizeof(isort_pair));
  for(i=0; i<_n; i++){
    ps[i].i = i;
    ps[i].p = _a + i * _d;
  }

  /* sort */
  qsort(ps, _n, sizeof(isort_pair), isort_comp);

  /* permutation */
  int *p = (int *)calloc(_n, sizeof(int));
  for(i=0; i<_n; i++)
    p[i] = ps[i].i;

  /* free */
  free(ps);

  return p;
}
/*------------------------------------*/
/* sort _a by permutation _p */
/*------------------------------------*/
void isort_by(void *_a, size_t _n, size_t _d, int *_p)
{
  int i, j, k;
  int  *p = (int *)calloc(_n, sizeof(int));
  int  *r = (int *)calloc(_n, sizeof(int));

  /* init */
  for(i=0; i<_n; i++){
    p[i] = _p[i]; /* permutation */
    r[_p[i]] = i; /* reverse permutation */
  }

  /* decompose permutation */
  for(i=0; i<_n; i++){
    j = p[i]; /* p[j] = i */
    k = r[i]; /* r[k] = i */

    /* swap a[j] <-> a[l] */
    void_swap(_a+_d*i, _a+_d*j, _d);
    void_swap(&p[i], &p[k], sizeof(int));
    void_swap(&r[i], &r[j], sizeof(int));
  }

  /* free */
  free(p);
  free(r);
}
/*------------------------------------*/
/* swap */
/*------------------------------------*/
void void_swap(void *_a, void *_b, size_t _d)
{
  void *t = malloc(_d);
  memmove( t, _a, _d); /* a -> t */
  memmove(_a, _b, _d); /* b -> a */
  memmove(_b,  t, _d); /* t -> b */
  free(t);
}
