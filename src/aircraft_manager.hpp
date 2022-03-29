#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int aircraft_crashed = 0;

public:
    void move() override;
    void add(std::unique_ptr<Aircraft> aircraft);
    int get_required_fuel();
    int get_aircraft_crashed() const { return aircraft_crashed; }
    void incremente_aircraft_crash() { aircraft_crashed++; }
};
