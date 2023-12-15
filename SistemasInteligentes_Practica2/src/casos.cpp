#include "casos.h"
#include "elemento.h"
#include "a_sbr_logger.h"

double caso2(double valor1, double valor2, std::string nombre)
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
    // TODO meter en el logger
    std::cout << "Caso 2: " << nombre << ", " << sol << std::endl;

    return sol;
}

double caso1(HechoAND *hechoAND)
{
    double min = 1;
    for (const auto &regla : hechoAND->getHechos())
    {
        double actual = regla->evaluar();
        if (actual < min)
        {
            min = actual;
        }
    }
    // TODO encontrar convención de poner nombre
    SBRLogger::instancia()->usoCaso1(hechoAND);
    return min;
}

double caso1(HechoOR *hechoOR)
{
    double max = -1;
    for (const auto &regla : hechoOR->getHechos())
    {
        double actual = regla->evaluar();
        if (actual > max)
        {
            max = actual;
        }
    }
    SBRLogger::instancia()->usoCaso1(hechoOR);
    return max;
}

double caso3(Regla *regla)
{
    double sol = regla->getFactorCerteza() * std::max(0.0, regla->getPrecondicion()->evaluar());
    regla->getConsecuencia()->setFactorCerteza(sol);
    SBRLogger::instancia()->usoCaso3(regla);
    return sol;
}
