#include <game_object.hpp>

class cube : public pt::game_object
{
    using pt::game_object::game_object;

    void start() override
    {
        set_model(pt::model("res/cube/cube.obj"));
    }

public:
    bool is_serializable() const override
    {
        return true;
    }
};
