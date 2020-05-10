#ifndef RTW_QUICK_SORT_HPP
#define RTW_QUICK_SORT_HPP

#include <iterator>

namespace rtw {

template<typename Iterator, typename Compare>
void move_median_to_first(Iterator result, Iterator a, Iterator b, Iterator c, Compare compare)
{
    if(compare(*a, *b)){
        if(compare(*b, *c)){
            std::iter_swap(result, b);
        }
        else if(compare(*a, *c)){
            std::iter_swap(result, c);
        }
        else{
            std::iter_swap(result, a);
        }
    }
    else if(compare(*a, *c)){
        std::iter_swap(result, a);
    }
    else if(compare(*b, *c)){
        std::iter_swap(result, c);
    }
    else{
        std::iter_swap(result, b);
    }
}

template<typename RandomAccessIterator, typename Compare>
constexpr RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    value_type pivot = *first;
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
constexpr RandomAccessIterator partition_pivot(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    RandomAccessIterator middle = first + (last - first) / 2;
    rtw::move_median_to_first(first, first, middle, last - 1, compare);
    return rtw::partition(first, last, compare);
}

template<typename RandomAccessIterator, typename Compare>
constexpr void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    while(last - first > 1){
        RandomAccessIterator cut = rtw::partition_pivot(first, last, compare);
        rtw::quick_sort(cut, last, compare);
        last = cut;
    }
}

template<typename RandomAccessIterator>
constexpr void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::quick_sort(first, last, std::less<value_type>());
}

} // namespace rtw

#endif // RTW_QUICK_SORT_HPP