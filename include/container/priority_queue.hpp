#ifndef RTW_PRIORITY_QUEUE_HPP
#define RTW_PRIORITY_QUEUE_HPP

#include <type_traits>
#include <vector>
#include <functional>
#include <utility>
#include <memory>

#include "algorithm/heap.hpp"

namespace rtw{

template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class priority_queue{
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
protected:
    Container c;
    Compare comp;
public:
    // constructor
    priority_queue() = default;

    explicit priority_queue(const Compare& compare)
    : c()
    , comp(compare){}

    priority_queue(const Compare& compare, const Container& container)
    : c(container)
    , comp(compare){
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    priority_queue(const Compare& compare, Container&& container)
    : c(std::move(container))
    , comp(compare){
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    priority_queue(const priority_queue& other) = default;
    priority_queue(priority_queue&& other) = default;

    template<typename Allocator>
    explicit priority_queue(const Allocator& allocator)
    : c(allocator)
    , comp(){}

    template<typename Allocator>
    priority_queue(const Compare& compare, const Allocator& allocator)
    : c(allocator)
    , comp(compare){}

    template<typename Allocator>
    priority_queue(const Compare& compare, const Container& container, const Allocator& allocator)
    : c(container, allocator)
    , comp(compare){
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    template<typename Allocator>
    priority_queue(const Compare& compare, Container&& container, const Allocator& allocator)
    : c(std::move(container), allocator)
    , comp(compare){
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    template<typename Allocator>
    priority_queue(const priority_queue& other, const Allocator& allocator)
    : c(other.c, allocator)
    , comp(other.comp){}

    template<typename Allocator>
    priority_queue(priority_queue&& other, const Allocator& allocator)
    : c(std::move(other.c), allocator)
    , comp(std::move(other.comp)){}

    template<typename InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& compare, const Container& container)
    : c(container)
    , comp(compare){
        c.insert(c.end(), first, last);
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    template<typename InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& compare = Compare(), Container&& container = Container())
    : c(std::move(container))
    , comp(compare){
        c.insert(c.end(), first, last);
        rtw::make_heap(c.begin(), c.end(), comp);
    }

    // operator=
    priority_queue& operator=(const priority_queue& other) = default;
    priority_queue& operator=(priority_queue&& other) = default;

    // destructor
    ~priority_queue() = default;
public:
    const_reference top() const{
        return c.front();
    }
    bool empty() const{
        return c.empty();
    }
    size_type size() const{
        return c.size();
    }
    void push(const value_type& value){
        c.push_back(value);
        rtw::push_heap(c.begin(), c.end(), comp);
    }
    void push(value_type&& value){
        c.push_back(std::move(value));
        rtw::push_heap(c.begin(), c.end(), comp);
    }
    template<typename... Args>
    void emplace(Args&&... args){
        c.emplace_back(std::forward<Args>(args)...);
        rtw::push_heap(c.begin(), c.end(), comp);
    }
    void pop(){
        rtw::pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }
    void swap(priority_queue& other) noexcept(std::is_nothrow_swappable_v<Container> && std::is_nothrow_swappable_v<Compare>){
        using std::swap;
        swap(c, other.c);
        swap(comp, other.comp);
    }
};

template<typename T, typename Container, typename Compare>
void swap(rtw::priority_queue<T, Container, Compare>& lhs, rtw::priority_queue<T, Container, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))){
    lhs.swap(rhs);
}

template<typename Compare, typename Container>
priority_queue(Compare, Container)->priority_queue<typename Container::value_type, Container, Compare>;

template<typename InputIterator, typename Compare = std::less<typename std::iterator_traits<InputIterator>::value_type>, typename Container = std::vector<typename std::iterator_traits<InputIterator>::value_type>>
priority_queue(InputIterator, InputIterator, Compare = Compare(), Container = Container())->priority_queue<typename std::iterator_traits<InputIterator>::value_type, Container, Compare>;

template<typename Compare, typename Container, typename Allocator>
priority_queue(Compare, Container, Allocator)->priority_queue<typename Container::value_type, Container, Compare>;

} // namespace rtw

namespace std{
    template<typename T, typename Container, typename Compare, typename Allocator>
    struct uses_allocator<rtw::priority_queue<T, Container, Compare>, Allocator> : uses_allocator<Container, Allocator>::type{};
} // namespace std

#endif // RTW_PRIORITY_QUEUE_HPP