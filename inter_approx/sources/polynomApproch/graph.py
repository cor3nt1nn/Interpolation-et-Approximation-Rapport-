import numpy as np
import matplotlib.pyplot as plt

# Chargez le fichier texte
data = np.loadtxt("results/41.txt", skiprows=1)  # Sautez la première ligne avec le nombre de points

# Divisez les données en Xi et Yi
xi = data[0]
yi = data[1]

# Chargez le polynôme depuis la dernière ligne
polynomial_coefficients = np.array(data[2])


# Créez un tableau de valeurs x pour le tracé
x_values = np.linspace(min(xi), max(xi), 100)

# Évaluez le polynôme aux valeurs de x
y_values = np.polyval(polynomial_coefficients, x_values)

# Tracez les points donnés
plt.scatter(xi, yi, label='Points donnés', color='red')

# Tracez la courbe du polynôme
plt.plot(x_values, y_values, label='Polynôme', color='blue')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Tracé des points et du polynôme')
plt.legend()
plt.grid(True)

plt.show()
