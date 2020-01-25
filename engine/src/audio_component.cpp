#include "audio_component.hpp"
#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <log_utils.hpp>

namespace pt
{

using chunk_ptr_type = std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)>;

struct audio_component_impl
{
    std::map<std::string, chunk_ptr_type> sounds;
};

void audio_component::init()
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        throw std::runtime_error("error: failed to initialize SDL audio " +
                                 std::string(SDL_GetError()));
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        throw std::runtime_error("error: failed to open SDL audio mixer " +
                                 std::string(SDL_GetError()));
    }
}

audio_component::audio_component()
    : impl(std::make_unique<audio_component_impl>())
{
}

bool audio_component::load_sound(const std::string& sound_name,
                                 const std::string& file_path)
{
    if (impl->sounds.count(sound_name) > 0)
    {
        std::cerr << "error: sound with the same name already exists "
                  << sound_name << '\n';
        return false;
    }

    auto wave = Mix_LoadWAV(file_path.c_str());

    if (wave == nullptr)
    {
        std::cerr << "error: could not load the sound from the file "
                  << file_path << ": " << SDL_GetError() << '\n';
        return false;
    }

    chunk_ptr_type chunk_ptr(wave, Mix_FreeChunk);
    impl->sounds.insert({ sound_name, std::move(chunk_ptr) });

    return true;
}

bool audio_component::play_sound(const std::string& sound_name) const
{
    if (impl->sounds.count(sound_name) == 0)
    {
        std::cerr << "error: sound with this name has not been loaded: "
                  << sound_name << '\n';
        return false;
    }

    auto wave = impl->sounds.at(sound_name).get();

    Mix_PlayChannel(-1, wave, 0);

    return true;
}

audio_component::~audio_component()
{
    Mix_CloseAudio();
}

} // namespace pt