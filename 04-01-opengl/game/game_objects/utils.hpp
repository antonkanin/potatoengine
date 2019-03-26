#pragma once

#include <engine.hpp>
#include <functional>
#include <glm/vec4.hpp>

pt::game_object* find_collision(pt::engine& engine, const glm::vec4& from_ndc,
                                const glm::vec4& to_ndc);
