#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

struct Solucion
{
    int *indices;
    int tamano;
    int totalDistancia;
};

struct Candidato
{
    int indice;
    int totalDistancia;
};

int calcularDistancia(int i, int j, int **matriz)
{
    return matriz[i][j] + matriz[j][i];
}

struct Solucion solucionDos(int dimensiones, int **matriz)
{
    int candidato;
    struct Solucion solucion;
    solucion.indices = new int[2];
    solucion.tamano = 2;
    solucion.totalDistancia = 0;

    for (int i = 0; i < dimensiones; i++)
    {
        for (int j = i; j < dimensiones; j++)
        {
            candidato = calcularDistancia(i, j, matriz);
            if (candidato > solucion.totalDistancia)
            {
                solucion.indices[0] = i;
                solucion.indices[1] = j;
                solucion.totalDistancia = candidato;
            }
        }
    }

    return solucion;
}
string resolver_problema(int numSub, int dimensiones, int **matriz)
{
    struct Solucion solucion;
    struct Candidato pretendiente;
    int *candidatos = new int[dimensiones];

    solucion = solucionDos(dimensiones, matriz);

    if (solucion.tamano < numSub)
    {
        for (int i = 0; i < dimensiones; i++)
        {
            candidatos[i] = i;
        }

        candidatos[solucion.indices[0]] = -1;
        candidatos[solucion.indices[1]] = -1;

        while (solucion.tamano < numSub)
        {
            // pretendiente = calcularSiguiente(solucion.indices, candidatos, dimensiones, matriz);            
            // int * indices = new int[solucion.tamano +1];

        }
    }
    return "";
}

int main()
{

    return 0;
}