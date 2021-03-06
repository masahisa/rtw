#ifndef RTW_VECTOR_HPP
#define RTW_VECTOR_HPP

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

#include <rtw/container/allocator.hpp>

namespace rtw{

template<typename Allocator>
struct vector_iterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename std::allocator_traits<Allocator>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using reference = value_type&;
protected:
    pointer current_;
public:
    vector_iterator() = default;
    vector_iterator(const vector_iterator& other) = default;
    vector_iterator(vector_iterator&& other) = default;
    vector_iterator(pointer ptr)
    : current_(ptr){}
    vector_iterator& operator=(const vector_iterator& other) = default;
    vector_iterator& operator=(vector_iterator&& other) = default;
    ~vector_iterator() = default;
public:
    reference operator*() const{
        return *current_;
    }
    pointer operator->() const{
        return current_;
    }
    vector_iterator& operator++(){
        ++current_;
        return *this;
    }
    vector_iterator operator++(int) const{
        return vector_iterator(current_++);
    }
    vector_iterator& operator--(){
        --current_;
        return *this;
    }
    vector_iterator operator--(int) const{
        return vector_iterator(current_--);
    }
    vector_iterator& operator+=(const difference_type n){
        current_ += n;
        return *this;
    }
    vector_iterator operator+(const difference_type n) const{
        vector_iterator temp = *this;
        return temp += n;
    }
    vector_iterator& operator-=(const difference_type n){
        current_ -= n;
        return *this;
    }
    vector_iterator operator-(const difference_type n) const{
        vector_iterator temp = *this;
        return temp -= n;
    }
    reference operator[](const difference_type n) const{
        return current_[n];
    }
    template<typename Allocator1>
    friend typename vector_iterator<Allocator1>::difference_type operator-(const vector_iterator<Allocator1>& lhs, const vector_iterator<Allocator1>& rhs);
    template<typename Allocator1>
    friend bool operator==(const vector_iterator<Allocator1>& lhs, const vector_iterator<Allocator1>& rhs);
    template<typename Allocator1>
    friend bool operator<(const vector_iterator<Allocator1>& lhs, const vector_iterator<Allocator1>& rhs);
    pointer base() const{
        return current_;
    }
};

template<typename Allocator>
typename vector_iterator<Allocator>::difference_type operator-(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    using difference_type = typename vector_iterator<Allocator>::difference_type;
    return difference_type(lhs.current_ - rhs.current_);
}
template<typename Allocator>
bool operator==(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return lhs.current_ == rhs.current_;
}
template<typename Allocator>
bool operator!=(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return !(lhs == rhs);
}
template<typename Allocator>
bool operator<(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return lhs.current_ < rhs.current_;
}
template<typename Allocator>
bool operator<=(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return !(rhs < lhs);
}
template<typename Allocator>
bool operator>(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return rhs < lhs;
}
template<typename Allocator>
bool operator>=(const vector_iterator<Allocator>& lhs, const vector_iterator<Allocator>& rhs){
    return !(lhs < rhs);
}

template<typename Allocator>
struct vector_const_iterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename std::allocator_traits<Allocator>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using reference = const value_type&;
protected:
    pointer current_;
public:
    vector_const_iterator() = default;
    vector_const_iterator(const vector_const_iterator& other) = default;
    vector_const_iterator(vector_const_iterator&& other) = default;
    vector_const_iterator(pointer ptr)
    : current_(ptr){}
    vector_const_iterator(const vector_iterator<Allocator>& other)  // allow only iterator to const_iterator conversion
    : current_(other.base()){}
    vector_const_iterator& operator=(const vector_const_iterator& other) = default;
    vector_const_iterator& operator=(vector_const_iterator&& other) = default;
    ~vector_const_iterator() = default;
