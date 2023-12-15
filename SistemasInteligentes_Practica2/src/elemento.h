#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>
#include <vector>

// Clase base para todas las reglas
class Elemento
{
protected:
    double factorCerteza;

public:
    static constexpr double SIN_CALCULAR = 69.0;
    Elemento(double factorCerteza = SIN_CALCULAR) : factorCerteza(factorCerteza){};
    // std::string getNombre();
    virtual double evaluar() = 0;
    virtual std::string getNombre() = 0;
    double getFactorCerteza() { return this->factorCerteza; };
    virtual std::vector<std::string> annadirNuevasMetas() = 0;
    virtual ~Elemento() {} // Destructor virtual para la herencia
};

class Hecho;

// Elemento compuesta que combina varias reglas con operador AND
class HechoAND : public Elemento
{
private:
    std::vector<Elemento *> hechos;
    std::string nombre;

public:
    HechoAND(const std::vector<Elemento *> &hechos);
    double evaluar();
    std::string getNombre() override;
    std::vector<std::string> annadirNuevasMetas() override;
    std::vector<Elemento *> getHechos();
    ~HechoAND() override;
};

// Elemento compuesta que combina varias reglas con operador OR
class HechoOR : public Elemento
{
private:
    std::vector<Elemento *> hechos;
    std::string nombre;

public:
    HechoOR(const std::vector<Elemento *> &hechos);
    double evaluar();
    std::string getNombre() override;
    std::vector<Elemento *> getHechos();
    std::vector<std::string> annadirNuevasMetas() override;
    ~HechoOR() override;
};

class Regla : public Elemento
{
private:
    Elemento *hecho;
    Hecho *consecuencia;
    std::string nombre;

public:
    std::string getNombre() override;
    Regla(double factorCerteza, Elemento *hecho, Hecho *consecuencia, std::string nombre);
    double evaluar();
    Hecho *getConsecuencia();
    std::vector<std::string> annadirNuevasMetas() override;
    Elemento *getPrecondicion();
};

// Elemento simple que verifica una condición específica
class Hecho : public Elemento
{
private:
    std::string nombre;
    std::vector<Regla *> reglas;

    void calcularFactorCerteza();

public:
    Hecho(std::string nombre, double factorCerteza = SIN_CALCULAR);
    void setFactorCerteza(double factorCerteza);
    double evaluar();
    std::string getNombre() override;
    void addRegla(Regla *nuevaRegla);
    void imprimirReglas();
    std::vector<std::string> annadirNuevasMetas() override;
};

#endif // ELEMENTO_H
