#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <functional>

using std::floor;
using std::swap;
using std::vector;
using std::greater;
using std::less;

template<typename _InIt, typename _Func>
void heapify(_InIt first, _InIt last, _InIt ite, _Func& Func) {
    int i = ite - first;
    _InIt it = ite;

    if ((last-ite)>i && Func(*(ite+i), *(it))) {
        it = ite + i;
    }

    if ((last-ite)>(i+1) && Func(*(ite+i+1), *(it))) {
        it = ite + i + 1;
    }

    if (*it != *ite) {
        swap(*ite, *it);
        heapify(first, last, it, Func);
    }
}

template<typename _InIt, typename _Func>
void build_heap(_InIt first, _InIt last, _Func &Func) {
    int i = (int)floor((float)(last - first)/2);
    for (; i>0; i--) {
        heapify(first, last, first+i, Func);
    }
}

template<typename _InIt, typename _Func>
void heap_sort(_InIt first, _InIt last, _Func &Func) {
    for (_InIt it=(last-1); it != (first+1); --it) {
        swap(*(first+1), *it);
        heapify(first, it, first+1, Func);
    }
}

template<typename T, typename _Func>
T heap_extract(vector<T> &v, _Func &Func) {
    assert(v.size() >= 2);  /* 因为多了一个填充元素 */   

    typename vector<T>::iterator it = v.begin() + 1;  /* 没有加typename gcc会报错 */
    T target = *(it);

    v.erase(it);
    heapify(v.begin(), v.end(), v.begin()+1, Func);
    return target;
}

template<typename T, typename _Func>
void heap_increase_key(vector<T>& v, _Func &Func, int i, T key) {
    v[i] = key;
    while(i>1 && !Func(v[i/2], v[i])) {
        swap(v[i], v[i/2]);
        i >>= 1;
    }
}

template<typename T, typename _Func>
void heap_insert(vector<T> &v, T key, _Func &Func) {
    v.push_back(key);
    heap_increase_key(v, Func, v.size()-1, key);
}

int main(int argc,  char* argv[]) {
    /* 堆的索引是1开始，所以第一个元素0是用来占位的 */
    int lst[] = {0,3,7,8,14,2,1,9,4,10,16};   
    vector<int> v(lst, lst+11);

    less<int> c;
    build_heap(v.begin(), v.end(), c);

    std::cout << heap_extract(v, c) << std::endl;
    heap_sort (v.begin(), v.end(), c);

    for (vector<int>::iterator it=v.begin(); it!=v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}