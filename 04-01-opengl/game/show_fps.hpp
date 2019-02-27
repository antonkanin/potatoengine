#include <game_object.hpp>
#include <iostream>

class show_fps : public pt::game_object
{
public:
    explicit show_fps(pt::engine& engine)
        : pt::game_object(engine){};

    void update() override
    {
        using namespace std;

        cout << "test/n";
    }
};
