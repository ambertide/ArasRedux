#pragma once
#include "Vector3.hpp"
#include "../Traits/Locatable.hpp"

namespace core
{
    class Object : public Locatable
    {
    protected:
        uint64_t id_;

    public:
        /**
         * @brief Get the unique object ID.
         *
         * @return const uint64_t& Const reference to object id.
         */
        const uint64_t &id() const;

        /**
         * @brief Construct a new Object object
         *
         * @param id
         */
        Object(uint64_t id, Vector3<float> position);
    };
};