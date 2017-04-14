#ifndef _iterator_HPP
#define _iterator_HPP

template <class T> class vector_base;

#include "iterator_base.hpp"
#include "../vector/vector_base.hpp"

template <class T>
class _iterator : public iterator_base<T> {
    public:
        _iterator(const _iterator&);

        T& operator*();
        T* operator->();

        friend class vector_base<T>;

    private:
        _iterator(T*);
};

template <class T>
_iterator<T>::_iterator(T* pointer) : iterator_base<T>(pointer) {

}

template <class T>
_iterator<T>::_iterator(const _iterator& other) : iterator_base<T>(other.pointer) {

}

template <class T>
T& _iterator<T>::operator*() {
    return *this->pointer;
}

template <class T>
T* _iterator<T>::operator->() {
    return this->pointer;
}

#endif // _iterator_HPP
