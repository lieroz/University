#ifndef VECTOR_BASE_HPP
#define VECTOR_BASE_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>

#include "../exceptions.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/const_iterator.hpp"

template <class T>
class vector_base {
        const size_t BASE_SIZE = 7;

    public:
        typedef _iterator<T> iterator;
        typedef _const_iterator<T> const_iterator;

        explicit vector_base();
        explicit vector_base(size_t);
        explicit vector_base(size_t, const T&);
        vector_base(iterator, iterator);
        vector_base(const_iterator, const_iterator);
        vector_base(std::initializer_list<T>);
        vector_base(const vector_base&);
        vector_base(vector_base&&);
        virtual ~vector_base();
        vector_base& operator=(const vector_base&);
        vector_base& operator=(vector_base&&);
        vector_base& operator=(std::initializer_list<T>);

        T& at(size_t);
        const T& at(size_t) const;
        T& operator[](size_t);
        const T& operator[](size_t) const;

        iterator begin();
        const_iterator cbegin() const;
        iterator end();
        const_iterator cend() const;

        iterator rbegin();
        const_iterator rcbegin() const;
        iterator rend();
        const_iterator rcend() const;

        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        void clear();
        void swap(vector_base&);

        template <class U>
        friend inline void swap(vector_base<T>&, vector_base<T>&);

        template <class U>
        friend inline bool operator==(const vector_base<T>&, const vector_base<T>&);
        template <class U>
        friend inline bool operator!=(const vector_base<T>&, const vector_base<T>&);
        template <class U>
        friend inline bool operator<(const vector_base<T>&, const vector_base<T>&);
        template <class U>
        friend inline bool operator<=(const vector_base<T>&, const vector_base<T>&);
        template <class U>
        friend inline bool operator>(const vector_base<T>&, const vector_base<T>&);
        template <class U>
        friend inline bool operator>=(const vector_base<T>&, const vector_base<T>&);

        template <class U>
        friend inline std::ostream& operator<<(std::ostream&, const vector_base<T>&);

    protected:
        size_t element_count;
        size_t memory_dump;
        T* buffer;

        inline void reallocate();
};

template <class T>
vector_base<T>::vector_base() : element_count(0), memory_dump(BASE_SIZE) {
    try {
        this->buffer = new T[this->capacity()];

    } catch (std::bad_alloc& ex) {
        throw bad_memory_allocation_exception();
    }
}

template <class T>
vector_base<T>::vector_base(size_t count) : element_count(count), memory_dump(count) {
    try {
        this->buffer = new T[this->capacity()];

    } catch (std::bad_alloc& ex) {
        throw bad_memory_allocation_exception();
    }
}

template <class T>
vector_base<T>::vector_base(size_t count, const T& value) : vector_base(count) {
    for (size_t i = 0; i < this->size(); ++i) {
        (*this)[i] = value;
    }
}

template <class T>
vector_base<T>::vector_base(iterator first, iterator last) : vector_base(last - first) {
    for (size_t i = 0; i < this->size(); ++i, ++first) {
        (*this)[i] = *first;
    };
}

template <class T>
vector_base<T>::vector_base(const_iterator first, const_iterator last) : vector_base(last - first) {
    for (size_t i = 0; i < this->size(); ++i, ++first) {
        (*this)[i] = *first;
    };
}

template <class T>
vector_base<T>::vector_base(std::initializer_list<T> lst) : vector_base(lst.size()) {
    std::copy(lst.begin(), lst.end(), this->buffer);
}

template <class T>
vector_base<T>::vector_base(const vector_base<T>& other) : vector_base(other.size()) {
    std::copy(other.buffer, other.buffer + other.size(), this->buffer);
}

template <class T>
vector_base<T>::vector_base(vector_base<T>&& other)
    : element_count(other.element_count), memory_dump(other.memory_dump), buffer(other.buffer) {
    other.element_count = 0;
    other.memory_dump = 0;
    other.buffer = nullptr;
}

template <class T>
vector_base<T>::~vector_base() {
    delete[] this->buffer;
    this->memory_dump = 0;
    this->buffer = nullptr;
}

template <class T>
vector_base<T>& vector_base<T>::operator=(const vector_base<T>& rhs) {
    if (this != &rhs) {
        this->element_count = rhs.size();
        this->memory_dump = rhs.capacity();

        try {
            this->buffer = new T[this->capacity()];

        } catch (std::bad_alloc& ex) {
            throw bad_memory_allocation_exception();
        }

        std::copy(this->buffer, this->buffer + this->size(), this->begin());
    }

    return *this;
}

