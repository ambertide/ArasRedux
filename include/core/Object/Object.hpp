#pragma once
#include <string>
#include "Vector3.hpp"
#include "../Traits/Locatable.hpp"

namespace core
{

    /**
     * @brief Types of the object.
     *
     */
    enum ObjectType
    {
        BASIC,
        CHARACTER,
        PLAYER
    };

    /**
     * @brief Any game object that has a physical presence on the map.
     *
     */
    class Object : virtual public Locatable
    {
    private:
        const ObjectType object_type_;

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
        uint64_t id() const { return this->id_; }

        /** @brief Get the name of the object. */
        const std::string name() const { return this->name_; };

        /** @brief Get the unique class id of the object. */
        uint16_t class_id() const { return this->class_id_; };

        ObjectType object_type() const { return this->object_type_; }

        /**
         * @brief Construct a new Object object.
         *
         * @param id
         */
        Object(uint32_t class_id, uint64_t id, const std::string name, Vector3<float> position, const ObjectType type = ObjectType::BASIC)
            : Locatable::Locatable(position),
              object_type_(type),
              class_id_(class_id),
              id_(id),
              name_(name) {}
    };
};