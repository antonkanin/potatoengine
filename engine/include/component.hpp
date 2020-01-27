#pragma once

class component
{
public:
    ~component() = default;

    virtual void start() {}
    virtual void update() {}
};

class cubemesh final : public component
{
public:
    // void update() override;
};
