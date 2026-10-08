#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"

template <typename Dato>
class Lista {
private:
    Nodo<Dato> *apPrimero;
    Nodo<Dato> *apUltimo;
    int aSiguienteId;
    int aCantidad;
    long long aVisitados;
    long long aComparaciones;

    int SumarDescendientes(int nIdPadre) {
        int suma = 0;
        Nodo<Dato> *pActual = apPrimero;
        while (pActual != nullptr) {
            aVisitados++;
            aComparaciones++;
            if (pActual->aDato.idPadre == nIdPadre) {
                if (!pActual->aDato.completada) suma += pActual->aDato.esfuerzo;
                suma += SumarDescendientes(pActual->aDato.id);
            }
            pActual = pActual->apSiguiente;
        }
        return suma;
    }

public:
    Lista() {
        apPrimero = nullptr;
        apUltimo = nullptr;
        aSiguienteId = 1;
        aCantidad = 0;
        aVisitados = 0;
        aComparaciones = 0;
    }

    ~Lista() {
        VaciarLista();
    }

    void VaciarLista() {
        while (apPrimero != nullptr) {
            Nodo<Dato> *pAuxiliar = apPrimero;
            apPrimero = apPrimero->apSiguiente;
            delete pAuxiliar;
        }
        apUltimo = nullptr;
        aCantidad = 0;
    }

    void AgregarInicio(const Dato &nDato) {
        Nodo<Dato> *pNuevo = new Nodo<Dato>(nDato, aSiguienteId++);
        pNuevo->apSiguiente = apPrimero;
        apPrimero = pNuevo;
        if (apUltimo == nullptr) apUltimo = pNuevo;
        aCantidad++;
    }

    void AgregarFinal(const Dato &nDato) {
        Nodo<Dato> *pNuevo = new Nodo<Dato>(nDato, aSiguienteId++);
        if (apPrimero == nullptr) {
            apPrimero = pNuevo;
            apUltimo = pNuevo;
        } else {
            apUltimo->apSiguiente = pNuevo;
            apUltimo = pNuevo;
        }
        aCantidad++;
    }

    Dato* BuscarPorId(int nId) {
        Nodo<Dato> *pActual = apPrimero;
        while (pActual != nullptr) {
            aVisitados++;
            aComparaciones++;
            if (pActual->aDato.id == nId) return &(pActual->aDato);
            pActual = pActual->apSiguiente;
        }
        return nullptr;
    }

    int EsfuerzoPendiente(int nId) {
        if (BuscarPorId(nId) == nullptr) return -1;
        return SumarDescendientes(nId);
    }

    bool EstaVacia() const {
        return apPrimero == nullptr;
    }

    int Elementos() const {
        return aCantidad;
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

    bool EliminarDato(int nId) {
        if (EstaVacia()) return false;

        Nodo<Dato> *pActual = apPrimero;
        Nodo<Dato> *pAnterior = nullptr;
        while (pActual != nullptr && pActual->aDato.id != nId) {
            pAnterior = pActual;
            pActual = pActual->apSiguiente;
        }
        if (pActual == nullptr) return false;

        if (pAnterior == nullptr) {
            apPrimero = pActual->apSiguiente;
        } else {
            pAnterior->apSiguiente = pActual->apSiguiente;
        }
        if (pActual == apUltimo) {
            apUltimo = pAnterior;
        }
        delete pActual;
        aCantidad--;
        return true;
    }
};

#endif
