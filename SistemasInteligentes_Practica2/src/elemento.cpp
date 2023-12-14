#include "casos.h"
#include "elemento.h"
#include <algorithm>
HechoAND::HechoAND(const std::vector<Elemento *> &reglas) : reglas(reglas) {}

double HechoAND::evaluar()
{
    double min = 1;
    for (const auto &regla : reglas)
    {
        double actual = regla->evaluar();
        if (actual < min)
        {
            min = actual;
        }
    }
    return min;
}

HechoAND::~HechoAND()
{
    for (const auto &regla : reglas)
    {
        delete regla;
    }
}

HechoOR::HechoOR(const std::vector<Elemento *> &reglas) : reglas(reglas) {}

double HechoOR::evaluar()
{
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

HechoOR::~HechoOR()
{
    for (const auto &regla : reglas)
    {
        delete regla;
    }
}

Hecho::Hecho(std::string nombre, double factorCerteza) : nombre(nombre)
{
    if (factorCerteza > -1 && factorCerteza < 1)
        this->factorCerteza = factorCerteza;
    else
        this->factorCerteza = this->SIN_CALCULAR;
}

void Hecho::setFactorCerteza(double factorCerteza)
{
    this->factorCerteza = factorCerteza;
}



void Hecho::calcularFactorCerteza()
{
    if (this->reglas.empty())
    {
        std::cout << "Error en Hecho evaluar. Sin factor de certeza o reglas." << std::endl;
        this->setFactorCerteza(0);
    }
    else if (this->reglas.size() == 1)
    {
        this->setFactorCerteza(this->reglas.front()->evaluar());
    }
    else if (this->reglas.size() == 2)
    {
        this->setFactorCerteza(
            caso2(
                reglas[0]->evaluar(),
                reglas[1]->evaluar(),
                this->nombre));
    }
    else
    {
        double valor = reglas[0]->evaluar();
        for (long unsigned int i = 1; i < this->reglas.size(); i++)
        {
            valor = caso2(valor,
                          reglas[i]->evaluar(), this->nombre);
        }
        this->setFactorCerteza(valor);
    }
}

double Hecho::evaluar()
{
    if (this->factorCerteza == this->SIN_CALCULAR)
    {
        this->calcularFactorCerteza();
    }

    return this->factorCerteza;
}

std::string Hecho::getNombre() const
{
    return this->nombre;
}

void Hecho::addRegla(Regla *nuevaRegla)
{
    this->reglas.push_back(nuevaRegla);
}

void Hecho::imprimirReglas()
{
    int i = 0;
    for (const auto &regla : reglas)
    {
        i++;
        std::cout << i << " " << regla->evaluar() << std::endl;
    }
}

Regla::Regla(double factorCerteza, Elemento *hecho, Hecho *consecuencia, std::string nombre) : factorCerteza(factorCerteza),
                                                                                               hecho(hecho),
                                                                                               consecuencia(consecuencia),
                                                                                               nombre(nombre)
{
    this->consecuencia->addRegla(this);
}

double Regla::evaluar()
{
    // Caso 3
    return factorCerteza * std::max(0.0, hecho->evaluar());
}