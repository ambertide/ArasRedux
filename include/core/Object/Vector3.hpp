#include <stdint.h>
#include <type_traits>
#include <cmath>

#pragma once
namespace core
{
	template <typename T>
	struct Vector3
	{
		// Limit the Vector3 to arithmatic classes.
		static_assert(std::is_arithmetic_v<T>);
		T x;
		T y;
		T z;
		bool operator==(const Vector3<T> &other) const = default;
		bool operator!=(const Vector3<T> &other) const
		{
			return !(this == other);
		}

		Vector3<T> &operator+=(const Vector3<T> &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		Vector3<T> operator+(const Vector3<T> &other) const
		{
			Vector3<T> newVector = *this;
			return newVector += other;
		}

		Vector3<T> &operator=(const Vector3<T> &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
		}

		Vector3<T> operator*(const double &scalar) const
		{
			return {
				this->x * (float)scalar,
				this->y * (float)scalar,
				this->z * (float)scalar};
		}

		Vector3<T> &operator-=(const Vector3<T> &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		Vector3<T> operator-(const Vector3<T> &other) const
		{
			Vector3<T> newCopy = *this;
			return newCopy -= other;
		}

		Vector3<T> &operator/=(const double &scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}

		Vector3<T> operator/(const double &scalar) const
		{
			Vector3<T> newVector = *this;
			return newVector /= scalar;
		}

		/**
		 * @brief Get the size of a vector.
		 *
		 * @return double
		 */
		double norm() const
		{
			return (double)std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		/**
		 * @brief Get the distance between two vectors as if
		 * they are points.
		 *
		 * @param a
		 * @param b
		 * @return float
		 */
		static const double point_distance(const Vector3<T> &a, const Vector3<T> &b)
		{
			T d_x = a.x - b.x;
			T d_y = a.y - b.y;
			T d_z = a.z - b.z;
			return std::sqrt(d_x * d_x + d_y * d_y + d_z * d_z);
		}

		Vector3(T x, T y, T z) : x(x), y(y), z(z)
		{
		}

		Vector3(const Vector3<T> &copy) : x(copy.x), y(copy.y), z(copy.z)
		{
		}
	};
};
