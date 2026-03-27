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

    this->rooms = new Room[this->room_count];
}

// TODO

ReservationSystem::~ReservationSystem() {
    delete[] this->room_capacities;
    delete[] this->rooms;
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
    int day = weekdayToInt(request.getWeekday());
    int start_hour = request.getStartHour();
    int end_hour = request.getEndHour();

    bool is_disponible;

    for (int i = 0; i < this->room_count; i++) {
        is_disponible = true;

        // Se a capacidade da sala for menor, vá para a próxima sala
        if (room_capacities[i] < request.getStudentCount())
            continue;

        for (int hora = start_hour; hora < end_hour; hora++) {
            // Se a sala no dia e no horário não estiver disponível, passe para a próxima sala.
            if (rooms[i].horarios[day][start_hour - 7] != "\0") {
                is_disponible = false;
                break;
            }
        }

        // Se existir sala, aloque o curso.
        if (is_disponible) {
            for (int hora = start_hour; hora < end_hour; hora++) {
                rooms[i].horarios[day][hora] = request.getCourseName();
            }
            return true;
        }
    }

    // Se não encontrar nenhuma sala no for
    return false;
}

bool ReservationSystem::cancel(std::string course_name) {

    return true;
}

void ReservationSystem::printSchedule() {
    std::cout << "Hello World!" << std::endl;
}
