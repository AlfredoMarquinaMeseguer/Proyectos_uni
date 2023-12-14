#ifndef CASOS_H
#define CASOS_H

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

double caso2(double valor1, double valor2, std::string nombre, bool dentroRegla = false);
double caso1AND(const std::vector<Elemento *> &reglas, bool dentroRegla = false);
double caso1OR(const std::vector<Elemento *> &reglas, bool dentroRegla = false);

#endif // CASOS_H