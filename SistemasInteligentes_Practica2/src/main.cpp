#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "elemento.h"
#include "casos.h"
#include "a_sbr_logger.h"

#define REGLAY 0 // Esta macro nos sirve para expresar que una regla contiene el operador y
#define REGLA0 1 // Esta macro nos sirve para expresar que una regla contiene el operador o
#define REGLAC 2
struct regla
{                      // Estructura de una regla
    double fc;         // Factor de certeza de la regla
    int tipo = REGLAC; // Por defecto el tipo de una regla es REGLAC
    std::string consecuente, id;
    std::vector<std::string> antecedentes; // Lista de antecedentes de la regla
};
std::string extraerNombre(std::string cadena)
{
    std::string nombre;
    auto it = cadena.begin();
    while (it != cadena.end() && *it != '.')
    {
        // Tiene el or para que funcione en linux y windows
        if (*it == '/' || *it == '\\')
            nombre.clear();
        else
            nombre += *it;
        it++;
    }
    return nombre;
}

std::vector<std::string> separarString(const std::string &input)
{
    std::vector<std::string> result;
    std::istringstream iss(input);

    // Iterate through each word in the string
    do
    {
        std::string word;
        iss >> word;
        if (!word.empty())
        {
            result.push_back(word);
        }
    } while (iss);

    return result;
}
std::vector<Hecho *> hechos;
Hecho *contiene(std::string nombre, bool annadir = true)
{
    Hecho *hecho = nullptr;
    auto it = hechos.begin();

    while (it != hechos.end() && hecho == nullptr)
    {
        if ((*it)->getNombre() == nombre)
        {
            hecho = *it;
        }
        it++;
    }
    if (hecho == nullptr && annadir)
    {
        hechos.push_back(new Hecho(nombre));
        return hechos.back();
    }
    return hecho;
}

Regla *contiene(std::vector<Regla *> reglas, std::string nombre)
{
    Regla *regla = nullptr;
    auto it = reglas.begin();

    while (it != reglas.end() && regla == nullptr)
    {
        if ((*it)->getNombre() == nombre)
        {
            regla = *it;
        }
        it++;
    }
    return regla;
}

