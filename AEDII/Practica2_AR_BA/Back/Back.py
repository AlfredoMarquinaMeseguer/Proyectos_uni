import copy
import dataclasses
import math
import sys
from functools import reduce


@dataclasses.dataclass
class Solucion:
    equipoA: list[int]
    equipoB: list[int]


def diferencia(equipos: Solucion) -> int:
    a = reduce(lambda x, y: x + y, equipos.equipoA)
    b = reduce(lambda x, y: x + y, equipos.equipoB)
    return abs(a - b)



OUTSITE = 0
def backtraking(candidatos, equipos: Solucion) -> Solucion | None:
    # Pa contar e
    global OUTSITE
    OUTSITE += 1
    # if len(equipos.equipoA) < len(equipos.equipoB) - 1 or len(
    #         equipos.equipoA) > len(equipos.equipoB) + 1:
    #     return None
    # elif len(candidatos) == 0:
    #     return equipos

    if len(candidatos) == 0:
        if len(equipos.equipoA) < len(equipos.equipoB) - 1 or len(
                equipos.equipoA) > len(equipos.equipoB) + 1:
            return None
        else:
            return equipos

    solution = None
    difer = sys.maxsize  # Cambiar por int.Max en c++
    # Creamos una copia de candidatos donde quitamos al participante que ya está en un equipo
    # para evitar añadirlo dos veces.
    copia_candidatos = copy.copy(candidatos)
    participante = copia_candidatos.pop(0)

    # Probamos a ponerlo en el equipo A
    copia_equipos = copy.deepcopy(equipos)
    copia_equipos.equipoA.append(participante)
    pretendiente1 = backtraking(copia_candidatos, copia_equipos)

    # Comprobamos
    if (pretendiente1 is not None and solution is not None and diferencia(pretendiente1) < difer) or \
            (pretendiente1 is not None and solution is None):
        solution = pretendiente1
        difer = diferencia(solution)

    # Probamos a ponerlo en el equipo B
    copia_equipos = copy.deepcopy(equipos)
    copia_equipos.equipoB.append(participante)
    pretendiente2 = backtraking(copia_candidatos, copia_equipos)

    if (pretendiente2 is not None and solution is not None and diferencia(pretendiente2) < difer) or \
            (pretendiente2 is not None and solution is None):
        solution = pretendiente2
        difer = diferencia(solution)

    return solution


if __name__ == "__main__":
    cant = [450, 106, 87, 66, 75, 372, 215, 6, 304, 291, 25, 88, 133, 221, 85, 108, 105, 381, 323, 352, 130, 100]
    print(len(cant))
    candidatos = [100, 90, 200]
    a = Solucion(equipoA=[450, 106, 87, 66, 75, 372, 215, 25, 133, 352, 130],
             equipoB=[6, 304, 291, 88, 221, 85, 108, 105, 381, 323, 100])
    print(diferencia(a))
    equipos = Solucion([], [])
    OUTSITE = 0
    print(backtraking(candidatos, equipos), OUTSITE)
    OUTSITE = 0
    print(backtraking([148, 305, 166, 81], equipos), OUTSITE)
    OUTSITE = 0
    print(backtraking(cant, equipos), OUTSITE)
