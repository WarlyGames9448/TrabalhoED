#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
#include <iostream>

int main() {
    int capacities[3] = {30, 50, 80};

    ReservationSystem system(3, capacities);

    system.addCourse("Data Structures");
    system.addCourse("Calculus");
    system.addCourse("Linear Algebra");

    // fazer uma reserva direto
    system.reserve((ReservationRequest){"Data Structures", "segunda", 7, 9, 10});
    system.reserve((ReservationRequest){"Calculus", "segunda", 8, 11, 10});
    system.reserve((ReservationRequest){"Linear Algebra", "quarta", 10, 12, 10});

    system.printSchedule();

    std::cout << "Fim do programa, aperte Ctrl + C para finalizar." << std::endl;
    while (true) {
    }
}
