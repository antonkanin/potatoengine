#pragma once

#include <string>

namespace pt
{

class PtException
{
public:
    explicit PtException(std::string message)
        : message_{ std::move(message) } {};

    [[nodiscard]] std::string message() const { return message_; }

private:
    std::string message_{};
};

} // namespace pt