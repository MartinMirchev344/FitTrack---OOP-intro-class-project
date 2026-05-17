#include "User.h"

User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}
User::~User() {
    for (int i = 0; i < activities.size(); i++)
    delete activities[i];
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

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }