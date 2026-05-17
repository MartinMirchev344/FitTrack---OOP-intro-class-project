#include "StrengthActivity.h"
#include<sstream>

StrengthActivity::StrengthActivity(const std::string& date, double dur, double cal, const std::string& exerciseName, int sets, int reps)
:Activity(date, dur, cal), exerciseName(exerciseName), sets(sets), reps(reps) {
    if(exerciseName == "")
    {
        throw std::invalid_argument("Exercise name cannot be empty");
    }
    if(sets <= 0 || reps <= 0)
    {
        throw std::invalid_argument("Sets and/or reps cannot be less than 1");
    }
}
int StrengthActivity::getsets() const{ return sets; }
int StrengthActivity::getreps() const{ return reps;}

std::string StrengthActivity::getType() const{ return "Strength"; }
std::string StrengthActivity::describe() const{
    std::ostringstream oss;
    oss << "[Strength] " << date << " | "
    << duration << " min | "
    << calories << " cal | "
    << exerciseName << " "
    << sets << "x" << reps;

    return oss.str();
}

StrengthActivity& StrengthActivity::operator=(const StrengthActivity& other){
    if(this == &other)
    {
        return *this;
    }

    date = other.date;
    duration = other.duration;
    calories = other.calories;
    exerciseName = other.exerciseName;
    sets = other.sets;
    reps = other.reps;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const StrengthActivity& sa){
    out << "[Strentgh] " << sa.date << " | "
    << sa.duration << " min | "
    << sa.calories << " cal | "
    << sa.exerciseName << " "
    << sa.sets << "x" << sa.reps;

    return out;
}

std::istream& operator>>(std::istream& in, StrengthActivity& sa){
    std::string type, date, name;
    double dur, cal, sets, reps;

    if(in >> type >> date >> dur >> cal >> name >> sets >> reps)
    {
        StrengthActivity temp(date, dur, cal, name, sets, reps);
        sa = temp;
    }

    return in;
}