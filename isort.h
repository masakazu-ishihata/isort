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

/*------------------------------------*/
/* comparison function */
/*------------------------------------*/
int (*isort_comp_inside)(const void *, const void *);
int isort_comp(const void *_a, const void *_b);
void isort_set_comp_inside(int (*_comp)(const void *, const void *));
int int_comp(const void *_a, const void *_b);
int double_comp(const void *_a, const void *_b);
int prob_comp(const void *_a, const void *_b);

/*------------------------------------*/
/* sort */
/*------------------------------------*/
void isort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *));
int *iargsort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *));
void isort_by(void *_a, size_t _n, size_t _d, int *_p);


/*------------------------------------*/
/* swap */
/*------------------------------------*/
void void_swap(void *_a, void *_b, size_t _d);

#endif
