#include <engine.hpp>
#include <game_object.hpp>
#include <input_manager.hpp>
#include <iostream>
#include <movable_object.hpp>

class object_selector final : public pt::game_object
{
public:
    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            auto dir = get_engine().get_camera().get_direction();
            auto pos = get_engine().get_camera().get_position();

            std::cout << "pos: " << pos << ", dir: " << dir << std::endl;

            auto bt_dir = btVector3{ dir.x, dir.y, dir.z };
            auto bt_pos = btVector3{ pos.x, pos.y, pos.z };

            btCollisionWorld::ClosestRayResultCallback rayCallBack(
                bt_pos, bt_dir * 100);

            get_engine().get_dynamics_world()->rayTest(bt_pos, bt_dir * 100,
                                                       rayCallBack);

            std::cout << "Click!" << std::endl;

            if (rayCallBack.hasHit())
            {
                std::cout << "Hit!" << std::endl;
            }
        }

        std::cout << get_engine().get_input_manager().get_axis_x() << ' '
                  << get_engine().get_input_manager().get_axis_y() << std::endl;
    }

public:
};
