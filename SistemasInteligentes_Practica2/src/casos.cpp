#include "casos.h"
#include "elemento.h"

double caso2(double valor1, double valor2, std::string nombre, bool dentroRegla = false)
{
    double sol;

    if (valor1 >= 0 && valor2 >= 0)
    {
        sol = valor1 + valor2 * (1 - valor1);
    }
    else if (valor1 <= 0 && valor2 <= 0)
    {
        sol = valor1 + valor2 * (1 + valor1);
    }
    else
    {
        sol = (valor1 + valor2) / (1.0 - std::min(std::abs(valor1), std::abs(valor2)));
    }

    if (dentroRegla) std::cout << "\t";
    std::cout << "Caso 2: " << nombre << ", " << sol << std::endl;

    return sol;
}

double caso1AND(const std::vector<Elemento *> &reglas, bool dentroRegla = false){
 double min = 1;
    for (const auto &regla : reglas)
    {
        double actual = regla->evaluar();
        if (actual < min)
        {
            min = actual;
        }
    }
    // TODO encontrar convención de poner nombre
    std::cout << "Caso 1: " << "hecho" << ", " << min << std::endl;
    return min;
}

double caso1OR(const std::vector<Elemento *> &reglas, bool dentroRegla = false){
 double max = -1;
    for (const auto &regla : reglas)
    {
        double actual = regla->evaluar();
        if (actual > max)
        {
            max = actual;
        }
    }
    return max;
}
