#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace pt
{

class game_object;

class game_objects_list
{
public:
    void add_object(std::unique_ptr<game_object> object);

    const char* const* get_names() const;

    void swap_names(int index_1, int index_2) {}

    game_object* find_object(std::string_view name);

    void delete_object(game_object* object) {}

    void update_name(game_object* object, std::string_view name);

    using game_object_list      = std::vector<std::unique_ptr<game_object>>;
    using const_object_iterator = game_object_list::const_iterator;

    const_object_iterator cbegin() const;
    const_object_iterator cend() const;

    using object_iterator = game_object_list::iterator;

    object_iterator begin();
    object_iterator end();

    size_t size() const;

    game_object& operator[](size_t index) { return *(objects_[index].get()); }

private:
    std::vector<std::unique_ptr<game_object>> objects_;

    std::vector<const char*>  names_;
    std::vector<unsigned int> indexes_;
};

} // namespace pt