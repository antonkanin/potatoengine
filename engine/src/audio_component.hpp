#pragma once

#include <memory>
#include <string>

namespace pt
{

class audio_component
{
public:
    audio_component();
    ~audio_component();

    void init();

    bool load_sound(const std::string& sound_name,
                    const std::string& file_path);

    bool play_sound(const std::string& sound_name) const;

private:
    std::unique_ptr<class audio_component_impl> impl;
};

} // namespace pt