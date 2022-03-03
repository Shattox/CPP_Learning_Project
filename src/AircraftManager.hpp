#pragma once

#include <memory>
#include <vector>
#include "aircraft.hpp"
class AircraftManager : public GL::DynamicObject, public GL::Displayable {
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    bool move() override;
};

