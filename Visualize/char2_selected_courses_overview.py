import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import textwrap

# Load data
df = pd.read_csv("output/selected_courses.csv")

total_time = df["Duration (h)"].sum()
total_price = df["Price (JPY)"].sum()
avg_rating = df["Rating"].mean()

x = np.arange(len(df))
width = 0.25

fig, ax1 = plt.subplots(figsize=(14, 6))

# BAR 1: Duration 
bars_time = ax1.bar(
    x - width,
    df["Duration (h)"],
    width,
    label="Duration (h)"
)

# BAR 2: Price 
bars_price = ax1.bar(
    x,
    df["Price (JPY)"] / 100,
    width,
    color="orange",
    label="Price (JPY / 100)"
)
labels = [
    "\n".join(textwrap.wrap(name, width=16))
    for name in df["Course Name"]
]

ax1.set_ylabel("Duration / Price")
ax1.set_xticks(x)
ax1.set_xticklabels(
    labels,
    fontsize=9,
    ha="center"
)
ax1.grid(axis="y", linestyle="--", alpha=0.5)

# BAR 3: Rating 
ax2 = ax1.twinx()
bars_rating = ax2.bar(
    x + width,
    df["Rating"],
    width,
    color="green",
    label="Rating"
)
ax2.set_ylabel("Rating")
ax2.set_ylim(3.5, 5.0)

# Annotate values 
def annotate_bars(bars, ax, offset=0):
    for bar in bars:
        height = bar.get_height()
        ax.text(
            bar.get_x() + bar.get_width() / 2,
            height + offset,
            f"{height:.1f}",
            ha="center",
            va="bottom",
            fontsize=9
        )

annotate_bars(bars_time, ax1, offset=1)
annotate_bars(bars_price, ax1, offset=0.5)
annotate_bars(bars_rating, ax2, offset=0.03)

lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(
    lines1 + lines2,
    labels1 + labels2,
    loc="upper left"
)

summary_text = (
    f"Total Duration: {total_time} h\n"
    f"Total Price: {total_price:,} JPY\n"
    f"Average Rating: {avg_rating:.2f}"
)

plt.text(
    0.98,
    0.95,
    summary_text,
    transform=ax1.transAxes,
    ha="right",
    va="top",
    fontsize=10,
    bbox=dict(boxstyle="round", facecolor="white", alpha=0.9)
)

plt.title("Selected Courses Overview: Duration, Price & Rating")

plt.tight_layout()
plt.show()
