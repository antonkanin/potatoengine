#include <game_object.hpp>
#include <input_manager.hpp>

class audio_test final : public pt::game_object
{
    using pt::game_object::game_object;

    void start() override
    {
        get_engine().load_sound(sound_name, "res/audio/door1.wav");
    }

    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::button_a))
        {
            get_engine().play_sound(sound_name);
        }
    }

    const std::string sound_name = "noise";
};
