#pragma once

#include <string>
#include "ReservationRequest.hpp"

struct Room {
    // Guarda os IDs dos cursos (0 = horário disponível)
    // [5] representa os dias da semana (0=segunda, ..., 4=sexta)
    // [14] representa os horários das 7h às 21h (0 = 7h~8h, 13 = 20h~21h)
    int horarios[5][14] = {{0}};
};

class ReservationSystem {
  private:
    int room_count;
    int* room_capacities;
    Room* rooms;

    // course_count rastreia quantos cursos existem.
    // course_array_length rastreia o tamanho atual do array alocado na memória.
    // O ID de um curso é sempre o seu índice no array + 1 (para o 0 representar "vazio").
    int course_count = 0, course_array_length = 0;
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
