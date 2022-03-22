#include "aircraft_manager.hpp"

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](std::unique_ptr<Aircraft>& a, std::unique_ptr<Aircraft>& b)
              { return a->has_terminal() < b->has_terminal() && a->get_fuel() < b->get_fuel(); });
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const auto& aircraft) { return !(aircraft)->move(); }),
                    aircrafts.end());
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

int AircraftManager::get_required_fuel()
{
    int sum = 0;
    for (const auto& aircraft : aircrafts)
    {
        if (aircraft->is_low_on_fuel() && !aircraft->get_has_finished())
        {
            sum += 3000 - aircraft->get_fuel();
        }
    }
    return sum;
}