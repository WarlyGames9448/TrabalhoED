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
}

// TODO

ReservationSystem::~ReservationSystem() {
    delete[] room_capacities;
}

int weekdayToInt(std::string weekday) {
    if (weekday == "segunda")
        return 0;
    if (weekday == "terca")
        return 1;
    if (weekday == "quarta")
        return 2;
    if (weekday == "quinta")
        return 3;
    if (weekday == "sexta")
        return 4;

    std::cerr << "Dia da Semana inválida" << std::endl;
    return -1;
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
