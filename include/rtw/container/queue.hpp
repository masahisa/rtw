#ifndef RTW_QUEUE_HPP
#define RTW_QUEUE_HPP

#include <deque>
#include <memory>
#include <type_traits>
#include <utility>

namespace rtw{

template<typename T, typename Container = std::deque<T>>
class queue{
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
    queue() = default;
    
    explicit queue(const Container& container)
    : c(container){}

    explicit queue(Container&& container)
    : c(std::move(container)){}

    queue(const queue& other) = default;
    queue(queue&& other) = default;

    template<typename Allocator>
    explicit queue(const Allocator& allocator)
    : c(allocator){}

    template<typename Allocator>
    queue(const Container& container, const Allocator& allocator)
    : c(container, allocator){}

    template<typename Allocator>
    queue(Container&& container, const Allocator& allocator)
    : c(std::move(container), allocator){}

    template<typename Allocator>
    queue(const queue& other, const Allocator& allocator)
    : c(other.c, allocator){}

    template<typename Allocator>
    queue(queue&& other, const Allocator& allocator)
    : c(std::move(other.c), allocator){}

    // operator=
    queue& operator=(const queue& other) = default;
    queue& operator=(queue&& other) = default;

    // destructor
    ~queue() = default;
public:
    reference front(){
        return c.front();
    }
    const_reference front() const{
        return c.front();
    }
    reference back(){
        return c.back();
    }
    const_reference back() const{
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
        c.pop_front();
    }
    void swap(queue& other) noexcept(std::is_nothrow_swappable_v<Container>){
        using std::swap;
        swap(c, other.c);
    }

    template<typename T1, typename Container1>
    friend bool operator==(const queue<T1, Container1>& lhs, const queue<T1, Container1>& rhs);

    template<typename T1, typename Container1>
    friend bool operator<(const queue<T1, Container1>& lhs, const queue<T1, Container1>& rhs);
};

template<typename T, typename Container>
bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return lhs.c == rhs.c;
}

template<typename T, typename Container>
bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return !(lhs == rhs);
}

template<typename T, typename Container>
bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return lhs.c < rhs.c;
}

template<typename T, typename Container>
bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return !(rhs < lhs);
}

template<typename T, typename Container>
bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return rhs < lhs;
}

template<typename T, typename Container>
bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs){
    return !(lhs < rhs);
}

template<typename T, typename Container>
void swap(rtw::queue<T, Container>& lhs, rtw::queue<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))){
    lhs.swap(rhs);
}

template<typename Container>
queue(Container)->queue<typename Container::value_type, Container>;

template<typename Container, typename Allocator>
queue(Container, Allocator)->queue<typename Container::value_type, Container>;

} // namespace rtw

namespace std{
    template<typename T, typename Container, typename Allocator>
    struct uses_allocator<rtw::queue<T, Container>, Allocator> : public std::uses_allocator<Container, Allocator>::type{};
} // namespace std

#endif // RTW_QUEUE_HPP