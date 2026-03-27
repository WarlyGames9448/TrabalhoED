#pragma once

#include <string>
#include "ReservationRequest.hpp"

struct Room {
    // Guarda os ID dos cursos (0 = horário disponível)
    int horarios[5][14] = {{0}};
};

class ReservationSystem {
  private:
    // numero de salas
    int room_count;
    // capacidade de cada sala
    int* room_capacities;
    // salas com os dias das semana e horários
    Room* rooms;

    // ID = posição do curso no array + 1
    int course_count = 0;
    std::string* course_names = nullptr;

    // Para auxiliar no print
    const std::string weekdayName[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};

  public:
    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    void addCourse(std::string course_name);

  private:
    int getCourseNameID(std::string course_name);
    int weekdayToInt(std::string weekday);
};
