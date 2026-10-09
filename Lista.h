#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
#include "Contadores.h"
#include "Tarea.h"

template <typename Dato>
class Lista {
private:
    Nodo<Dato> *apPrimero;
    Nodo<Dato> *apUltimo;
    int aSiguienteId;
    int aCantidad;
    Contadores aContadores;

    Nodo<Dato>* BuscarNodo(int nId) {
        Nodo<Dato> *pActual = apPrimero;
        while (pActual != nullptr) {
            aContadores.nodosVisitados++;
            aContadores.comparaciones++;
            if (pActual->aDato.id == nId) return pActual;
            pActual = pActual->apSiguiente;
        }
        return nullptr;
    }

    void AcumularDescendientes(int nIdPadre, ResumenTrabajo &rResumen) {
        Nodo<Dato> *pActual = apPrimero;
        while (pActual != nullptr) {
            aContadores.nodosVisitados++;
            aContadores.comparaciones++;
            if (pActual->aDato.idPadre == nIdPadre) {
                SumarTrabajo(pActual->aDato, rResumen);
                AcumularDescendientes(pActual->aDato.id, rResumen);
            }
            pActual = pActual->apSiguiente;
        }
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

public:
    Lista() {
        apPrimero = nullptr;
        apUltimo = nullptr;
        aSiguienteId = 1;
        aCantidad = 0;
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

    bool Insertar(const Dato &nDato) {
        if (nDato.idPadre != 0 && BuscarNodo(nDato.idPadre) == nullptr) {
            return false;
        }
        AgregarFinal(nDato);
        return true;
    }

    Dato* BuscarPorId(int nId) {
        Nodo<Dato> *pNodo = BuscarNodo(nId);
        if (pNodo == nullptr) return nullptr;
        return &(pNodo->aDato);
    }

    bool ResumenDescendientes(int nId, ResumenTrabajo &rResumen) {
        rResumen = ResumenTrabajo();
        Nodo<Dato> *pNodo = BuscarNodo(nId);
        if (pNodo == nullptr) return false;
        SumarTrabajo(pNodo->aDato, rResumen);
        AcumularDescendientes(nId, rResumen);
        return true;
    }

    bool EstaVacia() const {
        return apPrimero == nullptr;
    }

    int Elementos() const {
        return aCantidad;
    }

    const Contadores& ObtenerContadores() const {
        return aContadores;
    }

    void ReiniciarContadores() {
        aContadores.Reiniciar();
    }
};

#endif
