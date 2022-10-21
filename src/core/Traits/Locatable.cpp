#include <Traits/Locatable.hpp>

using namespace core;

Locatable::Locatable(Vector3<float> &position) : position_(position)
{
}

Vector3<float> &Locatable::position()
{
    return this->position_;
};

const Vector3<float> &Locatable::position() const
{
    return this->position_;
};