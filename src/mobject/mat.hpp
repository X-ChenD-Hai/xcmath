/**
 * @file mat.hpp
 * @brief Header file for matrix class template and related utilities
 * @author XCDH
 * @version 1.0
 * @date 2023-10-05
 */

#ifndef XCMATH_MAT_H
#define XCMATH_MAT_H

#include <cstddef>

#include "../utils/concepts.h"
#include "./declaration.hpp"
#include "./vec.hpp"

namespace xcmath {
/**
 * @brief Matrix class template
 *
 * @tparam _Tp Type of elements in the matrix
 * @tparam _rows Number of rows
 * @tparam _cols Number of columns (defaults to _rows for square matrices)
 */
template <typename _Tp, size_t _rows, size_t _cols = _rows>
class mat : public vec<vec<_Tp, _cols>, _rows> {
   public:
    /**
     * @brief Shape of the matrix (rows x columns)
     */
    static constexpr vec2<size_t> shape{_rows, _cols};

    /**
     * @brief Inherit constructors from base class
     */
    using vec<vec<_Tp, _cols>, _rows>::vec;

    /**
     * @brief Inherit operator[] from base class
     */
    using vec<vec<_Tp, _cols>, _rows>::operator[];

    /**
     * @brief Inherit begin() from base class
     */
    using vec<vec<_Tp, _cols>, _rows>::begin;

    /**
     * @brief Inherit end() from base class
     */
    using vec<vec<_Tp, _cols>, _rows>::end;

    /**
     * @brief Inherit assignment operator from base class
     */
    using vec<vec<_Tp, _cols>, _rows>::operator=;

    /**
     * @brief Alias for the matrix type with a different element type
     *
     * @tparam _T Type of elements for the new matrix
     */
    template <class _T>
    using Self = mat<_T, _rows, _cols>;

    mat<_Tp, _rows, _cols>(const vec<vec<_Tp, _cols>, _rows>& o)
        : vec<vec<_Tp, _cols>, _rows>(o) {}

    /**
     * @brief Matrix multiplication operator
     *
     * @tparam _ncols Number of columns in the right matrix
     * @param other Right matrix to multiply with
     * @return Resulting matrix of type mat<_Tp, _rows, _ncols>
     */
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

    /**
     * @brief Matrix-vector multiplication operator
     *
     * @tparam _VTp Vector type
     * @param other Vector to multiply with
     * @return Resulting vector of type _VTp
     */
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

    /**
     * @brief Transpose operator
     *
     * @return Transposed matrix of type mat<_Tp, _cols, _rows>
     */
    constexpr mat<_Tp, _cols, _rows> T() const {
        mat<_Tp, _cols, _rows> res;
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                res[j][i] = this->data[i][j];
            }
        }
        return res;
    }

    /**
     * @brief Create a matrix filled with ones
     *
     * @return Matrix of type mat<_Tp, _rows, _cols> filled with ones
     */
    constexpr static mat<_Tp, _rows, _cols> ones() {
        return Self<_Tp>{vec<_Tp, _cols>{_Tp{1}}};
    }

    /**
     * @brief Create an identity matrix
     *
     * @return Identity matrix of type mat<_Tp, _rows, _cols>
     */
    constexpr static mat<_Tp, _rows, _cols> eye() {
        mat<_Tp, _rows, _cols> res;
        size_t n = _rows < _cols ? _rows : _cols;
        for (size_t i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    /**
     * @brief Compute determinant of the matrix
     *
     * @return Determinant value of type _Tp
     */
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

}  // namespace xcmath

#endif  // XCMATH_MAT_H