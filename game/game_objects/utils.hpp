#pragma once

#include <engine.hpp>
#include <functional>
#include <glm/vec4.hpp>

pt::game_object* find_collision(pt::engine& engine, const glm::vec4& from_ndc,
                                const glm::vec4& to_ndc);

std::tuple<glm::vec4, glm::vec4> get_world_ray(pt::engine& engine,
                                               glm::vec4   from_ndc,
                                               glm::vec4   to_ndc);
