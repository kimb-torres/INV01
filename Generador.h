#ifndef GENERADOR_H
#define GENERADOR_H
#include <random>
#include <string>
#include <vector>
#include "Tarea.h"

const int ESFUERZO_MIN = 1;
const int ESFUERZO_MAX = 8;
const double PROB_COMPLETADA = 0.30;

const double PROB_TAREA_RAIZ = 0.10;
const int PROFUNDIDAD_MAXIMA = 4;

struct Generador {
    std::mt19937 aMotor;

    Generador(unsigned int nSemilla) : aMotor(nSemilla) {}

    int Entero(int nMin, int nMax) {
        std::uniform_int_distribution<int> dist(nMin, nMax);
        return dist(aMotor);
    }

    bool Probabilidad(double nP) {
        std::bernoulli_distribution dist(nP);
        return dist(aMotor);
    }

    Tarea NuevaTarea(int nId, int nIdPadre) {
        Tarea t;
        t.id = nId;
        t.idPadre = nIdPadre;
        t.nombre = "Tarea " + std::to_string(nId);
        t.esfuerzo = Entero(ESFUERZO_MIN, ESFUERZO_MAX);
        t.completada = Probabilidad(PROB_COMPLETADA);
        return t;
    }

    std::vector<Tarea> CargaBase(int n) {
        std::vector<Tarea> tareas;
        for (int i = 1; i <= n; i++) tareas.push_back(NuevaTarea(i, 0));
        return tareas;
    }

    std::vector<Tarea> CargaModificada(int n) {
        std::vector<Tarea> tareas;
        std::vector<int> profundidad(n + 1, 0);
        std::vector<int> candidatos;

        for (int i = 1; i <= n; i++) {
            int padre = 0;
            if (i > 1 && !candidatos.empty() && !Probabilidad(PROB_TAREA_RAIZ)) {
                padre = candidatos[Entero(0, (int)candidatos.size() - 1)];
            }
            profundidad[i] = (padre == 0) ? 1 : profundidad[padre] + 1;
            if (profundidad[i] < PROFUNDIDAD_MAXIMA) candidatos.push_back(i);
            tareas.push_back(NuevaTarea(i, padre));
        }
        return tareas;
    }
};

#endif
