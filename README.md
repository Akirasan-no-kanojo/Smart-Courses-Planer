# SmartCoursePlanner 📚

**Optimizing Full-Stack Learning Paths under Time and Budget Constraints**

SmartCourseGA is a logic-driven optimization system designed to solve the **“Course Selection Overload”** problem faced by self-learners in Full-Stack Development.

Instead of manually choosing courses based on intuition, this project uses a **Genetic Algorithm (GA)** to automatically select an optimal subset of courses under **real-world constraints** such as time and budget, while maximizing overall learning quality.

---

## 📖 Overview

With hundreds of online courses available, learners often struggle to decide:
- Which courses are *worth taking*
- How to stay within a **limited budget**
- How to fit learning into a **realistic time frame**

SmartCourseGA reframes this as an **optimization problem**:

> *Select the best combination of courses that maximizes learning value while respecting time and cost constraints.*

The system emphasizes **algorithmic reasoning**, **constraint handling**, and **explainable decision-making** rather than black-box recommendations.

---

## 🚀 How It Works (Core Logic)

Each course is represented as a structured data entity:


A **candidate solution (chromosome)** is a binary vector:

Course = {
  Course Name,
  Duration (hours),
  Price (JPY),
  Rating,
  Reviews,
  Skills
}

A candidate solution (chromosome) is encoded as a binary vector:
X = [x₁, x₂, ..., xₙ],   xᵢ ∈ {0, 1}

- 1 → the course is selected

- 0 → the course is not selected

The Genetic Algorithm evolves a population of such vectors to find an optimal course set.

# 🧠 Fitness Function Design

This project uses a skill-aware fitness function to generate an optimal and realistic learning roadmap using a Genetic Algorithm (GA).  
The design balances course quality, skill diversity, budget, and time constraints.

---

## 🎯 Objective (Reward)

The reward component encourages the algorithm to select learning paths that are both **high-quality** and **skill-diverse**.

The fitness function rewards:

- **High-quality courses**  
  Courses with higher ratings contribute more to the overall fitness score.

- **Balanced number of selected courses**  
  Selecting multiple courses helps expand knowledge coverage while avoiding unnecessary overload.

- **Skill diversity with prioritization**  
  Each newly introduced skill increases fitness based on its predefined **skill weight**, allowing important or in-demand skills to be emphasized.

This ensures that recommended learning paths are not only well-rated, but also aligned with the intended Full-Stack skill roadmap.

---

## ⚙️ Constraint Handling Strategy

To ensure that generated solutions are **realistic, feasible, and meaningful**, the system applies a two-layer constraint handling mechanism:

- **Hard Constraints** for strict feasibility
- **Soft Penalties** for smooth optimization near constraint boundaries

---

## 🚫 Hard Constraints (Strict Feasibility Filter)

Any candidate solution is immediately discarded if it violates essential real-world limitations:

- Total learning duration exceeds the allowed time limit  
- Total course cost exceeds the allocated budget  

### Purpose

Hard constraints ensure that all surviving solutions are **practically usable**, preventing the algorithm from favoring high-scoring but unrealistic course combinations.

---

## ⚖️ Soft Penalties (Boundary-Aware Optimization)

For solutions that approach (but do not exceed) the constraints, soft penalties are applied:

- Penalties for slight time overflow  
- Penalties for slight budget overflow  

These penalties:

- Discourage inefficient use of time and financial resources  
- Preserve smooth optimization behavior for the GA  
- Prevent abrupt fitness drops near constraint boundaries

---

## 🎓 Skill-Aware Optimization

To avoid redundant learning and promote efficiency, the fitness function explicitly models **skills and their importance**.

### Key Mechanisms

- **Skill weights**  
  Represent the relative importance of each skill in the learning roadmap.

- **Reward for new skills**  
  Introducing a previously unseen skill increases fitness, encouraging broader skill coverage.

- **Penalty for skill overlap**  
  Repeated skills across multiple courses are penalized to avoid redundancy and wasted learning effort.

### Purpose

This design encourages the algorithm to select courses that:

- Cover a **wide and diverse set of skills**
- Focus on **high-priority skills**
- Minimize unnecessary repetition

As a result, the generated learning path is **efficient, diverse, and goal-oriented**.

---

## ✅ Summary

The fitness function is designed to balance:

- Course quality  
- Skill diversity and importance  
- Budget and time feasibility  

This enables the Genetic Algorithm to generate learning recommendations that are both **optimal and realistic**.

---

## 📈 Effect on Optimization

This design allows the Genetic Algorithm to:

- Explore the solution space efficiently

- Gradually converge toward balanced trade-offs

Avoid extreme or degenerate solutions

## 💡 Key Engineering Decisions

1. Binary Encoding for Interpretability

- Each gene directly corresponds to a real course

- Easy to debug, visualize, and export

- Highly explainable in presentations

2. Two-Layer Constraint Strategy

- Hard constraints remove invalid solutions

- Soft penalties guide evolution near practical limits

- This prevents unrealistic “high-score but unusable” outputs.

3. Realistic Assumptions

- Constraints are chosen to reflect an actual self-learner:

- Time Limit: ~200 hours

- Budget Limit: ~40,000 JPY

- This makes the recommendations credible and actionable.

## 🛠️ Tech Stack & Architecture

- Core Algorithm: C++ (Genetic Algorithm)

- Data Format: CSV

## 📂 Project Structure

```text
.
├── .vscode/                 # VS Code configuration (build, debug, tasks)
├── data/                    # Input dataset
├── include/                 # Header files
├── src/                     # Core implementation
├── visualize/               # Result analysis & visualization
├── output/                  # Generated outputs (CSV results)
└── main.exe                 # Compiled executable (Windows)

```

## ⚠️ Limitations

- No Personalization Yet
All learners share the same fitness weights.

- Static Ratings
Course ratings are fixed and not learned from user feedback.

- Scalability
GA works well for medium-sized datasets; very large catalogs would require hybrid or heuristic methods.

## 🎯 Learning Outcomes

Through this project, I:

- Modeled a real-world decision problem as an optimization task

- Designed a multi-objective fitness function

- Implemented Genetic Algorithms with constraint handling

- Built an end-to-end pipeline from data → optimization → visualization

- onnected algorithmic results with explainable charts

## 🏃‍♂️ How to Run

Compile: g++ src/*.cpp -Iinclude -o main      

Run: ./main

Visualize Results:

- python Visualize/chart1_fitness_convergence.py

- python Visualize/chart2_selected_courses_overview.py


## 📌 Future Improvements

- Personalized learner profiles (beginner / advanced)

- Adaptive fitness weights

- Hybrid GA + Greedy initialization

- Web-based interactive interface
