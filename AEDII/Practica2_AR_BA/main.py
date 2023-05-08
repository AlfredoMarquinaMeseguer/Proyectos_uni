# This is a sample Python script.
import dataclasses
from typing import Tuple, Any


# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
# Esto en c++ sería una struct
@dataclasses.dataclass
class Solucion:
    indices: list[int]
    total: int


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


def solucion_con_dos(dimensiones, matriz) -> Solucion:
    pareja_ganadora = []
    maxi = 0
    for i in range(0, dimensiones):
        for j in range(i + 1, dimensiones):
            candidato = calculas_distancia(i, j, matriz)
            if candidato > maxi:
                pareja_ganadora = [i, j]
                maxi = candidato

    return Solucion(pareja_ganadora, maxi)


# len_matriz no es necesaria
def resolver_problema(matriz: [[int]], len_matriz: int, num_subs: int):
    # La solución para dos es diferente al resto de soluciones
    # Una vez obtenida se va añadiendo a ella.
    solution = solucion_con_dos(len_matriz, matriz)

    if len(solution.indices) < num_subs:
        # Creamos lista de indices candidatos
        candidatos = list(range(len_matriz))
        # quitamos los que ya se encuentran en la solución
        for i in solution.indices:
            candidatos.remove(i)

        while len(solution.indices) < num_subs:
            # Seleccionamos el siguiente indice
            siguiente, total = calc_siguiente(solution.indices, candidatos, matriz)
            # Como siempre da solución lo añadimos a siguiente
            solution.indices.append(siguiente)
            # También sustituimos el total
            solution.total = total
            # Quitamos al siguiente de los candidatos por si hacemos otro bucle
            candidatos.remove(siguiente)
    # Devuelve una clase tipo solución que contiene una lista de índices escogidos y el total que sumas. Esto en
    # c++ puede ser un struct con un array índices, tamaño array y total.
    return solution


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


def distancia_total(lista: list[int], matriz: list[list[int]]) -> int:
    # De la lista se obtienen y calculan todas las distancias
    sol = 0
    for i in range(0, len(lista)):
        for j in range(i + 1, len(lista)):
            sol += calculas_distancia(lista[i], lista[j], matriz)

    return sol


def calc_siguiente(en_sol: list[int], candidatos: list[int], matriz: list[list[int]]):
    pass
    calc = []
    maxi_indice = -1
    maxi = 0
    # Utilizamos el range para simular c++
    for i in range(len(candidatos)):
        pretendiente = distancia_total(en_sol + [candidatos[i]], matriz)
        if maxi < pretendiente:
            maxi_indice = candidatos[i]
            maxi = pretendiente

    return maxi_indice, maxi


if __name__ == '__main__':
    matriz = [[0, 3, 2, 4],
              [2, 0, 4, 5],
              [2, 1, 0, 4],
              [2, 3, 2, 0]]
    dimensiones = 6
    num_sub = 3
    matriz2 = [[5, 0, 4, 2, 5, 3],
               [4, 0, 1, 1, 3, 3],
               [2, 5, 0, 3, 0, 4],
               [3, 3, 4, 0, 4, 7],
               [2, 5, 7, 5, 0, 6],
               [4, 8, 5, 6, 8, 0]]
    print(resolver_problema(matriz, 4, 3))
    print(resolver_problema(matriz2, dimensiones, num_sub))
    # pares = calcular_pares(4)
    # solucion = resolver_problema(matriz, 3, 4)
    #
    # for i in  str_respuesta(solucion, 4):
    #     print(i)
    b = list(range(4))
    a = [0, 4, 2, 3, 4]
    # a.pop(4)
    print(a)
    print(b)
