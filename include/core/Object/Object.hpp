#include <Vector3.hpp>

namespace core
{
    class Object
    {
    protected:
        Vector3<float> position_;
        uint64_t id_;

    public:
        /** Setter for position */
        Vector3<float> &position();

        /** Getter for position */
        const Vector3<float> &position() const;

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