#ifndef RTW_BINARY_SEARCH_HPP
#define RTW_BINARY_SEARCH_HPP

#include <iterator>

namespace rtw {

template<typename ForwardIterator, typename T, typename Compare>
constexpr ForwardIterator binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
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
    return first != last && !(compare(value, *first)) ? first : last;
}

template<typename ForwardIterator, typename T>
constexpr ForwardIterator binary_search(ForwardIterator first, ForwardIterator last, const T& value)
{
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    return rtw::binary_search(first, last, value, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_BINARY_SEARCH_HPP