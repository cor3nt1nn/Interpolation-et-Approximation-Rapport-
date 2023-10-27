import matplotlib.pyplot as plt

with open('fichiertest.txt', 'r') as file:
    lines = file.readlines()   

iterations = []
erreurs = []

total_iterations = int(lines[1])
erreur_values = lines[0].strip().split()

for valeur in erreur_values:
    erreurs.append(float(valeur))

iterations = list(range(total_iterations))

plt.plot(iterations, erreurs, marker='o', linestyle='-')
plt.title('Erreur en fonction du nombre d\'itérations')
plt.xlabel('Nombre d\'itérations')
plt.ylabel('Erreur')
plt.grid(True)
plt.show()
