#ifndef RTW_MERGE_SORT_HPP
#define RTW_MERGE_SORT_HPP

#include <algorithm>
#include <iterator>

#include <rtw/container/vector.hpp>

namespace rtw {

template<typename ForwardIterator, typename Pointer, typename Compare>
void merge(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Pointer buffer, Compare compare)
{
    Pointer first1 = buffer;
    Pointer last1 = first1 + std::distance(first, middle);
    Pointer first2 = last1;
    Pointer last2 = first2 + std::distance(middle, last);
    std::move(first, last, buffer);
    while(first1 != last1 && first2 != last2){
        if(compare(*first1, *first2)){
            *first = std::move(*first1);
            ++first1;
        }
        else{
            *first = std::move(*first2);
            ++first2;
        }
        ++first;
    }
    std::move(first1, last1, first);
    std::move(first2, last2, first);
}

template<typename RandomAccessIterator, typename Pointer, typename Compare>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Pointer buffer, Compare compare)
{
    if(last - first > 1){
        RandomAccessIterator middle = first + (last - first) / 2;
        rtw::merge_sort(first, middle, buffer, compare);
        rtw::merge_sort(middle, last, buffer, compare);
        rtw::merge(first, middle, last, buffer, compare);
    }
}

template<typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    using difference_type = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    difference_type distance = std::distance(first, last);
    rtw::vector<value_type> buffer(distance);
    rtw::merge_sort(first, last, buffer.begin(), compare);
}

template<typename RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::merge_sort(first, last, std::less<value_type>());
}

} // namespace rtw

#endif // RTW_MERGE_SORT_HPP