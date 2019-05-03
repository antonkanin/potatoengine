#include "enemy.hpp"

#include "player.hpp"
#include "enemies_spawer.hpp"

int enemy::counter = 0;

void enemy::start()
{
    auto player_object = get_engine().find_game_object("Player");

    if (player_object == nullptr)
    {
        pt::log_line("Could not find Player game_object");
    }

    player_ = dynamic_cast<player*>(player_object);

    auto enemies_spawner_object = get_engine().find_game_object("Enemies spawner");

    enemies_spawner_ = dynamic_cast<enemies_spawner*>(enemies_spawner_object);

    if (enemies_spawner_ == nullptr)
    {
        pt::log_line("Could not find Enemies Spawner game_object");
    }

    // set_model(pt::model("res/cube/cube.obj"));
    // set_model(pt::model("res/figure.obj"));
    load_model("res/cube/cube_leopard.obj");

    pt::log_line("Enemy #" + std::to_string(counter));
}

void enemy::hit()
{
    health--;

    if (health <= 0)
    {
        self_destroy();

        if (enemies_spawner_ != nullptr)
        {
            enemies_spawner_->kill_enemy();
        }
    }
}

void enemy::move_enemy()
{
    if (player_ == nullptr)
    {
        return;
    }

    auto player_pos = player_->get_position();

    auto move_direction = player_pos - get_position();

    move_direction = ptm::normalize(move_direction);

    set_position(get_position() +
                 move_direction * get_engine().delta_time() * move_speed);
}
void enemy::rotate()
{
    set_rotation(ptm::vec3::up(), get_transformation().rotation_angle +
                                      0.2f * get_engine().delta_time());
}
