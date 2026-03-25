#pragma once

#include <string>

class ReservationRequest {

  private:
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;

  public:
    ReservationRequest(std::string course_name, std::string weekday, int start_hour, int end_hour, int student_count);
    ~ReservationRequest();

    inline int getStartHour() { return start_hour; }

    inline int getEndHour() { return end_hour; }

    inline std::string getCourseName() { return course_name; }

    inline std::string getWeekday() { return weekday; }

    inline int getStudentCount() { return student_count; }
};
