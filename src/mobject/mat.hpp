// mat.hpp
#ifndef XCMATH_MAT_H
#define XCMATH_MAT_H
#include <cstddef>

#include "../utils/concepts.h"
#include "./vec.hpp"

namespace xcmath {
template <typename _Tp, size_t _rows, size_t _cols = _rows>
class mat : public vec<vec<_Tp, _cols>, _rows> {
   public:
    static constexpr vec2<size_t> shape{_rows, _cols};
    using vec<vec<_Tp, _cols>, _rows>::vec;
    using vec<vec<_Tp, _cols>, _rows>::operator[];
    using vec<vec<_Tp, _cols>, _rows>::begin;
    using vec<vec<_Tp, _cols>, _rows>::end;
    using vec<vec<_Tp, _cols>, _rows>::operator=;
    template <class _T>
    using Self = mat<_T, _rows, _cols>;
    template <size_t _ncols>
    constexpr mat<_Tp, _rows, _ncols> operator^(
        const mat<_Tp, _cols, _ncols>& other) {
        mat<_Tp, _rows, _ncols> res;
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _ncols; j++) {
                for (size_t k = 0; k < _cols; k++) {
                    res[i][j] += this->data[i][k] * other[k][j];
                }
            }
        }
        return res;
    }
    template <Vec _VTp>
        requires(_VTp::length == _rows) &&
                concepts::Add<typename _VTp::DataType> &&
                concepts::Muitiply<typename _VTp::DataType, _Tp>
    constexpr _VTp operator^(const _VTp& other) {
        _VTp res;
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                res[i] += this->data[i][j] * other[j];
            }
        }
        return res;
    }
    constexpr mat<_Tp, _cols, _rows> T() const {
        mat<_Tp, _cols, _rows> res;
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                res[j][i] = this->data[i][j];
            }
        }
        return res;
    }
    constexpr static mat<_Tp, _rows, _cols> ones() {
        _Tp one{};
        return mat<_Tp, _rows, _cols>{
            vec<vec<_Tp, _cols>, _rows>{vec<_Tp, _cols>{++one}}};
    }
    constexpr static mat<_Tp, _rows, _cols> eye() {
        mat<_Tp, _rows, _cols> res;
        size_t n = _rows < _cols ? _rows : _cols;
        for (size_t i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }
    // determinant
    constexpr _Tp det() const
        requires(_rows == _cols)
    {
        if constexpr (_rows == 1) {
            return this->data[0][0];
        } else if constexpr (_rows == 2) {
            return this->data[0][0] * this->data[1][1] -
                   this->data[0][1] * this->data[1][0];
        } else {
            _Tp res = 0;
            for (size_t j = 0; j < _rows; j++) {
                mat<_Tp, _rows - 1, _cols - 1> submat;
                for (size_t i = 1; i < _rows; i++) {
                    for (size_t k = 0; k < j; k++) {
                        submat[i - 1][k] = this->data[i][k];
                    }
                    for (size_t k = j + 1; k < _cols; k++) {
                        submat[i - 1][k - 1] = this->data[i][k];
                    }
                }
                res +=
                    ((j % 2 == 0) ? 1 : -1) * this->data[0][j] * submat.det();
            }
            return res;
        }
    }
};

template <class _Tp>
using mat1x2 = mat<_Tp, 1, 2>;
template <class _Tp>
using mat1x3 = mat<_Tp, 1, 3>;
template <class _Tp>
using mat1x4 = mat<_Tp, 1, 4>;
template <class _Tp>
using mat2x1 = mat<_Tp, 2, 1>;
template <class _Tp>
using mat2x2 = mat<_Tp, 2, 2>;
template <class _Tp>
using mat2x3 = mat<_Tp, 2, 3>;
template <class _Tp>
using mat2x4 = mat<_Tp, 2, 4>;
template <class _Tp>
using mat3x1 = mat<_Tp, 3, 1>;
template <class _Tp>
using mat3x2 = mat<_Tp, 3, 2>;
template <class _Tp>
using mat3x3 = mat<_Tp, 3, 3>;
template <class _Tp>
using mat3x4 = mat<_Tp, 3, 4>;
template <class _Tp>
using mat4x1 = mat<_Tp, 4, 1>;
template <class _Tp>
using mat4x2 = mat<_Tp, 4, 2>;
template <class _Tp>
using mat4x3 = mat<_Tp, 4, 3>;
template <class _Tp>
using mat4x4 = mat<_Tp, 4, 4>;
template <class _Tp>
using mat3 = mat3x3<_Tp>;
template <class _Tp>
using mat4 = mat4x4<_Tp>;

