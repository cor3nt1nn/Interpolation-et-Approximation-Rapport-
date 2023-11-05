import numpy as np
import sympy as sp
import matplotlib.pyplot as plt

for i in range(1, 4):
    with open(f'text/4{i}.txt', 'r') as f:
        x_values = np.array([float(x) for x in f.readline().split()])
        y_values = np.array([float(y) for y in f.readline().split()])
        xi_values = np.array([float(x) for x in f.readline().split()])
        yi_values = np.array([float(y) for y in f.readline().split()])

    plt.scatter(x_values, y_values, label='Points donnés')
    plt.plot(xi_values, yi_values, label='Polynôme approximé', color='red')
    plt.xlabel('x')
    plt.ylabel('y')
    # plt.xlim([min(xi_values), max(xi_values)])
    # plt.ylim([min(y_values), max(y_values)])
    plt.legend()
    plt.title(f'Interpolation de Neville pour 4.{i}')
    plt.grid()
    plt.savefig(f'graphs/4{i}.png')
    plt.figure()

