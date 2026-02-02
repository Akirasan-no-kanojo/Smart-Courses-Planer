#include "data.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::vector<std::string> splitSkills(const std::string& s) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string token;

    while (std::getline(ss, token, ',')) {
        if (!token.empty())
            result.push_back(token);
    }
    return result;
}

std::vector<Course> DataLoader::loadCourses(const std::string& filename) {
    std::vector<Course> courses;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open course file: " << filename << "\n";
        return courses;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        Course c;
        std::string duration, price, rating, reviews, skills;

        std::getline(ss, c.name, ',');
        std::getline(ss, duration, ',');
        std::getline(ss, price, ',');
        std::getline(ss, rating, ',');
        std::getline(ss, reviews, ',');
        std::getline(ss, skills);

        c.time = std::stoi(duration);
        c.cost = std::stoi(price);
        c.rating = std::stod(rating);
        c.reviews = std::stoi(reviews);

        // Remove quotes
        if (!skills.empty() && skills.front() == '"')
            skills = skills.substr(1, skills.size() - 2);

        c.skills = splitSkills(skills);

        courses.push_back(c);
    }

    return courses;
}

std::unordered_map<std::string, double>
DataLoader::loadSkillWeights(const std::string& filename) {

    std::unordered_map<std::string, double> weights;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open skill weight file: " << filename << "\n";
        return weights;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string skill, weight, category;
        std::getline(ss, skill, ',');
        std::getline(ss, weight, ',');
        std::getline(ss, category);

        if (!skill.empty()) {
            weights[skill] = std::stod(weight);
        }
    }

    return weights;
}
