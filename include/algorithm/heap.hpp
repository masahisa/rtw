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
    rtw::make_heap(first, last, std::less<ValueType>());
}

template<typename RandomAccessIterator, typename Compare>
inline void __set_heap_key_impl(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    RandomAccessIterator parent = first + (last - first - 1) / 2;
    while(first < last && compare(*parent, *last)){
        std::iter_swap(parent, last);
        last = parent;
        parent = first + (last - first - 1) / 2;
    }
}

template<typename RandomAccessIterator, typename T, typename Compare>
constexpr bool set_heap_key(RandomAccessIterator first, RandomAccessIterator node, T value, Compare compare)
{
    if(compare(value, *node)){
        return false;
    }
    *node = value;
    rtw::__set_heap_key_impl(first, node, compare);
    return true;
}

template<typename RandomAccessIterator, typename T>
constexpr bool set_heap_key(RandomAccessIterator first, RandomAccessIterator node, T value)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    return rtw::set_heap_key(first, node, value, std::less<ValueType>());
}

template<typename RandomAccessIterator, typename Compare>
constexpr void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    --last;
    rtw::__set_heap_key_impl(first, last, compare);
}

template<typename RandomAccessIterator>
constexpr void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::push_heap(first, last, std::less<ValueType>());
}

template<typename RandomAccessIterator, typename Compare>
constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    --last;
    std::iter_swap(first, last);
    rtw::adjust_heap(first, first, last, compare);
}

template<typename RandomAccessIterator>
constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::pop_heap(first, last, std::less<ValueType>());
}

template<typename RandomAccessIterator, typename Compare>
constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    while(last - first > 1){
        rtw::pop_heap(first, last, compare);
        --last;
    }
}

template<typename RandomAccessIterator>
constexpr void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::sort_heap(first, last, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_HEAP_HPP