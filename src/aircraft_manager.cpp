#include "aircraft_manager.hpp"

void AircraftManager::move() {
    for (auto it = aircrafts.begin(); it != aircrafts.end(); ) {
        if (!(*it)->move()) {
            it = aircrafts.erase(it);
        } else {
            it++;
        }
    }
}

void AircraftManager::add(Aircraft* aircraft) {
    aircrafts.emplace_back(std::unique_ptr<Aircraft>(aircraft));
}