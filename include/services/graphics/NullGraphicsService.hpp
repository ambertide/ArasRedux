#include "GraphicsService.hpp"

namespace services
{
    class NullGraphicsService final : public GraphicsService
    {
    private:
        /* data */
    public:
        NullGraphicsService(/* args */);
        ~NullGraphicsService(){};
        void mainloop() override{};
    };
}