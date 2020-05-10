#ifndef RTW_BINARY_SEARCH_HPP
#define RTW_BINARY_SEARCH_HPP

#include <iterator>
#include <utility>

namespace rtw {

template<typename ForwardIterator, typename T, typename Compare>
constexpr ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    using DifferenceType = typename std::iterator_traits<ForwardIterator>::difference_type;
    DifferenceType distance = std::distance(first, last);
    while(distance > 0) {
        DifferenceType half = distance >> 1;
        ForwardIterator middle = first;
        std::advance(middle, half);
        if(compare(*middle, value)){
            first = middle;
            ++first;
            distance = distance - half - 1;
        }
        else{
            distance = half;
        }
    }
    return first;
}

template<typename ForwardIterator, typename T>
constexpr ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::lower_bound(first, last, value, std::less<ValueType>());
}

template<typename ForwardIterator, typename T, typename Compare>
constexpr ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    using DifferenceType = typename std::iterator_traits<ForwardIterator>::difference_type;
    DifferenceType distance = std::distance(first, last);
    while(distance > 0) {
        DifferenceType half = distance >> 1;
        ForwardIterator middle = first;
        std::advance(middle, half);
        if(compare(value, *middle)){
            distance = half;
        }
        else{
            first = middle;
            ++first;
            distance = distance - half - 1;
        }
    }
    return first;
}

template<typename ForwardIterator, typename T>
constexpr ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::upper_bound(first, last, value, std::less<ValueType>());
}

template<typename ForwardIterator, typename T, typename Compare>
constexpr bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    ForwardIterator it = rtw::lower_bound(first, last, value, compare);
    return it != last && !(compare(value, *it));
}

template<typename ForwardIterator, typename T>
constexpr bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::binary_search(first, last, value, std::less<ValueType>());
}

template<typename ForwardIterator, typename T, typename Compare>
constexpr std::pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    return std::make_pair(rtw::lower_bound(first, last, value, compare), rtw::upper_bound(first, last, value, compare));
}

template<typename ForwardIterator, typename T>
constexpr std::pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::equal_range(first, last, value, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_BINARY_SEARCH_HPP