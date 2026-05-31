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
    std::vector<Activity*> sortedActivities = activities;

    for (size_t i = 0; i < sortedActivities.size(); i++) {
        for (size_t j = i + 1; j < sortedActivities.size(); j++) {
            if (sortedActivities[i]->getDate() > sortedActivities[j]->getDate()) {
                Activity* temp = sortedActivities[i];
                sortedActivities[i] = sortedActivities[j];
                sortedActivities[j] = temp;
            }
        }
    }

    for(auto activity : sortedActivities){
        std::cout << *activity << "\n";
    }
}

void User::printStats(int days) const {
    if (days <= 0) {
        throw std::invalid_argument("Period must be a positive number of days");
    }

    double totalCal = 0, totalDur = 0;
    int activityCount = 0;

    for(auto activity : activities){
        if (isWithinLastDays(activity, days)) {
            totalCal += activity->getCalories();
            totalDur += activity->getDuration();
            activityCount++;
        }
    }

    if (activityCount == 0) {
        std::cout << "No activities for this period.\n";
        return;
    }

    std::cout << "Total calories: " << totalCal << " cal\n"
    << "Number of activities(training sessions): " << activityCount << "\n"
    << "Average duration: " << totalDur/activityCount << "\n";
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
const std::vector<Activity*>& User::getActivities() const { return activities; }
Goal* User::getGoal() const { return goal; }

void User::setGoal(Goal* g) {
    delete goal;
    goal = g;
}

bool User::hasGoal() const {
    return goal != nullptr;
}

bool User::checkGoal() const {
    if (!hasGoal()) {
        return false;
    }
    return goal->isAchieved(this);
}

void User::printGoalProgress() const {
    if (!hasGoal()) {
        std::cout << "No goal set.\n";
        return;
    }

    std::cout << goal->describe() << "\n";
    if (checkGoal()) {
        std::cout << "Goal achieved.\n";
    } else {
        std::cout << "Goal not achieved yet.\n";
    }
}
