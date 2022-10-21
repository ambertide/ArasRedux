#include <core/Traits/Locatable.hpp>

using namespace core;

Vector3<float> &Locatable::position()
{
    return this->position_;
};

const Vector3<float> &Locatable::position() const
{
    return this->position_;
};