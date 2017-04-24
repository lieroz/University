#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include "containers/matrix/matrix.hpp"
#include "vector4d.hpp"

template <class T>
class matrix4x4 : public matrix<T> {
        static_assert(std::is_arithmetic<T>::value, "Type nust be arithmetic!");

    public:
        matrix4x4();
        matrix4x4(std::initializer_list<T>);
        matrix4x4(const matrix4x4&);
        matrix4x4(matrix4x4&&);
        ~matrix4x4() = default;

        matrix4x4& operator=(const matrix4x4&);
        matrix4x4& operator=(matrix4x4&&);
        matrix4x4& operator=(std::initializer_list<T>);

        template <class U>
        friend vector4d<U> operator*(const vector4d<U>&, const matrix4x4<U>&);
        template <class U>
        friend matrix4x4<U> operator*(const matrix4x4<U>&, const U&);
};

template <class T>
matrix4x4<T>::matrix4x4()
    : matrix<double>(4, 4) {

}

template <class T>
matrix4x4<T>::matrix4x4(std::initializer_list<T> lst)
    : matrix<T>(4, 4, lst) {

}

template <class T>
matrix4x4<T>::matrix4x4(const matrix4x4<T>& other)
    : matrix<T>(other) {

}

template <class T>
matrix4x4<T>::matrix4x4(matrix4x4<T>&& other)
    : matrix<T>(std::move(other)) {

}

template <class T>
matrix4x4<T>& matrix4x4<T>::operator=(const matrix4x4& rhs) {
    matrix<T>::operator=(rhs);
    return *this;
}

template <class T>
matrix4x4<T>& matrix4x4<T>::operator=(matrix4x4&& rhs) {
    matrix<T>::operator=(std::move(rhs));
    return *this;
}

template <class T>
matrix4x4<T>& matrix4x4<T>::operator=(std::initializer_list<T> lst) {
    matrix<T>::operator=(lst);
    return *this;
}

template <class T>
vector4d<T> operator*(const vector4d<T>& vec, const matrix4x4<T>& mtx) {
    vector4d<double> result = {0, 0, 0, 0};

    for (size_t i = 0; i < 4; ++i) {

        for (size_t j = 0; j < 4; ++j) {
            result[i] += mtx[i][j] * vec[j];
        }
    }

    return result;
}

template <class T>
matrix4x4<T> operator*(const matrix4x4<T>& mtx, const T& value) {
    matrix4x4<T> result = mtx;

    for (size_t i = 0; i < mtx.capacity(); ++i) {
        result.buffer[i] *= value;
    }

    return result;
}

#endif // MATRIX4X4_HPP
