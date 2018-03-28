int decimal_num(int num, int p) {
    assert(num >0 && p > 0);
    int s = 1;
    while (p-->0) s *= 10;
    return ((num%s)*10)/s;
}

template<typename _InIt>
void counter_sort(_InIt first, _InIt last, _InIt result, int k, int p) {
    typedef typename iterator_traits<_InIt>::value_type _ValueType;

    vector<_ValueType> v(k, _ValueType(0));
    for(_InIt it=first; it!=last; ++it) v[decimal_num(*it, p)]++;

    typename vector<_ValueType>::iterator itx = v.begin()+1;
    for(; itx!=v.end() ; ++itx) (*itx) += *(itx-1);

    for (int i = last - first -1; i>=0; i--) {
        _ValueType val = *(first+i);
        _ValueType idx = decimal_num(val, p);
        29         *(result + v[idx] - 1) = val;
        v[idx]--;
    }

    for(_InIt it  = first; it!=last; ++it) *it = *result++;
}

template<typename _InIt>
void radix_sort(_InIt first, _InIt last, _InIt result, int p) {  /* 参数p是要排序的整数的最大位数，比如998就是3位数 p=3 */
    for (int i=1; i<=p; i++) {
        counter_sort(first, last, result, 10, i);
    }
}
