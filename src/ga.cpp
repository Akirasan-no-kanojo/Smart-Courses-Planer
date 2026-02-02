#include "ga.h"
#include <random>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cmath>

static std::mt19937 rng(50);

GeneticAlgorithm::GeneticAlgorithm(
    const std::vector<Course>& c,
    const std::unordered_map<std::string, double>& sw,
    int budget,
    int time
)
    : courses(c), skillWeights(sw),
      budgetLimit(budget), timeLimit(time)
{
    population.resize(populationSize,
        std::vector<int>(courses.size(), 0));

    std::bernoulli_distribution bin(0.15);
    for (auto& ind : population)
        for (int& g : ind)
            g = bin(rng);
}

double GeneticAlgorithm::fitness(const std::vector<int>& ind) {

    int totalTime = 0;
    int totalCost = 0;
    int count = 0;
    double totalRating = 0;

    std::unordered_set<std::string> uniqueSkills;
    double skillReward = 0;
    double overlapPenalty = 0;

    for (size_t i = 0; i < ind.size(); i++) {
        if (ind[i]) {
            totalTime += courses[i].time;
            totalCost += courses[i].cost;
            totalRating += courses[i].rating;
            count++;

            for (auto& sk : courses[i].skills) {
                double w = skillWeights.count(sk)
                               ? skillWeights[sk]
                               : 0.5;

                if (uniqueSkills.count(sk)) {
                    overlapPenalty += 400.0 * w * w; // strong redundancy penalty
                } else {
                    uniqueSkills.insert(sk);
                    skillReward += 100.0 * w * w;
                }
            }
        }
    }

    // Allow slight violation but punish strongly
    double penalty = 0;

    double costRatio = (double)totalCost / budgetLimit;
    double timeRatio = (double)totalTime / timeLimit;

    if (costRatio > 1.15 || timeRatio > 1.15) {
        return -1e12; // too much violation
    }

    if (costRatio > 1.0)
        penalty += 3500.0 * pow(costRatio - 1.0, 2);

    if (timeRatio > 1.0)
        penalty += 3000.0 * pow(timeRatio - 1.0, 2);

    // Reward structure
    double reward =
        40.0 * totalRating +
        20.0 * count +
        skillReward -
        overlapPenalty;

    return reward - penalty;
}

std::vector<int> GeneticAlgorithm::selectParent() {
    std::uniform_int_distribution<int> dist(0, populationSize - 1);

    int a = dist(rng);
    int b = dist(rng);

    return (fitness(population[a]) > fitness(population[b]))
        ? population[a]
        : population[b];
}

std::vector<int> GeneticAlgorithm::crossover(
    const std::vector<int>& p1,
    const std::vector<int>& p2) {

    std::vector<int> child = p1;
    std::uniform_int_distribution<int> cut(0, p1.size() - 1);

    int c = cut(rng);

    for (size_t i = c; i < p1.size(); i++)
        child[i] = p2[i];

    return child;
}

void GeneticAlgorithm::mutate(std::vector<int>& ind) {
    std::uniform_real_distribution<double> prob(0, 1);

    for (int& g : ind)
        if (prob(rng) < mutationRate)
            g = 1 - g;
}

void GeneticAlgorithm::run() {
    //  Fitness per generation
    std::ofstream log("output/fitness_per_generation.csv");
    log << "generation,best_fitness\n";

    std::vector<int> bestOverall;
    double bestFitnessOverall = -1e18;

    for (int gen = 0; gen < generations; gen++) {

        std::vector<std::vector<int>> newPop;

        int bestIdx = 0;
        double bestFit = fitness(population[0]);

        for (int i = 1; i < populationSize; i++) {
            double f = fitness(population[i]);
            if (f > bestFit) {
                bestFit = f;
                bestIdx = i;
            }
        }

        if (bestFit > bestFitnessOverall) {
            bestFitnessOverall = bestFit;
            bestOverall = population[bestIdx];
        }

        newPop.push_back(population[bestIdx]);

        while ((int)newPop.size() < populationSize) {
            auto p1 = selectParent();
            auto p2 = selectParent();
            auto child = crossover(p1, p2);
            mutate(child);
            newPop.push_back(child);
        }

        population = newPop;
        log << gen << "," << bestFitnessOverall << "\n";

        if (gen % 50 == 0)
            std::cout << "Gen " << gen
                      << " Best Fitness = "
                      << bestFitnessOverall << "\n";
    }

    log.close();

    // Selected courses
    std::ofstream out("output/selected_courses.csv");
    out << "Course Name,Duration (h),Price (JPY),Rating,Reviews\n";

    for (size_t i = 0; i < bestOverall.size(); i++) {
        if (bestOverall[i]) {
            out << courses[i].name << ","
                << courses[i].time << ","
                << courses[i].cost << ","
                << courses[i].rating << ","
                << courses[i].reviews << "\n";
        }
    }

    out.close();

    std::cout << "\nDone. Results saved in output/\n";
    // SELECTED COURSE → SKILLS
    std::ofstream skillMapOut("output/selected_course_skills.csv");
    skillMapOut << "Course Name,Skills\n";

    for (size_t i = 0; i < bestOverall.size(); i++) {
        if (bestOverall[i]) {

            skillMapOut << courses[i].name << ",\"";

            // Write all skills in one cell
            for (size_t j = 0; j < courses[i].skills.size(); j++) {
                skillMapOut << courses[i].skills[j];

                if (j < courses[i].skills.size() - 1)
                    skillMapOut << ",";
            }

            skillMapOut << "\"\n";
        }
    }

    skillMapOut.close();

}
