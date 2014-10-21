# isort

## 概要

配列を受け取り、その argsort 結果を返す。


## 使い方

    void isort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))

_a = データ配列  
_n = データ配列の長さ  
_d = データ配列の１要素のサイズ  
_comp = データ配列の要素を比較する関数  
のとき、_a を _comp を基準にソートする。


    int *iargsort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))

_a を _comp を基準にソートしたときの index を返す。


    void isort_by(void *_a, size_t _n, size_t _d, int *_p);

_a を permutation _p にしたがってソートする。
