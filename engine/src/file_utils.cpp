#include <file_utils.hpp>

#include <fstream>
#include <game_object.hpp>
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

    for (const auto& node : config)
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

                obj->add_body(false);
            }
        }
    }
}

void save_vector(YAML::Emitter& out, std::string_view name, ptm::vec3 position)
{
    out << YAML::Key << std::string(name) << YAML::Value;

    out << YAML::Flow;
    out << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << position.x;
    out << YAML::Key << "y" << YAML::Value << position.y;
    out << YAML::Key << "z" << YAML::Value << position.z;
    out << YAML::EndMap;
}

void save_scene(engine& engine, std::string_view file_path)
{
    YAML::Emitter out;

    out << YAML::BeginMap << YAML::Key << "game_objects" << YAML::BeginSeq;

    for (const auto& it : engine)
    {
        if (!it->is_serializable())
        {
            continue;
        }

        out << YAML::BeginMap;
        out << YAML::Key << "type" << YAML::Value << "cube";
        out << YAML::Key << "name" << YAML::Value << it->get_name();

        save_vector(out, "position", it->get_position());

        save_vector(out, "scale", it->get_scale());

        out << YAML::EndMap << YAML::Newline;
    }

    out << YAML::EndSeq << YAML::EndMap;

    std::ofstream out_file(file_path.data());
    out_file << out.c_str();
}

} // namespace pt