#pragma once
#include <string>
#include "Vector3.hpp"
#include "../Traits/Locatable.hpp"

namespace core
{
    class Object : virtual public Locatable
    {
    protected:
        /** Id of the Object's class. */
        const uint32_t class_id_;
        const uint64_t id_;
        const std::string name_;

    public:
        /**
         * @brief Get the unique object ID.
         *
         * @return const uint64_t& Const reference to object id.
         */
        const uint64_t &id() const;

        /** @brief Get the name of the object. */
        const std::string &name() const;

        /** @brief Get the unique class id of the object. */
        const uint16_t &class_id() const;

        /**
         * @brief Construct a new Object object
         *
         * @param id
         */
        Object(uint32_t class_id, uint64_t id, const std::string name, Vector3<float> position) : class_id_(class_id_), id_(id), name_(name), Locatable::Locatable(position) {}
        virtual ~Object();
    };
};