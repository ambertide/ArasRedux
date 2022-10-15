#include <Object/Vector3.hpp>

using namespace core;

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T> &other) const
{
    return !(this == other);
}

template <typename T>
Vector3<T> &Vector3<T>::operator+(const Vector3<T> &other)
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z};
}

template <typename T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}
