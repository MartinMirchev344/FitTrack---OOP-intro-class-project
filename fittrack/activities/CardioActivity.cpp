#include "CardioActivity.h"
#include<sstream>

CardioActivity:: CardioActivity(const std::string& date, double dur, double cal, double dist)
: Activity(date, dur, cal), distance(dist) {
    if(dist <= 0)
    {
        throw std::invalid_argument("Distance must be a positive number");
    }
}
double CardioActivity::getDistance() const{ return distance; }
std::string CardioActivity::getType() const{
    return "Cardio";
}
std::string CardioActivity::describe() const{
    std::ostringstream oss;
    oss << "[Cardio] " << date << " | "
    << duration << " min | "
    << calories << " cal | "
    << distance << " km";

    return oss.str();
}

CardioActivity& CardioActivity::operator=(const CardioActivity& other){
    if(this == &other)
    {
        return *this;
    }

    date = other.date;
    duration = other.duration;
    calories = other.calories;
    distance = other.distance;

    return *this;
}

std::istream& operator>>(std::istream& in, CardioActivity& ca){
    std::string type, date;
    double dur, cal, dist;

    if(in >> type >> date >> dur >> cal >> dist)
    {
        CardioActivity temp(date, dur, cal, dist);
        ca = temp;
    }

    return in;
}
