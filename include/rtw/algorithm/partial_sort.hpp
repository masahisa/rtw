#ifndef RTW_PARTIAL_SORT_HPP
#define RTW_PARTIAL_SORT_HPP

#include <rtw/algorithm/heap.hpp>

namespace rtw{

template<typename RandomAccessIterator, typename Compare>
constexpr void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare compare)
{
    rtw::make_heap(first, middle, compare);
    for(RandomAccessIterator it = middle; it < last; ++it){
        if(compare(*it, *first)){
            std::iter_swap(it, first);
            rtw::adjust_heap(first, first, middle, compare);
        }
    }
    rtw::sort_heap(first, middle, compare);
}

template<typename RandomAccessIterator>
constexpr void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::partial_sort(first, middle, last, std::less<value_type>());
}

}

#endif // RTW_PARTIAL_SORT_HPP