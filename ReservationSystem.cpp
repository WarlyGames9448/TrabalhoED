#include "ReservationSystem.hpp"

#include <iostream>

ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;
    this->room_capacities = room_capacities;

    // Outros Parâmetros
}

// TODO

ReservationSystem::~ReservationSystem() {
}

bool ReservationSystem::reserve(ReservationRequest request) {
    return true;
}

bool ReservationSystem::cancel(std::string course_name) {

    return true;
}

void ReservationSystem::printSchedule() {
    std::cout << "Hello World!" << std::endl;
}
