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
        auto node_name = node.first.as<std::string>();
        if (node_name == "game_objects")
        {
            auto objects = node.second;
            for (auto object : objects)
            {
                auto type = object["type"].Scalar();
                auto name = object["name"].Scalar();

                auto position = object["position"];

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

                auto scale = object["scale"];

                if (scale != nullptr)
                {
                    auto scale_x = scale["x"].as<float>();
                    auto scale_y = scale["y"].as<float>();
                    auto scale_z = scale["z"].as<float>();

                    obj->set_scale({ scale_x, scale_y, scale_z });
                }
            }
        }

    }

    return;

#ifdef no
    for (auto node : config)
    {
        auto game_objects = node["game_objects"];

        for (auto object : game_objects)
        {
            auto type = object["type"].Scalar();
            auto name = object["name"].Scalar();

            auto position = object["position"];

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

            auto scale = object["scale"];

            if (scale != nullptr)
            {
                auto scale_x = scale["x"].as<float>();
                auto scale_y = scale["y"].as<float>();
                auto scale_z = scale["z"].as<float>();

                obj->set_scale({ scale_x, scale_y, scale_z });
            }
        }
    }
#endif
}

void save_scene(engine& engine, std::string_view file_path)
{
    YAML::Emitter out;

    out << YAML::BeginSeq;

    for (const auto& it : engine)
    {
        if (it->is_serializable() == false)
        {
            continue;
        }

        // out << "game_object1";

        out << "game_object1";

        out << YAML::BeginSeq;

        // out << YAML::Block;

        // out << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "type" << YAML::Value << "cube";
        out << YAML::Key << "name" << YAML::Value << it->get_name();
        out << YAML::EndMap;

        out << YAML::EndSeq;

        out << YAML::Newline;
    }
    out << YAML::EndSeq;

    std::ofstream out_file(file_path.data());
    out_file << out.c_str();
}

} // namespace pt