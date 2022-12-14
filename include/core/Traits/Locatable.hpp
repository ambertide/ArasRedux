#pragma once
#include "../Object/Vector3.hpp"
namespace core
{
    /**
     * @brief Objects that have a position.
     *
     */
    class Locatable
    {
    protected:
        Vector3<float> position_;

    public:
        explicit Locatable(Vector3<float> position) : position_(position) {}
        virtual ~Locatable() = default;

        /** Setter for position */
        virtual Vector3<float> &position();

        /** Getter for position */
        virtual const Vector3<float> &position() const;
    };
};