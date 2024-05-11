#include <iostream>
#include <vector>

// Clase base para todas las reglas
class Hecho
{
public:
    virtual double evaluar() const = 0;
    virtual ~Hecho() {} // Destructor virtual para la herenciaehc
};

// Hecho compuesta que combina varias reglas con operador AND
class HechoAND : public Hecho
{
private:
    std::vector<Hecho *> reglas;

public:
    HechoAND(const std::vector<Hecho *> &reglas) : reglas(reglas) {}

    double evaluar() const override
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

    ~HechoAND() override
    {
        for (const auto &regla : reglas)
        {
            delete regla;
        }
    }
};

// Hecho compuesta que combina varias reglas con operador OR
class HechoOR : public Hecho
{
private:
    std::vector<Hecho *> reglas;

public:
    HechoOR(const std::vector<Hecho *> &reglas) : reglas(reglas) {}

    double evaluar() const override
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

    ~HechoOR() override
    {
        for (const auto &regla : reglas)
        {
            delete regla;
        }
    }
};

// Hecho simple que verifica una condición específica
class HechoSimple : public Hecho
{
private:
    double factorCerteza;
    std::string nombre;

public:
    HechoSimple(std::string nombre, double factorCerteza) : nombre(nombre)
    {
        if (factorCerteza < -1)
        {
            this->factorCerteza = -1;
        }
        else if (factorCerteza > 1)
        {
            this->factorCerteza = 1;
        }
        else
        {
            this->factorCerteza = factorCerteza;
        }
    }

    HechoSimple(std::string nombre) : HechoSimple(nombre, 0) {}

    void setFactorCerteza(double factorCerteza)
    {
        this->factorCerteza = factorCerteza;
    }
    double evaluar() const override
    {
        return factorCerteza;
    }
};
