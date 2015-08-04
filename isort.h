#ifndef _ISORT_H_
#define _ISORT_H_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*------------------------------------*/
/* pair of index & value */
/*------------------------------------*/
typedef struct ISORT_PAIR
{
  int   i;  /* index */
  void *p;  /* pointer */
} isort_pair;

/* comp for isort_pair */
void isort_pair_set_comp_inside(int (*_comp)(const void *, const void *));
int isort_pair_comp(const void *_a, const void *_b);

/*------------------------------------*/
/* comparison function */
/*------------------------------------*/
/* compare */
int int_comp(const void *_a, const void *_b);
int double_comp(const void *_a, const void *_b);
int long_double_comp(const void *_a, const void *_b);
/* same or not */
int int_same(const void *_a, const void *_b);
int double_same(const void *_a, const void *_b);
int long_double_same(const void *_a, const void *_b);

/*------------------------------------*/
/* swap */
/*------------------------------------*/
void void_swap(void *_a, void *_b, size_t _dsize);

/*------------------------------------*/
/* sort */
/*------------------------------------*/
/* sort / argsort */
void isort(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

/* sort by */
void isort_by(void *_base, size_t _num, size_t _size, int *_perm);
void isort_by_random(void *_base, size_t _num, size_t _size);
void isort_by_partition(void *_base, size_t _num, size_t _size, int _pnum, int *_part);
void isort_by_permutation(void *_base, size_t _num, size_t _size, int *_perm);

/*------------------------------------*/
/* arg */
/*------------------------------------*/
void iargsort(int *_args, void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));
int iargmax(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));
int iargmin(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));


/*------------------------------------*/
/* util */
/*------------------------------------*/
size_t iuniq(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

#endif
