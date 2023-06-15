#include <bits/stdc++.h>
using namespace std;

bool *backtracking_v2(int *candidatos, int n)
{
    int elementosSelecionados = 0,
        sumaActual = 0;
    bool *elementosActuales = new bool[n];
    bool *solucion = new bool[n];
    float diferenciaMin = INT_MAX;
    float suma = 0;
    for (int i = 0; i < n; i++)
    {
        // cout << candidatos[i] << " " << suma << endl;
        suma += candidatos[i];
        elementosActuales[i] = false;
        solucion[i] = false;
    }

    int iteraciones = pow(2, n - 1);
    int i = 0;
    // Condición de todas las posibilidades y segunda condición de solución
    // and diferenciaMin != 0
    float minimo = n % 2 / 2.0;
    do
    {
        // Reiniciar variables en cada iteración
        elementosSelecionados = 0;
        sumaActual = 0;
        // Función genera este bucle
        //&& sumaActual <= (suma / 2)
        for (int j = 0; j < n; j++)
        {
            // Por cada bit de i representado por j se asigna su valor a un array de booleanos
            elementosActuales[j] = (i & (1 << j)) != 0;
            if (elementosActuales[j])
            {
                elementosSelecionados++;
                sumaActual += candidatos[j];
            }
        }
        // Comprobar criterio
        if ((elementosSelecionados == n / 2 || elementosSelecionados == n / 2 + n % 2) && abs((suma / 2) - sumaActual) < diferenciaMin) // Criterio
        {

            diferenciaMin = abs((suma / 2) - sumaActual);
            // cout <<  diferenciaMin << " " << suma << " " <<  sumaActual << endl;
            for (int j = 0; j < n; j++)
                solucion[j] = elementosActuales[j];
        }
        i++;
    }while (i < iteraciones and diferenciaMin != minimo);

    delete elementosActuales;
    return solucion;
}

void resolver_v2(int *candidatos, int n)
{
    bool *solucion = backtracking_v2(candidatos, n);

    int total1 = 0;
    int total2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (solucion[i] == true)
        {
            total1 += candidatos[i];
        }
        else
        {
            total2 += candidatos[i];
        }
    }

    if (total1 < total2)
    {
        std::cout << total1 << " " << total2 << std::endl;
    }
    else
    {
        std::cout << total2 << " " << total1 << std::endl;
    }
    delete solucion;
}

int main()
{
    int problemas, numCandidatos, candidatoActual;
    // Entrada
    cin >> problemas;
    while (problemas--)
    {
        cin >> numCandidatos;

        int *candidatos = new int[numCandidatos];
        for (int j = 0; j < numCandidatos; ++j)
        {
            cin >> candidatoActual;
            candidatos[j] = candidatoActual;
        }
        // resolver(candidatos, numCandidatos);
        resolver_v2(candidatos, numCandidatos);
        delete candidatos;
    }
    return 0;
}