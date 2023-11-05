import numpy as np
import matplotlib.pyplot as plt
import sys
import sympy as s
# Chargez le fichier texte
#data = np.loadtxt(str(sys.argv[1]))  # Sautez la première ligne avec le nombre de points
def polynom(DD, X):
    s.var("x")
    P = DD[-1]
    for i in range(len(DD)-1, 1, -1):
        P = DD[i] + (x-X[i])*P
    P = s.expand(P)
   # s.pprint(P)
    return str(P)

data=[]
with open(str(sys.argv[1])) as f:
    data=f.readlines()
# Divisez les données en Xi et Yi
xi = list(map(float, data[0].split()))
yi = list(map(float, data[1].split()))
xn = list(map(float, data[3].split()))
yc = list(map(float,data[2].split()))
DD = list(map(float,data[4].split()))
print(polynom(DD,xi))

# Chargez le polynôme depuis la dernière ligne
#polynomial_coefficients = np.array(data[2])
# Créez un tableau de valeurs x pour le tracé
#x_values = np.linspace(min(xi), max(xi), 100)

# Évaluez le polynôme aux valeurs de x
#y_values = np.polyval(polynomial_coefficients, x_values)

# Tracez les points donnés
plt.scatter(xi, yi, label='Points donnés', color='red')
# Tracez la courbe du polynôme
plt.plot(xn, yc, label='Polynôme', color='blue')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Tracé des points et du polynôme '+polynom(DD,xi), fontsize=5)
plt.legend()
plt.grid(True)
plt.savefig(str(sys.argv[1])[:-3]+"-fig.png")
plt.show()
