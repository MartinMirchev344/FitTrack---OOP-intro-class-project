#include "FitnessTracker.h"
#include "activities/CardioActivity.h"
#include "activities/StrengthActivity.h"
#include "goals/CalorieGoal.h"
#include "goals/FrequencyGoal.h"
#include <fstream>
#include <stdexcept>

FitnessTracker::FitnessTracker() : currentUser(nullptr) {}

FitnessTracker::~FitnessTracker() {
    for (auto user : users) {
        delete user;
    }
}

void FitnessTracker::registerUser(const std::string& username, const std::string& password,
                                  int age, double weight, double height) {
    for (auto user : users) {
        if (user->getUsername() == username) {
            throw std::invalid_argument("Username is already taken");
        }
    }

    currentUser = new User(username, password, age, weight, height);
    users.push_back(currentUser);
}

bool FitnessTracker::login(const std::string& username, const std::string& password) {
    for (auto user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            currentUser = user;
            return true;
        }
    }

    return false;
}

void FitnessTracker::logout() {
    currentUser = nullptr;
}

User* FitnessTracker::getCurrentUser() const {
    return currentUser;
}

void FitnessTracker::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file for saving");
    }

    for (auto user : users) {
        outFile << "USER " << user->getUsername() << " " << user->getPassword() << " "
                << user->getAge() << " " << user->getWeight() << " " << user->getHeight() << "\n";

        Goal* goal = user->getGoal();
        if (goal == nullptr) {
            outFile << "GOAL NONE\n";
        } else if (goal->getType() == "Calorie") {
            CalorieGoal* calorieGoal = static_cast<CalorieGoal*>(goal);
            outFile << "GOAL CALORIE " << calorieGoal->getTarget() << " "
                    << calorieGoal->getPeriodDays() << "\n";
        } else {
            FrequencyGoal* frequencyGoal = static_cast<FrequencyGoal*>(goal);
            outFile << "GOAL FREQUENCY " << frequencyGoal->getTarget() << " "
                    << frequencyGoal->getPeriodDays() << "\n";
        }

        for (auto activity : user->getActivities()) {
            if (activity->getType() == "Cardio") {
                CardioActivity* cardio = static_cast<CardioActivity*>(activity);
                outFile << "ACTIVITY CARDIO " << cardio->getDate() << " "
                        << cardio->getDuration() << " " << cardio->getCalories() << " "
                        << cardio->getDistance() << "\n";
            } else {
                StrengthActivity* strength = static_cast<StrengthActivity*>(activity);
                outFile << "ACTIVITY STRENGTH " << strength->getDate() << " "
                        << strength->getDuration() << " " << strength->getCalories() << " "
                        << strength->getExerciseName() << " " << strength->getsets() << " "
                        << strength->getreps() << "\n";
            }
        }

        outFile << "END_USER\n";
    }

    outFile.close();
}
