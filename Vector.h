#include "Core.h"
#include <array>
#include <iostream>
#include <type_traits>
#include <cfloat>

namespace jmk {

    constexpr size_t DIM2 = 2;
    constexpr size_t DIM3 = 3;

    constexpr size_t X = 0;
    constexpr size_t Y = 1;
    constexpr size_t Z = 2;

    template <class coordinate_type, size_t dimension = DIM3>
    class Vector {
        static_assert(std::is_arithmetic<coordinate_type>::value, "Vector class can only store Integral or Floating point values");
        static_assert(dimension >= DIM2, "Vector dimension should be at least 2D");

        std::array<coordinate_type, dimension> coords;

    public:
        Vector() = default;

        Vector(const std::array<coordinate_type, dimension> _coords) : coords(_coords) {}

        Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z = 0) {
            static_assert(dimension == DIM3, "This constructor is only for 3D vectors.");
            coords = { _x, _y, _z };
        }

        // Equality Check
        bool operator==(const Vector<coordinate_type, dimension>&) const;

        // Not equal
        bool operator!=(const Vector<coordinate_type, dimension>&) const;

        // Addition
        Vector<coordinate_type, dimension> operator+(const Vector<coordinate_type, dimension>&) const;

        // Subtraction
        Vector<coordinate_type, dimension> operator-(const Vector<coordinate_type, dimension>&) const;

        // Less than operator
        bool operator <(const Vector<coordinate_type, dimension>&) const;

        // Greater than operator
        bool operator >(const Vector<coordinate_type, dimension>&) const;

        // Indexing operator
        coordinate_type operator[](int) const;

        void assign(int dim, coordinate_type value);

        template <class T, size_t D>
        friend float dotProduct(const Vector<T, D>&v1, 
        const Vector<T, D>& v2);

        float magnitude() const;

        void normalize();
    };

    typedef Vector<float, DIM2> Vector2f;
    typedef Vector<float, DIM3> Vector3f;

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator==(const Vector<coordinate_type, dimension>& _other) const {
        for (size_t i = 0; i < dimension; i++) {
            if (isEqualD(coords[i], _other.coords[i])) {
                return false;
            }
        }

        return true;
    }

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator!=(const Vector<coordinate_type, dimension>& _other) const {
        return !(*this == _other);
    }

    template<class coordinate_type, size_t dimension>
    inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator+(const Vector<coordinate_type, dimension>& _other) const {
        std::array<coordinate_type, dimension> result;
        for (size_t i = 0; i < dimension; i++) {
            result[i] = coords[i] + _other.coords[i];
        }
        return Vector<coordinate_type, dimension>(result);
    }

    template<class coordinate_type, size_t dimension>
    inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator-(const Vector<coordinate_type, dimension>& _other) const {
        std::array<coordinate_type, dimension> result;
        for (size_t i = 0; i < dimension; i++) {
            result[i] = coords[i] - _other.coords[i];
        }
        return Vector<coordinate_type, dimension>(result);
    }

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator<(const Vector<coordinate_type, dimension>& _other) const {
        for (size_t i = 0; i < dimension; i++) {
            if (this->coords[i] < _other.coords[i]) {
                return true;
            } else if (this->coords[i] > _other.coords[i]) {
                return false;
            }
        }
        return false;
    }

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator>(const Vector<coordinate_type, dimension>& _other) const {
       for (size_t i = 0; i < dimension; i++) {
            if (this->coords[i] > _other.coords[i]) {
                return true;
            } else if (this->coords[i] < _other.coords[i]) {
                return false;
            }
        }
        return false;
    }

    template<class coordinate_type, size_t dimension>
    inline coordinate_type Vector<coordinate_type, dimension>::operator[](int _index) const {
        if (_index >= coords.size() || _index < 0) {
            std::cerr << "Index out of bounds\n";
            return coordinate_type{};
        }
        return coords[_index];
    }

    template<class coordinate_type, size_t dimension>
    inline void Vector<coordinate_type, dimension>::assign(int dim, coordinate_type value)
    {
        coords[dim] = value;
    }

    template<class coordinate_type, size_t dimension>
    float dotProduct(const Vector<coordinate_type, dimension>&v1, 
        const Vector<coordinate_type, dimension>& v2) {
            if (v1.coords.size() != v2.coords.size()) {
                return FLT_MIN;
            }

            float product = 0.0;

            for (size_t i = 0; i < dimension; i++) {
                product += v1[i] * v2[i];
            }

            return product;
        }
    
    template<class coordinate_type, size_t dimension> 
    inline float Vector<coordinate_type, dimension>::magnitude() const
    {
        float value = 0.0f;

        for (size_t i = 0; i < dimension; i++) {
            value += pow(coords[i], 2.0);
        }

        return sqrt(value);
    } 

    template<class coordinate_type, size_t dimension> 
    inline void Vector<coordinate_type, dimension>::normalize()
    {
        auto mag = magnitude();

        for (size_t i = 0; i < dimension; i++) {
            assign(i, coords[i] / mag);
        }
    }

    float crossProduct2D(Vector2f v1, Vector2f v2);

    Vector3f crossProduct3D(Vector3f v1, Vector3f v2);

} // namespace jmk
