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
        Vector3<float> &position_;

    public:
        Locatable(Vector3<float> &position);
        virtual ~Locatable();

        /** Setter for position */
        virtual Vector3<float> &position();

        /** Getter for position */
        virtual const Vector3<float> &position() const;
    };
};