#include "Hurtable.hpp"
#include "Locatable.hpp"

namespace core
{
    /**
     * @brief Implies that this object can be tracked and hurt.
     *
     */
    class Targetable : public Hurtable, public Locatable
    {
    public:
        Targetable(Vector3<float> position, int max_health, int health) : Hurtable::Hurtable(max_health, health), Locatable::Locatable(position) {}
        ~Targetable();
    };
} // namespace core
