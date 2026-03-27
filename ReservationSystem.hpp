#pragma once

#include <string>
#include "ReservationRequest.hpp"

struct Room {
    // 70 bits por sala (o mínimo nescessário)
    bool horarios[5][14];

    Room();
    ~Room();
};

class ReservationSystem {
  private:
    // numero de salas
    int room_count;
    // capacidade de cada sala
    int* room_capacities;
    // salas com os dias das semana e horários
    Room* rooms;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

  public:
    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    int weekdayToInt(std::string weekday);
    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};
