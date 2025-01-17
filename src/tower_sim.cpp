#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    context_initializer { ContextInitializer(argc, argv) },
    aircraft_factory { new AircraftFactory }
{
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft() const
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    auto aircraft = aircraft_factory->create_random_aircraft(*airport);

    aircraft_manager->add(std::move(aircraft));
}

void TowerSimulation::create_keystrokes() const
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('m', []() { GL::ticks_per_sec++; });
    GL::keystrokes.emplace('l', []() { GL::ticks_per_sec--; });
    GL::keystrokes.emplace('p',
                           []()
                           {
                               GL::pause = !GL::pause;
                               GL::timer(0);
                           });
    for (int i = 0; i < 8; i++)
    {
        GL::keystrokes.emplace('0' + i, [this, i]() { aircraft_factory->count_airline_aircrafts(i); });
    }
    GL::keystrokes.emplace('k',
                           [this]() {
                               std::cout << "Number of aircraft crashed : "
                                         << aircraft_manager->get_aircraft_crashed() << std::endl;
                           });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, *aircraft_manager };
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraft_manager()
{
    aircraft_manager = new AircraftManager();

    GL::move_queue.emplace(aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_aircraft_manager();
    init_airport();

    GL::loop();
}
