import dataclasses
from typing import Tuple, Any


# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
# Esto en c++ sería una struct
@dataclasses.dataclass
class Solucion:
    indices: list[int]
    total: int


def calculas_distancia(i, j, matriz) -> int:
    return matriz[i][j] + matriz[j][i]


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
