import pandas as pd
import matplotlib.pyplot as plt

df_MC = pd.read_csv("../benchmarks/monte_carlo/monte_carlo_convergence.csv")
df_MC1234 = pd.read_csv("../benchmarks/monte_carlo/monte_carlo_convergence_1234.csv")
df_CRR = pd.read_csv("../benchmarks/crr_convergence/crr_convergence.csv")

# For Monte Carlo (42):
fig, ax = plt.subplots(figsize=(8, 6))
ax.loglog(df_MC["M"], df_MC["standard_error"], marker="o", linestyle="-", label="Erreur Standard1")
ax.loglog(df_MC["M"], df_MC["error"], marker="s", linestyle="--", label="Erreur Absolue (Monte Carlo vs Black-Scholes)1")

# For Monte Carlo (1234):
ax.loglog(df_MC1234["M"], df_MC1234["standard_error"], marker="o", linestyle="-", label="Erreur Standard2")
ax.loglog(df_MC1234["M"], df_MC1234["error"], marker="s", linestyle="--", label="Erreur Absolue (Monte Carlo vs Black-Scholes)2")

ax.set_xlabel("Nombre de simulations (M)")
ax.set_ylabel("Erreur")
ax.set_title("Convergence de la méthode de Monte-Carlo")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("monte_carlo_convergence.png", dpi=300)
print("Graphique sauvegardé avec succès sous : monte_carlo_convergence.png")



# For CRR:
fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df_CRR["n"], df_CRR["error"], marker="s", linestyle="--", label="Erreur Absolue (CRR vs Black-Scholes)")

ax.set_xlabel("Nombre de pas (n)")
ax.set_xlabel("Nombre de pas (n)")
ax.set_ylabel("Erreur")
ax.set_title("Convergence de la méthode de Cox-Ross-Rubinstein")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("crr_convergence.png", dpi=300)
print("Graphique sauvegardé avec succès sous : crr_convergence.png")

# CRR vs MC in time spending
fig, ax = plt.subplots(figsize=(8, 6))

ax.loglog(df_CRR["time"], df_CRR["error"], marker="s", linestyle="--", label="Erreur Absolue (CRR vs Black-Scholes)")
ax.loglog(df_MC["time"], df_MC["error"], marker="s", linestyle="--", label="Erreur Absolue (MC vs Black-Scholes)")

ax.set_xlabel("temps consommé (par second)")
ax.set_ylabel("Erreur")
ax.set_title("CRR vs MC in time spending")
ax.legend()
ax.grid(True, which="both", ls="--")

plt.tight_layout()
plt.savefig("crr_vs_mc.png", dpi=300)
print("Graphique sauvegardé avec succès sous : crr_vs_mc.png")