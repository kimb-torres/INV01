#ifndef ARBOL_H
#define ARBOL_H
#include "NodoArbol.h"

template <typename Dato>
class Arbol {
private:
    NodoArbol<Dato> *apRaiz;
    long long aVisitados;
    long long aComparaciones;

    void VaciarArbol(NodoArbol<Dato> *pNodo) {
        if (pNodo == nullptr) return;
        NodoArbol<Dato> *pHijo = pNodo->PrimerHijo();
        while (pHijo != nullptr) {
            NodoArbol<Dato> *pSiguiente = pHijo->SiguienteHermano();
            VaciarArbol(pHijo);
            pHijo = pSiguiente;
        }
        delete pNodo;
    }

    NodoArbol<Dato>* BuscarNodo(NodoArbol<Dato> *pNodo, int nId) {
        if (pNodo == nullptr) return nullptr;
        aVisitados++;
        aComparaciones++;
        if (pNodo->aDato.id == nId) return pNodo;

        NodoArbol<Dato> *pHijo = pNodo->PrimerHijo();
        while (pHijo != nullptr) {
            NodoArbol<Dato> *pEncontrado = BuscarNodo(pHijo, nId);
            if (pEncontrado != nullptr) return pEncontrado;
            pHijo = pHijo->SiguienteHermano();
        }
        return nullptr;
    }

    int SumarSubarbol(NodoArbol<Dato> *pPrimero) {
        int suma = 0;
        NodoArbol<Dato> *pActual = pPrimero;
        while (pActual != nullptr) {
            aVisitados++;
            if (!pActual->aDato.completada) suma += pActual->aDato.esfuerzo;
            suma += SumarSubarbol(pActual->PrimerHijo());
            pActual = pActual->SiguienteHermano();
        }
        return suma;
    }

    void InsertarHijo(NodoArbol<Dato> *pPadre, NodoArbol<Dato> *pNuevo) {
        pNuevo->AsignarPadre(pPadre);

        NodoArbol<Dato> *pActual = pPadre->PrimerHijo();
        if (pActual == nullptr) {
            pPadre->AsignarPrimerHijo(pNuevo);
            return;
        }
        while (pActual->SiguienteHermano() != nullptr) {
            pActual = pActual->SiguienteHermano();
        }
        pActual->AsignarSiguienteHermano(pNuevo);
    }

public:
    Arbol() {
        Dato raiz = Dato();
        raiz.id = 0;
        raiz.idPadre = -1;
        raiz.esfuerzo = 0;
        raiz.completada = true;
        apRaiz = new NodoArbol<Dato>(raiz);
        aVisitados = 0;
        aComparaciones = 0;
    }

    ~Arbol() {
        VaciarArbol(apRaiz);
    }

    NodoArbol<Dato>* ObtenerRaiz() {
        return apRaiz;
    }

    bool Insertar(const Dato &nDato) {
        NodoArbol<Dato> *pPadre = BuscarNodo(apRaiz, nDato.idPadre);
        if (pPadre == nullptr) return false;
        InsertarHijo(pPadre, new NodoArbol<Dato>(nDato));
        return true;
    }

    Dato* BuscarPorId(int nId) {
        if (nId == 0) return nullptr;
        NodoArbol<Dato> *pNodo = BuscarNodo(apRaiz, nId);
        if (pNodo == nullptr) return nullptr;
        return &(pNodo->aDato);
    }

    int EsfuerzoPendiente(int nId) {
        if (nId == 0) return -1;
        NodoArbol<Dato> *pNodo = BuscarNodo(apRaiz, nId);
        if (pNodo == nullptr) return -1;
        return SumarSubarbol(pNodo->PrimerHijo());
    }

    void ReiniciarContadores() {
        aVisitados = 0;
        aComparaciones = 0;
    }

    long long ObtenerVisitados() const {
        return aVisitados;
    }

    long long ObtenerComparaciones() const {
        return aComparaciones;
    }
};

#endif
