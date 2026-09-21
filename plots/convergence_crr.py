
import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("../benchmarks/crr_convergence/crr_convergence.csv")

# For CRR:
fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df["n"], df["price"], marker="s", linestyle="--", label="CRR")
ax.axhline(y=df["exactprice"].iloc[0], color='r', linestyle='-', label="Black-Scholes")

ax.set_xlabel("Nombre de pas (n)")
ax.set_ylabel("Price")
ax.set_title("Convergence de la méthode de Cox-Ross-Rubinstein")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("crr_convergence_price.png", dpi=300)
print("Graphique sauvegardé avec succès sous : crr_convergence_price.png")