#include "Activity.h"

Activity::Activity(const std::string& date, double dur, double cal): date(date), duration(dur),calories(cal) {
    if(date == "")
    {
        throw std::invalid_argument("Date cannot be empty");
    }
    if(dur <= 0)
    {
        throw std::invalid_argument("Duration must be a positive number");
    }
    if(cal <= 0)
    {
        throw std::invalid_argument("Calories must be a positive number");
    }
}
Activity::~Activity(){}

double Activity::getCalories() const{ return calories; }
int Activity::getDuration() const{ return duration; }
std::string Activity::getDate() const{ return date; }

std::ostream& operator<<(std::ostream& out, const Activity& a){
    out << a.date << "\n" << 
    a.duration << "min\n" <<
    a.calories << "cal\n";
    
    return out;
}
