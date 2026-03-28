#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
#include <iostream>

int main() {

    std::cout << "Olá, deseja entrar no modo demonstração? (exibe o exemplo do trabalho) Não (0) ou Sim (1)?";
    bool demo;
    std::cin >> demo;

    if (demo) {
        int capacities[3] = {30, 50, 80};

        ReservationSystem system(3, capacities);

        system.addCourse("Data Structures");
        system.addCourse("Calculus");
        system.addCourse("Linear Algebra");

        system.reserve((ReservationRequest){"Data Structures", "segunda", 7, 9, 10});
        system.reserve((ReservationRequest){"Calculus", "segunda", 9, 12, 10});
        system.reserve((ReservationRequest){"Linear Algebra", "quarta", 9, 12, 10});

        system.printSchedule();
    } else {
        std::cout << "Digite o número de salas: ";
        int room_count;
        std::cin >> room_count;
        std::cout << "Digite a capacidade dos alunos de cada sala: ";

        int* capacities = new int[room_count];
        int number;
        for (int i = 0; i < room_count; i++) {
            std::cin >> number;
            capacities[i] = number;
        }

        ReservationSystem system(room_count, capacities);

        while (true) {

            int escolha;
            std::cout << "Bem vindo ao sistema de reservas de sala, o que gostaria de fazer?" << std::endl;
            std::cout << "(1) Cadastrar disciplina" << std::endl;
            std::cout << "(2) Reservar Sala" << std::endl;
            std::cout << "(3) Exibir grade horária" << std::endl;
            std::cout << "(0) Sair" << std::endl;

            std::cin >> escolha;

            switch (escolha) {
            case 0:
                //finaliza programa
                return 0;
            case 1: {
                std::string course_name;
                std::cout << "Nome da disciplina: ";
                std::cin.ignore();
                std::getline(std::cin, course_name);

                system.addCourse(course_name);
                std::cout << "Disciplina Cadastrada!" << std::endl;
                break;
            }
            case 2: {
                std::string course_name;
                std::string weekday;
                int start_hour;
                int end_hour;
                int student_count;

                std::cout << "Nome da disciplina: ";
                std::cin.ignore(1000, '\n');
                std::getline(std::cin, course_name);
                std::cout << "Dia da semana: ";
                std::cin.ignore(1000, '\n');
                std::getline(std::cin, weekday);
                std::cout << "Horário de início | Horário de términio | Quantidade de alunos: ";
                std::cin >> start_hour >> end_hour >>student_count;

                bool status = system.reserve({course_name, weekday, start_hour, end_hour, start_hour});

                if(status) std::cout << "Reserva realizada com sucesso " << std::endl;
                else std::cout << "Não foi possível realizar uma reserva " << std::endl;

                break;
            }
            case 3: {
                system.printSchedule();
                break;
            }
            }
        }
    }
}
