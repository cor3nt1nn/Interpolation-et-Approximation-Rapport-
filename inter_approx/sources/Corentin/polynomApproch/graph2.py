import numpy as np
import sympy as sp
import matplotlib.pyplot as plt

with open('results/41.txt', 'r') as f:
    num_points = int(f.readline())
    x_values = np.array([float(x) for x in f.readline().split()])
    y_values = np.array([float(y) for y in f.readline().split()])
    xi_values = np.array([float(x) for x in f.readline().split()])
    yi_values = np.array([float(y) for y in f.readline().split()])

    #polynomial = f.readline()

# x = sp.symbols('x')
# polynomial_expr = sp.sympify(polynomial)
# simplified_polynomial=sp.simplify(polynomial_expr)
# sp.pprint(simplified_polynomial)
# x_range = np.linspace(x_values.min(), x_values.max(), 10)
# y_range = [simplified_polynomial.subs(x, val) for val in x_range]

plt.scatter(x_values, y_values, label='Points donnés')
plt.plot(xi_values, yi_values, label='Polynôme interpolé', color='red')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Interpolation de Neville')
plt.grid()
plt.show()

