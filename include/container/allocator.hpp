#ifndef RTW_ALLOCATOR_HPP
#define RTW_ALLOCATOR_HPP

#include <memory>

namespace rtw{

template<typename ForwardIterator, typename Allocator, typename... Args>
void construct(Allocator allocator, ForwardIterator first, ForwardIterator last, Args&&... args)
{
    using allocator_traits = std::allocator_traits<Allocator>;
    while(first != last){
        allocator_traits::construct(allocator, first, std::forward<Args>(args)...);
        ++first;
    }
}

template<typename ForwardIterator, typename Allocator>
void destroy(Allocator allocator, ForwardIterator first, ForwardIterator last)
{
    using allocator_traits = std::allocator_traits<Allocator>;
    while(first != last){
        allocator_traits::destroy(allocator, first);
        ++first;
    }
}

} // namespace rtw

#endif // RTW_ALLOCATOR_HPP