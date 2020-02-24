#ifndef RTW_HEAP_HPP
#define RTW_HEAP_HPP

#include <iterator>

namespace rtw {

template<typename RandomAccessIterator, typename Compare>
constexpr void adjust_heap(RandomAccessIterator first, RandomAccessIterator parent, RandomAccessIterator last, Compare compare)
{
    while(true){
        RandomAccessIterator left = first + 2 * (parent - first) + 1;
        RandomAccessIterator right = first + 2 * (parent - first) + 2;
        RandomAccessIterator top = parent;
        if(left < last && compare(*parent, *left)){
            top = left;
        }
        if(right < last && compare(*top, *right)){
            top = right;
        }
        if(top == parent){
            return;
        }
        std::iter_swap(parent, top);
        parent = top;
    }
}

template<typename RandomAccessIterator, typename Compare>
constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if(last - first < 2){
        return;
    }
    RandomAccessIterator parent = first + (last - first - 2) / 2;
    while(first <= parent){
        rtw::adjust_heap(first, parent, last, compare);
        --parent;
    }
}

template<typename RandomAccessIterator>
constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    if(last - first < 2){
        return;
    }
    RandomAccessIterator parent = first + (last - first - 2) / 2;
    while(first <= parent){
        rtw::adjust_heap(first, parent, last, std::less<ValueType>());
        --parent;
    }
}

template<typename RandomAccessIterator, typename Compare>
constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    while(last - first > 1){
        --last;
        std::iter_swap(first, last);
        rtw::adjust_heap(first, first, last, compare);
    }
}

template<typename RandomAccessIterator>
constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    while(last - first > 1){
        --last;
        std::iter_swap(first, last);
        rtw::adjust_heap(first, first, last, std::less<ValueType>());
    }
}

} // namespace rtw

#endif // RTW_HEAP_HPP