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

ReservationSystem::~ReservationSystem() {
    delete[] this->room_capacities;
    delete[] this->rooms;
    delete[] this->course_names;
}

int ReservationSystem::weekdayToInt(std::string weekday) {
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

        for (int hour = start_hour; hour < end_hour; hour++) {
            // Se a sala no dia e no horário não estiver disponível, passe para a próxima sala.
            if (rooms[i].horarios[day][hour - 7] != 0) {
                is_disponible = false;
                break;
            }
        }

        // Se existir sala, aloque o curso.
        if (is_disponible) {
            int id = getCourseNameID(request.getCourseName());
            for (int hour = start_hour; hour < end_hour; hour++) {
                rooms[i].horarios[day][hour - 7] = id;
            }
            return true;
        }
    }

    // Se não encontrar nenhuma sala no for
    return false;
}

int ReservationSystem::getCourseNameID(std::string course_name) {
    for (int id = 0; id < course_count; id++) {
        if (course_name == course_names[id])
            return id + 1;
    }
    std::cerr << "Não existe curso com esse nome." << std::endl;
    return 0;
}

// TODO: Fazer com que aloque o dobro do tamanho ao invés de 1

// Aumenta o tamanho do array
void ReservationSystem::addCourse(std::string course_name) {
    // copia para um novo array
    int lenght = this->course_count;
    std::string* new_course_names = new std::string[lenght + 1];

    for (int i = 0; i < lenght; i++) {
        new_course_names[i] = this->course_names[i];
    }
    new_course_names[lenght] = course_name;

    // deleta o antigo e aponta para o novo
    delete[] this->course_names;

    this->course_names = new_course_names;
    this->course_count++;
}

bool ReservationSystem::cancel(std::string course_name) {
    int id = getCourseNameID(course_name);
    if(id == 0){
        return false;
    }
    bool found = false;
    for(int r = 0; r < this->room_count; r++){
        for(int d =0; d < 5; d++){
            for(int h = 0; h <14; h++){
                if(this->rooms[r].horarios[d][h] == id){
                    rooms[r].horarios[d][h] = 0;
                    found = true;
                }
            }
        }
    }
    
    return found;
}

// TODO: Explicar melhor a função abaixo
// TODO: implementar que não printe o dia da semana e a sala que não há horários marcados

void ReservationSystem::printSchedule() {

    for (int room = 1; room <= this->room_count; room++) {
        std::cout << "Room " << room << std::endl;

        for (int day = 0; day < 5; day++) {
            std::cout << weekdayName[day] << ":" << std::endl;

            int id = 0, new_id = 0;
            int start_hour = 0;
            for (int hour = 0; hour < 14; hour++) {

                new_id = this->rooms[room - 1].horarios[day][hour];
                // printa ao percorrer uma sequencia consecutiva de id iguais
                if (new_id != id) {
                    // se a sequencia não é vazia, há um horário marcado.
                    if (id != 0) {
                        std::cout << start_hour + 7 << "h~" << hour + 7 << "h: " << this->course_names[id - 1] << std::endl;
                    }

                    id = new_id;
                    start_hour = hour;
                }
            }
            // Se houver id no ultimo horário
            if (id != 0) {
                std::cout << start_hour + 7 << "h~21h: " << this->course_names[id - 1] << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
