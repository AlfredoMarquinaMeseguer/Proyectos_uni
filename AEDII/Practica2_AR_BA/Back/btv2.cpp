#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Solucion {
    vector<int> equipoA;
    vector<int> equipoB;
};

int diferencia(Solucion equipos) {
    int a = 0;
    for (const int& element : equipos.equipoA) {
        a += element;
    }
    int b = 0;
    for (const int& element : equipos.equipoB) {
        b += element;
    }
    return abs(a - b);
}

Solucion* backtracking(vector<int>& candidatos, const Solucion& equipos, int mitadCandidatos, int alfa, int beta) {
    if (candidatos.empty()) {
        if (equipos.equipoA.size() < equipos.equipoB.size() - 1 || equipos.equipoA.size() > equipos.equipoB.size() + 1) {
            return nullptr;
        } else {
            return new Solucion(equipos);
        }
    }else if (equipos.equipoA.size() > mitadCandidatos || equipos.equipoB.size() > mitadCandidatos){
        return nullptr;
    }

    Solucion* solucion = nullptr;
    int difer = numeric_limits<int>::max();
    vector<int> copia_candidatos(candidatos);

    int participante = copia_candidatos[0];
    copia_candidatos.erase(copia_candidatos.begin());

    Solucion copia_equipos(equipos);
    copia_equipos.equipoA.push_back(participante);

    Solucion* pretendiente1 = nullptr;
    if (difer > alfa) {
        pretendiente1 = backtracking(copia_candidatos, copia_equipos, mitadCandidatos, alfa, beta);
        if (pretendiente1 != nullptr && (solucion == nullptr || diferencia(*pretendiente1) < difer)) {
            delete solucion;
            solucion = pretendiente1;
            difer = diferencia(*solucion);
        } else {
            delete pretendiente1;
        }
        alfa = max(alfa, difer);
        if (alfa >= beta) {
            return solucion;
        }
    }

    Solucion copia_equipos2(equipos);
    copia_equipos2.equipoB.push_back(participante);

    Solucion* pretendiente2 = nullptr;
    if (difer > alfa) {
        pretendiente2 = backtracking(copia_candidatos, copia_equipos2, mitadCandidatos, alfa, beta);
        if (pretendiente2 != nullptr && (solucion == nullptr || diferencia(*pretendiente2) < difer)) {
            delete solucion;
            solucion = pretendiente2;
            difer = diferencia(*solucion);
        } else {
            delete pretendiente2;
        }
        alfa = max(alfa, difer);
        if (alfa >= beta) {
            return solucion;
        }
    }

    return solucion;

}

int main() {
    int problemas, numCandidatos, candidatoActual, pesoA, pesoB;
    //vector<int> cant = {450, 106, 87, 66, 75, 372, 215, 6, 304, 291, 25, 88, 133, 221, 85, 108, 105, 381, 323, 352, 130, 100};
    vector<int> candidatos;
    vector<int> candidatos2 = {450, 106, 87, 66, 75, 372, 215, 6, 304, 291, 25, 88, 133, 221, 85, 108, 105, 381, 323, 352, 130, 100};
    //Solucion a{{450, 106, 87, 66, 75, 372, 215, 25, 133, 352, 130},
              // {6, 304, 291, 88, 221, 85, 108, 105, 381, 323, 100}};
    //Solucion a{{100, 90},{200}};
    // cout << "Cantidad de candidatos: " << candidatos2.size() << endl;

    double inf = std::numeric_limits<double>::infinity();
    // Entrada
    cin >> problemas;
    // cin.getline();
    // getline(aux, cin);
    for(int i =0; i<problemas; ++i) {
        cin >> numCandidatos;
        candidatos = {};
        for(int j=0; j< numCandidatos; ++j) {
            cin >> candidatoActual;
            candidatos.push_back(candidatoActual);
        }
        // getline(aux, cin);
        // Fin Entrada

        Solucion equipos{{}, {}};
        auto solucion = backtracking(candidatos, equipos, (candidatos.size()/2) + (candidatos.size()%2), -inf, inf);
        if (solucion == nullptr) {
            // No debería ocurrir nunca
            cout << "No se encontro solucion" << endl;
        } else {
            // cout << "Equipo A: ";
            pesoA = 0;
            for (const int &elem : solucion->equipoA) {
                // cout << elem << " ";
                pesoA += elem;
            }
            // cout << endl << "Equipo B: ";
            pesoB = 0;
            for (const int &elem : solucion->equipoB) {
                // cout << elem << " ";
                pesoB += elem;
            }
            // cout << endl << "Diferencia: " << diferencia(*solucion) << endl;

            if (pesoA < pesoB)
                cout << pesoA << " " << pesoB << endl;
            else
                cout << pesoB << " " << pesoA << endl;

        }
        delete solucion;
        // delete &equipos;
        // delete &candidatos;
    }

    return 0;
}
