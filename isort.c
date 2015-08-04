#include "isort.h"

/*------------------------------------*/
/* macros */
/*------------------------------------*/
#define int_new(n) (int *)calloc(n, sizeof(int));
#define FOR(n, i) for(i=0; i<n; i++)


/*----------------------------------------------------------------------------*/
/* isort_pair */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* comparison function */
/*------------------------------------*/
static int (*isort_pair_comp_inside)(const void *, const void *);

/*------------------------------------*/
/* compare item of isort_pair */
/*------------------------------------*/
void isort_pair_set_comp_inside(int (*_comp)(const void *, const void *))
{
  isort_pair_comp_inside = _comp;
}

/*------------------------------------*/
/* compare isort pairs */
/*------------------------------------*/
int isort_pair_comp(const void *_a, const void *_b)
{
  isort_pair *p = (isort_pair *)_a;
  isort_pair *q = (isort_pair *)_b;
  return isort_pair_comp_inside(p->p, q->p);
}


/*----------------------------------------------------------------------------*/
/* comparison functions */
/*----------------------------------------------------------------------------*/

/*------------------------------------*/
/* compare */
/*------------------------------------*/
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
int long_double_comp(const void *_a, const void *_b)
{
  long double *p = (long double *)_a;
  long double *q = (long double *)_b;
  return *p > *q;
}

/*------------------------------------*/
/* same */
/*------------------------------------*/
int int_same(const void *_a, const void *_b)
{
  int *p = (int *)_a;
  int *q = (int *)_b;
  return *p == *q;
}
int double_same(const void *_a, const void *_b)
{
  double *p = (double *)_a;
  double *q = (double *)_b;
  return *p == *q;
}
int long_double_same(const void *_a, const void *_b)
{
  long double *p = (long double *)_a;
  long double *q = (long double *)_b;
  return *p == *q;
}


/*----------------------------------------------------------------------------*/
/* swap */
/*----------------------------------------------------------------------------*/
void void_swap(void *_a, void *_b, size_t _d)
{
  void *t = malloc(_d);
  memmove( t, _a, _d); /* a -> t */
  memmove(_a, _b, _d); /* b -> a */
  memmove(_b,  t, _d); /* t -> b */
  free(t);
}


/*----------------------------------------------------------------------------*/
/* isort */
/*----------------------------------------------------------------------------*/

/*------------------------------------*/
/* sort _base by _comp */
/*------------------------------------*/
void isort(void *_base,  /* array */
           size_t _num,  /* # recodes */
           size_t _size, /* recode size */
           int (*_comp)(const void *, const void *))
{
  qsort(_base, _num, _size, _comp);
}

/*------------------------------------*/
/* sort _base by permutation _perm */
/*------------------------------------*/
void isort_by(void *_base,  /* array */
              size_t _num,  /* # recodes */
              size_t _size, /* recode size */
              int *_perm)   /* permutation */
{
  int i, j, k;
  int *p = int_new(_num); /* permutation */
  int *r = int_new(_num); /* reverse of p */

  /* init */
  FOR(_num, i){
    p[i] = _perm[i]; /* permutation */
    r[ p[i] ] = i;   /* reverse permutation */
  }

  /* decompose permutation */
  FOR(_num, i){
    j = p[i]; /* p[j] = i */
    k = r[i]; /* r[k] = i */

    /* swap a[j] <-> a[l] */
    void_swap(_base+_size*i, _base+_size*j, _size);
    void_swap(&p[i], &p[k], sizeof(int));
    void_swap(&r[i], &r[j], sizeof(int));
  }

  /* free */
  free(p);
  free(r);
}

