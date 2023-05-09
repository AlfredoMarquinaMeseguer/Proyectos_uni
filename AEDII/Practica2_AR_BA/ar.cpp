#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

struct Solucion
{
    vector<int> indices;
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
    int * indices = new int[2];
    solucion.tamano = 2;
    solucion.totalDistancia = 0;

    for (int i = 0; i < dimensiones - 1; i++)
    {
        for (int j = i + 1; j < dimensiones; j++)
        {
            candidato = calcularDistancia(i, j, matriz);
            if (candidato > solucion.totalDistancia)
            {
                indices[0] = i;
                indices[1] = j;
                solucion.totalDistancia = candidato;
            }
        }
    }
    solucion.indices.push_back(indices[0]);
    solucion.indices.push_back(indices[1]);

    delete indices;

    return solucion;
}

// int distanciaEntreListaYNumero(std::list<int> indices, int indice_cand, int **matriz)
// {
//     int total = 0;
//     for (std::list<int>::iterator it = indices.begin(); it != indices.end(); it++)
//     {
//         total += matriz[i][j] + matriz[j][i];
//     }
//     return total;
// }

struct Candidato calcularSiguiente(std::list<int> indices, std::list<int> candidatos, int **matriz)
{
    struct Candidato elegido;
    int pretendiente;
    std::list<int>::iterator it_indices;

    std::list<int>::iterator it_candidatos = candidatos.begin();
    elegido.indice = *(it_candidato);
    elegido.totalDistancia = distanciaEntreListaYNumero(indices, *(it_candidatos), matriz);
    while (it_candidatos != candidatos.end())
    {
        // for(std::list<int>::iterator it_candidatos = candidatos.begin(); it_candidatos != candidatos.end(); it_candidatos++){
        it_indices = indices.begin();
        pretendiente = 0;
        for (std::list<int>::iterator it = indices.begin(); it != indices.end(); it++)
        {
            pretendiente += matriz[i][j] + matriz[j][i];
        }

        if (pretendiente > elegido.totalDistancia)
        {
            elegido.indice = *(it_candidato);
            elegido.totalDistancia = pretendiente;
        }
        it_candidatos++;
    }

    return elegido;
}

std::string resolver_problema(int numSub, int dimensiones, int **matriz)
{
    struct Solucion solucion;
    struct Candidato pretendiente;    
    std::list<int> candidatos;
    int *indicesSeleccionados = new int[dimensiones];
    std::string salida = "";

    // Llenamos la lista de los indice del 0 al dimensiones-1
    for (int i = 0; i < dimensiones; i++)
    {
        candidatos.push_back(i);
        indicesSelecionados[i] = 0;
    }

    // Calculamos la solución para dos que es diferente
    // Es diferente a la forma que calculamos el resto de cosas
    solucion = solucionDos(dimensiones, matriz);

    for (int i = 2; i < numSub; i++)
    {

        pretendiente = calcularSiguiente(solucion.indices, candidatos, dimensiones, matriz);
        candidatos.remove(pretendiente.indice);
        solucion.indices.push_back(pretendiente.indice);
        solucion.totalDistancia = pretendiente.totalDistancia;
    }

    // Aquí Pasamos a string la solución con el formato de salida

    salida += std::to_string(solucion.totalDistancia) + "\n";

    for(std::list<int>::iterator it = solucion.indices.start(); it != Solucion.indices.end(); it++){
        indicesSeleccionados[*(it)] = 1;
    }
    for (int i = 0; i< dimensiones; i++){
        salida += indicesSeleccionados[i] + " ";
    }
    salida.pop_back()
    salida += "\n";
    
    return salida;
}

int main()
{

    return 0;
}