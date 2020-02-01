#ifndef RTW_INSERTION_SORT_HPP
#define RTW_INSERTION_SORT_HPP

#include <iterator>

namespace rtw {

template<typename BidirectionalIterator, typename Compare>
constexpr void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
{
    using ValueType = typename std::iterator_traits<BidirectionalIterator>::value_type;
    if(first == last){
        return;
    }
    for(BidirectionalIterator unsorted = std::next(first); unsorted != last; ++unsorted){
        ValueType value = *unsorted;
        if(compare(value, *first)){
            std::move_backward(first, unsorted, std::next(unsorted));
            *first = value;
        }
        else{
            BidirectionalIterator insert_position = unsorted;
            BidirectionalIterator next = std::prev(insert_position);
            while(compare(value, *next)){
                *insert_position = *next;
                insert_position = next;
                --next;
            }
            *insert_position = value;
        }
    }
}

template<typename BidirectionalIterator>
constexpr void insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
{
    using ValueType = typename std::iterator_traits<BidirectionalIterator>::value_type;
    insertion_sort(first, last, std::less<ValueType>());
}

} // namespace rtw

#endif // RTW_INSERTION_SORT_HPP