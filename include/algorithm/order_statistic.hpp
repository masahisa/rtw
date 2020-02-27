#ifndef RTW_ORDER_STATISTIC_HPP
#define RTW_ORDER_STATISTIC_HPP

#include <iterator>
#include <utility>

#include "quick_sort.hpp"

namespace rtw {

template<typename ForwardIterator, typename Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare compare)
{
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    ++first;
    while(first != last){
        if(compare(*first, *result)){
            result = first;
        }
        ++first;
    }
    return result;
}

template<typename ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::min_element(first, last, std::less<ValueType>());
}

template<typename ForwardIterator, typename Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare compare)
{
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    ++first;
    while(first != last){
        if(compare(*result, *first)){
            result = first;
        }
        ++first;
    }
    return result;
}

template<typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::max_element(first, last, std::less<ValueType>());
}

template<typename ForwardIterator, typename Compare>
std::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first, ForwardIterator last, Compare compare)
{
    ForwardIterator next = first;
    ++next;
    if(first == last || next == last){
        return std::make_pair(first, first);
    }
    ForwardIterator min, max;
    if(compare(*first, *next)){
        min = first;
        max = next;
    }
    else{
        min = next;
        max = first;
    }
    first = next;
    ++first;
    while(first != last){
        next = first;
        ++next;
        if(next == last){
            if(compare(*first, *min)){
                min = first;
            }
            if(compare(*max, *first)){
                max = first;
            }
            break;
        }
        if(compare(*first, *next)){
            if(compare(*first, *min)){
                min = first;
            }
            if(compare(*max, *next)){
                max = next;
            }
        }
        else{
            if(compare(*next, *min)){
                min = next;
            }
            if(compare(*max, *first)){
                max = first;
            }
        }
        first = next;
        ++first;
    }
    return std::make_pair(min, max);
}

template<typename ForwardIterator>
std::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first, ForwardIterator last)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::minmax_element(first, last, std::less<ValueType>());
}

template<typename RandomAccessIterator, typename Compare>
void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare compare)
{
    while(last - first > 1){
        RandomAccessIterator cut = rtw::partition_pivot(first, last, compare);
        if(cut <= nth){
            first = cut;
        }
        else{
            last = cut;
        }
    }
}

template<typename RandomAccessIterator>
void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last)
{
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::nth_element(first, nth, last, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_ORDER_STATISTIC_HPP