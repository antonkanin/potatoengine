#pragma once

namespace pt
{

class engine;

class game_object
{
public:
    game_object(engine& engine)
        : engine_(engine)
    {
    }

    virtual ~game_object() = default;

    virtual void update() = 0;

protected:
    engine& get_engine();

private:
    pt::engine& engine_;
};

} // namespace pt