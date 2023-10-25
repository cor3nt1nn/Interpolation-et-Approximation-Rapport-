import matplotlib.pyplot as plt

for i in range(1,13):
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
        erreursJ.append(float(erreur_valuesJ[valeur])+1)
        erreursGS.append(float(erreur_valuesGS[valeur]))

    iterations = list(range(total_iterations))
    plt.plot(iterations, erreursGS, marker='.', color="r", linestyle='', label="GS")
    plt.plot(iterations, erreursJ, marker='.', color="b", linestyle='', label="J")
    plt.title(f'Erreur en fonction du nombre d\'itérations sur le système A{str(i)}x=b')
    plt.xlabel('Nombre d\'itérations')
    plt.ylabel('Erreur ε')
    plt.grid(True)
    plt.savefig(f"graphs/resA{str(i)}.png", dpi=200)
    plt.figure()

