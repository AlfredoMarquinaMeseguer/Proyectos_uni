import pandas as pd
import time
import random
import subprocess

def imprimeMatriz(dimensiones):
    matriz = ""
    for i in range(dimensiones - 1):
        for j in range(dimensiones - 1):
            if i == j:
                matriz += str(0)
            else:
                matriz += str(random.randint(0, 255))

            if j == dimensiones - 1:
                matriz += "\n"
            else:
                matriz += " "
    return matriz


def generar_input(dimensiones: int, subpoblaciones: int, inputfilename: str = "in2.txt") -> None:
    input_file = open(inputfilename, 'w')
    input_file.write(1)
    input_file.write(dimensiones + " " + subpoblaciones)
    input_file.write(imprimeMatriz(dimensiones))
    input_file.close()


def ejecutar_programa(nombre_entrada: str, nombre_salida: str) -> None:
    fichero_entrada = open(nombre_entrada, "r")
    fichero_salida = open(nombre_salida, "w")

    tiempo_inicio = round(time.time() * 1000)
    # Ejecutar proceso
    proc = subprocess.Popen(["./solucion"],  # Edita esto
                            stdin=fichero_entrada, stdout=fichero_salida)
    proc.wait()
    # Obtener final de ejecución
    tiempo_final = round(time.time() * 1000)

    # Cerrar ficheros de i/o
    fichero_entrada.close()
    fichero_salida.close()

    return tiempo_final - tiempo_inicio


def pruebas(n: int, nombre_entrada, nombre_salida: str, nombre_guardar: str):
    df: pd.DataFrame = pd.DataFrame(
        columns=['dimensiones', 'subpoblaciones', 'tiempo_exec'])
    for dimensiones in range(4, n):
        for subpoblaciones in range(2, dimensiones - 1):
            generar_input(dimensiones, subpoblaciones, nombre_entrada)
            tiempo = ejecutar_programa(nombre_entrada, nombre_salida)
            df.loc[len(df)] = [dimensiones, subpoblaciones, tiempo]

    df.to_csv(nombre_guardar)

if __name__ == "__main__":
    print("coopila")