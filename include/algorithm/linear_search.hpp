#ifndef RTW_LINEAR_SEARCH_HPP
#define RTW_LINEAR_SEARCH_HPP

namespace rtw {

template<typename InputIterator, typename T>
constexpr InputIterator linear_search(InputIterator first, InputIterator last, const T& value)
{
    while(first != last){
        if(*first == value){
            return first;
        }
        ++first;
    }
    return last;
}

template<typename InputIterator, typename Predicate>
constexpr InputIterator linear_search_if(InputIterator first, InputIterator last, Predicate predicate)
{
    while(first != last){
        if(predicate(*first)){
            return first;
        }
        ++first;
    }
    return last;
}

} // namespace rtw

#endif // RTW_LINEAR_SEARCH_HPP