import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../build/monte_carlo_convergence.csv")

fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df["M"], df["standard_error"], marker="o", linestyle="-", label="Erreur Standard")
ax.loglog(df["M"], df["error"], marker="s", linestyle="--", label="Erreur Absolue (vs Black-Scholes)")

ax.set_xlabel("Nombre de simulations (M)")
ax.set_xlabel("Nombre de simulations (M)")
ax.set_ylabel("Erreur")
ax.set_title("Convergence de la méthode de Monte-Carlo")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("monte_carlo_convergence.png", dpi=300)
print("Graphique sauvegardé avec succès sous : monte_carlo_convergence.png")