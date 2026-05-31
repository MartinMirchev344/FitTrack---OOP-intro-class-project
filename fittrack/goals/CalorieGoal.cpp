#include "CalorieGoal.h"
#include "../User.h"
#include <sstream>
#include <stdexcept>

CalorieGoal::CalorieGoal(double targetCalories, int periodDays)
    : Goal(targetCalories, "Calorie goal"), periodDays(periodDays) {
    if (periodDays <= 0) {
        throw std::invalid_argument("Goal period must be a positive number of days");
    }
}

bool CalorieGoal::isAchieved(const User* user) const {
    return user->getTotalCaloriesForLastDays(periodDays) >= targetValue;
}

std::string CalorieGoal::describe() const {
    std::ostringstream output;
    output << description << ": burn " << targetValue
           << " calories in " << periodDays << " days";
    return output.str();
}
