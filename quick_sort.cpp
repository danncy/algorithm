#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

template<typename _InIt, typename _Func>
_InIt __partition(_InIt first, _InIt last, _Func& Func) {
    typedef typename  iterator_traits<_InIt>::value_type _ValueType;

    _ValueType val = *(last);
    _InIt _Ite = first-1;

    for (_InIt it = first; (last-it)>=1; ++it) {
        if (Func(*it, val)) {
            _Ite++;
            iter_swap(_Ite, it);
        }
    }

    iter_swap(++_Ite, last);
    return _Ite;
}

template<typename _InIt, typename _Func>
_InIt randomized_partition(_InIt first, _InIt last, _Func& Func) {
    size_t offset = last - first;
    assert((last - first)>0);

    random_device rd ;
    default_random_engine e(rd());
    uniform_int_distribution <> u(0, offset);

    iter_swap(last, first+u(e));
    return __partition(first, last, Func);
}

template<typename _InIt, typename _Func>
void __quick_sort(_InIt first, _InIt last, _Func& Func) {
    if (last - first > 0) {
        _InIt it = randomized_partition(first, last, Func);
        __quick_sort(first, it-1, Func);
        __quick_sort(it+1, last, Func);
    }
}

template<typename _InIt, typename _Func>
void quick_sort(_InIt first, _InIt last, _Func& Func) {
    __quick_sort(first, --last, Func);
}

template<typename _InIt, typename _Func>
void tail_rescursive_quick_sort(_InIt first, _InIt last, _Func& Func) {
    while (last - first > 0) {
        _InIt it = __partition(first, last, Func);
        tail_rescursive_quick_sort(first, it-1, Func);
        first = it + 1;
    }
}
