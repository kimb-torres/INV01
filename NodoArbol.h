#ifndef NODOARBOL_H
#define NODOARBOL_H

template <typename Dato>
struct NodoArbol {
    Dato aDato;
    NodoArbol<Dato> *apPrimerHijo;
    NodoArbol<Dato> *apSiguienteHermano;
    NodoArbol<Dato> *apPadre;

    NodoArbol(const Dato &nDato) {
        aDato = nDato;
        apPrimerHijo = nullptr;
        apSiguienteHermano = nullptr;
        apPadre = nullptr;
    }

    Dato& ObtenerDato() {
        return aDato;
    }

    NodoArbol<Dato>* PrimerHijo() const {
        return apPrimerHijo;
    }

    NodoArbol<Dato>* SiguienteHermano() const {
        return apSiguienteHermano;
    }

    NodoArbol<Dato>* ReturnPadre() const {
        return apPadre;
    }

    void AsignarPadre(NodoArbol<Dato> *pPadre) {
        apPadre = pPadre;
    }

    void AsignarPrimerHijo(NodoArbol<Dato> *pHijo) {
        apPrimerHijo = pHijo;
    }

    void AsignarSiguienteHermano(NodoArbol<Dato> *pHermano) {
        apSiguienteHermano = pHermano;
    }
};

#endif
