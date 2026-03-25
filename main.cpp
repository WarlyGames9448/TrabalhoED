#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

int main() {
    int capacities[3] = {30, 50, 80};

    ReservationSystem system(3, capacities);
    system.printSchedule();
    return 0;
}
