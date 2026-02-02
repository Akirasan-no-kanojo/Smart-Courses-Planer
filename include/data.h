#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <unordered_map>

struct Course {
    std::string name;
    int time;
    int cost;
    double rating;
    int reviews;

    std::vector<std::string> skills;
};

class DataLoader {
public:
    static std::vector<Course> loadCourses(const std::string& filename);

    static std::unordered_map<std::string, double>
    loadSkillWeights(const std::string& filename);
};

#endif
