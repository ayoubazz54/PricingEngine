import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../benchmarks/monte_carlo/monte_carlo_convergence.csv")
df_1 = pd.read_csv("../benchmarks/parallel/monte_carlo_convergence_parallel_1.csv")
df_2 = pd.read_csv("../benchmarks/parallel/monte_carlo_convergence_parallel_2.csv")
df_4 = pd.read_csv("../benchmarks/parallel/monte_carlo_convergence_parallel_4.csv")
df_8 = pd.read_csv("../benchmarks/parallel/monte_carlo_convergence_parallel_8.csv")
df_12 = pd.read_csv("../benchmarks/parallel/monte_carlo_convergence_parallel_12.csv")

fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df["time"], df["error"], marker="s", linestyle="--", label="without parallelization")
ax.loglog(df_1["time"], df_1["error"], marker="s", linestyle="--", label="1 thread")
ax.loglog(df_2["time"], df_2["error"], marker="s", linestyle="--", label="2 threads")
ax.loglog(df_4["time"], df_4["error"], marker="s", linestyle="--", label="4 threads")
ax.loglog(df_8["time"], df_8["error"], marker="s", linestyle="--", label="8 threads")
ax.loglog(df_12["time"], df_12["error"], marker="s", linestyle="--", label="12 threads")


ax.set_xlabel("temps (s)")
ax.set_ylabel("Erreur (Monte carlo - BlackScholes)")
ax.set_title("Erreur Monte Carlo en fonction du temps d'exécution")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("monte_carlo_convergence_parallel.png", dpi=300)
print("Graphique sauvegardé avec succès sous : monte_carlo_convergence_parallel.png")

# Error for M
fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df["M"], df["error"], marker="s", linestyle="--", label="without parallelization")
ax.loglog(df_1["M"], df_1["error"], marker="s", linestyle="--", label="1 thread")
ax.loglog(df_2["M"], df_2["error"], marker="s", linestyle="--", label="2 threads")
ax.loglog(df_4["M"], df_4["error"], marker="s", linestyle="--", label="4 threads")
ax.loglog(df_8["M"], df_8["error"], marker="s", linestyle="--", label="8 threads")
ax.loglog(df_12["M"], df_12["error"], marker="s", linestyle="--", label="12 threads")


ax.set_xlabel("Number of Simulations (M)")
ax.set_ylabel("Erreur (Monte carlo - BlackScholes)")
ax.set_title("Convergence Monte Carlo parallèlisé")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("monte_carlo_convergence_multiple_threads.png", dpi=300)
print("Graphique sauvegardé avec succès sous : monte_carlo_convergence_multiple_threads.png")