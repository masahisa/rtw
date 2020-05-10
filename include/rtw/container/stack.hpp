#ifndef RTW_STACK_HPP
#define RTW_STACK_HPP

#include <type_traits>
#include <deque>
#include <utility>
#include <memory>

namespace rtw{

template<typename T, typename Container = std::deque<T>>
class stack{
public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
protected:
    Container c;
public:
    // constructor
    stack() = default;
    
    explicit stack(const Container& container)
    : c(container){}

    explicit stack(Container&& container)
    : c(std::move(container)){}

    stack(const stack& other) = default;
    stack(stack&& other) = default;

    template<typename Allocator>
    explicit stack(const Allocator& allocator)
    : c(allocator){}

    template<typename Allocator>
    stack(const Container& container, const Allocator& allocator)
    : c(container, allocator){}

    template<typename Allocator>
    stack(Container&& container, const Allocator& allocator)
    : c(std::move(container), allocator){}

    template<typename Allocator>
    stack(const stack& other, const Allocator& allocator)
    : c(other.c, allocator){}

    template<typename Allocator>
    stack(stack&& other, const Allocator& allocator)
    : c(std::move(other.c), allocator){}

    // operator=
    stack& operator=(const stack& other) = default;
    stack& operator=(stack&& other) = default;

    // destructor
    ~stack() = default;
public:
    reference top(){
        return c.back();
    }
    const_reference top() const{
        return c.back();
    }
    [[nodiscard]] bool empty() const{
        return c.empty();
    }
    size_type size() const{
        return c.size();
    }
    void push(const value_type& value){
        c.push_back(value);
    }
    void push(value_type&& value){
        c.push_back(std::move(value));
    }
    template<typename... Args>
    decltype(auto) emplace(Args&&... args){
        return c.emplace_back(std::forward<Args>(args)...);
    }
    void pop(){
        c.pop_back();
    }
    void swap(stack& other) noexcept(std::is_nothrow_swappable_v<Container>){
        using std::swap;
        swap(c, other.c);
    }

    template<typename T1, typename Container1>
    friend bool operator==(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

    template<typename T1, typename Container1>
    friend bool operator<(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);
};

template<typename T, typename Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return lhs.c == rhs.c;
}

template<typename T, typename Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return !(lhs == rhs);
}

template<typename T, typename Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return lhs.c < rhs.c;
}

template<typename T, typename Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return !(rhs < lhs);
}

template<typename T, typename Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return rhs < lhs;
}

template<typename T, typename Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs){
    return !(lhs < rhs);
}

template<typename T, typename Container>
void swap(rtw::stack<T, Container>& lhs, rtw::stack<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))){
    lhs.swap(rhs);
}

template<typename Container>
stack(Container)->stack<typename Container::value_type, Container>;

template<typename Container, typename Allocator>
stack(Container, Allocator)->stack<typename Container::value_type, Container>;

} // namespace rtw

namespace std{
    template<typename T, typename Container, typename Allocator>
    struct uses_allocator<rtw::stack<T, Container>, Allocator> : public std::uses_allocator<Container, Allocator>::type{};
} // namespace std

#endif // RTW_STACK_HPP