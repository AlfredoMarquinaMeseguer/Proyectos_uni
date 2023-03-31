#include <iostream>
#include <string>
#include <cstring>
#include <set>

using namespace std;

// tamaño minimo de 6
int casoPequenno = 12;
std::set<std::string> cadenas;

void solucionDirecta(std::string problema, int inicio, int ultimo)
{
    /* Este for está aquí por si se cambia el caso pequeño,
       Si el caso pequeño es 6. Solo se ejecuta un ciclo.*/

    for (int i = inicio; i < ultimo - 5; i++) // Solución iterativa
    {
        if (cadenas.find(problema.substr(i, 3)) != cadenas.end() &&
            cadenas.find(problema.substr(i + 3, 3)) != cadenas.end())
        {
            // Se muestra el putno de inicio y la cadena
            cout << i + 1 << " " << problema.substr(i, 6) << endl;
        }
    }
}

// La junta se considera el final del de la izquierda
void combinar(std::string problema, int junta, int tamanno = casoPequenno)
{
    int inicio, ultimo, algo;

    inicio = junta - 5;
    ultimo = junta + 5;
    
    /*inicio = ultimo = junta;
    if (tamanno / 2 < casoPequenno - 1)
    {
        inicio -= tamanno / 2;
        ultimo += tamanno / 2;

        if (tamanno % 2 == 1)
        {
            ultimo += 1;
        }
    }
    else
    {
        inicio -= casoPequenno - 1;
        ultimo += casoPequenno - 1;
    }*/
    // inicio = junta - (tamanno - 1);
    // ultimo = junta + (tamanno - 1);

    //  Procuramos que los punteros no apunten fuera del array

    solucionDirecta(problema, inicio, ultimo);
}

void divide(std::string problema, int inicio, int ultimo)
{
    int tamannoProblema = ultimo - inicio;
    // cout << "Tamaño problema " << tamannoProblema << endl;
    if (tamannoProblema <= casoPequenno)
    {
        // Se asume que es de tamaño del caso pequenno
        solucionDirecta(problema, inicio, ultimo);
    }
    else if (tamannoProblema > casoPequenno)
    {
        int junta = (inicio + ultimo) / 2;
        divide(problema, inicio, junta);
        combinar(problema, junta, tamannoProblema);
        divide(problema, junta, ultimo);
    }
}

void divideYVenceras(std::string problema)
{
    divide(problema, 0, problema.length());
}

void iterativa(string problema)
{
    int n = problema.length();

    for (int i = 0; i < n - 5; i++)
    {
        if (cadenas.find(problema.substr(i, 3)) != cadenas.end() &&
            cadenas.find(problema.substr(i + 3, 3)) != cadenas.end())
        {
            cout << i + 1 << " " << problema.substr(i, 6) << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    string componentes;
    string problema;
    for (int i = 0; i < 3; i++)
    {
        getline(std::cin, componentes);
        cadenas.insert(componentes);
    }
    getline(std::cin, problema);

    if (argc > 1 && std::strcmp(argv[1], "it") == 0)
    {
        iterativa(problema);
    }
    else if (argc > 1 && std::strcmp(argv[1], "dyv") == 0)
    {
        divideYVenceras(problema);
    }
    return 0;
}
