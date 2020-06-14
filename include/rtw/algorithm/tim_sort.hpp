#ifndef RTW_TIM_SORT_HPP
#define RTW_TIM_SORT_HPP

#include <algorithm>
#include <iterator>
#include <stack>

#include <rtw/algorithm/insertion_sort.hpp>
#include <rtw/container/vector.hpp>

namespace rtw{

template<typename RandomAccessIterator>
constexpr auto merge_compute_minrun(RandomAccessIterator first, RandomAccessIterator last)
{
    using difference_type = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    difference_type n = std::distance(first, last);
    difference_type r = 0;
    while(n >= 64){
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template<typename RandomAccessIterator, typename Compare>
constexpr auto count_run(RandomAccessIterator first, RandomAccessIterator last, Compare compare, bool& descending)
{
    descending = false;
    if(last - first == 1){
        return last - first;
    }
    using difference_type = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    difference_type n = 2;
    if(compare(*(first + 1), *first)){
        descending = true;
        ++first;
        while(first != last - 1){
            if(!compare(*(first + 1), *first)){
                break;
            }
            ++n;
            ++first;
        }
    }
    else{
        descending = false;
        ++first;
        while(first != last - 1){
            if(compare(*(first + 1), *first)){
                break;
            }
            ++n;
            ++first;
        }
    }
    return n;
}
//void merge_collapse();    // rtw::merge
//void sortslice_advance();
//void merge_force_collapse();  // rtw::merge?

template<typename RandomAccessIterator, typename Compare>
constexpr void tim_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using difference_type = typename std::iterator_traits<RandomAccessIterator>::difference_type;
    difference_type minrun = merge_compute_minrun(first, last);
    difference_type remaining = std::distance(first, last);
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::vector<value_type> buffer(remaining);
    do{
        bool descending = false;
        difference_type n = count_run(first, last, compare, descending);
        if(descending){
            std::reverse(first, first + n);
        }
        if(n < minrun){
            difference_type force = remaining <= minrun ? remaining : minrun;
            rtw::insertion_sort(first, first + n, compare);
            n = force;
        }



        remaining -= n;
    } while(remaining >= 0);
}

template<typename RandomAccessIterator>
constexpr void tim_sort(RandomAccessIterator first, RandomAccessIterator last)
{
    using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
    rtw::tim_sort(first, last, std::less<value_type>());
}

}

#endif // RTW_TIM_SORT_HPP