#include "FitnessTracker.h"
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
