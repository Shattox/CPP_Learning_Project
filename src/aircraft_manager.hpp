#pragma once

#include <memory>
#include <vector>
#include "aircraft.hpp"
#include "GL/dynamic_object.hpp"

class AircraftManager : public GL::DynamicObject {
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add(Aircraft* aircraft);
};
