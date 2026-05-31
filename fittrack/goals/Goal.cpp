#include "Goal.h"
#include <stdexcept>

Goal::Goal(double targetValue, const std::string& description)
    : targetValue(targetValue), description(description) {
    if (targetValue <= 0) {
        throw std::invalid_argument("Goal target must be a positive number");
    }
}

Goal::~Goal() {}

double Goal::getTarget() const { return targetValue; }
