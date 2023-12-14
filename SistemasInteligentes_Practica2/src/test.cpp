#include "elemento.h"

int main()
{
    // Ejemplo de uso
    Elemento *reglaCompuesta = new HechoAND({new Hecho("A", 0.8),
                                             new HechoOR({new Hecho("B", 0.5),
                                                          new Hecho("C", 0.7)})});

    std::cout << "La salida es " << reglaCompuesta->evaluar() << " Patata" << std::endl;

    // Liberar memoria
    delete reglaCompuesta;
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