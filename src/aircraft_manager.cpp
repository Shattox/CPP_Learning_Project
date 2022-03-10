#include "aircraft_manager.hpp"

void AircraftManager::move() {
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const auto& aircraft) {
                                       if (!(aircraft)->move()) {
                                            return true;
                                       }
                                       return false;
                                   }), aircrafts.end());
}

void AircraftManager::add(Aircraft* aircraft) {
    aircrafts.emplace_back(std::unique_ptr<Aircraft>(aircraft));
}