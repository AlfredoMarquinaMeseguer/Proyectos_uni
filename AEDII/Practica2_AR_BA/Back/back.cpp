#include <bits/stdc++.h>
using namespace std;


void backtracking(int *candidatos, int n, bool *elementosActuales, int elementosSelecionados,
                  bool *equipos, int *diferenciaMin, int suma, int sumaActual, int posicionActual)
{
    
    if ((posicionActual == n) || ((n / 2 - elementosSelecionados) > (n - posicionActual)))
        return;

    
    backtracking(candidatos, n, elementosActuales, elementosSelecionados,
                 equipos, diferenciaMin, suma, sumaActual, posicionActual + 1);

    
    elementosSelecionados++;
    sumaActual += candidatos[posicionActual];
    elementosActuales[posicionActual] = true;

    // Comprobamos que sea un nodo hoja
    if (elementosSelecionados == n / 2)
    {
        // Si la solución obtenida es menor que la mínima, sobreescribir
        if (abs(suma / 2 - sumaActual) < *diferenciaMin)
        {
            *diferenciaMin = abs(suma / 2 - sumaActual);
            for (int i = 0; i < n; i++)
                equipos[i] = elementosActuales[i];
        }
    }
    else
    {
        backtracking(candidatos, n, elementosActuales, elementosSelecionados, equipos,
                     diferenciaMin, suma, sumaActual, posicionActual + 1);
    }

    elementosActuales[posicionActual] = false;
}


void resolver(int *candidatos, int n)
{
    bool *elementoActual = new bool[n];


    bool *solucion = new bool[n];

    int difrenciaMin = INT_MAX;

    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += candidatos[i];
        elementoActual[i] = false;
        solucion[i] = false;
    }


    backtracking(candidatos, n, elementoActual, 0, solucion, &difrenciaMin, suma, 0, 0);

    int total1 = 0;
    int  total2 = 0;
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
        cout << total1 << " " << total2 << endl;
    }
    else
    {   
        cout << total2 << " " << total1 << endl;
    }
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
            candidatos[j] =  candidatoActual;
        }
        resolver(candidatos, numCandidatos);        
        delete candidatos;
    }
    return 0;
}