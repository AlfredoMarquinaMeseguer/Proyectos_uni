#include <iostream>
#include <string>
#include <cstring>
#include <set>

using namespace std;

// El tamaño con el que se empiezan a realizar las soluciones directas
const int casoPequenno = 12;
const int tamannoSolucion = 6;
const int mitadSolucion = tamannoSolucion / 2;
// En este set o bolsa pondremos todas las subcadenas posibles
std::set<std::string> cadenas;

void solucionDirecta(std::string problema, int inicio, int ultimo)
{
    /* Este "for" está aquí por si se cambia el caso pequeño,
       Si el caso pequeño es 6. Solo se ejecuta un ciclo.*/
    // Se a cambiado a 12
    for (int i = inicio; i < ultimo - (tamannoSolucion - 1); i++) // Solución iterativa
    {
        if (cadenas.find(problema.substr(i, mitadSolucion)) != cadenas.end() &&
            cadenas.find(problema.substr(i + mitadSolucion, mitadSolucion)) != cadenas.end())
        {
            // Se muestra el punto de inicio y la cadena
            cout << i + 1 << " " << problema.substr(i, tamannoSolucion) << endl;
        }
    }
}

// La junta se considera el final del de la izquierda
void combinar(std::string problema, int junta, int tamanno = casoPequenno)
{
    int inicio, ultimo, algo;

    inicio = junta - 5;
    ultimo = junta + 5;
    solucionDirecta(problema, inicio, ultimo);
}

void divide(std::string problema, int inicio, int ultimo)
{
    // Autoexplicativo
    int tamannoProblema = ultimo - inicio;
    if (tamannoProblema <= casoPequenno)
    {
        solucionDirecta(problema, inicio, ultimo);
    }
    else if (tamannoProblema > casoPequenno)
    {
        // La zona donde se separan los dos subproblemas
        int junta = (inicio + ultimo) / 2;
        // Misma estrucutra que las torres de Hanoi
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
    for (int i = 0; i < int(problema.length()) - (tamannoSolucion-1); i++)
    {
        if (cadenas.find(problema.substr(i, mitadSolucion)) != cadenas.end() &&
            cadenas.find(problema.substr(i + mitadSolucion, mitadSolucion)) != cadenas.end())
        {
            std::cout << i + 1 << " " << problema.substr(i, tamannoSolucion) << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    // Aquí vamos a leer las subcadenas de patrones a identificar
    string componentes, 
    // La cadena continua larga del problema
        problema;

    // Leemos la cadena de stdin
    for (int i = 0; i < 3; i++)
    {
        getline(std::cin, componentes);
        cadenas.insert(componentes);
    }
    getline(std::cin, problema);

    // Lee del arg el tipo de solución
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