public:
    reference operator*() const{
        return *current_;
    }
    pointer operator->() const{
        return current_;
    }
    vector_const_iterator& operator++(){
        ++current_;
        return *this;
    }
    vector_const_iterator operator++(int) const{
        return vector_const_iterator(current_++);
    }
    vector_const_iterator& operator--(){
        --current_;
        return *this;
    }
    vector_const_iterator operator--(int) const{
        return vector_const_iterator(current_--);
    }
    vector_const_iterator& operator+=(const difference_type n){
        current_ += n;
        return *this;
    }
    vector_const_iterator operator+(const difference_type n) const{
        vector_const_iterator temp = *this;
        return temp += n;
    }
    vector_const_iterator& operator-=(const difference_type n){
        current_ -= n;
        return *this;
    }
    vector_const_iterator operator-(const difference_type n) const{
        vector_const_iterator temp = *this;
        return temp -= n;
    }
    reference operator[](const difference_type n) const{
        return current_[n];
    }
    template<typename Allocator1>
    friend typename vector_const_iterator<Allocator1>::difference_type operator-(const vector_const_iterator<Allocator1>& lhs, const vector_const_iterator<Allocator1>& rhs);
    template<typename Allocator1>
    friend bool operator==(const vector_const_iterator<Allocator1>& lhs, const vector_const_iterator<Allocator1>& rhs);
    template<typename Allocator1>
    friend bool operator<(const vector_const_iterator<Allocator1>& lhs, const vector_const_iterator<Allocator1>& rhs);
};

template<typename Allocator>
typename vector_const_iterator<Allocator>::difference_type operator-(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    using difference_type = typename vector_const_iterator<Allocator>::difference_type;
    return difference_type(lhs.current_ - rhs.current_);
}
template<typename Allocator>
bool operator==(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return lhs.current_ == rhs.current_;
}
template<typename Allocator>
bool operator!=(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return !(lhs == rhs);
}
template<typename Allocator>
bool operator<(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return lhs.current_ < rhs.current_;
}
template<typename Allocator>
bool operator<=(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return !(rhs < lhs);
}
template<typename Allocator>
bool operator>(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return rhs < lhs;
}
template<typename Allocator>
bool operator>=(const vector_const_iterator<Allocator>& lhs, const vector_const_iterator<Allocator>& rhs){
    return !(lhs < rhs);
}

