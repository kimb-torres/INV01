#ifndef REFERENCIA_H
#define REFERENCIA_H
#include <vector>
#include "Tarea.h"

struct Referencia {
    std::vector<Tarea> aTareas;
    std::vector<std::vector<int> > aHijos;

    Referencia(const std::vector<Tarea> &nTareas) {
        aTareas = nTareas;
        aHijos.assign(nTareas.size() + 1, std::vector<int>());
        for (size_t i = 0; i < nTareas.size(); i++) {
            aHijos[nTareas[i].idPadre].push_back(nTareas[i].id);
        }
    }

    bool Existe(int nId) const {
        return nId >= 1 && nId <= (int)aTareas.size();
    }

    int EsfuerzoPendiente(int nId) const {
        if (!Existe(nId)) return -1;
        int suma = 0;
        std::vector<int> pila(aHijos[nId]);
        while (!pila.empty()) {
            int id = pila.back();
            pila.pop_back();
            const Tarea &t = aTareas[id - 1];
            if (!t.completada) suma += t.esfuerzo;
            for (size_t k = 0; k < aHijos[id].size(); k++) pila.push_back(aHijos[id][k]);
        }
        return suma;
    }

    int CantidadDescendientes(int nId) const {
        if (!Existe(nId)) return 0;
        int total = 0;
        std::vector<int> pila(aHijos[nId]);
        while (!pila.empty()) {
            int id = pila.back();
            pila.pop_back();
            total++;
            for (size_t k = 0; k < aHijos[id].size(); k++) pila.push_back(aHijos[id][k]);
        }
        return total;
    }

    int Profundidad(int nId) const {
        int p = 0;
        while (nId != 0) {
            p++;
            nId = aTareas[nId - 1].idPadre;
        }
        return p;
    }
};

#endif
