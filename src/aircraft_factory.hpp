#pragma once

#include "aircraft_types.hpp"
#include "airport.hpp"

#include <string>
#include <unordered_set>

class AircraftFactory
{
private:
    const std::array<std::string, 8> airlines = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    static constexpr size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::unordered_set<std::string> flight_numbers;

public:
    AircraftFactory()
    {
        {
            aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
            aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
            aircraft_types[2] = new AircraftType { .02f, .1f, .04f, MediaPath { "concorde_af.png" } };
        }
    }
    std::unique_ptr<Aircraft> create_aircraft(Airport& airport, const AircraftType& type);
    std::unique_ptr<Aircraft> create_random_aircraft(Airport& airport);
    void count_airline_aircrafts(int x) const;
};