using mat1x2f = mat1x2<float>;
using mat1x3f = mat1x3<float>;
using mat1x4f = mat1x4<float>;
using mat2x1f = mat2x1<float>;
using mat2x2f = mat2x2<float>;
using mat2x3f = mat2x3<float>;
using mat2x4f = mat2x4<float>;
using mat3x1f = mat3x1<float>;
using mat3x2f = mat3x2<float>;
using mat3x3f = mat3x3<float>;
using mat3x4f = mat3x4<float>;
using mat4x1f = mat4x1<float>;
using mat4x2f = mat4x2<float>;
using mat4x3f = mat4x3<float>;
using mat4x4f = mat4x4<float>;

using mat1x2d = mat1x2<double>;
using mat1x3d = mat1x3<double>;
using mat1x4d = mat1x4<double>;
using mat2x1d = mat2x1<double>;
using mat2x2d = mat2x2<double>;
using mat2x3d = mat2x3<double>;
using mat2x4d = mat2x4<double>;
using mat3x1d = mat3x1<double>;
using mat3x2d = mat3x2<double>;
using mat3x3d = mat3x3<double>;
using mat3x4d = mat3x4<double>;
using mat4x1d = mat4x1<double>;
using mat4x2d = mat4x2<double>;
using mat4x3d = mat4x3<double>;
using mat4x4d = mat4x4<double>;

using mat1x2i = mat1x2<int>;
using mat1x3i = mat1x3<int>;
using mat1x4i = mat1x4<int>;
using mat2x1i = mat2x1<int>;
using mat2x2i = mat2x2<int>;
using mat2x3i = mat2x3<int>;
using mat2x4i = mat2x4<int>;
using mat3x1i = mat3x1<int>;
using mat3x2i = mat3x2<int>;
using mat3x3i = mat3x3<int>;
using mat3x4i = mat3x4<int>;
using mat4x1i = mat4x1<int>;
using mat4x2i = mat4x2<int>;
using mat4x3i = mat4x3<int>;
using mat4x4i = mat4x4<int>;

using mat1x2l = mat1x2<long>;
using mat1x3l = mat1x3<long>;
using mat1x4l = mat1x4<long>;
using mat2x1l = mat2x1<long>;
using mat2x2l = mat2x2<long>;
using mat2x3l = mat2x3<long>;
using mat2x4l = mat2x4<long>;
using mat3x1l = mat3x1<long>;
using mat3x2l = mat3x2<long>;
using mat3x3l = mat3x3<long>;
using mat3x4l = mat3x4<long>;
using mat4x1l = mat4x1<long>;
using mat4x2l = mat4x2<long>;
using mat4x3l = mat4x3<long>;
using mat4x4l = mat4x4<long>;

using mat1x2ul = mat1x2<unsigned long>;
using mat1x3ul = mat1x3<unsigned long>;
using mat1x4ul = mat1x4<unsigned long>;
using mat2x1ul = mat2x1<unsigned long>;
using mat2x2ul = mat2x2<unsigned long>;
using mat2x3ul = mat2x3<unsigned long>;
using mat2x4ul = mat2x4<unsigned long>;
using mat3x1ul = mat3x1<unsigned long>;
using mat3x2ul = mat3x2<unsigned long>;
using mat3x3ul = mat3x3<unsigned long>;
using mat3x4ul = mat3x4<unsigned long>;
using mat4x1ul = mat4x1<unsigned long>;
using mat4x2ul = mat4x2<unsigned long>;
using mat4x3ul = mat4x3<unsigned long>;
using mat4x4ul = mat4x4<unsigned long>;

using mat1x2b = mat1x2<bool>;
using mat1x3b = mat1x3<bool>;
using mat1x4b = mat1x4<bool>;
using mat2x1b = mat2x1<bool>;
using mat2x2b = mat2x2<bool>;
using mat2x3b = mat2x3<bool>;
using mat2x4b = mat2x4<bool>;
using mat3x1b = mat3x1<bool>;
using mat3x2b = mat3x2<bool>;
using mat3x3b = mat3x3<bool>;
using mat3x4b = mat3x4<bool>;
using mat4x1b = mat4x1<bool>;
using mat4x2b = mat4x2<bool>;
using mat4x3b = mat4x3<bool>;
using mat4x4b = mat4x4<bool>;

using mat2f = mat2x2f;
using mat3f = mat3x3f;
using mat4f = mat4x4f;
using mat2d = mat2x2d;
using mat3d = mat3x3d;
using mat4d = mat4x4d;
using mat2i = mat2x2i;
using mat3i = mat3x3i;
using mat4i = mat4x4i;
using mat2l = mat2x2l;
using mat3l = mat3x3l;
using mat4l = mat4x4l;
using mat2ul = mat2x2ul;
using mat3ul = mat3x3ul;
using mat4ul = mat4x4ul;
using mat2b = mat2x2b;
using mat3b = mat3x3b;
using mat4b = mat4x4b;

}  // namespace xcmath

#endif  // XCMATH_MAT_H