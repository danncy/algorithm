int bucket_index(int num, int p) {
    assert(num >0 && p > 0);
    int s = 1;
    while (p-->0) s *= 10;
    return ((num%s)*10)/s;
}

template<typename _InIt>
void bucket_sort(_InIt first, _InIt last, short decimal_bits) {
    typedef typename iterator_traits<_InIt>::value_type _ValueType;
    typedef typename vector<_ValueType>::iterator _Iterator;

    int n = last - first;
    if (n <= 0) return;

    vector< vector<_ValueType> > v(n, vector<_ValueType>());
    _InIt it = first;
    for(; it!=last; ++it) {
        int i = bucket_index(*it, decimal_bits);
        v[i].insert(v[i].begin(), *it);
    }

    typename vector< vector<_ValueType> >::iterator ite = v.begin();
    less_equal<_ValueType> cmp;
    it = first;

    for(; ite!=v.end(); ++ite) {
        if (ite->empty()) continue;
        insert_sort(ite->begin(), ite->end(), cmp);
        for(_Iterator _it=ite->begin(); _it!=ite->end(); ++_it)
            *it++ = *_it;
    }
}
