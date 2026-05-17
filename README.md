# FitTrack 🏋️

OOP Project, 10th grade — TUES at TU-Sofia

A console-based fitness tracking system written in C++.

---

## Description

FitTrack lets users register profiles, log workouts (cardio and strength), track burned calories, and set fitness goals. Data is saved to a text file and loaded on the next run.

---

## Features

- ✅ User registration with input validation
- ✅ Add workouts — cardio and strength
- ✅ View full workout history
- ✅ Statistics — total calories, workout count, average duration
- ✅ Set and track goals (CalorieGoal / FrequencyGoal)
- ✅ Save and load data from file
- ✅ `operator<<` for printing workouts
- ✅ Exceptions on invalid input

---

## Project Structure

```
fittrack/
├── activities/
│   ├── Activity.h / .cpp          # abstract base class
│   ├── CardioActivity.h / .cpp    # extends Activity
│   └── StrengthActivity.h / .cpp  # extends Activity
├── goals/
│   ├── Goal.h / .cpp              # abstract base class
│   ├── CalorieGoal.h / .cpp       # extends Goal
│   └── FrequencyGoal.h / .cpp     # extends Goal
├── User.h / .cpp                  # manages workouts and goal
├── FitnessTracker.h / .cpp        # main system, file I/O
├── main.cpp                       # console menu
└── data.txt                       # sample saved data
```

---

## Build & Run

```bash
g++ -std=c++17 -o fittrack *.cpp
./fittrack
```

---

## Class Hierarchy

```
Activity  (abstract)
├── CardioActivity
└── StrengthActivity

Goal  (abstract)
├── CalorieGoal
└── FrequencyGoal

User  <>── Activity*[]   (composition)
      <>── Goal*         (composition)

FitnessTracker  <>── User*[]  (composition)
```