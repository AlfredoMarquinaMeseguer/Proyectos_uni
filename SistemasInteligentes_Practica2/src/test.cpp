#include "elemento.h"

int main()
{
    // Ejemplo de uso
    std::cout << "Comenzando Programa" << std::endl;
    Hecho *q = new Hecho("A", 0.8);
    std::cout << "Se ha creado el Hecho A " << q->getNombre() << " FC=" << q->evaluar() << std::endl;

    Hecho *w = new Hecho("B", 0.5);
    std::cout << "Se ha creado el Hecho B " << w->getNombre() << " FC=" << w->evaluar()<< std::endl;

    HechoOR *  o = new HechoOR({q, w});
    std::cout << "Se ha creado el HechoOR  " << o->getNombre() << " FC= "<< o->evaluar() << std::endl;

    HechoAND * e = new HechoAND({q,w});
    std::cout << "Se ha creado el HechoAND " << e->getNombre() << " FC= "<< e->evaluar() << std::endl;

    Hecho * r = new Hecho("C");
    std::cout << "Se ha creado el Hecho A " << q->getNombre() << std::endl;

    Regla * regla = new Regla(0.5, e, r, "R1");
std::cout << "Se ha creado la Regla " << regla -> getNombre() << " FC= " << regla->evaluar() <<std::endl;

    // Liberar memoria
    Hecho *c = new Hecho("D");
    Regla *a = new Regla(0.8, new Hecho("A", 0.8), c, "R1");
    Regla *b = new Regla(0.8, new Hecho("A", -0.8), c, "R2");
    std::cout << "La regla es " << a->evaluar() << " " << b->evaluar() << std::endl;

    c->imprimirReglas();
    c->evaluar();
    std::cout << "Valor de " << c->getNombre() << " " << c->evaluar() << std::endl;

    std::cout << "\n\n\tTest ejercicio de Sherlock" << std::endl;

    // Simulamos BC

    Hecho *liw = new Hecho("li_w");
    Hecho *lig = new Hecho("li_g");
    Hecho *s = new Hecho("s");
    HechoAND *hechoand = new HechoAND({lig, s});
    Hecho *hecho_a = new Hecho("a");
    Regla *r1 = new Regla(0.5, liw, hecho_a, "R1");
    Regla *r2 = new Regla(0.9, hechoand, hecho_a, "R2");
    Hecho *final = new Hecho("R");
    Regla *r3 = new Regla(0.99, hecho_a, final, "R3");

    // Aquí simulamos BH

    liw->setFactorCerteza(1.0);
    lig->setFactorCerteza(1.0);
    s->setFactorCerteza(0.5);

    double resultado = final->evaluar();

    std::cout << "Objetivo " << resultado << std::endl;

    return 0;
}