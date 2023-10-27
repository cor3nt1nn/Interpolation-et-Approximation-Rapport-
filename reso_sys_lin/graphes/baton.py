import matplotlib.pyplot as plt
import numpy as np


# Données sur le nombre d'itérations pour Gauss-Seidel et Jacobi
iterations_gauss_seidel = []
iterations_jacobi = []

for i in range(3,13):
    with open(f'jacobi/resA{str(i)}.txt', 'r') as jacobi:
        linesJ = jacobi.readlines()
    with open(f'GS/a{str(i)}.txt', 'r') as gaussS:
        linesGS = gaussS.readlines()
    iterations_gauss_seidel.append(int(linesGS[1]))
    iterations_jacobi.append(int(linesJ[1]))
  
# Création de l'axe des x (indices des matrices)
matrices = np.arange(3, 13)

# Largeur des barres dans le diagramme à barres
bar_width = 0.15

# Création de la figure
plt.figure(figsize=(10, 6))

# Création des barres pour Gauss-Seidel
plt.bar(matrices - bar_width/2, iterations_gauss_seidel, bar_width, color='r', label='Gauss-Seidel')

# Création des barres pour Jacobi
plt.bar(matrices + bar_width/2, iterations_jacobi, bar_width, color='b', label='Jacobi')

# Remplacement des étiquettes de l'axe des x
matrices_labels=[]
for k in range(3,13):
	matrices_labels.append("$A_{" + str(k) +"}x=b$")
plt.xticks(matrices, matrices_labels)

# Ajout de légendes et de titres
plt.xlabel('Système résolu')
plt.ylabel('Nombre d\'itérations')
plt.title('Nombre d\'itérations pour Gauss-Seidel et Jacobi pour la résolution des systèmes $A_{k}x=b$, où les deux méthodes convergent')
plt.xticks(matrices)
plt.legend()

# Affichage du diagramme
plt.tight_layout()
plt.show()

