# isort

## 概要

任意の型の配列に対するソート。  
ほぼ qsort の力を使ってるだけ。

## 使い方

### sort

    void isort(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

要素数 _num, 要素サイズ _size の配列 _base を比較関数 _comp の元でソートする。

    void isort_by(void *_base, size_t _num, size_t _size, int *_perm);

要素数 _num, 要素サイズ _size の配列 _base を順列 _perm の元でソートする。

    void isort_by_random(void *_base, size_t _num, size_t _size);

要素数 _num, 要素サイズ _size の配列 _base をランダムに並び替える。

    void isort_by_partition(void *_base, size_t _num, size_t _size, int _pnum, int *_part);

要素数 _num, 要素サイズ _size の配列 _base を分割 _part の元でソートする。

    void isort_by_permutation(void *_base, size_t _num, size_t _size, int *_perm);

要素数 _num, 要素サイズ _size の配列 _base を順列 _perm の元でソートする。  
isort_by と等価。


### arg

    void iargsort(int *_args, void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

要素数 _num, 要素サイズ _size の配列 _base のインデックス配列 _args を比較関数 _comp の元でソートする。

    int iargmax(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));
    int iargmin(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

要素数 _num, 要素サイズ _size の配列 _base 中の比較関数 _comp の元で最大/最小の要素のインデックスを返す。


### uniq

    size_t iuniq(void *_base, size_t _num, size_t _size, int (*_comp)(const void *, const void *));

要素数 _num, 要素サイズ _size の配列 _base 中に登場する要素を比較関数 _comp の元で比較し、  
ユニークな要素数を返す。さらにそれらのユニークな要素を配列の先頭に固める。
