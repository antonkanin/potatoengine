#include <game_objects_list.hpp>

#include "log_utils.hpp"
#include <algorithm>
#include <game_object.hpp>

namespace pt
{

void game_objects_list::add_object(std::unique_ptr<game_object> object)
{
    auto  name_size = object->get_name().size();
    char* name_str  = new char[name_size + 1];

    std::strcpy(name_str, object->get_name().c_str());

    names_.push_back(name_str);

    objects_.push_back(std::move(object));
}

void game_objects_list::remove_object(const game_object* object)
{
    for (auto index = objects_.size() - 1; index >= 0; --index)
    {
        if (objects_[index].get() == object)
        {
            delete names_[index];
            names_.erase(names_.begin() + index);

            objects_.erase(objects_.begin() + index);
        }
    }
}

const char* const* game_objects_list::get_names() const
{
    return names_.data();
}

game_objects_list::const_object_iterator game_objects_list::cbegin() const
{
    return objects_.cbegin();
}

game_objects_list::const_object_iterator game_objects_list::cend() const
{
    return objects_.cend();
}

game_objects_list::object_iterator game_objects_list::begin()
{
    return objects_.begin();
}

game_objects_list::object_iterator game_objects_list::end()
{
    return objects_.end();
}

size_t game_objects_list::size() const
{
    return objects_.size();
}

void game_objects_list::update_name(game_object* object, std::string_view name)
{
    object->set_name(std::string(name));

    throw std::runtime_error("not implemented");
}

game_object* game_objects_list::find_object(std::string_view name)
{
    auto found_object =
        std::find_if(objects_.begin(), objects_.end(),
                     [name](const std::unique_ptr<game_object>& object) {
                         return object->get_name() == name;
                     });

    if (found_object == objects_.end())
    {
        return nullptr;
    }

    return found_object->get();
}

game_object* game_objects_list::find_object(btRigidBody* rigid_body)
{
    for (const auto& object : objects_)
    {
        if (object->body_ == rigid_body)
        {
            return object.get();
        }
    }
    return nullptr;
}

void game_objects_list::clean_destoyed_objects()
{
    delete_if(objects_.begin(), objects_.end(), [](const auto& object){}
    )
    for (auto& back_it = objects_.rbegin(); back_it != objects_.rbegin();
         ++back_it)
    {
        if (back_it->get()->to_be_destroyed_)
        {
            back_it->get()->destroy_forced();
        }

        objects_.erase(back_it);
    }
}

} // namespace pt