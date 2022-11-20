#pragma once
#include "Hurtable.hpp"
#include "Locatable.hpp"

namespace core
{
    /**
     * @brief Implies that this object can be tracked and hurt.
     *
     */
    class Targetable : public Hurtable, virtual public Locatable
    {
    public:
        explicit Targetable(Vector3<float> position, int max_health, int health) : Locatable::Locatable(position), Hurtable::Hurtable(max_health, health) {}
        virtual ~Targetable() = default;
    };
} // namespace core
