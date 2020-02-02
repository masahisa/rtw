#ifndef RTW_QUICK_SORT_HPP
#define RTW_QUICK_SORT_HPP

#include <iterator>

namespace rtw {

template<typename RandomAccessIterator, typename Compare>
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    ValueType pivot = *first;
    while(true){
        while(compare(*first, pivot)){
            ++first;
        }
        --last;
        while(compare(pivot, *last)){
            --last;
        }
        if(!(first < last)){
            return first != last ? first : first + 1;
        }
        std::iter_swap(first, last);
        ++first;
    }
}

template<typename RandomAccessIterator, typename Compare>
constexpr void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if(last - first > 1){
        RandomAccessIterator cut = rtw::partition(first, last, compare);
        rtw::quick_sort(first, cut, compare);
        rtw::quick_sort(cut, last, compare);
    }
}

template<typename RandomAccessIterator>
constexpr void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::quick_sort(first, last, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_QUICK_SORT_HPP