#include "casos.h"
#include "elemento.h"
#include "a_sbr_logger.h"
#include <algorithm>
HechoAND::HechoAND(const std::vector<Elemento *> &hechos) : hechos(hechos) {}

double HechoAND::evaluar()
{
    if (this->factorCerteza == Elemento::SIN_CALCULAR)
    {
        this->factorCerteza = caso1(this);
        SBRLogger::instancia()->usoCaso1(this);
    }

    return factorCerteza;
}

std::string HechoAND::getNombre()
{
    if (!this->nombre.empty())
        return this->nombre;

    std::string nombre = "";

    for (size_t i = 0; i < this->hechos.size(); ++i)
    {
        nombre.append(this->hechos[i]->getNombre());

        // Imprimir la coma solo si no es el último elemento
        if (i < this->hechos.size() - 1)
        {
            nombre.append(" y ");
        }
    }

    this->nombre = nombre;
    return nombre;
}
std::vector<Hecho *> HechoAND::annadirNuevasMetas()
{
    std::vector<Hecho *> nuevasMetas = {};
    std::vector<Hecho *> sublista;
    for (const auto &regla : this->hechos)
    {
        sublista = regla->annadirNuevasMetas();
        nuevasMetas.insert(nuevasMetas.end(), sublista.begin(), sublista.end());
    }
    return nuevasMetas;
}
std::vector<Elemento *> HechoAND::getHechos()
{
    return this->hechos;
}
HechoAND::~HechoAND()
{
    for (const auto &regla : hechos)
    {
        delete regla;
    }
}

HechoOR::HechoOR(const std::vector<Elemento *> &hechos) : hechos(hechos) {}

double HechoOR::evaluar()
{
    if (this->factorCerteza == Elemento::SIN_CALCULAR)
    {
        this->factorCerteza = caso1(this);
        SBRLogger::instancia()->usoCaso1(this);
    }

    return factorCerteza;
}

std::string HechoOR::getNombre()
{
    if (!this->nombre.empty())
        return this->nombre;

    std::string nombre = "";

    for (size_t i = 0; i < this->hechos.size(); ++i)
    {
        nombre.append(this->hechos[i]->getNombre());

        // Imprimir la coma solo si no es el último elemento
        if (i < this->hechos.size() - 1)
        {
            nombre.append(" o ");
        }
    }

    this->nombre = nombre;
    return nombre;
}

std::vector<Elemento *> HechoOR::getHechos()
{
    return this->hechos;
}

std::vector<Hecho *> HechoOR::annadirNuevasMetas()
{
    std::vector<Hecho *> nuevasMetas = {};
    std::vector<Hecho *> sublista;
    for (const auto &regla : this->hechos)
    {
        sublista = regla->annadirNuevasMetas();
        nuevasMetas.insert(nuevasMetas.end(), sublista.begin(), sublista.end());
    }
    return nuevasMetas;
}

HechoOR::~HechoOR()
{
    for (const auto &regla : hechos)
    {
        delete regla;
    }
}

Regla::Regla(double factorCerteza, Elemento *hecho, Hecho *consecuencia, std::string nombre) : Elemento(factorCerteza),
                                                                                               hecho(hecho),
                                                                                               consecuencia(consecuencia),
                                                                                               nombre(nombre)
{
    this->consecuencia->addRegla(this);
}

double Regla::evaluar() // TODO: ponerlo con el logger correcto
{
    SBRLogger::instancia()->aplicarRegla(this);
    SBRLogger::instancia()->addMeta(this->hecho->annadirNuevasMetas());
    // Caso 3
    double a = caso3(this);

    return a;
}

std::string Regla::getNombre()
{
    return this->nombre;
}

Hecho *Regla::getConsecuencia()
{
    return this->consecuencia;
}

std::vector<Hecho *> Regla::annadirNuevasMetas()
{
    return {};
}

Elemento *Regla::getPrecondicion()
{
    return this->hecho;
}

Hecho::Hecho(std::string nombre, double factorCerteza) : nombre(nombre)
{
    if (factorCerteza == Elemento::SIN_CALCULAR)
    {
        this->factorCerteza = Elemento::SIN_CALCULAR;
    }
    if (factorCerteza > -1 && factorCerteza < 1)
    {
        this->factorCerteza = factorCerteza;
    }
    else
    {
        this->factorCerteza = this->SIN_CALCULAR;
    }
}

void Hecho::setFactorCerteza(double factorCerteza)
{
    this->factorCerteza = factorCerteza;
}

void Hecho::calcularFactorCerteza()
{
    if (this->reglas.empty())
    {
        std::cout << "Error en Hecho evaluar/calcularFactorCerteza. Ni factor de certeza ni reglas." << std::endl;
        this->setFactorCerteza(0);
    }
    else if (this->reglas.size() == 1)
    {
        SBRLogger::instancia()->addCC(reglas);
        this->setFactorCerteza(this->reglas.front()->evaluar());
    }
    else if (this->reglas.size() == 2)
    {
        SBRLogger::instancia()->addCC(reglas);
        this->setFactorCerteza(
            caso2(
                this->reglas[0]->evaluar(),
                this->reglas[1]->evaluar(),
                this->nombre));
        SBRLogger::instancia()->usoCaso2(this->reglas[0],
                                         this->reglas[1],
                                         this);
    }
    else // TODO: PONER el logger
    {
        SBRLogger::instancia()->addCC(reglas);
        double valor = reglas[0]->evaluar();
        for (long unsigned int i = 1; i < this->reglas.size(); i++)
        {
            valor = caso2(valor,
                          reglas[i]->evaluar(), 
                          this->nombre);
        }
        this->setFactorCerteza(valor);
    }
    SBRLogger::instancia()->addBH(this);
}

double Hecho::evaluar()
{
    SBRLogger::instancia()->eliminarMeta(this);
    if (this->factorCerteza == this->SIN_CALCULAR)
    {
        this->calcularFactorCerteza();
    }

    return this->factorCerteza;
}

std::string Hecho::getNombre()
{
    return this->nombre;
}

std::vector<Hecho *> Hecho::annadirNuevasMetas()
{
    return {this};
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