int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 4)
    {
        std::cerr << "Uso: " << argv[0] << " <entrada_BC> <entrada_BH> <salida>" << std::endl;
        return 1; // Exit with an error code
    }

    std::vector<std::string> palabrasRegla, objetivos;
    std::string nombreRegla;
    std::string nombreHecho;
    std::vector<Elemento *> elementos;
    regla *nuevaR;
    std::vector<Regla *> reglasAux;
    std::ifstream ficheroBC(argv[1]);
    std::ifstream ficheroBH(argv[2]);

    if (!ficheroBC.is_open() || !ficheroBH.is_open())
    {
        std::cerr << "Error abriendo ficheros de entrada." << std::endl;
        return 1;
    }

    SBRLogger::instancia()->setFicheroSalida(argv[3]);
    std::ofstream *salida = SBRLogger::instancia()->getFicheroSalida();
    if (!(*salida).is_open())
    {
        std::cerr << "Error abriendo ficheor salida." << std::endl;
        return 1;
    }
    std::cout << "Comenzando parseo..." << std::endl;

    std::string nombreBC = extraerNombre(argv[1]);
    (*salida) << "Nombre de la Base de Conocimientos: " << nombreBC << std::endl; // TODO: La manera correcta de imprimir en ficheor salida

    std::string nombreBH = extraerNombre(argv[2]);
    (*salida) << "Nombre de la Base de Hechos: " << nombreBH << std::endl;

    std::string line;
    std::vector<Regla *> reglas;

    int n_reglas;
    std::getline(ficheroBC, line);
    n_reglas = std::stoi(line);
    std::cout << "Parseando Base de conocimientos número de reglas a parsear " << n_reglas << std::endl;
    for (int i = 0; i < n_reglas; i++)
    {
        std::getline(ficheroBC, line);
        std::cout << "Parseando una regla" << std::endl;
        palabrasRegla = separarString(line);

        auto it2 = palabrasRegla.begin();
        std::string c;
        std::string aux;
        nuevaR = new regla();
        c = *it2; // Extraemos el antecedente
        std::cout << "Palabra actual: " << c << std::endl;
        c.erase(c.length() - 1); // Borramos los dos puntos
        nuevaR->id = c;          // Establecemos el id de la regla
        *it2++;
        while (it2 != palabrasRegla.end())
        {
            c = *it2;
            it2++;
            std::cout << "Palabra actual: " << c << std::endl;
            if (c == "Si" || c == "o" || c == "y")
            {

                // Extablecemos el tipo de la regla
                if (c == "o")
                    nuevaR->tipo = REGLA0;
                else if (c == "y")
                    nuevaR->tipo = REGLAY;

                c = *it2; // Extraemos el antecedente
                it2++;
                std::cout << "Palabra actual: " << c << std::endl;
                nuevaR->antecedentes.push_back(c); // A�adimos el antecedente en la lista de antecedentes de la regla
            }
            else if (c == "Entonces")
            {

                c = *it2; // Extraemos el antecedente
                it2++;

                std::cout << "Palabra actual: " << c << std::endl;

                c.erase(c.length() - 1); // Borramos la coma
                nuevaR->consecuente = c; // Asignamos el consecuente a la regla

                c = *it2; // Extraemos el antecedente
                it2++;
                std::cout << "Palabra actual: " << c << std::endl;
                aux.clear();
                aux = c;
                aux.erase(0, 3); // Nos quedamos con el factor de certeza de la regla

                nuevaR->fc = std::atof(aux.c_str());

                Elemento *antecedente;
                if (nuevaR->tipo == REGLAY)
                {
                    std::vector<Elemento *> precondiciones;
                    for (auto p : nuevaR->antecedentes)
                    {
                        precondiciones.push_back(contiene(p));
                    }
                    antecedente = new HechoAND(precondiciones);
                }
                else if (nuevaR->tipo == REGLA0)
                {
                    std::vector<Elemento *> precondiciones;
                    for (auto p : nuevaR->antecedentes)
                    {
                        precondiciones.push_back(contiene(p));
                    }
                    antecedente = new HechoAND(precondiciones);
                }
                else
                {
                    antecedente = contiene(nuevaR->antecedentes.front());
                }
                reglas.push_back(new Regla(nuevaR->fc,
                                           antecedente,
                                           contiene(nuevaR->consecuente),
                                           nuevaR->id)); // A�adimos la nueva regla a la base de conocimientos

                nuevaR = new regla; // Reservamos memoria para una nueva regla
            }
        }
        std::cout << line << std::endl
                  << std::endl;
    }

    std::cout << "Reglas: " << std::endl;
    for (auto reglaAux : reglas)
    {
        std::cout << "Esta regla es " << reglaAux->getNombre() << "\n\tprecondiciones: " << reglaAux->getPrecondicion()->getNombre() << "\n\tpostcondicion: " << reglaAux->getConsecuencia()->getNombre() << std::endl;
    }

    std::cout << "\nHechos: " << std::endl;
    for (auto hecho : hechos)
    {
        std::cout << "Hecho: " << hecho->getNombre() << "\n\tPrecondición: ";
        reglasAux = hecho->getReglas();
        if (reglasAux.empty())
        {
            std::cout << " vacio.";
        }
        for (size_t i = 0; i < reglasAux.size(); ++i)
        {
            std::cout << reglasAux[i]->getNombre();

            // Imprimir la coma solo si no es el último elemento
            if (i < reglasAux.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    std::getline(ficheroBH, line);
    n_reglas = std::stoi(line);
    std::cout << n_reglas << std::endl;

    std::vector<std::string> palabrasBH;
    Hecho *hechoAux;
    std::vector<Hecho *> bhInicial;
    for (int i = 0; i < n_reglas; i++)
    {
        std::getline(ficheroBH, line);
        palabrasBH = separarString(line);
        palabrasBH[0].erase(palabrasBH[0].end() - 1);
        palabrasBH[1].erase(0, 3);
        std::cout << "Parseando una FC de " << palabrasBH[0] << " -> " << palabrasBH[1] << std::endl;
        hechoAux = contiene(palabrasBH[0], false);
        if (hechoAux != nullptr)
        {
            hechoAux->setFactorCerteza(std::atof(palabrasBH[1].c_str()));
            bhInicial.push_back(hechoAux);
        }
        else
        {
            std::cout << "Error hecho no encontrado " << std::endl;
        }
    }

    std::getline(ficheroBH, line); // Esta es la linea de objetivo y no sirve para nada
    std::getline(ficheroBH, line);

    std::cout << "Calculando objetivo" << std::endl;
    objetivos = separarString(line);
    if (objetivos.size() == 1)
    {
        if (*(objetivos[0].end() - 1) == '\n' || *(objetivos[0].end() - 1) == ',')
            objetivos[0].erase(objetivos[0].end() - 1);

        hechoAux = contiene(objetivos[0]);

        (*salida) << "Objetivo: " << objetivos[0] << std::endl
                  << std::endl;
        SBRLogger::instancia()->addBH(bhInicial);
        if (hechoAux == nullptr)
        {
            std::cout << "Error, hecho objetivo no encontrado " << std::endl;
        }
        else
        {
            SBRLogger::instancia()->addMeta(hechoAux);
            hechoAux->evaluar();

            (*salida) << "Objetivo " << hechoAux->getNombre() << ", " << hechoAux->getFactorCerteza() << "\n";
        }
    }
    else
    {
        Hecho *objetivoMax = new Hecho("Dummy", -1);

        (*salida) << "Objetivo: ";
        for (size_t i = 0; i < objetivos.size(); i++)
        {
            if (*(objetivos[i].end() - 1) == '\n' || *(objetivos[i].end() - 1) == ',')
                objetivos[i].erase(objetivos[i].end() - 1);

            (*salida) << objetivos[i];

            if (i != objetivos.size() - 1)
            {
                (*salida) << ", ";
            }
        }
        (*salida) << std::endl
                  << std::endl;
        SBRLogger::instancia()->addBH(bhInicial);

        for (auto objetivo : objetivos)
        {

            hechoAux = contiene(objetivo);

            if (hechoAux == nullptr)
            {
                std::cout << "Error, hecho objetivo no encontrado " << std::endl;
            }
            else
            {
                SBRLogger::instancia()->addMeta(hechoAux);
                hechoAux->evaluar();

                if (hechoAux->getFactorCerteza() > objetivoMax->getFactorCerteza())
                {
                    objetivoMax = hechoAux;
                }
                (*salida) << std::endl;
            }
        }
        (*salida) << "Objetivo " << hechoAux->getNombre() << ", " << hechoAux->getFactorCerteza() << "\n";
    }
    // Read from the second input file and write to the output file

    // Close the file streams
    ficheroBC.close();
    ficheroBH.close();
    delete SBRLogger::instancia();

    std::cout << "Programa ha ejecutado sin explotar. La salida \"log\" se encuentra en fichero " << argv[3] << std::endl
              << "Pulsa Enter para terminar el programa.";

    // No hago los deleters porque se invocan los deletes de las clases automágicamente cuando salgo de alcance
    getchar();
    return 0; // Exit successfully
}
