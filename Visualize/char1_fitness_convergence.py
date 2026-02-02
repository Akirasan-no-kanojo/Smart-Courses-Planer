import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("output/fitness_per_generation.csv")

plt.figure(figsize=(8, 5))
plt.plot(df["generation"], df["best_fitness"], linewidth=2)
plt.xlabel("Generation")
plt.ylabel("Best Fitness")
plt.title("Genetic Algorithm Convergence")
plt.grid(True)

# GENERATIONS Values 
mark_gens = [0,8, 50, 100, 200, 299]

for g in mark_gens:
    if g in df["generation"].values:
        y = df.loc[df["generation"] == g, "best_fitness"].values[0]

        
        plt.scatter(g, y, zorder=5)

        
        plt.text(
            g,
            y,
            f"{int(y)}",
            fontsize=9,
            ha="center",
            va="bottom"
        )

plt.tight_layout()
plt.show()


