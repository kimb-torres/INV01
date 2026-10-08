#ifndef NODO_H
#define NODO_H

template <typename Dato>
struct Nodo {
    Dato aDato;
    Nodo<Dato> *apSiguiente;
    int id;

    Nodo(const Dato &nDato, int nId) {
        aDato = nDato;
        id = nId;
        apSiguiente = nullptr;
    }

    Nodo<Dato>* siguienteNodo() const {
        return apSiguiente;
    }

    int Id() const {
        return id;
    }

    Dato returnDato() const {
        return aDato;
    }
};

#endif
