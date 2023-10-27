import matplotlib.pyplot as plt

for i in range(1,3):
    with open(f'jacobi/resA{str(i)}.txt', 'r') as jacobi:
        linesJ = jacobi.readlines()   

    with open(f'GS/a{str(i)}.txt', 'r') as gaussS:
        linesGS = gaussS.readlines()   

    iterations = []
    erreursJ = []
    erreursGS = []
    total_iterations = min(int(linesJ[1]),int(linesGS[1]))

    erreur_valuesJ = linesJ[0].strip().split()
    erreur_valuesGS = linesGS[0].strip().split()

    for valeur in range(total_iterations):
        erreursJ.append(float(erreur_valuesJ[valeur]))
        erreursGS.append(float(erreur_valuesGS[valeur]))
	
    iterations = list(range(total_iterations))
    plt.yscale('log')

    plt.plot(iterations, erreursGS, label='Gauss-Seidel', marker='', color="r", linestyle='-')
    plt.plot(iterations, erreursJ, label='Jacobi', marker='', color="b", linestyle='-')
    plt.title("Erreur en fonction du nombre d'itérations sur le système $A_{" + str(i) +"}x=b$")
    plt.xlabel('Nombre d\'itérations')
    plt.ylabel('Erreur $ε^{k}$')
    plt.grid(True)
    plt.legend()
    plt.savefig(f"graphs/resA{str(i)}.png", dpi=200)
    plt.figure()

