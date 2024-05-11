#include <iostream>
#include <climits>
using namespace std;

int *backtracking_v2(int *candidatos, int n) {
  int elementosSelecionados = 0, sumaActual = 0;
  int *elementosActuales = new int[n];
  int *solucion = new int[n];
  float diferenciaMin = INT_MAX;
  float suma = 0;
  bool mejorSol = false;

  for (int i = 0; i < n; i++) {
    suma += candidatos[i];
    elementosActuales[i] = -1;
  }
  elementosActuales[0] = 0;


  int nivel = 1;
  // Condición de todas las posibilidades y segunda condición de solución

  float minimo = n % 2 / 2.0;

  elementosSelecionados = 0;
  sumaActual = 0;
  do {

    // Generar
    elementosActuales[nivel] += 1;
    sumaActual += candidatos[nivel] * elementosActuales[nivel]; // Bact
    elementosSelecionados += elementosActuales[nivel];  // Pact
    // Solucion
    if (nivel + 1 == n &&
        (elementosSelecionados == n / 2 ||
         elementosSelecionados == n / 2 + n % 2) &&
        std::abs((suma / 2) - sumaActual) < diferenciaMin) // bact > voa
    {

      diferenciaMin = std::abs((suma / 2) - sumaActual);
      for (int j = 0; j < n; j++)
        solucion[j] = elementosActuales[j];

      // Poda extra
      if (diferenciaMin == minimo) {
        mejorSol = true;
      }
    }
    // Criterio
    if (nivel + 1 < n){
      nivel++;
    } else {
      // Mas hermanos
      while (!elementosActuales[nivel] < 1) {
        elementosSelecionados -= elementosActuales[nivel];
        sumaActual -= candidatos[nivel] * elementosActuales[nivel]; // Bact
        elementosActuales[nivel] = -1;
        nivel--;
      }
    }

  } while (nivel != 0  and !mejorSol); // hasta nivel == 0 + poda
   

  delete elementosActuales;
  return solucion;
}

void resolver_v2(int *candidatos, int n) {
  int *solucion = backtracking_v2(candidatos, n);
  
  int total1 = 0;
  int total2 = 0;
  for (int i = 0; i < n; i++) {
    if (solucion[i] == 1) {
      total1 += candidatos[i];
    } else {
      total2 += candidatos[i];
    }
  }

  if (total1 < total2) {
    std::cout << total1 << " " << total2 << std::endl;
  } else {
    std::cout << total2 << " " << total1 << std::endl;
  }
  delete solucion;
  
}

int main() {
  int problemas, numCandidatos, candidatoActual;
  // Entrada
  cin >> problemas;
  while (problemas--) {
    cin >> numCandidatos;

    int *candidatos = new int[numCandidatos];
    for (int j = 0; j < numCandidatos; ++j) {
      cin >> candidatoActual;
      candidatos[j] = candidatoActual;
    }
    // resolver(candidatos, numCandidatos);
    resolver_v2(candidatos, numCandidatos);
    delete candidatos;
  }
  return 0;
}