template<typename T, typename Allocator = std::allocator<T>>
class vector{
public:
    using allocator_traits = std::allocator_traits<Allocator>;
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename allocator_traits::pointer;
    using const_pointer = typename allocator_traits::const_pointer;
    using iterator = vector_iterator<Allocator>;
    using const_iterator = vector_const_iterator<Allocator>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
protected:
    allocator_type allocator_;
    pointer begin_;
    pointer end_;
    pointer capacity_;
private:
    void copy_constructor_impl(const vector& other){
        size_type capacity = other.capacity();
        begin_ = allocator_traits::allocate(allocator_, capacity);
        std::uninitialized_copy(other.begin(), other.end(), begin());
        end_ = begin_ + other.size();
        capacity_ = begin_ + capacity;
    }
    template<typename InputIterator>
    void constructor_with_range(InputIterator first, InputIterator last){
        size_type count = size_type(last - first);
        begin_ = allocator_traits::allocate(allocator_, count);
        std::uninitialized_copy(first, last, begin_);
        capacity_ = begin_ + count;
        end_ = begin_ + count;
    }
    bool is_full() const{
        return end_ == capacity_;
    }
    size_type calculate_new_capacity() const{
        size_type old_capacity = capacity();
        return old_capacity == 0 ? 1 : 2 * old_capacity;
    }
    void reallocate(size_type new_capacity){
        pointer const new_begin = allocator_traits::allocate(allocator_, new_capacity);
        size_type old_size = size();
        std::uninitialized_move(begin_, end_, new_begin);
        std::destroy(begin_, end_);
        allocator_traits::deallocate(allocator_, begin_, capacity());
        begin_ = new_begin;
        end_ = begin_ + old_size;
        capacity_ = begin_ + new_capacity;
    }
    template<typename... Args>
    void resize_impl(size_type count, Args&&... args){
        if(count < size()){
            std::destroy(begin_ + count, end_);
            end_ = begin_ + count;
        }
        else if(count > size()){
            size_type old_size = size();
            if(count > capacity()){
                reallocate(count);
            }
            rtw::construct(allocator_, begin_ + old_size, begin_ + count, std::forward<Args>(args)...);
            end_ = begin_ + count;
        }
    }
    template<typename... Args>
    void reallocate_emplace(const_iterator position, Args&&... args){
        size_type new_capacity = calculate_new_capacity();
        pointer const new_begin = allocator_traits::allocate(allocator_, new_capacity);
        size_type position_distance = size_type(position - cbegin());
        pointer const old_position = begin_ + position_distance;
        size_type old_size = size();
        std::uninitialized_move(begin_, old_position, new_begin);
        allocator_traits::construct(allocator_, new_begin + position_distance, std::forward<Args>(args)...);
        std::uninitialized_move(old_position, end_, new_begin + position_distance + 1);
        std::destroy(begin_, end_);
        allocator_traits::deallocate(allocator_, begin_, capacity());
        begin_ = new_begin;
        end_ = begin_ + old_size + 1;
        capacity_ = begin_ + new_capacity;
    }
    template<typename... Args>
    void no_reallocate_emplace(const_iterator position, Args&&... args){
        pointer const pointer_position = begin_ + size_type(position - cbegin());
        std::move(pointer_position, end_, pointer_position + 1);
        allocator_traits::construct(allocator_, pointer_position, std::forward<Args>(args)...);
        ++end_;
    }
    void swap_without_allocator(vector&& other) noexcept{
        using std::swap;
        swap(begin_, other.begin_);
        swap(end_, other.end_);
        swap(capacity_, other.capacity_);
    }
public:
    // constructor
    vector() noexcept(noexcept(Allocator()))
    : allocator_(Allocator())
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){}
    explicit vector(const Allocator& allocator) noexcept
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){}
    vector(size_type count, const T& value, const Allocator& allocator = Allocator())
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        begin_ = allocator_traits::allocate(allocator_, count);
        std::uninitialized_fill_n(begin_, count, value);
        capacity_ = begin_ + count;
        end_ = begin_ + count;
    }
    explicit vector(size_type count, const Allocator& allocator = Allocator())
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        begin_ = allocator_traits::allocate(allocator_, count);
        std::uninitialized_value_construct_n(begin_, count);
        capacity_ = begin_ + count;
        end_ = begin_ + count;
    }
    template<typename InputIterator, typename = std::enable_if_t<std::is_convertible_v<typename std::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>>>
    vector(InputIterator first, InputIterator last, const Allocator& allocator = Allocator())
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        constructor_with_range(first, last);
    }
    vector(const vector& other)
    : allocator_(other.get_allocator())
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        copy_constructor_impl(other);
    }
    vector(const vector& other, const Allocator& allocator)
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        copy_constructor_impl(other);
    }
    vector(vector&& other) noexcept
    : allocator_(Allocator())
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        swap(other);
    }
    vector(vector&& other, const Allocator& allocator)
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        if constexpr(allocator_traits::is_always_equal::value){
            swap_without_allocator(std::move(other));
        }
        else{
            if(get_allocator() == other.get_allocator()){
                swap_without_allocator(std::move(other));
            }
            else{
                size_type capacity = other.capacity();
                begin_ = allocator_traits::allocate(allocator_, capacity);
                std::uninitialized_move(other.begin(), other.end(), begin());
                end_ = begin_ + other.size();
                capacity_ = begin_ + capacity;
            }
        }

    }
    vector(std::initializer_list<T> ilist, const Allocator& allocator = Allocator())
    : allocator_(allocator)
    , begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr){
        constructor_with_range(ilist.begin(), ilist.end());
    }
    // destructor
    ~vector(){
        std::destroy(begin_, end_);
        allocator_traits::deallocate(allocator_, begin_, capacity());
    }
    // operator=
    vector& operator=(const vector& other){
        if(&other != this){
            if constexpr(allocator_traits::propagate_on_container_copy_assignment::value){
                if constexpr(!allocator_traits::is_always_equal::value && get_allocator() != other.get_allocator()){
                    clear();
                }
                allocator_ = other.get_allocator();
            }

            size_type other_size = other.size();
            if(other_size > capacity()){
                pointer const new_begin = allocator_traits::allocate(allocator_, other_size);
                std::uninitialized_copy(other.begin(), other.end(), new_begin);
                std::destroy(begin_, end_);
                allocator_traits::deallocate(allocator_, begin_, capacity());
                begin_ = new_begin;
                capacity_ = begin_ + other_size;
            }
            else if(size() >= other_size){
                std::copy(other.begin(), other.end(), begin());
                std::destroy(begin_ + other_size, end_);
            }
            else{
                std::copy(other.begin(), other.begin() + size(), begin());
                std::uninitialized_copy(other.begin() + size(), other.end(), begin() + size());
            }
            end_ = begin_ + other_size;
        }
        return *this;
    }
    vector& operator=(vector&& other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<Allocator>::is_always_equal::value){
        if(&other != this){
            if constexpr(allocator_traits::propagate_on_container_move_assignment::value || allocator_traits::is_always_equal::value){
                swap(other);
            }
            else{
                if(get_allocator() == other.get_allocator()){
                    swap(other);
                }
                else{
                    assign(std::make_move_iterator(other.begin()), std::make_move_iterator(other.end()));
                    other.clear();
                }
            }
        }
        return *this;
    }
    vector& operator=(std::initializer_list<T> ilist){
        assign(ilist.begin(), ilist.end());
        return *this;
    }
    // assign
    void assign(size_type count, const T& value){
        if(count > capacity()){
            pointer const new_begin = allocator_traits::allocate(allocator_, count);
            std::uninitialized_fill_n(new_begin, count, value);
            std::destroy(begin_, end_);
            allocator_traits::deallocate(allocator_, begin_, capacity());
            begin_ = new_begin;
            capacity_ = begin_ + count;
        }
        else if(size() >= count){
            std::fill_n(begin_, count, value);
            std::destroy(begin_ + count, end_);
        }
        else{
            std::fill_n(begin_, size(), value);
            std::uninitialized_fill_n(begin_ + size(), count - size(), value);
        }
        end_ = begin_ + count;
    }
    template<typename InputIterator, typename = std::enable_if_t<std::is_convertible_v<typename std::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>>>
    void assign(InputIterator first, InputIterator last){
        size_type count = size_type(last - first);
        if(count > capacity()){
            pointer const new_begin = allocator_traits::allocate(allocator_, count);
            std::uninitialized_copy(first, last, new_begin);
            std::destroy(begin_, end_);
            allocator_traits::deallocate(allocator_, begin_, capacity());
            begin_ = new_begin;
            capacity_ = begin_ + count;
        }
        else if(size() >= count){
            std::copy(first, last, begin_);
            std::destroy(begin_ + count, end_);
        }
        else{
            std::copy(first , first + size(), begin_);
            std::uninitialized_copy(first + size(), last, begin_ + size());
        }
        end_ = begin_ + count;
    }
    void assign(std::initializer_list<T> ilist){
        assign(ilist.begin(), ilist.end());
    }
    // get_allocator
    allocator_type get_allocator() const{
        return allocator_;
    }
    // element access
    reference at(size_type position){
        if(position > size()){
            throw std::out_of_range("out_of_range");
        }
        return *(begin_ + position);
    }
    const_reference at(size_type position) const{
        if(position > size()){
            throw std::out_of_range("out_of_range");
        }
        return *(begin_ + position);
    }
    reference operator[](size_type position){
        return *(begin_ + position);
    }
    const_reference operator[](size_type position) const{
        return *(begin_ + position);
    }
    reference front(){
        return *begin_;
    }
    const_reference front() const{
        return *begin_;
    }
    reference back(){
        return *(end_ - 1);
    }
    const_reference back() const{
        return *(end_ - 1);
    }
    T* data() noexcept{
        return begin_;
    }
    const T* data() const noexcept{
        return begin_;
    }
    // iterators
    iterator begin() noexcept{
        return iterator(begin_);
    }
    const_iterator begin() const noexcept{
        return const_iterator(begin_);
    }
    const_iterator cbegin() const noexcept{
        return begin();
    }
    iterator end() noexcept{
        return iterator(end_);
    }
    const_iterator end() const noexcept{
        return const_iterator(end_);
    }
    const_iterator cend() const noexcept{
        return end();
    }
    reverse_iterator rbegin() noexcept{
        return reverse_iterator(end_);
    }
    const_reverse_iterator rbegin() const noexcept{
        return const_reverse_iterator(end_);
    }
    const_reverse_iterator crbegin() const noexcept{
        return rbegin();
    }
    reverse_iterator rend() noexcept{
        return reverse_iterator(begin_);
    }
    const_reverse_iterator rend() const noexcept{
        return const_reverse_iterator(begin_);
    }
    const_reverse_iterator crend() const noexcept{
        return rend();
    }
    // capacity
    [[nodiscard]] bool empty() const{
        return (begin_ == end_);
    }
    size_type size() const noexcept{
        return size_type(end_ - begin_);
    }
    size_type max_size() const noexcept{
        return allocator_traits::max_size(allocator_);
    }
    void reserve(size_type new_capacity){
        if(new_capacity > max_size()){
            throw std::length_error("length_error");
        }
        if(new_capacity > capacity()){
            reallocate(new_capacity);
        }
    }
    size_type capacity() const noexcept{
        return size_type(capacity_ - begin_);
    }
    void shrink_to_fit(){
        reallocate(size());
    }
    // modifiers
    void clear() noexcept{
        std::destroy(begin_, end_);
        end_ = begin_;
    }
    iterator insert(const_iterator position, const T& value){
        return emplace(position, value);
    }
    iterator insert(const_iterator position, T&& value){
        return emplace(position, std::move(value));
    }
    iterator insert(const_iterator position, size_type count, const T& value){
        size_type position_distance = size_type(position - cbegin());
        size_type new_size = size() + count;
        if(count != 0){
            if(new_size > capacity()){
                pointer const new_begin = allocator_traits::allocate(allocator_, new_size);
                pointer const old_position = begin_ + position_distance;
                std::uninitialized_move(begin_, old_position, new_begin);
                rtw::construct(allocator_, new_begin + position_distance, new_begin + position_distance + count, value);
                std::uninitialized_move(old_position, end_, new_begin + position_distance + count);
                std::destroy(begin_, end_);
                allocator_traits::deallocate(allocator_, begin_, capacity());
                begin_ = new_begin;
                end_ = begin_ + new_size;
                capacity_ = end_;
            }
            else{
                pointer const pointer_position = begin_ + position_distance;
                std::copy_backward(pointer_position, end_, end_ + count);
                std::fill(pointer_position, pointer_position + count, value);
                end_ += count;
            }
        } 
        return begin() + position_distance;
    }
    template<typename InputIterator, typename = std::enable_if_t<std::is_convertible_v<typename std::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>>>
    iterator insert(const_iterator position, InputIterator first, InputIterator last){
        size_type count = size_type(last - first);
        size_type position_distance = size_type(position - cbegin());
        size_type new_size = size() + count;
        if(count != 0){
            if(new_size > capacity()){
                pointer const new_begin = allocator_traits::allocate(allocator_, new_size);
                pointer const old_position = begin_ + position_distance;
                pointer const new_position = new_begin + position_distance;
                std::uninitialized_move(begin_, old_position, new_begin);
                std::uninitialized_copy(first, last, new_position);
                std::uninitialized_move(old_position, end_, new_position + count);
                std::destroy(begin_, end_);
                allocator_traits::deallocate(allocator_, begin_, capacity());
                begin_ = new_begin;
                end_ = begin_ + new_size;
                capacity_ = end_;
            }
            else{
                pointer const pointer_position = begin_ + position_distance;
                std::copy_backward(pointer_position, end_, end_ + count);
                std::copy(first, last, pointer_position);
                end_ += count;
            }
        }
        return begin() + position_distance;
    }
    iterator insert(const_iterator position, std::initializer_list<T> ilist){
        return insert(position, ilist.begin(), ilist.end());
    }
    template<typename... Args>
    iterator emplace(const_iterator position, Args&&... args){
        size_type position_distance = size_type(position - cbegin());
        if(position == cend()){
            emplace_back(std::forward<Args>(args)...);
        }
        else{
            if(is_full()){
                reallocate_emplace(position, std::forward<Args>(args)...);
            }
            else{
                no_reallocate_emplace(position, std::forward<Args>(args)...);
            }
        }
        return begin() + position_distance;
    }
    iterator erase(const_iterator position){
        iterator nonconst_position = begin() + size_type(position - cbegin());
        if(nonconst_position + 1 != end()){
            std::move(nonconst_position + 1, end(), nonconst_position);
        }
        --end_;
        std::destroy_at(end_);
        return nonconst_position;
    }
    iterator erase(const_iterator first, const_iterator last){
        iterator nonconst_first = begin() + size_type(first - cbegin());
        iterator nonconst_last = begin() + size_type(last - cbegin());
        if(nonconst_first != nonconst_last){
            if(nonconst_last != end()){
                std::move(nonconst_last, end(), nonconst_first);
            }
            end_ = nonconst_first.base() + size_type(end() - nonconst_last);
            std::destroy(end_, end_ + size_type(last - first));
        }
        return nonconst_first;
    }
    void push_back(const T& value){
        emplace_back(value);
    }
    void push_back(T&& value){
        emplace_back(std::move(value));
    }
    template<typename... Args>
    reference emplace_back(Args&&... args){
        if(is_full()){
            reallocate(calculate_new_capacity());
        }
        allocator_traits::construct(allocator_, end_, std::forward<Args>(args)...);
        ++end_;
        return back();
    }
    void pop_back(){
        --end_;
        std::destroy_at(end_);
    }
    void resize(size_type count){
        resize_impl(count);
    }
    void resize(size_type count, const value_type& value){
        resize_impl(count, value);
    }
    void swap(vector& other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value || std::allocator_traits<Allocator>::is_always_equal::value){
        using std::swap;
        swap(allocator_, other.allocator_);
        swap(begin_, other.begin_);
        swap(end_, other.end_);
        swap(capacity_, other.capacity_);
    }
};

template<typename T, typename Allocator>
bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template<typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return !(lhs == rhs);
}
template<typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template<typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return !(rhs < lhs);
}
template<typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return rhs < lhs;
}
template<typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs){
    return !(lhs < rhs);
}

template<typename T, typename Allocator>
void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs))){
    lhs.swap(rhs);
}

template<typename T, typename Allocator, typename U>
void erase(vector<T, Allocator>& container, const U& value){
    container.erase(std::remove(container.begin(), container.end(), value), container.end());
}
template<typename T, typename Allocator, typename Predicate>
void erase_if(vector<T, Allocator>& container, Predicate predicate){
    container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}

template<typename InputIterator, typename Allocator = std::allocator<typename std::iterator_traits<InputIterator>::value_type>>
vector(InputIterator, InputIterator, Allocator = Allocator()) -> vector<typename std::iterator_traits<InputIterator>::value_type, Allocator>;

}

#endif // RTW_VECTOR_HPP