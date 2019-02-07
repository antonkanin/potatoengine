#pragma onace

#include "engine.h"

namespace pt
{

class game_object
{
public:
    explicit game_object(engine* engine) : engine_(engine) {}
    virtual ~game_object() = 0;

    virtual void input()  = 0;
    virtual void update() = 0;
    virtual void draw()   = 0;

private:
    pt::engine* engine_;
};

} // namespace pt