#include "Activity.h"
#include <iomanip>
#include <sstream>

Activity::Activity(const std::string& date, double dur, double cal): date(date), duration(dur),calories(cal) {
    std::tm parsedDate = {};
    std::istringstream dateStream(date);
    dateStream >> std::get_time(&parsedDate, "%Y-%m-%d");
    if(date.empty() || dateStream.fail() || !dateStream.eof())
    {
        throw std::invalid_argument("Date must use the YYYY-MM-DD format");
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
double Activity::getDuration() const{ return duration; }
std::string Activity::getDate() const{ return date; }

std::ostream& operator<<(std::ostream& out, const Activity& a){
    out << a.describe();
    return out;
}
