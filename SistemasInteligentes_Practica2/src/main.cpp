#include <iostream>
#include <fstream>
#include <string>
#include "elemento.h"
#include "casos.h"
#include "a_sbr_logger.h"

int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file1> <input_file2> <output_file>" << std::endl;
        return 1; // Exit with an error code
    }

    // Open the input files
    std::ifstream ficheroBC(argv[1]);
    std::ifstream ficheroBH(argv[2]);

    // Check if input files are opened successfully
    if (!ficheroBC.is_open() || !ficheroBH.is_open())
    {
        std::cerr << "Error opening input files." << std::endl;
        return 1; // Exit with an error code
    }

    // Open the output file
    SBRLogger::instancia()->setFicheroSalida(argv[3]);
    std::ofstream *salida = SBRLogger::instancia()->getFicheroSalida();
    // Check if the output file is opened successfully
    if (!(*salida).is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return 1; // Exit with an error code
    }

    // Read from the first input file and write to the output file
    std::string line;
    std::vector<Regla *> reglas;
    std::vector<Elemento *> hechos;

    int n_reglas;
    std::getline(ficheroBC, line);
    n_reglas = std::stoi(line);

    while (std::getline(ficheroBC, line))
    {
        (*salida) << line << std::endl;
    }

    // Read from the second input file and write to the output file
    while (std::getline(ficheroBH, line))
    {
        (*salida) << line << std::endl;
    }

    // Close the file streams
    ficheroBC.close();
    ficheroBH.close();
    delete SBRLogger::instancia();

    std::cout << "Files successfully merged. Check the content in " << argv[3] << std::endl;

    return 0; // Exit successfully
}
