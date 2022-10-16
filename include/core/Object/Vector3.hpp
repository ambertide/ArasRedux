#include <stdint.h>
#include <type_traits>

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
		bool operator==(const Vector3<T> &) const = default;
		bool operator!=(const Vector3<T> &) const;
		Vector3<T> &operator+(const Vector3<T> &other) const;
		Vector3<T> &operator+=(const Vector3<T> &other);
		Vector3<T> &operator=(const Vector3<T> &other);
		Vector3<T> &operator*(const double &scalar) const;
		Vector3<T> &operator*=(const double &scalar);
		Vector3<T> &operator-(const Vector3<T> &other) const;
		Vector3<T> &operator-=(const Vector3<T> &other);
		Vector3<T> &operator/(const double &scalar) const;
		Vector3<T> &operator/=(const double &scalar);
		/**
		 * @brief Get the size of a vector.
		 *
		 * @return double
		 */
		double norm() const;
	};
};
