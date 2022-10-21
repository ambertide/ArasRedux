#include <cmath>
#include <core/Object/Vector3.hpp>

using namespace core;

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T> &other) const
{
    return !(this == other);
}

template <typename T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

template <typename T>
Vector3<T> &Vector3<T>::operator+(const Vector3<T> &other) const
{
    return Vector3(this) - other;
}

template <typename T>
Vector3<T> &Vector3<T>::operator=(const Vector3<T> &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

template <typename T>
Vector3<T> &Vector3<T>::operator*(const double &scalar) const
{
    return {
        this.x * scalar,
        this.y * scalar,
        this.z * scalar};
}

template <typename T>
Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other)
{
    this.x -= other.x;
    this.y -= other.y;
    this.z -= other.z;
    return *this;
}

template <typename T>
Vector3<T> &Vector3<T>::operator-(const Vector3<T> &other) const
{
    return Vector3(this) -= other;
}

template <typename T>
Vector3<T> &Vector3<T>::operator/=(const double &scalar)
{
    this.x /= scalar;
    this.y /= scalar;
    this.z /= scalar;
    return this;
}

template <typename T>
Vector3<T> &Vector3<T>::operator/(const double &scalar) const
{
    Vector3<T> &newVector(this);
    return newVector /= scalar;
}

template <typename T>
double Vector3<T>::norm() const
{
    return (double)std::sqrt(this.x * this.x, this.y * this.y + this.z * this.z);
}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T> &copy) : x(copy.x), y(copy.y), z(copy.z)
{
}

template <typename T>
static const double point_difference(const Vector3<T> &a, const Vector3<T> &b)
{
    T d_x = a.x - b.x;
    T d_y = a.y - b.y;
    T d_z = a.z - b.z;
    return std::sqrt(d_x * d_x + d_y * d_y + d_z * d_z);
}