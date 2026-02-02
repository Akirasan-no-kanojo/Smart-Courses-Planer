#ifndef GA_H
#define GA_H

#include "data.h"
#include <vector>
#include <unordered_map>

class GeneticAlgorithm {
private:
    std::vector<Course> courses;
    std::unordered_map<std::string, double> skillWeights;

    std::vector<std::vector<int>> population;

    int populationSize = 100;
    int generations = 300;
    double mutationRate = 0.02;

    int budgetLimit;
    int timeLimit;

public:
    GeneticAlgorithm(
        const std::vector<Course>& c,
        const std::unordered_map<std::string, double>& sw,
        int budget,
        int time
    );

    double fitness(const std::vector<int>& ind);

    std::vector<int> selectParent();
    std::vector<int> crossover(
        const std::vector<int>& p1,
        const std::vector<int>& p2
    );
    void mutate(std::vector<int>& ind);

    void run();
};

#endif
