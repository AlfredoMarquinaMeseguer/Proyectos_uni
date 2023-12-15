#ifndef A_SBR_LOGGER
#define A_SBR_LOGGER

#include "elemento.h"
#include "casos.h"
#include <vector>
#include <string>
#include <iostream>

struct bh_element
{
    std::string nombre;
    double factorCerteza;
};

class SBRLogger
{
    std::vector<Hecho *> nuevasMetas;
    std::vector<Hecho *> bh;
    std::vector<Regla *> cc;
    int n_tabuladores;
    static SBRLogger *s_instancia;

    SBRLogger(int n_tabuladores);

    void imprimirTabuladores();

public:
    int getNTabuladores();

    void addMeta(Hecho *nuevaMeta);
    void addMeta(std::vector<Hecho *> metas);
    void addBH(Hecho *bh);
    void addBH(std::vector<Hecho *> elems);
    void addCC(Regla *cc);
    void addCC(std::vector<Regla *> elems);

    void eliminarMeta();
    void eliminarCC();
    void aplicarRegla(Regla * regla);
    void aplicarRegla();

    void usoCaso1(Elemento * hechoCompuesto);
    void usoCaso2(Regla *antecedente1, Regla *antecedente2, Hecho *consecuencia);
    void usoCaso3(Regla * regla);

    void imprimirNuevasMetas();
    void imprimirBH();
    void imprimirBHContenido();
    void imprimirCC();

    void reset(bool usarLogger = true, int n_tabuladores = 0);
    static SBRLogger *instancia();
    ~SBRLogger();
};
#endif