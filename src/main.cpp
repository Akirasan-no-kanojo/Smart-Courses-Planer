#include "data.h"
#include "ga.h"
#include <iostream>

int main() {

    std::cout << "Loading datasets...\n";

    auto courses = DataLoader::loadCourses(
        "data/full_stack_coursera_courses_with_skills.csv"
    );

    auto skillWeights = DataLoader::loadSkillWeights(
        "data/skill_weights.csv"
    );

    std::cout << "Courses loaded: " << courses.size() << "\n";
    std::cout << "Skills loaded: " << skillWeights.size() << "\n";

    int budget = 40000;
    int timeLimit = 200;

    GeneticAlgorithm ga(courses, skillWeights, budget, timeLimit);

    std::cout << "\nRunning GA optimization...\n";
    ga.run();

    return 0;
}
