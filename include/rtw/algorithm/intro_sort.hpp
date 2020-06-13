#ifndef RTW_INTRO_SORT_HPP
#define RTW_INTRO_SORT_HPP

#include <cmath>
#include <type_traits>

#include <rtw/algorithm/heap.hpp>
#include <rtw/algorithm/insertion_sort.hpp>
#include <rtw/algorithm/quick_sort.hpp>

namespace rtw{

enum { threshold = 32 };

template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
inline constexpr T intro_sort_depth_limit(T depth)
{
    return 2 * std::log2(depth);
}

template<typename RandomAccessIterator, typename Size, typename Compare>
void intro_sort_loop(RandomAccessIterator first, RandomAccessIterator last, Size depth, Compare compare)
{
    while(last - first > threshold){
        if(depth == 0){
            rtw::make_heap(first, last, compare);
            rtw::sort_heap(first, last, compare);
            return;
        }
        --depth;
        RandomAccessIterator cut = rtw::partition_pivot(first, last, compare);
        rtw::intro_sort_loop(cut, last, depth, compare);
        last = cut;
    }
}

template<typename RandomAccessIterator, typename Compare>
constexpr void intro_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    rtw::intro_sort_loop(first, last, rtw::intro_sort_depth_limit(last - first), compare);
    rtw::insertion_sort(first, last, compare);
}

template<typename RandomAccessIterator>
constexpr void intro_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::intro_sort(first, last, std::less<value_type>());
}

}

#endif // RTW_INTRO_SORT_HPP