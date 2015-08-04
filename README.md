# isort

## 概要

任意の型の配列に対するソート。  
ほぼ qsort の力を使ってるだけ。

## 使い方

    void isort(void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))

長さ _n, 要素サイズ _d の 配列 _a を比較関数 _comp を元にソートを行う。

    void iargsort(int *_arg, void *_a, size_t _n, size_t _d, int (*_comp)(const void *, const void *))


長さ _n, 要素サイズ _d の 配列 _a を比較関数 _comp を元にソートしたときのインデックスの順列を _arg に格納する。


    void isort_by(void *_a, size_t _n, size_t _d, int *_p);

長さ _n, 要素サイズ _d の 配列 _a を順列 _p を元に並び替える。
