#ifndef CONTADORES_H
#define CONTADORES_H

struct Contadores {
    long comparaciones;
    long nodosVisitados;

    Contadores() {
        Reiniciar();
    }

    void Reiniciar() {
        comparaciones = 0;
        nodosVisitados = 0;
    }
};

#endif
