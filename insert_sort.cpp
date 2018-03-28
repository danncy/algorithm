template<typename _InIt, typename _Func>
void __insert_sort(_InIt first, _InIt last, _Func& Func) {
    typedef typename iterator_traits<_InIt>::value_type _ValueType;

    for (_InIt it = first + 1; it != last+1; ++it) {
        _ValueType key = *it;
        _InIt ite = it - 1;
        for (; (ite - first)>=0 && !Func(*ite, key); --ite)
            *(ite + 1) = *ite;
        *(ite + 1) = key;
    }
}

template<typename _InIt, typename _Func>
void insert_sort(_InIt first, _InIt last, _Func& Func) {
    __insert_sort(first, last-1, Func);
}