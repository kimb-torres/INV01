#ifndef ARBOL_H
#define ARBOL_H
#include "NodoArbol.h"
#include "Contadores.h"
#include "Tarea.h"

template <typename Dato>
class Arbol {
private:
    NodoArbol<Dato> *apRaiz;
    Contadores aContadores;

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
        aContadores.nodosVisitados++;
        aContadores.comparaciones++;
        if (pNodo->aDato.id == nId) return pNodo;

        NodoArbol<Dato> *pHijo = pNodo->PrimerHijo();
        while (pHijo != nullptr) {
            NodoArbol<Dato> *pEncontrado = BuscarNodo(pHijo, nId);
            if (pEncontrado != nullptr) return pEncontrado;
            pHijo = pHijo->SiguienteHermano();
        }
        return nullptr;
    }

    void InsertarHijo(NodoArbol<Dato> *pPadre, NodoArbol<Dato> *pNuevo) {
        pNuevo->AsignarPadre(pPadre);

        NodoArbol<Dato> *pActual = pPadre->PrimerHijo();
        if (pActual == nullptr) {
            pPadre->AsignarPrimerHijo(pNuevo);
            return;
        }
        aContadores.nodosVisitados++;
        while (pActual->SiguienteHermano() != nullptr) {
            pActual = pActual->SiguienteHermano();
            aContadores.nodosVisitados++;
        }
        pActual->AsignarSiguienteHermano(pNuevo);
    }

    void AcumularSubarbol(NodoArbol<Dato> *pHijo, ResumenTrabajo &rResumen) {
        while (pHijo != nullptr) {
            aContadores.nodosVisitados++;
            SumarTrabajo(pHijo->aDato, rResumen);
            AcumularSubarbol(pHijo->PrimerHijo(), rResumen);
            pHijo = pHijo->SiguienteHermano();
        }
    }

public:
    Arbol() {
        Dato raiz = Dato();
        raiz.id = 0;
        raiz.idPadre = -1;
        apRaiz = new NodoArbol<Dato>(raiz);
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

    bool ResumenDescendientes(int nId, ResumenTrabajo &rResumen) {
        rResumen = ResumenTrabajo();
        if (nId == 0) return false;
        NodoArbol<Dato> *pNodo = BuscarNodo(apRaiz, nId);
        if (pNodo == nullptr) return false;
        SumarTrabajo(pNodo->aDato, rResumen);
        AcumularSubarbol(pNodo->PrimerHijo(), rResumen);
        return true;
    }

    const Contadores& ObtenerContadores() const {
        return aContadores;
    }

    void ReiniciarContadores() {
        aContadores.Reiniciar();
    }
};

#endif
