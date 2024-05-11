#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

struct Solucion
{
    list<int> indices;
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

Solucion solucionDos(int dimensiones, int **matriz)
{
    int candidato;
    Solucion solucion;
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

Candidato calcularSiguiente(list<int> indices, list<int> candidatos, int **matriz)
{
    Candidato elegido;
    int pretendiente;
    list<int>::iterator it_indices;
    list<int>::iterator it_candidatos = candidatos.begin();
    elegido.indice = *(it_candidatos);
    elegido.totalDistancia = 0;
        for (list<int>::iterator it = indices.begin(); it != indices.end(); it++)
        {
            elegido.totalDistancia += matriz[*(it)][*(it_candidatos)] + matriz[*(it_candidatos)][*(it)];
        }
    it_candidatos++;
    while (it_candidatos != candidatos.end())
    {
        // for(std::list<int>::iterator it_candidatos = candidatos.begin(); it_candidatos != candidatos.end(); it_candidatos++)
        it_indices = indices.begin();
        pretendiente = 0;
        for (list<int>::iterator it = indices.begin(); it != indices.end(); it++)
        {
            pretendiente += matriz[*(it)][*(it_candidatos)] + matriz[*(it_candidatos)][*(it)];
        }

        if (pretendiente > elegido.totalDistancia)
        {
            elegido.indice = *(it_candidatos);
            elegido.totalDistancia = pretendiente;
        }
        it_candidatos++;
    }

    return elegido;
}

Solucion resolver_problema(int numSub, int dimensiones, int **matriz)
{
    Solucion solucion;
    Candidato pretendiente;
    list<int> candidatos;
    int *indicesSeleccionados = new int[dimensiones];
    string salida = "";

    // Llenamos la lista de los indice del 0 al dimensiones-1
    for (int i = 0; i < dimensiones; i++)
    {
        candidatos.push_back(i);
        indicesSeleccionados[i] = 0;
    }

    // Calculamos la solución para dos que es diferente
    // Es diferente a la forma que calculamos el resto de cosas
    solucion = solucionDos(dimensiones, matriz);

    for (int i = 2; i < numSub; i++)
    {
        pretendiente = calcularSiguiente(solucion.indices, candidatos, matriz);
        candidatos.remove(pretendiente.indice);
        solucion.indices.push_back(pretendiente.indice);
        solucion.totalDistancia = pretendiente.totalDistancia;
    }

    // Aquí Pasamos a string la solución con el formato de salida

    return solucion;
}

int main()
{
    int numCasos;
    int dimensiones, numSubpoblaciones;
    int ** matriz;

    cin >> numCasos;
    for( int caso =0; caso< numCasos; ++caso){
        cin >> dimensiones >> numSubpoblaciones;
        matriz = new int*[dimensiones];
        for (int i = 0; i < dimensiones; i++)
        {
            matriz[i] = new int[dimensiones];
        }


        for(int j=0; j<dimensiones; ++j){
            for(int k=0; k<dimensiones; ++k){
                // int aux;
                // cin >> aux;
                // matriz[i][j] = aux;
                cin >> matriz[j][k];
            }
        }
        // cout << resolver_problema(numSubpoblaciones,dimensiones,matriz);
        Solucion sol = resolver_problema(numSubpoblaciones,dimensiones,matriz);
        cout << to_string(sol.totalDistancia) << endl;
        int * salida = new int[dimensiones];
        for(int i= 0; i< dimensiones; ++i){
            salida[i] = 0;
        }
        for(list<int>::iterator it = sol.indices.begin(); it != sol.indices.end(); ++it){
            salida[*(it)] = 1;
        }

        for(int i= 0; i< dimensiones-1; ++i){
            cout << salida[i] << " ";
        }
        cout << salida[dimensiones-1] << endl;

        for (int i = 0; i < dimensiones; i++)
        {
            delete matriz[i];
        }
        delete matriz;
    }

    return 0;
}
