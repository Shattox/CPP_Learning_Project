#pragma once

#include <string>
#include "aircraft_types.hpp"
#include "airport.hpp"

class AircraftFactory {
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    static constexpr size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

public:
    AircraftFactory()
    {
        {
            aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
            aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
            aircraft_types[2] = new AircraftType { .02f, .1f, .04f, MediaPath { "concorde_af.png" } };
        }
    }
    Aircraft* create_aircraft(Airport* airport, const AircraftType& type) const;
    Aircraft* create_random_aircraft(Airport* airport);
};