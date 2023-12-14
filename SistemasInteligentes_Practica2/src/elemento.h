#ifndef ELEMENTO_H 
#define ELEMENTO_H

#include <iostream>
#include <vector>

// Clase base para todas las reglas
class Elemento
{
/*
protected:
    double factorCerteza;

    void setFactorCerteza(double factorCerteza);
*/
public:
    // std::string getNombre();
    virtual double evaluar() = 0;
    virtual ~Elemento() {} // Destructor virtual para la herencia
};

class Hecho;

// Elemento compuesta que combina varias reglas con operador AND
class HechoAND : public Elemento
{
private:
    std::vector<Elemento *> reglas;

public:
    HechoAND(const std::vector<Elemento *> &reglas);
    double evaluar() ;
    ~HechoAND() override;
};

// Elemento compuesta que combina varias reglas con operador OR
class HechoOR : public Elemento
{
private:
    std::vector<Elemento *> reglas;

public:
    HechoOR(const std::vector<Elemento *> &reglas);
    double evaluar() ;
    ~HechoOR() override;

};


class Regla : public Elemento
{
    private:
        double factorCerteza;
        Elemento * hecho;
        Hecho * consecuencia;
        std::string nombre;
    public:
        Regla(double factorCerteza, Elemento * hecho, Hecho * consecuencia, std::string nombre);
        double evaluar() ;
};

// Elemento simple que verifica una condición específica
class Hecho : public Elemento
{
private:
    double factorCerteza;
    std::string nombre;
    std::vector<Regla*> reglas;

    void calcularFactorCerteza() ;
public:
    static constexpr double SIN_CALCULAR = 69.0;
    Hecho(std::string nombre, double factorCerteza = SIN_CALCULAR);
    void setFactorCerteza(double factorCerteza);
    double evaluar() ;
    std::string getNombre() const;
    void addRegla(Regla* nuevaRegla);
    void imprimirReglas();
};



#endif // ELEMENTO_H
