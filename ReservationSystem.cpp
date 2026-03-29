#include "ReservationSystem.hpp"

#include <iostream>

ReservationSystem::ReservationSystem(int room_count, int* room_capacities_extern) {
    this->room_count = room_count;
    // Alocação dinâmica em um ponteiro para capacidade de cada sala
    this->room_capacities = new int[this->room_count];

    for (int i = 0; i < this->room_count; i++) {
        this->room_capacities[i] = room_capacities_extern[i];
    }

    this->rooms = new Room[this->room_count];
}

ReservationSystem::~ReservationSystem() {
    // É vital deletar tudo que foi alocado com 'new' para evitar vazamento de memória
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
    if (day == -1)
        return false;
    int start_hour = request.getStartHour();
    int end_hour = request.getEndHour();

    bool is_disponible;

    for (int i = 0; i < this->room_count; i++) {
        is_disponible = true;

        // Se a capacidade da sala for menor que a solicitada, vá para a próxima sala
        if (room_capacities[i] < request.getStudentCount())
            continue;

        for (int hour = start_hour; hour < end_hour; hour++) {
            // (hour - 7) ajusta a hora real para o índice do array. Ex: 7h vira índice 0, 8h vira índice 1.
            // Se diferente de 0, significa que já há um curso alocado neste horário.
            if (rooms[i].horarios[day][hour - 7] != 0) {
                is_disponible = false;
                break;
            }
        }

        // Se encontrou sala disponível e do tamanho certo, efetua a reserva
        if (is_disponible) {
            int id = getCourseNameID(request.getCourseName());
            if (id == 0)
                return false; // Impede reserva se a disciplina não estiver cadastrada

            for (int hour = start_hour; hour < end_hour; hour++) {
                rooms[i].horarios[day][hour - 7] = id;
            }
            return true;
        }
    }

    // Se varreu todas as salas e não encontrou espaço, a reserva falha
    return false;
}

int ReservationSystem::getCourseNameID(std::string course_name) {
    for (int id = 0; id < course_count; id++) {
        if (course_name == course_names[id])
            return id + 1; // +1 porque o ID 0 é reservado para "horário livre"
    }
    std::cerr << "Não existe curso com esse nome." << std::endl;
    return 0;
}

void ReservationSystem::addCourse(std::string course_name) {
    int length = this->course_count;

    // Lógica de redimensionamento de array dinâmico (similar a como um std::vector funciona por baixo dos panos)
    // Se não houver mais espaço para alocar, crie um array com o dobro do tamanho
    if (length >= this->course_array_length) {
        // Aloca um novo array maior. Fórmula 2*(length+1) garante crescimento mesmo se length for 0
        std::string* new_course_names = new std::string[2 * (length + 1)];

        // Copia os dados antigos para o novo espaço de memória
        for (int i = 0; i < length; i++) {
            new_course_names[i] = this->course_names[i];
        }

        // Libera a memória do array antigo e aponta o ponteiro para o novo array
        delete[] this->course_names;
        this->course_names = new_course_names;
        this->course_array_length = 2 * (length + 1);
    }

    // Adiciona o novo curso e incrementa o contador
    this->course_names[length] = course_name;
    this->course_count++;
}

bool ReservationSystem::cancel(std::string course_name) {
    int id = getCourseNameID(course_name);
    if (id == 0)
        return false; // Curso não existe

    bool found = false;
    // Varre todas as salas, todos os dias e todos os horários procurando o ID para limpar (setar para 0)
    for (int r = 0; r < this->room_count; r++) {
        for (int d = 0; d < 5; d++) {
            for (int h = 0; h < 14; h++) {
                if (this->rooms[r].horarios[d][h] == id) {
                    rooms[r].horarios[d][h] = 0;
                    found = true;
                }
            }
        }
    }

    return found;
}

void ReservationSystem::printSchedule() {
    for (int room = 1; room <= this->room_count; room++) {
        bool value_found_room = false;

        // 1º Passo: Checa se a sala tem QUALQUER reserva durante a semana toda.
        // Se estiver totalmente vazia, pula para a próxima sala (não imprime nada).
        for (int day = 0; day < 5; day++) {
            for (int h = 0; h < 14; h++) {
                if (this->rooms[room - 1].horarios[day][h] != 0) {
                    value_found_room = true;
                    break;
                }
            }
            if (value_found_room)
                break;
        }

        if (!value_found_room)
            continue; // Pula a sala vazia

        std::cout << "Room " << room << std::endl;

        for (int day = 0; day < 5; day++) {
            bool value_found_day = false;

            // 2º Passo: Checa se há alguma reserva neste dia específico.
            for (int h = 0; h < 14; h++) {
                if (this->rooms[room - 1].horarios[day][h] != 0) {
                    value_found_day = true;
                    break;
                }
            }

            if (value_found_day) {
                std::cout << weekdayName[day] << ":" << std::endl;

                // 3º Passo: Agrupa os blocos contínuos da mesma disciplina.
                int id_atual = 0;
                int start_hour = 0;

                for (int h = 0; h < 14; h++) {
                    int id_na_matriz = this->rooms[room - 1].horarios[day][h];

                    // Se o ID mudou (ex: passou de livre para ocupado, ou trocou de disciplina)
                    if (id_na_matriz != id_atual) {
                        // Se o bloco anterior não era livre (0), imprime o bloco que acabou de terminar
                        if (id_atual != 0) {
                            std::cout << start_hour + 7 << "h~" << h + 7 << "h: " << this->course_names[id_atual - 1] << std::endl;
                        }

                        // Atualiza o rastreador para a nova disciplina (ou horário livre) e marca a hora de início
                        id_atual = id_na_matriz;
                        start_hour = h;
                    }
                }

                // Trata o caso especial em que a última aula do dia vai até as 21h (fim do array)
                if (id_atual != 0) {
                    std::cout << start_hour + 7 << "h~21h: " << this->course_names[id_atual - 1] << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}