/*------------------------------------*/
/* sort _a by random */
/*------------------------------------*/
void isort_by_random(void *_base,  /* array */
                     size_t _num,  /* # recodes */
                     size_t _size) /* recode size */
{
  int i;
  int *ary = int_new(_num);
  int *arg = int_new(_num);

  /* init */
  FOR(_num, i){
    arg[i] = i;
    ary[i] = (int)rand();
  }

  /* shuffle */
  iargsort(arg, ary, _num, sizeof(int), int_comp);
  isort_by(_base, _num, _size, arg);

  /* free */
  free(ary);
  free(arg);
}

/*------------------------------------*/
/* sort _base by partition _part */
/*------------------------------------*/
void isort_by_partition(void *_base,  /* array */
                        size_t _num,  /* # recodes */
                        size_t _size, /* recode size */
                        int _pnum,    /* # partitions */
                        int *_part)   /* partition */
{
  int i;

  /* size of each partition */
  int *s = int_new(_pnum);
  FOR(_num, i)
    s[ _part[i] ]++;

  /* Geta */
  int *b = int_new(_pnum);
  FOR(_pnum-1, i)
    b[i+1] = b[i] + s[i];

  /* pointer */
  int *p = int_new(_pnum);

  /* partition -> permutation */
  int *perm = int_new(_num);
  FOR(_num, i)
    perm[ b[ _part[i] ] + (p[ _part[i] ]++) ] = i;

  /* sort */
  isort_by_permutation(_base, _num, _size, perm);

  /* free */
  free(s);
  free(b);
  free(p);
  free(perm);
}

/*------------------------------------*/
/* sort by permutation */
/*------------------------------------*/
void isort_by_permutation(void *_base,  /* array */
                          size_t _num,  /* # recodes */
                          size_t _size, /* recode size */
                          int *_perm)   /* permutation */
{
  isort_by(_base, _num, _size, _perm);
}


/*----------------------------------------------------------------------------*/
/* arg */
/*----------------------------------------------------------------------------*/

/*------------------------------------*/
/* sort _arg by _ary with _comp */
/*------------------------------------*/
void iargsort(int *_args,   /* sorted index */
              void *_base,  /* array */
              size_t _num,  /* # recodes */
              size_t _size, /* recode size */
              int (*_comp)(const void *, const void *))
{
  int i;

  /* isort pair */
  isort_pair_set_comp_inside(_comp);
  isort_pair *ps = (isort_pair *)calloc(_num, sizeof(isort_pair));
  FOR(_num, i){
    ps[i].i = i;
    ps[i].p = _base + i * _size;
  }

  /* sort */
  qsort(ps, _num, sizeof(isort_pair), isort_pair_comp);

  /* permutation */
  FOR(_num, i)
    _args[i] = ps[i].i;

  /* free */
  free(ps);
}

/*------------------------------------*/
/* find the argmax of _base with _comp */
/*------------------------------------*/
int iargmax(void *_base,
            size_t _num,
            size_t _size,
            int (*_comp)(const void *, const void *))
{
  int i, argmax=0;
  for(i=1; i<_num; i++)
    if(_comp(_base + _size * i, _base + _size * argmax))
      argmax = i;
  return argmax;
}
int iargmin(void *_base,
            size_t _num,
            size_t _size,
            int (*_comp)(const void *, const void *))
{
  int i, argmin=0;
  for(i=1; i<_num; i++)
    if(_comp(_base + _size * argmin, _base + _size * i))
      argmin = i;
  return argmin;
}


/*----------------------------------------------------------------------------*/
/* uniq */
/*----------------------------------------------------------------------------*/

/*------------------------------------*/
/* uniq */
/*------------------------------------*/
size_t iuniq(void *_a, size_t _n, size_t _d, int (*_same)(const void *, const void *))
{
  /* _a must be sorted */

  int num=0;
  int head = 0;
  int tail = 0;

  for(num=1; num<_n; num++){
    for(tail=head+1; tail<_n && _same(_a+_d*(num-1), _a+_d*tail); tail++);
    if(tail == _n) break;
    void_swap(_a+_d*num, _a+_d*tail, _d);
    head = tail;
  }

  return num;
}
