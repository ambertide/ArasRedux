#include <stdint.h>

namespace core
{
	template <typename T>
	struct Vector3
	{
		T x;
		T y;
		T z;
		bool operator==(const Vector3<T> &) const = default;
		bool operator!=(const Vector3<T> &) const;
		Vector3<T> &operator+(const Vector3<T> &other);
		Vector3<T> &operator+=(const Vector3<T> &other);
	};
};
