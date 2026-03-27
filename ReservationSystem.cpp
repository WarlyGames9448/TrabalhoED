#include "ReservationSystem.hpp"

#include <iostream>

ReservationSystem::ReservationSystem(int room_count, int* room_capacities_extern) {
    // recebe o valor para saber o limite de salas:
    this->room_count = room_count;
    // alocação dinâmica em um ponteiro para capacidade de cada sala:
    this->room_capacities = new int[this->room_count];

    for (int i = 0; i < this->room_count; i++) {
        this->room_capacities[i] = room_capacities_extern[i];
    }

    this->room = new Room[this->room_count];
}

// TODO

ReservationSystem::~ReservationSystem() {
    delete[] this->room_capacities;
    delete[] this->room;
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
