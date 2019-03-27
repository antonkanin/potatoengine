#include "enemy.hpp"

#include "player.hpp"

void enemy::start()
{
    auto player_object = get_engine().find_game_object("Player");

    if (player_object == nullptr)
    {
        throw std::runtime_error("Could not find Player game_object");
    }

    player_ = dynamic_cast<player*>(player_object);

    set_model(pt::model("res/cube/cube.obj"));
}

void enemy::hit()
{
    pt::log_line("My health " + std::to_string(health));
    health--;
}

void enemy::update()
{
    auto player_pos = player_->get_position();

    auto move_direction = player_pos - get_position();

    move_direction = ptm::normalize(move_direction);

    set_position(get_position() + move_direction * get_engine().delta_time() * move_speed);
}
