template<typename _InIt, typename _Func>
void __merge(_InIt first, _InIt last, _Func& Func) {
    typedef typename iterator_traits<_InIt>::value_type _ValueType;
    vector<_ValueType> lv, rv;
    size_t q = floor((last-first)/2);

    copy(first, first+q+1, back_inserter(lv));
    copy(first+q+1, last+1, back_inserter(rv));

    typename vector<_ValueType>::iterator lit = lv.begin();
    typename vector<_ValueType>::iterator rit = rv.begin();

    _InIt it = first;
    for (; it != last+1; ++it) {
        if (lit == lv.end() || rit == rv.end()) break;
        *it = Func(*lit, *rit) ? *(lit++) : *(rit++);
    }

    for(; lit != lv.end() && it != last+1; ++lit, ++it) *it = *lit;
    for(; rit != rv.end() && it != last+1; ++rit, ++it) *it = *rit;
}

template<typename _InIt, typename _Func>
void __merge_sort(_InIt first, _InIt last, _Func& Func) {
    if (last - first > 0) {
        size_t q = floor((last - first)/2);
        __merge_sort(first, first+q, Func);
        __merge_sort(first+q+1, last, Func);
        __merge(first, last, Func);
    }
}

template<typename _InIt, typename _Func>
void merge_sort(_InIt first, _InIt last, _Func& Func) {
    __merge_sort(first, last-1, Func);
}