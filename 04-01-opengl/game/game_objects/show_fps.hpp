#include <game_object.hpp>
#include <iostream>

class show_fps final : public pt::game_object
{
public:
    void start() override { get_engine().enable_vsync(false); }

    void update() override
    {
        delta_ += get_engine().delta_time();
        ++frames_count_;

        if (delta_ >= 1.f)
        {
            std::cout << frames_count_ << std::endl;
            frames_count_ = 0;
            delta_        = 0;
        }
    }

private:
    float        delta_        = 0.f;
    unsigned int frames_count_ = 0;
};
