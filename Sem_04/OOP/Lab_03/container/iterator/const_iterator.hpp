#ifndef _const_iterator_HPP
#define _const_iterator_HPP

template <class T> class vector_base;

#include "iterator_base.hpp"
#include "../vector/vector_base.hpp"

template <class T>
class _const_iterator : public iterator_base<T> {
    public:
        _const_iterator(const _const_iterator&);

        const T& operator*();
        const T* operator->();

        friend class vector_base<T>;

    private:
        _const_iterator(T*);
};

template <class T>
_const_iterator<T>::_const_iterator(T* pointer) : iterator_base<T>(pointer) {

}

template <class T>
_const_iterator<T>::_const_iterator(const _const_iterator& other) : iterator_base<T>(other.pointer) {

}

template <class T>
const T& _const_iterator<T>::operator*() {
    return *this->pointer;
}

template <class T>
const T* _const_iterator<T>::operator->() {
    return this->pointer;
}

#endif // _const_iterator_HPP
