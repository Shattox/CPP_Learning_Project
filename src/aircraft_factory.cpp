#include "aircraft_factory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(Airport& airport, const AircraftType& type)
{
    assert(&airport); // make sure the airport is initialized before creating aircraft

    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));

    while (flight_numbers.find(flight_number) != flight_numbers.end())
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    flight_numbers.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, *(&airport.get_tower()));
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport& airport)
{
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}

void AircraftFactory::count_airline_aircrafts(int x) const
{
    assert(x >= 0 && x < 8);

    std::cout << airlines[x] << " : "
              << std::count_if(flight_numbers.begin(), flight_numbers.end(),
                               [this, x](const std::string& flight_number)
                               { return airlines[x] == flight_number.substr(0, 2); })
              << std::endl;
}