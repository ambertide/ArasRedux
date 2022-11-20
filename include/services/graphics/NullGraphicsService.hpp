#include "GraphicsService.hpp"

namespace services
{
    class NullGraphicsService final : public GraphicsService
    {
    private:
        /* data */
    protected:
        virtual void init_screen() override {}
        virtual void release_screen() override {}
        virtual void print_player_stats() override {}
        virtual void render_player() override {}
        virtual void render(core::Object*) override {}
        virtual void render(core::Character*) override {}
        virtual void render_objects() override {}
        virtual void handle_user_input() override {}

    public:
        NullGraphicsService(/* args */) : GraphicsService(){};
        ~NullGraphicsService(){};
        virtual void mainloop() override{};
        virtual bool available() const override { return true; }
    };
}