template <class T>
vector_base<T>& vector_base<T>::operator=(vector_base<T>&& rhs) {
    if (this != &rhs) {
        this->element_count = rhs.size();
        this->memory_dump = rhs.capacity();
        this->buffer = (std::move(rhs.buffer));

        rhs.element_count = 0;
        rhs.memory_dump = 0;
        rhs.buffer = nullptr;
    }

    return *this;
}

template <class T>
vector_base<T>& vector_base<T>::operator=(std::initializer_list<T> lst) {
    this->vector_base(lst);
    return *this;
}

template <class T>
T& vector_base<T>::at(size_t pos) {
    if (pos < this->size()) {
        return (*this)[pos];

    } else {
        throw out_of_range_exception();
    }
}

template <class T>
const T& vector_base<T>::at(size_t pos) const {
    if (pos < this->size()) {
        return (*this)[pos];

    } else {
        throw out_of_range_exception();
    }
}

template <class T>
T& vector_base<T>::operator[](size_t pos) {
    if (pos < this->size()) {
        return this->buffer[pos];

    } else {
        throw out_of_range_exception();
    }
}

template <class T>
const T& vector_base<T>::operator[](size_t pos) const {
    if (pos < this->size()) {
        return this->buffer[pos];

    } else {
        throw out_of_range_exception();
    }
}

template <class T>
typename vector_base<T>::iterator vector_base<T>::begin() {
    return iterator(this->buffer);
}

template <class T>
typename vector_base<T>::const_iterator vector_base<T>::cbegin() const {
    return const_iterator(this->buffer);
}

template <class T>
typename vector_base<T>::iterator vector_base<T>::end() {
    return iterator(this->buffer + this->size());
}

template <class T>
typename vector_base<T>::const_iterator vector_base<T>::cend() const {
    return const_iterator(this->buffer + this->size());
}

template <class T>
typename vector_base<T>::iterator vector_base<T>::rbegin() {
    return iterator(this->buffer + this->size() - 1);
}

template <class T>
typename vector_base<T>::const_iterator vector_base<T>::rcbegin() const {
    return const_iterator(this->buffer + this->size() - 1);
}

template <class T>
typename vector_base<T>::iterator vector_base<T>::rend() {
    return iterator(this->buffer - 1);
}

template <class T>
typename vector_base<T>::const_iterator vector_base<T>::rcend() const {
    return const_iterator(this->buffer - 1);
}

template <class T>
bool vector_base<T>::empty() const {
    return this->element_count == 0;
}

template <class T>
size_t vector_base<T>::size() const {
    return this->element_count;
}

template <class T>
size_t vector_base<T>::capacity() const {
    return this->memory_dump;
}

template <class T>
void vector_base<T>::clear() {
    for (size_t i = 0; i < this->size(); ++i) {
        (*this)[i].~T();
    }

    this->element_count = 0;
}

template <class T>
inline void vector_base<T>::reallocate() {
    try {
        T* temp_buffer = new T[this->capacity()];
        std::copy(this->buffer, this->buffer + this->size(), temp_buffer);
        delete[] this->buffer;
        this->buffer = temp_buffer;

    } catch (std::bad_alloc& ex) {
        throw bad_memory_allocation_exception();
    }
}

template <class T>
void vector_base<T>::swap(vector_base<T>& other) {
    std::swap(this->element_count, other.element_count);
    std::swap(this->memory_dump, other.memory_dump);
    std::swap(this->buffer, other.buffer);
}

template <class T>
void swap(vector_base<T>& lhs, vector_base<T>& rhs) {
    lhs.swap(rhs);
}

template <class T>
bool operator==(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    bool are_equal = lhs.size() == rhs.size();

    if (are_equal) {

        for (size_t i = 0; i < lhs.size() && are_equal; ++i) {

            if (lhs[i] != rhs[i]) {
                are_equal = false;
            }
        }
    }

    return are_equal;
}

template <class T>
bool operator!=(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    return !(rhs == lhs);
}

template <class T>
bool operator<(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    bool is_less = lhs.size() < rhs.size();

    if (!is_less && lhs.size() == rhs.size()) {

        for (size_t i = 0; i < lhs.size() && !is_less; ++i) {

            if (lhs[i] < rhs[i]) {
                is_less = true;
            }
        }
    }

    return is_less;
}

template <class T>
bool operator<=(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    return lhs < rhs || lhs == rhs;
}

template <class T>
bool operator>(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

template <class T>
bool operator>=(const vector_base<T>& lhs, const vector_base<T>& rhs) {
    return lhs > rhs || lhs == rhs;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const vector_base<T>& vec) {
    for (typename vector_base<T>::const_iterator iter = vec.cbegin(); iter != vec.cend(); ++iter) {
        std::cout << *iter << " ";
    }

    return stream;
}

#endif // VECTOR_BASE_HPP
