#include "User.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::time_t parseDate(const std::string& date) {
    std::tm parsedDate = {};
    std::istringstream dateStream(date);
    dateStream >> std::get_time(&parsedDate, "%Y-%m-%d");

    if (dateStream.fail() || !dateStream.eof()) {
        throw std::invalid_argument("Date must use the YYYY-MM-DD format");
    }

    parsedDate.tm_isdst = -1;
    return std::mktime(&parsedDate);
}

std::time_t startOfToday() {
    std::time_t now = std::time(nullptr);
    std::tm today = *std::localtime(&now);
    today.tm_hour = 0;
    today.tm_min = 0;
    today.tm_sec = 0;
    today.tm_isdst = -1;
    return std::mktime(&today);
}

bool isWithinLastDays(const Activity* activity, int days) {
    const double secondsPerDay = 24 * 60 * 60;
    const double ageInDays = std::difftime(startOfToday(), parseDate(activity->getDate())) / secondsPerDay;
    return ageInDays >= 0 && ageInDays < days;
}
}

User::User(const std::string& username, const std::string& password, int age, double weight, double height)
    : username(username), password(password), age(age), weight(weight), height(height), goal(nullptr) {
    if (username.empty()) {
        throw std::invalid_argument("Username cannot be empty");
    }
    if (password.empty()) {
        throw std::invalid_argument("Password cannot be empty");
    }
    if (age <= 0 || weight <= 0 || height <= 0) {
        throw std::invalid_argument("Age, weight and height must be positive numbers");
    }
}
User::~User() {
    for (auto activity : activities) {
        delete activity;
    }
    delete goal;
}

void User::addActivity(Activity* a) {
    activities.push_back(a);
}

void User::printHistory() const {
    for(auto a : activities){
        std::cout << *a << "\n";
    }
}

void User::printStats() const {
    double totalCal = 0, totalDur = 0;

    if (activities.size() == 0) {
        std::cout << "No activities yet.\n";
        return;
    }

    for(auto a : activities){
        totalCal += a->getCalories();
        totalDur += a->getDuration();
    }

    std::cout << "Total calories: " << totalCal << " cal\n"
    << "Number of activities(training sessions): " << activities.size() << "\n"
    << "Average duration: " << totalDur/activities.size();
}

double User::getTotalCaloriesForLastDays(int days) const {
    if (days <= 0) {
        throw std::invalid_argument("Period must be a positive number of days");
    }

    double totalCalories = 0;
    for (auto activity : activities) {
        if (isWithinLastDays(activity, days)) {
            totalCalories += activity->getCalories();
        }
    }
    return totalCalories;
}

int User::getActivityCountForLastDays(int days) const {
    if (days <= 0) {
        throw std::invalid_argument("Period must be a positive number of days");
    }

    int activityCount = 0;
    for (auto activity : activities) {
        if (isWithinLastDays(activity, days)) {
            activityCount++;
        }
    }
    return activityCount;
}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
int User::getAge() const { return age; }
double User::getWeight() const { return weight; }
double User::getHeight() const { return height; }

void User::setGoal(Goal* g) {
    delete goal;
    goal = g;
}
