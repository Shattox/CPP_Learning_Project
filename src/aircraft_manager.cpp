#include "aircraft_manager.hpp"

void AircraftManager::move() {
    for (auto it = move_queue.begin(); it != move_queue.end(); it++) {
        if (!(*it)->move()) {
            auto aircraft = (*it);
            it = move_queue.erase(it);
            delete (aircraft);
        }
    }
}

void AircraftManager::add(const Aircraft& aircraft) {
    aircrafts.emplace_back(aircraft);
}