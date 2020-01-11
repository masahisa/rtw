#ifndef RTW_BINARY_SEARCH
#define RTW_BINARY_SEARCH

#include <iterator>

namespace rtw {

template<typename ForwardIterator, typename T>
constexpr bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
{
    using DifferenceType = typename std::iterator_traits<ForwardIterator>::difference_type;
    DifferenceType distance = std::distance(first, last);
    while(distance > 0) {
        DifferenceType half = distance >> 1;
        ForwardIterator middle = first;
        std::advance(middle, half);
        if(*middle == value){
            return true;
        }
        else if(*middle < value){
            first = middle;
            ++first;
            distance = distance - half - 1;
        }
        else{
            distance = half;
        }
    }
    return false;
}

template<typename ForwardIterator, typename T, typename Compare>
constexpr bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    using DifferenceType = typename std::iterator_traits<ForwardIterator>::difference_type;
    DifferenceType distance = std::distance(first, last);
    while(distance > 0) {
        DifferenceType half = distance >> 1;
        ForwardIterator middle = first;
        std::advance(middle, half);
        if(!(compare(*middle, value) || compare(value, *middle))){
            return true;
        }
        else if(compare(*middle, value)){
            first = middle;
            ++first;
            distance = distance - half - 1;
        }
        else{
            distance = half;
        }
    }
    return false;
}

} // namespace rtw

#endif // RTW_BINARY_SEARCH