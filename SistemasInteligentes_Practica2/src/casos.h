#ifndef CASOS_H
#define CASOS_H

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "elemento.h"

double caso2(double valor1, double valor2, std::string nombre);
double caso1(HechoAND * hechoAND);
double caso1(HechoOR * hechoOR);
double caso3(Regla * regla);
#endif // CASOS_H