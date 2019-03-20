#include <file_utils.hpp>

#include <game_object.hpp>
#include <iostream>
#include <log_utils.hpp>
#include <yaml-cpp/yaml.h>

namespace pt
{

void load_scene(engine& engine, std::string_view file_path)
{

    YAML::Node config = YAML::LoadFile(std::string(file_path));
    if (config == nullptr)
    {
        throw std::runtime_error("File not found: " + std::string(file_path));
    }

    for (const auto& node : config)
    {
        auto game_object = node["game_object"];

        auto type = game_object["type"].Scalar();
        auto name = game_object["name"].Scalar();

        auto position = game_object["position"];

        auto pos_x = position["x"].as<float>();
        auto pos_y = position["y"].as<float>();
        auto pos_z = position["z"].as<float>();

        auto scale = game_object["scale"];

        auto scale_x = scale["x"].as<float>();
        auto scale_y = scale["y"].as<float>();
        auto scale_z = scale["z"].as<float>();

        auto obj = engine.make_object(type, name);
        obj->set_position({ pos_x, pos_y, pos_z });
        ///obj->set_scale({ scale_x, scale_y, scale_z });

        log_line() << "position : " << obj->get_position() << std::endl;

        //        engine.add_object<tyope>()
        //
        //        std::cout << pos_x << std::endl;
        //
        //        std::cout << game_object.as<std::string>() << std::endl;
        //
        //        if (node["game_object"])
        //        {
        //            std::cout << "node[name]" << node["game_object"] <<
        //            std::endl;
        //        }
    }
}

} // namespace pt