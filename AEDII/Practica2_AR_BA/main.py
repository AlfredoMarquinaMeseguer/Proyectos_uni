# This is a sample Python script.
from typing import Tuple, Any


# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def combinaciones_2(dimensiones) -> list[list[int]]:
    lista = []
    for i in range(0, dimensiones):
        for j in range(i + 1, dimensiones):
            lista.append([i, j])
    return lista


def combinaciones_2_de_lista(lista: [int]) -> list[Tuple[int, int]]:
    sol = []
    for i in range(0, len(lista)):
        for j in range(i + 1, len(lista)):
            sol.append((lista[i], lista[j]))
    return sol


def combinaciones_2_con_n(lista: [int], n: int) -> list[list[int]]:
    sol = []
    for i in lista:
        sol.append([i, n])
    return sol


def calculas_distancia(i, j, matriz) -> int:
    return matriz[i][j] + matriz[j][i]


def calcular_distancias_listas(lista, matriz) -> int:
    return [calculas_distancia(i[0], i[1], matriz) for i in lista]


def solucion_con_dos():
    dimensiones = 4
    subconjuntos = 2
    matriz = [[0, 3, 2, 4],
              [2, 0, 4, 5],
              [2, 1, 0, 4],
              [2, 3, 2, 0]]
    sol = []
    maxi = 0
    # [0,1] [0,2] 0,3 1,2 1,3 2,4
    #
    # matriz[candidatos[0]][candidatos[1]] + matriz[candidatos[1]][candidatos[0]]
    candidatos = combinaciones_2(dimensiones, subconjuntos)

    for i in candidatos:
        x = calculas_distancia(i[0], i[1], matriz)
        if x > maxi:
            maxi = x
            sol = i

    return maxi, sol


# len_matriz no es necesaria
def resolver_problema(matriz: [[int]], num_subs: int, len_matriz: int):
    conjunto_solucion = []
    tamanno_sol = 2

    pares = calcular_pares(len_matriz, matriz)
    sol, indice = calcular_max(pares)
    pares.pop(indice)
    while tamanno_sol < num_subs:
        tamanno_sol += 1
        pares_copy = pares.copy()
        a = None
        while a is None:
            candidato, indice = calcular_max(pares_copy)  # seleccionar
            if candidato[0][0] in sol[0]:
                a = candidato[0][1]
            elif candidato[0][1] in sol[0]:  # factible
                a = candidato[0][0]
            else:
                pares_copy.pop(indice)

        # añadir a solución
        # eliminar sol de pares
        pares_sol = combinaciones_2_con_n(sol[0], a)
        # sumar = 0
        for i in pares_sol:
            sol[1] += calculas_distancia(i[0], i[1], matriz)
        sol[0].append(a)

    return sol


def calcular_max(lista: list[list[int], int]) -> Tuple[list[list[int] | int], int]:
    indice_del_max = 0

    for i in range(1, len(lista)):
        if lista[i][1] > lista[indice_del_max][1]:
            indice_del_max = i

    return lista[indice_del_max], indice_del_max


def entrada():
    file = open("entrada.txt")
    num_problemas = file.readline()

    for _ in num_problemas:
        # Esto en c++ se puede poner directamente en dos variables
        dimensiones_subconjuntos = file.readline().split()
        # EN c++ hay que declarar directamente
        matriz = []

        for i in dimensiones_subconjuntos[0]:
            for j in dimensiones_subconjuntos[0]:
                linea = [int(a) for a in file.readline().split()]
                matriz.append(linea)

        print(resolver_problema(matriz, dimensiones_subconjuntos[1], dimensiones_subconjuntos[0]))

        # Press the green button in the gutter to run the script.


def calcular_pares(dimensiones: int, matriz):
    combi = combinaciones_2(dimensiones)
    pares = []

    for i in combi:
        pares.append([i, calculas_distancia(i[0], i[1], matriz)])

    # TODO: Ordenar por distancia

    return pares


def str_respuesta(solucion, dimensiones) -> Tuple[str, str]:
    salida_list = []
    for _ in range(dimensiones):
        salida_list.append(0)

    for i in solucion[0]:
        salida_list[i] = 1

    salida_str = ""
    for i in salida_list:
        salida_str += str(i) + " "

    return str(solucion[1]), salida_str.strip()


if __name__ == '__main__':
    matriz = [[0, 3, 2, 4],
              [2, 0, 4, 5],
              [2, 1, 0, 4],
              [2, 3, 2, 0]]
    dimensiones = 6
    num_sub = 3
    matriz2 =[[5,    0,    4,    2,    5,    3],
    [4,    0,    1,    1,    3,    3],
    [2,    5,    0,    3,    0,    4],
    [3,    3,    4,    0,    4,    7],
    [2,    5,    7,    5,    0,    6],
    [4,    8,    5,    6,    8,    0]]
    # pares = calcular_pares(4)
    # solucion = resolver_problema(matriz, 3, 4)
    #
    # for i in  str_respuesta(solucion, 4):
    #     print(i)

    for i in  str_respuesta(resolver_problema(matriz2, num_sub, dimensiones), dimensiones):
            print(i)



    # print(pares)
    # print(calcular_max(pares))
    print(combinaciones_2_con_n([1, 2, 3, 4], 5))

    print(1 | 2 in (1, 4, 1))
