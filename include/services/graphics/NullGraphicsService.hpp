#include "GraphicsService.hpp"

namespace services
{
    class NullGraphicsService final : public GraphicsService
    {
    private:
        /* data */
    protected:
        virtual void draw(const core::Object &locatable) override{};
        virtual void init_screen() override{};
        virtual void release_screen() override{};

    public:
        NullGraphicsService(/* args */) : GraphicsService(){};
        ~NullGraphicsService(){};
        virtual void mainloop() override{};
        virtual bool available() const override { return true; }
    };
}