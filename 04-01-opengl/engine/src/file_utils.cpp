#include <file_utils.hpp>

#include <fstream>
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
        throw std::runtime_error("Error: file not found: " +
                                 std::string(file_path));
    }

    for (auto node : config)
    {
        auto game_object = node["game_object"];

        auto type = game_object["type"].Scalar();
        auto name = game_object["name"].Scalar();

        auto position = game_object["position"];

        if (position == nullptr)
        {
            log_error("Error: object '" + name +
                      "' does not have position parameter");
            continue;
        }

        auto pos_x = position["x"].as<float>();
        auto pos_y = position["y"].as<float>();
        auto pos_z = position["z"].as<float>();

        auto obj = engine.make_object(type, name);
        obj->set_position({ pos_x, pos_y, pos_z });

        auto scale = game_object["scale"];

        if (scale != nullptr)
        {
            auto scale_x = scale["x"].as<float>();
            auto scale_y = scale["y"].as<float>();
            auto scale_z = scale["z"].as<float>();

            obj->set_scale({ scale_x, scale_y, scale_z });
        }
    }
}

void save_scene(engine& engine, std::string_view file_path)
{
    YAML::Emitter out;

    for (const auto& it : engine)
    {
        if (it->is_serializable() == false)
        {
            continue;
        }

        out << YAML::BeginMap;

        out << YAML::Key << "game_object";

        out << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "type" << YAML::Value << "cube";
        out << YAML::Key << "name" << YAML::Value << it->get_name();
        out << YAML::EndMap;

        out << YAML::EndMap;
    }

    std::ofstream out_file(file_path.data());
    out_file << out.c_str();
}

} // namespace pt