#include <game_object.hpp>
#include <iostream>

class show_fps : public pt::game_object
{
public:
    void update() override
    {
        using namespace std;

        cout << "test/n";
    }

};
